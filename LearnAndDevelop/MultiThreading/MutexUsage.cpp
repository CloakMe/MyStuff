#include <iostream>
#include <thread>
#include <mutex>
#include "MutexUsage.h"
using namespace std;

MutexUsage::MutexUsage() : m_x(0), m_condition_flag(false) {}

void MutexUsage::runTwoJobs(std::function<void(int, std::mutex&)> job1, std::function<void(double, std::mutex&)> job2) const
{
	mutex mutex;
	int i = 1;
	double d = 2.4;
	std::thread thread1(job1, i, std::ref(mutex));
	std::thread thread2(job2, d, std::ref(mutex));

	thread1.join();
	thread2.join();

	cout << "jobs using mutexes are done!\n";
}

void MutexUsage::runAJob()
{
	unique_lock<mutex> unique_lock(m_condition_mutex);
	m_condition_flag = false;

	std::thread thread1(&MutexUsage::AJob, this);
	
	m_condition_var.wait(unique_lock, [this]() {return m_condition_flag; });

	thread1.join();
	cout << "the cv job is done!\n";
}

void MutexUsage::runAJobUsingJthread()
{
	{
		lock_guard<mutex> lock(m_condition_mutex);
		m_x = 1;
		m_condition_flag = false;
	}
#if __cplusplus >= 202002L
	// C++20 or above
	{
		std::jthread jthread(&MutexUsage::AJob, this);
	}
#else
	// C++17 or below
	{
		std::thread simple_thread(&MutexUsage::AJob, this);
		simple_thread.join();
	}
#endif	
	cout << "the jthread job is done!\n";
}

void MutexUsage::AJob()
{
	{
		lock_guard lock(m_condition_mutex);
		m_condition_flag = true;
		m_x = 45;
		cout << "x=" << m_x << endl;
	}
	m_condition_var.notify_one();
}