#version 150
#pragma include "shaders_gl3/libs/mercury.glsl"


uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform sampler2D tex6;

uniform vec2 resolution;
uniform float iGlobalTime;
uniform float sdf1;
uniform float sdf2;
uniform int sdfOp;
uniform float sdfOpRadius;
uniform float sdfOpStairs;
uniform int sdfSolidId1;
uniform int sdfSolidId2;
uniform vec3 solid2Pos;

in vec2 vTexCoord;
out vec4 fragColor;

const int MAX_MARCHING_STEPS = 64;
const float EPSILON = 0.0011;
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

// operations
float smin( float a, float b, float k ){
    float res = exp( -k*a ) + exp( -k*b );
    return -log( res )/k;
}

float smins( float a, float b ){
    return smin(a, b, 3.0);
}

float sdfSphere(vec3 pos, float radius){
    return length(pos) - radius;
}

float sdTorus( vec3 p, vec2 t ){
    vec2 q = vec2(length(p.xz)-t.x,p.y);
    return length(q)-t.y;
}

float bendTorus( vec3 p, vec2 dim ){
    float wave = sin(iGlobalTime * 0.2) * 2.2;
    float c = cos(wave*p.y);
    float s = sin(wave*p.y);
    mat2  m = mat2(c,-s,s,c);
    vec3  q = vec3(m*p.xy,p.z);
    return sdTorus(q, dim);
}

float map(vec3 pos){
    float freqOnYZ = .8;
    float freqOnXZ = .4;

    pos.y += 1.0;
    //pos.xz = rotate(pos.xz, PI/2.);

    float distance = abs(sin(iGlobalTime*0.2) *2.7)/2.;
    vec3 pos1 = pos;
    pos1.x -= distance;
    vec3 pos2 = pos;
    pos2.x += distance;

    float blob1 = fBlob(pos1);
    float blob2 = fBlob(pos2);
    float nStairs = 10.;
    float radius = 1.132;
    //float radius = 1.132;
    return fOpUnionColumns(blob1, blob2,radius, nStairs);
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

float softshadow( in vec3 ro, in vec3 rd, in float mint, in float tmax ) {
    float res = 1.0;
    float t = mint;
    for( int i=0; i<16; i++ ) {
        float h = map( ro + rd*t );
        res = min( res, 8.0*h/t );
        t += clamp( h, 0.02, 0.10 );
        if( h<0.001 || t>tmax ) break;
    }
    return clamp( res, 0.0, 1.0 );
}


float ao( in vec3 pos, in vec3 nor ){
    float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float hr = 0.01 + 0.06*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos );
        occ += -(dd-hr)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 );
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
    float ambient = 0.7;
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
    //tex1.y+= fract(iGlobalTime);
    vec4 color0 = texture(tex0, (0.5 * (r.xy) + .5));
    vec4 color1 = texture(tex1, (0.5 * (r.xy) + .5));
    vec4 color2 = texture(tex2, (0.5 * (r.xy) + .5));
    vec4 color3 = texture(tex3, (0.5 * (r.xy) + .5));
    vec4 color4 = texture(tex4, (0.5 * (r.xy) + .5));
    vec4 color5 = texture(tex5, (0.5 * (r.xy) + .5));
    vec4 color6 = texture(tex6, (0.5 * (r.xy) + .5));

    return color4.xyz;
}

vec3 calculateColor(vec3 pos, vec3 dir){
    vec3 normal = computeNormal(pos);
    vec3 color;

    vec3 colTex = getRefTexture(normal, dir);
    float diffLight = diffuse(normal);
    float specLight = specular(normal, dir);
    float fresnelLight = fresnel(normal, dir);
    float ambientOcc = ao(pos, normal);
    color = (diffLight + specLight + fresnelLight) * colTex;
    return colTex;
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
    vec3 eye = vec3(-1.8, -2.5,19.5);

    vec3 ta = vec3( -0.0, -1., 0. );
    mat3 camera = setCamera( eye, ta, 0.0 );
    float fov = 9.0;
    vec3 dir = camera * normalize(vec3(uv, fov));

    float shortestDistanceToScene = raymarching(eye, dir);

    vec3 color;
    //vec3 bgColor = vec3(0.1, 0.35, 0.75);
    vec3 bgColor = vec3(0.0, 0.0, 0.0);

    if (shortestDistanceToScene < FAR_CLIP - EPSILON) {
        vec3 collision = (eye += (shortestDistanceToScene*0.995) * dir );
        float shadow  = softshadow(collision, lightDirection, 0.02, 2.5 );
        color = calculateColor(collision, dir);

        shadow = mix(shadow, 1.0, 0.7);
        color = color * shadow;
        float fogFactor = exp(collision.z * 0.04);
        color = mix(bgColor, color, fogFactor);
    } else {
        color = bgColor;
    }

    fragColor = vec4(color , 1.0);
}
