/*  C++ Maths 1
    
    Write a function WithinMaxAngle that checks if the angle between two arbitrary vectors is less than MAX_DEGREES.
*/

#include <iostream>
#include <math.h>
# define M_PI           3.14159265358979323846  /* pi */

struct Vec3
{
    float x, y, z;
};

const float MAX_DEGREES = 43.f;

bool WithinMaxAngle(const Vec3 &v1, const Vec3 &v2)
{

	float dotProduct = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	float norms = sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z) * 
		sqrt(v2.x*v2.x + v2.y*v2.y + v2.z*v2.z);

	float angle = 0;
	if(norms == 0.0f)
		return angle<MAX_DEGREES ? true : false;

	angle = acos(dotProduct/norms) * 180 / M_PI;
    return angle<MAX_DEGREES ? true : false;
}

int main(int argc, char* argv[])
{
    Vec3 a = {0, 0, 0};
    Vec3 b = {0.3f, 1, 1};
    Vec3 c = {0, 0.0f, 0};
	std::cout << std::boolalpha;
    std::cout << WithinMaxAngle(a, b) << std::endl;
    std::cout << WithinMaxAngle(a, c) << std::endl;

	return 0;
}