#ifndef _INPUT_DEVICES_ENCODER_h
#define _INPUT_DEVICES_ENCODER_h

#include <SimpleGPIO/GPIO.h>

#include <chrono>
#include <functional>


namespace InputDevices
{
class Encoder
{
public:
   Encoder(SimpleGPIO::DigitalInputPin encoderAPin,
           SimpleGPIO::DigitalInputPin encoderBPin);

   void onScroll(std::function<void(int)> callback);

   void update();

private:
   void onScroll(int distance);

private:
   SimpleGPIO::DigitalInputPin encoderAPin_;
   SimpleGPIO::DigitalInputPin encoderBPin_;

   std::chrono::steady_clock::time_point lastEncoderPulse_;
   int lastScrollOfset_ = 0;
   std::function<void(int)> onScrollCallback_;

   std::chrono::milliseconds debounceTime = std::chrono::milliseconds(5);
   std::chrono::milliseconds directionDebounceTime =
       std::chrono::milliseconds(100);
};

}  // namespace InputDevices

#endif