#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace SimpleServer{
	
	class RequestDetails
	{
	public:
		RequestDetails(std::string& receivedStr);
		RequestDetails(const char* receivedStr);
		~RequestDetails();
		std::string ToJson();

		std::string GetMethod();
		std::string GetUri();
		std::string GetProtocol();
		std::map<std::string, std::string> GetHeaders();

	private:
		void ParseRequest(std::string& receivedStr);
		void ParseRequestLine(std::string& requestLine);
		void ParseOptionalHeaders(std::vector<std::string>& headersVec);

		std::string method;
		std::string uri;
		std::string protocol;
		std::map<std::string, std::string> headers;


	};

}
