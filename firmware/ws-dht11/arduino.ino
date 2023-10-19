#include <WiFi.h>

// WiFi credentials
const char* ssid = "your ssid";
const char* password = "your wifi password";

// Node.js server details
const char* serverIP = "123.456.789.012";  // IPv4 of your computer (type "ipconfig" in terminal if you're not sure what it is)
const int serverPort = 2467;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { //If wifi is NOT connected, print "Connecting to wifi" to console every second. Once wifi is connected print "Connected to wifi"
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int value = analogRead(33);  // Read sensor value

  Serial.print("Sound value: ");
  Serial.println(value);
 
  if (value >= 300) //Adjust this number depending on how loud you want your class to be and how your board is positioned
    Serial.println("Too loud!");
  else
    Serial.println("Keep it quiet");

  // Send the value to the Node.js server
  sendToServer(value);
  Serial.println("Value sent: " + String(value));

  delay(250);
}

void sendToServer(int soundValue) {
  WiFiClient client;

  if (client.connect(serverIP, serverPort)) {
    // Form the HTTP POST request
    String postData = "sound=" + String(soundValue);
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
  else {Serial.println("Failed to connect to server");
  }
}