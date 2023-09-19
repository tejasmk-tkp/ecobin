#include <dht11.h>
//#include <Adafruit_Sensor.h>

//#include <dht11.h>

#define pH 8          // pH sensor analog pin
#define DHT11PIN 4           // DHT11 sensor digital pin
#define smoke A0           // Gas sensor analog pin
#define buzzer 13            // Buzzer pin

dht11 DHT11;

int buf[100];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pH, INPUT);
  pinMode(DHT11PIN, INPUT);
  pinMode(smoke, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //pH Sensor
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(pH);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }

  float avgValue=0;
  
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  
  float phValue= (float) avgValue*(5.0/1024/6); //convert the analog into millivolt
  
  phValue=3.5*phValue;
  Serial.print("pH: ");
  Serial.println(phValue);

  delay(3000);

  //DHT11

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  delay(3000);

  //smoke sensor

  int air_qValue = analogRead(smoke);

  Serial.print("AirQuality Value: ");
  Serial.println(air_qValue, DEC); 

  delay(3000);

}
