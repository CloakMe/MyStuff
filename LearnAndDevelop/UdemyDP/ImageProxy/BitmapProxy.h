#pragma once
#include "Image.h"
#include <memory>

class Bitmap;
class BitmapProxy : public Image
{
public:
	BitmapProxy(const std::string& fileName = "");
	~BitmapProxy() = default;
	void Display() const override;
	void Load() override;
	void Load(const std::string& fileName) override;

private:
	std::unique_ptr<Bitmap> m_Bitmap;
	static bool m_Loaded;
};

