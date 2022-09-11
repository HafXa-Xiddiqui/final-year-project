
#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <Encoder.h>
#include <geometry_msgs/Twist.h>


#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int64MultiArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int16.h>
Encoder myEnc1(10, 11);
Encoder myEnc2(12,13);
Encoder myEnc3(3, 2);

int motor1pin1 = 26;
int motor1pin2 = 27;
int motor2pin1 = 25;
int motor2pin2 = 24;
int motor3pin1 = 22;
int motor3pin2 = 23;
int pwm1 = 5;
int pwm2 = 8;
int pwm3 = 6;
long encPos1=0;
long encPos2=0;
long encPos3=0;
long pose1  = -999;
long pose2  = -999;
long pose3  = -999;
float L0=0.0;
float L1=0.0;
float L2=0.0;
ros::NodeHandle nh;
int i=0;
//std_msgs::Int64MultiArray enc_ticks;
//ros::Publisher enc_ticks_pub("encoder_ticks", &enc_ticks);

void onTwist(const std_msgs::Float32MultiArray& msg)
{
   
  L1 = msg.data[1]*57.29577;
  L0 = msg.data[0]*57.29577;
  L2 = msg.data[2]*57.29577;

}

ros::Subscriber<std_msgs::Float32MultiArray> cmd_sub("set_vel", &onTwist);

void setup() {
  // put your setup code here, to run once:
  nh.getHardware()->setBaud(115200);
  
  //MOTOR 1
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(pwm1, OUTPUT); 
  //MOTOR 2
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(pwm2, OUTPUT); 
  //MOTOR 3
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(pwm3, OUTPUT);  

  nh.initNode();

  //encoder ticks array initialiazation
//  char dim0_label[] = "encoder_ticks";
//  enc_ticks.layout.dim = (std_msgs::MultiArrayDimension *) malloc(sizeof(std_msgs::MultiArrayDimension) * 2);
//  enc_ticks.layout.dim[0].label = dim0_label;
//  enc_ticks.layout.dim[0].size = 4;
//  enc_ticks.layout.dim[0].stride = 1*4;
//  enc_ticks.data = (long long int *)malloc(sizeof(long long int)*4);
//  enc_ticks.layout.dim_length = 0;
//  enc_ticks.data_length = 4;

//  nh.advertise(enc_ticks_pub);
  nh.subscribe(cmd_sub);
}

void loop() {
  // put your main code here, to run repeatedly:   

//enc_ticks.data[0]=angle;
//  enc_ticks.data[1]=0;
//  enc_ticks.data[2]=0;
//  enc_ticks.data[3]=0;
//  
//enc_ticks_pub.publish(&enc_ticks);
while (i<=200)
{
 analogWrite(pwm1, 0);
 analogWrite(pwm2, 0);
 analogWrite(pwm3, 0);
 delay(40);
  nh.spinOnce();
  i=i+1;
}
if (i>200)
{
  pose1=RotMotor(L0,motor1pin1,motor1pin2,pwm1,pose1,&myEnc1);
  
    if (((pose1*4.5) >= L0-2.25) && (pose1*4.5) <= L0+2.25)
  {  analogWrite(pwm1, 0);
     analogWrite(pwm3, 0);
    i=201;
   pose2=RotMotor(L1,motor2pin1,motor2pin2,pwm2,pose2,&myEnc2);
  
    if (((pose2*4.5) >= L1-2.25) && (pose2*4.5) <= L1+2.25)
    { analogWrite(pwm1, 0);
      analogWrite(pwm2, 0);
    i=201;
    pose3=RotMotor(L2,motor3pin1,motor3pin2,pwm3,pose3,&myEnc3);
    }
  }
  nh.spinOnce();
}
String abc = String(pose1*4.5);
nh.loginfo(abc.c_str());
}



float RotMotor(float data, int motorpin1, int motorpin2, int pwm, int pose, Encoder *myEnc)
  {
  int k=1;
  int j=1;
  float angle=pose*4.5;

  if (angle >= data-2.25 && angle <= data+2.25)
    {
      i=0;
      return pose;
  
    }

    
 else if(data > angle && k==1)
{  
  analogWrite(pwm, 250); //ENA pin
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  long newPos = myEnc->read();
  if (newPos != pose) {
    pose = newPos;
  } 
  j=0;
  k=1;
}

else if (data < angle && j==1)
{
  analogWrite(pwm, 250); //ENA pin
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  long newPos = myEnc->read();
  if (newPos != pose) {
    pose = newPos;
  } 
  j=1;
  k=0;
}
return pose;
 }
