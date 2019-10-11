#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial wifiAntenna(2, 3);  //RX,TX

//  Try https://www.instructables.com/id/Arduino-Esp8266-Post-Data-to-Website/
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH

String ssid = "ADIP-DFMF";
String pass = "bhuq0e3z";
String host = "10.42.0.33";
String port = "80";
    
void resetAntenna(){
    wifiAntenna.println("AT+RST");
    delay(1000);
    if(wifiAntenna.find("OK")) 
        Serial.println("Module Reset");
}


void connectWifi(){
    wifiAntenna.println("AT+CIPSTATUS");
    if(wifiAntenna.find("2")||wifiAntenna.find("3")||wifiAntenna.find("4")) 
        Serial.println("Connected to " + ssid);
    else{
        String cmd = "AT+CWJAP_CUR=\"" + ssid + "\",\"" + pass + "\"";
        wifiAntenna.println(cmd);
        delay(4000);
        if(wifiAntenna.find("OK")) 
            Serial.println("Connected to " + ssid);
        else{
            Serial.println("Error connecting to "+ ssid +". Retrying..."); 
            connectWifi();
        }
    }

}

int setTCPConnection(){
    wifiAntenna.println("AT+CIPSTATUS");
    if(wifiAntenna.find("3")){ 
        Serial.println("TCP Connection Established");
        return 1;
    }
    else{
        wifiAntenna.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + port );
        delay(250);
        if(wifiAntenna.find("OK")){ Serial.println("TCP Connection Established"); return 1;}
        else{ Serial.println("Error setting TCP Connection."); return 0; }
    }
}

int getResource(String resource){
    String request = "GET " + resource + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
    int lengthRequest = request.length();
    String cmd = "AT+CIPSEND=";
    cmd.concat(lengthRequest);

    Serial.println("Sending:");
    Serial.println(cmd);
    Serial.println(request);
    wifiAntenna.println(cmd);
    delay(100);

    if(wifiAntenna.find(">")){ 
        wifiAntenna.println(request);
    }
    delay(1000);
}

void setup() {
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    wifiAntenna.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
    resetAntenna();
    connectWifi();
    while(!setTCPConnection());
    
    getResource("/medicion/7.7/3.3");
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( wifiAntenna.available() )   {  Serial.write( wifiAntenna.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  wifiAntenna.write( Serial.read() );  }
}
