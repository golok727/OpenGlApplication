#pragma once
class IndexBuffer
{
public: 
	IndexBuffer(const unsigned int* data, unsigned int count); 
	~IndexBuffer();
	void Bind() const; 
	void UnBind() const; 
	inline int GetCount() const { return m_Count; }
private: 
	unsigned int m_RendererId; 
	int m_Count; 
};

