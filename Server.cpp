#include "Server.h"


namespace SimpleServer{

	Server::Server(int buffer_size) : Router() {
		this->bufferSize = buffer_size;
		Socket::Init_Winsock();

	}

	Server::~Server() {
		std::cout << "Server Closed\n";
		WSACleanup();
	}

	void Server::Run(int port) {

				
		Socket serverSocket(AF_INET);
		serverSocket.Bind(port);
		serverSocket.Listen([]() {std::cout << "Server is listening\n"; });
		do {
			Socket* clientsocket = serverSocket.Accept();
			std::cout << "Received client" << "\n";
			//clientsocket->PrintInfo();
			try
			{
				this->HandleConnection(*clientsocket);
			}
			catch (const std::exception&)
			{
				clientsocket->Close();
				//serverSocket.Close();
			}
			clientsocket->Close();
			//serverSocket.Close();

		} while (true);

		
	}

	void Server::HandleConnection(Socket& clientsocket) {
		
		std::string msg = clientsocket.Read();
		std::cout << msg << std::endl;

		if (msg=="") 
			throw std::exception("Either client sent nothing or parsing failed\n");
		
		RequestDetails request(msg);
		ResponseWriter responseWriter;
		this->ProcessRequest(responseWriter, request);
		clientsocket.SendAll(responseWriter.GetResponse(), responseWriter.GetContentLength());

    }

	void Server::ProcessRequest(ResponseWriter& rw, RequestDetails& r) {
		
		std::string method = r.GetMethod();
		std::string uri = r.GetUri();

		auto handler = this->GetHandlerForUrl(method, uri);
		std::cout << "Handler found for method [" << method << "] and uri [" << uri << "]\n";

		this->urlMapping[method][uri].Process(rw, r);

	}

	Handler Server::GetHandlerForUrl(std::string method, std::string uri) {

		std::cout << "Getting results for method [" << method << "] and uri [" << uri << "]\n";
		
		auto it = this->urlMapping.find(method);
		
		if (it == urlMapping.end()) {
			auto msg = "Invalid method [" + method + "]\n";
			throw std::exception(msg.c_str());
		}

		
		std::string processed_uri = this->ProcessPattern(uri);
		
		auto methodMap = it->second;
	    
		auto it2 = methodMap.find(processed_uri);

		if (it2 == methodMap.end()) {
			throw std::exception("Either client sent nothing or parsing failed\n");
		}
		else {
			return it2->second;
		}
	}

}