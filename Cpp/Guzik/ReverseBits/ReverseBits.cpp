// ReverseBits.cpp : Defines the entry point for the console application.
//

unsigned int reverseBitsOLogN(unsigned int n) 
{
    unsigned int x = 0;
    for(unsigned int i = 31; n; ) 
    {
        x |= (n & 1) << i;
        n >>= 1;
        -- i;
    }
    return x;
}

unsigned int reverseBitsO1(unsigned int n) 
{
    n = (n >> 1) & 0x55555555 | (n << 1) & 0xaaaaaaaa;
    n = (n >> 2) & 0x33333333 | (n << 2) & 0xcccccccc;
    n = (n >> 4) & 0x0f0f0f0f | (n << 4) & 0xf0f0f0f0;
    n = (n >> 8) & 0x00ff00ff | (n << 8) & 0xff00ff00;
    n = (n >> 16) & 0x0000ffff | (n << 16) & 0xffff0000;
    return n;
}

int main()
{
    unsigned int n = 12341234;
    unsigned int result1 = reverseBitsOLogN(n);
    unsigned int result2 = reverseBitsO1(n);
	return 0;
}

