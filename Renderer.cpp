//
// Created by programas on 23/09/2025.
//


#include <cstdarg>
#include "Renderer.h"
#include "imgui_impl_opengl3_loader.h"

#include <string>
#include <sstream>
#include <fstream>

namespace PAG {
    Renderer* Renderer::instancia=nullptr;
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {

        if ( idVS!=0){
            glDeleteShader (idVS);
        }

        if (idFS!=0){
            glDeleteShader (idFS);
        }

        if (idSP!=0){
            glDeleteProgram (idSP);
        }

        if (idVBO!=0){
            glDeleteBuffers (1,&idVBO);
        }

        if (idIBO!=0){
            glDeleteBuffers (1,&idIBO);
        }

        if (idVAO!=0){
            glDeleteVertexArrays (1,&idVAO);
        }
    }

    void PAG::Renderer::inicializaOpenGL() {
        glClearColor(rojo,verde, azul, 1.0 );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_MULTISAMPLE );
    }

    Renderer& Renderer::getInstancia() {
        if(!instancia){
            instancia=new Renderer;
        }
        return *instancia;
    }
//modificado para que incluir el shader
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glUseProgram ( idSP );
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements( GL_TRIANGLES, 3 , GL_UNSIGNED_INT, nullptr );

    }

  /*  void Renderer::wakeUp(WindowType t, ... ){
        switch (t) {
            case WindowType::Background:
            {
                std::va_list args;
                va_start(args,t);
                _bgColor = *(va_arg(args,glm::vec3*));
                _showAxis=*(va_arg(args,bool*));
                va_end(args);
                break;
            }
            //procesar el resto de tipos de ventana

        }
        //termianr cualquier otro tipo de procesamiento que sea necesario
    }*/


  void Renderer::colorfondo(float rojo1,float verde1,float azul1){
      rojo=rojo1;
      verde=verde1;
      azul=azul1;

      glClearColor(rojo,verde,azul,1);
  }

  /*
   * Método para crear, compilar y enlazar el shader program
   * @note No se incluye ninguna comprobación de errores
   */
  void PAG::Renderer::creaShaderProgram() {
      /*std::string miVertexShader =
              "#version 410\n"
              "layout (location = 0) in vec posicion;\n"
              "void main ()\n"
              "{ gl_Position = vec4 ( posicion, 1 );\n"
              "}\n";
*/
      /*
      std::string  miFragmentShader =
              "#version 410\n"
              "out vec4 colorFragmento;\n"
              "void main ()\n"
              "{ colorFragmento = vec4 (1.0,0.4,0.2,1.0);\n"
              "}\n";
*/

      std::string rutaVertex= "../Shaders/pag03-vs.glsl";
      std::string rutaFragment= "../Shaders/pag03-fs.glsl";

      std::ifstream archivoShader;
      archivoShader.open (rutaVertex);

      if (!archivoShader.is_open()){
          //error abriendo el archivo
          throw std::runtime_error("Error: No se pudo abrir el archivo del VertexShader");
      }

      std::stringstream streamShader;
      streamShader << archivoShader.rdbuf ();
      std::string codigoFuenteShader = streamShader.str();

      archivoShader.close();

      std::ifstream archivoShaderFrag;
      archivoShaderFrag.open (rutaFragment);

      if (!archivoShaderFrag.is_open()){
          //error abriendo el archivo
          throw std::runtime_error("Error: No se pudo abrir el archivo del FragmentShader");
      }

      std::stringstream streamShaderFrag;
      streamShaderFrag << archivoShaderFrag.rdbuf ();
      std::string codigoFuenteShaderFag = streamShaderFrag.str();

      archivoShaderFrag.close();

      GLuint idShader=0;
      const GLchar* codigofuenteFormatoC = codigoFuenteShader.c_str();
      glShaderSource(idShader,1,&codigofuenteFormatoC,NULL);
      glCompileShader(idShader);

      GLint resultadoCompilacion;
      glGetShaderiv ( idShader, GL_COMPILE_STATUS, &resultadoCompilacion );

      if ( resultadoCompilacion == GL_FALSE )
      {  // Ha habido un error en la compilación.
          // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
          GLint tamMsj = 0;
          std::string mensaje = "";
          glGetShaderiv ( idShader, GL_INFO_LOG_LENGTH, &tamMsj );
          if ( tamMsj > 0 )
          {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
              GLint datosEscritos = 0;
              glGetShaderInfoLog ( idShader, tamMsj, &datosEscritos, mensajeFormatoC );
              mensaje.assign ( mensajeFormatoC );
              delete[] mensajeFormatoC;
              mensajeFormatoC = nullptr;
              // En "mensaje" tenemos la información del error. Comunicarla de alguna
              // forma
          }
      }

      GLuint idShaderFR=0;
      const GLchar* codigofuenteFormatoCF = codigoFuenteShaderFag.c_str();
      glShaderSource(idShaderFR,1,&codigofuenteFormatoCF,NULL);
      glCompileShader(idShaderFR);

      GLint resultadoCompilacion2;
      glGetShaderiv ( idShaderFR, GL_COMPILE_STATUS, &resultadoCompilacion2 );

      if ( resultadoCompilacion2 == GL_FALSE )
      {  // Ha habido un error en la compilación.
          // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
          GLint tamMsj = 0;
          std::string mensaje = "";
          glGetShaderiv ( idShader, GL_INFO_LOG_LENGTH, &tamMsj );
          if ( tamMsj > 0 )
          {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
              GLint datosEscritos = 0;
              glGetShaderInfoLog ( idShaderFR, tamMsj, &datosEscritos, mensajeFormatoC );
              mensaje.assign ( mensajeFormatoC );
              delete[] mensajeFormatoC;
              mensajeFormatoC = nullptr;
              // En "mensaje" tenemos la información del error. Comunicarla de alguna
              // forma
          }
      }

      GLuint idPrograma = glCreateProgram();
      GLuint idVertexShader=0;
      GLuint idFragmentShader=0;

      glAttachShader ( idPrograma, idVertexShader );
      glAttachShader ( idPrograma, idFragmentShader );

      glLinkProgram ( idPrograma );
      GLint resultadoEnlazado = 0;
      glGetProgramiv ( idPrograma, GL_LINK_STATUS, &resultadoEnlazado );
      if ( resultadoEnlazado == GL_FALSE )
      {  // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
          GLint tamMsj = 0;
          std::string mensaje = "";
          glGetProgramiv ( idPrograma, GL_INFO_LOG_LENGTH, &tamMsj );
          if ( tamMsj > 0 )
          {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
              GLint datosEscritos = 0;
              glGetProgramInfoLog ( idPrograma, tamMsj, &datosEscritos, mensajeFormatoC );
              mensaje.assign ( mensajeFormatoC );
              delete[] mensajeFormatoC;
              mensajeFormatoC = nullptr;
              // En "mensaje" tenemos la información del error. Comunicarla de alguna forma
          }
      }

      /*
      idVS = glCreateShader ( GL_VERTEX_SHADER );
      const GLchar* fuenteVS = miVertexShader.c_str();
      glShaderSource (idVS,1,&fuenteVS, nullptr);
      glCompileShader( idFS);

      idSP = glCreateProgram ();
      glAttachShader (idSP, idVS);
      glAttachShader (idSP, idFS);
      glLinkProgram ( idSP);
*/
  }

  void PAG::Renderer::creaModelo() {
      GLfloat vertices[] = { -0.5,-0.5, 0,
                             0.5,-0.5,0,
                             0.0,0.5,0};
      GLuint indices[]={0,1,2};
      glGenVertexArrays (1, &idVAO);
      glBindVertexArray (idVAO);
      glGenBuffers (1, &idVBO);
      glBindBuffer (GL_ARRAY_BUFFER, idVBO);
      glBufferData (GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer (0,3,GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr);
      glEnableVertexAttribArray (0);
      glGenBuffers (1,&idIBO);
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER,idIBO);
      glBufferData ( GL_ELEMENT_ARRAY_BUFFER,3*sizeof(GLuint),indices, GL_STATIC_DRAW);
  }

  std::string PAG::Renderer::informeopenGL() {

     std::string aux;
      std::ostringstream oss;
      oss << glGetString(GL_RENDERER) << '\n'
          << glGetString(GL_VENDOR) << '\n'
          << glGetString(GL_VERSION) << '\n'
          << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
      aux = oss.str();
      return aux;
  }
void PAG::Renderer::llamadaviewport(int width, int height) {
    glViewport ( 0, 0, width, height );
  }


} // PAG