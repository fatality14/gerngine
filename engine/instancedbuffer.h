#pragma once

#include <mesh.h>
#include <position.h>
#include <abuffer.h>

class InstancedBuffer : public ABuffer<Mesh, Vertex>{
public:
    InstancedBuffer(Mesh& m, Shader& s, string name = "noname")
        : ABuffer(m, s, name),
          vmodel("model", 4, 0, 1)
    {
        shaderfields.push(vpos);
        shaderfields.push(vtex);
        shaderfields.push(vnorm);
    }
    ~InstancedBuffer(){
        glDeleteBuffers(1, &VBO1);
    }

    void setModelMatrices(vector<Position>& modelMatrices){
        this->modelMatrices.clear();
        for(size_t i = 0; i < modelMatrices.size(); ++i){
            this->modelMatrices.push_back(modelMatrices[i].getModelMatrix());
        }

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->modelMatrices.size(), this->modelMatrices.data(), GL_STATIC_DRAW);

        vmodel.pushToShader(*shader);
    }
    void setShader(Shader* s){
        ABuffer::setShader(s);

        bind();

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);

        vmodel.pushToShader(*shader);

        unbind();
    }

    void genBuffers(){
        ABuffer::genBuffers();

        bind();

        glGenBuffers(1, &VBO1);

        //current vao should be set in while window loop
        unbind();
    }

private:
    GLuint VBO1;
    vector<glm::mat4> modelMatrices;
    ShaderMatAttrib<glm::mat4> vmodel;

    ShaderAttrib<GLfloat, Vertex> vpos = ShaderAttrib<GLfloat, Vertex>(
                "vertex_position", 3,
                offsetof(Vertex, position));

    ShaderAttrib<GLfloat, Vertex> vtex = ShaderAttrib<GLfloat, Vertex>(
                "vertex_texcoord", 2,
                offsetof(Vertex, texcoord));

    ShaderAttrib<GLfloat, Vertex> vnorm = ShaderAttrib<GLfloat, Vertex>(
                "vertex_normal", 3,
                offsetof(Vertex, normal));
};
