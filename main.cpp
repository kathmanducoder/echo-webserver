/*
 * A simple web server in C++ that responds back with contents of the incoming
 * HTTP header in its 200 OK response body.
 */

#include <exception>
#include <iostream>
#include <unistd.h>
using namespace std;

#include "HTTPServer.h"

#define HTTP_SERVER_PORT 8080

int main() {
    try {
        HTTPServer http_server(HTTP_SERVER_PORT);
        /* Start the server */
        http_server.start();
    } catch(const exception& e) {
        cerr << "echo_webserver : shutting down the server." << endl;
    }
    return 0;
}
