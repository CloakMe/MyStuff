/*  C++ Algorithms 3
    
    Given the struct Vertex, representing vertices in a graph, write a function DFVisit() that traverses the graph and fills 
    the vector result with all connected vertices in Depth First order. Write a comment with the time complexity of your implementation.
    
*/

#include <iostream>
#include <vector>

struct Vertex
{
    std::vector<Vertex*> m_adjacent;
};

void DFVisit(Vertex* v, std::vector<Vertex*>& result)
{
}

int main(int argc, char* argv[])
{
    Vertex a, b, c, d;
    a.m_adjacent.push_back(&b);
    b.m_adjacent.push_back(&c);
    c.m_adjacent.push_back(&d);
    d.m_adjacent.push_back(&b);

    std::vector<Vertex*> visited;
    DFVisit(&d, visited);

    std::cout << "Number of visited vertices: " << visited.size() << std::endl;

	return 0;
}