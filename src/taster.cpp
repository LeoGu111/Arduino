#include <display.h>

// Taster für schnell aus wahl
void Tasterfunktion()
{
    if (digitalRead(PIN_Timer_1) == HIGH)
    {
        Timer_1 = TimerArray[0];
        Timer_1_1 = TimerArray[0];
        Menue_Timer_1 = 1;
        SUB_ACTIVE = 0;
        SUB_ACTIVE_2 = 0;
        SUB_ACTIVE_3 = 0;
    }
    if (digitalRead(PIN_Timer_2) == HIGH)
    {
        Timer_2 = TimerArray[1];
        Timer_2_1 = TimerArray[1];
        Menue_Timer_1 = 1;
        SUB_ACTIVE = 0;
        SUB_ACTIVE_2 = 0;
        SUB_ACTIVE_3 = 0;
    }
    if (digitalRead(PIN_Timer_3) == HIGH)
    {
        Timer_3 = TimerArray[2];
        Timer_3_1 = TimerArray[2];
        Menue_Timer_1 = 1;
        SUB_ACTIVE = 0;
        SUB_ACTIVE_2 = 0;
        SUB_ACTIVE_3 = 0;
    }
}