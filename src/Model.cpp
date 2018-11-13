#include "stdafx.h"
#include "Model.h"
#include "ModelLoader.h"
#include "TextureLoader.h"


Model::Model()
{
}


Model::~Model()
{
}



void Model::PrepareToDraw(string bmp, string obj)
{

	//alternatively try these cruder filters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	CreateTextureID(bmp, m_textureDataID);

	ModelLoader modelLoader; // modelloader object

	modelLoader.LoadModel(obj);


	// you will need to ensure your model conatins UV data and that the code reads and expands the textureUV values
	m_vertices = modelLoader.GetVertices();
	m_normals = modelLoader.GetNormals();
	m_textureUV = modelLoader.GetTextures();

	//GLuint vboVertices;
	glGenBuffers(1, &m_vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);

	//GLuint vboNormals;
	glGenBuffers(1, &m_vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboNormals);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(GLfloat), &m_normals[0], GL_STATIC_DRAW);

	//GLuint vboTextures;
	glGenBuffers(1, &m_vboTextures);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboTextures);
	glBufferData(GL_ARRAY_BUFFER, m_textureUV.size() * sizeof(GLfloat), &m_textureUV[0], GL_STATIC_DRAW);

	//GLuint vao;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboNormals);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboTextures);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);


	// vertices are element 0 in VAO
	// normals element 1
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


}

void Model::Draw(GLuint program, float yPos, float xPos, float zPos, float xRot, float yRot, float zRot, float Scale)
{



	glBindTexture(GL_TEXTURE_2D, m_textureDataID);
	m_modelMatrix = glm::mat4(1.0f);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(xPos, yPos, zPos));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(xRot), glm::vec3(1.0f, 0, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(yRot), glm::vec3(0, 1.0f, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(zRot), glm::vec3(0, 0, 1.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(Scale));
	Win32OpenGL::SendUniformMatrixToShader(program, m_modelMatrix, "model_matrix");



	glBindVertexArray(m_vao);		// select first VAO
	GLuint numberOfElements = m_vertices.size() / 3;
	glDrawArrays(GL_TRIANGLES, 0, numberOfElements);
	//glBindVertexArray(NULL);




}


void Model::CreateTextureID(string fileName, GLuint& id)
{
	TextureLoader::LoadBMP(fileName, id, true);
}
