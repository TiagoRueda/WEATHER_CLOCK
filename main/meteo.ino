void get_weather_description(int code) {
  switch (code) {
    case 0:
      if(is_day==1) { lv_image_set_src(weather_image, &image_weather_sun); }
      else { lv_image_set_src(weather_image, &image_weather_night); }
      weather_description = "CEU LIMPO";
      break;
    case 1: 
      if(is_day==1) { lv_image_set_src(weather_image, &image_weather_sun); }
      else { lv_image_set_src(weather_image, &image_weather_night); }
      weather_description = "PARCIALMENTE LIMPO";
      break;
    case 2: 
      lv_image_set_src(weather_image, &image_weather_cloud);
      weather_description = "PARCIALMENTE NUBLADO";
      break;
    case 3:
      lv_image_set_src(weather_image, &image_weather_cloud);
      weather_description = "NUBLADO";
      break;
    case 45:
      lv_image_set_src(weather_image, &image_weather_cloud);
      weather_description = "NEBLINA";
      break;
    case 48:
      lv_image_set_src(weather_image, &image_weather_cloud);
      weather_description = "NEVOEIRO COM GEADA";
      break;
    case 51:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA FRACA";
      break;
    case 53:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA MODERADA";
      break;
    case 55:
      lv_image_set_src(weather_image, &image_weather_rain); 
      weather_description = "CHUVA INTENSA";
      break;
    case 56:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA CONGELANTE FRACA";
      break;
    case 57:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA CONGELANTE INTENSA";
      break;
    case 61:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA LEVE";
      break;
    case 63:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA MODERADA";
      break;
    case 65:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA FORTE";
      break;
    case 66:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA CONGELANTE LEVE";
      break;
    case 67:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA CONGELANTE FORTE";
      break;
    case 71:
      lv_image_set_src(weather_image, &image_weather_snow);
      weather_description = "NEVE LEVE";
      break;
    case 73:
      lv_image_set_src(weather_image, &image_weather_snow);
      weather_description = "NEVE MODERADA";
      break;
    case 75:
      lv_image_set_src(weather_image, &image_weather_snow);
      weather_description = "NEVE FORTE";
      break;
    case 77:
      lv_image_set_src(weather_image, &image_weather_snow);
      weather_description = "GRAOS DE NEVE";
      break;
    case 80:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVAS LEVES";
      break;
    case 81:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVAS MODERADAS";
      break;
    case 82:
      lv_image_set_src(weather_image, &image_weather_rain);
      weather_description = "CHUVA FORTE";
      break;
    case 85:
      lv_image_set_src(weather_image, &image_weather_snow);
      weather_description = "PANCADAS DE NEVE LEVES";
      break;
    case 86:
      lv_image_set_src(weather_image, &image_weather_snow);
      weather_description = "PANCADAS DE NEVE FORTES";
      break;
    case 95:
      lv_image_set_src(weather_image, &image_weather_thunder);
      weather_description = "TEMPESTADE";
      break;
    case 96:
      lv_image_set_src(weather_image, &image_weather_thunder);
      weather_description = "TEMPESTADE COM GRANIZO";
      break;
    case 99:
      lv_image_set_src(weather_image, &image_weather_thunder);
      weather_description = "TEMPESTADE COM GRANIZO";
      break;
    default: 
      weather_description = "CODIGO DE TEMPO DESCONHECIDO";
      break;
  }
}

void get_weather_data() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String("http://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude + "&current=temperature_2m,relative_humidity_2m,is_day,precipitation,rain,weather_code" + temperature_unit + "&timezone=" + timezone + "&forecast_days=1");
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
          const char* datetime = doc["current"]["time"];

          temperature = doc["current"]["temperature_2m"].as<String>();
          humidity = doc["current"]["relative_humidity_2m"].as<String>();
          is_day = doc["current"]["is_day"].as<int>();
          weather_code = doc["current"]["weather_code"].as<int>();
          String datetime_str = String(datetime);
          int splitIndex = datetime_str.indexOf('T');
          current_date = datetime_str.substring(0, splitIndex);
          last_weather_update = datetime_str.substring(splitIndex + 1, splitIndex + 9);
        } else {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
        }
      }
    } else {
      Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("Not connected to Wi-Fi");
  }
}