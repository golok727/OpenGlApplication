#pragma once
#include <iostream>

class ShaderSource
{
public:
    std::string vertex;
    std::string fragment;
    ShaderSource() = default;
    ShaderSource(const char* filepath);

private: 
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };
    void parseFile(const char* filepath);
};


