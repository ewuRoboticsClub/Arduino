//  team phoenix
//  ewurc-lft
//  east west university robotics club


#include <QTRSensors.h>
#include <SparkFun_TB6612.h>

// ir sensor
#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN

QTRSensorsAnalog qtra((unsigned char[]) {14, 27, 26, 25, 33, 32, 35, 34},
                      NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

// motor
#define AIN1 5
#define BIN1 16
#define AIN2 18
#define BIN2 17
#define PWMA 19
#define PWMB 21
#define STBY 4

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


// declaration
const int base_speed = 200;
float Kp = 0.057;
float Ki = 0.00;     //PID tuning
float Kd = 0.000025;

unsigned long iTime, tTime;  // added
float eTime = 0;

int error = 0;
int last_error = 0;

int i = 0;
unsigned int position = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  go_pid();
}

void go_pid() {
  position = 0;
  qtra.read(sensorValues, QTR_EMITTERS_ON);
  position =  qtra.readLine(sensorValues, QTR_EMITTERS_ON, 1);

  Serial.print(position);

  iTime = millis();  // added

  int error = position - 3500;
  Serial.print('\t');
  Serial.print(error);
  Serial.print('\t');  

  eTime = (float)(iTime - tTime) / 1000;  //  added

  int P = error;
  int I = (I * 2 / 3) + (last_error * eTime);  // added + modified
  int D = (error - last_error) / eTime;   // added + modified
  last_error = error;
  tTime = iTime;    //  added

  int speed_change = (P * Kp) + (I * Ki) + (D * Kd);
  Serial.print(speed_change);
  Serial.print('\t');
  int motor_speed1 = base_speed - speed_change;
  int motor_speed2 = base_speed + speed_change;

  motor_speed1 = constrain(motor_speed1, 0, 255);   // added + modified
  motor_speed2 = constrain(motor_speed2, 0, 255);   // added + modified

  forward(motor_speed1, motor_speed2);
}

//  added + modified
void forward(int L_speed, int R_speed) {
  motor1.drive(L_speed);
  motor2.drive(R_speed);
  Serial.print(L_speed);
  Serial.print("\t");
  Serial.print(R_speed);
  Serial.println();
}