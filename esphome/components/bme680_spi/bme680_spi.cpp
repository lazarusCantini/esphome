#include <cstdint>
#include <cstddef>

#include "bme680_spi.h"
#include <esphome/components/bme680_bsec/bme680_bsec.h>

namespace esphome {
namespace bme680_spi {

uint8_t set_bit(uint8_t num, int position) {
  int mask = 1 << position;
  return num | mask;
}

uint8_t clear_bit(uint8_t num, int position) {
  int mask = 1 << position;
  return num & ~mask;
}

void bme680SPIComponent::setup() {
  this->spi_setup();
  bme680Component::setup();
};

// In SPI mode, only 7 bits of the register addresses are used; the MSB of register address is not used
// and replaced by a read/write bit (RW = ‘0’ for write and RW = ‘1’ for read).
// Example: address 0xF7 is accessed by using SPI register address 0x77. For write access, the byte
// 0x77 is transferred, for read access, the byte 0xF7 is transferred.
// https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme680-ds002.pdf

bool bme680SPIComponent::read_byte(uint8_t a_register, uint8_t *data) {
  this->enable();
  this->transfer_byte(set_bit(a_register, 7));
  *data = this->transfer_byte(0);
  this->disable();
  return true;
}

bool bme680SPIComponent::write_byte(uint8_t a_register, uint8_t data) {
  this->enable();
  this->transfer_byte(clear_bit(a_register, 7));
  this->transfer_byte(data);
  this->disable();
  return true;
}

bool bme680SPIComponent::read_bytes(uint8_t a_register, uint8_t *data, size_t len) {
  this->enable();
  this->transfer_byte(set_bit(a_register, 7));
  this->read_array(data, len);
  this->disable();
  return true;
}

bool bme680SPIComponent::read_byte_16(uint8_t a_register, uint16_t *data) {
  this->enable();
  this->transfer_byte(set_bit(a_register, 7));
  ((uint8_t *) data)[1] = this->transfer_byte(0);
  ((uint8_t *) data)[0] = this->transfer_byte(0);
  this->disable();
  return true;
}

}  // namespace bme680_spi
}  // namespace esphome
