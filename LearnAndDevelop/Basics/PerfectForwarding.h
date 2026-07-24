#pragma once
#include <iostream>

void ForwardAB()
{
	std::cout << "end!" << std::endl;
}

template<typename A, typename... Args>
void ForwardAB(A && a, Args... rest)
{
	std::cout << a << endl;
	//B && b = std::_Get_first_parameter(other);
	// std::tuple_element<0, std::tuple<EntityTs...>>::type
	ForwardAB(rest...);
}

template<typename... T>
void Foo(T... args)
{
    ((std::cout << args << " "), ...); 
    std::cout << std::endl;
    
}

