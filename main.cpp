
#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <deque>
#include <string>
#include "Shader.h"
#include <imgui_stdlib.h>

float colorfondo[4]={0.6,0.6,0.6,1};
std::deque<std::string> mensajesporventana;

//Funcion para agregar los mensajes a la estructura
void aniadirmensajesporventana(const std::string& mensaje){
    mensajesporventana.push_back(mensaje);
}


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if (action == GLFW_PRESS){
        //Si es necesario hacer algo con este evento, indicarlo aqui
        //Finalmente, comunica el evente de ratón a ImGui
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button,true);
    }else if(action == GLFW_RELEASE){
        //Si es necesario hacer algo con este evento, indicarlo aqui
        //Finalmente, comunica el evento de ratón a ImGui
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button,false);
    }
}


void callbackRefrescoVentana(GLFWwindow* ventana){
    Shader::getInstancia().refrescar();
    glfwSwapBuffers(ventana);
    //std::cout << "Finaliza el callback de refresco" << std::endl;
    aniadirmensajesporventana("Finaliza el callback de refresco");
}

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback ( int errno, const char* desc )
{  std::string aux (desc);
    //std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
    aniadirmensajesporventana("Error de GLFW número " + std::to_string(errno)+ ": " + std::string(aux));
}
/*
// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback ( GLFWwindow *window )
{  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
    // intercambia el buffer back (que se ha estado dibujando) por el
    // que se mostraba hasta ahora front. Debe ser la última orden de
    // este callback
    //std::cout << "Refresh callback called" << std::endl;
}*/

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback ( GLFWwindow *window, int width, int height )
{  //glViewport ( 0, 0, width, height );
    PAG::Renderer::getInstancia().llamadaviewport(width,height);
    //std::cout << "Resize callback called" << std::endl;
    aniadirmensajesporventana("Resize callback called");
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods )
{  if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {  glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    //std::cout << "Key callback called" << std::endl;
    aniadirmensajesporventana("Key callback called");
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods )
{  if ( action == GLFW_PRESS )
    {  //std::cout << "Pulsado el botón: " << button << std::endl;
        aniadirmensajesporventana("Pulsado el botón: " + std::to_string(button));
    }
    else if ( action == GLFW_RELEASE )
    {  //std::cout << "Soltado el botón: " << button << std::endl;
        aniadirmensajesporventana("Soltado el botón: " + std::to_string(button));
    }
}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset )
{  //std::cout << "Movida la rueda del ratón " << xoffset
             //<< " Unidades en horizontal y " << yoffset
             //<< " unidades en vertical" << std::endl;

    //aniadirmensajesporventana("Movida la rueda del ratón " + std::to_string(xoffset)
      //                          + "Unidades en horizontal y " + std::to_string(yoffset) + "unidades en vertical"
         //                       );

    float delta=(float)yoffset*0.02;
    for (int i = 0; i < 3; ++i) {
        colorfondo[i]+=delta;
        if(colorfondo[i]<=0){
            colorfondo[i]=0;
        }
        if(colorfondo[i]>=1){
            colorfondo[i]=1;
        }

    }
    //agragado para cambiar el color cuando se use la rueda del raton
    PAG::Renderer::getInstancia().colorfondo(colorfondo[0],colorfondo[1],colorfondo[2]);
}

int main()
{  //std::cout << "Starting Application PAG - Prueba 01" << std::endl;
    aniadirmensajesporventana("Starting Application PAG - Prueba 01");
    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) error_callback );

    // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE )
    //como es un error lo dejo para que se ponga en la consola
    {  std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 ); // OpenGL Core Profile 4.1.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;
    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow ( 1024, 576, "PAG Introduction", nullptr, nullptr );

    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr )
        //como es un error lo dejo para que se ponga en la consola
    {  std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent ( window );

    // - Ahora inicializamos GLAD.
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) )
    {
        //como es un error lo dejo para que se ponga en la consola
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, callbackRefrescoVentana );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );


/*

    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
    // 3D construido.
    std::cout << glGetString ( GL_RENDERER ) << std::endl
              << glGetString ( GL_VENDOR ) << std::endl
              << glGetString ( GL_VERSION ) << std::endl
              << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
*/


    // - Establecemos un gris medio como color con el que se borrará el frame buffer.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    //glClearColor ( colorfondo[0] , colorfondo[1] , colorfondo[2] , colorfondo[3] );

    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    //glEnable ( GL_DEPTH_TEST );



    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io= ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //Aquí w es el puntero a la ventana GLFW (GLFWWindow*)
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init();

    //no se donde hay que ponerlo
    PAG::Renderer::getInstancia().inicializaOpenGL();
    aniadirmensajesporventana(PAG::Renderer::getInstancia().informeopenGL());


// se supone que va aqui
/*try{
    Shader::getInstancia().creaShaderProgram();
}catch (const std::exception& e){
    aniadirmensajesporventana(e.what());
}
*//*
    Shader::getInstancia().creaModelo();
*/



    // - Ciclo de eventos de la aplicación. La condición de parada es que la
    // ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
    // botón de cerrar la ventana (la X).
    while ( !glfwWindowShouldClose ( window ) )
    {





        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //Se dibujan los controles de Dear ImGui
        ImGui::SetNextWindowPos ( ImVec2 (10, 10), ImGuiCond_Once );

        if(ImGui::Begin("Mensajes"))
        {
            //La ventana está despegada
            ImGui::SetWindowFontScale(1.0f); //Escalamos el texto si fuera necesario

            for (const auto& mensaje : mensajesporventana) {
                ImGui::TextUnformatted(mensaje.c_str());
            }

            if (ImGui::GetScrollY()>= ImGui::GetScrollMaxY()){
                ImGui::SetScrollHereY(1);
            }

            //Pintamos los controles



            //si la ventana no esta desplegada devuelve false
            ImGui::End();
        }
        //Aqui ve el dibujado de la escena con instrucciones OpenGL


        ImGui::SetNextWindowPos ( ImVec2 (700, 10), ImGuiCond_Once );

        if(ImGui::Begin("Fondo"))
        {
            //La ventana está despegada
            ImGui::SetWindowFontScale(1.0f); //Escalamos el texto si fuera necesario
            //Pintamos los controles
            if(ImGui::ColorPicker4("color de fondo", (float*)colorfondo,ImGuiColorEditFlags_PickerHueWheel)){
                PAG::Renderer::getInstancia().colorfondo(colorfondo[0],colorfondo[1],colorfondo[2]);
            }


            //si la ventana no esta desplegada devuelve false
            ImGui::End();
        }


        static std::string _name="";
        ImGui::SetNextWindowPos ( ImVec2 (500, 100), ImGuiCond_Once );
        if(ImGui::Begin("Shader Program"))
        {
            //La ventana está despegada
            ImGui::SetWindowFontScale(1.0f); //Escalamos el texto si fuera necesario
            //Pintamos los controles
            ImGui::InputText("##",&_name,ImGuiInputTextFlags_AutoSelectAll);


            bool _buttonPressed = ImGui::Button("Load");

            if (_buttonPressed && !_name.empty()){
                try{

                    Shader::getInstancia().creaShaderProgram(_name);
                    Shader::getInstancia().creaModelo();
                }catch (const std::exception& e){
                    aniadirmensajesporventana(e.what());
                }
            }

            //si la ventana no esta desplegada devuelve false
            ImGui::End();
        }



        Shader::getInstancia().refrescar();

        ImGui::Render();
        //PAG::Renderer::getInstancia().colorfondo(colorfondo[0],colorfondo[1],colorfondo[2]);
        //PAG::Renderer::getInstancia().refrescar();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());











        // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
        // intercambia el buffer back (en el que se ha estado dibujando) por el
        // que se mostraba hasta ahora (front).
        glfwSwapBuffers ( window );
        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents ();
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    aniadirmensajesporventana("Finishing application pag prueba");
    //std::cout << "Finishing application pag prueba" << std::endl;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    //glfwDestroyWindow(window);

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.

}