#ifndef _INPUT_DEVICES_ENCODER_h
#define _INPUT_DEVICES_ENCODER_h

#include <SimpleGPIO.h>

#include <functional>
#include <chrono>

class Encoder
{
public:
   Encoder(DigitalInputPin encoderAPin, DigitalInputPin encoderBPin);

   void onScroll(std::function<void(int)> callback);

   void update();

private:
   void onScroll(int distance);

private:
   DigitalInputPin encoderAPin_;
   DigitalInputPin encoderBPin_;

   std::chrono::steady_clock::time_point lastEncoderPulse_;
   int lastScrollOfset_ = 0;
   std::function<void(int)> onScrollCallback_;

   std::chrono::milliseconds encoderDebounceTime = std::chrono::milliseconds(100);
};

#endif