#include "Server.h"

void Server::Run()
{// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2,2);
	
	int wsok = WSAStartup(ver, &wsData );
	if(wsok != 0)
	{
		std::cerr << "Can not Initialize winsock! Quitting" << std::endl;
        return;
	}

	//create a master socket  
    SOCKET masterSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(masterSocket == INVALID_SOCKET)
	{
		std::cerr << "Can not create a socket! Quitting" << std::endl;
        return;
	}
     
    int code;
    //set master socket to allow multiple connections ,  
    //this is just a good habit, it will work without this  
	int opt = TRUE;
	code = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    if( code < 0 )   
    {   
        std::cerr << "Can not set socket options! Quitting" << std::endl;  
        return;
    }   
		
	// Bind the ip address and port to the socket
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(Constants::PORT);
	address.sin_addr.S_un.S_addr = INADDR_ANY; //Could also use inet_pton...
    //address.sin_addr.s_addr = INADDR_ANY;
	int addressLen = sizeof(address);

	code = bind(masterSocket, (sockaddr*)&address, sizeof(address));
	if(code)
	{
		std::cerr << "Could not bind ip and port to the socket!" << std::endl;
        return;
	}

	// Tell Winsock the socket is for listening
	code = listen(masterSocket, Constants::MAX_PENDING_CONNECTIONS); //SOMAXCONN
	if (code != 0)
	{
		std::cerr << "Could not set up listen on the socket! Quitting" << std::endl;
        return;
	}

	//==============================
	//set of socket descriptors  
    fd_set readfds;
	int max_sd, i, client_socket[Constants::MAX_CLIENTS], sd, activity, newSocket;
    int socketCount = 0;
	for (i = 0; i < Constants::MAX_CLIENTS; i++)   
    {   
        client_socket[i] = 0;   
    }   

	char *message = "ECHO Daemon v1.0 \r\n"; 
	char buffer[Constants::BUF_SIZE];  //data buffer of 1K  

	while(true)   
    {   
        //clear the socket set  
        FD_ZERO(&readfds);   
     
        //add master socket to set  
        FD_SET(masterSocket, &readfds);   
        max_sd = masterSocket;

        //add child sockets to set
        for ( i = 0 ; i < Constants::MAX_CLIENTS ; i++)   
        {   
            //socket descriptor  
            sd = client_socket[i];   
                 
            //if valid socket descriptor then add to read list  
            if(sd > 0)   
                FD_SET( sd , &readfds);   
                 
            //highest file descriptor number, need it for the select function  
            if(sd > max_sd)
                max_sd = sd;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR))   
        {
            std::cerr << "Waiting for an activity on one of the sockets failed!" << std::endl;
        }

        //If something happened on the master socket,  
        //then its an incoming connection
        int fdResult = FD_ISSET(masterSocket, &readfds);
        bool flag = socketCount < Constants::MAX_CLIENTS ? true : false;
        if (fdResult != 0 && flag)
        {
			newSocket = accept(masterSocket,  (sockaddr *)&address, (socklen_t*)&addressLen);
            if ( newSocket < 0 )
            {   
				std::cerr << "Could not accept new connection! Quitting" << std::endl;
                return;
            }   
             
            //inform user of socket number - used in send and receive commands  
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n",
				newSocket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port) );
           
            //send new connection greeting message  
            if( send(newSocket, message, strlen(message), 0) != strlen(message) )   
            {   
                std::cerr << "Could not send greeting message" << std::endl;   
            }   
                 
            printf("Welcome message sent successfully\n");   
            //add new socket to array of sockets  
            for (i = 0; i < Constants::MAX_CLIENTS; i++)   
            {   
                //if position is empty  
                if( client_socket[i] == 0 )   
                {   
                    client_socket[i] = newSocket;
                    ++socketCount;
                    printf("Adding to list of sockets as %d\n" , i);                         
                    break;   
                }   
            }   
        }// incoming connection 
             
        //else its some IO operation on some other socket 
        for (i = 0; i < Constants::MAX_CLIENTS; i++)   
        {
            sd = client_socket[i];   
                 
            if (FD_ISSET( sd , &readfds))   
            {   
                //Check if it was for closing , and also read the  
                //incoming message
                int bytesReceived = recv(sd, buffer, Constants::BUF_SIZE-1, 0);

				if( bytesReceived == SOCKET_ERROR)
				{
                    int code = WSAGetLastError();
                                        
                    if(code == WSAECONNABORTED)
                    {
                        printf("Number of maximum connections was reached.\n");
                        getpeername(sd, (sockaddr*)&address, (socklen_t*)&addressLen);
                        printf("Client with ip %s and port %d has disconnected while being in the queue of pending connections.\n" ,  
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                        //Close the socket and mark as 0 in list for reuse
                        closesocket(sd);
                        --socketCount;
                        client_socket[i] = 0;
                    }else
                    {
                        std::cerr << "err code = " << code << std::endl;
                        char *s = NULL;
                        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                                        NULL, code,
                                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                        (LPSTR)&s, 0, NULL);
                        std::cerr << s;
                        LocalFree(s);
                        return;
                    }

				}else if( bytesReceived == 0)
				{
					//Somebody disconnected, get his details and print  
                    getpeername(sd, (sockaddr*)&address, (socklen_t*)&addressLen);   
                    printf("Host disconnected , ip %s , port %d \n" ,  
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    closesocket(sd);
                    --socketCount;
                    client_socket[i] = 0;
				}                     
                else
                {
                    //set the string terminating NULL byte on the end  
                    //of the data read
                    buffer[bytesReceived] = '\0';
                    std::string bufferToString(buffer);

                    // Echo back the result message 
                    // CmdWrapper process all commands at once using the GeoCmd class.
                    // GeoCmd class process one command at a time
                    // depending on the command type.
                    // For each command type the Database class is used
                    // to process the required server operations
                    std::string result = GeoCmd::CmdWrapper(bufferToString);

                    if(result.find("exit") != std::string::npos)
                    {
                        getpeername(sd, (sockaddr*)&address, (socklen_t*)&addressLen);  
                        std::string adr(inet_ntoa(address.sin_addr));
                        if(adr.compare("127.0.0.1")==0)
                            return;
                    }

                    if(!result.empty())
                        send(sd, result.c_str(), result.size()+1, 0 );
                    
                }   
            }  //end if bytesReceived
        }//end IO operation on some other socket
    }//end while
}

Server::~Server()
{
    // Cleanup winsock
	int wsok = WSACleanup();
    if(wsok != 0)
	{
		std::cerr << "Could not cleanup winsock!" << std::endl;
	}
}

