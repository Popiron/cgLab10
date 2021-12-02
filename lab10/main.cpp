// ������ ����� � ��������

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


// ���������� � ����������������� ID
// ID ��������� ���������
GLuint Program;
// ID �������� ������
GLint Attrib_vertex;
// ID �������� �����
GLint Attrib_color;
// ID ������� ���������� �����
GLint Unif_color;
// ID VBO ������
GLuint VBO_position;
// ID VBO �����
GLuint VBO_color;

GLint Unif_translate_x;
GLint Unif_translate_y;


float translate_x = 0.0;
float translate_y = 0.0;


// �������
struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};



// �������� ��� ���������� �������
const char* VertexShaderSource = R"(
    #version 330 core

    // ���������� �������. �������, ���������������� ����� �����.
    in vec3 vertexPosition;
    in vec4 color;

    uniform float translate_y;
    uniform float translate_x;

    
    // �������� �������� � ������������ �������, ��������������� � �������� �� ����������� ������ 
    out vec3 vPosition;
    out vec4 vert_color;

    void main() {
        // ������� ����������������� ���������� �� ����������� ������
        vPosition = vertexPosition;

        // ����������� ���� ��������
        float x_angle = 185;
        float y_angle = 0;
        
        // ������������ �������
        vec3 position = vertexPosition * mat3(
            1, 0, 0,
            0, cos(x_angle), -sin(x_angle),
            0, sin(x_angle), cos(x_angle)
        ) * mat3(
            cos(y_angle), 0, sin(y_angle),
            0, 1, 0,
            -sin(y_angle), 0, cos(y_angle)
        );

        position[0] = position[0] + translate_x;
        position[1] = position[1] + translate_y;

        // ����������� ������� ��������� ���������� gl_Position
        gl_Position = vec4(position, 1.0);
        vert_color = color;
    }
)";

// �������� ��� ������������ �������
const char* FragShaderSource = R"(
    #version 330 core
    in vec4 vert_color;

    out vec4 color;
    void main() {
        color = vert_color;
    }
)";


void Init();
void Draw();
void Release();


int main() {
    sf::Window window(sf::VideoMode(1200, 1200), "My OpenGL window", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    window.setActive(true);

    // ������������� glew
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

        if (event.type == event.KeyPressed) {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (event.key.code == sf::Keyboard::Up)
            {
                translate_y += 0.01;
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                translate_y -= 0.01;
            }
            if (event.key.code == sf::Keyboard::Left)
            {
                translate_x -= 0.01;
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                translate_x += 0.01;
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
    glGenBuffers(1, &VBO_position);
    glGenBuffers(1, &VBO_color);
    // ������� ���������
    Vertex triangle[] = {
        { 0.0f, 0.0f, 0.16f }, 
        { 0.0f, 0.3f, 0.0f }, 
        { 0.3f, -0.3f, 0.0f },

        { 0.0f, 0.0f, 0.16f },
        { 0.3f, -0.3f, 0.0f },
        { -0.3f, -0.3f, 0.0f },

        { 0.0f, 0.0f, 0.16f },
        { -0.3f, -0.3f, 0.0f },
        { 0.0f, 0.3f, 0.0f },

       { 0.0f, 0.3f, 0.0f },
       { 0.3f, -0.3f, 0.0f },
       { -0.3f, -0.3f, 0.0f }, 
    };

    // ���� ������������
    float colors[12][4] = {
        { 1.0, 1.0, 1.0, 1.0 },
        { 0.0, 0.0, 1.0, 1.0 },
        { 0.0, 1.0, 0.0, 1.0 },

        { 1.0, 1.0, 1.0, 1.0 },
        { 0.0, 1.0, 0.0, 1.0 },
        { 1.0, 0.0, 0.0, 1.0 },

        { 1.0, 1.0, 1.0, 1.0 },
        { 1.0, 0.0, 0.0, 1.0 },
        { 0.0, 0.0, 1.0, 1.0 },

        { 0.0, 0.0, 1.0, 1.0 },
        { 0.0, 1.0, 0.0, 1.0 },
        { 1.0, 0.0, 0.0, 1.0 },
    };


    // �������� ������� � �����
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    checkOpenGLerror();
}


void InitShader() {
    // ������� ��������� ������
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    // �������� �������� ���
    glShaderSource(vShader, 1, &VertexShaderSource, NULL);
    // ����������� ������
    glCompileShader(vShader);
    std::cout << "vertex shader \n";
    ShaderLog(vShader);

    // ������� ����������� ������
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    // �������� �������� ���
    glShaderSource(fShader, 1, &FragShaderSource, NULL);
    // ����������� ������
    glCompileShader(fShader);
    std::cout << "fragment shader \n";
    ShaderLog(fShader);

    // ������� ��������� � ����������� ������� � ���
    Program = glCreateProgram();
    glAttachShader(Program, vShader);
    glAttachShader(Program, fShader);

    // ������� ��������� ���������
    glLinkProgram(Program);
    // ��������� ������ ������
    int link_ok;
    glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
    {
        std::cout << "error attach shaders \n";
        return;
    }

    // ���������� ID �������� �� ��������� ���������
    const char* attr_name = "vertexPosition";
    Attrib_vertex = glGetAttribLocation(Program, attr_name);
    if (Attrib_vertex == -1)
    {
        std::cout << "could not bind attrib " << attr_name << std::endl;
        return;
    }

    // ���������� ID �������
    const char* unif_name_x = "translate_x";
    Unif_translate_x = glGetUniformLocation(Program, unif_name_x);
    if (Unif_color == -1)
    {
        std::cout << "could not bind uniform " << unif_name_x << std::endl;
        return;
    }

    // ���������� ID �������
    const char* unif_name_y = "translate_y";
    Unif_translate_y = glGetUniformLocation(Program, unif_name_y);
    if (Unif_color == -1)
    {
        std::cout << "could not bind uniform " << unif_name_y << std::endl;
        return;
    }

    checkOpenGLerror();
}

void Init() {
    InitShader();
    InitVBO();
    // �������� �������� �������
    glEnable(GL_DEPTH_TEST);
}


void Draw() {
    // ������������� ��������� ��������� �������
    glUseProgram(Program);

    // �������� ������� � ������
    glUniform1f(Unif_translate_x, translate_x);
    glUniform1f(Unif_translate_y, translate_y);

    // �������� ������� ���������
    glEnableVertexAttribArray(Attrib_vertex);
    glEnableVertexAttribArray(Attrib_color);

    // ���������� VBO_position
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // ���������� VBO_color
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glVertexAttribPointer(Attrib_color, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // ��������� VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // �������� ������ �� ����������(������)
    glDrawArrays(GL_TRIANGLES, 0, 12);

    // ��������� ������� ���������
    glDisableVertexAttribArray(Attrib_vertex);
    glDisableVertexAttribArray(Attrib_color);

    glUseProgram(0);
    checkOpenGLerror();
}


// ������������ ��������
void ReleaseShader() {
    // ��������� ����, �� ��������� �������� ���������
    glUseProgram(0);
    // ������� ��������� ���������
    glDeleteProgram(Program);
}

// ������������ ������
void ReleaseVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO_position);
    glDeleteBuffers(1, &VBO_color);
}

void Release() {
    ReleaseShader();
    ReleaseVBO();
}
