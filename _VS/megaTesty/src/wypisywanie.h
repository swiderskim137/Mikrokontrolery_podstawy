//#include <Arduino.h>

class print
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
        Serial.println("klasa print");
    }

private:
};