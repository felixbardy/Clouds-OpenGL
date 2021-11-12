#ifndef WORLEY_H
#define WORLEY_H

#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/** @class Worley
 * @brief Module générateur de bruit de worley
*/
class Worley
{
    public:

    /** @brief Constructeur par argument
     * @param s resolution du worley
     * @param w largeur de la texture
     * @param h hauteur de la texture
     * @param d profondeur de la texture
     */
    Worley(float s, int w, int h, int d);

    /** @brief Renvoie la valeur du worley en un point donner
     * @param x position en x du point
     * @param y position en y du point
     * @param z position en z du point
     */
    float get3d(float x, float y, float z);

    /** @brief Renvoie la valeur du worley en un point donner
     * @param position position du point
     */
    float get3d(glm::vec3 position);

     /** @brief Renvoie la valeur du worley en un point donner
     * @param x position en x du point
     * @param y position en y du point
     */
    float get2d(float x, float y);

    /** @brief Renvoie la valeur du worley en un point donner
     * @param position position du point
     */
    float get2d(glm::vec2 position);

    /** @brief Mutateur resolution worley
     * @param s nouvelle resolution
     */
    void setScale(float s);

    /** @brief Accesseur resolution worley
     * @return resolution du worley
     */
    float getScale();

    /** @brief Mutateur Largeur worley
     * @param w nouvelle Largeur
     */
    void setWidth(int w);


    /** @brief Mutateur Hauteur worley
     * @param h nouvelle Hauteur
     */
    void setHeight(int h);


    /** @brief Mutateur Profondeur worleyLargeur
     * @param d nouvelle Profondeur
     */
    void setDepth(int d);

   /** @brief Accesseur Largeur worley
     * @return Largeur du worley
     */
    int getWidth();

    /** @brief Accesseur Hauteur worley
     * @return Hauteur du worley
     */
    int getHeight();

    /** @brief Accesseur Profondeur worley
     * @return Profondeur du worley
     */
    int getDepth();
    private:
    
    float m_scale;
    void iniPoint();
    int m_width, m_height, m_depth;
    std::vector<std::vector<std::vector<glm::vec3>>> m_points;
};

#endif // WORLEY_H