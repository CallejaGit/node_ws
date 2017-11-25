#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const geometry_msgs::Twist::ConstPtr& twist)
{
  ROS_INFO("%d", twist.linear.x );
  ROS_INFO("%d", twist.linear.y );
  ROS_INFO("%d", twist.linear.z );
  ROS_INFO("%d", twist.linear.theta );

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("keyboard_control", 1000, chatterCallback);
  ros::spin();
  return 0;
}
