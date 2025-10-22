//
// Created by programas on 21/10/2025.
//

#ifndef PAG2_CAMARA_H
#define PAG2_CAMARA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PAG {
    enum class Movimiento_Camara {
        orbit=0,
        pan=1,
        dolly=2

    };


    class camara {
    private:
        glm::vec3 posicion;
        glm::vec3 punto_de_referencia;
        glm::vec3 vector_up;
        float radio;
        float yaw;
        float pitch;

    public:
        camara(glm::vec3 posicion = glm::vec3(0.0f, 0.0f, 3.0f),
               glm::vec3 punto_de_referencia = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 vector_up = glm::vec3(0.0f, 1.0f, 0.0f));

        void orbit(float deltaX, float deltaY);

        void pan(float deltaX, float deltaY);

        void dolly(float delta);

        void reset();

        glm::mat4 getViewMatrix() const;

        glm::vec3 getPosition() const {
            return posicion;
        }
    };

}//PAG

#endif //PAG2_CAMARA_H
