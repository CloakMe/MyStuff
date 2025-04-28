#include <iostream>
#include <thread>
#include <mutex>
#include "MutexUsage.h"
using namespace std;

void MutexUsage::runTwoJobs(std::function<void(int, std::mutex&)> job1, std::function<void(double, std::mutex&)> job2) const
{
	std::mutex mutex;
	int i = 1;
	double d = 2.4;
	std::thread thread1(job1, i, std::ref(mutex));
	std::thread thread2(job2, d, std::ref(mutex));

	thread1.join();
	thread2.join();

	cout << "jobs are done!\n";
}