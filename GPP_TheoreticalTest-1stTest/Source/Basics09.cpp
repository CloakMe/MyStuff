/*  C++ Basics 9
    
    In the code below change the auto in front of f and g to the most specific possible concrete types
*/

#include <iostream>

int mulBy2(float a)
{
    return (int) (a*a);
}

int main(int argc, char* argv[])
{
    int (*f)(float) = mulBy2;
    float c = 3.f;
    auto g = [=](float a) { return a * c; };
    std::cout << f(2.0f) << " " << g(2.0f) << std::endl;

	return 0;
}