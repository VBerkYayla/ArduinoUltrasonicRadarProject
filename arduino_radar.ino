#include <Servo.h> // Servo için Arduino kütüphanesini yüklüyoruz.

// Arduino üzerindeki bağlantılar için pin atamalarını yapıyoruz.
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 12;

Servo myServo;
long duration;
int distance;

int calculateDistance() {
  digitalWrite(trigPin, LOW); // Pini önce 2 mikrosaniye LOW yapıyoruz.
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Pini sonra 10 mikrosaniye boyunca HIGH yapıyoruz.
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Sesin havadaki hızını gidiş-geliş sürelerini de katarak 2'ye bölüyoruz Yani tek yönlü mesafeyi buluyoruz.
  return distance;
}

void setup() {
  // INPUT ve OUTPUT belirlenir.
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(9600); // Bilgisayarla 9600 baud rate hızında seri haberleşme başlatıyoruz.
  myServo.attach(servoPin);
}

void loop() {
  // 15° ile 165° arası ileri yönde tarama yapmasını sağlıyoruz.
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30); // Motorun belirtilen açıya dönebilmesi için 30 ms bekliyoruz yoksa hatalı sonuç alırız.
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
  
  // 165° ile 15° arası geri yönde tarama yapmasını sağlıyoruz.
  for (int i = 165; i >= 15; i--) {
    myServo.write(i);
    delay(30); // Motorun belirtilen açıya dönebilmesi için 30 ms bekliyoruz yoksa hatalı sonuç alırız.
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}