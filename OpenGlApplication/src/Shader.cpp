#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const char* filepath)
{
	ShaderSource sSrc(filepath);
	m_ShaderSource = sSrc;

	createShader(); 
}

Shader::~Shader()
{
	GL(glDeleteProgram(m_Program)); 
}

void Shader::Bind() const 
{
	GL(glUseProgram(m_Program)); 
}

void Shader::UnBind() const 
{
	GL(glUseProgram(0)); 
}

void Shader::SetUniformMat4(const std::string &name, const glm::mat4 &matrix )
{
	GL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GL(glUniform1i(getUniformLocation(name), value)); 
}

void Shader::SetUnifrom1f(const std::string& name, float v0)
{
	GL(glUniform1f(getUniformLocation(name), v0));
}

void Shader::SetUnifrom2f(const std::string& name, float v0, float v1)
{
	GL(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::SetUnifrom3f(const std::string& name, float v0, float v1, float v2)
{
	GL(glUniform3f(getUniformLocation(name), v0, v1, v2));
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::createShader()
{
	GL(m_Program = glCreateProgram());
	GL(unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, m_ShaderSource.vertex));
	GL(unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, m_ShaderSource.fragment));

	GL(glAttachShader(m_Program, vertexShader));
	GL(glAttachShader(m_Program, fragmentShader));
	GL(glLinkProgram(m_Program));
	GL(glValidateProgram(m_Program));

	GL(glDeleteShader(vertexShader));
	GL(glDeleteShader(fragmentShader));

}

unsigned int Shader::compileShader(unsigned int type, std::string &source)
{
	GL(unsigned int shader = glCreateShader(type));
	const char* src = source.c_str();

	GL(glShaderSource(shader, 1, &src, nullptr));
	GL(glCompileShader(shader));

	int isSucess;
	GL(glGetShaderiv(shader, GL_COMPILE_STATUS, &isSucess));
	if (isSucess == GL_FALSE)
	{
		int logLength;
		GL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength));

		char* message = (char*)_malloca(sizeof(char) * logLength);
		GL(glGetShaderInfoLog(shader, logLength, &logLength, message));
		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << " shader."
			<< "\nError: \n" << message << "\n*-------------End-------------*\n\n";

		GL(glDeleteShader(shader));
		return 0;
	}

	return shader;
}

int Shader::getUniformLocation(const std::string& name)
{
	auto cache = m_UniformLocationsCache.find(name);
	if (cache != m_UniformLocationsCache.end())
		return cache->second;
	
	GL(int location = glGetUniformLocation(m_Program, name.c_str()));
	ASSERT(location != -1);

	m_UniformLocationsCache[name] = location;

	return location; 
}
