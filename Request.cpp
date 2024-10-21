#include "Request.h"
#include <sstream>

/**
 * @brief Constructs a new Request object.
 * 
 * Generates random incoming (`ip_in`) and outgoing (`ip_out`) IP addresses 
 * and assigns a random time (between 1 and 100) for processing the request.
 */
Request::Request(){
    ip_in = create_ip();
    ip_out = create_ip();
    time = rand() % 100 + 1;
}

/**
 * @brief Generates a random IP address in the format XXX.XXX.XXX.XXX.
 * 
 * Each segment of the IP address is a randomly generated integer between 0 and 255.
 * 
 * @return std::string A randomly generated IP address.
 */
// function made using AI
std::string Request::create_ip() {
    std::stringstream ip;
    for (int i = 0; i < 4; ++i) {
        ip << (rand() % 256);
        if (i < 3) ip << ".";
    }
    return ip.str();
}

// Request::Request(std::string ip_in, std::string ip_out, int time, char job_type)
//     : ip_in(ip_in), ip_out(ip_out), time(time) {}
