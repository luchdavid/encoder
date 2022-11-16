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
  
   encoder.cpp - Libreria para operar un encoder rotativo tipo potenciometro.
   Creada por CaffeineSnorter
*/

#include "encoder.h"

encoder::encoder(int pinClk, int pinDat, int pinSw) {
  pinReloj = pinClk;
  pinData = pinDat;
  pinSwitch = pinSw;

  estado = 0;
  estadoDir = 0;
}

void encoder::init() {

  pinMode(pinReloj, INPUT);
  pinMode(pinData, INPUT);
  pinMode(pinSwitch, INPUT_PULLUP);

  referenciaGiroReloj = digitalRead(pinReloj);
  referenciaGiroData = digitalRead(pinData);
  ultimoEstadoSwitch = HIGH;
  ultimoTiempoDeGiro = 0;
  ultimoTiempoDeGiro_ = 0;
  ultimoTiempoPresionado = 0;


}

bool encoder::isTurning() {

  //unsigned long ultimoTiempoDeGiro;

  bool lecturaReloj = digitalRead(pinReloj);
  bool lecturaData = digitalRead(pinData);

  switch (estado) {

    case 0:

      if ((lecturaReloj != referenciaGiroReloj) or (lecturaData != referenciaGiroData)) { //Se detecto un cambio de giro
        //Puede ser verdadero o estar rebotando
        ultimoTiempoDeGiro_ = millis();
        estado = 1;

      }

      break;

    case 1:

      if (!(lecturaReloj != referenciaGiroReloj) or !(lecturaData != referenciaGiroData)) {

        estado = 0;

      }
      else if ((millis() - ultimoTiempoDeGiro_) > 5) {


        estado = 2;

        referenciaGiroReloj = digitalRead(pinReloj);
        referenciaGiroData = digitalRead(pinData);

      }

      break;


    case 2:

      estadoGiro = true;

      estado = 3;

      return estadoGiro;

      break;


    case 3:

      if (estadoGiro) {

        estadoGiro = !estadoGiro;

      }

      estado = 0;

      break;

  }

  return estadoGiro;;
}


int encoder::isTurningDir() { //Crear maquina de estados

  int lecturaReloj = digitalRead(pinReloj);
  int lecturaData = digitalRead(pinData);
  //unsigned long ultimoTiempoDeGiro;


  if (direccionDeGiro != 0) {

    direccionDeGiro = 0;
  }

  if (lecturaReloj != referenciaGiroReloj) {

    if ((millis() - ultimoTiempoDeGiro ) > 5) {

      if (lecturaData != lecturaReloj) {

        direccionDeGiro = 1;

      }
      else {

        direccionDeGiro = -1;

      }
      ultimoTiempoDeGiro = millis();
    }

  }
  referenciaGiroReloj = lecturaReloj;


  return direccionDeGiro;

}

bool encoder::switchWasPressed() {
  
  if (salida){
    salida = 0;
    }
    
  int lecturaSwitch = digitalRead(pinSwitch);

  if (lecturaSwitch != ultimoEstadoSwitch) {
    ultimoTiempoPresionado = millis();
  }
  if ((millis() - ultimoTiempoPresionado) > 10) {

    if (lecturaSwitch != estadoSwitch) {
      estadoSwitch = lecturaSwitch;

      if (!estadoSwitch) {
        salida = !salida;
      }
    }
  }
  ultimoEstadoSwitch = lecturaSwitch;

  return salida;
}


Contador::Contador(int pinClk, int pinDat, int pinSw, int _valMin, int _valMax) : encoder(pinClk, pinDat, pinSw) {
  valMin = _valMin;
  valMax = _valMax;
  //estadoContador = 0;
}


int Contador::cuenta() {//crear maquina de estados

  int lecturaReloj = digitalRead(pinReloj);
  int lecturaData = digitalRead(pinData);
  unsigned long ultimoTiempoDeGiro;

  if (lecturaReloj != referenciaGiroReloj) {

    if ((millis() - ultimoTiempoDeGiro ) > 5) {

      if (lecturaData != lecturaReloj) {

        contador++;

      }
      else {

        contador--;

      }
      ultimoTiempoDeGiro = millis();
    }

  }
  referenciaGiroReloj = lecturaReloj;

  if (contador > valMax) {
    contador = valMin;
  }
  else if (contador < valMin) {
    contador = valMax;
  }


  return contador;
}
