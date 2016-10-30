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
}

void loop() {
  if(!digitalRead(boton1)) {pinMode(f1,OUTPUT);}
  else {pinMode(f1,INPUT);}

  if(!digitalRead(boton2)) {pinMode(f2,OUTPUT);}
  else {pinMode(f2,INPUT);}

  if(!digitalRead(boton3)) {pinMode(f3,OUTPUT);}
  else {pinMode(f3,INPUT);}

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
