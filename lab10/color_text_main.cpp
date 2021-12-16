// Вращающийся треугольник с текстурой (можно вращать стрелочками)

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


// В C и C++ есть оператор #, который позволяет превращать параметры макроса в строку
#define TO_STRING(x) #x


// Переменные с индентификаторами ID
// ID шейдерной программы
GLuint shaderProgram;
// ID атрибута вершин
GLint attribVertex;
// ID атрибута текстурных координат
GLint attribTexture;
GLint attribColor;
// ID юниформа текстуры
GLint unifTexture;
GLint unifTexture2;
GLint modId;
// ID буфера ыершин
GLuint vertexVBO;
// ID буфера текстурных координат
GLuint textureVBO;

GLuint colorsVBO;
// ID текстуры
GLint textureHandle;
GLint textureHandle2;
// SFML текстура
sf::Texture textureData;
sf::Texture textureData2;

// Вершина
struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

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

const char* VertexShaderSource = TO_STRING(
    #version 330 core\n

in vec3 vertCoord;
in vec3 textureCoord;
in vec4 color;
out vec4 vert_color;
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
    vert_color = color;
    gl_Position = vec4(position, 1.0);
}
);

const char* FragShaderSource = TO_STRING(
    #version 330 core\n

    uniform sampler2D textureData;
    uniform sampler2D textureDataToo;
    uniform float mod;
in vec4 vert_color;
in vec3 tCoord;
out vec4 color;
void main()
{
    vec4 tex = texture(textureData, tCoord.xy) * (mod / 10);
    vec4 tex2 = texture(textureDataToo, tCoord.xy) * ((10 - mod) / 10);
    color = vec4(tex2.r + tex.r, tex2.g + tex.g, tex2.b + tex.b, tex2.a + tex.a);
}
);


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
                switch (event.key.code) {
                case (sf::Keyboard::Left): DecMod(); break;
                case (sf::Keyboard::Right): IncMod(); break;
                default: break;
                }
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


void InitVBO()
{
    glGenBuffers(1, &colorsVBO);
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &vertexVBO);
    

    // Объявляем вершины треугольника
    Vertex triangle[] = {
            {-0.5,-0.5,0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},
            {-0.5,-0.5,0.5},{-0.5,0.5,0.5},{-0.5,0.5,-0.5},{-0.5,-0.5,-0.5},
            {-0.5,-0.5,-0.5},{-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
            {0.5,-0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
            {-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},
            {-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5}
    };

    // Объявляем текстурные координаты
    Vertex texture[] = {
            {0,0,0},{0,1,0},{1,1,0},{1,0,0},
            {0,0,0},{0,1,0},{1,1,0},{1,0,0},
            {0,0,0},{0,1,0},{1,1,0},{1,0,0},
            {0,0,0},{0,1,0},{1,1,0},{1,0,0},
            {0,0,0},{0,1,0},{1,1,0},{1,0,0},
            {0,0,0},{0,1,0},{1,1,0},{1,0,0},
    };

    float colors[24][4] =
    {
        {1.0,0.0,0.0,1.0},{0.0,1.0,0.0,1.0},{0.0,0.0,1.0,1.0},{0.0,0.0,0.0,1.0},
        {1.0,0.0,0.0,1.0},{0.0,1.0,0.0,1.0},{1.0,1.0,0.0,1.0},{1.0,0.0,1.0,1.0},
        {1.0,0.0,1.0,1.0},{1.0,1.0,0.0,1.0},{0.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},
        {0.0,0.0,0.0,1.0},{0.0,0.0,1.0,1.0},{0.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},
        {0.0,1.0,0.0,1.0},{0.0,0.0,1.0,1.0},{0.0,1.0,1.0,1.0},{1.0,1.0,0.0,1.0},
        {1.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,0.0,1.0,1.0}
    };

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
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

    unifTexture2 = glGetUniformLocation(shaderProgram, "textureDataToo");
    if (unifTexture2 == -1)
    {
        std::cout << "could not bind uniform textureDataToo" << std::endl;
        return;
    }


    modId = glGetUniformLocation(shaderProgram, "mod");
    if (modId == -1)
    {
        std::cout << "could not bind uniform mod" << std::endl;
        return;
    }


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
    const char* filename = "image.jpg";

    const char* filename2 = "image2.jpg";
    if (!textureData.loadFromFile(filename))
    {
        return;
    }
    if (!textureData2.loadFromFile(filename2))
    {
        return;
    }
    textureHandle = textureData.getNativeHandle();
    textureHandle2 = textureData2.getNativeHandle();
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

    glUniform1f(modId, mod);

    // Àêòèâèðóåì òåêñòóðíûé áëîê 0, äåëàòü ýòîãî íå îáÿçàòåëüíî, ïî óìîë÷àíèþ
// è òàê àêòèâèðîâàí GL_TEXTURE0, ýòî íóæíî äëÿ èñïîëüçîâàíèÿ íåñêîëüêèõ òåêñòóð
    glActiveTexture(GL_TEXTURE1);
    // Îá¸ðòêà SFML íà opengl ôóíêöèåé glBindTexture
    sf::Texture::bind(&textureData2);
    // Â uniform êëàä¸òñÿ òåêñòóðíûé èíäåêñ òåêñòóðíîãî áëîêà (äëÿ GL_TEXTURE0 - 0, äëÿ GL_TEXTURE1 - 1 è òä)
    glUniform1i(unifTexture2, 1);

    // Подключаем VBO
    glEnableVertexAttribArray(attribVertex);
    glEnableVertexAttribArray(attribColor);
    glEnableVertexAttribArray(attribTexture);

    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glVertexAttribPointer(attribTexture, 3, GL_FLOAT, GL_FALSE, 0, 0);


    

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Передаем данные на видеокарту(рисуем)
    glDrawArrays(GL_QUADS, 0, 24);

    // Отключаем массив атрибутов
    glDisableVertexAttribArray(attribVertex);
    glDisableVertexAttribArray(attribColor);
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
    glDeleteBuffers(1, &colorsVBO);
    glDeleteBuffers(1, &textureVBO);
}

void Release() {
    ReleaseShader();
    ReleaseVBO();
}
