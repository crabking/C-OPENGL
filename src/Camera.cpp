#pragma once
#include "stdafx.h"
#include "Camera.h"
 



void Camera::ComputeViewMatrixUsingLookAt()
{
	//	float eyeX = m_x;
	//	float eyeY = m_y;
	//	float eyeZ = m_z;

	//	float centerX = m_x + m_directionX;
	//	float centerY = m_y + m_directionY;
	//	float centerZ = m_z + m_directionZ;

	float upX = 0;
	float upY = 1;
	float upZ = 0;

	// vec3 forward = vec3(centerX - eyeX, centerY - eyeY, centerZ - eyeZ); - simplified now...
	// we already store centreX - eyeX as m_directionX
	glm::vec3 forward = glm::vec3(m_directionX, m_directionY, m_directionZ);
	glm::vec3 up = glm::vec3(upX, upY, upZ);
	glm::vec3 forwardNormalised = glm::normalize(forward);		//normalize(forward);
	glm::vec3 side = glm::vec3(forwardNormalised);				// copy cross(forward, up, side);
	side = glm::cross(side, up);
	glm::vec3 sideNormalised = glm::normalize(side);				//normalize(side);
	up = glm::vec3(sideNormalised);
	up = glm::cross(up, forwardNormalised);					// no need to normalise as generated from 2 normalised vectors of unit length
															// now we build the matrix... (column major)
															// this is the transpose for the V matrix as  Vinverse == VT for rotation matrices

															// row 0
	m_viewMatrix[0][0] = sideNormalised[0];				//0
	m_viewMatrix[1][0] = sideNormalised[1];				//4
	m_viewMatrix[2][0] = sideNormalised[2];				//8
	m_viewMatrix[3][0] = 0;								//12
														// row 1
	m_viewMatrix[0][1] = up[0];							//1
	m_viewMatrix[1][1] = up[1];							//5
	m_viewMatrix[2][1] = up[2];							//9
	m_viewMatrix[3][1] = 0;								//13
														// row 2
	m_viewMatrix[0][2] = -(forwardNormalised[0]);		//2
	m_viewMatrix[1][2] = -(forwardNormalised[1]);		//6
	m_viewMatrix[2][2] = -(forwardNormalised[2]);		//10
	m_viewMatrix[3][2] = 0;								//14
														// row 3
	m_viewMatrix[0][3] = 0;								//3
	m_viewMatrix[1][3] = 0;								//7
	m_viewMatrix[2][3] = 0;								//11
	m_viewMatrix[3][3] = 1;								//15
														// now apply translation to camera position

	glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(-m_x, -m_y, -m_z));

	m_viewMatrix = m_viewMatrix * cameraTranslation;  // pre or post multiply - - definitely POST!!!
}

void Camera::ComputeDirectionVector()
{
	float angleYZRadians = 3.14156f * m_angleYZ / 180.0f;

	m_directionY = sin(angleYZRadians);

	float m_other = cos(angleYZRadians);

	float angleXZRadians = 3.14156f * m_angleXZ / 180.0f;
	m_directionX = m_other * sin(angleXZRadians);
	m_directionZ = m_other * -cos(angleXZRadians);
}

void Camera::UpdateCameraPosition(float distanceMoved)
{
	// later might use matrices to calculate this....
	// for now use angle in xz and stay on ground....
	// if moved update position

	m_x += distanceMoved * m_directionX;
	m_y += distanceMoved * m_directionY;
	m_z += distanceMoved * m_directionZ;
}
void Camera::SetViewMatrix(GLuint program)
{
		Win32OpenGL::SendUniformMatrixToShader(program, m_viewMatrix, "view_matrix");
}

void Camera::HandleInput(unsigned char virtualKeyCode)
{
		float distanceMoved = 0.0f;

		float angleStep = 2.5f;

		if (virtualKeyCode == VK_LEFT)
		{
			m_angleXZ -= angleStep;
		}
		else if (virtualKeyCode == VK_RIGHT)
		{
			m_angleXZ += angleStep;
		}
		else if (virtualKeyCode == VK_UP)
		{
			distanceMoved = 1.0f;
		}
		else if (virtualKeyCode == VK_DOWN)
		{
			distanceMoved = -1.0f;
		}
		else if (virtualKeyCode == VK_PRIOR)	//PAGEUP
		{
			m_angleYZ += angleStep;
		}
		else if (virtualKeyCode == VK_NEXT)	//PAGEDOWN
		{
			m_angleYZ -= angleStep;
		}
		else if (virtualKeyCode == VK_ADD)
		{
			m_y += 1.0f;
		}
		else if (virtualKeyCode == VK_SUBTRACT)
		{
			m_y -= 1.0f;
		}
		// MORE KEY RESPONSES HERE
		// move camera and update view matrix

		ComputeDirectionVector();

		if (distanceMoved != 0.0f)
		{
			UpdateCameraPosition(distanceMoved);
		}
		ComputeViewMatrixUsingLookAt();
}

void Camera::HandleMouseInput(int xPos, int yPos)
{
	const float inverseSensitivity = 10;
	m_angleXZ += (float)xPos / inverseSensitivity;
	if (m_angleYZ <= 89 && m_angleYZ >= -89)
	{
		m_angleYZ += (float)yPos / -inverseSensitivity;
	}
	else if (m_angleYZ >= 89)
	{
		m_angleYZ = m_angleYZ - 2;
	}
	else if (m_angleYZ <= -89)
	{
		m_angleYZ = m_angleYZ + 2;
	}

	

	ComputeDirectionVector();
	ComputeViewMatrixUsingLookAt();

}

float Camera::GetXcampos()
{
	m_camXpos = m_x;
	return m_camXpos;

}

float Camera::GetYcampos()
{
	m_camYpos = m_y;
	return m_camYpos;

}

float Camera::GetZcampos()
{
	m_camZpos = m_z;
	return m_camZpos;

}
