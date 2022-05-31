#include "RequestDetails.h"


std::vector<std::string>  vecop(std::function<void(std::vector<std::string>&, int&)> func, int end, int start = 0) {

	std::vector<std::string> vec = {};

	for (int i = start; i < end; i++)
		func(vec, i);

	return vec;
}

std::vector<std::string>  vecop_with_end(std::function<void(std::vector<std::string>&, int&)> func, std::function<void(std::vector<std::string>&)> onEnd, int end, int start = 0) {

	std::vector<std::string> vec = vecop(func, end, start);
	onEnd(vec);
	return vec;
}


std::vector<std::string> split_str(std::string m) {

	std::string str = "";
	int n = m.length();
	return vecop_with_end(
		[&](std::vector<std::string>& vec, int& i) {
			int i2 = i + 1;
			if (m[i] == '\r' && m[i2] == '\n') {
				vec.push_back(str);
				str = "";
				i += 1;
			}
			else {
				str += m[i];
				if (i == n - 2) {
					str += m[i2];
				}
			}
		},
		[&str](std::vector<std::string>& vec) {vec.push_back(str); },
			n
	  );
}

namespace SimpleServer {

    RequestDetails::RequestDetails(std::string& receivedStr) {
		this->ParseRequest(receivedStr);
    }

	RequestDetails::RequestDetails(const char* receivedStr) {
		std::string str (receivedStr);
		this->ParseRequest(str);
	}

    RequestDetails::~RequestDetails() {

    }

	std::string RequestDetails::ToJson() {
		throw std::exception("Not implemented");
	}

	std::string RequestDetails::GetMethod() {
		return this->method;
	}

	std::string RequestDetails::GetUri() {
		return this->uri;
	}

	std::string RequestDetails::GetProtocol() {
		return this->protocol;
	}

	std::map<std::string, std::string> RequestDetails::GetHeaders() {
		return this->headers;
	}


	void RequestDetails::ParseRequest(std::string &receivedStr) {

		std::vector<std::string>  headerVec = split_str(receivedStr);
		std::string request_line = headerVec.at(0);
		std::vector<std::string> optional_headers = vecop([&](std::vector<std::string>& vec, int& i) {vec.push_back(headerVec.at(i)); }, headerVec.size(), 1);
		
		ParseRequestLine(request_line);
		ParseOptionalHeaders(optional_headers);
	}

	void RequestDetails::ParseRequestLine(std::string& requestLine) {

		std::string str = "";
		int n = requestLine.length();
		std::vector<std::string> arr = vecop_with_end(

			[&](std::vector<std::string>& vec, int& i) {
				if (requestLine[i] == ' ') {
					vec.push_back(str);
					str = "";
				}
				else {
					str += requestLine[i];
					if (i == n ) {
						str += requestLine[i + 1];
					}
				}
			},
			[&str](std::vector<std::string>& vec) {vec.push_back(str); },
				n
		);

		this->method = arr[0];
		this->uri = arr[1];
		this->protocol = arr[2];

	}

	void RequestDetails::ParseOptionalHeaders(std::vector<std::string>& headersVec) {
		
		for (auto it = headersVec.begin(); it != headersVec.end(); it++) {
		
			bool found_colon = false;
			std::string line = (*it);
			std::string str = "";
			int n = line.length();
			
			auto result = vecop_with_end(

				[&](std::vector<std::string>& vec, int& i) {

					if (line[i] == ':' && !found_colon) {
						found_colon = true;
						vec.push_back(str);
						str = "";
						i += 1;
					}
					else if (line[i]!=' ')
						str += line[i];
				},
				[&str](std::vector<std::string>& vec) {vec.push_back(str); },
					n
				);
			if (result.size() != 2) continue;
		//	std::cout << " [" << result[0] << "] - [" << result[1] << "] " << std::endl;

			this->headers[result[0]] = result[1];
		}
	}



}