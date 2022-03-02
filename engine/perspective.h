#pragma once

#include <common.h>
#include <window.h>
#include <mouselistener.h>
#include <camera.h>
#include <shader.h>

class Perspective{
public:
    float fov = 90.f;
    float nearPlane = 0.001f;
    float farPlane = 1000.f;

    Perspective(Window& w){
        window = &w;

        projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(window->fbWidth) / window->fbHeight, nearPlane, farPlane);
    }

    void pushToShader(Shader* s, string uniformName){
        updateMatrices();
        s->setUniformMatrix4fv(uniformName, glm::value_ptr(projectionMatrix));
    }
    void updateMatrices(){
        glfwGetFramebufferSize(window->__getWindowPtr(), &window->fbWidth, &window->fbHeight);
        projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(window->fbWidth) / window->fbHeight, nearPlane, farPlane);
    }
    const GLFWwindow* __getWindowPtr(){
        return  window->__getWindowPtr();
    }
    glm::mat4& getProjectionMatrix(){
        return projectionMatrix;
    }

    //TODO: fill with smth later
    void setDefaultEvents(){}
private:
    glm::mat4 projectionMatrix;

    Window* window;
};
