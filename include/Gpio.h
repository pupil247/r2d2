#pragma once

#include "driver/gpio.h"
#include "esp_log.h"

namespace Gpio{
    enum GpioState{
        LOW = 0,
        HIGH = 1
    };
    
    class GpioBase{
    protected:
        const gpio_num_t _pin;
        const gpio_config_t _cfg;
    public:
        GpioBase(const gpio_num_t pin, const gpio_config_t& config) : _pin{pin}, _cfg{config}
        {
        };
        virtual ~GpioBase(){};
        [[nodiscard]] virtual esp_err_t     init(void) = 0;
        virtual bool state(void) = 0;
    };

    class GpioOutput : public GpioBase{
    private:
        bool _state = false;
    public:
        [[nodiscard]] esp_err_t init(void){
             // Configure the GPIO pin as output
            if (gpio_config(&_cfg) != ESP_OK) {
                return ESP_FAIL; // Return an error if configuration fails
            }
            return set(_state);
        }

        esp_err_t set(const bool state){
            _state = state;
            //ESP_LOGI("GPIO","set pin %d, %d",_pin,state);
            gpio_set_level(_pin, _state); 
            return ESP_OK;
        }
        esp_err_t toggle(){
            set(!_state);
            return ESP_OK;
        }
        bool state(void){return _state;}
        virtual ~GpioOutput(){};
        GpioOutput(const gpio_num_t pin): 
            GpioBase{pin,
                gpio_config_t{
                    .pin_bit_mask = static_cast<uint64_t>(1) << pin,
                    .mode = GPIO_MODE_OUTPUT,
                    .pull_up_en = GPIO_PULLUP_DISABLE,
                    .pull_down_en = GPIO_PULLDOWN_ENABLE,
                    .intr_type = GPIO_INTR_DISABLE,
                }
            }

        {
        }

    };

    class GpioInput : public GpioBase{
    private:
        bool _state = false;
    public:
        
        GpioInput(const gpio_num_t pin): 
            GpioBase{pin,
                gpio_config_t{
                    .pin_bit_mask = static_cast<uint64_t>(1) << pin,
                    .mode = GPIO_MODE_INPUT,
                    .pull_up_en = GPIO_PULLUP_DISABLE,
                    .pull_down_en = GPIO_PULLDOWN_DISABLE,
                    .intr_type = GPIO_INTR_DISABLE, 
                }
            }
        {
        }
        virtual ~GpioInput(){};
        [[nodiscard]] esp_err_t init(void){
             // Configure the GPIO pin as output
            if (gpio_config(&_cfg) != ESP_OK) {
                return ESP_FAIL; // Return an error if configuration fails
            }
        }
        bool state(void){return _state;}
    };
}