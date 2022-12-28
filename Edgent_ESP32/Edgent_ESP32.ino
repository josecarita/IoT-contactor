
// Llenar con información de plantilla de Blynk aquí
#define BLYNK_TEMPLATE_ID "TMPLTl396KbO" 
#define BLYNK_DEVICE_NAME "ContactorWifi"

//versión de Blynk
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG


// Descomentar la tarjeta que usarás, o configura una tarjeta en Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7

#include "BlynkEdgent.h"

int RELE = 2;      // rele en pin 2
int TRIG = 18;     // trigger en pin 18
int ECO = 5;       // echo en pin 5
float DURACION, DISTANCIA;

void setup()
{
  Serial.begin(115200); //establece comunicación serial
  delay(100); //espera 100ms
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  //pinMode(PULSADOR,INPUT_PULLUP);  //pulsador como entrada pullup
  pinMode(RELE, OUTPUT);   // rele como salida
  digitalWrite(RELE,HIGH);  //estado inicial de rele es LOW

  BlynkEdgent.begin();
  
}

void loop() {
  BlynkEdgent.run();
  digitalWrite(TRIG, LOW);     // generacion del pulso a enviar
  delayMicroseconds(2);        // al pin conectado al trigger
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso alto en Echo
  DISTANCIA = DURACION / 58.3;    // distancia medida en centimetros

  Serial.println(DISTANCIA);    //linea de prueba de sensor
  delay(400);                   //linea de prueba de sensor
  if (DISTANCIA <= 150.00)        // si la distancia medida es menor o igual a 100 centimetros
  {                               // entonces se activa el rele
    digitalWrite(RELE,LOW);
  }
   Blynk.virtualWrite(V1, DISTANCIA); //envia el valor de DISTANCIA a V1
}

BLYNK_WRITE(V0)
{
  int vpulsador = param.asInt(); //el pulsador virtual obtiene su valor desde V0
  if (vpulsador==1)              //si el pulsador virtual es '1' entonces
  {                              //el rele se apaga
    digitalWrite(RELE,HIGH);
  }
}
