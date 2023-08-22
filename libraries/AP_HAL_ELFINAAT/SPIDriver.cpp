/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  ElfinAAT port by Mike McCauley
 */
#include <AP_HAL/AP_HAL.h>

#if CONFIG_HAL_BOARD == HAL_BOARD_ELFINAAT

// ElfinAAT SPI driver
// ElfinAAT has no actual SPI devices, so this generic

#include "SPIDriver.h"
#include "ElfinAATWirish.h"

using namespace AP_HAL_ELFINAAT_NS;

#define ELFINAAT_SPI_CS_PIN 8
// Only one port so far:
#define ELFINAAT_SPI_PORT 1
HardwareSPI spi(ELFINAAT_SPI_PORT);


ELFINAATSPIDeviceDriver::ELFINAATSPIDeviceDriver()
{}

void ELFINAATSPIDeviceDriver::init()
{
    spi.begin(SPI_9MHZ, MSBFIRST, SPI_MODE_0);
    digitalWrite(ELFINAAT_SPI_CS_PIN, 1);
    pinMode(ELFINAAT_SPI_CS_PIN, OUTPUT);
}

AP_HAL::Semaphore* ELFINAATSPIDeviceDriver::get_semaphore()
{
    return &_semaphore;
}

void ELFINAATSPIDeviceDriver::transaction(const uint8_t *tx, uint8_t *rx, uint16_t len)
{
    cs_assert();
    if (rx == NULL) {
        for (uint16_t i = 0; i < len; i++) {
            transfer(tx[i]);
        }
    } else {
        for (uint16_t i = 0; i < len; i++) {
            rx[i] = transfer(tx[i]);
        }
    }
    cs_release();
}


void ELFINAATSPIDeviceDriver::cs_assert()
{
    digitalWrite(ELFINAAT_SPI_CS_PIN, 0);
}

void ELFINAATSPIDeviceDriver::cs_release()
{
    digitalWrite(ELFINAAT_SPI_CS_PIN, 1);
}

uint8_t ELFINAATSPIDeviceDriver::transfer (uint8_t data)
{
    return spi.transfer(data);
}

void ELFINAATSPIDeviceDriver::transfer (const uint8_t *data, uint16_t len)
{
    spi.write(data, len);
}

ELFINAATSPIDeviceManager::ELFINAATSPIDeviceManager()
{
}

void ELFINAATSPIDeviceManager::init(void *)
{
}

AP_HAL::SPIDeviceDriver* ELFINAATSPIDeviceManager::device(enum AP_HAL::SPIDevice)
{
    _device.init(); // Defer this until GPIO pin 13 is set up else its a slave
    return &_device;
}

#endif
