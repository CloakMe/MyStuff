#include <iostream>
#include <thread>
#include <latch>
#include <chrono>
#include "LatchUsage.h"
using namespace std;

static void displayA(std::latch& latch)
{
	latch.arrive_and_wait();
	for (int i = 0; i < 10; i++)
	{
		std::cout << "A";
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

static void displayB(std::latch& latch)
{
	latch.arrive_and_wait();
	for (int i = 0; i < 10; i++)
	{
		std::cout << "B";
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void LatchUsage::runTwoJobs() const
{
	std::latch latch(2);
	std::thread thread1(displayA, std::ref(latch));
	std::thread thread2(displayB, std::ref(latch));
	latch.wait();
	thread1.join();
	thread2.join();

	cout << "\njobs (using latch) are done!\n";
}
