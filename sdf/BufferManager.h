//
//  BufferManager.h
//  sdf
//
//  Created by Данил on 09/03/2015.
//  Copyright (c) 2015 Данил. All rights reserved.
//

#ifndef __sdf__BufferManager__
#define __sdf__BufferManager__

#include "glInclude.h"
#include "math_3d.h"
#include "ShaderManger.h"
#include <map>
#endif /* defined(__sdf__BufferManager__) */
using namespace std;


struct Vertex {
    Vector3f m_pos;
    Vector2f m_tex;
    Vector3f m_normal;
    Vertex() {}
    Vertex(Vector3f pos, Vector2f tex) {
        m_pos = pos;
        m_tex = tex;
        m_normal = Vector3f(0.0f, 0.0f, 0.0f);
    }
};

class Buffer{
   // string nameInShader;
    GLuint VBO[1];
    GLuint IBO;
    float* vert;

    GLuint size;
public:
    Buffer(){};
    Buffer(float* _vert, GLuint _size) : vert(_vert), size(_size){}

    void CalcNormals(const GLuint* pIndi, unsigned int IndexCount,Vertex* pVertices,  unsigned int VertexCount);
    void CreateVertexBuffer(ShaderProgram* program,string name);
    void CreateIndexBuffer(int* indi);

};


class BufferVao{
    GLuint VAO[1];
    map<string,Buffer*> buffers;
public:

    Buffer * addBuffer(string name,float* _vert,GLuint _size){
     //   buffers[name] = new Buffer(_vert,_size);
        buffers.insert(pair<string,Buffer*>(name,new Buffer(_vert,_size)));

        return buffers[name];
    }
    void CreateVao();
    void linkBuffer(const string &_bufferName,ShaderProgram* program,string name);
    
    Buffer * operator[](const string &_bufferName);
    void drawArrays();
};
class BuffeManager{
    map<string,BufferVao*> buffers;
public:
    BufferVao * operator[](const string &_bufferName);
    BufferVao * addBuffer(string name){
        buffers.insert(pair<string,BufferVao*>(name,new BufferVao));
        return buffers[name];
    }


//mapBuffer

};