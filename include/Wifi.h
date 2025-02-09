#pragma once

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "../lib/Task.h"
#include <string.h>
#include "../lib/singleton.hpp" // Include the header file for TSingleton
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "cJSON.h"  // Include the cJSON library
#include "Subject.h"
#include <vector>
#include <variant>
#include "esp_http_client.h"
#include "secrets.h"


class Wifi : public Task, public Subject{

private:
    command_t currentCommand;
    std::vector<std::variant<int, std::string>> data;

public:
    static bool reconnecting; // Declaration only
    
    Wifi(): Task("Task Wifi"){

    }
     ~Wifi() {}

    esp_err_t begin(){
        esp_err_t ret = ESP_OK;
        return ret;
    }
    esp_err_t connect(const char* ssid, const char* password){
        //Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        // Initialize network interface
        ESP_ERROR_CHECK(esp_netif_init());

        // Create default event loop
        ESP_ERROR_CHECK(esp_event_loop_create_default());

        // Create default Wi-Fi station
        esp_netif_create_default_wifi_sta();

        // Initialize Wi-Fi
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));

        // Register event handlers
        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &event_handler,
                                                            NULL,
                                                            NULL));

        ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                            IP_EVENT_STA_GOT_IP,
                                                            &event_handler,
                                                            NULL,
                                                            NULL));
        // Initialize Wi-Fi
        wifi_config_t wifi_config = {
            .sta = {
                .ssid = WIFI_SSID,       // Empty SSID initially
                .password = WIFI_PASSWORD    // Empty password initially
            }
        };
        
        // Set SSID and password from arguments
        //strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
        //strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
        ESP_LOGI("wifissid", " %s.", wifi_config.sta.ssid);
        ESP_LOGI("wifipass", " %s.", wifi_config.sta.password);
        

        
        
        ret = esp_wifi_set_mode(WIFI_MODE_STA);
        if (ret != ESP_OK) {
            ESP_LOGE("wifi", "Failed to set Wi-Fi mode: %s", esp_err_to_name(ret));
            return ret;
        }
        
        ret = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
        if (ret != ESP_OK) {
            ESP_LOGE("wifi", "Failed to set Wi-Fi config: %s", esp_err_to_name(ret));
            return ret;
        }
        
        ret = esp_wifi_start();
        if (ret != ESP_OK) {
            ESP_LOGE("wifi", "Failed to start Wi-Fi: %s", esp_err_to_name(ret));
            return ret;
        }
        vTaskDelay(pdMS_TO_TICKS(2000)); // Add a small delay before connecting
        for (int i = 0; i < 5; i++) {
            ret = esp_wifi_connect();
            if (ret == ESP_OK) {
                ESP_LOGI("WiFi", "Connection attempt %d successful", i + 1);
                break;
            }
            ESP_LOGE("WiFi", "Connection attempt %d failed. Retrying...", i + 1);
            vTaskDelay(pdMS_TO_TICKS(3000));
        }
        ESP_ERROR_CHECK(ret);
        return ret;
    }

    esp_err_t disconnect(){
        esp_err_t ret;
        return ret;
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
        return ret;
    }

    std::string getMacAddress(){
        uint8_t mac[6];
        esp_wifi_get_mac(WIFI_IF_STA, mac);
        char mac_str[18];
        snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X", 
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return std::string(mac_str);
    }
    
    void task() override{
        const char * TAG = "Wifi-Task";
        ESP_LOGI(TAG, "Test4");
        const unsigned short SERVER_PORT = 12345;
        ESP_LOGI(TAG, "Test5");
        int server_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (server_sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            vTaskDelete(NULL);
            return;
        }
        ESP_LOGI(TAG, "Test");
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        // Bind the socket to the address and port
        int err = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (err < 0) {
            ESP_LOGE(TAG, "Unable to bind socket: errno %d", errno);
            close(server_sock);
            vTaskDelete(NULL);
            return;
        }
         ESP_LOGI(TAG, "Test2");
        // Listen for incoming connections
        err = listen(server_sock, 1);
        if (err < 0) {
            ESP_LOGE(TAG, "Unable to listen: errno %d", errno);
            close(server_sock);
            vTaskDelete(NULL);
            return;
        }

         ESP_LOGI(TAG, "Test3");

        // Receive data from the client
        char recv_buf[1024];
        int len;

        
        while(1){
            // Accept connections
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
            if (client_sock < 0) {
                ESP_LOGI(TAG, "Unable to accept connection: errno %d", errno);
                vTaskDelay(100);
                continue;
            }

            ESP_LOGI(TAG, "Client connected");
              
            len = recv(client_sock, recv_buf, sizeof(recv_buf) - 1, 0);
            if (len < 0) {
                ESP_LOGE(TAG, "Error receiving data: errno %d", errno);
                break;
            }
            recv_buf[len] = 0;
            
            // Parse JSON
            cJSON *root = cJSON_Parse(recv_buf);
            if (root == NULL) {
                ESP_LOGE(TAG, "Error parsing JSON");
                break;
            }
            ESP_LOGI("new data","data1");
            // Iterate through all keys in the JSON object
            cJSON *current = NULL;
            data.clear();
            cJSON_ArrayForEach(current, root) {
                ESP_LOGI("new data","data2");
                if (cJSON_IsNumber(current)) {
                    // Store integer value
                    ESP_LOGI("new data", "number");
                    data.emplace_back(current->valueint);
                } else if (cJSON_IsString(current)) {
                    // Store string value
                    ESP_LOGI("new data", "string");
                    data.emplace_back(std::string(current->valuestring));
                }
                ESP_LOGI("new len", "%d", data.size());
                // Other types can be handled here if needed
                // Clean up
                ESP_LOGI("new data","data3");

                
                ESP_LOGI("new data","data5");
                
                ESP_LOGI("new data","data4");
                
            }
            setData(data);
            notifyObservers();
            cJSON_Delete(root);

            //parseCommand((command_t)getCommandType(commandType->valuestring), data1->valueint, data2->valueint);
            
            // Close the socket
            close(client_sock);
            vTaskDelay(pdMS_TO_TICKS(100));    
        }
        
        close(server_sock);
        ESP_LOGI(TAG, "Connection closed");

        //vTaskDelete(NULL);    
        
    }

    

    // Event handler for Wi-Fi and IP events
    static void event_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data) {
        const char * TAG = "Wifi-Event";
        
        if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
            ESP_LOGI(TAG, "Wi-Fi started, connecting...");
            esp_wifi_connect();
            vTaskDelay(pdMS_TO_TICKS(2000));
        } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
            if (!reconnecting) {
                reconnecting = true;
                esp_wifi_connect();
                ESP_LOGI("WiFi", "Reconnecting...");
                reconnecting = false;
            }
        } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
            ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
            ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        }
    }

    std::vector<std::variant<int, std::string>> getData(){
        return data;
    }

    void setData(std::vector<std::variant<int, std::string>> data){
        this->data = data;
        notifyObservers();
    }

    subject_t getType() const override{
        return WIFI;
    }

    static esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
        switch (evt->event_id) {
            case HTTP_EVENT_ERROR:
                ESP_LOGI("HTTP", "HTTP_EVENT_ERROR");
                break;
            case HTTP_EVENT_ON_CONNECTED:
                ESP_LOGI("HTTP", "HTTP_EVENT_CONNECTED");
                break;
            case HTTP_EVENT_HEADER_SENT:
                ESP_LOGI("HTTP", "HTTP_EVENT_HEADER_SENT");
                break;
            case HTTP_EVENT_ON_DATA:
                ESP_LOGI("HTTP", "HTTP_EVENT_BODY, len=%d", evt->data_len);
                if (!esp_http_client_is_chunked_response(evt->client)) {
                    ESP_LOGI("HTTP", "Response: %s", (char*)evt->data);
                }
                break;
            case HTTP_EVENT_DISCONNECTED:
                ESP_LOGI("HTTP", "HTTP_EVENT_DISCONNECTED");
                break;
            default:
                break;
        }
        return ESP_OK;
    }

    static void send_data_http(int16_t x, int16_t y, int16_t z) {
        char payload[100];
        snprintf(payload, sizeof(payload), "{\"x\": %d, \"y\": %d, \"z\": %d}", x, y, z);

        esp_http_client_config_t config = {
            .url = SERVER_URL,
            .method = HTTP_METHOD_POST,
            .timeout_ms = 5000,
        };

        esp_http_client_handle_t client = esp_http_client_init(&config);
        esp_http_client_set_header(client, "Content-Type", "application/json");
        esp_http_client_set_post_field(client, payload, strlen(payload));
        esp_err_t err = esp_http_client_perform(client);
        esp_http_client_cleanup(client);

        if (err == ESP_OK) {
            ESP_LOGI("HTTP", "Data Sent: %s", payload);
        } else {
            ESP_LOGE("HTTP", "Failed to send data");
        }
    }



    //TODO Implement wifi functions
        //std::string getIpAddress();   
        //esp_err_t getRssi();  
        //esp_err_t status();
        //esp_err_t stop();
};
bool Wifi::reconnecting = false;