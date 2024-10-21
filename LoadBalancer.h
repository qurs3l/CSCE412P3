#include "WebServer.h"
#include "Request.h"
#include <string>
#include <queue>
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

/**
 * @brief The LoadBalancer class manages a set of WebServers and dispatches incoming requests to them.
 * 
 * This class handles the creation of new requests, dispatches them to available servers,
 * processes the requests, and dynamically adjusts the number of servers based on load and idle time.
 */
class LoadBalancer{
    public:
        int max_servers;          ///< Maximum number of servers allowed.
        int request_threshold;    ///< Threshold of request queue size to trigger server addition.
        int max_idle;             ///< Maximum allowed idle time before a server is removed.
        int curr_idle;            ///< Current count of idle servers.
        std::queue<Request> requests;  ///< Queue of incoming requests to be processed.
        std::vector<WebServer*> servers;  ///< List of active servers

        LoadBalancer();
        LoadBalancer(int numServers, int numRequests, int maxServers, int requestThreshold, int maxIdle);
        ~LoadBalancer();

        void create_requests();
        void dispatch_requests();
        void process_requests(int time);
        void adjust_servers();
};

#endif