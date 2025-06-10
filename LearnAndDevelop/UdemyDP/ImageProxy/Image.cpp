#include "Image.h"

Image::Image(const std::string& fileName) :
	m_FileName(fileName)
{}

void Image::SetFileName(const std::string& fileName) 
{
	m_FileName = fileName;
}

const std::string& Image::GetFileName() const 
{
	return m_FileName;
}
