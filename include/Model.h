#pragma once
#include "Win32OpenGL.h"


class Model
{


	// model data
	vector<float> m_vertices;			// we can't initialise at compile time
	vector<float> m_normals;
	vector<float> m_textureUV;

	// ids for vao and vbo's
	GLuint m_vao;
	GLuint m_vboVertices;
	GLuint m_vboNormals;
	GLuint m_vboTextures;


	//new for textures - the id for the actual bitmap data
	GLuint m_textureDataID;

	glm::mat4 m_modelMatrix;

	// this is same as before
	float m_xAngle{ 0.0f };
	float m_yAngle{ 0.0f };
	float m_zAngle{ 0.0f };
	float m_scaler{ 0.0f };

public:
	Model();
	~Model();

	void PrepareToDraw(string bmp, string obj);

	void Draw(GLuint program, float yPos, float xPos, float zPos, float xRot, float yRot, float zRot, float Scale);

	void CreateTextureID(string fileName, GLuint& id);

};

