#pragma once
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "Game.h"


#pragma comment(lib, "ws2_32.lib")

class Server
{
private:
	SOCKET listenSock;
	SOCKET socks[2];
	Game game;
public:
	Server();
	~Server();


	bool Init();
	void WaitClient();
	void Run();
	void Cleanup();

};
