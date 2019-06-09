#include "3D.h"

LoadTexture TextureLoader;

void Simple3DObject::Initalise(glm::vec3 _position, glm::vec3 _scale, std::string textureFilePath, std::string vShaderFilePath, std::string fShaderFilePath, GLuint Indices[], GLfloat Verts[], std::string _name, int _size, bool _reflective)
{
	Console_OutputLog("Initalising Basic 3D: " + _name, LOGINFO);

	position = _position;
	scale = _scale;
	name = _name;
	m_size = _size;
	reflective = _reflective;

	program = ShaderLoader::CreateProgram(vShaderFilePath.c_str(), fShaderFilePath.c_str());

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)(3 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)(6 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	texture = TextureLoader.loadTexture(textureFilePath.c_str());
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	Console_OutputLog("Initalised Basic 3D: " + name, LOGINFO);

}

void Simple3DObject::Render(Camera* cam, CubeMap _skyBox)
{

	glUseProgram(program);
	
	glm::mat4 model;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), scale);
	model = translationMatrix * rotationZ * scaleMatrix;
	glm::mat4 mvp = cam->proj * cam->view * glm::scale(glm::mat4(), scale);

	//POSITION AND SCALE
	glm::mat4 projCalc = cam->proj * cam->view * model;

	GLint mvpLoc = glGetUniformLocation(program, "proj_calc");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(projCalc));
	GLint lightModel = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(lightModel, 1, GL_FALSE, glm::value_ptr(model));
	
	//glm::mat4 mvp = cam.getMVP(position, scale, rotationZ);
	//GLuint mvpLoc = glGetUniformLocation(program, "proj_calc");
	//glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	if (reflective) {
		glActiveTexture(GL_TEXTURE1); 
		glUniform1i(glGetUniformLocation(program, "skybox"), 1); 
		glBindTexture(GL_TEXTURE_CUBE_MAP, _skyBox.texID);
	}

	glBindVertexArray(VAO);

	glBindTexture(GL_TEXTURE_2D, program);

	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

Bullet::Bullet(Model* mObject, float deltaTime)
{
	object = mObject;
	time = deltaTime;
	deadLifeTime = time + lifeTime;
}

Bullet::~Bullet()
{
	delete object;
}

void Bullet::Tick(float deltaTime)
{
	time += deltaTime;
}

bool Bullet::amAllowedAlive()
{
	if (time > deadLifeTime) {
		return false;
	}
	return true;
}

Enemy::Enemy(Model* mObject, float deltaTime)
{
	object = mObject;
}

Enemy::~Enemy()
{
}

void Enemy::Tick(float deltaTime)
{
}