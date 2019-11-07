/*  C++ Advanced 5
    
    Add code that will make the template function add() work for objects of class Vec3. 
    In this case it should call the Vec3::add() method.
*/

#include <iostream>

template <typename T> T add(T a, T b)
{
	if (std::is_same<T, Vec3>::value) 
	{ 
		const Vec3* a1 = reinterpret_cast<Vec3*>(&a);
		const Vec3* b1 = reinterpret_cast<Vec3*>(&b);
		Vec3* result = &(a1->add(*b1));
		T* newResult = reinterpret_cast<T*>(result);
		return *newResult;
	}else
	{
		return T(a + b);
	}
}

class Vec3
{
public:
    explicit Vec3(float _x = 0.f, float _y = 0.f, float _z = 0.f): m_x(_x), m_y(_y), m_z(_z) {}

    Vec3 add(const Vec3& v) const { return Vec3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z); }

    float operator+(const Vec3& v) const { return m_x + m_y + m_z + v.m_x + v.m_y + v.m_z; }

    float x() { return m_x; }
    float y() { return m_y; }
    float z() { return m_z; }
private:
    float m_x, m_y, m_z;
};

int main(int argc, char* argv[])
{
    Vec3 a(1, 2, 3), b(4, 5, 6);
    Vec3 c;
    // Uncomment the following line to test your solution
    c = add<Vec3>(a, b);
	int g = add<int>(5, 7);
    std::cout << c.x() << " " << c.y() << " " << c.z() << std::endl;

	return 0;
}