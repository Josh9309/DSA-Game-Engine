#include "Model.h"



Model::Model()
{
	vertArr = 0;
	vertCount = 0;
	modelFile = "sphere.obj";
}


Model::~Model()
{
}

Model::Model(std::string modFile)
{
	vertArr = 0;
	vertCount = 0;
	modelFile = modFile;
}

bool Model::Buffer()
{
	std::vector<glm::vec3> locs =
	{
	};

	std::vector<unsigned int> locInds =
	{
	};

	std::vector<glm::vec2> uvs =
	{
	};

	std::vector<unsigned int> uvInds =
	{
	};

	std::vector<vec3> normals = {};
	std::vector<VertInd> vertInds = {};

	//read model file
	bool reading = true;

	while (reading)
	{
		std::ifstream inFile;
		std::string line;
		inFile.open(modelFile);

		if (inFile.is_open())
		{
			while (std::getline(inFile, line))
			{
				std::istringstream ss(line);

				std::string lineLabel;

				ss >> lineLabel;

				if (lineLabel == "v")
				{
					float  locsFloats[3];

					ss >> locsFloats[0];
					ss >> locsFloats[1];
					ss >> locsFloats[2];
					vec3 location1 = vec3(locsFloats[0], locsFloats[1], locsFloats[2]);
					locs.push_back(location1);
				}
				else if (lineLabel == "vt")
				{
					float uvFloats[2];

					ss >> uvFloats[0];
					ss >> uvFloats[1];

					glm::vec2 uv1 = glm::vec2(uvFloats[0], uvFloats[1]);
					uvs.push_back(uv1);
				}
				else if (lineLabel == "vn")
				{
					float  normsFloats[3];

					ss >> normsFloats[0];
					ss >> normsFloats[1];
					ss >> normsFloats[2];

					vec3 norm = vec3(normsFloats[0], normsFloats[1], normsFloats[2]);
					normals.push_back(norm);
				}
				else if (lineLabel == "f")
				{
					for (int i = 0; i < 3; i++)
					{
						unsigned int vertInd1;
						char slash1;
						unsigned int vertInd2;
						char slash2;
						unsigned int vertInd3;

						ss >> vertInd1;
						ss >> slash1;
						ss >> vertInd2;
						ss >> slash2;
						ss >> vertInd3;

						vertInd1 -= 1;
						vertInd2 -= 1;
						vertInd3 -= 1;

						VertInd vi = VertInd();
						vi.locInd = vertInd1;
						vi.normInd = vertInd3;
						vi.uvInd = vertInd2;
						vertInds.push_back(vi);
					}

				}
				else
				{
					//reading = false;
					//close file
				}
			}
			inFile.close();
			reading = false;
		}
	}






	vertCount = vertInds.size();

	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i].location = locs[vertInds[i].locInd];
		vertBufData[i].uv = uvs[vertInds[i].uvInd];
		vertBufData[i].normal = normals[vertInds[i].normInd];
	}



	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, //where to copy to
		sizeof(Vertex) * vertCount, //# bytes to copy
		&vertBufData[0], //where to copy from
		GL_STATIC_DRAW); //"hint to OpenGL

						 //Location
	glEnableVertexAttribArray(0); //Attribute index - 0
	glVertexAttribPointer(
		0, //Attribute index - 0 in this case
		3, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(Vertex), // stride (bytes per vertex)
		0); // offset to this attribute

			//UV 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, //Attribute index - 0 in this case
		2, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(Vertex), // stride (bytes per vertex)
		(void*)sizeof(glm::vec3)); // offset to this attribute
	return true;
}

bool Model::Buffer(std::string objFile)
{

	std::vector<glm::vec3> locs =
	{
	};

	std::vector<unsigned int> locInds =
	{
	};

	std::vector<glm::vec2> uvs =
	{
	};

	std::vector<unsigned int> uvInds =
	{
	};

	std::vector<vec3> normals = {};
	std::vector<VertInd> vertInds = {};

	//read model file
	bool reading = true;
	
	while(reading)
	{
		std::ifstream inFile;
		std::string line;
		inFile.open(objFile);

		if (inFile.is_open())
		{
			while (std::getline(inFile, line))
			{
				std::istringstream ss(line);

				std::string lineLabel;

				ss >> lineLabel;

				if (lineLabel == "v")
				{
					float  locsFloats[3];

					ss >> locsFloats[0];
					ss >> locsFloats[1];
					ss >> locsFloats[2];
					vec3 location1 = vec3(locsFloats[0], locsFloats[1], locsFloats[2]);
					locs.push_back(location1);
				}
				else if (lineLabel == "vt")
				{
					float uvFloats[2];

					ss >> uvFloats[0];
					ss >> uvFloats[1];

					glm::vec2 uv1 = glm::vec2(uvFloats[0], uvFloats[1]);
					uvs.push_back(uv1);
				}
				else if (lineLabel == "vn")
				{
					float  normsFloats[3];

					ss >> normsFloats[0];
					ss >> normsFloats[1];
					ss >> normsFloats[2];

					vec3 norm = vec3(normsFloats[0], normsFloats[1], normsFloats[2]);
					normals.push_back(norm);
				}
				else if (lineLabel == "f")
				{
					for (int i = 0; i < 3; i++)
					{
						unsigned int vertInd1;
						char slash1;
						unsigned int vertInd2;
						char slash2;
						unsigned int vertInd3;

						ss >> vertInd1;
						ss >> slash1;
						ss >> vertInd2;
						ss >> slash2;
						ss >> vertInd3;

						vertInd1 -= 1;
						vertInd2 -= 1;
						vertInd3 -= 1;

						VertInd vi = VertInd();
						vi.locInd = vertInd1;
						vi.normInd = vertInd3;
						vi.uvInd = vertInd2;
						vertInds.push_back(vi);
					}

				}
				else
				{
					//reading = false;
					//close file
				}
			}
			inFile.close();
			reading = false;
		}
	}
	
	
	
	
	
	
	vertCount = vertInds.size();

	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i].location = locs[vertInds[i].locInd];
		vertBufData[i].uv = uvs[vertInds[i].uvInd];
		vertBufData[i].normal = normals[vertInds[i].normInd];
	}



	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, //where to copy to
		sizeof(Vertex) * vertCount, //# bytes to copy
		&vertBufData[0], //where to copy from
		GL_STATIC_DRAW); //"hint to OpenGL

						 //Location
	glEnableVertexAttribArray(0); //Attribute index - 0
	glVertexAttribPointer(
		0, //Attribute index - 0 in this case
		3, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(Vertex), // stride (bytes per vertex)
		0); // offset to this attribute

			//UV 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, //Attribute index - 0 in this case
		2, //Number of components (x,y,z)
		GL_FLOAT, //Type of data
		GL_FALSE, //should we normalize the data
		sizeof(Vertex), // stride (bytes per vertex)
		(void*)sizeof(glm::vec3)); // offset to this attribute
	return true;
}

void Model::render()
{
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
