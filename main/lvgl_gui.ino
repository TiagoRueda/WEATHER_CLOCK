static void style_init(void) {
    lv_style_init(&style_container_btn);
    lv_style_set_radius(&style_container_btn, 10);
    lv_style_set_bg_opa(&style_container_btn, LV_OPA_100);
    lv_style_set_bg_color(&style_container_btn, lv_color_make(0, 0, 0));
    lv_style_set_bg_grad_color(&style_container_btn, lv_color_make(50, 50, 50));
    lv_style_set_bg_grad_dir(&style_container_btn, LV_GRAD_DIR_VER);

    lv_style_set_text_color(&style_container_btn, lv_color_black());

    lv_style_init(&style_container_datehour);
    lv_style_set_radius(&style_container_datehour, 0);
    lv_style_set_bg_opa(&style_container_datehour, LV_OPA_100);
    lv_style_set_bg_color(&style_container_datehour, lv_color_make(0, 0, 0));
    lv_style_set_bg_grad_color(&style_container_datehour, lv_color_make(50, 50, 50));
    lv_style_set_bg_grad_dir(&style_container_datehour, LV_GRAD_DIR_VER);

    lv_style_set_text_color(&style_container_datehour, lv_color_black());
}

void lv_create_main_gui(void) {
  LV_IMAGE_DECLARE(image_weather_sun);
  LV_IMAGE_DECLARE(image_weather_cloud);
  LV_IMAGE_DECLARE(image_weather_rain);
  LV_IMAGE_DECLARE(image_weather_thunder);
  LV_IMAGE_DECLARE(image_weather_snow);
  LV_IMAGE_DECLARE(image_weather_night);
  LV_IMAGE_DECLARE(image_weather_temperature);
  LV_IMAGE_DECLARE(image_weather_humidity);
  LV_IMAGE_DECLARE(teste);

  get_weather_data();
  
  lv_obj_t* fundo = lv_obj_create(lv_scr_act());
  lv_obj_set_size(fundo, lv_pct(100), lv_pct(100));
  lv_obj_set_style_bg_color(fundo, lv_color_hex(0x808080), 0);
  lv_obj_set_style_bg_opa(fundo, LV_OPA_COVER, 0);
  lv_obj_clear_flag(fundo, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t* container_btn = lv_btn_create(lv_screen_active());
  lv_obj_add_style(container_btn, &style_container_btn, 0);
  lv_obj_set_pos(container_btn, -10, 230);
  lv_obj_set_size(container_btn, 160, 90);

  weather_image = lv_image_create(container_btn);
  lv_obj_align(weather_image, LV_ALIGN_TOP_LEFT, 0, 0);

  get_weather_description(weather_code);

  lv_obj_t * weather_image_temperature = lv_image_create(container_btn);
  lv_image_set_src(weather_image_temperature, &image_weather_temperature);
  lv_obj_align(weather_image_temperature, LV_ALIGN_TOP_LEFT, 52, 0);
  text_label_temperature = lv_label_create(container_btn);
  lv_label_set_text(text_label_temperature, String("      " + temperature + degree_symbol).c_str());
  lv_obj_align(text_label_temperature, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_style_text_font((lv_obj_t*) text_label_temperature, &lv_font_montserrat_20, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_label_temperature, lv_color_white(), 0);

  lv_obj_t * weather_image_humidity = lv_image_create(container_btn);
  lv_image_set_src(weather_image_humidity, &image_weather_humidity);
  lv_obj_align(weather_image_humidity, LV_ALIGN_TOP_LEFT, 52, 25);
  text_label_humidity = lv_label_create(container_btn);
  lv_label_set_text(text_label_humidity, String("           " + humidity + "%").c_str());
  lv_obj_align(text_label_humidity, LV_ALIGN_TOP_RIGHT, 0, 25);
  lv_obj_set_style_text_font((lv_obj_t*) text_label_humidity, &lv_font_montserrat_20, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_label_humidity, lv_color_white(), 0);

  text_label_weather_description = lv_label_create(container_btn);
  lv_label_set_text(text_label_weather_description, weather_description.c_str());
  lv_obj_align(text_label_weather_description, LV_ALIGN_BOTTOM_LEFT, 0, -10);
  lv_obj_set_style_text_font((lv_obj_t*) text_label_weather_description, &lv_font_montserrat_10, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_label_weather_description, lv_color_white(), 0);

  text_label_time_location = lv_label_create(container_btn);
  lv_label_set_text(text_label_time_location, String(last_weather_update + "  |  " + location).c_str());
  lv_obj_align(text_label_time_location, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_set_style_text_font((lv_obj_t*) text_label_time_location, &lv_font_montserrat_10, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_label_time_location, lv_color_white(), 0);

  lv_obj_t* container_datehour = lv_btn_create(lv_screen_active());
  lv_obj_add_style(container_datehour, &style_container_datehour, 0);
  lv_obj_set_pos(container_datehour, 0, -10);
  lv_obj_set_size(container_datehour, 240, 30);

  text_label_date = lv_label_create(container_datehour);
  lv_label_set_text(text_label_date, current_date.c_str());
  lv_obj_align(text_label_date, LV_ALIGN_TOP_RIGHT, 0, 2);
  lv_obj_set_style_text_font((lv_obj_t*) text_label_date, &lv_font_montserrat_18, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_label_date, lv_color_white(), 0);

  lv_obj_t* text_div = lv_label_create(container_datehour);
  lv_label_set_text(text_div, "|");
  lv_obj_align(text_div, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_text_font((lv_obj_t*) text_div, &lv_font_montserrat_18, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_div  , lv_color_white(), 0);

  text_label_time = lv_label_create(container_datehour);
  lv_obj_align(text_label_time, LV_ALIGN_TOP_LEFT, 13, 2);
  lv_obj_set_style_text_font((lv_obj_t*) text_label_time, &lv_font_montserrat_18, 0);
  lv_obj_set_style_text_color((lv_obj_t*) text_label_time, lv_color_white(), 0);

  lv_timer_t * timerhour = lv_timer_create(timer_hr, 1000, NULL);
  lv_timer_ready(timerhour);
  lv_timer_t * timer = lv_timer_create(timer_cb, 900000, NULL);
  lv_timer_ready(timer);
}
