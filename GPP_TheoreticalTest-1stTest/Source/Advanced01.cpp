/*  C++ Advanced 1
    
    Fix the problem with the code below. Write a comment explaining the cause.

	In both casese of 
	A a;
    B b;
	the non - default constructor of A() is called which initializes m_data = 5;
	The constructor will always call the local implementation of initData()
	if no further specifications are given (e.g. B::initData() or A::initData() )
*/

#include <iostream>

struct A
{
    A() { initData(); }

    virtual void initData() { m_data = 5; }
    virtual void processData() { m_data += 5; }

    int m_data;
};

struct B: public A
{
	B() { initData(); } //fix

    virtual void initData() { m_data = 6; }
    virtual void processData() { m_data += 4; }
};

int main(int argc, char* argv[])
{
    A a;
    B b;
    a.processData();
    b.processData();
    std::cout << a.m_data << std::endl;
    std::cout << b.m_data << std::endl;

	return 0;
}