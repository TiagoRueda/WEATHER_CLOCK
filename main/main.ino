#include "definitions.h"

void setup() {
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to Wi-Fi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  lv_init();
  lv_log_register_print_cb(log_print);

  lv_display_t * disp;
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);
  tft.setRotation(2);

  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov"); 
  style_init();
  lv_create_main_gui();

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  speech = true;
}

void loop() {
  lv_task_handler(); 
  lv_tick_inc(5);
  delay(5);
  audio.loop();

  if(speech){
    speech = false;
    audio.connecttospeech(lv_label_get_text(text_label_time), "pt");
  }
}
