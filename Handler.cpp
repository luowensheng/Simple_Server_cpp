#include "Handler.h"

namespace SimpleServer {

	Handler::Handler() {
	}


	Handler::Handler(HandlerfuncWithArgs handlerFunc) {
		this->handlerFunc = handlerFunc;
	}

	Handler::Handler(HandlerfuncWithoutArgs handlerFunc) {
		this->handlerFunc = [=](ResponseWriter& rw, RequestDetails& r) {
			rw.SetContent(handlerFunc());
		};
	}

	void Handler::operator() (ResponseWriter& rw, RequestDetails& r) {
		this->handlerFunc(rw, r);
	}

	void Handler::Process (ResponseWriter& rw, RequestDetails& r) {
		this->handlerFunc(rw, r);
	}

}