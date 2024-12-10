#pragma once

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "../lib/Task.h"
#include <cstring>

class Wifi : public Task, public Singleton<Wifi>{
public:
    esp_err_t begin(){
        esp_err_t ret;
    }
    esp_err_t connect(const char* ssid, const char* password){
        
        // Initialize Wi-Fi
        wifi_config_t wifi_config = {
            .sta = {
                .ssid = "",       // Empty SSID initially
                .password = ""    // Empty password initially
            }
        };

        // Set SSID and password from arguments
        strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
        strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
        esp_wifi_start();
        esp_wifi_connect();
        esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    }
    esp_err_t disconnect(){
        esp_err_t ret;
    }
    
    esp_err_t scan(){

        esp_err_t ret;
        const char * TAG = "Wifi-Scan";

        wifi_scan_config_t scan_config;
        scan_config.ssid = 0;
        scan_config.bssid = 0;
        scan_config.channel = 0;
        scan_config.show_hidden = true;
        scan_config.scan_type = WIFI_SCAN_TYPE_ACTIVE;
        scan_config.scan_time.active.min = 0;
        scan_config.scan_time.active.max = 0;
        //start scan
        esp_wifi_scan_start(&scan_config, true);

        //return APS found
        uint16_t num = 0;
        wifi_ap_record_t *ap_records = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * 20);  // Allocate memory for 20 APs
        ret = esp_wifi_scan_get_ap_records(&num, ap_records);
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Found %d APs", num);
            for (int i = 0; i < num; i++) {
                ESP_LOGI(TAG, "AP %d: SSID: %s, RSSI: %d, Channel: %d", i, ap_records[i].ssid, ap_records[i].rssi, ap_records[i].primary);
            }
        } else {
            ESP_LOGE(TAG, "Failed to get scan results");
        }
    }

    std::string getMacAddress(){
        uint8_t mac[6];
        esp_wifi_get_mac(WIFI_IF_STA, mac);
        char mac_str[18];
        snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X", 
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return std::string(mac_str);
    }
    //TODO Implement wifi functions
    //std::string getIpAddress();   
    //esp_err_t getRssi();  
    //esp_err_t status();
    //esp_err_t stop();
};