#pragma once
#include <queue>
#include <mutex>
#include <thread>
#include <future>
#include <condition_variable>

template <typename T>
class ThreadQueue {
public:
	void push(T&& value) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(std::move(value));
		m_cond.notify_one();
	}

	bool try_pop(T& value) {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_queue.empty()) return false;
		value = m_queue.front();
		m_queue.pop();
		return true;
	}

	void wait_and_pop(T& value) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [this] { return !m_queue.empty(); });
		value = std::move(m_queue.front());
		m_queue.pop();
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}

	int size() const {
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queue.size();
	}
private:
	mutable std::mutex m_mutex;
	std::queue<T> m_queue;
	std::condition_variable m_cond;
};

template <>
bool ThreadQueue<std::future<void>>::try_pop(std::future<void>& value)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_queue.empty()) 
		return false;
		
	if (m_queue.front().wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
		return false;
	}

	value = std::move(m_queue.front()); // Move, do not copy!
	m_queue.pop();
	return true;
}
//class Worker {
//public:
//	using Task = std::function<void()>;
//
//	Worker(ThreadQueue<Task>& queue)
//		: queue_(queue), stop_flag_(false), thread_([this] { run(); }) {}
//
//	~Worker() {
//		stop_flag_ = true;
//		// Push a dummy task to unblock wait_and_pop
//		queue_.push([] {});
//		thread_.join();
//	}
//
//private:
//	void run() {
//		while (!stop_flag_) {
//			Task task;
//			queue_.wait_and_pop(task);
//			if (stop_flag_) break;
//			task();
//		}
//	}
//
//	ThreadSafeQueue<Task>& mqueue;
//	std::atomic<bool> stop_flag_;
//	std::thread thread_;
//};