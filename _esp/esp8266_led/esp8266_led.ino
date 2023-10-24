    #include <SoftwareSerial.h>
        
    //SoftwareSerial Serial2(17,16); // komunikacja Rx i Tx z modułem 
    
    void setup()
    {
      Serial.begin(9600);
      Serial2.begin(9600); // wartość zależna od modułu, najczęściej 9600 lub 115200
      
      pinMode(11,OUTPUT);    //ustawienie diód LED w stanie niskim
      digitalWrite(11,LOW);
      
      pinMode(12,OUTPUT);
      digitalWrite(12,LOW);
      
      pinMode(13,OUTPUT);
      digitalWrite(13,LOW);
      sendData("AT",1000);
      sendData("AT+RST\r\n",2000); // reset modułu
      sendData("AT+CWMODE=2\r\n",1000); // ustawienie w trybie Access Point
      sendData("AT+CIFSR\r\n",1000); // Uzyskanie adresu IP (domyślnie 192.168.4.1)
      sendData("AT+CIPMUX=1\r\n",1000); // Tryb połączeń wielokrotnych
      sendData("AT+CIPSERVER=1,80\r\n",1000); // Ustawienie serwera na porcie 80
    }
     
    void loop()
    {
      if(Serial2.available()) // sprawdzenie czy moduł otzrymał dane 
      {
        if(Serial2.find("+IPD,"))
        {
         delay(1000); // czekanie na zapełnienie bufora danymi
         
         // odczytanie ID połączenia
         int connectionId = Serial2.read()-48; // odjęcie 48 ponieważ funkcja read() zwraca wartość dziesiętną ASCII na pozycji 48
              
         Serial2.find("pin="); // wyszukanie frazy "pin=" oraz ustawienie tam "kursora"
         
         int pinNumber = (Serial2.read()-48)*10; // pobranie pierwszej cyfry, np. dla pinu 13, pierwsza cyfra to 1, należy ją pomnożyć przez 10
         pinNumber += (Serial2.read()-48); // pobranie drugiej cyfry, np. dla pinu 13, druga cyfra to 3, należy ją dodać do poprzedniego wyniku
         
         digitalWrite(pinNumber, !digitalRead(pinNumber)); // zmiana stanu wybranego pinu    
         
         // zamknięcie połączenia
         String closeCommand = "AT+CIPCLOSE="; 
         closeCommand+=connectionId; // ID połączenia odczytane na początku
         closeCommand+="\r\n";
         
         sendData(closeCommand,1000); 
        }
      }
    }
     
    /*
    * Funkcja wysyłająca komendy do modułu Serial2
    * Parametry:
    * command - komenda do wysłania
    * timeout - czas oczekiwania na odpowiedź
    */
    String sendData(String command, const int timeout)
    {
        String response = "";
        
        Serial2.print(command); // wysłanie polecenia do Serial2
        
        long int time = millis();
        
        while( (time+timeout) > millis())
        {
          while(Serial2.available()) //jeśli są jakieś dane z modułu, wtedy następuje ich odczyt
          {
            char c = Serial2.read(); // odczyt kolejnego znaku
            response += c;
          }  
        } 
        Serial.print(response);
        return response;
    }
