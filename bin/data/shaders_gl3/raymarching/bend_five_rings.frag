#version 150

uniform sampler2D tex0;
uniform vec2 resolution;
uniform float iGlobalTime;

in vec2 vTexCoord;
out vec4 fragColor;

const int MAX_MARCHING_STEPS = 64;
const float EPSILON = 0.0011;
const float NEAR_CLIP = 0.0;
const float FAR_CLIP = 100.00;
const float PI = 3.14159265358979323846;

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

float bendTorusA( vec3 p, vec2 dim ){
    float wave = sin(iGlobalTime * 2.2) * 0.3;
    float c = cos(wave*p.y);
    float s = sin(wave*p.y);
    mat2  m = mat2(c,-s,s,c);
    vec3  q = vec3(m*p.xy,p.z);
    return sdTorus(q, dim);
}

float bendTorusB( vec3 p, vec2 dim ){
    float wave = cos(iGlobalTime * 2.2) * 0.4;
    float c = cos(wave*p.y);
    float s = sin(wave*p.y);
    mat2  m = mat2(c,-s,s,c);
    vec3  q = vec3(m*p.xy,p.z);
    return sdTorus(q, dim);
}

float map(vec3 pos){
    float diam = 2.7;
    float thick = 0.8;
    float freqOnXZ = .4;

    pos.xz = rotate(pos.xz, sin(iGlobalTime*freqOnXZ)*1.6);
    pos.xy = rotate(pos.xy, PI/2.);

    vec3 s2pos = pos - vec3(0., 3.0, 0.);
    vec3 s3pos = pos + vec3(0., 3.0, 0.);
    vec3 s4pos = pos - vec3(0., 6., 0.);
    vec3 s5pos = pos + vec3(0., 6., 0.);
    float s1 = bendTorusA(pos, vec2(diam, thick));
    float s2 = bendTorusB(s2pos, vec2(diam, thick));
    float s3 = bendTorusB(s3pos, vec2(diam, thick));
    float s4 = bendTorusA(s4pos, vec2(diam, thick));
    float s5 = bendTorusA(s5pos, vec2(diam, thick));

    return smins(s1, smins(s2, smins(s3, smins(s4, s5))));
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
    vec4 color = texture(tex0, (0.5 * (r.xy) + .5));
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
    vec3 eye = vec3(0.5, 0.0,19.5);

    vec3 ta = vec3( -0.5, 0.0, 0.5 );
    mat3 camera = setCamera( eye, ta, 0.0 );
    float fov = 4.6;
    vec3 dir = camera * normalize(vec3(uv, fov));

    float shortestDistanceToScene = raymarching(eye, dir);

    vec3 color;
    vec3 bgColor = vec3(0.0, 0.0, 0.0);

    if (shortestDistanceToScene < FAR_CLIP - EPSILON) {
        vec3 collision = (eye += (shortestDistanceToScene*0.995) * dir );
        color = calculateColor(collision, dir);
        float fogFactor = exp(collision.z * 0.08);
        color = mix(bgColor, color, fogFactor);
    } else {
        color = bgColor;
    }

    //
    //vec4 color = texture(tex0, (0.5 * (uv.xy) + .5));
    fragColor = vec4(color , 1.0);
    //fragColor = vec4(vec3(1.,0.,0.), 1.);
}
