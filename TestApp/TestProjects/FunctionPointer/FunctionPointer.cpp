// FunctionPointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int GetMid(int a, int b)
{
	return (a + b ) / 2;
}

struct FOO
{
	explicit FOO(int i) : mI(i){} //constructor
	operator int() const {
		return mI;
	}

private:
	int mI;
};
//
class C
{
public:
	void f1(){}
	void f2() const{}
};
//struct my
//{
//
//}
int _tmain(int argc, _TCHAR* argv[])
{
	//C c;
	//const C& cr =c;

	//FOO f1(1);
	//FOO f2 = 1;
	//FOO f1= FOO(1);
	int f1 = FOO(7);
	//cr.f1();
	//cr.f2();

	typedef int (* MidFun_ptr) (int, int);
	MidFun_ptr getMid_ptr = &GetMid;
	int p = getMid_ptr(3,5);

	char f[2];
	f[0] = '1';
	f[1] = '2';
	typedef const char * charPtr;
	charPtr pp  = f;
	pp = "foo";
	//pp[0] = '0';
	//pp = "12";
	const char *pp2 = f;
	pp2 = "12";

	const char * s = f;
	//s[0] = '3';
	char const * s2 = f;
	s2 = "12";
	char * const s3 = f;
	//s3 = "12";

	int i = 2;
	printf("%d %d \n", i++, i++);

	int a[5];// = {2, 3};
	printf("%d %d %d \n", a[2], a[3], a[4]);

	char *pe = "sam";
	char pa[] = "sami";

	char g = *(pe + 1) ;
//	pe[1] = '3';
	g = *(pa + 2) ;
	pa[1] = '2';

	return 0;
}

