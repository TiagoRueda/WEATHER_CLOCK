bool contains_time(const String& last_weather_update) {
    const char* times[] = {
        "00:00:00", "01:00:00", "02:00:00", "03:00:00", "04:00:00", "05:00:00", "06:00:00", "07:00:00", 
        "08:00:00", "09:00:00", "10:00:00", "11:00:00", "12:00:00", "13:00:00", "14:00:00", "15:00:00", 
        "16:00:00", "17:00:00", "18:00:00", "19:00:00", "20:00:00", "21:00:00", "22:00:00", "23:00:00",
    };

    for (int i = 0; i < 24; i++) {
        if (last_weather_update.indexOf(times[i]) != -1) {
            return true;
        }
    }

    return false;
}


static void timer_hr(lv_timer_t * timer){
  LV_UNUSED(timer);

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    char timeStr[10];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
    lv_label_set_text(text_label_time, timeStr);
  }

  if (contains_time(String(lv_label_get_text(text_label_time)))) {
    speech = true;
  }
}

static void timer_cb(lv_timer_t * timer){
  LV_UNUSED(timer);
  get_weather_data();
  get_weather_description(weather_code);
  lv_label_set_text(text_label_date, current_date.c_str());
  lv_label_set_text(text_label_temperature, String("      " + temperature + degree_symbol).c_str());
  lv_label_set_text(text_label_humidity, String("   " + humidity + "%").c_str());
  lv_label_set_text(text_label_weather_description, weather_description.c_str());
  lv_label_set_text(text_label_time_location, String(last_weather_update + "  |  " + location).c_str());
}