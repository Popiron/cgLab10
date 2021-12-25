#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "ids.h"
#include "logs.h"

void Draw() {
    // ������������� ��������� ��������� �������
    glUseProgram(shaderProgram);

    // ���������� ���������� ���� 0, ������ ����� �� �����������, �� ���������
    // � ��� ����������� GL_TEXTURE0, ��� ����� ��� ������������� ���������� �������
    glActiveTexture(GL_TEXTURE0);
    // ������ SFML �� opengl �������� glBindTexture
    sf::Texture::bind(&textureData);
    // � uniform ������� ���������� ������ ����������� ����� (��� GL_TEXTURE0 - 0, ��� GL_TEXTURE1 - 1 � ��)
    glUniform1i(unifTexture, 0);

    // ���������� VBO
    glEnableVertexAttribArray(attribVertex);
    glEnableVertexAttribArray(attribTexture);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glVertexAttribPointer(attribTexture, 3, GL_FLOAT, GL_FALSE, 0, 0);




    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // �������� ������ �� ����������(������)
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    // ��������� ������ ���������
    glDisableVertexAttribArray(attribVertex);
    glDisableVertexAttribArray(attribTexture);

    // ��������� ��������� ���������
    glUseProgram(0);
    checkOpenGLerror();
}


void ReleaseShader() {
    glUseProgram(0);
    glDeleteProgram(shaderProgram);
}

void ReleaseVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &textureVBO);
}

void Release() {
    ReleaseShader();
    ReleaseVBO();
}