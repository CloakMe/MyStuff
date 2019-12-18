// sequenceOfBits.cpp : Defines the entry point for the console application.
//
//There is a long sequence of bits. Initially all bits are set to 0.
//- On the 1-st step each bit (1,2,3, ...) is inverted
//- On the 2-nd step each 2nd bit (2,4,6, ...) is inverted
//- On the 3-nd step each 3rd bit (3,6,9, ...) is inverted
//        and so on.
//It is easy to see that no matter how long the sequence is, the value of 
//n-th bit will remain stable after the n-th step.
//What will this stable value of the n-th bit be?

//After the n-th step:
//1)All positions N <= n, which are exact squares, i.e. p*p=N, where p is natural number, e.g. 4, 9, 16, 36, etc.
//will toggle the ONE bit.
//2)All other positions N <= n will toggle the ZERO bit.
//This is because all numbers of type 1) have odd count of divisors
//and all numbers of type 2) have even count of divisors.
int main()
{
	return 0;
}

