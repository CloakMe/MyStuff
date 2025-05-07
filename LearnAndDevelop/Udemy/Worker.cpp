#include "Worker.h"
#include <future>
#include <iostream>
using namespace std;

void Worker::add(std::function<void()> fun)
{
    future<void> future = async(launch::async, [fun] {
		fun();
	});

	m_queue.push(move(future));
}

void Worker::joinFinishedUntilFirstRunning(int threshold)
{
	int size = m_queue.size();
	if (size < threshold)
		return;

	//cout << "queue size = " << size ;
	while (true)
	{
		// Check if thread is finished
		future<void> future;
		if (!m_queue.try_pop(future)) {
			break;
		}
	}
	size = m_queue.size();
	//cout << "| queue size after clean = " << size << endl;
}

void Worker::joinAll()
{
	int size = m_queue.size();
	cout << "queue (All) size = " << size;
	while (m_queue.size()>0)
	{
		future<void> future;
		m_queue.wait_and_pop(future);
		future.wait();
	}
	size = m_queue.size();
	cout << "| queue (All) size after clean = " << size << endl;
}