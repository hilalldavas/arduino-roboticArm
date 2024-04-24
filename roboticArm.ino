#include <MPU6050.h>
#include <Wire.h>
#include <Servo.h>

MPU6050 mpu;  // MPU60500 sensörü için nesne oluşturuluyor.

Servo servo1, servo2, servo3, servo4;  // Dört adet servo motor için nesneler oluşturuluyor.

const int buttonPin = 6;  // Butonun bağlı olduğu pin
int buttonState = 0;  // Buton durumu (HIGH veya LOW)

void setup() 
{
  Serial.begin(9600);  // Seri haberleşme başlatılıyor.

  // Servo motorlar belirtilen pinlere bağlanıyor.
  servo1.attach(11);  //sağ sol
  servo2.attach(9);   //yukarı aşşağı
  servo3.attach(10);  //ileri geri
  servo4.attach(6);   //kıskaç aç kapa

  mpu.initialize();  // MPU60500 sensörü başlatılıyor.

  pinMode(buttonPin, INPUT);  // Buton pin'i giriş olarak ayarlanıyor.
}

void loop() 
{
  buttonState = digitalRead(buttonPin);  // Butonun durumu okunuyor.

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  if (buttonState == LOW) {
    // Buton basılmamışsa, el hareketlerine göre robot kolunun tepkisini belirle

    if (ay > -5) {
      // Eğer sensör aşağı eğiliyorsa, robot kol ileri uzanır.
      servo3.write(90);
    } else if (ay < 5) {
      // Eğer sensör yukarı eğiliyorsa, robot kol geri uzanır.
      servo3.write(0);
    }

    if (ax > -5) {
      // Eğer sensör sağa eğiliyorsa, robot kol sağa döner.
      servo1.write(0);
    } else if (ax < 5) {
      // Eğer sensör sola eğiliyorsa, robot kol sola döner.
      servo1.write(180);
    }
  } 
    else 
  {
    if (ay > -5) {
      // Eğer sensör aşağı eğiliyorsa, robot kol aşağı yönde hareket eder.
      servo2.write(45);
    } else if (ay < 5) {
      // Eğer sensör yukarı eğiliyorsa, robot kol yukarı yönde hareket eder.
      servo2.write(135);
    } else {
      // Eğer sensör düz duruyorsa, robot kol belirli bir açıya getirir
      servo2.write(90);
    }
      if (ax > -5) {
      // Eğer sensör sağa eğiliyorsa, robot kolun ağzını açar.
      servo4.write(10);
    } else if (ax < 5) {
      // Eğer sensör sola eğiliyorsa, robot kolun ağzını kapatır.
      servo4.write(18);
    }
  }
}