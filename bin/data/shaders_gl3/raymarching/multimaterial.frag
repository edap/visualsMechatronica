#version 150
#pragma include "shaders_gl3/libs/mercury.glsl"

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec2 resolution;
uniform float iGlobalTime;

in vec2 vTexCoord;
out vec4 fragColor;

const int MAX_MARCHING_STEPS = 64;
const float EPSILON = 0.0011;
const float NEAR_CLIP = 0.0;
const float FAR_CLIP = 100.00;
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

float opScaleBlob( vec3 p, float s ){
    return fBlob(p/s)*s;
}

vec2 sminsMat(vec2 a, vec2 b){
    float d = smins(a.x, b.x);
    vec2 aMat = vec2(d, a.y);
    vec2 bMat = vec2(d, b.y);
    return (a.x < b.x) ? aMat: bMat;
}

float sdfSphere(vec3 pos, float radius){
    return length(pos) - radius;
}

float sdTorus( vec3 p, vec2 t ){
    vec2 q = vec2(length(p.xz)-t.x,p.y);
    return length(q)-t.y;
}

float bendTorusOld( vec3 p, vec2 dim ){
    //float wave = sin(iGlobalTime * 0.2) * 2.2;
    float wave = 0.6;
    float amp = 1.1;
    float c = cos(wave*p.y) * amp;
    float s = sin(wave*p.y) * amp;
    mat2  m = mat2(c,-s,s,c);
    vec3  q = vec3(m*p.xy,p.z);
    //return sdTorus(q, dim);
    return sdTorus(p, dim);
}

float bendTorus( vec3 p, vec4 dim ){
    float blob = opScaleBlob(p, (dim.x));
    float capsule = fCapsule(p, dim.y, dim.w);
    return fOpDifferenceRound(blob,capsule,dim.z);
}

vec2 map(vec3 pos){
    float freqOnYZ = .1;
    float freqOnXZ = .4;
    float yOscFreq = 0.2;
    pos.yz = rotate(pos.yz, PI/1.4);
    pos.xy = rotate(pos.xy, PI/1.3);

    //pos.xz = rotate(pos.xz, sin(iGlobalTime*freqOnXZ)*1.6);
    //pos.xy = rotate(pos.xy, PI/2.);

    vec3 s6pos = vec3(0.5, sin(iGlobalTime*(yOscFreq*2.)) * 1.3, -1.1);
    vec3 s5pos = vec3(0.5, cos(iGlobalTime*(yOscFreq*4.)) * 4.4, -1.1);
    vec3 s4pos = vec3(0.5, sin(iGlobalTime*(yOscFreq*4.)) * 3.9, -1.1);
    vec3 s3pos = vec3(0.5, cos(iGlobalTime*(yOscFreq*4.)) * 6.9, -1.1);
    vec3 s2pos = vec3(0.5, sin(iGlobalTime*(yOscFreq*5.)) * 6.4, -1.1);

    float sRadius = 4.5;
    float s2 = bendTorus(pos - s2pos,vec4(1.9, 1.9, 0.8, 0.5));
    float s3 = bendTorus(pos - s3pos,vec4(2.3, 2.4, 0.9, .9));
    float s4 = bendTorus(pos - s4pos,vec4(3.1, 3.2, 0.845, 2.2));
    float s5 = bendTorus(pos - s5pos,vec4(4.6, 4.8, 0.97, 2.2));
    float s6 = bendTorus(pos - s6pos,vec4(5.6, 7.0, 0.3, 4.1));

    vec2 s2M = vec2(s2, 0.2);
    vec2 s3M = vec2(s3, 0.3);
    vec2 s4M = vec2(s4, 0.1);
    vec2 s5M = vec2(s5, 0.2);
    vec2 s6M = vec2(s6, 0.1);

    return sminsMat(s6M, sminsMat(s5M, sminsMat(s4M, sminsMat(s3M, s2M))));
}

vec2 squareFrame(vec2 res, vec2 coord){
    vec2 uv = 2.0 * coord.xy / res.xy - 1.0;
    uv.x *= res.x / res.y;
    return uv;
}

vec2 raymarching(vec3 eye, vec3 marchingDirection){
    // the x value store the depth distance, the y the material
    vec2 res = vec2(NEAR_CLIP, 0.);
    for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
        vec2 distAndMat = map(eye + res.x * marchingDirection);
        res.y = distAndMat.y;
        if (distAndMat.x < EPSILON){
            return res;
        }
        res.x += distAndMat.x;

        if (distAndMat.x >= FAR_CLIP) {
            res.x = FAR_CLIP;
            return res;
        }
    }
    res.x = FAR_CLIP;
    return res;
}

float softshadow( in vec3 ro, in vec3 rd, in float mint, in float tmax ) {
    float res = 1.0;
    float t = mint;
    for( int i=0; i<16; i++ ) {
        float h = map( ro + rd*t ).x;
        res = min( res, 8.0*h/t );
        t += clamp( h, 0.02, 0.10 );
        if( h<0.001 || t>tmax ) break;
    }
    return clamp( res, 0.0, 1.0 );
}


float ao( in vec3 pos, in vec3 nor ){
    float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ ){
        float hr = 0.01 + 0.06*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos ).x;
        occ += -(dd-hr)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 );
}

vec3 computeNormal(vec3 pos){
    vec2 eps = vec2(0.01, 0.);
    return normalize(vec3(
                          map(pos + eps.xyy).x - map(pos - eps.xyy).x,
                          map(pos + eps.yxy).x - map(pos - eps.yxy).x,
                          map(pos + eps.yyx).x - map(pos - eps.yyx).x
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

vec3 getRefTexture(vec3 normal, vec3 dir, float mat) {
    vec3 eye = -dir;
    vec3 r = reflect( eye, normal );
    vec4 color;
    if (mat == 0.1) {
        color = texture(tex0, (0.5 * (r.xy) + .5));
    }
    else if (mat == 0.2) {
        color = texture(tex1, (0.5 * (r.xy) + .5));
    }
    else if (mat == 0.3) {
        color = texture(tex2, (0.5 * (r.xy) + .5));
    };
    return color.xyz;
}

vec3 calculateColor(vec3 pos, vec3 dir, float mat){
    vec3 normal = computeNormal(pos);
    vec3 color;

    vec3 colTex = getRefTexture(normal, dir, mat);
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
    vec3 eye = vec3(0.5, 3.0,19.5);

    vec3 ta = vec3( -0.5, -0.9, 0.5 );
    mat3 camera = setCamera( eye, ta, 0.0 );
    float fov = 2.8;
    vec3 dir = camera * normalize(vec3(uv, fov));

    vec2 distanceAndMat = raymarching(eye, dir);
    float shortestDistanceToScene = distanceAndMat.x;
    float mat = distanceAndMat.y;

    vec3 color;
    //vec3 bgColor = vec3(0.1, 0.35, 0.75);
    vec3 bgColor = vec3(0.0, 0.0, 0.0);

    if (shortestDistanceToScene < FAR_CLIP - EPSILON) {
        vec3 collision = (eye += (shortestDistanceToScene*0.995) * dir );
        float shadow  = softshadow(collision, lightDirection, 0.02, 2.5 );
        color = calculateColor(collision, dir, mat);

        shadow = mix(shadow, 1.0, 0.7);
        color = color * shadow;
        float fogFactor = exp(collision.z * 0.04);
        color = mix(bgColor, color, fogFactor);
    } else {
        color = bgColor;
    }

    fragColor = vec4(color, 1.0);
}
