#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "mod8i8o.h"
#include "rs485_modbus_rtu.h"
#include "mod8i8o.cpp"
#include "rs485_modbus_rtu.cpp"
#include <unistd.h>
#include <stdio.h>
#include <sstream>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>
#include<stdlib.h>
using namespace std;
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

void PositionCallback(const std_msgs::Int32::ConstPtr& array)
{
  
    ROS_INFO("Position callback called");
 int new_x;
    new_x=array->data;
   int read_setpin_status;
 int read_resetpin_status;
RS485_Modbus_RTU test1(testDevParam);
	//getting modbus pointer variable for local access
	modbus_t *ctx = test1.getDev();

	MOD8I8O ioDev1;
	ioDev1.mapModbus(test1.isModbusOpen(), ctx, 1);
    // print all the remaining numbers
  
	printf("Position:%d\n",new_x);	
    	for(int i=1;i<=new_x;i++)
    	 {                                  
    	    ROS_INFO("Forwared");
		ioDev1.setOutputPort(0x05);    
		sleep(1);

             
   	 }
ioDev1.setOutputPort(0x00); 
 sleep(5);
           ROS_INFO("RESET");
		
    return ;
  
}

void DegreeCallback(const std_msgs::Int32::ConstPtr& deg)
{
     ROS_INFO("Degree callback called");
      int i = 0,new_x=0,y=0,new_degree=0;
     RS485_Modbus_RTU test1(testDevParam);
	//getting modbus pointer variable for local access
	modbus_t *ctx = test1.getDev();

	MOD8I8O ioDev1;
	ioDev1.mapModbus(test1.isModbusOpen(), ctx, 1);
       
   printf("Degree:%d\n",deg->data);
   
    if(deg->data<0) // Turn left
    {
         for(int i=1;i<=deg->data;i++)
    	 {
    	 ROS_INFO("Turn Left");
		
		ioDev1.setOutputPort(0x06);    
		sleep(1);
    
   	 }
    }
    if(deg->data>=0) // Turn right
    {
         for(int i=1;i<=deg->data;i++)
    	 {                                  
    	    ROS_INFO("Turn Right");
		ioDev1.setOutputPort(0x09);    
		sleep(1);
		
   	 }
    }  
	
 	ioDev1.setOutputPort(0x00);    
		sleep(5);	
    
    return ;


}
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "modbus_motor");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
ros::Rate loop_rate(10);
  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
    ros::Subscriber sub1 = n.subscribe("degree", 1000, DegreeCallback); 
  ros::Subscriber sub = n.subscribe("position", 1000, PositionCallback);

    
	  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
 
  ros::spin();
 loop_rate.sleep();
  return 0;
}
