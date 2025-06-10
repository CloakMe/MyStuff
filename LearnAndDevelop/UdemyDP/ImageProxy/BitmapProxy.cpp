#include <iostream>
#include <filesystem>
#include "BitmapProxy.h"
#include "Bitmap.h"

bool BitmapProxy::m_Loaded = false;

BitmapProxy::BitmapProxy(const std::string& fileName)
{
	m_Bitmap = std::make_unique<Bitmap>( fileName );
}

void BitmapProxy::Display() const 
{
	if(!m_Loaded) 
	{
		std::cout << "[Proxy] Loading bitmap\n";
		std::string input_string = GetFileName();
		if (std::filesystem::exists(input_string))
		{
			m_Bitmap->Load(input_string);
			m_Loaded = true;
		}
		else if(input_string.empty() && std::filesystem::exists(m_Bitmap->GetFileName()))
		{
			m_Bitmap->Load();
			m_Loaded = true;
		}
		else
		{
			std::cout << "The provided bitmap file name is wrong\n";
			return;
		}
	}
	m_Bitmap->Display();
}

void BitmapProxy::Load() 
{
}

void BitmapProxy::Load(const std::string& fileName) 
{
	SetFileName(fileName);
}
