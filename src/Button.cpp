/**
 *  Copyright (c) 2019 Julian Schroden. All rights reserved.
 *  Licensed under the MIT License. See LICENSE file in the project root for
 *  full license information.
 */

#include <InputDevices/Button.h>

using namespace std::chrono;
using namespace SimpleGPIO;

namespace InputDevices
{
Button::Button(DigitalInputPin buttonPin)
    : buttonPin_(std::move(buttonPin))
    , currentButtonPressTime_(steady_clock::now())
    , lastButtonPressTime_(steady_clock::now())
    , lastButtonReleaseTime_(steady_clock::now())
{
}

void Button::onClick(std::function<void()> callback)
{
   onClickCallback_ = callback;
}

void Button::onLongClick(std::function<void()> callback)
{
   onLongClickCallback_ = callback;
}

void Button::update()
{
   buttonPin_.poll([this](PinEvent event, DigitalPinState state) {
      switch (event)
      {
         case PinEvent::Fall:
         {
            lastButtonReleaseTime_ = steady_clock::now();
            if (lastButtonReleaseTime_ - currentButtonPressTime_ > pressTime)
            {
               if (currentButtonPressTime_ - lastButtonPressTime_ >
                   debounceTime)
               {
                  onClick();
                  lastButtonPressTime_ = currentButtonPressTime_;
               }
            }
            break;
         }
         case PinEvent::Rise:
         {
            currentButtonPressTime_ = steady_clock::now();
            break;
         }
      }
   });

   if (buttonPin_.state() == DigitalPinState::High &&
       steady_clock::now() - currentButtonPressTime_ > longPressTime &&
       currentButtonPressTime_ != lastButtonPressTime_)
   {
      onLongClick();
      lastButtonPressTime_ = currentButtonPressTime_;
   }
}

void Button::onClick()
{
   if (onClickCallback_) onClickCallback_();
}

void Button::onLongClick()
{
   if (onLongClickCallback_) onLongClickCallback_();
}

}  // namespace InputDevices