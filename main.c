#include <LiquidCrystal.h>
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define potenciometro  A0
#define pinoBotaoTempo  8
#define pinoBotaoPower  9
#define pinoRele 7 

int potenciometroRead;
int potenciometroCoverted;

bool setTemp = false;
bool power = false;

bool btnSetTemp;
bool btnSetPower;

int tempSetted;
float tempo;

int tempAux;

bool ligar = false;
void setup() {
  Serial.begin(9600);
  pinMode(pinoBotaoTempo, INPUT_PULLUP); 
  pinMode(pinoBotaoPower, INPUT_PULLUP); 

  pinMode(pinoRele, OUTPUT); 
  digitalWrite(pinoRele, HIGH);

  lcd.clear();
  lcd.begin(16, 2);

}

void loop() {
  
  Serial.println(tempo);
  Serial.println(tempSetted);

  btnSetTemp = digitalRead(pinoBotaoTempo);
  btnSetPower = digitalRead(pinoBotaoPower);
  
  potenciometroRead = analogRead(potenciometro);
  potenciometroCoverted = map(potenciometroRead, 0, 1023, 1, 24);

  if(setTemp == false){
  lcd.setCursor(0, 0);
  lcd.write("Length: ");
  lcd.print(int(potenciometroCoverted));
  lcd.write(" hrs");
  delay(500);
  lcd.clear();
  }else{
  lcd.setCursor(0, 0);
  lcd.print("Length Set:");
  lcd.print(tempSetted);
  lcd.write(" hrs/ ");

  
  lcd.setCursor(8, 1);
  lcd.print("Pass:");
  lcd.print((tempo / 3600));
  lcd.write("hrs");

  }
    
  lcd.setCursor(0, 1);
  lcd.write("Power:");
  lcd.print(power);
  

  
  if(btnSetTemp == false)
  {
    tempSetted = potenciometroCoverted;
    setTemp = true;
  }
  
  
  if(btnSetPower == false)
  {
    ligar = true;
  }
  
  if(ligar == true)
  {
    powerSys();
  }

}

void contarTempo(bool comando){
 if(comando == true){
    tempo = tempo + 1;
    delay(1000);
    Serial.print("Tempo decorrido: ");
    Serial.println(tempo);
    Serial.print("Tempo setado");
    Serial.println(tempSetted);
 }else{
  tempo = 0;
 }
}
void ligaRele(bool comando){
  if(comando == true){
  Serial.println("RELE OFF, ENERGIA PASSANDO");
 power = true;

  }else{
  power = false;
 
  }
}
void powerSys(){
  tempAux = (tempo / 3600);
    if(tempAux >= tempSetted){
  	contarTempo(false);
    ligaRele(false);
    ligar = false;
    Serial.println("Desetratacao concluida");
    digitalWrite(pinoRele, HIGH); //DESLIGA O MÓDULO RELÉ (LÂMPADA APAGA)
  }else{
    contarTempo(true);
    ligaRele(true);
    Serial.println("Iniciando Desetratacao");
    digitalWrite(pinoRele, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
  }
}
