#include "main.h"
#define LOG_TAG "MAIN"
#include "esp_wifi.h"
#include <esp_mac.h>

static Main my_main;
char data = 0;
uint8_t value = 0;

extern "C" void app_main(void) {

    ESP_ERROR_CHECK(my_main.setup());
    
    while(true)
    {
        my_main.loop();
    }
}

esp_err_t Main::setup(){
    esp_err_t status(ESP_OK);
    vTaskDelay(pdMS_TO_TICKS(500));
    
    accelerometer = new Accelerometer(ioMapping::sda, ioMapping::scl, I2C_NUM_1);
    wifi = new Wifi();
    rightLeg = new RightLeg();
    leftLeg = new LeftLeg();
    //movement = new Movement();
    wifi->attach(rightLeg);
    wifi->attach(leftLeg);
    wifi->begin();
    wifi->scan();
    if(wifi->connect("Loulou","Loulou141295") == ESP_OK){
        ESP_LOGI(LOG_TAG,"Connected to wifi");
    }
    else{
        ESP_LOGE(LOG_TAG,"Failed to connect to wifi");
    }
    vTaskDelay(pdMS_TO_TICKS(5000));

    wifi->start();
    accelerometer->begin();
    //movement->start();
    
    return status;
}

void Main::loop(){
    //((RightLeg*)rightLeg)->forward();
    ESP_LOGI("Alive","test");
    //vTaskDelay(pdSecond); //1s
    //((RightLeg*)rightLeg)->reverse();

    ESP_LOGI("AccelerometerX","%d",accelerometer->getXAccel());
    ESP_LOGI("AccelerometerY","%d",accelerometer->getYAccel());
    ESP_LOGI("AccelerometerZ","%d",accelerometer->getZAccel());

    vTaskDelay(pdSecond); //1s
}