#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "structures.h"


Index slash_string_to_index(std::string s)
{
	std::vector<std::string> split;
	std::stringstream ss(s);
	std::string str;
	while (std::getline(ss, str, '/'))
	{
		split.push_back(str);
	}
	Index i = { std::stoi(split[0]), std::stoi(split[1]), std::stoi(split[2]) };
	return i;
}

Index surface_to_index(Surface s)
{
	std::vector<Index> v;
	Index i = { s.vert[0].x, s.vert[1].x, s.vert[2].x };
	return i;
}

std::vector<float> InitializeVBO(std::string filename, int& count)
{
	std::vector<Vertex> v;
	std::vector<Tex> t;
	std::vector<Normal> n;
	std::vector<Surface> s;

	std::ifstream infile(filename);
	std::string line;

	//проходим по строкам файла
	while (std::getline(infile, line))
	{
		if (line[0] == 'v' || line[0] == 'f')
		{
			//разбиваем каждую строку по пробелам в вектор split
			std::vector<std::string> split;
			std::stringstream ss(line);
			std::string str;
			while (std::getline(ss, str, ' '))
			{
				split.push_back(str);
			}

			//заполняем вектор вершин
			if (split[0] == "v")
			{
				Vertex vert = { std::stof(split[1]), std::stof(split[2]), std::stof(split[3]) };
				v.push_back(vert);
			}

			//заполняем вектор текстурных координат
			else if (split[0] == "vt")
			{
				Tex tex = { std::stof(split[1]), std::stof(split[2]) };
				t.push_back(tex);
			}

			//заполняем вектор нормалей
			else if (split[0] == "vn")
			{
				Normal norm = { std::stof(split[1]), std::stof(split[2]), std::stof(split[3]) };
				n.push_back(norm);
			}

			//заполняем массив индексов и соответствий
			else if (split[0] == "f")
			{
				Surface surf =
				{
					slash_string_to_index(split[1]),
					slash_string_to_index(split[2]),
					slash_string_to_index(split[3]),
				};
				s.push_back(surf);
			}
		}
	}

	std::vector<float> pos_tex;
	for (int i = 0; i < s.size(); ++i)
	{
		pos_tex.push_back(v[s[i].vert[0].x - 1].x);
		pos_tex.push_back(v[s[i].vert[0].x - 1].y);
		pos_tex.push_back(v[s[i].vert[0].x - 1].z);
		pos_tex.push_back(t[s[i].vert[0].y - 1].x);
		pos_tex.push_back(1 - t[s[i].vert[0].y - 1].y);
		pos_tex.push_back(n[s[i].vert[0].z - 1].x);
		pos_tex.push_back(n[s[i].vert[0].z - 1].y);
		pos_tex.push_back(n[s[i].vert[0].z - 1].z);

		pos_tex.push_back(v[s[i].vert[1].x - 1].x);
		pos_tex.push_back(v[s[i].vert[1].x - 1].y);
		pos_tex.push_back(v[s[i].vert[1].x - 1].z);
		pos_tex.push_back(t[s[i].vert[1].y - 1].x);
		pos_tex.push_back(1 - t[s[i].vert[1].y - 1].y);
		pos_tex.push_back(n[s[i].vert[1].z - 1].x);
		pos_tex.push_back(n[s[i].vert[1].z - 1].y);
		pos_tex.push_back(n[s[i].vert[1].z - 1].z);

		pos_tex.push_back(v[s[i].vert[2].x - 1].x);
		pos_tex.push_back(v[s[i].vert[2].x - 1].y);
		pos_tex.push_back(v[s[i].vert[2].x - 1].z);
		pos_tex.push_back(t[s[i].vert[2].y - 1].x);
		pos_tex.push_back(1 - t[s[i].vert[2].y - 1].y);
		pos_tex.push_back(n[s[i].vert[2].z - 1].x);
		pos_tex.push_back(n[s[i].vert[2].z - 1].y);
		pos_tex.push_back(n[s[i].vert[2].z - 1].z);
	}
	count = s.size() * 3;
	return pos_tex;
}