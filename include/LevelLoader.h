#pragma once
#include "Win32OpenGL.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class LevelLoader
{


private:



	vector<string> loadModelName;
	vector<string> loadTextureName;
	vector<float> m_posList;
	vector<float> m_rotList;
	vector<float> m_scaleList;







public:
	LevelLoader();
	~LevelLoader();


	void LoadModel(string modelName);


	

	vector<string> GetModelName();
	vector<string> GetTextureName();

	vector<float> GetPosList();
	vector<float> GetRotList();
	vector<float> GetScaleList();

};

