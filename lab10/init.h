#pragma once
#include <GL/glew.h>
#include "ids.h"
#include "data.h"
#include "logs.h"
#include "shaders.h"

void InitVBO()
{
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &vertexVBO);
    LoadOBJ("bus2.obj", vertices, textures);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(Vertex), &textures[0], GL_STATIC_DRAW);
    checkOpenGLerror();
}


void InitShader() {
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &VertexShaderSource, NULL);
    glCompileShader(vShader);
    std::cout << "vertex shader \n";
    ShaderLog(vShader);

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &FragShaderSource, NULL);
    glCompileShader(fShader);
    std::cout << "fragment shader \n";
    ShaderLog(fShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);

    glLinkProgram(shaderProgram);
    int link_status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_status);
    if (!link_status)
    {
        std::cout << "error attach shaders \n";
        return;
    }

    attribVertex = glGetAttribLocation(shaderProgram, "vertCoord");
    if (attribVertex == -1)
    {
        std::cout << "could not bind attrib vertCoord" << std::endl;
        return;
    }

    attribTexture = glGetAttribLocation(shaderProgram, "textureCoord");
    if (attribTexture == -1)
    {
        std::cout << "could not bind attrib textureCoord" << std::endl;
        return;
    }

    unifTexture = glGetUniformLocation(shaderProgram, "textureData");
    if (unifTexture == -1)
    {
        std::cout << "could not bind uniform textureData" << std::endl;
        return;
    }

    checkOpenGLerror();
}

void InitTexture()
{
    const char* filename = "bus2.png";

    if (!textureData.loadFromFile(filename))
    {
        return;
    }

    textureHandle = textureData.getNativeHandle();
}

void Init() {
    InitShader();
    InitVBO();
    InitTexture();
    glEnable(GL_DEPTH_TEST);
}