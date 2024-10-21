#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @brief The WebServer class simulates a server that processes network requests.
 * 
 * A WebServer can handle a single request at a time, and tracks the time left to process
 * the current request. It also keeps track of its idle time when not processing requests.
 */
class WebServer {
public:
    Request curr_request;  ///< The current request being processed by the server.
    int time_left;         ///< The remaining time to finish the current request.
    int time_idle;         ///< The amount of time the server has been idle.
    bool busy;             ///< Indicates whether the server is currently busy.

    WebServer();
    void create_request(Request& request);
    void process_request(int time);
    void finish_request();
};

#endif
