#include "Encoder.h"

using namespace std::chrono;

Encoder::Encoder(DigitalInputPin encoderAPin, DigitalInputPin encoderBPin)
    : encoderAPin_(std::move(encoderAPin))
    , encoderBPin_(std::move(encoderBPin))
    , lastEncoderPulse_(steady_clock::now())
{
}

void Encoder::onScroll(std::function<void(int)> callback)
{
   onScrollCallback_ = callback;
}

void Encoder::update()
{
   int currentScrollOffset = 0;
   encoderAPin_.poll(
       [&currentScrollOffset, this](PinEvent event, DigitalPinState state) {
          if (state == encoderBPin_.state())
          {
             currentScrollOffset = -1;
          }
          else
          {
             currentScrollOffset = 1;
          }
       });

   if (currentScrollOffset)
   {
      steady_clock::time_point currentEncoderPulse = steady_clock::now();

      if ((currentScrollOffset < 0 && lastScrollOfset_ > 0) ||
          (currentScrollOffset > 0 && lastScrollOfset_ < 0))
      {
         if ((currentEncoderPulse - lastEncoderPulse_) < encoderDebounceTime)
         {
            return;
         }
      }

      onScroll(currentScrollOffset);
      lastEncoderPulse_ = currentEncoderPulse;
      lastScrollOfset_ = currentScrollOffset;
   }
}

void Encoder::onScroll(int distance)
{
   if (onScrollCallback_) onScrollCallback_(distance);
}