#pragma once

#include "esphome/components/bme680_bsec/bme680_bsec.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace bme680_spi {

class bme680SPIComponent : public esphome::bme680_base::bme680Component,
                           public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                                 spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_200KHZ> {
  void setup() override;
  bool read_byte(uint8_t a_register, uint8_t *data) override;
  bool write_byte(uint8_t a_register, uint8_t data) override;
  bool read_bytes(uint8_t a_register, uint8_t *data, size_t len) override;
  bool read_byte_16(uint8_t a_register, uint16_t *data) override;
};

}  // namespace bme680_spi
}  // namespace esphome
