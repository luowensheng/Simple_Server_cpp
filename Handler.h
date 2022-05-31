#pragma once
#include <functional>
#include "RequestDetails.h"
#include "ResponseWriter.h"

namespace SimpleServer {
	
	using HandlerfuncWithArgs = std::function<void(ResponseWriter& rw, RequestDetails& r)>;
	using HandlerfuncWithoutArgs = std::function<std::string(void)>;

	class Handler {

	public:
		Handler();

		Handler(HandlerfuncWithArgs handlerFunc);
		Handler(HandlerfuncWithoutArgs handlerFunc);

		void operator() (ResponseWriter& rw, RequestDetails& r);
		void Process(ResponseWriter& rw, RequestDetails& r);

	private:
		HandlerfuncWithArgs handlerFunc;
	};
}
