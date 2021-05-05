#include "ros/ros.h"
#include "std_msgs/String.h"
#include <trajectory_msgs/JointTrajectory.h>

void chatterCallback(const trajectory_msgs::JointTrajectory& msg)  //funzione di callback che stampa in shell il messaggio ricevuto dal subscriber
{
ROS_INFO_STREAM("I heard: " << msg);
}


int main(int argc, char **argv)
{
ros::init(argc, argv, "listener");
ros::NodeHandle nodeHandle;
ros::Subscriber subscriber = nodeHandle.subscribe("joints_chatter",10,chatterCallback);  //subscribe sullo stesso chatter del publisher
ros::spin();
return 0;
}