#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs.h"
#include "std_msgs/Bol.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include "PATH.h"
#include "VISION.h"
#include <iostream>
using namespace ros;

void main (int argc, char **argv){//argc argument number, argv strings of arguments
	int frequency =10;
	float orientation=0; //initialize
	float x,y=0;
	ros::init(argc, argv, "name");
	ros::NodeHandle n;
	Publisher path=n.advertise<std_msg::String>("path_node",10,callback);
	Publisher vision=n.advertise<std msg::Int32>("vision_node",10,callback);
	ros::Subscriber sub = n.subscribe("master_node", 1000, callback);
	ros::Rate loop_rate(frequency);

	while (ros::ok()){//if returns false, ros shut down
		std_msgs::String back;
		back.data="Backward";
		std_msgs::String front;
		front.data="Forward";
		std_msgs::String turn;
		turn.data="Turning";
		std_msgs::Float64 angle;
		angle.data=orientation;
		path.publish(front);
		path.publish(back);
		path.publish(angle);
		path.publish(orientation);
		std_msgs::Float64 x1;
		x1.data=x;
		std_msgs::Float64 y1;
		y1.data=y;
		vision.publish(x1);
		vision.publish(y1);
		vision.publish(orientation);
		ros::spinOnce();//check messages
		loop_rate.sleep();
	}
}
void callback(const std_msgs::StringConstPtr& str){
	ROS_INFO("The information: [%s]", msg->data.c_str());
}

