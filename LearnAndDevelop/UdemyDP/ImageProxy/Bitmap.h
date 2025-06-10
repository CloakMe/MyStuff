#pragma once
#include <string>

#include "Image.h"

class Bitmap : public Image
{
public:
	Bitmap() = default;
	Bitmap(const std::string& fileName);
	void Display() const override ;
	void Load() override;
	void Load(const std::string & fileName) override;
private:
	std::string m_Buffer{};
	void InternalLoad();
};

