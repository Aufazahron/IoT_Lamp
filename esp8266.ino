// #include <WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid     = "Aufazahron.dev";
const char* password = "sayasukajuga";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "on";
String output27State = "on";
String output28State = "on";
String output29State = "on";

// Assign output variables to GPIO pins
const int output26 = 5;
const int output27 = 4;
const int output28 = 0;
const int output29 = 2;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output28, OUTPUT);
  pinMode(output29, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output28, LOW);
  digitalWrite(output29, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
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
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "off";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "on";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "off";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "on";
              digitalWrite(output27, LOW);
            } else if (header.indexOf("GET /28/on") >= 0) {
              Serial.println("GPIO 28 on");
              output28State = "off";
              digitalWrite(output28, HIGH);
            } else if (header.indexOf("GET /28/off") >= 0) {
              Serial.println("GPIO 28 off");
              output28State = "on";
              digitalWrite(output28, LOW);
            } else if (header.indexOf("GET /29/on") >= 0) {
              Serial.println("GPIO 29 on");
              output29State = "off";
              digitalWrite(output29, HIGH);
            } else if (header.indexOf("GET /29/off") >= 0) {
              Serial.println("GPIO 29 off");
              output29State = "on";
              digitalWrite(output29, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button {border: none; color: white; padding: 16px 25px;");
            client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer; border-radius: 10px}");
            client.println(".blue{background-color: #0079FF} .red{background-color: #D71313} .green{background-color:#4CAF50}");
            client.println(".bo{border: 2px #0079FF solid} .ro{border: 2px #D71313 solid} .go{border: 2px #4CAF50 solid} .blo{border: 2px black solid}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>PAPER LIGHT ART</h1>");
            
            client.println("<h2>3D Horse Art Paper Cut Light Box</h2>");
            if (output26State=="off" & output27State=="off" & output28State=="off") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/off.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="on" & output27State=="off" & output28State=="off") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/red.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="on" & output27State=="on" & output28State=="off") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/lime.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="on" & output27State=="on" & output28State=="on") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/all.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="off" & output27State=="on" & output28State=="on") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/cyan.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="off" & output27State=="off" & output28State=="on") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/blue.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="off" & output27State=="on" & output28State=="off") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/green.png\" style=\"width: 50%\"><br>");
            } else if (output26State=="on" & output27State=="off" & output28State=="on") {
              client.println("<img src=\"http://192.168.4.17:8080/pict/purple.png\" style=\"width: 50%\"><br>");
            }

            // Display current state, and ON/OFF buttons for GPIO 26  
            // client.println("<p>State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="on") {
              client.println("<a href=\"/26/on\"><button class=\"button button2 ro\">OFF</button></a>");
            } else {
              client.println("<a href=\"/26/off\"><button class=\"button red\">ON</button></a>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            // client.println("<p>State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="on") {
              client.println("<a href=\"/27/on\"><button class=\"button button2 go\">OFF</button></a>");
            } else {
              client.println("<a href=\"/27/off\"><button class=\"button green\">ON</button></a>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27  
            // client.println("<p>State " + output28State + "</p>");
            // If the output28State is off, it displays the ON button       
            if (output28State=="on") {
              client.println("<a href=\"/28/on\"><button class=\"button button2 bo\">OFF</button></a>");
            } else {
              client.println("<a href=\"/28/off\"><button class=\"button blue\">ON</button></a>");
            }

            // LED 2
            // Display current state, and ON/OFF buttons for GPIO 27  
            // client.println("<p>State " + output29State + "</p>");
            client.println("<h2>Tamsis Light Paper Art Painting</h2>");

            if (output29State=="on"){
              client.println("<img src=\"http://192.168.4.17:8080/pict/Tms1.png\" style=\"width: 50%\"><br>");
            } else{
              client.println("<img src=\"http://192.168.4.17:8080/pict/Tms2.png\" style=\"width: 50%\"><br>");
            }

            // If the output29State is off, it displays the ON button       
            if (output29State=="on") {
              client.println("<p><a href=\"/29/on\"><button class=\"button button2 blo\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/29/off\"><button class=\"button green\">ON</button></a></p>");
            }
            client.println("</body></html>");
            
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
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
