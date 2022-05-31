#pragma once
#include <iostream>
#include <map>

namespace SimpleServer {

	class ResponseWriter
	{
		public:

			ResponseWriter();
			~ResponseWriter();

			void SetItem(std::string key, std::string value);
			std::string GetItem (std::string key);
			void SetProtocol(std::string value);
			void SetStatusCode(std::string value);
			void SetStatus(std::string value);
			void SetContentType(std::string value);
			void SetContent(std::string value);
			void SetJsonContent(std::string value);
			void SetJsonContent(std::map<std::string, std::string> json_map);

			size_t GetContentLength();
			std::string GetResponse();
			std::string ToString();

		private:
			std::string protocol = "HTTP/1.1";
			std::string statusCode = "200";
			std::string status = "OK";
			std::string contentType = "text/html";
			std::string content = "";
			std::map<std::string, std::string> headers;
	};



}

