/*
Moving around:
   u    i    o
   j    k    l
   m    ,    . */

/*keys =    {
		'i':(1,0,0,0),
		'o':(1,0,0,-1),
		'j':(0,0,0,1),
		'l':(0,0,0,-1),
		'u':(1,0,0,1),
		',':(-1,0,0,0),
		'.':(-1,0,0,1),
		'm':(-1,0,0,-1),
		'O':(1,-1,0,0),
		'I':(1,0,0,0),
		'J':(0,1,0,0),
		'L':(0,-1,0,0),
		'U':(1,1,0,0),
		'<':(-1,0,0,0),
		'>':(-1,-1,0,0),
		'M':(-1,1,0,0),
		't':(0,0,1,0),
		'b':(0,0,-1,0),
}*/
   
#include <unordered_map> 
#include <iostream>
#include <tuple> 
#include "ros/ros.h"
#include "geometry_msgs/Twist.msg" //for Twist message
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


//create a hash table of chars and tuples of the possible key presses that can be made
//the tuples store the (x,y,z,theta) values that the key represents
std::unordered_map <char, std::tuple> keys = {
        { 'u', std::make_tuple(1,0,0,1) },
        { 'i', std::make_tuple(1,0,0,0) }, { 'o', std::make_tuple(1,0,0,-1) }, { 'j', std::make_tuple(0,0,0,1) },
        { 'l', std::make_tuple(0,0,0,-1)}, { 'm', std::make_tuple(-1,0,0,-1) }, { ',', std::make_tuple(-1,0,0,0) }, { '.', std::make_tuple(-1,0,0,1)}
};

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "keyboard_node_publisher");
  ros::NodeHandle n;
  ros::Publisher keyboard_control_pub = n.advertise<std_msgs::Twist>("keyboard_control", 1000); // publish Twist messages to the topic 
  ros::Rate loop_rate(10);

  int c, x,y,z,theta;
  //std::Twist twist
  
   double speed = 1;
   double turn = 0.5;
 
	  
	while (1)
	{
		c = getch();   // call your non-blocking input function		
		
		//use an iterator to go through the unordered map to see if the character matches the key pressed 
		//if it does then assign x, y, z and theta the values of that tuple respectively
		
		for (auto it = keys.begin(); it != keys.end(); ++it ){
			if (it->first == c){
				
				//get the tuple for that corresponding key
				auto t = it->second;
				
				//extract values from the tuple
				x = std::get<0>(t);
				y = std::get<1>(t);
				z = std::get<2>(t);
				theta = std::get<3>(t);
			}
		//if none of the assigned keys are pressed then do nothing (do not move)
			else{
				x = 0;
				y = 0;
				z = 0;
				theta = 0;
			}
		}
				
			auto twist = Twist()	//instantiate the message structure Twist //essentially twist is our msg
			
			
			//assign the x,y,z to the the twist members 
			//publish the msg package to the keyboard_control topic
			
			twist.linear.x = x*speed; 
			twist.linear.y = y*speed; 
			twist.linear.z = z*speed;
			twist.angular.x = 0; 
			twist.angular.y = 0; 
			twist.angular.z = theta*turn;
			keyboard_control_pub.publish(twist);
				
				
	}
	
}
   
   
 
