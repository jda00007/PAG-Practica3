//
// Created by programas on 21/10/2025.
//

#include "camara.h"
#include <cmath>

namespace PAG {
    camara::camara(glm::vec3 posicion_aux, glm::vec3 punto_de_referencia_aux, glm::vec3 vector_up_aux)
            : posicion(posicion_aux), punto_de_referencia(punto_de_referencia_aux), vector_up(vector_up_aux) {
        glm::vec3 direccion = glm::normalize(punto_de_referencia - posicion);
        radio = glm::length(punto_de_referencia - posicion);
        yaw = atan2(direccion.x, direccion.z);
        pitch = asin(direccion.y);
    }


    void camara::orbit(float deltaX, float deltaY) {
        yaw += deltaX;
        pitch -= deltaY;
        pitch = glm::clamp(pitch,-1.5f,-1.5f);

        float x = radio * sin(yaw) * cos(pitch);
        float y = radio * sin(pitch);
        float z = radio * cos(yaw) * cos(pitch);

        posicion = punto_de_referencia - glm::vec3(x,y,z);
    }

    void camara::pan(float deltaX,float deltaY){
        glm::vec3 n = glm::normalize(punto_de_referencia - posicion);
        glm::vec3 u = glm::normalize(glm::cross(n,vector_up));
        glm::vec3 v = glm::normalize(glm::cross(u,n));

        posicion -= u * deltaX;
        punto_de_referencia -= u * deltaX;
        posicion += v* deltaY;
        punto_de_referencia += u * deltaY;
    }


    void camara::dolly(float delta) {
        radio -= delta;
        radio = glm::max(0.1f, radio);

        glm::vec3 direccion = glm::normalize(punto_de_referencia - posicion);
        posicion = punto_de_referencia - direccion * radio;
    }

    void camara::reset() {
        posicion = glm::vec3(0.0f, 0.0f, 3.0f);
        punto_de_referencia = glm::vec3(0.0f, 0.0f, 0.0f);
        vector_up = glm::vec3(0.0f,1.0f,0.0f);
        radio= 3.0f;
        yaw= 0.0f;
        pitch= 0.0f;
    }
    glm::mat4 camara::getViewMatrix() const {
        return glm::lookAt(posicion, punto_de_referencia,vector_up);
    }

}