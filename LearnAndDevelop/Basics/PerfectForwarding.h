#pragma once
#include <iostream>

void ForwardAB()
{
	std::cout << "end!" << endl;
}

template<typename A, typename... Args>
void ForwardAB(A && a, Args... rest)
{
	std::cout << a << endl;
	//B && b = std::_Get_first_parameter(other);
	// std::tuple_element<0, std::tuple<EntityTs...>>::type
	ForwardAB(rest...);
}
