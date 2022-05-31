#pragma once
#include <WS2tcpip.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
#include <functional>

namespace SimpleServer {

	class Socket
	{

	public:	
		Socket();
		Socket(int address_family, int address_type = SOCK_STREAM, int protocol = 0);
		~Socket();

		void Bind(int port);
		void Listen();
		void Listen(std::function<void(void)> onInit);

		Socket* Accept();
		std::string Read();
		void Close();
		void PrintInfo();
		void SendAll(std::string response, int bytesReceived);

		void static Init_Winsock();

		private:
			SOCKET sock;
			sockaddr_in address;
			int addressFamily = AF_INET;
			char outputBuffer[4096];
			const int bufferSize = 4096;
	};


}

