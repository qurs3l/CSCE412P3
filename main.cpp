#include <iostream>
#include <cstdlib>  
#include <ctime> 
#include "LoadBalancer.h"
#include "Request.h"
#include "WebServer.h"

int main() {
    std::srand(std::time(0));           
    int maxServers = 25;  
    int requestThreshold = 15;    
    int maxIdleTime = 20;         
    
    
    int simulationTime;   
    int initialServers;    

    std::cerr << "Enter similation time: ";
    std::cin >> simulationTime;

    std::cout << "\n";

    std::cerr << "Enter initial servers: ";
    std::cin >> initialServers;

    LoadBalancer loadBalancer(initialServers, initialServers*100, maxServers, requestThreshold, maxIdleTime);

    std::cout << "\n--- Start Queue Size: "<< loadBalancer.requests.size() << " ---\n";

    // Main simulation loop
    for (int time = 0; time < simulationTime; time += 1) {
        std::cout << "\n--- Time: " << time << " ---\n";
        loadBalancer.create_requests();
        loadBalancer.dispatch_requests();
        loadBalancer.process_requests(time);
        loadBalancer.adjust_servers();
        std::cout << "Request Queue Size:  " << loadBalancer.requests.size() << "\n";
    }

    std::cout << "\n--- End Queue Size: "<< loadBalancer.requests.size() << " ---\n";
    return 0;
}
