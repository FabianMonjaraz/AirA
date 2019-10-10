int measurePin = A0;
int battLed = 4
float rawValue = 0;
float voltMeasured = 0;
float chargedBat = 4.2;
float dischargedBat = 3.2;
float percent = 0.0;
int stateBat = 0;
int aux = 0;

void setup(){
    Serial.begin(9600); 
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
            delay(200);
        break;
        case 2: //Almost-dead battery
            digitalWrite(battLed, LOW);
            delay(200);
            digitalWrite(battLed, HIGH);
            delay(200);
        break
        default: //Full battery or more than 50%
            digitalWrite(battLed, HIGH);
        break;
    }
}

void loop(){
    rawValue = analogRead(measurePin);
    voltMeasured = (rawValue + 0.5) * 5.0 / 1024.0;
    percent = map(voltMeasured, dischargedBat, chargedBat, 0.0, 100.0); //Convert from voltage to percentage.

    batteryOutput(stateBat);

    if (percent >= 51.0)
        batteryOutput(0);
    else if (percent >= 15)
        batteryOutput(1);
    else
        batteryOutput(2);

    /*Serial.print("Raw Value: ");
    Serial.print(rawValue);
    Serial.print("; Voltage: ");
    Serial.println(voltMeasured);*/
    delay(1000);
}
