#include "Server.h"
#include <iostream>

int main()
{
	Server server;

	if (!server.Init())
	{
		return -1;
	}
	server.WaitClient();
	server.Run();
	server.Cleanup();
}