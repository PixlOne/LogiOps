/*
 * Copyright 2019-2020 PixlOne, michtere
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "ThresholdGesture.h"

using namespace logid::actions;

ThresholdGesture::ThresholdGesture(Device *device, libconfig::Setting &root) :
    Gesture (device), _config (device, root)
{
}

void ThresholdGesture::press(bool init_threshold)
{
    _axis = init_threshold ? _config.threshold() : 0;
    this->_executed = false;
}

void ThresholdGesture::release(bool primary)
{
    (void)primary; // Suppress unused warning
    
    this->_executed = false;
}

void ThresholdGesture::move(int16_t axis)
{
    _axis += axis;

    if(!this->_executed && metThreshold()) {
        _config.action()->press();
        _config.action()->release();
        this->_executed = true;
    }
}

bool ThresholdGesture::metThreshold() const
{
    return _axis >= _config.threshold();
}

bool ThresholdGesture::wheelCompatibility() const
{
    return false;
}