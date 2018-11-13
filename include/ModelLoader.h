#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class ModelLoader
{


private:


	vector<float> m_indexedVertices;
	vector<unsigned int> m_faceIndices;

	vector<float> m_indexedNormals;
	vector<unsigned int> m_faceNormalsIndices;

	vector<float> m_indexedTextures;
	vector<unsigned int> m_faceTexturesIndices;




	vector<float> m_vertices;
	vector<float> m_normals;
	vector<float> m_textureUV;

	//duplicated


	

public:
	ModelLoader();
	~ModelLoader();


	void LoadModel(string modelName);


	vector<float>& GetVertices();
	vector<float>& ModelLoader::GetNormals();
	vector<float>& ModelLoader::GetTextures();


};

