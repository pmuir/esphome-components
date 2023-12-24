#include "esphome/core/log.h"
#include "CST816S_touchscreen.h"
#include "CST816S.h"

namespace esphome {
namespace cst816s_touchscreen {

unsigned long previousMillis = 0UL;
unsigned long interval = 500UL;

static const char *TAG = "cst816s.text_sensor";

CST816S touc

void CST816STouchScreen::setup() {
    ESP_LOGI("touchscreen", "Starting touchscreen");
    this->interrupt_pin_->pin_mode(gpio::FLAG_INPUT | gpio::FLAG_PULLUP);
    this->interrupt_pin_->setup();
    this->attach_interrupt_(this->interrupt_pin_, gpio::INTERRUPT_FALLING_EDGE);
    this->rts_pin_->setup();
    touch.begin();
}

void CST816STouchScreen::dump_config() { 
    ESP_LOGCONFIG(TAG, "CST816STouchScreen");
    LOG_I2C_DEVICE(this);
    LOG_PIN("  Interrupt Pin: ", this->interrupt_pin_);
    LOG_PIN("  RTS Pin: ", this->rts_pin_);
}

void CST816STouchScreen::loop() {
    unsigned long currentMillis = millis();

    if (touch.available()) {
        if(touch.data.gestureID != 0){                          //ignore None gesture type
            if(currentMillis - previousMillis > interval) {     //debounce
                char buf[20];
                sprintf(buf, "%s", touch.gesture());
                ESP_LOGI("touchscreen", "Gesture: %s", touch.gesture());
                this->publish_state(buf);
                previousMillis = currentMillis;
            }
        }
    }
}

}  // namespace cst816s_touchscreen
}  // namespace esphome
