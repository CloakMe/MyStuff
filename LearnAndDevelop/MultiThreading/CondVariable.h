#pragma once
#include <string>
#include <condition_variable>
#include <mutex>
#include <string>

class CondVariable
{
public:
	CondVariable() : m_cv_flag(true)
	{}
	void Read();
	void Write(/*std::string str*/);
private:
	std::string m_resource;
	std::condition_variable m_cv;
	std::mutex m_mtx;
	bool m_cv_flag;
};

