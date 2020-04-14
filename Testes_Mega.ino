#include <LiquidCrystal.h>
#include "DHT.h"
#include "RTClib.h"

LiquidCrystal lcd(53,52,48,49,50,51);
char linha1[16], linha2[16];

RTC_DS1307 rtc;
char dow[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char mon[12][4] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dez"};

#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int chk;
float hum, temp;

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16,2);
  
  dht.begin();
  
  if (!rtc.begin()) {
    Serial.println("rtc not working");
    while(true);
  } else {
    Serial.println("rtc connected");
  }
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  delay(2000);

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  DateTime now = rtc.now();

  lcd.clear();
  lcd.setCursor(0,0);
  sprintf(linha1, "%02u:%02u %3s %3s/%02u", now.hour(), now.minute(), dow[now.dayOfTheWeek()], mon[now.month()-1], now.day());
  lcd.print(linha1);
  lcd.setCursor(0,1);
  sprintf(linha2, " %s    %2.2f ", "teste", hum);
  lcd.print(linha2);
  //lcd.print(temp);
  //lcd.print(char(223));
  //lcd.print("C   61.2% ");

  Serial.println(linha1);

  Serial.print("Hum: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  //Serial.print("\xC2\xB0");
  //Serial.println("C");
  delay(5000);
}
