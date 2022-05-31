#include "Socket.h"


namespace SimpleServer {

    Socket::Socket() {
    }
    Socket::Socket(int address_family, int address_type, int protocol) {
        
        addressFamily = address_family;
        sock = socket(addressFamily, address_type, protocol);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Can't create a socket! Quitting\n";
             throw std::exception("Can't create a socket! Quitting\n");
            //exit(1);
        }
        std::cout << "Created a socket!  \n";
    }


    Socket::~Socket() {
        closesocket(sock);
        std::cout << "socket cleaned  \n";
        shutdown(sock, SD_SEND);
    }

    void Socket::Bind(int port) {

        address.sin_family = addressFamily;
        address.sin_port = htons(port);
        address.sin_addr.S_un.S_addr = INADDR_ANY;

        bind(sock, (sockaddr*)(&address), sizeof(address));
    }

    void Socket::Listen() {

        listen(sock, SOMAXCONN);
    }

    void Socket::Listen(std::function<void(void)> onInit) {

        this->Listen();
        onInit();
    }

    std::string Socket::Read() {

        ZeroMemory(outputBuffer, bufferSize);
        int bytesReceived = recv(sock, outputBuffer, bufferSize, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            std::exception("Error in recv(). Quitting\n");
          //  exit(1);
        }
        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected\n";
        }
        return outputBuffer;
    }


    Socket* Socket::Accept() {

        Socket* clientsocket =  new Socket();        

        int clientSize = sizeof(clientsocket->address);
        clientsocket->sock = accept(sock,
                                     (sockaddr*)&clientsocket->address,
                                     &clientSize
                                     );
        std::cout << " GOTCLIENT on port " << "\n";

        char host[NI_MAXHOST]; // client remote name
        char service[NI_MAXHOST]; // service (i.e. port) the client is connect on

        ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST)
        ZeroMemory(service, NI_MAXHOST);

        if (getnameinfo((sockaddr*)&clientsocket->address, sizeof(clientsocket->address), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
        {
            std::cout << host << " connected on port " << service << "\n";
        }
        else
        {
            inet_ntop(AF_INET, &clientsocket->address.sin_addr, host, NI_MAXHOST);
            std::cout << host << " connected on port " << ntohs(clientsocket->address.sin_port) << "\n";
        }

        return clientsocket;
    }

    void Socket::Close() {
         this->~Socket();
    }

    void Socket::SendAll(std::string response, int bytesReceived) {
         
        ZeroMemory(outputBuffer, bufferSize);
         strcpy_s(outputBuffer, response.c_str());
         send(sock, outputBuffer, bytesReceived , 0);
    }
    void Socket::PrintInfo() {
        std::cout << "socket at port:" << (this->address.sin_port)<< ", adrdress size: "<<(sizeof(this->address)) << ", address:" << (this->address.sin_family) << " and socket:" << (this->sock) << "\n";
    }

    void  Socket::Init_Winsock() {

        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);

        int wsOk = WSAStartup(ver, &wsData);
        //std::cout <<"windows is ok value is " << wsOk <<"\n";

        if (wsOk != 0) {
            std::cout << "Can't Initialize winsock! Quitting\n";
            exit(1);
            //   throw std::exception("Can't Initialize winsock! Quitting\n");
        }

        std::cout << "Initialized winsock!  \n";
    }


}
   
