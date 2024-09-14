#define FL_MRIGHT_0 5
#define FL_MRIGHT_1 6
#define FL_MLEFT_0 9
#define FL_MLEFT_1 10
#define FL_SENSOR_SENSITIVITY_VALUE 400
#define FL_MIN_VALUE_ANALOG 150
#define FL_MIN_BEHIND_VALUE 200

/**
 *  Sensor mais a direita, A1.
 *  Sensor mais a esquerda, A7.
 */

void setup() {
  pinMode(FL_MRIGHT_0, 1);
  pinMode(FL_MRIGHT_1, 1);
  pinMode(FL_MLEFT_0, 1);
  pinMode(FL_MLEFT_1, 1);
}

void loop() {
  uint8_t right_gain = FL_MIN_VALUE_ANALOG;
  uint8_t left_gain = FL_MIN_VALUE_ANALOG;
  right_gain += ((analogRead(A7) < FL_SENSOR_SENSITIVITY_VALUE) ? 106 : ((analogRead(A6) < FL_SENSOR_SENSITIVITY_VALUE) ? 75 : ((analogRead(A5) < FL_SENSOR_SENSITIVITY_VALUE) ? 50 : 0)));
  left_gain += ((analogRead(A1) < FL_SENSOR_SENSITIVITY_VALUE) ? 106 : ((analogRead(A2) < FL_SENSOR_SENSITIVITY_VALUE) ? 75 : ((analogRead(A3) < FL_SENSOR_SENSITIVITY_VALUE) ? 50 : 0)));

  if((right_gain > left_gain) && (right_gain > FL_MIN_BEHIND_VALUE))
  {
    right_behind(right_gain, left_gain);
  }
  else if((left_gain > right_gain) && (left_gain > FL_MIN_BEHIND_VALUE))
  {
    right_behind(right_gain, left_gain);
  }
  else if(analogRead(A4) < FL_SENSOR_SENSITIVITY_VALUE)
  {
    front(); 
  }
  else if(right_gain > left_gain)
  {
    left_front(right_gain, left_gain);
  }
  else if(left_gain > right_gain)
  {
    left_front(right_gain, left_gain);
  }
  delay(20);
}

void stop()
{
  digitalWrite(FL_MRIGHT_0, 1);
  digitalWrite(FL_MRIGHT_1, 1);
  digitalWrite(FL_MLEFT_0, 1);
  digitalWrite(FL_MLEFT_1, 1);
  delay(5);  
}

void front()
{
  stop();
  digitalWrite(FL_MRIGHT_0, 0);
  digitalWrite(FL_MRIGHT_1, 1);
  digitalWrite(FL_MLEFT_0, 0);
  digitalWrite(FL_MLEFT_1, 1);
}

void behind()
{
  stop();
  digitalWrite(FL_MRIGHT_0, 1);
  digitalWrite(FL_MRIGHT_1, 0);
  digitalWrite(FL_MLEFT_0, 1);
  digitalWrite(FL_MLEFT_1, 0);
}

void left_front(uint8_t motor_right, uint8_t motor_left)
{
  stop();
  digitalWrite(FL_MRIGHT_0, 0);
  analogWrite(FL_MRIGHT_1, motor_right);
  analogWrite(FL_MLEFT_0, motor_left);
  digitalWrite(FL_MLEFT_1, 0);
}

void left_behind(uint8_t motor_right, uint8_t motor_left)
{
  stop();
  analogWrite(FL_MRIGHT_0, motor_right);
  digitalWrite(FL_MRIGHT_1, 0);
  digitalWrite(FL_MLEFT_0, 0);
  analogWrite(FL_MLEFT_1, motor_left);
}

void right_front(uint8_t motor_right, uint8_t motor_left)
{
  stop();
  analogWrite(FL_MRIGHT_0, motor_right);
  digitalWrite(FL_MRIGHT_1, 0);
  digitalWrite(FL_MLEFT_0, 0);
  analogWrite(FL_MLEFT_1, motor_left);
}

void right_behind(uint8_t motor_right, uint8_t motor_left)
{
  stop();
  digitalWrite(FL_MRIGHT_0, 0);
  analogWrite(FL_MRIGHT_1, motor_right);
  analogWrite(FL_MLEFT_0, motor_left);
  digitalWrite(FL_MLEFT_1, 0);
}
