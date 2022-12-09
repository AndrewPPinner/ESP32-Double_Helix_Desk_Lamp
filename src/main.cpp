#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#include <html.h>
#include <js.h>

#define LED_PIN 14
#define LED_COUNT 300

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
AsyncWebServer server(80);
const char* ssid = "Celeste";
const char* password = "Andrew1021";
int r = 182;
int g = 24;
int b = 226;
bool spiralAction = false;

void main_Page(AsyncWebServerRequest *request) {
  request->send(200, "text/html", HTML() + JS());
}

void primary_LED(AsyncWebServerRequest *request){
  spiralAction = false;
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
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.Color(random(0,255), random(0,255), random(0,255)));
  }
  strip.show();
  request->send(200);
}

void spiral_LED(AsyncWebServerRequest *request){
  spiralAction = true;
  request->send(200);
}

void xmas_LED(AsyncWebServerRequest *request){
  spiralAction = false;
  for (int i = 0; i < 100; i++)
  {
    strip.setPixelColor(i, strip.Color(30, 255, 27));

  }
  for (int i = 100; i < 200; i++)
  {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
    for (int i = 200; i < 300; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  
  strip.show();
  request->send(200);
}

void clear_LED(AsyncWebServerRequest *request){
  spiralAction = false;
  strip.show();
  strip.clear();
  request->send(200);
}

void setup() {
  WiFi.begin(ssid, password);
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request){main_Page(request);});
  server.on("/primary", HTTP_GET, [] (AsyncWebServerRequest *request){primary_LED(request);});
  server.on("/random", HTTP_GET, [] (AsyncWebServerRequest *request){random_LED(request);});
  server.on("/spiral",  HTTP_GET, [] (AsyncWebServerRequest *request){spiral_LED(request);});
  server.on("/xmas",  HTTP_GET, [] (AsyncWebServerRequest *request){xmas_LED(request);});
  server.on("/clear",  HTTP_GET, [] (AsyncWebServerRequest *request){clear_LED(request);});


  server.begin();

  strip.begin();
  strip.show();
  strip.clear();
  strip.setBrightness(50);
}

void loop() {
  if (spiralAction) {
     for (int i = 0; i < LED_COUNT; i++)
    {
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show();
    }
    delay(10);
    for (int i = LED_COUNT; i > 0; i--)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
    }
  }
}