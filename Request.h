#ifndef REQUEST_H
#define REQUEST_H

#include <string>


/**
 * @brief The Request struct represents a network request with incoming and outgoing IPs, 
 * a time duration for processing, and (optionally) a job type.
 * 
 * This struct is used by the LoadBalancer to queue and assign tasks to WebServers.
 */
struct Request {
    std::string ip_in;   ///< The incoming IP address of the request.
    std::string ip_out;  ///< The outgoing IP address of the request.
    int time;            ///< The time required to process the request in clock cycles.
    // char job_type; 
    
    Request();
    Request(std::string ip_in, std::string ip_out, int time, char job_type);
    std::string create_ip();
};

#endif
