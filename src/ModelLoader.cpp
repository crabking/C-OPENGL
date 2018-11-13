#include "stdafx.h"
#include "ModelLoader.h"


ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

void ModelLoader::LoadModel(string modelName)
{

	// code 

	std::fstream modelfile(modelName, std::ios_base::in);


	string line = "";

	


	//an if statement to check the file opened correctly
	if (modelfile.is_open())
	{

	
		//Read the file in to a stl string one line at a time in a while loop (getline returns false for eof)
		while (getline(modelfile, line))
		{
			string s;
			istringstream iss(line);

			iss >> s; // read to first whitespace

			if (s == "f")
			{

				// process face line

				unsigned int faceIndex;

				while (iss >> faceIndex)
				{
					faceIndex--;   // change to zero based indices
					// TODO store this in face indices

					m_faceIndices.push_back(faceIndex);


					// now look for a slash

					static const int forwardSlash = 0x2F;
					int lookAhead = iss.peek();  	// peek character
					if (lookAhead == forwardSlash)    // "/"
					{
						iss.get();		// moves past the slash

						lookAhead = iss.peek();  	// peek character
						if (lookAhead == forwardSlash)    // "/"
						{
							// here its  f 56//78 ... just normals

							iss.get();		// moves past the slash

							unsigned int normalIndex;

							iss >> normalIndex;
							normalIndex--;
							m_faceNormalsIndices.push_back(normalIndex);


						}
						else
						{


							//            v  t  n
							// here its f 45/32/67
							//               ^
							
							

							unsigned int textureIndex;

							iss >> textureIndex;
							textureIndex--;
							m_faceTexturesIndices.push_back(textureIndex);

							iss.get();		// moves past the slash

							unsigned int normalIndex;

							iss >> normalIndex;
							normalIndex--;
							m_faceNormalsIndices.push_back(normalIndex);

						}



					}


				}

			}
			else if (s == "v")
			{
				// TODO process indexed vertices using floats


				float indexedVertex;

				while (iss >> indexedVertex)
				{

								   // TODO store this in face indices

					m_indexedVertices.push_back(indexedVertex);
				}

			}
			else if (s == "vn")
			{
				// TODO process indexed vertices using floats


				float indexedVertexNormal;

				while (iss >> indexedVertexNormal)
				{

					// TODO store this in face indices

					m_indexedNormals.push_back(indexedVertexNormal);
				}

			}
			else if (s == "vt")
			{
				// TODO process indexed vertices using floats


				float indexedVertexTextures;

				while (iss >> indexedVertexTextures)
				{

					// TODO store this in face indices

					m_indexedTextures.push_back(indexedVertexTextures);
				}

			}



		}
		// closes the modelfile
		modelfile.close();

	}
	
	// TODO create the m_vertices vector


	for (int i = 0; i < m_faceIndices.size(); i++)
	{

		// reading faces
		// look up how to use a stl::vector - reading values
		unsigned int faceIndex = m_faceIndices[i];

		// get the place in the vindexedVerticesvector

		unsigned int placeInIndexedVerticesVector = faceIndex * 3;

		for (int j = 0; j < 3; j++)
		{
			// get an indexed vertex (using [place.... + j]

			float value = m_indexedVertices[placeInIndexedVerticesVector + j];

			// push back onto m_vertices vector
			m_vertices.push_back(value);


		}
	}
	for (int i = 0; i < m_faceNormalsIndices.size(); i++)
	{


		// reading normals
		// look up how to use a stl::vector - reading values
		unsigned int normalIndex = m_faceNormalsIndices[i];

		// get the place in the vindexedVerticesvector
		unsigned int placeInIndexedNormals = normalIndex * 3;

		for (int j = 0; j < 3; j++)
		{
			// get an indexed vertex (using [place.... + j]

			float value = m_indexedNormals[placeInIndexedNormals + j];

			// push back onto m_vertices vector
			m_normals.push_back(value);

		}
	}

	for (int i = 0; i < m_faceTexturesIndices.size(); i++)
	{


		// reading textures
		// look up how to use a stl::vector - reading values
		unsigned int normalTextures = m_faceTexturesIndices[i];

		// get the place in the vindexedVerticesvector
		unsigned int placeInIndexedTextures = normalTextures * 2;

		for (int j = 0; j < 2; j++)
		{
			// get an indexed texture (using [place.... + j]

			float value = m_indexedTextures[placeInIndexedTextures + j];

			// push back onto m_vertices vector
			m_textureUV.push_back(value);


		}


	}




}

vector<float>& ModelLoader::GetVertices()
{
	return m_vertices;
}

vector<float>& ModelLoader::GetNormals()
{
	return m_normals;
}

vector<float>& ModelLoader::GetTextures()
{
	return m_textureUV;
}

//duplicated
