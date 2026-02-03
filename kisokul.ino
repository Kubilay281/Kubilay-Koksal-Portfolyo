#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

int potPin = A0;
int oyuncuSatir = 0;
int engelSutun = 15;
int engelSatir = 0;
int skor = 0;
unsigned long sonHareketZamani = 0;
int hiz = 200; 
int tetik=9;
int echo=10;


void setup() {
  pinMode(tetik,OUTPUT);
  pinMode(echo,INPUT);
  lcd.init();
  lcd.backlight();
  randomSeed(analogRead(A1)); 
  engelSatir = random(0, 2);  
}

void loop() {
  
  int potDeger = analogRead(potPin);
  if (potDeger > 512) {
    oyuncuSatir = 0;
  } else {
    oyuncuSatir = 1;
  }

  
  if (millis() - sonHareketZamani > hiz) {
    sonHareketZamani = millis();
    engelSutun--; 

    
    if (engelSutun < 0) {
      engelSutun = 15;
      engelSatir = random(0, 2); 
      skor++;
      hiz = max(50, hiz - 5); 
    }
  }

  
  if (engelSutun == 0 && engelSatir == oyuncuSatir) {
    gameOver();
  }

  
  lcd.clear();
  lcd.setCursor(0, oyuncuSatir);
  lcd.print(">"); 
  
  lcd.setCursor(engelSutun, engelSatir);
  lcd.print("#"); 

  lcd.setCursor(13, 0); 
  lcd.print(skor);
  
  delay(10); 
}

void gameOver() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("OYUN BITTI!");
  lcd.setCursor(5, 1);
  lcd.print("SKOR: ");
  lcd.print(skor);

  bool bekliyor = true;
  
  while(bekliyor) {
    digitalWrite(tetik, LOW);
    delayMicroseconds(2);
    digitalWrite(tetik, HIGH);
    delayMicroseconds(10); 
    digitalWrite(tetik, LOW);

    long sure = pulseIn(echo, HIGH);
    int mesafe = sure * 0.034 / 2;

    
    if (mesafe > 0 && mesafe < 10) {
      bekliyor = false;
    }
    
    delay(100); 
  }
  skor = 0;
  hiz = 200;
  engelSutun = 15;
  engelSatir = random(0, 2);
  sonHareketZamani = millis(); 
  
  lcd.clear(); 
}