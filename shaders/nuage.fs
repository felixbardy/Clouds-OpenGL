#version 330 core

// Source: https://fiftylinesofcode.com/ray-sphere-intersection/
// Renvoie -1 sans intrsectio

uniform mat4 mvpInvMatrix;
uniform mat4 mvMatrix;

uniform sampler3D texture1;

// coordonées de la boîte à nuages
uniform vec3 vmin;
uniform vec3 vmax;

uniform float time;

uniform float temperature; // Plus froid = plus dense

in vec2 position;

out vec4 fragment_color;

vec3 random( vec3 p ) 
{
    return fract(sin(vec3(
        dot(p,vec3(127.1,311.7, 214.4)),
        dot(p,vec3(269.5,183.3, 107.5)),
        dot(p,vec3(114.5,413.3, 49.5))
        ))*43758.5453);
}

vec4 worley(vec3 position, bool drawPropagation, bool drawPoint, bool drawGrid)
{
    vec3 st = position;
    st *= 3;
    vec3 i_st = floor(st);
    vec3 f_st = fract(st);
    vec4 color = vec4(0);

    float minDist = 1;

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            for(int z = -1; z <= 1; z++)
            {
                vec3 voisin = vec3(float(x), float(y), float(z));
                vec3 point = random(i_st + voisin);
                //point = 0.5 + 0.5*sin(time + 6.2831*point);
                vec3 diff = voisin + point - f_st;
                float dist = length(diff);
                minDist = min(minDist, dist);
            }
        }
    }

    color += minDist;
    if(drawPropagation)
    {
        // Draw Propagation
        color -= step(.7,abs(sin(50.0*minDist)))*.3;
    }
    
    if(drawPoint)
    {
        // Draw Points
        color.g += 1.-step(.02, minDist);
    }

    if(drawGrid)
    {
        // Draw grid
        color.r += step(.98, f_st.x) + step(.98, f_st.y);
    }

    return vec4(1) - color;
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
    entry = entry - vmin;
    exit = exit - vmin;
    vec3 texcoords;
    vec3 boxdim = vmax - vmin;
    float step_value = 1.0f / float(steps);
    float t;
    float density = 0;
    for (int i = 0; i < steps; i++)
    {
        t = step_value * float(i);
        texcoords = entry * (1 - t) + exit * t;
        texcoords.x /= boxdim.x;
        texcoords.y /= boxdim.y;
        texcoords.z /= boxdim.z;
        vec3 centre = vec3(0.5);
        float delta = 1 - (distance(centre, texcoords));
        density += mix(worley(texcoords, false, false, false).x, texture(texture1, texcoords).x, 0.35) * delta;
    }

    return density / float(steps);

}

void main() 
{
    // construction du rayon pour le pixel
    vec4 origin_s = mvpInvMatrix * vec4(position, 0, 1); // origine sur near
    vec4 end_s    = mvpInvMatrix * vec4(position, 1, 1); // fin sur far

    const vec3 light = vec3(2,0,0); // origine de la lumière
    const float min_light = 0.2; // Luminosité minimum des objets

    // normalisation pour l'expression du rayon
    //? pas compris
    vec3 o = origin_s.xyz / origin_s.w;                         // origine
    vec3 d = normalize(end_s.xyz / end_s.w - origin_s.xyz / origin_s.w); // direction
    
    vec2 itrsect = cloudBoxIntersection(o,d);
    float T_in = itrsect.x;
    float T_out = itrsect.y;
    
    vec4 bgcolor = vec4(0.4, 0.4, 0.8, 1.);

    // Si intersection:
    if (T_out >= 0)
    {
        // Prendre en compte le cas où la caméra est dans le nuage
        if (T_in < 0) T_in = 0;
        //TODO Vrai calcul de densité à partir de la texture3D
        vec3 entry = o + T_in * d;
        vec3 exit = o + T_out * d;
        float density = computeCloudDensity(entry, exit, 25);

        // Une densité inférieure à density_offset donnera un espace vide
        float density_offset = 0.25;
        density = max(density - density_offset, 0) / (1.0 - density_offset);
        fragment_color = bgcolor * exp(-density);
    }
    // Si pas d'intersection:
    else  fragment_color = bgcolor;
    
    
}