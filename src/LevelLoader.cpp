#include "stdafx.h"
#include "LevelLoader.h"


LevelLoader::LevelLoader()
{
}


LevelLoader::~LevelLoader()
{
}

void LevelLoader::LoadModel(string LevelName)
{

	// code 

	std::fstream textfile(LevelName, std::ios_base::in);


	string line = "";

	if (textfile.is_open())
	{



		while (getline(textfile, line))
		{
			string s;
			istringstream iss(line);

			iss >> s; // read to first whitespace

			if (s == "t")
			{

				string textureText;

				while (iss >> textureText)
				{
					loadTextureName.push_back(textureText);
				}

			}

			if (s == "m")
			{

				string modelnameText;

				while (iss >> modelnameText)
				{
					loadModelName.push_back(modelnameText);
				}

			}
		


			if (s == "p") // position Y X Z
			{

				float positionIndex;

				while (iss >> positionIndex)
				{
					m_posList.push_back(positionIndex);
				}

			}
			if (s == "r") // Ro tation
			{

				float RotationIndex;

				while (iss >> RotationIndex)
				{
					m_rotList.push_back(RotationIndex);
				}

			}
			if (s == "s") // Scaling
			{

				float ScalingIndex;

				while (iss >> ScalingIndex)
				{
					m_scaleList.push_back(ScalingIndex);
				}

			}



		}
		// closes the modelfile
		textfile.close();

	}

	// TODO create the m_vertices vector
}



vector<string> LevelLoader::GetModelName()
{
	return loadModelName;
}

vector<string> LevelLoader::GetTextureName()
{
	return loadTextureName;
}

vector<float> LevelLoader::GetPosList()
{
	return m_posList;
}

vector<float> LevelLoader::GetRotList()
{
	return m_rotList;
}

vector<float> LevelLoader::GetScaleList()
{
	return m_scaleList;
}
