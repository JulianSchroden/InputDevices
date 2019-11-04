/**
 *  Copyright (c) 2019 Julian Schroden. All rights reserved.
 *  Licensed under the MIT License. See LICENSE file in the project root for
 *  full license information.
 */

#ifndef _INPUT_DEVICES_BUTTON_h
#define _INPUT_DEVICES_BUTTON_h

#include <SimpleGPIO/GPIO.h>

#include <chrono>
#include <functional>


namespace InputDevices
{
class Button
{
public:
   Button(SimpleGPIO::DigitalInputPin buttonPin);

   void onClick(std::function<void()> callback);
   void onLongClick(std::function<void()> callback);

   void update();

private:
   void onClick();
   void onLongClick();

private:
   SimpleGPIO::DigitalInputPin buttonPin_;
   std::function<void()> onClickCallback_;
   std::function<void()> onLongClickCallback_;

   std::chrono::steady_clock::time_point currentButtonPressTime_;
   std::chrono::steady_clock::time_point lastButtonPressTime_;
   std::chrono::steady_clock::time_point lastButtonReleaseTime_;

   std::chrono::milliseconds pressTime = std::chrono::milliseconds(10);
   std::chrono::seconds longPressTime = std::chrono::seconds(1);
   std::chrono::milliseconds debounceTime = std::chrono::milliseconds(50);
};

}  // namespace InputDevices

#endif