#include <ros/ros.h>
#include <client_server_msgs/fk_service_msg.h>
#include <cstdlib>


int main(int argc, char **argv) {
ros::init(argc, argv, "forward_kinematics_client");
if (argc != 3) {
    ROS_INFO("Client started");
}

ros::NodeHandle nh;
ros::ServiceClient client = nh.serviceClient<client_server_msgs::fk_service_msg>("forward_kinematics");

client_server_msgs::fk_service_msg service;
service.request.target = "flange";

if (client.call(service)) {
    ROS_INFO_STREAM("risposta:" << service.response);
}else {
    ROS_ERROR("Failed to call service forward_kinematics");
    return 1;
    }

return 0;
}