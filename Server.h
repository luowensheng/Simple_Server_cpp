#pragma once
#include "Router.h"
#include <iostream>
#include "Socket.h"

namespace SimpleServer {
	

	class Server: public Router
	{
	public:
		Server(int buffer_size = 1024);
		~Server();
		void Run(int port = 54000);
	
	private:
		void HandleConnection(Socket& client);
		void ProcessRequest(ResponseWriter& rw, RequestDetails& r);
		Handler GetHandlerForUrl(std::string method, std::string uri);
		int bufferSize;
		SOCKET listening;
		sockaddr_in hint;
	};

}



