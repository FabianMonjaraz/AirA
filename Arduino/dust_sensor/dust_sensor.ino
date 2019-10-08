int measurePin = 0;
int ledPower = 12;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float pm25=0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
}


void loop(){
  digitalWrite(ledPower,HIGH); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,LOW); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 3.3V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = 5*voMeasured/1024;


  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;

  // Ecuacion linear de PM 2.5
  pm25=(calcVoltage-0.0356)*120000;

  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);

  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);

  Serial.print(" - Dust Density(mg/m3): ");
  Serial.println(dustDensity);

  Serial.print(" - PM 0.5(particulas/0.01 pie3): ");
  Serial.println(pm05);
  delay(1000);
}
