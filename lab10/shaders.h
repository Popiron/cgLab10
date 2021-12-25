#pragma once

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
    //vec3 coord = normalize(tCoord);
    color = texture(textureData, tCoord.xy);
}
)";