#include <fstream>
#include <sstream>
#include <string>
#include "ShaderSource.h"


ShaderSource::ShaderSource(const char* filepath)
{
	parseFile(filepath);
}

void ShaderSource::parseFile(const char* filepath)
{
    std::ifstream shaderFile(filepath);
    if (!shaderFile.is_open()) {
        std::cerr << "Error reading shader source file: " << filepath << ". Please make sure that this file exists.\n";
        throw std::runtime_error("Failed to open shader source file.");
    }
    std::string line;
    std::stringstream ss[2];
    ShaderType currentType = ShaderType::NONE;

    while (getline(shaderFile, line))
    {
        if (line.empty())
            continue;

        // Check the current Shader Type;
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                currentType = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                currentType = ShaderType::FRAGMENT;
            continue;
        }

        if (currentType != ShaderType::NONE)
            ss[(int) currentType] << line << "\n";
    }
    vertex = ss[(int)ShaderType::VERTEX].str();
    fragment = ss[(int)ShaderType::FRAGMENT].str();
}
