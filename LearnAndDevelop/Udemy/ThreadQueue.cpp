#include "ThreadQueue.h"

#include <future>
#include <mutex>
#include <chrono>

using namespace std;

template <>
bool ThreadQueue<future<void>>::try_pop(std::future<void>& value)
{
	lock_guard<mutex> lock(m_mutex);
	if (m_queue.empty()) 
		return false;
		
	if (m_queue.front().wait_for(chrono::milliseconds(0)) != future_status::ready) {
		return false;
	}

	value = move(m_queue.front()); // Move, do not copy!
	m_queue.pop();
	return true;
}
template class ThreadQueue<std::future<void>>;