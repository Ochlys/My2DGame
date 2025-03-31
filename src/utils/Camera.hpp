#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <SFML/Graphics.hpp>

namespace GAME {

    class Camera {
    public:
        
        Camera(float mapWidth, float mapHeight, float windowWidth, float windowHeight)
        : mapWidth(mapWidth), mapHeight(mapHeight), windowWidth(windowWidth), windowHeight(windowHeight) {

            //Ajoute la vue avec le taille de la fenêtre
            view.setSize(windowWidth, windowHeight);
        }

        void update(sf::Vector2f playerPosition) {


            // Limites de la caméra
            float halfWidth = windowWidth / 2.f;
            float halfHeight = windowHeight / 2.f;

            // Centre de la caméra
            float cameraX = playerPosition.x - (windowWidth / 2.f);
            float cameraY = playerPosition.y - (windowHeight / 2.f);

            // Empeche la cam de sortir
            if (cameraX + halfWidth > mapWidth) cameraX = mapWidth - halfWidth;
            if (cameraY + halfHeight > mapHeight) cameraY = mapHeight - halfHeight;

            // Mettre à jour le cantrage de la caméra        
            view.setCenter(cameraX + halfWidth, cameraY + halfHeight);
        }

        sf::View getView() const{
            return view;
        } // Récuperer la vue pour la caméra et retounrer la MAJ de du centrage

    private:

        float windowWidth, windowHeight; // Taille de la fenêtre
        float mapWidth, mapHeight; // Taille de la map
        sf::View view; // Vue de la caméra

    };

}

#endif // __CAMERA_HPP__
