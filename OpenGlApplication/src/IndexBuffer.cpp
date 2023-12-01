#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint)); 
	GL(glGenBuffers(1, &m_RendererId));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GL(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const 
{
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}


void IndexBuffer::UnBind() const 
{
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
