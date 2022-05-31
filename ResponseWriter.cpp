#include "ResponseWriter.h"


std::string quote(std::string str) {
	return "\""+str+"\"";
}

namespace SimpleServer {

    ResponseWriter::ResponseWriter() {

    }

    ResponseWriter::~ResponseWriter() {

    }

    void ResponseWriter::SetContent(std::string value) {
		this->content = value;
    };

	void ResponseWriter::SetItem(std::string key, std::string value) {
		this->headers[key] = value;
	}

	std::string ResponseWriter::GetItem(std::string key) {
		std::string value = this->headers[key];
		return value;
	}

	void ResponseWriter::SetProtocol(std::string value) {
		this->protocol = value;
	}

	void ResponseWriter::SetStatusCode(std::string value) {
		this->statusCode = value;
	}

	void ResponseWriter::SetStatus(std::string value) {
		this->status = value;
	}

	void ResponseWriter::SetContentType(std::string value) {
		this->contentType = value;
	}

	void ResponseWriter::SetJsonContent(std::map<std::string, std::string> json_map) {

		std::string jsonStr = "{";
		
		bool add_comma = false;
		
		for (auto it = json_map.begin(); it != json_map.end(); it++) {
			if (add_comma)
				jsonStr += ",";
			jsonStr += quote(it->first) + ": " + quote(it->second) + ",";
			add_comma = true;
		}
		
		jsonStr += "}";

		this->SetJsonContent(jsonStr);

	}

	void ResponseWriter::SetJsonContent(std::string value) {

		this->SetContentType("application/json");
		this->SetContent(value);
	
	}
	size_t ResponseWriter::GetContentLength() {
		return this->GetResponse().length();
	}

	std::string ResponseWriter::GetResponse() {

		std::string headerStr = "";
		for (auto it = this->headers.begin(); it != this->headers.end(); it++)
		{
			std::string key = it->first;
			std::string value = it->second;
			headerStr += key + ": " + value + "\r\n";
		}
		std::string response =  this->protocol + " " + this->statusCode + " " + this->status + "\r\n"
			    + "Content-Type: " + this->contentType + "\r\n" 
			    + headerStr + "\r\n\r\n"
			    + this->content
			;
		std::cout << "\n\nSending:\n" << response << "\n\n";
		return response;
	}

	std::string ResponseWriter::ToString() {
		return this->GetResponse();
	}

}