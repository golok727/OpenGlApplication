#include "Renderer.h"
#include <iostream>


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{

		std::cerr << "OpenGLError: (" << error << ") "
			<< "\nAt Function: " << function << "\nAt File: " << file << "\nAt Line: " << line << "\n*-----End-----*\n";
		return false;
	}


	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind(); 

	GL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
	GL(glClear(GL_COLOR_BUFFER_BIT))
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
	GL(glClearColor(r, g, b, a))
}
