#pragma once
#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Camera.h"
#include "ShaderLoader.h"
#include "ConsoleController.h"

class Sprite {
public:
	Camera camera;

	glm::vec3 position;
	glm::vec3 scale = glm::vec3(90.0f, 90.0f, 90.0f);

	glm::mat4 model;
	glm::mat4 projCalc;
	glm::mat4 rotationZ;
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;

	GLuint VAO = NULL;
	GLuint VBO = NULL;
	GLuint EBO = NULL;
	GLuint texture = NULL;
	GLuint image = NULL;
	GLuint program = NULL;

	std::string name = "Untitled Sprite";

	void Initalise(glm::vec3 _position, glm::vec3 _scale, std::string textureFilePath, std::string vShaderFilePath, std::string fShaderFilePath, GLuint Indices[], GLfloat Verts[], std::string _name);
	void Tick(float rotationAngle, glm::vec3 rotationAxisZ, Camera _Cam);
	void Render();

};
