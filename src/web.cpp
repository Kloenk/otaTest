//
// Created by finn on 2/2/19.
//

#include "web.h"

String rootUrl(String ip) {
    return "HTTP/1.1 303 See Other\n"
           "Server: kloenk/0.0.1\n"
           "Content-Type: text/html\n"
           "Connection: close\n"
           "Location: http://" + ip + "/ota\n\n";
}

String otaUrl() {
    return "HTTP/1.1 200 Ok \n"
           "Server: kloenk/0.0.1\n"
           "Connection: close\n"
           "Content-Type: text/html\n\n"
           "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>OTA</title></header></head><body><h1>OTA</h1><form id=\""
           "upload_form\" action=\"/otaUpload\" enctype=\"multipart/form-data\" method=\"POST\"><input name=\"update\" "
           "type=\"file\"/> <input type=\"submit\" value=\"Update\"/></form></body></html>";
}