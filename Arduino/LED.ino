void setup() {
  pinMode(2, OUTPUT); // устанавливаем 2 и 3 пин на отправку данных
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char a = Serial.read();

    if (a == 'b') {
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);
      Serial.print("Blue is on");
    } else if (a == 'r') {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      Serial.print("Red is on");
    } else if (a == 'p') {
      int val = analogRead(0);
      Serial.print(val);
    }
  }
}