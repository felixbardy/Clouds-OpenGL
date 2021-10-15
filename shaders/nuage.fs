#version 330 core

#define PI 3.1415926538
#define TWO_PI 6.2831853076

uniform mat4 mvpInvMatrix;
uniform mat4 mvMatrix;

uniform sampler3D texture1;
uniform sampler3D texture2;

// coordonées de la boîte à nuages
uniform vec3 vmin;
uniform vec3 vmax;

uniform vec3 SunPos;
uniform float SunPower;
uniform vec3 SunColor;

uniform float lightMultiplicator;

uniform float time;

uniform float temperature; // Plus froid = plus dense

uniform int CloudSamples;
uniform int LightingSamples;

uniform int ScatteringFactor;
uniform int AbsorptionFactor;
uniform int ExtinctionFactor;

uniform vec3 IsotropicLightBottom;
uniform vec3 IsotropicLightTop;

in vec2 position;

out vec4 fragment_color;

// Approximation de l'intégrale exponentielle par développement limité
float Ei( float z ) 
{ 
  return 0.5772156649015328606065 + log( 1e-4 + abs(z) ) + z * (1.0 + z * (0.25 + z * ( (1.0/18.0) + z * ( (1.0/96.0) + z * (1.0/600.0) ) ) ) ); // For x!=0 
}

float angleBetweenNormedVec3(vec3 u, vec3 v)
{
    float angle = acos(dot(u,v));
    if (angle > PI) angle = TWO_PI - angle;
    return angle;
}

vec2 cloudBoxIntersection(vec3 ray_o, vec3 ray_d)
{
    float temp;
    float tmin = (vmin.x - ray_o.x) / ray_d.x; 
    float tmax = (vmax.x - ray_o.x) / ray_d.x; 
 
    if (tmin > tmax) {temp=tmin; tmin=tmax; tmax=temp;} 
 
    float tymin = (vmin.y - ray_o.y) / ray_d.y; 
    float tymax = (vmax.y - ray_o.y) / ray_d.y; 
 
    if (tymin > tymax) {temp=tymin; tymin=tymax; tymax=temp;}
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return vec2(-1,-1);
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (vmin.z - ray_o.z) / ray_d.z; 
    float tzmax = (vmax.z - ray_o.z) / ray_d.z; 
 
    if (tzmin > tzmax) {temp=tzmin; tzmin=tzmax; tzmax=temp;}
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return vec2(-1,-1); 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
    
    //FIXME Renvoyer Tmin et Tmax
    return vec2(tmin,tmax); 
}


float rayleighPhase(float angle)
{
    float cosvalue = cos(angle);
    return 3.0/8.0 * (1 + cosvalue*cosvalue);
}


float sampleDensity(vec3 pos) {
    //TODO Mixer les textures avec des paramètres d'Amplitude et de fréquence
    pos.x = mod(pos.x, 1.0);
    pos.y = mod(pos.y, 1.0);
    pos.z = mod(pos.z, 1.0);

    //return 1;
    return texture(texture1, pos).x;
    
}

vec3 getSunColorAtPoint(vec3 position) {
    // Au début, on a aucune extinction (on multiplie la couleur par 1)
    float extinction = 1.0;


    vec3 dir = normalize(-SunPos);
    vec2 tminmax = cloudBoxIntersection(position-dir, dir);
    vec3 origin = position + tminmax.x*dir;
    vec3 end = position;

    float raylength = length(end-origin);
    //? Le rayon part du soleil
    float sun_phase = rayleighPhase(0);

    float stepSize = raylength / LightingSamples;

    for (int i = 0; i < LightingSamples; i++) {
        vec3 pos = origin + i*stepSize;

        float density = sampleDensity(pos);
        float extinction_coeff = ExtinctionFactor * density;

        extinction *= exp(-extinction_coeff * stepSize);
    }

    // On renvoie la couleur du soleil, atténuée par l'extinction
    return SunColor * extinction;
}

vec3 getAmbientColorAtPoint(vec3 pos, float extinction_coeff) {
    float volume_top = vmax.y;
    float volume_bottom = vmin.y;

    float Hp = volume_top - pos.y;
    float a = -extinction_coeff * Hp;
    vec3 IsotropicScatteringTop = IsotropicLightTop * max(0.0, exp(a) - a * Ei(a));

    float Hb = pos.y - volume_bottom;
    a = -extinction_coeff * Hb;
    vec3 IsotropicScatteringBottom = IsotropicLightBottom * max(0.0, exp(a) - a * Ei(a));

    return IsotropicLightBottom + IsotropicLightTop;
}

vec4 computeCloud(vec3 origin, vec3 end) {
    float extinction = 1.0;
    vec3 scattering = vec3(0.0);


    vec3 dir = normalize(end-origin);
    float raylength = length(end-origin);
    //? On considère le soleil comme étant à une distance infinie (ç.à.d. tous les rayons sont parallèles)
    float sun_phase = rayleighPhase(angleBetweenNormedVec3(dir,normalize(SunPos)));

    float stepSize = raylength / float(CloudSamples);

    for (int i = 0; i < CloudSamples; i++) {
        vec3 pos = origin + i*stepSize;

        float density = sampleDensity(pos);
        float scattering_coeff = ScatteringFactor * density;
        float extinction_coeff = ExtinctionFactor * density;

        extinction *= exp(-extinction_coeff * stepSize);

        vec3 sun_color = getSunColorAtPoint(pos);
        //TODO Remmetre la lumière ambiante
        //vec3 ambient_color = getAmbientColorAtPoint(pos, extinction_coeff);
        vec3 step_scattering = scattering_coeff * stepSize * (sun_phase * sun_color);

        // On rajoute la dispersion de cette étape qu'on atténue avec l'extinction accumulée
        // (moins de lumière a atteint cette étape que ce qu'on avait initialement)
        scattering += extinction * step_scattering;
    }
    return vec4(scattering,extinction);
}



void main() 
{
    //TODO Remplacer par un uniform qui indique la couleur de fond si fragment_color est nul
    fragment_color = vec4(0.4,0.4,0.8,1);

    /*****************/
    /****  MESHS  ****/
    /*****************/


    /*****************/
    /****  NUAGE  ****/
    /*****************/
    // construction du rayon pour le pixel
    vec4 origin_s = mvpInvMatrix * vec4(position, 0, 1); // origine sur near
    vec4 end_s    = mvpInvMatrix * vec4(position, 1, 1); // fin sur far

    // normalisation pour l'expression du rayon
    //? pas compris
    vec3 o = origin_s.xyz / origin_s.w;                         // origine
    vec3 d = normalize(end_s.xyz / end_s.w - origin_s.xyz / origin_s.w); // direction
    
    vec2 itrsect = cloudBoxIntersection(o,d);
    float T_in = itrsect.x;
    float T_out = itrsect.y;

    // Si intersection avec le conteneur de nuages:
    if (T_out >= 0)
    {
        // Prendre en compte le cas où la caméra est dans le conteneur
        if (T_in < 0) T_in = 0;

        // Dispersion en rgb (scattering) et extinction (float)
        vec4 scatt_ext = computeCloud(o + T_in*d, o+T_out*d);

        fragment_color = fragment_color * scatt_ext;
    }
}