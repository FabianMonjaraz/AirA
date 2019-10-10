#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial mySerial(2, 3);  //RX,TX

//  Try https://www.instructables.com/id/Arduino-Esp8266-Post-Data-to-Website/
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH

// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266

char *request = "GET / HTTP/1.1\n\rHost: 192.168.43.220\n\rUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\n\rAccept: text/html,application/xhtml+xml,application/xml;q=0.9,\n\rAccept-Language: es-MX,es;q=0.8,en-US;q=0.5,en;q=0.3\n\rAccept-Encoding: gzip, deflate\n\rConnection: keep-alive\n\rUpgrade-Insecure-Requests: 1\n\rIf-Modified-Since: Mon, 30 Sep 2019 19:02:41 GMT\n\rIf-None-Match: \"29cd-593c9e152adf9-gzip\"\n\rCache-Control: max-age=0";

void sendCommand(char *cmd){
    mySerial.println(cmd);
    while ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
    delay(250);
}
 
void initConnection(){
    sendCommand("AT+RST");
    sendCommand("ATE0");
    sendCommand("AT+GMR");
    sendCommand("AT+CWJAP_CUR=\"Bastion\",\"#4rt0r14s#\"");
    delay(1000);
}
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    mySerial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
    initConnection();
    Serial.println(request);
    Serial.println(strlen(request));
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  mySerial.write( Serial.read() );  }
}
