import esphome.codegen as cg
import esphome.config_validation as cv

from esphome import pins
from esphome.components import i2c, text_sensor
from esphome.const import CONF_ID, CONF_INTERRUPT_PIN


cst816s_touchscreen_ns = cg.esphome_ns.namespace('cst816s_touchscreen')
CST816STouchScreen = cst816s_touchscreen_ns.class_('CST816STouchScreen', text_sensor.TextSensor, cg.Component, i2c.I2CDevice)

CONF_RTS_PIN = "rts_pin"

CONFIG_SCHEMA = text_sensor.TEXT_SENSOR_SCHEMA.extend(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(CST816STouchScreen),
            cv.Required(CONF_INTERRUPT_PIN): cv.All(
                pins.internal_gpio_input_pin_schema
            ),
            cv.Required(CONF_RTS_PIN): pins.gpio_output_pin_schema,
            
        }
    ).extend(i2c.i2c_device_schema(0x15))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await text_sensor.register_text_sensor(var, config)
    await i2c.register_i2c_device(var, config)
    cg.add_library(
            name="CST816S",
            repository="https://github.com/GadgetFactory/CST816S.git",
            version="1.1.1",
        )
    interrupt_pin = await cg.gpio_pin_expression(config[CONF_INTERRUPT_PIN])
    cg.add(var.set_interrupt_pin(interrupt_pin))
    rts_pin = await cg.gpio_pin_expression(config[CONF_RTS_PIN])
    cg.add(var.set_rts_pin(rts_pin))
