//
// Created by programas on 23/09/2025.
//

#ifndef PAG2_RENDERER_H
#define PAG2_RENDERER_H

#include <string>
#include "glad/glad.h"
#include "Shader.h"
#include "camara.h"

namespace PAG {
    //enum class WindowType {Background};

    class Renderer {
    private:
        static Renderer* instancia ; ///< Puntero al unico objeto
        Renderer();

        float rojo=0.6;
        float verde=0.6;
        float azul=0.6;
        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader
        GLuint idSP = 0; // Identificador del shader program
        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object
        Shader shader;
        PAG::camara camara;
        PAG::Movimiento_Camara movimientoCamara = PAG::Movimiento_Camara::orbit;
    public:
        virtual ~Renderer();
        static Renderer& getInstancia ();

        void refrescar ();
        //void wakeUp(WindowType t, ...);
        void colorfondo(float rojo1,float verde,float azul);

        void creaShaderProgram(const std::string& nombre);

        void creaModelo();

        void inicializaOpenGL();

        std::string informeopenGL();

        void llamadaviewport(int width, int height);

        void cargaShaders();

        void setMovimientoCamara(PAG::Movimiento_Camara movimiento);
        void movimientoraton(float deltaX, float deltaY);
        glm::mat4 getViewMatrix() const;

        void reseteo_camara(){ camara.reset();}

    };

} // PAG

#endif //PAG2_RENDERER_H
