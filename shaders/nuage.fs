#version 330 core

#define PI 3.1415926538
#define TWO_PI 6.2831853076

uniform mat4 vpInvMatrix;
uniform mat4 mvpInvMatrix;
uniform mat4 mvMatrix;

uniform sampler3D shape;
uniform sampler3D detail;

// coordonées de la boîte à nuages
uniform vec3 vmin;
uniform vec3 vmax;

uniform vec3 SunPos;
uniform float SunPower;
uniform vec3 SunColor;

uniform float time;

uniform float temperature; // Plus froid = plus dense

uniform int CloudSamples;
uniform int LightingSamples;

uniform int ScatteringFactor;
uniform int AbsorptionFactor;
uniform int ExtinctionFactor;

uniform vec3 IsotropicLightBottom;
uniform vec3 IsotropicLightTop;

in vec3 position;

out vec4 fragment_color;

// WEATHER MAP
uniform sampler2D weathermap;

uniform float globalCoverage;
uniform float globalDensity;
uniform float anvilAmount;

uniform float minDensity;
uniform float maxDensity;

uniform float minHeight;
uniform float maxHeight;

// LIGHT UNIFORM

uniform float extraIntensity;
uniform float centralizedValue;
uniform float cloudDensityImpact;
uniform float lightAbsorbtion;
uniform float clampAttenuation;

// coordonées de la boîte à nuages

uniform vec3 lightpos;
uniform float lightpower;

uniform float lightMultiplicator;


/// UTILITY ///
/** clamp la valeur en paramètre entre 0 et 1
*   r -> valeur a clamper
*/
float saturation(float r)
{
    return clamp(r, 0.0, 1.0);
}

/** Transforme une valeur de l'intervalle 0 [l0, h0] en une valeur de l'intervale n [ln, hn]
* v -> valeur d'entrée a remapper
* l0 -> valeur basse de I0
* h0 -> valeur haute de I0
* ln -> valeur basse de IN
* hn -> valeur basse de IN
*/
float remap(float v, float l0 , float h0 , float ln ,float hn)
{
    return ln + (v - l0) * (hn - ln) / (h0 - l0); 
}
/// WEATHER MAP FUNCTION ///  

/** Renvoit la valeur de localisation dans la weather map du fragment actuel
* c0 -> [0, 1] valeur dans le rouge
* c1 -> [0, 1] valeur dans le vert (bruit)
*/
float weatherMapCoverage(float c0, float c1)
{
    return max(c0, saturation(globalCoverage - 0.5) * c1 * 2.0);
}

/// HEIGHT FUNCTION ///

/** arondie le nuage en bas
* y -> [0, 1] hauteur dans le cube
*/
float roundShapeBottom(float y)
{
    return saturation(remap(y, 0, 0.07, 0, 1));
}

/** arondie le nuage en haut
* y -> [0, 1] hauteur dans le cube
* weatherHeight -> [0, 1] hauteur max dans la weather map
*/
float roundShapeTop(float y, float weatherHeight)
{
    return saturation(remap(y, weatherHeight * 0.2, weatherHeight, 1, 0));
}

/** arondie le nuage
* y -> [0, 1] hauteur dans le cube
* weatherHeight -> [0, 1] hauteur max dans la weather map
*/
float roundShape(float y, float weatherHeight)
{
    return pow(roundShapeBottom(y) * roundShapeTop(y, weatherHeight), saturation(remap(y, 0.65, 0.95, 1, 1 - anvilAmount * globalCoverage)));
}

/// DENSITY FUNCTION ///

/** reduit la densité du nuage en bas
* y -> [0, 1] hauteur dans le cube
*/
float densityReductionBottom(float y)
{
    return y * saturation(remap(y, 0, 0.15, 0, 1));
}

/** reduit la densité du nuage en haut
* y -> [0, 1] hauteur dans le cube
*/
float densityReductionTop(float y)
{
    return y * saturation(remap(y, 0.9, 1.0, 1, 0));
}

/** Altère la densité du nuage
* y -> [0, 1] hauteur dans le cube
* weatherDensity -> [0, 1] densité actuel dans la weather map
*/
float densityReduction(float y, float weatherDensity)
{
    return (globalDensity * densityReductionBottom(y) * densityReductionTop(y) * 1 * 2) * mix(1, saturation(remap(sqrt(y), 0.4, 0.95, 1, 0.2)), 1);
}

/// SHAPE FUNCTION ///
/** Recupere la valeur de la texture de forme
*   position -> xyz[0, 1] position actuel dans la texture
*/
float shapeNoiseSample(vec3 position)
{
    vec4 Shape = texture(shape, position);
    return remap(Shape.r, (Shape.g * 0.625 + Shape.b * 0.25 + Shape.a * 0.125) - 1, 1, 0, 1);
}

/** calcul la forme du nuage a cette endroit du rayon
*   position -> xyz[0, 1] position actuel dans la texture
*/
float getShape(vec3 position, float weatherHeight, float c0, float c1, float weatherDensity)
{
    return remap(shapeNoiseSample(position) * roundShape(position.y, weatherHeight), 
                1 - globalCoverage * weatherMapCoverage(c0, c1), 
                1, 
                0, 
                1) * densityReduction(position.y, weatherDensity);
}

/// DETAIL FUNCTION
/** Recupere la valeur de la texture de détails
*   position -> xyz[0, 1] position actuel dans la texture
*/
float detailNoiseSample(vec3 position)
{
    vec4 Detail = texture(detail, position);
    return Detail.r * 0.625 + Detail.g * 0.25 + Detail.b * 0.125;
}

/** calcul les détails du nuage a cette endroit du rayon
*   position -> xyz[0, 1] position actuel dans la texture
*/
float getDetail(vec3 position)
{
    float sample = detailNoiseSample(position);
    return 0.35 * exp(-globalCoverage * 0.75) * mix(sample, 1 - sample, saturation(position.y * 5));
}

/// NOISE COMBINING FUNCTION
/** calcul la forme FINAL du nuage a cette endroit du rayon
*   position -> xyz[0, 1] position actuel dans la texture
*   weatherHeight -> hauteur dans la weather map
*   c0 -> [0, 1] coverage rouge du ciel
*   c1 -> [0, 1] coverage vert(bruit) du ciel
*/
float getCloudNoise(vec3 position, float weatherHeight, float c0, float c1, float densityValue)
{
    return saturation(remap(getShape(position, weatherHeight, c0, c1, densityValue), getDetail(position), 1, 0, 1));
}

/// END WEATHER MAP FUNCTION

/// WM LIGHT
/** Calcul simplifié de la loi de beer lambert, sert a déterminer l'atténuation lumineuse
*   sunAccumulatedDensity -> [0, inf] Densité accumulé jusqu'au soleil
*   lightAbsorbtion -> [0, inf] Lumiere a absorber 
*/
float beerLaw(float sunAccumulatedDensity)
{
    return exp(-lightAbsorbtion * sunAccumulatedDensity);
}

/** henyey-greenstein phase function, sert a calculer la diffusion de la lumiere
*   angleSunRay -> [-1, 1] produit scalaire entre la direction du soleil et la direction du rayon de la caméra
*   scattering -> [-1, 1] intervalle entre la "rétrodiffusion",  isotropique et la diffusion d'intérieur
*/
float HGPhase(float angleSunRay, float scattering)
{
    return (1 / 4 * PI) * ((1 - scattering * scattering) / pow(1 + (scattering * scattering) - 2 * (scattering *cos(angleSunRay) ), 3.0/2.0));
}

/** Utilisé pour crée des couchert de soleil plus intense
*   angleSunRay -> [-1, 1] produit scalaire entre la direction du soleil et la direction du rayon de la caméra
*
*   extraIntensity -> Intensité ajouté autour du soleil
*   centralizedValue -> décalage par rapport au centre du soleil
*/
float extraScattering(float angleSunRay)
{
    return extraIntensity * pow(saturation(angleSunRay), centralizedValue);
}

/** Fonction de diffusion interieur/exterieur
*   angleSunRay -> [-1, 1] produit scalaire entre la direction du soleil et la direction du rayon de la caméra
*   iScat -> [-1, 1] diffusion d'intérieur (in-scatter, pas sur pour la trad sorry)
*   oScat -> [-1, 1] intervalle entre la "rétrodiffusion",  isotropique et la diffusion d'intérieur
*   scatTransition -> [0, 1] valeur d'interpolation
*/
float inOutScattering(float angleSunRay, float iScat, float oScat, float scatTransition)
{
    return mix(max(HGPhase(angleSunRay, iScat), extraScattering(angleSunRay)), HGPhase(angleSunRay, -oScat), scatTransition);
}

/** Sert a avoir des bord plus foncé, surtout pour les nuages façant le soleil
*   y -> [0, 1] hauteur dans le cube
*   oScat -> [-1, 1] diffusion d'exterieur (out-scatter, pas sur pour la trad sorry)
*   cloudDensity -> [0, 1] densité du nuage en ce point
*
*   
*/
float extraOutScattering(float y, float oScat, float cloudDensity)
{
    return 1 - saturation(oScat * pow(cloudDensity, remap(y, 0.3, 0.9, 0.5, 1.0))) * saturation(pow(remap(y, 0, 0.3, 0.8, 1.0), 0.8));
}

/** Sert a clamper la fonction de beer lambert (L'atténuation lumineuse)
*   sunAccumulatedDensity -> [0, inf] Densité accumulé jusqu'au soleil
*
*   lightAbsorbtion -> [0, inf] Lumiere a absorber   
*   clampAttenuation -> [0, 1] valeur pour atténuer le clamping
*/
float beerClamping(float sunAccumulatedDensity)
{
    return max(beerLaw(sunAccumulatedDensity), beerLaw(clampAttenuation));
}

/** Ajoute des nuances a beerClamping
*   density -> [0, 1] densité du fragment
*   sunAccumulatedDensity -> [0, inf] Densité accumulé jusqu'au soleil
*
*   lightAbsorbtion -> [0, inf] Lumiere a absorber   
*   clampAttenuation -> [0, 1] valeur pour atténuer le clamping
*/
float densityMinimumAlteration(float density, float sunAccumulatedDensity)
{
    return max(density * cloudDensityImpact, beerClamping(sunAccumulatedDensity));
}

/** Lumiere final
*   density -> [0, 1] densité du fragment
*   sunAccumulatedDensity -> [0, inf] Densité accumulé jusqu'au soleil
*   y -> [0, 1] hauteur sur le cube de nuage
*   angleSunRay -> [-1, 1] produit cartésien entre le soleil et le rayon de la caméra
*   iScat -> [0, 1] nombre de diffusion interieur
*   oScat -> [0, 1] nombre de diffusion exterieur
*   scatTransition -> [0, 1] interpolation in out
*
*   lightAbsorbtion -> [0, inf] Lumiere a absorber   
*   clampAttenuation -> [0, 1] valeur pour atténuer le clamping
*/
float lightFinal(float density, float sunAccumulatedDensity, float y, float angleSunRay, float iScat, float oScat, float scatTransition)
{
    return densityMinimumAlteration(density, sunAccumulatedDensity) 
    * inOutScattering(angleSunRay, iScat, oScat, scatTransition) 
    * extraOutScattering(y, oScat, density);
}
/// END WM LIGHT

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

    return texture(shape, pos).x;
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
    /*****************/
    /****  NUAGE  ****/
    /*****************/
    // construction du rayon pour le pixel
    vec4 origin_s = vpInvMatrix * vec4(position.xy, 0, position.z); // origine sur near
    vec4 end_s    = vpInvMatrix * vec4(position.xy, 1, position.z); // fin sur far

    // normalisation pour l'expression du rayon
    //? pas compris
    vec3 o = origin_s.xyz / origin_s.w;                         // origine
    vec3 d = normalize(end_s.xyz / end_s.w - origin_s.xyz / origin_s.w); // direction

    vec2 itrsect = cloudBoxIntersection(o,d);
    float T_in = itrsect.x;
    float T_out = itrsect.y;

    // TRUC MANQUANT //
    vec4 bgcolor = vec4(0.5, 0.5, 1.0, 1.0);
    vec4 lightcolor = vec4(1.0, 1.0, 1.0, 1.0);
    fragment_color = vec4(1.0);
    float lum = 1;

    

    // Si intersection avec le conteneur de nuages:
    if (T_out >= 0)
    {
        // Prendre en compte le cas où la caméra est dans le conteneur
        if (T_in < 0) T_in = 0;

        // Dispersion en rgb (scattering) et extinction (float)
        vec4 scatt_ext = computeCloud(o + T_in*d, o+T_out*d);

         fragment_color= fragment_color * scatt_ext;
    }
    // Si pas d'intersection:
    else    fragment_color = vec4(0.0);

    // Affichage lumière
    vec3 dir_to_light = normalize(lightpos - o);
    float angle = angleBetweenNormedVec3(d, dir_to_light);
    // 0.03490658503988659rad ~= 2deg
    if ( angle < 0.03490658503988659 && angle > -0.03490658503988659) {
        fragment_color = fragment_color + lightcolor * lum;
        return;
    }
}
