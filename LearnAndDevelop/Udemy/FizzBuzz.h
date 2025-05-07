#pragma once
#include <string>
#include <mutex>

class FizzBuzz
{
public:
	FizzBuzz() = default;

	void PlayGame(int n);
	
	std::string GetResult();
private:
	std::string GetPrefix(int idx) const;

	std::mutex m_mutex;
	std::string m_result;
};
