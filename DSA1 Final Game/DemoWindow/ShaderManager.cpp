#include "ShaderManager.h"

using std::ifstream;
using std::ios;

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

GLuint ShaderManager::getProgram() const
{

	return programIndex;
}

bool ShaderManager::loadShaders(const char * vertexFile, const char * fragmentFile)
{
	GLuint vertexshade = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vertexshade == 0)
	{
		return 0;
	}
	GLuint fragshade = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if(fragshade == 0)
	{
		return 0;
	}

	programIndex = glCreateProgram();
	glAttachShader(programIndex, vertexshade);
	glAttachShader(programIndex, fragshade);
	glLinkProgram(programIndex);

	GLint* linkstatus = new GLint();
	glGetProgramiv(programIndex, GL_LINK_STATUS, linkstatus);
	if(linkstatus == 0)
	{
		GLint* logLength = new GLint();
		glGetProgramiv(programIndex, GL_INFO_LOG_LENGTH, logLength);

		GLchar* log = new GLchar[*logLength];
		glGetProgramInfoLog(programIndex, *logLength, 0, log);

		std::cout << log << std::endl;

		glDeleteProgram(programIndex);

		delete log;
		delete logLength;
		delete linkstatus;

		return false;
	}
	else
	{
		delete linkstatus;
		return true;
	}
	
}

GLuint ShaderManager::loadShader(const char * file, GLenum shaderType)
{
	ifstream ifs(file, ios::binary);

	if (ifs.is_open())
	{
		ifs.seekg(0, std::ios::end);
		int length = (int)ifs.tellg();

		ifs.seekg(0, std::ios::beg);

		char* fileContents = new char[length + 1];

		ifs.read(fileContents, length);
		fileContents[length] = 0;

		ifs.close();

		GLuint shaderIndex = glCreateShader(shaderType);
		glShaderSource(shaderIndex, 1, &fileContents, 0);
		glCompileShader(shaderIndex);
		delete fileContents;
		
		GLint* result = new GLint();
		glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, result);

		if (*result != 0) 
		{
			delete result;
			return shaderIndex;
		}
		else
		{
			GLint* logLength = new GLint();
			glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, logLength);

			GLchar* log = new GLchar[*logLength];
			glGetShaderInfoLog(shaderIndex, *logLength, 0, log);

			std::cout << log << std::endl;

			glDeleteShader(shaderIndex);

			delete log;
			delete logLength;
			delete result;
			return 0;
		}
		
	}
	else
	{
		std::cout << "Error reading shader file" << std::endl;
		return 0;
	}

	
	return 0;
}
