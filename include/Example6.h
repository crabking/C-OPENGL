/*

Example6.h

*/
#pragma once
//  for M_PI constant
#define _USE_MATH_DEFINES
#include <cmath>

#include "Win32OpenGL.h"
#include "resource.h"
#include "ModelLoader.h"
#include "Log.h"
#include "Camera.h"
#include "Model.h"
#include "LevelLoader.h"

class Example6
{
	// open gl helper class
	Win32OpenGL m_win32OpenGL;

	float m_cameraX{ 0 };
	float m_cameraY{ 0 };
	float m_cameraZ{ 2.5f };

	// matrices
	//glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;


	Model ground;

	Model plane;
	Model plane1;
	Model plane2;
	Model plane3;
	Model plane4;

	Model radioTower;
	Model piperPlane;
	Model runway;
	Model Terminal;
	Model Hangar;
	Model Bump;
	Model House1;
	Model House2;
	Model House3;
	Model Barracks;
	Model SkyBox;
	Model Heli;
	Model Humve1;
	Model Humve2;
	Model Humve3;
	Model Humve4;
	Model Humve5;
	Model Humve6;
	Model Humve7;
	Model Humve8;
	Model Humve9;
	Model Humve10;
	Model Humve11;
	Model Humve12;

	LevelLoader level;

	vector<string> loadModelName;

	vector<string> loadTextureName;

	vector<Model*> modelList;

	vector<float> m_posList;
	vector<float> m_rotList;
	vector<float> m_scaleList;


	float m_aspectRatio;

	// and this is from the lighting
	glm::vec3 m_lightColourSpecular{ 1.0f,1.0f,1.0f };
	glm::vec3 m_lightColourDiffuse{ 0.8f, 0.8f, 0.8f };
	glm::vec3 m_lightColourAmbient{ 0.1f, 0.1f, 0.1f };
	glm::vec3 m_lightPosition{ 0.0f, 20.0f, 0.0f };

public:
	Example6();
	~Example6();

	void CreateGLWindow(HWND hWnd, RECT rect);
	void DestroyGLWindow();

	void PrepareToDraw();
	void Draw();

	void Update();

	void HandleInput(unsigned char virtualKeyCode);

	void HandleMouseInput(int xPosRelative, int yPosRelative);

	void Resize(HDC hdc, RECT rect);

	void ComputeProjectionMatrix();
	


	Camera m_camera;

};