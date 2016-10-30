//Joystick analogico para spectrum
#define arriba 2
#define abajo 3
#define izquierda 4
#define derecha 5
#define f1 6
#define f2 7
#define f3 8

#define boton1 9
#define boton2 10
#define boton3 11
#define boton4 12

#define joy_x 0
#define joy_y 1

#define deadband 75

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

  digitalWrite(arriba, LOW); //inicializar salidas latch a cero para activar el pin de direccion que sera cambiado a la salida
  digitalWrite(abajo, LOW);
  digitalWrite(izquierda, LOW);
  digitalWrite(derecha, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(f3, LOW);

  pinMode(0,INPUT);
  pinMode(1,INPUT); 
  
  pinMode(boton1,INPUT_PULLUP);
  pinMode(boton2,INPUT_PULLUP);
  pinMode(boton3,INPUT_PULLUP);
  pinMode(boton4,INPUT_PULLUP);

  // set up Timer 1
  TCCR1A = 0;          // normal operation
  TCCR1B = bit(WGM12) | bit(CS10) | bit (CS12);   // CTC, scale to clock / 1024
  OCR1A =  999;       // compare A register value (1000 * clock speed / 1024)
  TIMSK1 = bit (OCIE1A);             // interrupt on Compare A Match
}

void loop() {
  if(!digitalRead(boton1)) {pinMode(f1,OUTPUT);}
  else {pinMode(f1,INPUT);}

//  if(!digitalRead(boton2)) {pinMode(f2,OUTPUT);}
//  else {pinMode(f2,INPUT);}

//  if(!digitalRead(boton3)) {pinMode(f3,OUTPUT);}
//  else {pinMode(f3,INPUT);}

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
//gestion temporizadores de autodisparo
ISR(TIMER1_COMPA_vect)
{
    static boolean state_b2 = false; //estado salidas de los autofires
    static boolean state_b3 = false;
    static boolean state_b4 = false;
    static byte cont_b3 = 0;//contadores para la division de autofire
    static byte cont_b4 = 0;

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

    if(!digitalRead(boton2)) {
       pinMode (f2, state_b2 ? OUTPUT : INPUT);
    }

    if(!digitalRead(boton3)) {
       pinMode (f2, state_b3 ? OUTPUT : INPUT);
    }

    if(!digitalRead(boton4)) {
       pinMode (f2, state_b4 ? OUTPUT : INPUT);
    }

    if (digitalRead(boton4) & digitalRead(boton3) & digitalRead(boton2)){
      pinMode (f2, INPUT);
    }
}


