#include <iostream>
#include "Net/game_server.h"
#include <chrono>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

int main( int argc, char * argv[])
{
	GameServer server(5000,true);
	std::cout << "Waiting for 2 clients ...\n";
	server.waitForClients();
	std::cout << "notifying clients\n";
	server.notifyClients();
	std::cout << "Receiving packets ...\n";
	server.receivePacketsFromClients();
	std::cout << "Done!\n";
	return 0;
}


