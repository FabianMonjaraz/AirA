int DANGER = 0;
int WARNING = 1;
int NORMAL = 2;
int CO[3] = {12,11,10}; //DANGER,WARNING,NORMAL
int PM25[3] = {9,8,7}; //DANGER,WARNING,NORMAL
int BAT = 6;
int LimPM25[3] = {25,10}; // ug/m^3 https://www.who.int/es/news-room/fact-sheets/detail/ambient-(outdoor)-air-quality-and-health
int LimCO[3] = {200,100}; // ppm http://www.aire.cdmx.gob.mx/default.php?opc=%27ZaBhnmI=&dc=%27Zw==

float LvlCO = 73.0;
float LvlPM25 = 15.0;

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
}
