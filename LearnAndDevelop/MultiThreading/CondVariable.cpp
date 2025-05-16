#include <iostream>
#include <thread>
#include <chrono>
#include "CondVariable.h"
using namespace std;
using namespace literals;

void CondVariable::Read()
{
	unique_lock<mutex> lock(m_mtx);
	m_cv.wait(lock, [this]() {return m_cv_flag; });
	cout << "The resource is: ";
	cout << m_resource << endl;
	this_thread::sleep_for(2s);
}

void CondVariable::Write(string str)
{	
	lock_guard<mutex> lock(m_mtx);
	cout << "Writing string: " << str << endl;
	this_thread::sleep_for(1s);
	m_resource += str;
	m_cv_flag = true;
	m_cv.notify_all();
}