#include <display.h>

void Setup_Encoder()
{
  pinMode(PIN_SW, INPUT);

  // Konfiguriere die Pins für den Encoder
  ESP32Encoder::useInternalWeakPullResistors = UP;
  encoder.attachSingleEdge(PIN_DT, PIN_CLK);
}

void encoder_position()
{
  // Lese die aktuelle Position des Encoders
  int rawPosition = encoder.getCount();
  bool x = debounceEncoder(rawPosition, pos);
  if (x == 1)
  {
    if (pos < rawPosition)
    {
      pos = pos + 1;
    }
    else
    {
      pos = pos - 1;
    }
    encoder.setCount(pos);
  }
}

bool debounceEncoder(int rawPosition, int lastPosition)
{

  unsigned long currentTime = millis();

  if (rawPosition == lastPosition)
  {
    lastDebounceTime = currentTime;
  }

  if (currentTime - lastDebounceTime > debounceDelay)
  {
    return true; // Successfully updated debounced position
  }
  else
  {
    return false; // No update of debounced position
  }
}
