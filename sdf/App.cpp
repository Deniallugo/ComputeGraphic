//
//  App.cpp
//  sdf
//
//  Created by Данил on 09/03/2015.
//  Copyright (c) 2015 Данил. All rights reserved.
//

#include "App.h"
using namespace::std;

//void drawCube(float xrf, float yrf, float zrf);

bool App::init(int width,int height){

    // Инициализация SDL

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
        exit(1);
    }

    // Включаем двойной буфер, настраиваем цвета

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    // Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

    window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

    if(window == NULL){ // если не получилось создать окно, то выходим
        exit(1);
    }

    // Инициализация OpenGL
    glewExperimental = GL_TRUE;

    glewInit ();

    if ( !GLEW_VERSION_3_3 )
    {
        printf ( "OpenGL 3.3 not supported.\n" );

        return 1;
    }
//    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
    glClearDepth(1.0);
    glFrontFace(GL_CW);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // включаем тест глубины
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
    glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
    workingWithShaders();
    return true;
}



bool App::event(){

    SDL_Event event; // события SDL
    if( keystates[ SDL_SCANCODE_UP ] )
    {
        printf("up");

       // apply_surface( ( SCREEN_WIDTH - up->w ) / 2, ( SCREEN_HEIGHT / 2 - up->h ) / 2, up, screen );
    }

    //Если нажата стрелка вниз
    if( keystates[ SDL_SCANCODE_DOWN ] )
    {
     //   apply_surface( ( SCREEN_WIDTH - down->w ) / 2, ( SCREEN_HEIGHT / 2 - down->h ) / 2 + ( SCREEN_HEIGHT / 2 ), down, screen );
        printf("down");

    }

    //Если нажата стрелка влево
    if( keystates[ SDL_SCANCODE_LEFT ] )
    {
       // apply_surface( ( SCREEN_WIDTH / 2 - left->w ) / 2, ( SCREEN_HEIGHT - left->h ) / 2, left, screen );
        printf("left");

    }

    //Если нажата стрелка вправо
    if( keystates[ SDL_SCANCODE_RIGHT ] )
    {
        //apply_surface( ( SCREEN_WIDTH / 2 - right->w ) / 2 + ( SCREEN_WIDTH / 2 ), ( SCREEN_HEIGHT - right->h ) / 2, right, screen );
        printf("right");
    }

    if (keystates[SDL_SCANCODE_ESCAPE])
        return false;

    return true;

}



void App::Run(){

    bool running = true;
    keystates = SDL_GetKeyboardState(NULL);

    while(running){


        running = event();
        //        update() //логика работы игры
        //      render()//отрисовка учитывает интрерполяцию по времени

        //        drawCube(xrf, yrf, zrf); // рисуем сам куб с текущими углами поворота
        Render();


        // обновляем экран

        glFlush();
        SDL_GL_SwapWindow(window);
    }

}




void App::workingWithShaders(){


    shaderManager.createShaderProgram("Simple");

    shaderManager.attachShader("SimpleVertex",VERTEX);
    shaderManager.attachShader("SimpleFragment",FRAGMENT);
    shaderManager.loadShaderSource("SimpleVertex","shaders/Vertex.vs");
    shaderManager.loadShaderSource("SimpleFragment","shaders/Fragment.fs");

    shaderManager.compileShader("SimpleVertex");
    shaderManager.compileShader("SimpleFragment");
    shaderManager.attachShaderToProgram("Simple","SimpleVertex");
    shaderManager.attachShaderToProgram("Simple","SimpleFragment");


    shaderManager.bindAttributes("Simple",0,"inPosition");
    shaderManager.bindAttributes("Simple",1,"inColour");

    shaderManager.linkProgramObject("Simple");
    shaderManager["Simple"]->use();
    createTriangle();

}


void App::Render(){


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderManager["Simple"]->use();

    bufferManager["first"]->drawArrays();

    bufferManager["second"]->drawArrays();

}


void App::ShutDown(){
    SDL_Quit();
}
void App::createTriangle()
{
    // First simple object
    float* vert = new float[9]; // vertex array
    float* col  = new float[9]; // color array

    vert[0] =-0.0; vert[1] = 0.5; vert[2] =-1.0;
    vert[3] =-1; vert[4] =-0.5; vert[5] =-1.0;
    vert[6] = 0.2; vert[7] =-0.5; vert[8]= -1.0;

    col[0] = 1.0; col[1] = 0.0; col[2] = 0.0;
    col[3] = 0.0; col[4] = 1.0; col[5] = 0.0;
    col[6] = 0.0; col[7] = 0.0; col[8] = 1.0;

    // Second simple object
    float* vert2 = new float[9]; // vertex array
    float* col2  = new float[9]; // color array

    vert2[0] =-0.2; vert2[1] = 0.5; vert2[2] =-1.0;
    vert2[3] = 0.3; vert2[4] =-0.5; vert2[5] =-1.0;
    vert2[6] = 0.8; vert2[7] = 0.5; vert2[8]= -1.0;
    col2[0] = 0.5; col2[1] = 0.0; col2[2] = 0.0;
    col2[3] = 0.2; col2[4] = 0.0; col2[5] = 0.9;
    col2[6] = 0.0; col2[7] = 0.0; col2[8] = 0.8;

    
    bufferManager.addBuffer("first")->addBuffer("vert", vert, 9);
    bufferManager["first"]->addBuffer("color", col, 9);
    bufferManager["first"]->CreateVao();

    bufferManager["first"]->operator[]("vert")->CreateVertexBuffer(shaderManager["Simple"], "inPosition");
    bufferManager["first"]->operator[]("color")->CreateVertexBuffer(shaderManager["Simple"], "inColour");



    bufferManager.addBuffer("second")->addBuffer("vert", vert2, 9);
    bufferManager["second"]->addBuffer("color", col2, 9);
    bufferManager["second"]->CreateVao();

    bufferManager["second"]->operator[]("vert")->CreateVertexBuffer(shaderManager["Simple"], "inPosition");
    bufferManager["second"]->operator[]("color")->CreateVertexBuffer(shaderManager["Simple"], "inColour");



    glEnableVertexAttribArray(0);
    glBindVertexArrayAPPLE(0);

    delete [] vert;
    delete [] vert2;
    delete [] col;
}