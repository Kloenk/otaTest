//
// Created by finn on 2/2/19.
//

#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>

#include "main.h"
#include "web.h"

Servo ser;

WiFiServer server(80);
String header;

void setup() {
    Serial.begin(SERIALBAUT);
    Serial.println("test");

    ser.attach(SERVOPORT);
    ser.write(0);

    WiFi.begin(WIFI_NAME, WIFI_PASS);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connectd, IP address: "); Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("new client");
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                header += c;
                if (c == '\n') {                    // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        if (header.indexOf("GET /ota") >= 0) {
                            client.println(otaUrl());
                        } else if (header.indexOf("POST /otaUpload") >= 0) {
                            client.println("uploading");
                        } else {
                            client.println(rootUrl(WiFi.localIP().toString()));
                        }
                        // The HTTP response ends with another blank line
                        client.println();
                        // Break out of the while loop
                        break;
                    } else { // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        // give the web browser time to receive the data
        delay(1);

        // close the connection:
        client.stop();
        Serial.println("client disonnected");
    }
}