#pragma once
#include <iostream>
#include <map>
#include  "Handler.h"
#include <string>
#include <functional>

namespace SimpleServer {

    class Router {
    public:
        Router(std::string base_url = "");
        ~Router();

        void Get(std::string pattern, HandlerfuncWithArgs handler);
        void Post(std::string pattern, HandlerfuncWithArgs handler);
        void Put(std::string pattern, HandlerfuncWithArgs handler);
        void Delete(std::string pattern, HandlerfuncWithArgs handler);

        void Get(std::string pattern, HandlerfuncWithoutArgs handler);
        void Post(std::string pattern, HandlerfuncWithoutArgs handler);
        void Put(std::string pattern, HandlerfuncWithoutArgs handler);
        void Delete(std::string pattern, HandlerfuncWithoutArgs handler);

        void AddSubRouter(std::string pattern, Router& router);
        void ShowUrlMapping();
        void IterMapping(std::function<void(std::string method, std::string pattern, Handler handler)>);

        std::string ProcessPattern(std::string pattern);
        std::map<std::string, std::map<std::string, Handler>> urlMapping;

    private:
        std::string base_url;
        void AddToMapping(std::string method, std::string pattern, Handler handler);

    };

}

