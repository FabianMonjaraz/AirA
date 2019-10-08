int ALTO = 0;
int MEDIO = 1;
int BAJO = 2;
int CO[3] = {12,11,10}; //ALTO,MEDIO,BAJO
int PM25[3] = {9,8,7}; //ALTO,MEDIO,BAJO
int BAT = 6;
int LimPM25[3] = {25,10,0}; // ug/m^3 https://www.who.int/es/news-room/fact-sheets/detail/ambient-(outdoor)-air-quality-and-health
int LimCO[3] = {200,100,0}; // ppm http://www.aire.cdmx.gob.mx/default.php?opc=%27ZaBhnmI=&dc=%27Zw==

float LvlCO = 73.0;
float LvlPM25 = 15.0;


void changeLed(int LedDown, int LedUp){
    digitalWrite(ledDown, LOW);        
    digitalWrite(ledUp, HIGH);        
}
void measure(int COLevel, int PMLevel){    
    if(
}

void setup(){
    pinMode(CO[ALTO], OUTPUT);
    pinMode(CO[MEDIO], OUTPUT);
    pinMode(CO[BAJO], OUTPUT);
    pinMode(PM25[ALTO], OUTPUT);
    pinMode(PM25[MEDIO], OUTPUT);
    pinMode(PM25[BAJO], OUTPUT);
    pinMode(BAT, OUTPUT);
}

void loop(){
}
