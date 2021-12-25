#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "ids.h"
#include "logs.h"

void Draw() {
    // Устанавливаем шейдерную программу текущей
    glUseProgram(shaderProgram);

    // Активируем текстурный блок 0, делать этого не обязательно, по умолчанию
    // и так активирован GL_TEXTURE0, это нужно для использования нескольких текстур
    glActiveTexture(GL_TEXTURE0);
    // Обёртка SFML на opengl функцией glBindTexture
    sf::Texture::bind(&textureData);
    // В uniform кладётся текстурный индекс текстурного блока (для GL_TEXTURE0 - 0, для GL_TEXTURE1 - 1 и тд)
    glUniform1i(unifTexture, 0);

    // Подключаем VBO
    glEnableVertexAttribArray(attribVertex);
    glEnableVertexAttribArray(attribTexture);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glVertexAttribPointer(attribTexture, 3, GL_FLOAT, GL_FALSE, 0, 0);




    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Передаем данные на видеокарту(рисуем)
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    // Отключаем массив атрибутов
    glDisableVertexAttribArray(attribVertex);
    glDisableVertexAttribArray(attribTexture);

    // Отключаем шейдерную программу
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