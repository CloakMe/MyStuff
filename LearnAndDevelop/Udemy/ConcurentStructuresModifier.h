#pragma once
#include <forward_list>
#include <mutex>
#include <string>

// Helper to invoke member function with or without argument
template<typename Obj, typename Func1, typename Func2, typename... Args>
void runThreads(Obj obj, Func1 func1, Func2 func2, Args&&... args) {
	std::thread thr1;
	if constexpr (sizeof...(args) == 0) {
		thr1 = std::thread(func1, &obj);
	}
	else 
	{
		thr1 = std::thread(func1, &obj, std::forward<Args>(args)...);
	}
	std::thread thr2(func2, &obj);

	thr1.join();
	thr2.join();

	obj.printElems();
}

class ConcurentStructuresModifier
{
public:
	ConcurentStructuresModifier();

	void modifyEl1(int modifier);
	void readEl2();

	void removeEl1();
	//void readEl2();

	void removeEl2();
	void readEl1();

	//void removeEl1();
	//void removeEl2();

	//void removeEl2();
	//void removeEl1();

	//void removeEl2();
	void removeEl5();

	void printElems();
	
private:
	void printStringConcurently(std::string s);
	std::forward_list<int> m_fwd_list;
	std::mutex m_mtx;
};

