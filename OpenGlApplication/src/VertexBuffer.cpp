#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GL(glGenBuffers(1, &m_RendererId)); 
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId)); 
	GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); 
}

VertexBuffer::~VertexBuffer()
{
	GL(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const 
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::UnBind() const 
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
