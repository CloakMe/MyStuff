#pragma once
#include <functional>
#include <mutex>
#include <condition_variable>

class MutexUsage
{
public:
	MutexUsage();
	void runTwoJobs(std::function<void(int, std::mutex&)> job1, std::function<void(double, std::mutex&)> job2) const;
	void runAJob();
	void runAJobUsingJthread();
private:
	void AJob();
	int m_x;
	//condition variable definition
	std::condition_variable m_condition_var;
	bool m_condition_flag;
	std::mutex m_condition_mutex;
};

