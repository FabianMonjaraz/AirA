//Pins
int measurePMSensor = A0;
int measureCOSensor = A1;
int LedPMPower = 12;
int LedCOPower = 11;

//Variables for the PM2.5 sensor
unsigned int pm_samplingTime = 280;
unsigned int pm_deltatime = 40;
unsigned int pm_SleepTime = 9680;
float pm_voMeasured = 0;
float pm_calcVoltage = 0;
float pm_dustDensity = 0; //PM2.5 level

//Variables for the CO sensor
unsigned int co_samplingTime = 50;
unsigned int co_burningSeconds = 60;
unsigned int co_coolingSeconds = 90;

float getPMLevels(){
  digitalWrite(LedPMPower,HIGH);
  delayMicroseconds(pm_samplingTime);

  pm_voMeasured = analogRead(measurePMSensor);

  delayMicroseconds(pm_deltatime);
  digitalWrite(LedPMPower,LOW);
  delayMicroseconds(pm_SleepTime);

  pm_calcVoltage = pm_voMeasured*(5.0/1024);
  pm_dustDensity = 0.17*pm_calcVoltage-0.1;

  if( pm_dustDensity < 0)
    pm_dustDensity = 0.00;
  
  return pm_dustDensity;
}



void setup(){
  Serial.begin(9600);
  pinMode(LedPMPower,OUTPUT);
  pinMode(LedCOPower,OUTPUT);
  digitalWrite(LedCOPower, HIGH);
}


void loop(){
  getPMLevels();
  delay(1000);
}
