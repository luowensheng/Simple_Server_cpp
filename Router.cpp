#include "Router.h"


namespace SimpleServer {

    Router::Router(std::string base_url) {
        this->base_url = base_url;
    }

    Router::~Router() {
    }

    void Router::Get(std::string pattern, HandlerfuncWithArgs handler) {
        this->AddToMapping("GET", pattern, handler);
    }

    void Router::Post(std::string pattern, HandlerfuncWithArgs handler) {
        this->AddToMapping("POST", pattern, handler);
    }
        
    void Router::Put(std::string pattern, HandlerfuncWithArgs handler) {
        this->AddToMapping("PUT", pattern, handler);
    }
        
    void Router::Delete(std::string pattern, HandlerfuncWithArgs handler) {
        this->AddToMapping("DELETE", pattern, handler);
    }

    void Router::Get(std::string pattern, HandlerfuncWithoutArgs handler) {
        this->AddToMapping("GET", pattern, handler);
    }

    void Router::Post(std::string pattern, HandlerfuncWithoutArgs handler) {
        this->AddToMapping("POST", pattern, handler);
    }

    void Router::Put(std::string pattern, HandlerfuncWithoutArgs handler) {
        this->AddToMapping("PUT", pattern, handler);
    }

    void Router::Delete(std::string pattern, HandlerfuncWithoutArgs handler) {
        this->AddToMapping("DELETE", pattern, handler);
    }

    void Router::ShowUrlMapping() {
        int count = 0;
        this->IterMapping([&count](std::string method, std::string pattern, HandlerfuncWithArgs handler) {
            std::cout << ++count << ". " << method << "\t->\t" << pattern << "\t->\t" << &handler << "\n";
        });

        std::cout << "\n";
    }

    void Router::AddSubRouter(std::string newPattern, Router& router) {

        router.IterMapping([newPattern, this](std::string method, std::string pattern, Handler handler) {
            this->AddToMapping(method, pattern + newPattern, handler);
         });
    }

    void Router::IterMapping(std::function<void(std::string method, std::string pattern, Handler handler)> function) {

        for (auto it1 = urlMapping.begin(); it1 != urlMapping.end(); it1++)
        {
            std::string method = it1->first;
            std::map<std::string, Handler> route_mapping = it1->second;

            for (auto map_it = route_mapping.begin(); map_it != route_mapping.end(); map_it++) {

                std::string pattern = map_it->first;
               function(method, pattern, map_it->second);
            }
        }
    }

    void Router::AddToMapping(std::string method, std::string pattern, Handler handler) {
        std::string processPattern = this->ProcessPattern(pattern);
        this->urlMapping[method][this->base_url+ processPattern] = handler;
    }

    std::string Router::ProcessPattern(std::string pattern) {

        if (pattern.at(0) != '/')
            pattern = "/" + pattern;

        size_t length = pattern.length();
        if (length == 0)
            return "/";

        else if (pattern.at(length - 1) == '/')
            return pattern.substr(0, length-2);

        return pattern;
    }

    };
