#pragma once
//#include "stdafx.h"
#include "Win32OpenGL.h" 

class Camera
{

private:
	const float startX = 0;
	const float startY = 20.5f;
	const float startZ = 10.f;

	float m_x{ startX };
	float m_y{ startY };
	float m_z{ startZ };


	float m_angleXY{ 0 };
	float m_angleXZ{ 0 };
	float m_angleYZ{ 0 };

	float m_directionX{ 0 };
	float m_directionY{ 0 };
	float m_directionZ{ 0 };

	float m_camXpos;
	float m_camYpos;
	float m_camZpos;


	glm::mat4 m_viewMatrix;

	glm::vec3 m_LookAt{ 0.0f,0.0f,0.0f };

public:
	void ComputeViewMatrixUsingLookAt();
	void ComputeDirectionVector();
	void UpdateCameraPosition(float distanceMoved);
	void SetViewMatrix(GLuint program);
	void HandleInput(unsigned char virtualKeyCode);
	void HandleMouseInput(int xPos, int yPos);

	float GetXcampos();
	float GetYcampos();
	float GetZcampos();
	

};
