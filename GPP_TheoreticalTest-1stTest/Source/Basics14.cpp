/*  C++ Basics 14
    
    Write a comment to explain the output
	funcCaller(&someA);
	produces
	Calling A::baz()
	Calling A::bar() 
	Since someA is object of type A and the function "funcCaller" accepts argument of type A*,
	the functions A::baz() and A::bar() are called respectively.
	This is straightforward.

	funcCaller(&someB);
	Here is a cast from type B* to type A*, 
		as the function "funcCaller" accepts argument of type A* AND
		the object passed to the function is of type B*.
	This produces 
		1.
		Calling A::baz(), because the pointer someA is of type A*.

		2. 
		Calling B::bar(), because the function A:bar() is defined as virtual:
		virtual void bar() 
		Thus it is very possible that the compilator uses late binding to call the function
		by looking first at the VPTR inside the object passed to the "funcCaller"
		and then checking the correct function to call inside the VTABLE.
		The pointer passed is of type A* but the object related to that pointer is
		actually of type B. Thus we look at the VTABLE of B which points to B::bar().
*/

#include <iostream>

class A
{
public:
    void baz()              { std::cout << "Calling A::baz() " << std::endl; }
    virtual void bar()      { std::cout << "Calling A::bar() " << std::endl; }
};

class B : public A
{
public:
    void baz()              { std::cout << "Calling B::baz() " << std::endl; }
    virtual void bar()      { std::cout << "Calling B::bar() " << std::endl; }
};

void funcCaller(A* someA)
{
	if (someA)
	{
		someA->baz();
		someA->bar();
	}
}

int main(int argc, char* argv[])
{
	A someA;
	B someB;
	
	funcCaller(&someA);
	funcCaller(&someB);

	return 0;
}