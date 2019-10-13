String buffer  = "";
boolean dataRcvd = false;
String resource = "/medicion/";
String request;
String host = "10.42.0.33";
int sizeRequest = 0;
float LvlCO = 0.0;
float LvlPM25 = 0.0;
String cmd;
void setup(){
    Serial.begin(9600);
    buffer.reserve(12);
    pinMode(13, OUTPUT);
}

void loop(){
    if(dataRcvd == true){
        LvlCO = atof(buffer.substring(0,buffer.indexOf("/")).c_str()); 
        LvlPM25 = atof(buffer.substring(buffer.indexOf("/")+1).c_str()); 
        resource += buffer;
        request = "GET " + resource + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";

        sizeRequest = request.length();
        cmd = "AT+CIPSEND=";
        cmd.concat(sizeRequest);

        Serial.println(cmd);
        Serial.println(request);
        Serial.print("CO: ");
        Serial.print(LvlCO);
        Serial.print("; PM2.5: ");
        Serial.println(LvlPM25);
        Serial.println();

        dataRcvd = false;
        resource = "/medicion/";
        buffer = "";
    }
    /*if(dataRcvd == true){
        Serial.println(buffer.length());
        dataRcvd = false;
    }*/
}
void serialEvent(){
    //If message ends with or without an enter
    //buffer = Serial.readStringUntil('\n');
    buffer = Serial.readString();
    dataRcvd = true;
}
