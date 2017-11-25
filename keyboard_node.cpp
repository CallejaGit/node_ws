/*
Moving around:
   u    i    o
   j    k    l
   m    ,    . */
   
#include <unordered_map>
#include <iostream>
#include <tuple>
#include <Twist>
#include "ros/ros.h"
#include "std_msgs/Twist.h"
#include <sstream>
#include <termios.h> //for terminal I/O interfaces
   
   
//get char from keyboard input
int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt; 
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar();  // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}


//create a hash table of all the possible key presses that can be made
std::unordered_map <char, std::tuple> keys = {
        { 'u', std::make_tuple(1,0,0,1) },
        { 'i', std::make_tuple(1,0,0,0) }, { 'o', std::make_tuple(1,0,0,-1) }, { 'j', std::make_tuple(0,0,0,1) },
        { 'l', std::make_tuple(0,0,0,-1)}, { 'm', std::make_tuple(-1,0,0,-1) }, { ',', std::make_tuple(-1,0,0,0) }, { '.', std::make_tuple(-1,0,0,1)}
};

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "publisher");
  ros::NodeHandle n;
  ros::Publisher keyboard_control_pub = n.advertise<std_msgs::Twist>("keyboard_control", 1000); //do I need to add anything else here for Twist?
  ros::Rate loop_rate(10);

  int c;
  int x;
  int y;
  int z;
  int theta;
  std::Twist twist
  
  //int speed = 1;
	
	double speed;
	double turn;
  
	speed = rospy.get_param("~speed", 0.5)
	turn = rospy.get_param("~turn", 1.0)

	  
	while (1))
	{
		c = getch();   // call your non-blocking input function
		//std::stringstream ss;
		
		
		//use an iterator to go through the unordered map to see if the character matches the key pressed 
		//if it does then assign x, y, z and theta the values of that tuple
		
		for (auto it = keys.begin(); it != keys.end(); ++it ){
			if (it->first == c){
				x = it->second[0];
				y = it->second[1];
				z = it->second[2];
				theta = it->second[3];
			}
			else{
				x = 0;
				y = 0;
				z = 0;
				theta = 0;
			}
		}
				
			twist = Twist()	//instantiate the message structure Twist //essentially twist is our msg
			
			
			//assign the x,y,z to the the twist members 
			//publish the msg package to the keyboard_control topic
			
			twist.linear.x = x*speed; 
			twist.linear.y = y*speed; 
			twist.linear.z = z*speed;
			twist.angular.x = 0; 
			twist.angular.y = 0; 
			twist.angular.z = th*turn;
			keyboard_control_pub.publish(twist);
				
				
	}
	
}
   
   
 