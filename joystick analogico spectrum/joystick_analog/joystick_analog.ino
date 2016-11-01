//Joystick analogico para spectrum
//Stormbytes 2016

//salidas para el interface kempston
#define arriba 2  //D2
#define abajo 3   //D3
#define izquierda 4 //D4
#define derecha 5 //D5
#define f1 6  //D6
#define f2 7 //D7
#define f3 8 //D8

// botones 1,2,3,4 mapeados a la salida f1
#define boton1 9  //sin autofire D9
#define boton2 10 //autofire nivel 1 D10
#define boton3 11 //autofire nivel 2  D11
#define boton4 12 //autofire nivel 3  D12
//botones sin autofire:
#define fire2 0 //mapeado a f2  (TX)
#define fire3 1 //mapeado a f3  (RX)

#define joy_x 0 //entrada joystick analogico X izquierdo A0
#define joy_y 1 //entrada joystick analogico Y izquierdo  A1

#define deadband 75 //valor de punto muerto para los ejes (ajusta sensibilidad)

int lim_inf=511-deadband;
int lim_sup=511+deadband;

void setup() {  //las salidas se programan como entradas para simular colector abierto
  pinMode(arriba,INPUT);
  pinMode(abajo,INPUT);
  pinMode(izquierda,INPUT);
  pinMode(derecha,INPUT);
  pinMode(f1,INPUT);
  pinMode(f2,INPUT);
  pinMode(f3,INPUT); 
  
  pinMode(fire2,INPUT); //boton fire 2
  pinMode(fire3,INPUT); //boton fire 3 
  
  digitalWrite(arriba, LOW); //inicializar salidas latch a cero para activar el pin de direccion que sera cambiado a la salida
  digitalWrite(abajo, LOW);
  digitalWrite(izquierda, LOW);
  digitalWrite(derecha, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(f3, LOW);

  
  pinMode(boton1,INPUT_PULLUP);
  pinMode(boton2,INPUT_PULLUP);
  pinMode(boton3,INPUT_PULLUP);
  pinMode(boton4,INPUT_PULLUP);

  // configurar el timer 1 para interrupcion por comparacion
  TCCR1A = 0;          // normal operation
  TCCR1B = bit(WGM12) | bit(CS10) | bit (CS12);   // CTC, scale to clock / 1024 entrada timer=f_reloj/1024(preescaler)
  OCR1A =  999;       // compare A register value (1000 * clock speed / 1024) valor a comparar
  TIMSK1 = bit (OCIE1A);             // interrupt on Compare A Match  interrupcion al igualar
}

void loop() {
  
  if(!digitalRead(fire2)) {pinMode(f2,OUTPUT);} //fire2 (fire2 y fire3 no tienen autofire)
    else{pinMode(f2,INPUT);}
  if(!digitalRead(fire3)) {pinMode(f3,OUTPUT);} //fire3
     else{pinMode(f3,INPUT);}
     
  int v=analogRead(joy_x);

  if (v<lim_inf){
    pinMode(izquierda,OUTPUT);
    pinMode(derecha,INPUT);
  }
  if ((v>(lim_inf+1))&&(v<(lim_sup-1))){
    pinMode(izquierda,INPUT);
    pinMode(derecha,INPUT);
  }
  if (v>lim_sup){
    pinMode(izquierda,INPUT);
    pinMode(derecha,OUTPUT);
  }

  v=analogRead(joy_y);

  if (v<lim_inf){
    pinMode(arriba,OUTPUT);
    pinMode(abajo,INPUT);
  }
  if ((v>(lim_inf+1))&&(v<(lim_sup-1))){
    pinMode(arriba,INPUT);
    pinMode(abajo,INPUT);
  }
  if (v>lim_sup){
    pinMode(arriba,INPUT);
    pinMode(abajo,OUTPUT);
  }

}


//rutina servicio de interrupcion al timer 1
//gestion temporizadores de autodisparo
ISR(TIMER1_COMPA_vect)
{
    //variables estaticas para almacenar el estado del autofire de los distintos botones:
    static boolean state_b2 = false; //estado salidas de los autofires
    static boolean state_b3 = false;
    static boolean state_b4 = false;
    static byte cont_b3 = 0;//contadores para la division de autofire
    static byte cont_b4 = 0;
    
    //calcular y actualizar el estado de las distintas salidas:
    state_b2 = !state_b2;  // toggle valor de b2 (no necesita division)
    
    cont_b3++;
    if (cont_b3 == 3){    //divide entre 2
      cont_b3=0;
      state_b3=!state_b3;
    }
    
    cont_b4++;
    if (cont_b4 == 5){  //divide entre 4
      cont_b4=0;
      state_b4=!state_b4;
    }
    
    //comprobar si se pulsan los botones de disparo:
    if(!digitalRead(boton1)) {pinMode(f1,OUTPUT);} //el boton 1 actua sin autofire
     
    if(!digitalRead(boton2)) {
       pinMode (f1, state_b2 ? OUTPUT : INPUT);
    }

    if(!digitalRead(boton3)) {
       pinMode (f1, state_b3 ? OUTPUT : INPUT);
    }

    if(!digitalRead(boton4)) {
       pinMode (f1, state_b4 ? OUTPUT : INPUT);
    }
    // de no haber ningun boton pulsador desactivamos la salida inmediatamente:
    if (digitalRead(boton4) & digitalRead(boton3) & digitalRead(boton2) & digitalRead(boton1)){
      pinMode (f1, INPUT);
    }
}


