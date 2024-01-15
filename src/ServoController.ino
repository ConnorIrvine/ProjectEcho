#include <Servo.h> 

// Declare signal input pin
int emgSignal = A0;

class Movement
{
  public:
  bool move;
  bool wasMoving;
  Servo Servo1;
  int servoPin;
  float threshold;
  Movement();
  void Update(float RMS);
};

Movement::Movement()
{
  move = false;
  wasMoving = false;
  servoPin = 3;
  threshold = 42;
}

void Movement::Update(float RMS)
{
  // Binary vals
  if(RMS >= threshold) move = true;
  else if (RMS < threshold && move == true) // We just told it to stop moving
  {
    move = false;
    wasMoving = true;
  }
  else
  {
    move = false;
    wasMoving = false;
  }
}

class Time
{
  public:
  static float time;
  static float previousTime;
  void Update();
};

float Time::time = 0;
float Time::previousTime = 0;

void Time::Update()
{
  Time::previousTime = time;
  Time::time = millis();
}

class Derivative
{
  public:
  float derivative;
  int voltage;
  int previousVoltage;
  float Update(int value);
};

float Derivative::Update(int value)
{
  voltage = value;
  if(Time::time == 0) previousVoltage = voltage;

  float interval = Time::time - Time::previousTime;
  derivative = abs((voltage - previousVoltage) / interval);

  previousVoltage = voltage;
  return derivative;
}

class RMS
{
  public:
  RMS();
  float Update(float val);
  private:
  float *derivatives;
  float lastVal;
  int size;
  const int n = 30;
};

RMS::RMS()
{
  size = 0;
  derivatives = new float[n];
  lastVal = 0;
}

float RMS::Update(float val)
{
  if(size < n)
  {
      derivatives[size] = val;
      size++;
      return lastVal;
  }

  float sum = 0;
  for(int i = 0; i < n; i++)
  {
    sum+=pow(derivatives[i], 2);
  }

  float mean = sum / (float)n;
  float RMS = sqrt(mean);
  lastVal = RMS;

  size = 0;

  return RMS; 
}

Time m_time;
Derivative m_derivative;
RMS m_RMS;
Movement m_move;

void setup()
{ 
  // Attach servo object to the pin 
  m_move.Servo1.attach(m_move.servoPin); 
  // Set baud rate (data rate in bits per sec)
  Serial.begin(9600);
}

void loop()
{
  // Update time
  m_time.Update();

  // Get current sampled signal val
  int val = analogRead(emgSignal);

  // Take derivative
  float derivative = m_derivative.Update(val);

  // Take RMS
  float RMS = m_RMS.Update(derivative);

  // Check if servo should move
  m_move.Update(RMS);

  // Move servo
  if(m_move.move == true) 
  {
    m_move.Servo1.write(0);
  }
  else
  {
    m_move.Servo1.write(180);
  }
}