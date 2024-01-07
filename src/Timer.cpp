#include <Timer.h>




Time convertFromIndustrialHours(double industrialHours) 
{
    int hours = static_cast<int>(industrialHours); // Extrahiere die ganzen Stunden
    double fractionalPart = industrialHours - hours; // Der Dezimalteil entspricht den Minuten und Sekunden

    int minutes = static_cast<int>(fractionalPart * 60); // Umwandlung des Dezimalteils in Minuten
    double fractionalMinutes = (fractionalPart * 60) - minutes; // Der Dezimalteil entspricht den Sekunden

    int seconds = static_cast<int>(fractionalMinutes * 60); // Umwandlung des Dezimalteils in Sekunden

    Time result { hours, minutes, seconds };
    return result;
}

