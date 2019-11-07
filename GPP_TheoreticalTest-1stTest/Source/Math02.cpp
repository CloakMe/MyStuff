/*  C++ Maths 2
    
    Given an origin O and 2 points A and B in 3D, write a function that calculates the parameters of a rotation that will rotate point A in the direction of point B regarding the origin.
*/

#include <iostream>

struct Vec3
{
    float x, y, z;
};

void CalcRotation(const Vec3 &o, const Vec3 &a, const Vec3 &b, Vec3 &axis, float &angle)
{
	Vec3 d;
	d.x = -a.x+o.x;
	d.y = -a.y+o.y;
	d.z = -a.z+o.z;

	Vec3 p;
	p.x = -b.x+o.x;
	p.y = -b.y+o.y;
	p.z = -b.z+o.z;

	//d = normalize(d);
	//double yaw = Math.Atan2(d.X, d.Y);
	//double pitch = Math.Atan2(d.Z, Math.Sqrt((d.X * d.X) + (d.Y * d.Y)));
	//p.rotateXYZ(pitch, yaw, 0); //Roll == 0
}

int main(int argc, char* argv[])
{
    Vec3 o = {2, 2, 2};
    Vec3 a = {1, 1, 1};
    Vec3 b = {0.5f, 0, 1.5f};

    Vec3 axis;
    float angle;
    CalcRotation(o, a, b, axis, angle);
    std::cout << "Axis: " << axis.x << ", " << axis.y << ", " << axis.z << " angle: " << angle << std::endl;

	return 0;
}