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

#define deadband 61

int lim_inf=511-deadband;
int lim_sup=511+deadband;

void setup() {
  pinMode(arriba,OUTPUT);
  pinMode(abajo,OUTPUT);
  pinMode(izquierda,OUTPUT);
  pinMode(derecha,OUTPUT);
  pinMode(f1,OUTPUT);
  pinMode(f2,OUTPUT);
  pinMode(f3,OUTPUT); 

  pinMode(0,INPUT);
  pinMode(1,INPUT); 
  
  pinMode(boton1,INPUT_PULLUP);
  pinMode(boton2,INPUT_PULLUP);
  pinMode(boton3,INPUT_PULLUP);
}

void loop() {
  if(!digitalRead(boton1)) {digitalWrite(f1,LOW);}
  else {digitalWrite(f1,HIGH);}

  if(!digitalRead(boton2)) {digitalWrite(f2,LOW);}
  else {digitalWrite(f2,HIGH);}

  if(!digitalRead(boton3)) {digitalWrite(f3,LOW);}
  else {digitalWrite(f3,HIGH);}

  int v=analogRead(joy_x);

  if (v<lim_inf){
    digitalWrite(izquierda,LOW);
    digitalWrite(derecha,HIGH);
  }
  if ((v>(lim_inf+1))&&(v<(lim_sup-1))){
    digitalWrite(izquierda,HIGH);
    digitalWrite(derecha,HIGH);
  }
  if (v>lim_sup){
    digitalWrite(izquierda,HIGH);
    digitalWrite(derecha,LOW);
  }

  v=analogRead(joy_y);

  if (v<lim_inf){
    digitalWrite(arriba,LOW);
    digitalWrite(abajo,HIGH);
  }
  if ((v>(lim_inf+1))&&(v<(lim_sup-1))){
    digitalWrite(arriba,HIGH);
    digitalWrite(abajo,HIGH);
  }
  if (v>lim_sup){
    digitalWrite(arriba,HIGH);
    digitalWrite(abajo,LOW);
  }
}
