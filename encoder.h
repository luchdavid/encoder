/*
   ============================================================================
                           ¡¡D I S C L A I M E R!!
   ============================================================================
   Estas a punto de leer el codigo más perro puerco de tu vida
   si por alguna razón lo llegas a leer sientete libre de
   mentarme la madre o enviarme una critica constructiva a:
   
                            Caffeine.Snorter@gmail.com
                            
  ==============================================================================
  ==============================================================================

   encoder.h - Libreria para operar un encoder rotativo tipo potenciometro.
   Creada por CaffeineSnorter
*/


#ifndef encoder_h //Si encoder_h no esta definido
#define encoder_h //define encoder_h junto con los parametros del codigo

#if (ARDUINO >= 100) //Si la version del IDE de arduino es >= a 1.0.0
#include "Arduino.h" //incluye la libreria Arduino.h

#else //Si no
#include "WProgram.h" //incluye la libreria WProgram.h

#endif //Termina condicional


class encoder {

  protected:

    int referenciaGiroReloj;
    int referenciaGiroData;
    int ultimoEstadoSwitch;
    int estadoSwitch;
    bool salida;
    bool estadoGiro;
    int direccionDeGiro; // Derecha = HIGH; Izquierda = LOW;

    unsigned long ultimoTiempoPresionado;
    unsigned long ultimoTiempoDeGiro;
    unsigned long ultimoTiempoDeGiro_;

    int pinReloj;
    int pinData;
    int pinSwitch;

    int estado;
    int estadoDir;


  public:

    //Constructor
    encoder(int pinClk, int pinDat, int pinSw);

    //Metodos
    void init();
    bool isTurning(); //listo
    int isTurningDir();
    //bool switchIsPressed();
    bool switchWasPressed();

};

class Contador : public encoder {

  private:

    int valMin;
    int valMax;
    int numList;
    int contador;
    bool estadoContador;

  public:

    //constructor
    Contador(int pinClk, int pinDat, int pinSw, int _valMin, int _valMax);

    int cuenta();

};


#endif
