#include <iostream>
#include "Server.h"

#pragma comment (lib, "ws2_32.lib")

void main() 
{
    bool flag = Database::ReadLocations("GeoLocations.txt");
	if(!flag)
	{
		std::cerr << "Can not Initialize GeoLocations! Quitting" << std::endl;
        return;
	}
    
    Server server;
    server.Run();	

    printf("Object count: %d\n", Database::ObjectCount());
    printf("Loc count: %d\n", Database::LocationCount());
}
