#include <WiFi.h>

// WiFi credentials
const char* ssid = "TelstraE847BC"; //Wifi SSID; sometimes referred to as WiFi name
const char* password = "69c33uvm4f"; //WiFi Passowrd

// Node.js server details
const char* serverIP = "192.168.0.246";  // Make sure this is the IP of your computer running the server (If you're not sure, type "ipconfig" into windows terminal. It should be under "IPv4 Address", in the "Wireless LAN adapter WiFi" section)
const int serverPort = 2467;
char* loudnessCheck;
int value;

void setup() {
  Serial.begin(9600);

  // Connecting to Wifi router established by variables ssid & password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  value = analogRead(33); //Set to pin plugged into sound sensor
  if (value >= 250) //Change this to make sensor less or more sensitive
    loudnessCheck = "Too Loud!";
  else
    loudnessCheck = "Good Volume.";

  // Send the moisture value to the Node.js server
  sendToServer(loudnessCheck, value);
  delay(250);
}

void sendToServer(const char* loudness, int sensorValue) { //set variables loudnessCheck & value to loudness & sensorValue respectively (avoids issues with scope)
     
  WiFiClient client;   
  if (client.connect(serverIP, serverPort)) {
    // Form the HTTP POST request
    String postData = "sound=" + String(sensorValue) + ", " + loudness;  //Send text displaying relevant data to the server
    client.print(String("POST /update HTTP/1.1\r\n") +
                 "Host: " + serverIP + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded\r\n" +
                 "Content-Length: " + String(postData.length()) + "\r\n\r\n" +
                 postData);

    delay(10);  // Give the server some time to respond

    // Read the server's response
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    client.stop();
  } 
  else {Serial.println("Failed to connect to server"); //If esp cannot connect to the server, print an error to the console.
  }
}