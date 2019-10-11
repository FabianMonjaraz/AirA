int measurePin = A6;
int battLed = 7;
float rawValue = 0;
float voltMeasured = 0;
float chargedBat = 4.2;
float dischargedBat = 3.2;
int stateBat = 0;

void setup(){
    //Serial.begin(9600); 
    pinMode(battLed, OUTPUT);
}

void batteryOutput(int state){
    switch(state){
        case 1: //Half battery or less
            digitalWrite(battLed, LOW);
            delay(50);
            digitalWrite(battLed, HIGH);
            delay(50);
            digitalWrite(battLed, LOW);
            delay(50);
            digitalWrite(battLed, HIGH);
        break;
        case 2: //Almost-dead battery
            digitalWrite(battLed, LOW);
            delay(500);
            digitalWrite(battLed, HIGH);
        break;
        default: //Full battery or more than 50%
            digitalWrite(battLed, HIGH);
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

void loop(){
    batteryCheck();
    delay(1000);
}
