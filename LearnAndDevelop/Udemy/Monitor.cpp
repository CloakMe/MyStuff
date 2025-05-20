#include "Monitor.h"
#include <iostream>
//#include <m>

using namespace std;

void Monitor::show(std::string name)
{
	lock_guard<mutex> lock(m_mutex);
	cout << name << " cash :" << m_users[name] << endl;
}

void Monitor::credit(std::string name, double amount)
{
	lock_guard<mutex> lock(m_mutex);

	cout << name << " old cash :" << m_users[name] << endl;

	m_users[name] += amount;

	cout << name << " new cash :" << m_users[name] << endl;
}

void Monitor::debit(std::string name, double amount)
{
	lock_guard<mutex> lock(m_mutex);

	cout << name << " old cash :" << m_users[name] << endl;

	m_users[name] -= amount;

	cout << name << " new cash :" << m_users[name] << endl;
}

void Monitor::add_user(std::string name, double amount)
{
	lock_guard<mutex> lock(m_mutex);
	m_users[name] = amount;
}


void Bank::show(std::string name)
{
	cout << name << " cash :" << m_users[name] << endl;
}

void Bank::credit(std::string name, double amount)
{
	cout << name << " old cash :" << m_users[name] << endl;

	m_users[name] += amount;

	cout << name << " new cash :" << m_users[name] << endl;
}

void Bank::debit(std::string name, double amount)
{
	cout << name << " old cash :" << m_users[name] << endl;

	m_users[name] -= amount;

	cout << name << " new cash :" << m_users[name] << endl;
}

void Bank::add_user(std::string name, double amount)
{
	m_users[name] = amount;
}
