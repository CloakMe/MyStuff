#include "ConcurentStructuresModifier.h"
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <string>
using namespace std;

// Conflicting operations on STL containers are not safe
// They must be synchronized


ConcurentStructuresModifier::ConcurentStructuresModifier()
	: m_fwd_list(),
	m_mtx()
{
	m_fwd_list.push_front(5);
	m_fwd_list.push_front(4);
	m_fwd_list.push_front(3);
	m_fwd_list.push_front(2);
	m_fwd_list.push_front(1);
}

void ConcurentStructuresModifier::modifyEl1(int modifier)
{
	lock_guard lock(m_mtx);
	forward_list<int>::iterator it = m_fwd_list.begin();
	*it = modifier;
	printStringConcurently("first elem modified!");
}
void ConcurentStructuresModifier::readEl2()
{
	lock_guard lock(m_mtx);
	forward_list<int>::iterator it = m_fwd_list.begin();
	int elm = *(++it);
	printStringConcurently("second element equals " + to_string(elm));
}

void ConcurentStructuresModifier::removeEl1()
{
	lock_guard lock(m_mtx);
	m_fwd_list.remove(1);
	printStringConcurently("remove first element! ");
}
//void readEl2();

void ConcurentStructuresModifier::removeEl2()
{
	lock_guard lock(m_mtx);
	m_fwd_list.remove(2);
	printStringConcurently("remove second element! ");
}
void ConcurentStructuresModifier::readEl1()
{
	lock_guard lock(m_mtx);
	int elm = *(m_fwd_list.begin());
	printStringConcurently("first elm is " + to_string(elm));
}

//void removeEl1();
//void removeEl2();

//void removeEl2();
//void removeEl1();

//void removeEl2();
void ConcurentStructuresModifier::removeEl5()
{
	lock_guard lock(m_mtx);
	m_fwd_list.remove(5);
	printStringConcurently("remove fifth element! ");
}

void ConcurentStructuresModifier::printStringConcurently(string s)
{	
	cout << s << endl;
}

void ConcurentStructuresModifier::printElems()
{
	cout << "the list is: ";
	for(int& elem : m_fwd_list)
		cout << elem;
	cout << endl;
}