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

uniform vec3 lightpos;
uniform float lightpower;

uniform float lightMultiplicator;

uniform float time;

uniform float temperature; // Plus froid = plus dense

in vec2 position;

out vec4 fragment_color;

float angle_between_normed_vec3(vec3 u, vec3 v)
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

float computeCloudDensity(vec3 entry, vec3 exit, int steps)
{
}

float getIlluminationAtPoint(vec3 point)
{
}

float rayleighPhase(float angle)
{
    float cosvalue = cos(angle);
    return 3.0/8.0 * (1 + cosvalue*cosvalue);
}

float getLightAlongRay(vec3 entry, vec3 exit, int steps)
{
}

void main() 
{
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
        
    
}