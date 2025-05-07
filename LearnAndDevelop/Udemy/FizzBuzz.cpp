#include "FizzBuzz.h"
#include <vector>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;

static vector<string> children{ "Divya", "Abdul", "Bart", "Claudia" };

string FizzBuzz::GetPrefix(int idx) const
{
	int i = idx % children.size();
	return children[i] + " says ";
}

void FizzBuzz::PlayGame(int n)
{
	if (n < 1)
		return;

	stringstream output;
	for (int i = 1; i <= n; i++)
	{
		if (i > 1)
			output << endl;

		output << GetPrefix(i);
		if (i % 15 == 0)
			output << "fizzbuzz";
		else if (i % 3 == 0)
			output << "fizz";
		else if (i % 5 == 0)
			output << "buzz";
		else
			output << i;
	}

	lock_guard<mutex> lock(m_mutex);
	m_result = output.str();
}

string FizzBuzz::GetResult()
{
	lock_guard<mutex> lock(m_mutex);
	return m_result;
}
