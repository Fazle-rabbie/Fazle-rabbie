#include <DHTesp.h>
DHTesp dht;
#include <Servo.h>
Servo myservo;

int rled =D1; 
int gled =D5;
int buzzer =D8 ;
int motor =D6;
int fire = D0;
int flame;
int temp;

#define BLYNK_TEMPLATE_ID "TMPL8eXU_mdV"
#define BLYNK_DEVICE_NAME "project"
#define BLYNK_AUTH_TOKEN "QpA42C_ZBwLtGM7nq4fnZru8aWMJMr_A"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define DHTTYPE DHT11 

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
WidgetLCD lcd(V4);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "abcde";
char pass[] = "123456789";
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
digitalWrite(rled,pinValue);
lcd.print(0, 0, "Room Light ON   ");
delay(2000);

}
BLYNK_WRITE(V1)
{
  int pinValue1 = param.asInt(); // assigning incoming value from pin V1 to a variable
digitalWrite(gled,pinValue1);
lcd.print(0, 0, "Garage Light ON    ");
delay(2000);

}
BLYNK_WRITE(V2)
{
  int pinValue2 = param.asInt(); // assigning incoming value from pin V1 to a variable
digitalWrite(motor,pinValue2);
lcd.print(0, 0, "    Fan On      ");
delay(2000);

}
BLYNK_WRITE(V3)
{
  int pinValue3 = param.asInt(); // assigning incoming value from pin V1 to a variable
myservo.write(pinValue3);
lcd.print(0, 0, "  Gate Activated    ");
delay(2000);

}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(rled, OUTPUT);
pinMode(gled, OUTPUT);
pinMode(motor, OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(fire,INPUT);
myservo.attach(D3); 
dht.setup(D4, DHTesp::DHT11); 

//Blynk.begin(auth, ssid, pass);
Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);



}

void loop() {
 Blynk.run();
flame=digitalRead(fire);
 
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();
Serial.println(humidity);

 Blynk.virtualWrite(V5, humidity);
 Blynk.virtualWrite(V6, temperature);

if(flame==LOW){
digitalWrite(buzzer,LOW);
lcd.print(0, 0, "  System Normal     ");
delay(2000);

    }
if(flame==HIGH){
  digitalWrite(buzzer,HIGH);
lcd.print(0, 0, "  Fire Detected     ");
delay(1000);


    }

}
