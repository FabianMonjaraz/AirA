int DANGER = 2;
int WARNING = 1;
int NORMAL = 0;
int CO[3] = {8,9,10}; //NORMAL,WARNING,DANGER
int PM25[3] = {4,5,6}; //NORMAL,WARNING,DANGER
int LimPM25[3] = {25,10}; // ug/m^3 https://www.who.int/es/news-room/fact-sheets/detail/ambient-(outdoor)-air-quality-and-health
int LimCO[3] = {200,100}; // ppm http://www.aire.cdmx.gob.mx/default.php?opc=%27ZaBhnmI=&dc=%27Zw==

float LvlCO = 204.0;
float LvlPM25 = 9.0;

int BAT = 7;
int stateBat = 0;
float dischargedBat = 3.2;
float chargedBat = 4.2;
float voltMeasured = 0;
float rawValue = 0;
int measurePin = A6;

void batteryOutput(int state){
    switch(state){
        case 1: //Half battery or less
            digitalWrite(BAT, LOW);
            delay(50);
            digitalWrite(BAT, HIGH);
            delay(50);
            digitalWrite(BAT, LOW);
            delay(50);
            digitalWrite(BAT, HIGH);
        break;
        case 2: //Almost-dead battery
            digitalWrite(BAT, LOW);
            delay(500);
            digitalWrite(BAT, HIGH);
        break;
        default: //Full battery or more than 50%
            digitalWrite(BAT, HIGH);
        break;
    }
}

void batteryCheck(){
    rawValue = analogRead(measurePin);
    voltMeasured = (rawValue + 0.5) * 5.0 / 1024.0;
    batteryOutput(stateBat);

    if (voltMeasured  >= 3.8)
        batteryOutput(0);
    else if (voltMeasured >= 3.4)
        batteryOutput(1);
    else
        batteryOutput(2);
    /*Serial.print("Raw Value: ");
    Serial.print(rawValue);
    Serial.print("; Voltage: ");
    Serial.print(voltMeasured);*/
}

void outputLedsCO(int level){

    if(digitalRead(CO[level]) != HIGH){
        digitalWrite(CO[DANGER], LOW);
        digitalWrite(CO[WARNING], LOW);
        digitalWrite(CO[NORMAL], LOW);
        digitalWrite(CO[level], HIGH);
    }
}

void outputLedsPM25(int level){
    if(digitalRead(PM25[level]) != HIGH){
        digitalWrite(PM25[DANGER], LOW);
        digitalWrite(PM25[WARNING], LOW);
        digitalWrite(PM25[NORMAL], LOW);
        digitalWrite(PM25[level], HIGH);
    }
}

void measure(){
    if(LvlCO >= (float)LimCO[0])
        outputLedsCO(DANGER);
    else if(LvlCO >= (float)LimCO[1])
        outputLedsCO(WARNING);
    else
        outputLedsCO(NORMAL);

    if(LvlPM25 >= (float)LimPM25[0])
        outputLedsPM25(DANGER);
    else if(LvlPM25 >= (float)LimPM25[1])
        outputLedsPM25(WARNING);
    else
        outputLedsPM25(NORMAL);
}

void setup(){
    pinMode(CO[DANGER], OUTPUT);
    pinMode(CO[WARNING], OUTPUT);
    pinMode(CO[NORMAL], OUTPUT);
    pinMode(PM25[DANGER], OUTPUT);
    pinMode(PM25[WARNING], OUTPUT);
    pinMode(PM25[NORMAL], OUTPUT);
    pinMode(BAT, OUTPUT);
}

void loop(){
    measure();
    batteryCheck();
    delay(1000);
}
