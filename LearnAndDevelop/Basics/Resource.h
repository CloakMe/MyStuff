#include <vector>
#include <iostream>
using namespace std;

class Resource
{
public:
    Resource() = delete;
    Resource(int size, int val);
    Resource(const Resource& rhs);
    Resource& operator=(const Resource& rhs);
    Resource(Resource&& rhs) noexcept;
    Resource& operator=(Resource&& rhs) noexcept;

    int& operator[](int i);

    Resource add(const Resource& other);
    ~Resource();
    friend ostream& operator<<(ostream& o, const Resource& a);
private:
    int * data;
	int size;
};

Resource Resource::add(const Resource& other)
{
    Resource temp(size + other.size, 0);
    
    for(int i = 0; i<size; i++)
        temp[i] = data[i];

    for(int i = 0; i<other.size; i++)
        temp[size +i] = other.data[i];
    
    return temp;
}

int& Resource::operator[](int i)
{
    if(i > -1 && i < size)
        return data[i];
    else if(size == 0)
        throw;
    else
        return data[size-1];
}

std::ostream& operator<<(std::ostream& o, const Resource& a)
{
	int i = 0;
    while (i < a.size)
    {
        o << a.data[i] <<" ";
		i++;
    }
    return o;
}


Resource::Resource(int size, int val)
{
	this->size = size;
    data = new int[size];
    for( int i = 0; i < size; i++)
    {
        data[i] = val;
    }
}

Resource::Resource(const Resource& rhs)
{
    cout << "copy constructor" << endl;
	size = rhs.size;
	data = new int[size];
	
	for (int i = 0; i < size; i++)
		data[i] = rhs.data[i];
}

Resource& Resource::operator=(const Resource& rhs)
{
    cout << "copy assignment operator" << endl; 
    if(&rhs == this)
    {
        return *this;
    }

	size = rhs.size;
	if (data)
		delete[] data;
	data = new int[size];

	for (int i = 0; i < size; i++)
		data[i] = rhs.data[i];
	
    return *this;
}

Resource::Resource(Resource&& rhs) noexcept
{
    cout << "move constructor" << endl;
    data = rhs.data;
	size = rhs.size;

	rhs.data = nullptr;
}

Resource& Resource::operator=(Resource&& rhs) noexcept
{
    cout << "move assignment operator" << endl;
	if (data)
		delete[] data;
    data = rhs.data;
	size = rhs.size;

	rhs.data = nullptr;
    return *this;
}

Resource::~Resource()
{
	if(data)
		delete [] data;
}

void RuleOfFive()
{
	Resource resource(2, 10);
	cout << resource << endl;
	Resource other = resource;
	other[3] = 3;
	other[0] = 4;
	cout << other << endl;
	cout << resource << endl;
	Resource newResource = other.add(resource);
	cout << newResource << endl;
	newResource = resource.add(other);
	cout << newResource << endl;
	newResource = Resource(5, 5);
	cout << newResource << endl;
}