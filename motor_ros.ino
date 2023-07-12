#include <ros.h>
#include <geometry_msgs/Twist.h>

//Creating Nodehandle
ros::NodeHandle nh;


float throttle, direction;

//Defining callback just read from topic and save to inx,angz
void filterVelocityCallback(const geometry_msgs::Twist& msg) {
  //Using the callback function just for subscribing
  //Subscribing the message and storing it in 'linx' and 'angZ'
  throttle = msg.linear.x;      direction = msg.angular.z;

}

//Defining Subscriber
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", filterVelocityCallback);


//------------------------------------------------------

const byte controllerFA = 3; //PWM FORWARD PIN for OSMC Controller A (left motor)
const byte controllerRA = 2;  //PWM DIRECTION PIN for OSMC Controller A (left motor)
const byte controllerFB = 5;  //PWM FORWARD PIN for OSMC Controller B (right motor)
const byte controllerRB = 4;  //PWM DIRECTION PIN for OSMC Controller B (right motor)
const byte ENA=6;
const byte ENB=9;
int leftMotor, leftMotorScaled = 0; //left Motor helper variables
int rightMotor, rightMotorScaled = 0; //right Motor helper variables
int deadZone = 10; //jostick dead zone


void setup() {
  //Initializing node
  nh.initNode();
  //Start subscribing
  nh.subscribe(sub);

  pinMode(controllerFA, OUTPUT);
  pinMode(controllerRA, OUTPUT);
  pinMode(controllerFB, OUTPUT);
  pinMode(controllerRB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //mix throttle and direction
  leftMotor = throttle - direction;//19-3=16
  rightMotor = throttle + direction;//19+3=22
  Serial.println(leftMotor);
  Serial.println(rightMotor);

  leftMotorScaled = constrain(leftMotor, -255, 255);
  rightMotorScaled = constrain(rightMotor, -255, 255);

  //apply the results to appropriate uC PWM outputs for the LEFT motor:
  if (abs(leftMotorScaled) > deadZone)
  {
    if (leftMotorScaled > 0)
    {
      digitalWrite(controllerRA, LOW);//forward left motor
      digitalWrite(controllerFA, HIGH);//reverse righht motor
      analogWrite(ENA, abs(leftMotorScaled));
    }
    else
    {
       digitalWrite(controllerRA, HIGH);//forward left motor
      digitalWrite(controllerFA, LOW);//reverse righht motor
      analogWrite(ENA, abs(leftMotorScaled));
    }
  }
  else
  {
    analogWrite(ENA, 0);
    digitalWrite(controllerRA, LOW);
    digitalWrite(controllerFA, LOW);
  }


  //apply the results to appropriate uC PWM outputs for the RIGHT motor:
  if (abs(rightMotorScaled) > deadZone)
  {

    if (rightMotorScaled > 0)
    {
      digitalWrite(controllerRB, LOW);//forward right
      digitalWrite(controllerFB, HIGH);//reverssse left
      analogWrite(ENB, abs(rightMotorScaled));
    }
    else
    {
      digitalWrite(controllerRB, HIGH);//reverssse left
      digitalWrite(controllerFB, LOW);//reverssse left
      analogWrite(ENB, abs(rightMotorScaled));
    }
  }
  else
  {
    analogWrite(ENB, 0);
    digitalWrite(controllerRB, LOW);
    digitalWrite(controllerFB, LOW);//reverssse left
  }

  //nh.loginfo("nsocb")
  //rate.sleep();
  nh.spinOnce();
  delay(3);
}
