String data[4] = {"50/7.12","115.4/15","200/25","74/17117};
void setup(){
    Serial.begin(9600);
}
void loop(){
    Serial.write(data[0].c_str());
    delay(2000);
    Serial.write(data[1].c_str());
    delay(2000);
    Serial.write(data[2].c_str());
    delay(2000);
    Serial.write(data[3].c_str());
    delay(2000);
}
