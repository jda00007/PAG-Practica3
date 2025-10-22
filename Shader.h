//
// Created by programas on 08/10/2025.
//

#ifndef PAG2_SHADER_H
#define PAG2_SHADER_H
#include <string>
#include "glad/glad.h"

class Shader {



public:
    virtual ~Shader();


    static void creaShaderProgram(const std::string& nombre, GLuint& idVS, GLuint& idFS, GLuint& idSP);
    //void creaModelo();

    //void refrescar();


};


#endif //PAG2_SHADER_H
