#include "Sprite.h"

//Set up values for a sprite to be used ingame
void Sprite::Initalise(glm::vec3 _position, glm::vec3 _scale, std::string textureFilePath, std::string vShaderFilePath, std::string fShaderFilePath, GLuint Indices[], GLfloat Verts[], std::string _name)
{

	Console_OutputLog("Initalising Sprite: " + _name, LOGINFO);

	try
	{
		position = _position;
		scale = _scale;
		name = _name;

		//Texture

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;

		unsigned char* image = SOIL_load_image(textureFilePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Program

		program = ShaderLoader::CreateProgram(vShaderFilePath.c_str(), fShaderFilePath.c_str());

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		//sprites->push_back(this);

		Console_OutputLog("Initalised Sprite: " + name, LOGINFO);
	}
	catch (...) {
		Console_OutputLog("Failed To Initalise Sprite: " + name, LOGWARN);
	}
}

void Sprite::Tick(float rotationAngle, glm::vec3 rotationAxisZ, Camera _Cam) {
	try {
		camera = _Cam;
		translationMatrix = glm::translate(glm::mat4(), position);
		rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);
		scaleMatrix = glm::scale(glm::mat4(), scale);
		model = translationMatrix * rotationZ * scaleMatrix;
		projCalc = camera.proj * camera.view * model;
	}
	catch (...) {
		Console_OutputLog("Sprite Failed Tick: " + name, LOGWARN);
	}
}

void Sprite::Render()
{
	try {
		glUseProgram(program);
		GLuint mvpLoc2 = glGetUniformLocation(program, "proj_calc");
		glUniformMatrix4fv(mvpLoc2, 1, GL_FALSE, glm::value_ptr(projCalc));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
	catch (...) {
		Console_OutputLog("Sprite Failed To Render: " + name, LOGWARN);
	}
}
