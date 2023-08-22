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

#ifndef __AP_HAL_ELFINAAT_GPIO_H__
#define __AP_HAL_ELFINAAT_GPIO_H__

#include "AP_HAL_ELFINAAT.h"

class AP_HAL_ELFINAAT_NS::ELFINAATGPIO : public AP_HAL::GPIO {
public:
    ELFINAATGPIO();
    void    init();
    void    pinMode(uint8_t pin, uint8_t output);
    int8_t  analogPinToDigitalPin(uint8_t pin);
    uint8_t read(uint8_t pin);
    void    write(uint8_t pin, uint8_t value);
    void    toggle(uint8_t pin);

    /* Alternative interface: */
    AP_HAL::DigitalSource* channel(uint16_t n);

    /* Interrupt interface: */
    bool    attach_interrupt(uint8_t interrupt_num, AP_HAL::Proc p,
            uint8_t mode);

    /* return true if USB cable is connected */
    bool    usb_connected(void);

};

class AP_HAL_ELFINAAT_NS::ELFINAATDigitalSource : public AP_HAL::DigitalSource {
public:
    ELFINAATDigitalSource(uint8_t v);
    void    mode(uint8_t output);
    uint8_t read();
    void    write(uint8_t value); 
    void    toggle();

private:
    uint8_t _v;
};

#endif // __AP_HAL_ELFINAAT_GPIO_H__
