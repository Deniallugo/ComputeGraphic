//
//  App.h
//  sdf
//
//  Created by Данил on 09/03/2015.
//  Copyright (c) 2015 Данил. All rights reserved.
//

#ifndef __sdf__App__
#define __sdf__App__
#include <GL/glxew.h>
#include <GL/glew.h>

#include <stdio.h>
#include <SDL2/SDL.h> // Библиотека SDL 2

#include "ShaderManger.h"
#include "BufferManager.h"
#include <iostream>
#include "math_3d.h"

#endif /* defined(__sdf__App__) */

//singleton
class App{

    App(){shaderManager = *new ShaderManager();}
    App(const App& root);
    App& operator=(const App& root);
    ShaderManager shaderManager;
    BuffeManager bufferManager;
    const Uint8 *keystates;
public:
    SDL_Window *window; // задаем окно для SDL
    void createTriangle();
    bool init(int width,int height);//Also create App
    void onExecute();
    bool event();
    static  App& instance()
    {
        static App theSingleInstance;
        return theSingleInstance;
    }
    void Render();
    void Run();
    void workingWithShaders();
    void ShutDown();
};