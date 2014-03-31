#include <ObjLoader.h>
#include <FileReader.h>

using namespace NoHope;

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

bool ObjLoader::loadOBJ(const char* path, std::vector<Vec3> & out_vertices,
									      std::vector<Vec2> & out_uvs,
									      std::vector<Vec3> & out_normals,
										  std::vector<GLushort>& out_indices)
{
	openFile(path);
	parseData();

	for(unsigned int i=0; i<vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		Vec3 vertex = temp_vertices[vertexIndex-1];
		out_vertices.push_back(vertex);
	}

	for(unsigned int i=0; i<uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		Vec2 uv = temp_uvs[uvIndex-1];
		out_uvs.push_back(uv);
	}

	for(unsigned int i=0; i<normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		Vec3 normal = temp_normals[normalIndex-1];
		out_normals.push_back(normal);
	}


	return 1;
}

void ObjLoader::openFile(const char* path)
{
	FileReader* FR = new FileReader(path);
	lenght = FR->length();
	buff = (char*) malloc(lenght+1);
	FR->read(lenght, buff);
	delete FR;
}

void ObjLoader::parseData()
{
	char character;
	std::string token;
	size_t i = 0;
	for(i; i < lenght; i++)
	{
		character = (char)buff[i];
		switch(character)
		{
			case '\t':
			case '\n':
			case '\r':
			case ' ':
			case '/':
				if(!token.empty())
				{
					_tokens.push_back(token);
					token = std::string();
				}
				break;
			case '#':
				while(character != '\n')
				{
					i++;
					character = (char)buff[i];
				}
				break;
			default:
				token.push_back(character);
				break;
		}
	}

	if(!token.empty())
		_tokens.push_back(token);

	for(size_t i = 0; i < _tokens.size(); ++i)
	{
		if(_tokens[i] == "v")
		{
			addVertices(i + 1);
			i += 3;
		}
		else if(_tokens[i] == "vt")
		{
			addUvs(i + 1);
			i += 2;
		}
		else if(_tokens[i] == "vn")
		{
			addNormals(i + 1);
			i += 3;
		}
		else if(_tokens[i] == "f")
		{
			addIndices(i + 1);
			i += 9;
		}
	}	
}

void ObjLoader::addVertices(const size_t bufferIndex)
{
	Vec3 vertex;
	vertex.x = (float)atof(_tokens[bufferIndex].c_str());
	vertex.y = (float)atof(_tokens[bufferIndex+1].c_str());
	vertex.z = (float)atof(_tokens[bufferIndex+2].c_str());
	temp_vertices.push_back(vertex);
}

void ObjLoader::addUvs(const size_t bufferIndex)
{
	Vec2 uv;
	uv.x = (float)atof(_tokens[bufferIndex].c_str());
	uv.y = (float)atof(_tokens[bufferIndex+1].c_str());
	temp_uvs.push_back(uv);
}

void ObjLoader::addNormals(const size_t bufferIndex)
{
	Vec3 normal;
	normal.x = (float)atof(_tokens[bufferIndex].c_str());
	normal.y = (float)atof(_tokens[bufferIndex+1].c_str());
	normal.z = (float)atof(_tokens[bufferIndex+2].c_str());
	temp_normals.push_back(normal);
}

void ObjLoader::addIndices(const size_t bufferIndex)
{
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

	vertexIndex[0]	= atof(_tokens[bufferIndex].c_str());
	uvIndex[0]		= atof(_tokens[bufferIndex+1].c_str());
	normalIndex[0]	= atof(_tokens[bufferIndex+2].c_str());
	vertexIndex[1]	= atof(_tokens[bufferIndex+3].c_str());
	uvIndex[1]		= atof(_tokens[bufferIndex+4].c_str());
	normalIndex[1]	= atof(_tokens[bufferIndex+5].c_str());
	vertexIndex[2]	= atof(_tokens[bufferIndex+6].c_str());
	uvIndex[2]		= atof(_tokens[bufferIndex+7].c_str());
	normalIndex[2]	= atof(_tokens[bufferIndex+8].c_str());

	vertexIndices.push_back(vertexIndex[0]);
	vertexIndices.push_back(vertexIndex[1]);
	vertexIndices.push_back(vertexIndex[2]);
	uvIndices	 .push_back(uvIndex[0]);
	uvIndices	 .push_back(uvIndex[1]);
	uvIndices	 .push_back(uvIndex[2]);
	normalIndices.push_back(normalIndex[0]);
	normalIndices.push_back(normalIndex[1]);
	normalIndices.push_back(normalIndex[2]);
}