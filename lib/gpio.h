#pragma once
#include "driver/gpio.h"

namespace Gpio{
    class GpioBase{
    protected:
        const gpio_num_t _pin;
        const gpio_config_t _cfg;
    public:
        GpioBase(const gpio_num_t pin, const gpio_config_t& config) : _pin{pin}, _cfg{config}
        {
        };
        virtual ~GpioBase(){};
        [[nodiscard]] virtual esp_err_t init(void) = 0;
        virtual bool state(void) = 0;
    };

    class GpioOutput : public GpioBase{
    private:
        bool _state = false;
    public:
        [[nodiscard]] esp_err_t init();

        esp_err_t set(const bool state);
        esp_err_t toggle();
        bool state(void){return _state;};
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
        [[nodiscard]] esp_err_t init(void);
        bool state(void);
    };
}