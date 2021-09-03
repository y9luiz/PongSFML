#include <iostream>
#include "Net/game_server.h"
#include <chrono>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

int main( int argc, char * argv[])
{
	GameServer server(5000,false);
	std::cout << "Waiting for 2 clients ...\n";
	server.waitForClients();
	std::cout << "notifying clients\n";
	server.notifyClients();
	std::cout << "Running game server ...\n";
	//server.receivePacketsFromClients();
	//std::cout << "Done!\n";
	server.run();

	return 0;
}


