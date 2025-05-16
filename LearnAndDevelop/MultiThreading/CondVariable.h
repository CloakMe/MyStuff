#pragma once
#include <string>
#include <condition_variable>
#include <mutex>

class CondVariable
{
public:
	CondVariable() : 
		m_cv_flag(true),
		m_resource("")
	{}
	void Read();
	void Write(std::string str);
private:
	std::string m_resource;
	std::condition_variable m_cv;
	std::mutex m_mtx;
	bool m_cv_flag;
};

