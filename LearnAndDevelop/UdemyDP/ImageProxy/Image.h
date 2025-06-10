#pragma once
#include <string>

class Image
{
public:
	Image() = default;
	Image(const std::string & fileName);

	const std::string& GetFileName() const;
	virtual ~Image() = default;
	virtual void Display() const = 0;
	virtual void Load() = 0;
	virtual void Load(const std::string & fileName) = 0;

protected:
	void SetFileName(const std::string& fileName);

private:
	std::string m_FileName;
};


