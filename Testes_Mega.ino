#include "LiquidCrystal.h"
#include "DHT.h"
#include "RTClib.h"

LiquidCrystal lcd(53,52,48,49,50,51);
char linha1[17], linha2[17];

RTC_DS1307 rtc;
char dow[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char mon[12][4] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dez"};

#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

char hum[5], temp[5];

void setup() {
  Serial.begin(9600);

  lcd.begin(16,2);

  dht.begin();

  if (!rtc.begin()) {
    Serial.println("RTC not working!");
    while(true);
  } else {
    Serial.println("RTC connected");
  }

  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  delay(2000);

  DateTime now = rtc.now();

  lcd.clear();
  lcd.setCursor(0,0);
  sprintf(linha1, "%02u:%02u %3s %3s/%02u", now.hour(), now.minute(), dow[now.dayOfTheWeek()], mon[now.month()-1], now.day());
  lcd.print(linha1);
  lcd.setCursor(0,1);
  dtostrf(dht.readTemperature(), 4, 1, temp);
  dtostrf(dht.readHumidity(), 4, 1, hum);
  sprintf(linha2, " %s%cC   %s%% ", temp, char(223), hum);
  lcd.print(linha2);

  Serial.println(linha1);
  Serial.println(linha2);
  delay(5000);
}
