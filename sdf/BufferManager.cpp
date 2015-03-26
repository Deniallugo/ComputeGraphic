//
//  BufferManager.cpp
//  sdf
//
//  Created by Данил on 09/03/2015.
//  Copyright (c) 2015 Данил. All rights reserved.
//

#include "BufferManager.h"
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))



void Buffer::CreateVertexBuffer( ShaderProgram* program,string name){


    //    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vert, GL_STATIC_DRAW);

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vert)*sizeof(GLfloat), vert, GL_STATIC_DRAW);

    program->vertexAttribPointer(name,size/3,GL_FLOAT,0,0,0);
    program->enableAttribArray(name);

}



void Buffer::CreateIndexBuffer(int* indi) {

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STATIC_DRAW);

}



void Buffer::CalcNormals(const GLuint* pIndi, unsigned int IndexCount,Vertex* pVertices,  unsigned int VertexCount) {

    for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
        unsigned int Index0 = pIndi[i];
        unsigned int Index1 = pIndi[i + 1];
        unsigned int Index2 = pIndi[i + 2];
        Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
        Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
        Vector3f Normal = v1.Cross(v2);
        Normal.Normalize();

        pVertices[Index0].m_normal += Normal;
        pVertices[Index1].m_normal += Normal;
        pVertices[Index2].m_normal += Normal;
    }

    for (unsigned int i = 0 ; i < VertexCount ; i++) {
        pVertices[i].m_normal.Normalize();
    }

}

BufferVao * BuffeManager::operator[](const std::string &bufferName)
{
    std::map <std::string, BufferVao * >::const_iterator buffer= buffers.find(bufferName);
    // make sure we have a valid  program
    if(buffer!=buffers.end() )
    {
        return  buffer->second;
    }
    else
    {
        std::cerr<<"Warning Program not know in [] "<<bufferName.c_str();
        std::cerr<<"returning a null program and hoping for the best\n";
        return nullptr;
    }

}

void BufferVao::drawArrays(){

    glBindVertexArrayAPPLE(VAO[0]);  // select first VAO

    glDrawArrays(GL_TRIANGLES, 0, 3); // draw first object

}

void BufferVao::CreateVao(){


    glGenVertexArraysAPPLE(2,VAO);

    glBindVertexArrayAPPLE(VAO[0]);

}

Buffer * BufferVao::operator[](const std::string &bufferName)
{
    std::map <std::string, Buffer * >::const_iterator buffer= buffers.find(bufferName);
    // make sure we have a valid  program
    if(buffer!=buffers.end() )
    {
        return  buffer->second;
    }
    else
    {
        std::cerr<<"Warning Program not know in [] "<<bufferName.c_str();
        std::cerr<<"returning a null program and hoping for the best\n";
        return nullptr;
    }
}

