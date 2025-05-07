#include "BarrierUsage.h"
#include <barrier>
#include <thread>
#include <iostream>
using namespace std;

static void displayA(barrier<>& barrier)
{
	for (char i = 'A'; i < 'K'; i=i+2)
	{
		std::barrier<>::arrival_token arrival_token = barrier.arrive();
		barrier.wait(std::move(arrival_token));
		cout << i;
		barrier.arrive_and_wait();
	}
	barrier.arrive_and_wait();
}

static void displayB(barrier<>& barrier)
{
	barrier.arrive_and_wait();
	for (char i = 'B'; i < 'K'; i=i+2)
	{
		barrier.arrive_and_wait();
		barrier.arrive_and_wait();
		cout << i;
	}
}

void BarrierUsage::runTwoJobs() const
{
	cout << "Write first 10 letters of the english alphabet:\n";
	std::barrier<> barrier(2);
	std::thread thread1(displayA, std::ref(barrier));
	std::thread thread2(displayB, std::ref(barrier));

	thread1.join();
	thread2.join();

	cout << "\njobs (using barrier) are done!\n";
}
