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

float bendTorus( vec3 p, vec2 dim ){
    float wave = sin(iGlobalTime * 0.2) * 2.2;
    float c = cos(wave*p.y);
    float s = sin(wave*p.y);
    mat2  m = mat2(c,-s,s,c);
    vec3  q = vec3(m*p.xy,p.z);
    return sdTorus(p, dim);
}

float map(vec3 pos){
    float freqOnYZ = .1;
    float freqOnXZ = .4;

    pos.yz = rotate(pos.yz, PI/1.4);
    pos.xy = rotate(pos.xy, PI/1.3);

    float yOscFreq = 0.2;
    vec3 s6pos = vec3(0.5, sin(iGlobalTime*(yOscFreq*4.)) * 0.9, -1.1);
    vec3 s5pos = vec3(0.5, cos(iGlobalTime*(yOscFreq*4.)) * 1.8, -1.1);
    vec3 s4pos = vec3(0.5, sin(iGlobalTime*(yOscFreq*4.)) * 2.9, -1.1);
    vec3 s3pos = vec3(0.5, cos(iGlobalTime*(yOscFreq*4.)) * 3.9, -1.1);
    vec3 s2pos = vec3(0.5, sin(iGlobalTime*(yOscFreq*9.)) * 4.4, -1.1);

    float sRadius = 5.5;
    float s2 = bendTorus(pos - s2pos,vec2(sRadius-3.8, 0.7));
    float s3 = bendTorus(pos - s3pos,vec2(sRadius-3.1, 0.3));
    float s4 = bendTorus(pos - s4pos,vec2(sRadius-2.3, 0.4));
    float s5 = bendTorus(pos - s5pos,vec2(sRadius-1.3, 0.5));
    float s6 = bendTorus(pos - s6pos,vec2(sRadius, 0.6));

    return smins(s6, smins(s5, smins(s4, smins(s3, s2))));
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
    float fov = 4.6;
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

    //
    //vec4 color = texture(tex0, (0.5 * (uv.xy) + .5));
    fragColor = vec4(color , 1.0);
    //fragColor = vec4(vec3(1.,0.,0.), 1.);
}
