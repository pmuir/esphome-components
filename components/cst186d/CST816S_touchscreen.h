#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "CST816S.h"

namespace esphome {
namespace cst816s_touchscreen {

class CST816STouchScreen : public text_sensor::TextSensor, public i2c::I2CDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }
  void set_rts_pin(GPIOPin *pin) { this->rts_pin_ = pin; }

 protected:
  InternalGPIOPin *interrupt_pin_;
  GPIOPin *rts_pin_;
  
};

}  // namespace cst816s_touchscreen
}  // namespace esphome
