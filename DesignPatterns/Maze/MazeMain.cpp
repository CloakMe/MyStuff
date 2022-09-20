// Maze.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Maze.h"
#include "MazeGame.h"
#include "StandardMazeBuilder.h"
#include "EnchantedMazeFactory.h"
using namespace MazeApp;
class A {
public:
	A() {}
	
	virtual void doStuff()
	{
		std::cout << "virtual doA()\n";
	}

	void doOther()
	{
		std::cout << "doOther() from A\n";
	}
};

class B : public A
{
public:
	B() :A() {}

	virtual void doStuff() override
	{
		std::cout << "virtual doB()\n";
	}

	 void doOther()
	{
		std::cout << "doOther() from B\n";
	}
};

int main()
{
	A* a = new A;
	A* b1 = new B;
	B* b2 = new B;

	a->doStuff();
	a->doOther();

	b1->doStuff();
	b1->doOther();
	((B*)b1)->doOther();

	b2->doStuff();
	b2->doOther();

    std::cout << "Creating amazing maze...!\n";
	Maze* maze;
	MazeGame game;
	StandardMazeBuilder builder;

	game.CreateMaze(builder);
	maze = builder.GetMaze();

	EnchantedMazeFactory enchantedMazeFactory;
	maze = game.CreateMaze(enchantedMazeFactory);

	std::cout << "done!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
