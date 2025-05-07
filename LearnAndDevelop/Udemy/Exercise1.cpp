#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

#include "FizzBuzz.h"

using namespace std;

mutex mtx;
int counter = 0;
void incrementCounter()
{
	lock_guard<mutex> lock(mtx);
	++counter;
}

int main()
{
	FizzBuzz game;
	
	thread thread(&FizzBuzz::PlayGame, &game, 20);
	thread.join();
	cout << game.GetResult();

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 100000; i++)
	{
		std::thread thrd(&incrementCounter);
		thrd.join();
	}

	cout << endl << "counter = " << counter << endl;
	auto end = std::chrono::steady_clock::now();
	chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Elapsed time: " << elapsed.count() << " ms\n";

	return 0;
}