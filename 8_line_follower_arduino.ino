int sensor[4];
int weight[] = {-4,-2,2,4};

int left = 10;    //pwm of left motor
int right = 11;   //pwm of right motor
int i=0;

int kp = 2, ki = 0.01, kd = 1.5;

int error=0, error_sum=0, error_diff=0, old_error=0;
int pid_correct = 0, left_rpm = 0, right_rpm = 0;
int base = 120;

void setup() 
{
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  Serial.begin(9600);
}

void loop() 
{
  read_sensors();
  calc_error();
  pid_out();
  motor_out();
}

void read_sensors()
{
  sensor[0]=digitalRead(3);
  sensor[1]=digitalRead(4);
  sensor[2]=!digitalRead(5);
  sensor[3]=!digitalRead(6);
}

void calc_error()
{
  int sum = 0;
  for(i=0;i<4;i++)
  {
    sum = sum + sensor[i]*weight[i];
  }
  error = 0-sum;
}

void pid_out()
{
  error_sum += error;
  error_diff = old_error - error;
  old_error = error;

  pid_correct = kp*error + ki*error_sum + kd*error_diff;
  
  error = 0;
}

void motor_out()
{
  left_rpm = base+10*pid_correct;
  right_rpm = base-10*pid_correct;

  analogWrite(left, left_rpm);
  analogWrite(right, right_rpm);

  Serial.println(left_rpm);
  Serial.println(right_rpm);
}

