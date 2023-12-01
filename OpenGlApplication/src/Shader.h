#pragma once
#include "ShaderSource.h"	
#include <unordered_map>
#include "glm/glm.hpp"
class Shader
{
public: 
	Shader(const char *filepath);
	~Shader();

	void Bind() const; 
	void UnBind() const; 
	void SetUniform1i(const std::string& name, int value); 

	void SetUnifrom1f(const std::string& name, float v0);
	void SetUnifrom2f(const std::string& name, float v0, float v1);
	void SetUnifrom3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3); 
	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
private: 
	void createShader(); 
	unsigned int compileShader(unsigned int type, std::string& source); 
	int getUniformLocation(const std::string& name);

	unsigned int m_Program; 
	ShaderSource m_ShaderSource; 
	std::unordered_map<std::string, int> m_UniformLocationsCache;
};

