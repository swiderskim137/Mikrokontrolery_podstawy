#include <Arduino.h>

class print2
{
public:
    int i;
    float f;
    double d;

    void integer(int x)
    {
        Serial.println(x);
    }
    void kto()
    {
        Serial.println("klasa print2");
    }

private:
};