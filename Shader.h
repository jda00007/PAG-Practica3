//
// Created by programas on 08/10/2025.
//

#ifndef PAG2_SHADER_H
#define PAG2_SHADER_H
#include <string>
#include "glad/glad.h"

class Shader {
    static Shader* instancia;
    Shader();
    GLuint idVS = 0; // Identificador del vertex shader
    GLuint idFS = 0; // Identificador del fragment shader
    GLuint idSP = 0; // Identificador del shader program
    GLuint idVAO = 0; // Identificador del vertex array object
    GLuint idVBO = 0; // Identificador del vertex buffer object
    GLuint idIBO = 0; // Identificador del index buffer object

public:
    virtual ~Shader();
    static Shader& getInstancia();

    void creaShaderProgram(const std::string& nombre);
    void creaModelo();

    void refrescar();
};


#endif //PAG2_SHADER_H
