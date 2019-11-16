#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main() 
{
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2,2);
	
	int wsok = WSAStartup(ver, &wsData );
	if(wsok != 0)
	{
		cerr << "Can not Initialize winsock! Quitting" << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == INVALID_SOCKET)
	{
		cerr << "Can not create a socket! Quitting" << endl;
	}
	
	// Bind the ip address and port to the socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //Could also use inet_pton...

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if( clientSocket == INVALID_SOCKET )
	{
		//DO something
		cerr << "Can not create a socket! Quitting" << endl;
		return;
	}
	
	char host[NI_MAXHOST];     //Client's remote name
	char service[NI_MAXSERV];
	
	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if(getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0 )
	{
		cout << host << " connect on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port_ " << 
			ntohs(client.sin_port) << endl;
	}


	// Close listening socket
	closesocket(listening); // do not close that soon...

	// While loop: accept and echo message back to client
	const int BSIZE = 4096;
	char buf[BSIZE];

	while(true)
	{
		ZeroMemory(buf, BSIZE);

		//Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, BSIZE, 0);
		if( bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if( bytesReceived == 0)
		{
			cout << "Client disconnected " << endl;
			break;
		}

		//Echo message back to client
		send(clientSocket, buf, bytesReceived + 1, 0); //automatically sends the terminating \0 char		
	}

	// Close the sock
	closesocket(clientSocket);

	// Cleanup winsock
	WSACleanup();
	return;
	//Sloan Kelly
	//https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
}