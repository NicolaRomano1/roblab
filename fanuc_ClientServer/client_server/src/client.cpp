#include <ros/ros.h>
#include <roscpp_tutorials/TwoInts.h>
#include <cstdlib>


int main(int argc, char **argv) {
ros::init(argc, argv, "add_two_ints_client");
if (argc != 3) {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
}
ros::NodeHandle nh;
ros::ServiceClient client = nh.serviceClient<roscpp_tutorials::TwoInts>("add_two_ints");
roscpp_tutorials::TwoInts service;
service.request.a = atoi(argv[1]);
service.request.b = atoi(argv[2]);
if (client.call(service)) {
    ROS_INFO("Sum: %ld", (long int)service.response.sum);
}else {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
    }

return 0;
}