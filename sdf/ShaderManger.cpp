//
//  ShaderManger.cpp
//  sdf
//
//  Created by Данил on 09/03/2015.
//  Copyright (c) 2015 Данил. All rights reserved.
//

#include "ShaderManger.h"








Shader::Shader(string _name, SHADERTYPE _type){

    name = _name;
    type = _type;
    compiled = false;
    switch (type) {
        case VERTEX:
            shaderHandle = glCreateShader(GL_VERTEX_SHADER_ARB);
            break;

        case FRAGMENT:
            shaderHandle = glCreateShader(GL_FRAGMENT_SHADER_ARB);
            break;
        case GEOMETRY:
            shaderHandle = glCreateShader(GL_GEOMETRY_SHADER_EXT);
    }
    refCount = 0;
    source = "";

}

void Shader::loadShader(string name){

    name = "/Users/danil/Documents/Programming & HardCoding/sdf/sdf/" + name;
    ifstream sSource(name.c_str());
    source = *new string(istreambuf_iterator<char>(sSource), istreambuf_iterator<char>());
    sSource.close();
    source +="\0";
    const char* data=source.c_str();
    glShaderSource(shaderHandle , 1, &data,NULL);
    compiled=false;
    

}

void Shader::compile(){
    if (source.c_str() == 0)
    {
        std::cerr<<"Warning no shader source loaded\n";
        return;
    }
    glCompileShader(shaderHandle);
    compiled=true;
}


ShaderProgram::ShaderProgram(string name){
    programID = glCreateProgram();
    linked = false;
    active = false;
    programName = name;

}


void ShaderProgram::attachShader(Shader *shader){

    Shaders.push_back(shader);
    glAttachShader(programID, shader->getShaderHandle());

}

void ShaderProgram::link(){

    glLinkProgram(programID);
    GLint infologLength = 0;

    glGetProgramiv(programID, GL_INFO_LOG_LENGTH,&infologLength);
    std::cerr<<"Link Log Length "<<infologLength<<"\n";
    GLchar *infoLog = new GLchar[infologLength];
    if (infologLength > 0) {

        glGetProgramInfoLog(programID, GL_INFO_LOG_LENGTH, &infologLength, infoLog);

        cerr <<infoLog;
    }
    linked=true;

}


void ShaderProgram::bindAttributes(GLuint index,string name){
    if(linked == true)
    {
        cerr<<"Warning binding attribute after link\n";
    }
    attribs[name]=index;
    glBindAttribLocation(programID,index,name.c_str());
    std::cerr<<"bindAttribLoc "<<programID<<" index "<<index<<" name "<<name<<"\n";

}

void ShaderManager::bindAttributes(std::string _programName, GLuint _index, std::string _attribName) {
    std::map<std::string, ShaderProgram *>::const_iterator program = shaderPrograms.find(_programName);
    if (program != shaderPrograms.end()) {
        program->second->bindAttributes(_index, _attribName);
    } else {
        std::cerr << "Warning Program not know in bindAttrib " << _programName.c_str();
    }
}

//void ShaderProgram::enableAttribArray(string name){
//
//
//}


bool ShaderProgram::vertexAttribPointer(string name, GLint size, GLenum type, GLsizei stride, const GLvoid *data, bool normalise){


    map <std::string, GLuint >::const_iterator attrib=attribs.find(name);
    // make sure we have a valid  program

    if(attrib!=attribs.end() )
    {
        glVertexAttribPointer(attrib->second,size,type,normalise,stride,data);
        return  true;
    }

    return false;

}



void ShaderProgram::vertexAttrib1f(string name, GLfloat v_0){

    std::map <std::string, GLuint >::const_iterator attrib=attribs.find(name);
    // make sure we have a valid  program
    if(attrib!=attribs.end() )
    {
        glVertexAttrib1f(attrib->second, v_0);
        
    }

}
void ShaderProgram::vertexAttrib3f(string name, GLfloat v_0,GLfloat v_1,GLfloat v_2){

    std::map <std::string, GLuint >::const_iterator attrib=attribs.find(name);
    // make sure we have a valid  program
    if(attrib!=attribs.end() )
    {
        glVertexAttrib3f(attrib->second, v_0,v_1,v_2);

    }

    
}

GLuint ShaderProgram::getUniformLocation(const char *name)const{

    GLuint loc = glGetUniformLocation(programID, name);
    if (loc == -1 ){
        std::cerr<<"Uniform \""<<name<<"\" not found in Program \""<<programName<<"\"\n";

    }
    return  loc;
}

void ShaderProgram::setUniform1f(const char *_varname, float _v0)const{

    glUniform1f(getUniformLocation(_varname),_v0);

}



void ShaderManager::linkProgramObject(std::string _name) {

    std::map<std::string, ShaderProgram *>::const_iterator program = shaderPrograms.find(_name);
    if (program != shaderPrograms.end()) {

        std::cerr << "Linking " << _name.c_str() << "\n";
        program->second->link();

    } else {
        std::cerr << "Warning Program not known in link " << _name.c_str();
    }
}



void ShaderManager::loadShaderSource(std::string _shaderName, std::string _sourceFile)
{
    std::map <std::string, Shader * >::const_iterator shader=shaders.find(_shaderName);
    // make sure we have a valid shader and program
    if(shader!=shaders.end() )
    {
        shader->second->loadShader(_sourceFile);
    }
    else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.c_str();}
}


void ShaderManager::compileShader(std::string _name)
{
    // get an iterator to the shaders
    std::map <std::string, Shader * >::const_iterator shader=shaders.find(_name);
    // make sure we have a valid shader
    if(shader!=shaders.end())
    {
        // grab the pointer to the shader and call compile
        shader->second->compile();
    }
    else {std::cerr<<"Warning shader not know in compile "<<_name.c_str();}//добавить то что произошло
}

void ShaderManager::attachShaderToProgram(std::string _program,std::string _shader)

{

    // get an iterator to the shader and program
    std::map <std::string, Shader * >::const_iterator shader=shaders.find(_shader);
    std::map <std::string, ShaderProgram * >::const_iterator program=shaderPrograms.find(_program);

    // make sure we have a valid shader and program
    if(shader!=shaders.end() && program !=shaderPrograms.end())
    {
        // now attach the shader to the program

        program->second->attachShader(shader->second);
        // now increment the shader ref count so we know if how many references
        shader->second->incRefCount();

    }
    else {std::cerr<<"Warning cant attach "<<_shader.c_str() <<" to "<<_program.c_str()<<"\n";}
}





ShaderProgram * ShaderManager::operator[](const std::string &_programName)
{
    std::map <std::string, ShaderProgram * >::const_iterator program=shaderPrograms.find(_programName);
    // make sure we have a valid  program
    if(program!=shaderPrograms.end() )
    {
        return  program->second;
    }
    else
    {
        std::cerr<<"Warning Program not know in [] "<<_programName.c_str();
        std::cerr<<"returning a null program and hoping for the best\n";
        return nullProgram;
    }
}






