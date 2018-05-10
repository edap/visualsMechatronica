#version 150
#pragma include "shaders_gl3/libs/mercury.glsl"

uniform sampler2D tex4;
uniform vec2 resolution;
uniform float beat;
uniform float iGlobalTime;
uniform float sdf2;
in vec2 vTexCoord;
out vec4 fragColor;
uniform float sdfOpStairs;

const int MAX_MARCHING_STEPS = 64;
const float EPSILON = 0.0001;
const float NEAR_CLIP = 0.0;
const float FAR_CLIP = 100.00;


// noise
float hash(float n) { return fract(sin(n) * 1e4); }
float noise(float x) {
        float i = floor(x);
        float f = fract(x);
        float u = f * f * (3.0 - 2.0 * f);
        return mix(hash(i), hash(i + 1.0), u);
}

vec3 lightDirection = normalize(vec3(1.0, 0.6, 1.));

vec2 rotate(vec2 pos, float angle){
    float c = cos(angle);
    float s = sin(angle);
    return mat2(c, s, -s, c) * pos;
}

float map(vec3 pos){
    float freq = .2;
    float time = iGlobalTime*freq;
    float grid = 4.;
    float mov = grid*2.;

    if( fract(time)>0.5 ){
        pos.z -= fract(time) * mov;
        pos.xy = rotate(pos.xy, fract(time)*PI);
    } else {
        pos.x += fract(time) * mov;
    }

    pMod3(pos, vec3(grid, grid, grid));
    float sdfOpRadius = clamp((sdf2*0.2), .74, 0.95);
    float blob = fBlob(pos);
    float oct = fOctahedron(pos, 0.6);
    return fOpDifferenceColumns(blob,oct,sdfOpRadius , 2);
}

vec2 squareFrame(vec2 res, vec2 coord){
    vec2 uv = 2.0 * coord.xy / res.xy - 1.0;
    uv.x *= res.x / res.y;
    return uv;
}

float raymarching(vec3 eye, vec3 marchingDirection){
    float depth = NEAR_CLIP;
    for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
        float dist = map(eye + depth * marchingDirection);
        if (dist < EPSILON){
            return depth;
        }

        depth += dist;

        if (depth >= FAR_CLIP) {
            return FAR_CLIP;
        }
    }
    return FAR_CLIP;
}

vec3 computeNormal(vec3 pos){
    vec2 eps = vec2(0.01, 0.);
    return normalize(vec3(
                          map(pos + eps.xyy) - map(pos - eps.xyy),
                          map(pos + eps.yxy) - map(pos - eps.yxy),
                          map(pos + eps.yyx) - map(pos - eps.yyx)
                          ));
}

float diffuse(vec3 normal){
    float ambient = 0.5;
    return clamp( dot(normal, lightDirection) * ambient + ambient, 0.0, 1.0 );
}

float specular(vec3 normal, vec3 dir){
    vec3 h = normalize(normal - dir);
    float specularityCoef = 100.;
    return clamp( pow(max(dot(h, normal), 0.), specularityCoef), 0.0, 1.0);
}

float fresnel(vec3 normal, vec3 dir){
    return pow( clamp(1.0+dot(normal,dir),0.0,1.0), 2.0 );
}

vec3 getRefTexture(vec3 normal, vec3 dir) {
    vec3 eye = -dir;
    vec3 r = reflect( eye, normal );
    vec4 color = texture(tex4, (0.5 * (r.xy) + .5));
    return color.xyz;
}

vec3 calculateColor(vec3 pos, vec3 dir){
    vec3 normal = computeNormal(pos);
    vec3 color;

    vec3 colTex = getRefTexture(normal, dir);
    float diffLight = diffuse(normal);
    float specLight = specular(normal, dir);
    float fresnelLight = fresnel(normal, dir);
    color = (diffLight + specLight + fresnelLight) * colTex;
    return color;
}

vec3 calculateColor2(vec3 pos, vec3 dir){
  //light via https://vimeo.com/124721382
  vec3 nor = computeNormal(pos);

  vec3 lig = normalize(vec3(1.,-1.,1.));
  float NL = max(dot(nor, lig),0.);
  float NV = max(dot(nor, -dir),0.);
  NV =  pow(1.-NV, 3.);

  float bli =  max(dot(normalize(lig+-dir), nor), 0.);
  bli = pow(bli, 80.);

  float c = NL + NV * 0.5 + bli;
  return vec3(c) * getRefTexture(nor, dir);
}


mat3 setCamera( in vec3 ro, in vec3 ta, float cr ){
    vec3 cw = normalize(ta-ro);
    vec3 cp = vec3(sin(cr), cos(cr),0.0);
    vec3 cu = normalize( cross(cw,cp) );
    vec3 cv = normalize( cross(cu,cw) );
    return mat3( cu, cv, cw );
}

void main(){
    vec2 uv = squareFrame(resolution.xy, gl_FragCoord.xy);
    float x = -1.8 + noise(iGlobalTime * 0.5) * 8.8;
    //vec3 eye = vec3(-1.8, -2.5, 19);
    vec3 eye = vec3(0., 0., 14.5);

    //vec3 ta = vec3( -0.5, -0.9, 0.5 );
    vec3 ta = vec3( -0.0, -1.0, 0. );
    mat3 camera = setCamera( eye, ta, 0.0 );
    float fov = 3.0;
    vec3 dir = camera * normalize(vec3(uv, fov));

    float shortestDistanceToScene = raymarching(eye, dir);


    vec3 color;
    vec3 bgColor = vec3(0.0, 0.0, 0.0);

    if (shortestDistanceToScene < FAR_CLIP - EPSILON) {
        vec3 collision = (eye += (shortestDistanceToScene*0.99) * dir );
        color = calculateColor(collision, dir);

        float fogFactor = exp(collision.z * 0.001);
        color = mix(bgColor, color, fogFactor);
    } else {
        color = bgColor;
    }

    fragColor = vec4(color , 1.0);
}
