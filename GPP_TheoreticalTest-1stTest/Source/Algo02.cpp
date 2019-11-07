/*  C++ Algorithms 2
    
    Write a function that removes K random elements from a std::vector as efficiently as you can. 
    The function should work in place, but does not need to preserve the order of elements.
*/

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void removeK(std::vector<int>& v, unsigned k)
{
    // This vector has it coming...
	
	std::vector<int> randVec(k);
	for(int i=0; i<k; i++)
	{
		/* generate k secret numbers between 0 and 49-i: */
		int posK = rand() % (49-i);
				
		// remove each element from the vector v
		std::vector<int>::iterator it = v.begin() + posK;
		*it = std::move(v.back());
		v.pop_back();
	}	
}

int main(int argc, char* argv[])
{
	/* initialize random seed: */
    srand (time(NULL));  

    std::vector<int> arr;
    for (int i = 0; i < 50; ++i)
        arr.push_back(i);

    removeK(arr, 5);

    for (auto i: arr)
        std::cout << i << std::endl;

	return 0;
}