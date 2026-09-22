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
String ssid = "GB";
String password = "administrator";

// "tft" is the graphics libary, which has functions to draw on the screen
TFT_eSPI tft = TFT_eSPI();

// Display dimentions
// this is simply the screen size in pixels 
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 170

// idk this sets a variable to so we can have wifi for no reason? 
WiFiClient wifi_client;

/**
 * Setup function
 * This function is called once when the program starts to initialize the program
 * and set up the hardware.
 * Carefull when modifying this function.
 */
void setup() {
  // Initialize Serial for debugging
  // idk what this means? 
  Serial.begin(115200);
  // Wait for the Serial port to be ready
  // what is serial port? 
  // i suppose it's the usbc? 
  while (!Serial);
  // this doesn't happen really, it just
  Serial.println("Starting ESP32 program...");
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // this contros the buttons
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);

  // Connect to WIFI
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
  Serial.println("Connected to WiFi");
  // Add your code bellow 

}

/**
 * This is the main loop function that runs continuously after setup.
 * Add your code here to perform tasks repeatedly.
 */

// initialize the variable that is about the pages
int currentPage = 0; 

bool buttonPressed0 = false; 
bool buttonPressed1 = false; 


// TODOs

// we want to have is screen 1 (the first we see before we press any button) 'Group 2'
// upon button press, we have 

void loop() {

  buttonPressed0 = (digitalRead(PIN_BUTTON_1) == LOW);
  buttonPressed1 = (digitalRead(PIN_BUTTON_2) == LOW);

  // KNAPP 1 
  if (buttonPressed0) {
    currentPage = 0;

  // Wait until the button is pressed 
  while (digitalRead(PIN_BUTTON_1) == LOW) {
  }
}

  // KNAPP 2 
  if (buttonPressed1) {
    currentPage = 1;
    
  // Wait until the button is pressed 
  while (digitalRead(PIN_BUTTON_2) == LOW) {
  }
}

// rita rätt sida 
if (currentPage == 0) {

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Hell o student", 10, 10);
  tft.drawString(":)", 10, 50);
}

else if (currentPage == 1) {

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Edil", 10, 10);
  tft.drawString("Gustav", 30, 50);
  tft.drawString("William", 60, 100);
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