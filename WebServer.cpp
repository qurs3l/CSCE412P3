#include "WebServer.h"
#include <iostream>

/**
 * @brief Constructs a new WebServer object.
 * 
 * Initializes the server in an idle state.
 */
WebServer::WebServer(){}

/**
 * @brief Assigns a request to the server and marks it as busy.
 * 
 * @param request The request to be processed by the server. 
 * The request contains the incoming IP, outgoing IP, and the time required for processing.
 */
void WebServer::create_request(Request& request) {
    curr_request = request;
    time_left = request.time;
    busy = true;
    std::cout << "WebServer received request from " << curr_request.ip_in 
              << " to " << curr_request.ip_out << " for " << curr_request.time 
              << " clock cycles.\n";
}

/**
 * @brief Processes the current request for the specified time.
 * 
 * Decreases the time left on the request by the given time unit. If the request 
 * is finished (time_left <= 0), the server marks the request as completed. If no request 
 * is being processed, the server remains idle and increments its idle time counter.
 * 
 * @param time The amount of time to process the request.
 */
void WebServer::process_request(int time) {
    if (busy) {
        time_left -= time;
        if (time_left <= 0) {
            finish_request();
        } else {
            std::cout << "WebServer is processing... " << time_left << " cycles left.\n";
        }
    } else {
        std::cout << "WebServer is idle.\n";
        this->time_idle++;
    }
}

/**
 * @brief Marks the current request as finished and sets the server to idle.
 * 
 * Prints a message indicating that the server has completed the request.
 */
void WebServer::finish_request() {
    busy = false;
    std::cout << "WebServer finished processing request from " 
              << curr_request.ip_in << " to " << curr_request.ip_out << ".\n";
}
