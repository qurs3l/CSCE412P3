#include "WebServer.h"
#include "Request.h"
#include "LoadBalancer.h"
#include <string>
#include <iostream>
#include <algorithm> 
using namespace std;

/**
 * @brief Constructs a LoadBalancer with the specified number of servers and requests.
 * 
 * @param numServers Initial number of servers.
 * @param numRequests Initial number of requests to populate the request queue.
 * @param maxServers Maximum number of servers allowed to be created.
 * @param requestThreshold The threshold of requests to decide when to add more servers.
 * @param maxIdle The maximum idle time allowed for servers before they are deallocated.
 */
LoadBalancer::LoadBalancer(int numServers, int numRequests, int maxServers, int requestThreshold, int maxIdle){
    this->max_servers = maxServers;
    this->max_idle = maxIdle;
    this->request_threshold = requestThreshold;

    for(int i = 0; i < numRequests; i+=1){
        this->requests.push(Request());
    }

    for(int i = 0; i < numServers; i+=1){
        this->servers.push_back(new WebServer());
    }   
}

/**
 * @brief Destructor for the LoadBalancer class, deletes all dynamically allocated servers.
 */
LoadBalancer::~LoadBalancer(){
    for(WebServer *server : this->servers){
        delete server;
    }
}

/**
 * @brief Creates a new request with a 10% chance on each call and adds it to the request queue.
 */
void LoadBalancer::create_requests(){
    if((rand() % 100) <= 10){
        this->requests.push(Request());
        cout << "Added new request" << endl;
    }
}

/**
 * @brief Dispatches requests from the queue to available servers. 
 * 
 * If a server is not busy and there are requests in the queue, the server is assigned the top request.
 */
void LoadBalancer::dispatch_requests(){
    int i = 0;
    for(WebServer *server : this->servers){
        if(!server->busy && !requests.empty()){
            server->create_request(requests.front());
            cout << "Request assigned to server" << i + 1 <<  endl;
            requests.pop();
        }
        i+=1;
    }
}

/**
 * @brief Processes requests on all servers for a given time unit.
 * 
 * @param time The amount of time to process each request.
 */
void LoadBalancer::process_requests(int time){
    for(WebServer *server : this->servers){
        server->process_request(time);
    }
}

/**
 * @brief Adjusts the number of servers based on the size of the request queue and server idle times.
 * 
 * - Adds new servers if the request queue size exceeds the number of servers, up to the maximum server limit.
 * - Deallocates (deletes) servers that have been idle for longer than the allowed maximum idle time.
 */
void LoadBalancer::adjust_servers(){
    /* check if the request queue is larger than the servers vector. if it is, then add new servers.
     the number of servers you add is min(RQ.size - servers.size, maxServers)
    then loop that many times and add servers
    */
    if(requests.size() > servers.size()){
        int size_difference = requests.size() - servers.size();
        int new_servers = std::min(size_difference, max_servers);

        for(int i = 0; i < new_servers; i+=1){
            this->servers.push_back(new WebServer());
             std::cout << "Allocated new server" << std::endl;
        }
    }

    /*
    iterate through the servers vector and check it’s idle count. 
    if it’s idle count is larger than the maxIdle then deallocate (delete) it. 
    ou will have to use vector iterators bc you are deleting pointers 
    */
    for (auto it = servers.begin(); it != servers.end(); /* no increment here */) {
        WebServer* server = *it;
        
        if (server->time_idle > max_idle) {
            std::cout << "Deleting server with idle time: " << server->time_idle << std::endl;

            delete server;

            it = servers.erase(it);
        } else {
            ++it; 
        }
    }

}