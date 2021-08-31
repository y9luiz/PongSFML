#include <iostream>
#include "Net/game_server.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main( int argc, char * argv[])
{
	GameServer server;
	while (true)
	{
		if (server.checkForNewConnections())
		{	
			std::cout << "connected\n";
		}
		std::this_thread::sleep_for(1ms);
	}
	return 0;
}