#include <iostream>
using namespace std;
#include "Resource.h"

int main()
{
	cout << "hello world Resource" << endl;
	Resource resource(2, 10);
	cout << resource << endl;
	Resource other = resource;
	other[3] = 3;
	other[0] = 4;
	cout << other << endl;
	cout << resource << endl;
	Resource newResource = other.add(resource);
	cout << newResource << endl;
	newResource = resource.add(other);
	cout << newResource << endl;
	newResource = Resource(5, 5);
	cout << newResource << endl;
	int a = 54;
	int b = 45 + a;
	return b;
}