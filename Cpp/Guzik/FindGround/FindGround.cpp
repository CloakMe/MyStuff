// FindGround.cpp : Defines the entry point for the console application.
//
//The Ground net (points connected to the electrical ground) has more than (VERY IMPORTANT)
//N/2 contact points!

//array holding the contact points:
//int contactPnts[] = { 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0};
//NOTICE: the digit with most repetitions represent the Ground

//The program needs at most (N-2) measurements!
//The beeper variable counts the number of measurements.

#include <vector>
#include <iostream>
#include <assert.h> 

int beeper = 0;

//returns the positions inside the points array
int GetGround(const std::vector<int>& points, 
              std::vector<int>& oldPositions, 
              std::vector<int>& newPositions,
              std::vector<int>& rest)
{   
    unsigned sz = oldPositions.size();
    newPositions.clear();
    for(int i=0; i<sz-1; i=i+2)
    {
        beeper++;
        if( points[oldPositions[i]] == points[oldPositions[i+1]] )
        {            
            newPositions.push_back(oldPositions[i+1]);
        }
    }
    if(sz % 2 == 1)
        rest.push_back(*oldPositions.rbegin());

    if(newPositions.size() == 0)
    {
        return (*rest.rbegin());

    }else if(newPositions.size() == 1)
    {
        return *newPositions.begin();
    }else // if(newPositions.size() > 1 )
    {
        oldPositions.clear();
        for(int i : newPositions)
        {
            oldPositions.push_back(i);
        }

        return GetGround(points, oldPositions, newPositions, rest);
    }

}

int TestFun(int contactPnts[], int arraySize)
{
    beeper = 0;
    std::vector<int> points(contactPnts, contactPnts + arraySize);
    std::vector<int> oldPositions;
    std::vector<int> newPositions;
    std::vector<int> rest;

    int residual = (points.size() % 2);
    oldPositions.resize(points.size()-residual);
    newPositions.resize(points.size()-residual);
    //set initial positions
    
    for(int i=0; i<(points.size() - residual); i++)
        oldPositions[i] = i;

    if(points.size() % 2 == 1)
        rest.push_back(points.size()-1);

    int result = GetGround(points, oldPositions, newPositions, rest);
    return result;
}

void AllTests()
{
    int resultT, arraySize;
    int contactPnts1[] = { 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0};
    arraySize = sizeof contactPnts1 / sizeof contactPnts1[0];
    resultT = TestFun(contactPnts1, arraySize);
    assert(contactPnts1[resultT] == 0);

    int contactPnts2[] = { 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1};
    arraySize = sizeof contactPnts2 / sizeof contactPnts2[0];
    resultT = TestFun(contactPnts2, arraySize);
    assert(contactPnts2[resultT] == 0);

    int contactPnts3[] = { 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1};
    arraySize = sizeof contactPnts3 / sizeof contactPnts3[0];
    resultT = TestFun(contactPnts3, arraySize);
    assert(contactPnts3[resultT] == 0);

    int contactPnts4[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0};
    arraySize = sizeof contactPnts4 / sizeof contactPnts4[0];
    resultT = TestFun(contactPnts4, arraySize);
    assert(contactPnts4[resultT] == 0);

    int contactPnts5[] = { 0, 0, 1, 1, 0, 0, 2, 1, 0, 0, 2, 1, 0, 0, 1, 1, 0};
    arraySize = sizeof contactPnts5 / sizeof contactPnts5[0];
    resultT = TestFun(contactPnts5, arraySize);
    assert(contactPnts5[resultT] == 0);

    int contactPnts6[] = { 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 2, 1, 0, 0, 1, 1, 0};
    arraySize = sizeof contactPnts6 / sizeof contactPnts6[0];
    resultT = TestFun(contactPnts6, arraySize);
    assert(contactPnts6[resultT] == 0);

    int contactPnts7[] = { 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1};
    arraySize = sizeof contactPnts7 / sizeof contactPnts7[0];
    resultT = TestFun(contactPnts7, arraySize);
    assert(contactPnts7[resultT] == 0);

    int contactPnts8[] = { 0, 0, 2, 2, 0, 0, 1};
    arraySize = sizeof contactPnts8 / sizeof contactPnts8[0];
    resultT = TestFun(contactPnts8, arraySize);
    assert(contactPnts8[resultT] == 0);

    int contactPnts9[] = { 0, 0, 2, 2, 0, 0, 0, 1};
    arraySize = sizeof contactPnts9 / sizeof contactPnts9[0];
    resultT = TestFun(contactPnts9, arraySize);
    assert(contactPnts9[resultT] == 0);

    int contactPnts10[] = { 2, 2, 0, 0, 0, 1, 0, 0};
    arraySize = sizeof contactPnts10 / sizeof contactPnts10[0];
    resultT = TestFun(contactPnts10, arraySize);
    assert(contactPnts10[resultT] == 0);

    int contactPnts11[] = { 2, 2, 0, 0, 0, 0, 1};
    arraySize = sizeof contactPnts11 / sizeof contactPnts11[0];
    resultT = TestFun(contactPnts11, arraySize);
    assert(contactPnts11[resultT] == 0);

    int contactPnts12[] = { 0, 0, 2, 0, 0, 0, 2, 2, 0, 2, 2};
    arraySize = sizeof contactPnts12 / sizeof contactPnts12[0];
    resultT = TestFun(contactPnts12, arraySize);
    assert(contactPnts12[resultT] == 0);

    int contactPnts13[] = { 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2};
    arraySize = sizeof contactPnts13 / sizeof contactPnts13[0];
    resultT = TestFun(contactPnts13, arraySize);
    assert(contactPnts13[resultT] == 0);

    int contactPnts14[] = { 3, 3, 0, 3, 3, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 2};
    arraySize = sizeof contactPnts14 / sizeof contactPnts14[0];
    resultT = TestFun(contactPnts14, arraySize);
    assert(contactPnts14[resultT] == 0);

    int contactPnts15[] = { 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2};
    arraySize = sizeof contactPnts15 / sizeof contactPnts15[0];
    resultT = TestFun(contactPnts15, arraySize);
    assert(contactPnts15[resultT] == 0);
}

int main()
{
    AllTests();
    beeper = 0;
    int contactPnts[] = { 1, 0, 1, 0, 1, 0, 0};
    int arraySize = sizeof contactPnts / sizeof contactPnts[0];
    std::vector<int> points(contactPnts, contactPnts + arraySize);
    std::vector<int> oldPositions;
    std::vector<int> newPositions;
    std::vector<int> rest;

    int residual = (points.size() % 2);
    oldPositions.resize(points.size()-residual);
    newPositions.resize(points.size()-residual);
    //set initial positions
    
    for(int i=0; i<(points.size() - residual); i++)
        oldPositions[i] = i;

    if(points.size() % 2 == 1)
        rest.push_back(points.size()-1);

    int result = GetGround(points, oldPositions, newPositions, rest);
    std::cout << "contact point position " << result << ", contact point " << points[result] << std::endl;
    std::cout << "beeper measurements "<< beeper << std::endl;
	return 0;
}

