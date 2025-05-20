#pragma once

#include <mutex>
#include <string>
#include <map>
//#include <pair>

class Monitor
{
public:
	Monitor() :
		m_users(),
		m_mutex()
	{}
	void show(std::string name);
	void credit(std::string name, double amount);
	void debit(std::string name, double amount);
	void add_user(std::string name, double amount);
private:
	std::mutex m_mutex;
	std::map< std::string, double > m_users;
};

class Bank
{
public:
	Bank() :
		m_users()
	{}
	void show(std::string name);
	void credit(std::string name, double amount);
	void debit(std::string name, double amount);
	void add_user(std::string name, double amount);
private:
	std::map< std::string, double > m_users;
};

class BankMonitor
{
public:
	BankMonitor() : m_bank()
	{}
	void show(std::string name)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_bank.show(name);
	}
	void credit(std::string name, double amount)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_bank.credit(name, amount);
	}
	void debit(std::string name, double amount)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_bank.debit(name, amount);
	}
	void add_user(std::string name, double amount)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_bank.add_user(name, amount);
	}
private:
	Bank m_bank;
	std::mutex m_mutex;
};