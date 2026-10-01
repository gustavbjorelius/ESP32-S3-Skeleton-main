#include <Arduino.h>
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc_cal.h"
#include <SPI.h>
#include "pin_config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <time.h>


// This is the wifi settings. We assume Gustavs mobile hotspot with ssid and password 
/*String ssid = "GB";
String password = "administrator";  */

// "tft" is the graphics libary, which has functions to draw on the screen
TFT_eSPI tft = TFT_eSPI();

// this is simply the screen size in pixels 
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 170

// För Wifi
//WiFiClient wifi_client;

void setup() {
  // Setup kod som kom med Skeleton
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Starting ESP32 program...");
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // this controls the buttons
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);
  
  // Vi valde att Kommentera ut Wifi delen eftersom vi inte behöver den just nu och för att den tar massa tid vid start ibland.
  /*
  WiFi.begin(ssid, password);

  // Will be stuck here until a proper wifi is configured
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Connecting to WiFi...", 10, 10);
    Serial.println("Attempting to connect to WiFi...");
  }

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Connected to WiFi", 10, 10);
  Serial.println("Connected to WiFi");*/
  // Add your code bellow 

}

// initialize the variable that is about the pages
int currentPage = 0; 

bool buttonPressed0 = false; 
bool buttonPressed1 = false; 

//Sant om current page är utritad
bool drawn = false;

void loop() {
  // Hämta button states
  buttonPressed0 = (digitalRead(PIN_BUTTON_1) == LOW);
  buttonPressed1 = (digitalRead(PIN_BUTTON_2) == LOW);

  // KNAPP 1 
  if (buttonPressed0 && drawn && currentPage == 1) {
    currentPage = 0;
    drawn = false;
  }

  // KNAPP 2 
  if (buttonPressed1 && drawn && currentPage == 0) {
    currentPage = 1;
    drawn = false;
  }
  // Ser till att det endast ritas om det inte redan har blivit ritat.
  if (!drawn) {
    //Rensar Skärmen, sätter text färg och storlek
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    //Ritar rätt sida
    if (currentPage == 0) {
      tft.drawString("Hello student", 10, 10);
      tft.drawString("Grupp 2", 10, 150);
      tft.drawString("V0.4", 270, 150);
      // Smiley
      tft.fillCircle(160, 80, 30, TFT_YELLOW);
      tft.fillCircle(150, 72, 3, TFT_BLACK);
      tft.fillCircle(170, 72, 3, TFT_BLACK);
      tft.drawLine(148, 88, 155, 94, TFT_BLACK);
      tft.drawLine(155, 94, 165, 94, TFT_BLACK);
      tft.drawLine(165, 94, 172, 88, TFT_BLACK);
    }
    else if (currentPage == 1) {
      tft.drawString("Edil", 10, 10);
      tft.drawString("Gustav", 30, 50);
      tft.drawString("William", 50, 90);
    }
    drawn = true;
  }
}

// TFT Pin check
  //////////////////
 // DO NOT TOUCH //
//////////////////
#if PIN_LCD_WR  != TFT_WR || \
    PIN_LCD_RD  != TFT_RD || \
    PIN_LCD_CS    != TFT_CS   || \
    PIN_LCD_DC    != TFT_DC   || \
    PIN_LCD_RES   != TFT_RST  || \
    PIN_LCD_D0   != TFT_D0  || \
    PIN_LCD_D1   != TFT_D1  || \
    PIN_LCD_D2   != TFT_D2  || \
    PIN_LCD_D3   != TFT_D3  || \
    PIN_LCD_D4   != TFT_D4  || \
    PIN_LCD_D5   != TFT_D5  || \
    PIN_LCD_D6   != TFT_D6  || \
    PIN_LCD_D7   != TFT_D7  || \
    PIN_LCD_BL   != TFT_BL  || \
    TFT_BACKLIGHT_ON   != HIGH  || \
    170   != TFT_WIDTH  || \
    320   != TFT_HEIGHT
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5,0,0)
#error  "The current version is not supported for the time being, please use a version below Arduino ESP32 3.0"
#endif
