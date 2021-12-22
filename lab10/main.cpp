// Вращающийся треугольник с текстурой (можно вращать стрелочками)

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include "Vertex.h"


// В C и C++ есть оператор #, который позволяет превращать параметры макроса в строку
#define TO_STRING(x) #x


// Переменные с индентификаторами ID
// ID шейдерной программы
GLuint shaderProgram;
// ID атрибута вершин
GLint attribVertex;
// ID атрибута текстурных координат
GLint attribTexture;
// ID юниформа текстуры
GLint unifTexture;
// ID буфера ыершин
GLuint vertexVBO;
// ID буфера текстурных координат
GLuint textureVBO;

// ID текстуры
GLint textureHandle;
// SFML текстура
sf::Texture textureData;


float mod = 5.0;

void DecMod()
{
    mod -= 1;
    if (mod < 0)
        mod = 0;
}

void IncMod()
{
    mod += 1;
    if (mod > 10)
        mod = 10;
}



// Шейдер это просто строка, и не кажно, каким образом она получена -
// можно загружать шейдеры из файла, можно объявлять прямо в программе,
// в том числе таким образом, при помощи специального макроса

// К сожалению, этот макрос не учитывает переводы строк, так что если они нужны,
// например, после дирректив препроцессора, нужно явно ставить символ '\n'

const char* VertexShaderSource = R"(
    #version 330 core

    in vec3 vertCoord;
in vec3 textureCoord;
out vec3 tCoord;
void main() {
    tCoord = textureCoord;
    float x_angle = 1.0;
    float y_angle = 1.0;

    vec3 position = vertCoord * mat3(
        1, 0, 0,
        0, cos(x_angle), -sin(x_angle),
        0, sin(x_angle), cos(x_angle)
    )
        *
        mat3(
            cos(y_angle), 0, sin(y_angle),
            0, 1, 0,
            -sin(y_angle), 0, cos(y_angle)
        );
    vec4 vert = vec4(position, 1.0);
    
    gl_Position = vec4(vert.xy / 10, vert.z * vert[3] / 100, vert[3]);
}
)";

const char* FragShaderSource = R"(
    #version 330 core

    uniform sampler2D textureData;
in vec3 tCoord;
out vec4 color;
void main()
{
    vec3 coord = normalize(tCoord);
    color = texture(textureData, coord.xy);
}
)";


void Init();
void Draw();
void Release();


int main() {
    sf::Window window(sf::VideoMode(600, 600), "My OpenGL window", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    window.setActive(true);

    glewInit();

    Init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                //switch (event.key.code) {
                //case (sf::Keyboard::Left): DecMod(); break;
                //case (sf::Keyboard::Right): IncMod(); break;
                //default: break;
                //}
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Draw();

        window.display();
    }

    Release();
    return 0;
}


// Проверка ошибок OpenGL, если есть то вывод в консоль тип ошибки
void checkOpenGLerror() {
    GLenum errCode;
    // Коды ошибок можно смотреть тут
    // https://www.khronos.org/opengl/wiki/OpenGL_Error
    if ((errCode = glGetError()) != GL_NO_ERROR)
        std::cout << "OpenGl error!: " << errCode << std::endl;
}

// Функция печати лога шейдера
void ShaderLog(unsigned int shader)
{
    int infologLen = 0;
    int charsWritten = 0;
    char* infoLog;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
    if (infologLen > 1)
    {
        infoLog = new char[infologLen];
        if (infoLog == NULL)
        {
            std::cout << "ERROR: Could not allocate InfoLog buffer" << std::endl;
            exit(1);
        }
        glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
        std::cout << "InfoLog: " << infoLog << "\n\n\n";
        delete[] infoLog;
    }
}

std::vector<Vertex> vertices;
std::vector<Vertex> textures;

void InitVBO()
{
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &vertexVBO);
    LoadOBJ("bus2.obj", vertices, textures);


    // Объявляем вершины треугольника
    //Vertex triangle[] = {
    //        {-0.5,-0.5,0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},
    //        {-0.5,-0.5,0.5},{-0.5,0.5,0.5},{-0.5,0.5,-0.5},{-0.5,-0.5,-0.5},
    //        {-0.5,-0.5,-0.5},{-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
    //        {0.5,-0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
    //        {-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},
    //        {-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5}
    //};

    // Объявляем текстурные координаты
    //Vertex texture[] = {
    //        {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    //        {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    //        {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    //        {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    //        {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    //        {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    //};

    //float colors[24][4] =
    //{
    //    {1.0,0.0,0.0,1.0},{0.0,1.0,0.0,1.0},{0.0,0.0,1.0,1.0},{0.0,0.0,0.0,1.0},
    //    {1.0,0.0,0.0,1.0},{0.0,1.0,0.0,1.0},{1.0,1.0,0.0,1.0},{1.0,0.0,1.0,1.0},
    //    {1.0,0.0,1.0,1.0},{1.0,1.0,0.0,1.0},{0.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},
    //    {0.0,0.0,0.0,1.0},{0.0,0.0,1.0,1.0},{0.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},
    //    {0.0,1.0,0.0,1.0},{0.0,0.0,1.0,1.0},{0.0,1.0,1.0,1.0},{1.0,1.0,0.0,1.0},
    //    {1.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,0.0,1.0,1.0}
    //};

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, textures.size()*sizeof(Vertex), &textures[0], GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
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

    //unifTexture2 = glGetUniformLocation(shaderProgram, "textureDataToo");
    //if (unifTexture2 == -1)
    //{
    //    std::cout << "could not bind uniform textureDataToo" << std::endl;
    //    return;
    //}


    //modId = glGetUniformLocation(shaderProgram, "mod");
    //if (modId == -1)
    //{
    //    std::cout << "could not bind uniform mod" << std::endl;
    //    return;
    //}


    /*
    * unifAngle = glGetUniformLocation(shaderProgram, "angle");
    if (unifAngle == -1)
    {
        std::cout << "could not bind uniform angle" << std::endl;
        return;
    }
    */


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
