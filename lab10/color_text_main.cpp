// ����������� ����������� � ��������� (����� ������� �����������)

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


// � C � C++ ���� �������� #, ������� ��������� ���������� ��������� ������� � ������
#define TO_STRING(x) #x


// ���������� � ����������������� ID
// ID ��������� ���������
GLuint shaderProgram;
// ID �������� ������
GLint attribVertex;
// ID �������� ���������� ���������
GLint attribTexture;
GLint attribColor;
// ID �������� ��������
GLint unifTexture;
// ID �������� ���� ��������
GLint unifAngle;
// ID ������ ������
GLuint vertexVBO;
// ID ������ ���������� ���������
GLuint textureVBO;

GLuint colorsVBO;
// ID ��������
GLint textureHandle;
// SFML ��������
sf::Texture textureData;

float objectRotation = 0;


// �������
struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};



// ������ ��� ������ ������, � �� �����, ����� ������� ��� �������� -
// ����� ��������� ������� �� �����, ����� ��������� ����� � ���������,
// � ��� ����� ����� �������, ��� ������ ������������ �������

// � ���������, ���� ������ �� ��������� �������� �����, ��� ��� ���� ��� �����,
// ��������, ����� ��������� �������������, ����� ���� ������� ������ '\n'

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
in vec4 vert_color;
in vec3 tCoord;
out vec4 color;
void main()
{
    vec4 tex = texture(textureData, tCoord.xy);
    color = vec4(vert_color.r * tex.r, vert_color.g * tex.g, vert_color.b * tex.b, vert_color.a * tex.a);
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
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Draw();

        window.display();
    }

    Release();
    return 0;
}


// �������� ������ OpenGL, ���� ���� �� ����� � ������� ��� ������
void checkOpenGLerror() {
    GLenum errCode;
    // ���� ������ ����� �������� ���
    // https://www.khronos.org/opengl/wiki/OpenGL_Error
    if ((errCode = glGetError()) != GL_NO_ERROR)
        std::cout << "OpenGl error!: " << errCode << std::endl;
}

// ������� ������ ���� �������
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
    

    // ��������� ������� ������������
    Vertex triangle[] = {
            {-0.5,-0.5,0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},
            {-0.5,-0.5,0.5},{-0.5,0.5,0.5},{-0.5,0.5,-0.5},{-0.5,-0.5,-0.5},
            {-0.5,-0.5,-0.5},{-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
            {0.5,-0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5},
            {-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},
            {-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5}
    };

    // ��������� ���������� ����������
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

    attribColor = glGetAttribLocation(shaderProgram, "color");
    if (attribColor == -1)
    {
        std::cout << "could not bind attrib color" << std::endl;
        return;
    }

    unifTexture = glGetUniformLocation(shaderProgram, "textureData");
    if (unifTexture == -1)
    {
        std::cout << "could not bind uniform textureData" << std::endl;
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
    // ��������� �������� �� �����
    if (!textureData.loadFromFile(filename))
    {
        // �� ����� ��������� ��������
        return;
    }
    // ������ �������� openGL ���������� ��������
    textureHandle = textureData.getNativeHandle();
}

void Init() {
    InitShader();
    InitVBO();
    InitTexture();
    glEnable(GL_DEPTH_TEST);
}


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
    glEnableVertexAttribArray(attribColor);
    glEnableVertexAttribArray(attribTexture);

    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glVertexAttribPointer(attribTexture, 3, GL_FLOAT, GL_FALSE, 0, 0);


    

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // �������� ������ �� ����������(������)
    glDrawArrays(GL_QUADS, 0, 24);

    // ��������� ������ ���������
    glDisableVertexAttribArray(attribVertex);
    glDisableVertexAttribArray(attribColor);
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
    glDeleteBuffers(1, &colorsVBO);
    glDeleteBuffers(1, &textureVBO);
}

void Release() {
    ReleaseShader();
    ReleaseVBO();
}
