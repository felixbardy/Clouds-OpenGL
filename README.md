# Cloud OpenGL

## Description

Objectif: Simulation de nuages volumétriques sur openGL \
État actuel: Mise en place de l'environnement de travail

## Librairies

* **Glad**: \
 Glad est un loader openGL, à réinstaller dans `lib/` si vous rencontrez des problèmes. \
 La librairie peut être [générée ici.](https://glad.dav1d.de/)

* **GLFW**: \
 Gestionnaire de fenêtres pour openGL \
 Installation:

        sudo apt-get update
        sudo apt-get install libglfw3
        sudo apt-get install libglfw3-dev

* **GLM**: \
Librairie de fonctions mathématiques pour openGL

        sudo apt install libglm-dev

## Compilation

La compilation se fait à l'aide d'un Makefile.

* `make` compile le projet
* `make doc` génère la documentation à l'aide de [Doxygen](https://www.doxygen.nl/index.html)

* `make all` compile le projet ET génère la documentation
* `make clean` nettoie les dossiers `bin/` et `obj/`
* `make pentaclean` nettoie `bin/` `obj/` et `doc/`

## Lancement

L'exécutable principal se lance avec `bin/run` à la racine du projet

## Équipe

Développement par:

* **Bastien Ruivo**, L3 Info \
mail: _bastien.ruivo@etu.univ-lyon1.fr_

* **Félix Bardy**, L3 Info \
mail: _felix.bardy@etu.univ-lyon1.fr_

* **Mattéo Deransart**, L3 Info \
mail: _matteo.deransart@etu.univ-lyon1.fr_

Sous la supervision de Alexandre Meyer dans le cadre de l'UE LifProjet d'automne 2021.
