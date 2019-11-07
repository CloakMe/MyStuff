/*  C++ Advanced 6
    
    The method Entity::PerceptSurroundings() runs an order of magnitude slower than it should.
    Fix the performance problems.
	Hint: There are 5 problems in total, of which 2 are logical, 2 are language specific and 1 is mathematical in nature.
*/

#include <iostream>
#include <vector>
#include <random>

#define Len 50  //*

class Entity
{
public:
    static const float PERCEPTION_RANGE;
    Entity(float x, float y, float z, bool perceptible, bool blind)
        :m_x(x), m_y(y), m_z(z), m_perceptible(perceptible), m_blind(blind) 
	{
	}

    float DistanceTo(Entity &other);

protected:
    float m_x, m_y, m_z;
public:
    bool m_perceptible;
    bool m_blind;    
};

const float Entity::PERCEPTION_RANGE = 20.0f;

float Entity::DistanceTo(Entity &other)
{
    return sqrt( pow(m_x - other.m_x, 2) + 
				pow(m_y - other.m_y, 2) + 
				pow(m_z - other.m_z, 2)
			   );  //*
}

class Player : public Entity
{
	std::vector<Entity*> m_perceptedObjects;
public:
	Player(float x, float y, float z, bool perceptible, bool blind) : Entity(x, y, z, perceptible, blind)
	{
		m_perceptedObjects.reserve(Len); 
	}

	void PerceptSurroundings(std::vector<Entity*> allObjects);

	std::vector<Entity*> &GetPerceptedObjects() { return m_perceptedObjects; }
};

void Player::PerceptSurroundings(std::vector<Entity*> allObjects)
{
    m_perceptedObjects.clear();

    for (unsigned i = 0; i < allObjects.size(); ++i)
    {
        Entity objectToCheck = *allObjects[i];
        if (!m_blind)
        {
            float distance = DistanceTo(objectToCheck);

            if (distance < PERCEPTION_RANGE && 
                objectToCheck.m_perceptible)
            {
                m_perceptedObjects.push_back(allObjects[i]);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> randBool(0, 1);
    std::uniform_real_distribution<float> randCoord(-20.0f, 20.0f);

    std::vector<Entity*> objects;
    for (int i = 0; i < Len; ++i)
        objects.push_back(new Entity(randCoord(rng), randCoord(rng), randCoord(rng), randBool(rng) != 0, randBool(rng) != 0));

    Player player(10.f, 10.f, 10.f, true, false);

    //for (int i = 0; i < 100000; ++i)  why ?
    player.PerceptSurroundings(objects);

    std::cout << "Number of objects the player can see: " << player.GetPerceptedObjects().size() << std::endl;

    for (int i = 0; i < Len; ++i)
        delete objects[i];

    objects.clear();

	return 0;
}