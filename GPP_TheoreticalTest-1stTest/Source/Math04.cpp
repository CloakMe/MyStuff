/*  C++ Maths 4
    
    Using the primitives below, write as many type definitions for a transform in 3D space as you can think of.
    Add comments about the constraints and advantages of each the new types, if any.
*/

#include <iostream>

struct Quaternion
{
    float w, x, y, z;
};

struct Vec3
{
    float x, y, z;
};

struct Matrix3x3
{
    float m[3][3];
};

struct Matrix4x4
{
    float m[4][4];
};

struct Transform1
{
    // ?!?
};

int main(int argc, char* argv[])
{
    std::cout << "I know maths, really." << std::endl;

	return 0;
}