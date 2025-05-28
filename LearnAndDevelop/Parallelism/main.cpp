#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>

using namespace std;

template<typename T>
T call_c11algo(const std::vector<T>& vec, T a);

void call_foreach(int n, execution::parallel_policy policy);

int main()
{
	char in;
	do
	{
		cout << "Please choose\n1 std algorithms with execution policy\n"
			"2 for executon policies examples (continued...)\n"
			"3 not ready yet\n";
		cin >> in;

	} while (in < '1' || '6' < in);

	if (in == '1')
	{
		std::vector<int> vec{ 1, 2, 3, 4, 5, 6 };
		try {
			int res = call_c11algo(vec, 3);
			cout << "res = " << res << endl;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}
	else if (in == '2')
	{
		call_foreach(20'000, execution::par);
	}
	
	
	return 0;
}

template<typename T>
T call_c11algo(const std::vector<T>& vec, T a)
{
	typename vector<T>::const_iterator it = find_if(execution::par, vec.begin(), vec.end(), [a](const int& val) {
		throw exception("Throw Now!");
		return val > a ? true : false;
	});

	return *it;
}

void call_foreach(int n, execution::parallel_policy policy)
{
	std::vector<int> vec(n);
	int count = 0;

	for_each(policy, vec.begin(), vec.end(),
		[&count](int& x) { x = ++count; }
	);

	for (auto i : vec)
		std::cout << i << ',';
	std::cout << '\n';
}