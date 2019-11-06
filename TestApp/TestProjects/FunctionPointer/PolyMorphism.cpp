// PolyMorphism.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
using namespace std;

enum note { middleC, Csharp, Eflat }; // Etc.
class Instrument {
public:
	// void play(note) const 
	virtual void play(note) const 
	{
		cout << "Instrument::play" << endl;
	}
};
// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {
public:
	// Redefine interface function:
	void play(note) const {
	cout << "Wind::play" << endl;
	}
};

void tune(Instrument& i) {
    // ...
	i.play(middleC);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Wind flute;
	tune(flute); // Upcasting

	Instrument& flut = Wind();
	flut.play(middleC);
	return 0;
}

