#include "lvgl.h"
#include <time.h> 
#include "TFT_eSPI.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Audio.h>
#include <vector>

const char* ssid = "your_ssid";
const char* password = "your_pass";

String latitude = "-23.5411";
String longitude = "-46.4432";
String location = "SP";
String timezone = "America/Sao_Paulo";

String current_date;
String last_weather_update;
String temperature;
String humidity;
int is_day;
int weather_code = 0;
String weather_description;

#define TEMP_CELSIUS 1

#if TEMP_CELSIUS
  String temperature_unit = "";
  const char degree_symbol[] = "\u00B0C";
#else
  String temperature_unit = "&temperature_unit=fahrenheit";
  const char degree_symbol[] = "\u00B0F";
#endif

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

static lv_obj_t * weather_image;
static lv_obj_t * text_label_date;
static lv_obj_t * text_label_temperature;
static lv_obj_t * text_label_humidity;
static lv_obj_t * text_label_weather_description;
static lv_obj_t * text_label_time_location;

static lv_obj_t * text_label_time;

static lv_style_t style_container_btn;
static lv_style_t style_container_datehour;

#define I2S_DOUT 18
#define I2S_BCLK 4
#define I2S_LRC 5

Audio audio;
bool speech = false;
TFT_eSPI tft = TFT_eSPI();