#include <ros/ros.h>
#include <roscpp_tutorials/TwoInts.h>
#include <client_server_msgs/fk_service_msg.h>
#include <robot_model_loader/robot_model_loader.h>
#include <robot_state/robot_state.h>
 

bool fk(client_server_msgs::fk_service_msg::Request &request, client_server_msgs::fk_service_msg::Response &response){
    robot_model_loader::RobotModelLoader robot_model_loader("m20ia");
    robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
    robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));

    const Eigen::Isometry3d& end_effector_state = kinematic_state->getGlobalLinkTransform(request.target);

    /* Print end-effector pose. Remember that this is in the model frame */
    ROS_INFO_STREAM("Translation: \n" << end_effector_state.translation() << "\n");
    ROS_INFO_STREAM("Rotation: \n" << end_effector_state.rotation() << "\n");

    response.translation.x = end_effector_state.translation().x();
    response.translation.y = end_effector_state.translation().y();
    response.translation.z = end_effector_state.translation().z();
    
    response.rotation.w = end_effector_state.rotation().w();
    response.rotation.x = end_effector_state.rotation().x();
    response.rotation.y = end_effector_state.rotation().y();
    response.rotation.z = end_effector_state.rotation().z();

    return true;
}


int main(int argc, char **argv){
ros::init(argc, argv, "forward_kinematics_server");
ros::NodeHandle nh;
ros::ServiceServer service = nh.advertiseService("forward_kinematics", fk);
ros::spin();
return 0;
}