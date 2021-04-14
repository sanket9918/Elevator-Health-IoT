#define trigPin 9
#define echoPin 8
#define buzzer 10
#define led 11
#define HighLvl 12
#define LowLvl 7
long duration;
float distanceInch;
int timer;
int baselineTemp = 0;
int celsius = 0;
int fahrenheit = 0;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(A0, INPUT); //Temp
  pinMode(led, OUTPUT);
  pinMode(HighLvl, OUTPUT);
  pinMode(LowLvl, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  //Temp
  baselineTemp = 40;
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F\n");

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distanceInch = duration * 0.0133 / 2;
  digitalWrite(buzzer, HIGH);
  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  timer = distanceInch * 10;
  delay(timer);
  if (distanceInch <= 20)
  {
    digitalWrite(HighLvl, HIGH);
    Serial.print("High\n");
  }

  else
  {
    digitalWrite(HighLvl, LOW);
    Serial.print("Low\n");
  }
  if (distanceInch >= 50)
  {
    digitalWrite(LowLvl, HIGH);
    Serial.print("High\n");
  }
  else
  {
    digitalWrite(LowLvl, LOW);
    Serial.print("Low\n");
  }

  if (celsius < baselineTemp)
  {
    Serial.print("0 0 0");
    if (celsius >= baselineTemp && celsius < baselineTemp + 10)
    {
      Serial.print("1 0 0");
      if (celsius >= baselineTemp + 10 && celsius < baselineTemp + 20)
      {
        Serial.print("1 1 0");
      }
      if (celsius >= baselineTemp + 20 && celsius < baselineTemp + 30)
      {
        Serial.print("1 1 1");
      }
      if (celsius >= baselineTemp + 30)
      {
        Serial.print("1 1 1");
      }
    }
  }
}