/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <website.h>
#include <Servo.h>

// Replace with your network credentials
const char *ssid = "SSID";
const char *password = "PASSWORD";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
int output1State = 0;
int output2State = 0;
int output3State = 0;
int output4State = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup()
{

  Serial.begin(115200);
  servo1.attach(2);
  servo1.write(0);
  servo2.attach(0);
  servo2.write(0);
  servo3.attach(4);
  servo3.write(0);
  servo4.attach(5);
  servo4.write(0);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /1/on") >= 0)
            {
              servo1.write(180);
              output1State = 1;
            }
            else if (header.indexOf("GET /1/off") >= 0)
            {
              servo1.write(0);
              output1State = 0;
            }
            else if (header.indexOf("GET /2/on") >= 0)
            {
              servo2.write(180);
              output2State = 1;
            }
            else if (header.indexOf("GET /2/off") >= 0)
            {
              servo2.write(0);
              output2State = 0;
            }
            else if (header.indexOf("GET /3/on") >= 0)
            {
              servo3.write(180);
              output3State = 1;
            }
            else if (header.indexOf("GET /3/off") >= 0)
            {
              servo3.write(0);
              output3State = 0;
            }
            else if (header.indexOf("GET /4/on") >= 0)
            {
              servo4.write(180);
              output4State = 1;
            }
            else if (header.indexOf("GET /4/off") >= 0)
            {
              servo4.write(0);
              output4State = 0;
            }

            // Display the HTML web page
            client.println(web_header);

            client.println("<p>Servo 1</p>");
            if (output1State == 0)
            {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>Servo 2</p>");
            if (output2State == 0)
            {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>Servo 3</p>");
            if (output3State == 0)
            {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>Servo 4</p>");
            if (output4State == 0)
            {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println(web_endtag);
            client.println();

            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}