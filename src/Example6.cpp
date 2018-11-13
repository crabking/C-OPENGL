#include "stdafx.h"
#include "Example6.h"
#include "ModelLoader.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "Model.h"
#include "LevelLoader.h"


Example6::Example6()
{
	// we don't use RAII currently so no action in constructor
}

Example6::~Example6()
{
}

void Example6::CreateGLWindow(HWND hWnd, RECT rect)
{
	m_win32OpenGL.CreateGLContext(hWnd);	// may throw an exception!!! // MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
	m_aspectRatio = static_cast<float>(rect.right / rect.bottom);
	m_win32OpenGL.CreateShadersAndProgram("phongTextureScaled2");
	m_win32OpenGL.SetupDisplay();
	m_win32OpenGL.GetError();			// check all ok
}

void Example6::DestroyGLWindow()
{
	m_win32OpenGL.TearDownGLContext();
}


void Example6::PrepareToDraw()
{
	ComputeProjectionMatrix();
	m_camera.ComputeDirectionVector();
	m_camera.ComputeViewMatrixUsingLookAt();

	// send the matrices to the shader
	GLuint program = m_win32OpenGL.GetShaderProgram();
	m_camera.SetViewMatrix(program);


	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightPosition, "light_position_world");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourSpecular, "light_colour_specular");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourDiffuse, "light_colour_diffuse");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourAmbient, "light_colour_ambient");

	/*
	//draws groundfloor
	Bump.PrepareToDraw("Textures\\TextureConcrete.bmp", "Models\\Bump.obj");
	ground.PrepareToDraw("Textures\\SeamlessSand.bmp", "Models\\Terrain.obj");
	runway.PrepareToDraw("Textures\\Road.bmp", "Models\\Road.obj");
	// draws planes
	plane.PrepareToDraw("Textures\\P51.bmp", "Models\\P51.obj");
	plane1.PrepareToDraw("Textures\\P51.bmp", "Models\\P51.obj");
	plane2.PrepareToDraw("Textures\\P51.bmp", "Models\\P51.obj");
	plane3.PrepareToDraw("Textures\\P51.bmp", "Models\\P51.obj");
	plane4.PrepareToDraw("Textures\\P51.bmp", "Models\\P51.obj");

	radioTower.PrepareToDraw("Textures\\TriangulatedTexture.bmp", "Models\\TriangulatedTexture.obj");
	Terminal.PrepareToDraw("Textures\\TerminalTriangulatedNew.bmp", "Models\\TerminalTriangulatedNew.obj");
	Hangar.PrepareToDraw("Textures\\Hangar.bmp", "Models\\Hangar.obj");

	House1.PrepareToDraw("Textures\\House.bmp", "Models\\House.obj");
	House2.PrepareToDraw("Textures\\House.bmp", "Models\\House.obj");
	House3.PrepareToDraw("Textures\\House.bmp", "Models\\House.obj");

	Barracks.PrepareToDraw("Textures\\Barracks.bmp", "Models\\Barracks.obj");

	SkyBox.PrepareToDraw("Textures\\SkyBox.bmp", "Models\\SkyBox.obj");
	Heli.PrepareToDraw("Textures\\m24.bmp", "Models\\m24.obj");

	Humve1.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve2.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve3.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve4.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve5.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve6.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve7.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve8.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve9.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve10.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve11.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");
	Humve12.PrepareToDraw("Textures\\humve.bmp", "Models\\humve.obj");*/


	SkyBox.PrepareToDraw("Textures\\SkyBox.bmp", "Models\\SkyBox.obj");

	//opening level 1 textfil
	level.LoadModel("Level1.txt");

	// passing over al the data
	loadModelName = level.GetModelName();
	loadTextureName = level.GetTextureName();
	m_posList = level.GetPosList();
	m_rotList = level.GetRotList();
	m_scaleList = level.GetScaleList();

	for (int i = 0; i < loadModelName.size(); i++)
	{

		modelList.push_back(new Model());
		modelList[i]->PrepareToDraw( loadTextureName[i], loadModelName[i]);
	}

	//piperPlane.PrepareToDraw("Textures\\piper_pa18TriTA4.bmp", "Models\\piper_pa18TriTA4.obj");



	m_win32OpenGL.GetError();			// check all ok
	Win32OpenGL::GetError();
}

void Example6::Draw()
{
	m_win32OpenGL.ClearGLDisplay();
	GLuint program = m_win32OpenGL.GetShaderProgram();

	for (int i = 0; i < modelList.size(); i++)
	{

		modelList[i]->Draw(program, m_posList[i*3], m_posList[i*3+1], m_posList[i*3+2], m_rotList[i*3], m_rotList[i*3+1], m_rotList[i*3+2], m_scaleList[i]);
	}

	
	/*
	Bump.Draw(program, 0.0f, -30.0f, -10.0f, 0, 0, 0, 2.0f);
	ground.Draw(program, 0.0f, 0.0f, 0.0f, 0, -90, 0, 4.0f);
	runway.Draw(program, 0.02f, 0.0f, 0.0f, 0, 0, 0, 0.25f);

	plane.Draw(program, 0.02f, 10.0f, 0.0f, 0, 90.f, 0, 0.25f);
	plane1.Draw(program, 0.01f, -18.0f, -27.0f, 0, 0, 0, 0.20f);
	plane2.Draw(program, 0.01f, -14.0f, -27.0f, 0, 0, 0, 0.20f);
	plane3.Draw(program, 0.01f, -10.0f, -27.0f, 0, 0, 0, 0.20f);
	plane4.Draw(program, 0.01f, -6.0f, -27.0f, 0, 0, 0, 0.20f);

	radioTower.Draw(program, 0.0f, -25.0f, -30.0f, 0, 0, 0, 0.20f);
	Terminal.Draw(program, 0.0f, 2.0f, -27.0f, 0, -90, 0, 0.5f);

	Hangar.Draw(program, 0.01f, -18.0f, -27.0f, 0, 0, 0, 0.20f);
	Hangar.Draw(program, 0.01f, -14.0f, -27.0f, 0, 0, 0, 0.20f);
	Hangar.Draw(program, 0.01f, -10.0f, -27.0f, 0, 0, 0, 0.20f);
	Hangar.Draw(program, 0.01f, -6.0f, -27.0f, 0, 0, 0, 0.20f);

	House1.Draw(program, 0.01f, 10.0f, -30.0f, 0, -90, 0, 0.5f);
	House2.Draw(program, 0.01f, 14.0f, -30.0f, 0, -90, 0, 0.5f);
	House3.Draw(program, 0.01f, 18.0f, -30.0f, 0, -90, 0, 0.5f);*/

	//Barracks.Draw(program, 0.1f, 35.0f, -24.0f, 0, 90, 0, 0.7f); // NEED TO FLIP THE GROUDN
	//Barracks.Draw(program, 0.05f, 55.0f, -25.0f, 0, 90, 0, 0.7f);


	// not loading in by file
	SkyBox.Draw(program, m_camera.GetYcampos(),m_camera.GetXcampos(),m_camera.GetZcampos(), 0, 0, 0, 30.0f);

	/*
	Heli.Draw(program, 0.02f, -15.0f, -18.0f, 0, 90.f, 0, 0.020f);

	Humve1.Draw(program, 0.3f, 42.0f, -10.0f, 0, 0, 0, 0.015f);
	Humve2.Draw(program, 0.3f, 40.0f, -10.0f, 0, 0, 0, 0.015f);
	Humve3.Draw(program, 0.3f, 38.0f, -10.0f, 0, 0, 0, 0.015f);
	Humve4.Draw(program, 0.3f, 36.0f, -10.0f, 0, 0, 0, 0.015f);
	Humve5.Draw(program, 0.3f, 34.0f, -10.0f, 0, 0, 0, 0.015f);
	Humve6.Draw(program, 0.3f, 32.0f, -10.0f, 0, 0, 0, 0.015f);											 
	Humve7.Draw(program, 0.3f, 42.0f, -13.0f, 0, 0, 0, 0.015f);
	Humve8.Draw(program, 0.3f, 40.0f, -13.0f, 0, 0, 0, 0.015f);
	Humve9.Draw(program, 0.3f, 38.0f, -13.0f, 0, 0, 0, 0.015f);
	Humve10.Draw(program, 0.3f, 36.0f, -13.0f, 0, 0, 0, 0.015f);
	Humve11.Draw(program, 0.3f, 34.0f, -13.0f, 0, 0, 0, 0.015f);
	Humve12.Draw(program, 0.3f, 32.0f, -13.0f, 0, 0, 0, 0.015f);*/
														 
	// unbind
	glBindTexture(GL_TEXTURE_2D, NULL);

	m_win32OpenGL.FinishedDrawing();

}

void Example6::Update()
{
	while (ShowCursor(false) >= 0);
	// we tumble the cube to see all the faces.
	//m_yAngle += 1.0f;
	//m_xAngle += 0.2f;
}

void Example6::HandleInput(unsigned char virtualKeyCode)
{
	m_camera.HandleInput(virtualKeyCode);
	GLuint program = m_win32OpenGL.GetShaderProgram();
	m_camera.SetViewMatrix(program);
}

void Example6::HandleMouseInput(int xPosRelative, int yPosRelative) // MOUSe MOVEMENT
{
	// probably need to pass the data to the camera
	m_camera.HandleMouseInput(xPosRelative, yPosRelative);
	GLuint program = m_win32OpenGL.GetShaderProgram();
	m_camera.SetViewMatrix(program);
}


void Example6::Resize(HDC hdc, RECT rect)
{
	// if the display is resized then OpenGL needs to know about the apect ratio
	// to compute the correct projection matrix
	m_win32OpenGL.Reshape(hdc, rect.right, rect.bottom);
	m_aspectRatio = (float)rect.right / rect.bottom;
	ComputeProjectionMatrix();
	GLuint program = m_win32OpenGL.GetShaderProgram();
	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");
}

void Example6::ComputeProjectionMatrix()
{
	// we will look at this later in the course
	// in Modern OpenGL we must supply a projection matrix
	const float oneDegreeInRadians = static_cast<float>((2.0 * M_PI) / 360.0);
	//ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

	// input variables
	float zNear = 0.1f;		// clipping plane
	float zFar = 500.0f;	// clipping plane
	float fov = static_cast<float>(67.0f * oneDegreeInRadians); // convert 67 degrees to radians

	float range = tan(fov * 0.5f) * zNear;
	float Sx = (2.0f * zNear) / (range * m_aspectRatio + range * m_aspectRatio);
	float Sy = zNear / range;
	float Sz = -(zFar + zNear) / (zFar - zNear);
	float Pz = -(2.0f * zFar * zNear) / (zFar - zNear);
	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};
	m_projectionMatrix = glm::make_mat4(proj_mat);
}
