#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GL(glGenVertexArrays(1, &m_RendererId)); 
}

VertexArray::~VertexArray()
{
	GL(glDeleteVertexArrays(1, &m_RendererId)); 
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind(); 
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0; 

	for (int i = 0; i < elements.size(); i++)
	{
		auto &element = elements[i];
		GL(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, element.count, element.type,  element.normalized, layout.GetStride(), (const void *)offset); 

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GL(glBindVertexArray(m_RendererId)); 
}

void VertexArray::UnBind() const
{
	GL(glBindVertexArray(m_RendererId)); 
}
