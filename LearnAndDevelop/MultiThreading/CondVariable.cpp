#include <iostream>
#include <thread>
#include <latch>
#include <chrono>
#include "CondVariable.h"
using namespace std;
using namespace literals;

void CondVariable::Read()
{
	unique_lock<mutex> lock(m_mtx);
	m_cv_flag = false;
	m_cv.wait(lock, [this]() {return m_cv_flag; });
	cout << m_resource;
	cout << "The resource is:" << endl;
	std::this_thread::sleep_for(1s);
	cout << m_resource;
}

void CondVariable::Write(/*string str*/)
{	
	lock_guard<mutex> lock(m_mtx);
	//cout << "Writing string:\n";
	//cout << str;
	
	std::this_thread::sleep_for(200ms);
	m_resource += "yo";
	m_cv_flag = true;
	m_cv.notify_all();
}