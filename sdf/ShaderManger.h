//
//  ShaderManger.h
//  sdf
//
//  Created by Данил on 09/03/2015.
//  Copyright (c) 2015 Данил. All rights reserved.
//

#ifndef __sdf__ShaderManger__
#define __sdf__ShaderManger__

#include "glInclude.h"
#include <string>
#endif /* defined(__sdf__ShaderManger__) */
using namespace std;
#pragma once

enum SHADERTYPE{

    VERTEX,
    FRAGMENT,
    GEOMETRY,
    

};

class Shader{
    string name;
    string source;
    bool compiled;
    SHADERTYPE type;
    GLuint shaderHandle;
    int refCount;

public:
    Shader(string name, SHADERTYPE type);
    void loadShader(string name);
    void compile();
    GLuint getShaderHandle(){return shaderHandle;}
    void incRefCount(){refCount++;}
    void decRefCount(){refCount--;}
    int getRefCount(){return refCount;}
};

class ShaderProgram{
    bool linked;
    vector<Shader*> Shaders;
    GLuint programID;
    string programName;
    map<string,GLuint> attribs;
    bool active;
public:
    ShaderProgram( string _name);
    void use(){
        glUseProgram(programID);
        active = true;
    }
    void unBind(){
        active = false;
        glUseProgram(0);

    }

    void attachShader(Shader *shader);
    void bindAttributes(GLuint _index, string _attribName);
    void link();
    GLuint getId(){return programID ;}
    void enableAttribArray(string name){
        glEnableVertexAttribArrayARB(attribs[name]);

    }
    void disableAttribArray(string name){
        glDisableVertexAttribArrayARB(attribs[name]);
    }
    bool vertexAttribPointer(string name, GLint size, GLenum type, GLsizei stride, const GLvoid* data,bool normalize);
    void vertexAttrib1f(string name, GLfloat v_0);
    void vertexAttrib3f(string name, GLfloat v_0,GLfloat v_1,GLfloat v_2);

    GLuint getUniformLocation( const char* _name) const;
    void setUniform1f(const char* _varname,float _v0) const;
    

};

class ShaderManager{

    map<string,ShaderProgram*> shaderPrograms;
    map<string,Shader*> shaders;
    ShaderProgram* nullProgram;
    bool isUsingGBuffer;

public:
    ShaderManager(){ //nullProgram = new ShaderProgram(NULL);
    }
    ShaderProgram* createShaderProgram(string _name){
        std::cerr<<"creating empty ShaderProgram "<<_name.c_str()<<"\n";
        shaderPrograms[_name]= new ShaderProgram(_name);
        return shaderPrograms[_name];
    }
    void attachShader(string _name,SHADERTYPE _type) {shaders[_name]= new Shader(_name,_type);}
    void loadShaderSource(string _shaderName, string _sourceFile);
    void compileShader(string _name);
    void attachShaderToProgram(string _program,string _shader);
    ShaderProgram * operator[](const string &_programName);
    void bindAttributes(std::string _program, GLuint _index, std::string _attribName);
    void linkProgramObject(std::string _name);


};


