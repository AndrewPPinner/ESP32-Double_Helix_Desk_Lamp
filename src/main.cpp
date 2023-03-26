#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESP32Time.h>

#include <html.h>
#include <js.h>

#define LED_PIN 14
#define LED_COUNT 11

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
AsyncWebServer server(80);
ESP32Time rtc;

const char* ssid = "Diya_Is_Great!";
const char* password = "123456789";
int r = 182;
int g = 24;
int b = 226;
bool spiralAction = false;
bool spiralRandomAction = false;
bool dotAction = false;
bool dateSet = false;
bool birthday = false;
bool birthdayOverride = false;

void main_Page(AsyncWebServerRequest *request) {
  if (dateSet){
    if (birthday) {
      request->send(200, "text/html", bDayHtml() + bDayJS());
    }
    request->send(200, "text/html", MainHtml() + MainJS());
  }
  request->send(200, "text/html", SetDateHtml() + SetDateJS());
}

void set_date(AsyncWebServerRequest *request) {
  rtc.setTime(
    0,0,0,
    request->getParam("date")->value().substring(8).toInt(),
    request->getParam("date")->value().substring(5,8).toInt(),
    request->getParam("date")->value().substring(0,4).toInt()
  );
  dateSet = true;
  request->send(200);
}
  

void primary_LED(AsyncWebServerRequest *request){
  spiralRandomAction = false;
  spiralAction = false;
  dotAction = false;
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.Color(request->getParam("r")->value().toInt(), request->getParam("g")->value().toInt(), request->getParam("b")->value().toInt()));
  }
  strip.show();
  r = request->getParam("r")->value().toInt();
  g = request->getParam("g")->value().toInt();
  b = request->getParam("b")->value().toInt();
  request->send(200);
}

void random_LED(AsyncWebServerRequest *request){
  spiralAction = false;
  spiralRandomAction = false;
  dotAction = false;
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.Color(random(0,255), random(0,255), random(0,255)));
  }
  strip.show();
  request->send(200);
}

void random_spiral_LED(AsyncWebServerRequest *request){
  spiralAction = false;
  spiralRandomAction = true;
  dotAction = false;
  request->send(200);
}

void spiral_LED(AsyncWebServerRequest *request){
  spiralRandomAction = false;
  spiralAction = true;
  dotAction = false;
  request->send(200);
}

void xmas_LED(AsyncWebServerRequest *request){
  spiralRandomAction = false;
  spiralAction = false;
  dotAction = false;
  for (int i = 0; i < 3; i++)
  {
    strip.setPixelColor(i, strip.Color(30, 255, 27));

  }
  for (int i = 3; i < 6; i++)
  {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
    for (int i = 6; i < 11; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  
  strip.show();
  request->send(200);
}

void clear_LED(AsyncWebServerRequest *request){
  spiralRandomAction = false;
  spiralAction = false;
  dotAction = false;
  strip.show();
  strip.clear();
  request->send(200);
}

void LED_brightness(AsyncWebServerRequest *request){
  strip.setBrightness(request->getParam("b")->value().toInt());
  strip.show();
  request->send(200, "text/html", String(strip.getBrightness()));
}

void dot_LED(AsyncWebServerRequest *request){
  dotAction = true;
  spiralRandomAction = false;
  spiralAction = false;
  request->send(200);
}

void resetBday(AsyncWebServerRequest *request){
  birthday = false;
  birthdayOverride = true;
  request->send(200);
}

void setup() {
  WiFi.softAP(ssid, password);
  Serial.begin(115200);
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request){main_Page(request);});
  server.on("/primary", HTTP_GET, [] (AsyncWebServerRequest *request){primary_LED(request);});
  server.on("/random", HTTP_GET, [] (AsyncWebServerRequest *request){random_LED(request);});
  server.on("/random_spiral", HTTP_GET, [] (AsyncWebServerRequest *request){random_spiral_LED(request);});
  server.on("/spiral",  HTTP_GET, [] (AsyncWebServerRequest *request){spiral_LED(request);});
  server.on("/xmas",  HTTP_GET, [] (AsyncWebServerRequest *request){xmas_LED(request);});
  server.on("/clear",  HTTP_GET, [] (AsyncWebServerRequest *request){clear_LED(request);});
  server.on("/brightness",  HTTP_GET, [] (AsyncWebServerRequest *request){LED_brightness(request);});
  server.on("/dot",  HTTP_GET, [] (AsyncWebServerRequest *request){dot_LED(request);});
  server.on("/setDate",  HTTP_GET, [] (AsyncWebServerRequest *request){set_date(request);});
  server.on("/resetPage",  HTTP_GET, [] (AsyncWebServerRequest *request){resetBday(request);});

  AsyncElegantOTA.begin(&server, &strip);
  server.begin();

  strip.begin();
  strip.show();
  strip.clear();
  strip.setBrightness(50);
}

void loop() {
  if (spiralAction) {
     for (int i = 0; i <= LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show();
      delay(200);
    }
    delay(10);
    for (int i = LED_COUNT; i >= 0; i--)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
      delay(200);
    }
  }
  if (spiralRandomAction) {
    for (int i = 0; i <= LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(random(0,255), random(0,255), random(0,255)));
      strip.show();
      delay(200);
    }
    delay(10);
    for (int i = LED_COUNT; i >= 0; i--)
    {
      strip.setPixelColor(i, strip.Color(random(0,255), random(0,255), random(0,255)));
      strip.show();
      delay(200);
    }
  }
  if (dotAction) {
    for (int i = 0; i <= LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.setPixelColor(i + 1, strip.Color(r, g, b));
      strip.setPixelColor(i - 1, strip.Color(0, 0, 0));
      strip.show();
      delay(100);
    }
  }
  if(!birthdayOverride && rtc.getMonth() == 7 && rtc.getDay() == 17) {
    birthday = true;
    //add something attention grabbing!
  } else {birthday = false;}
  if(!birthdayOverride && rtc.getMonth() == 7 && rtc.getDay() == 18) {
    birthdayOverride = false;
  }
}