#include <ros/ros.h>
#include <client_server_msgs/fk_service_msg.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <tf_conversions/tf_eigen.h>
 

bool fk(client_server_msgs::fk_service_msg::Request &request, client_server_msgs::fk_service_msg::Response &response){
    ROS_INFO_STREAM("operando...");
    robot_model_loader::RobotModelLoader robot_model_loader;
    robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
    robot_state::RobotState robot_state(kinematic_model);
    robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));
    kinematic_state->setToDefaultValues();

    Eigen::Isometry3d globLinkTf = kinematic_state->getGlobalLinkTransform(request.target);
    
    tf::Matrix3x3 tf_matrix;
    tf::matrixEigenToTF(globLinkTf.rotation(), tf_matrix);

    tf::Quaternion q;
    tf_matrix.getRotation(q);
    response.rotation.w = q.getW();
    response.rotation.x = q.getX();
    response.rotation.y = q.getY();
    response.rotation.z = q.getZ();

    tf::Vector3 trasl;
    tf::vectorEigenToTF(globLinkTf.translation(), trasl);
    response.translation.x = trasl.getX();
    response.translation.y = trasl.getY();
    response.translation.z = trasl.getZ();

    ROS_INFO_STREAM("Forward kinematics for " << request.target << "\n" << response);
    return true;
}


int main(int argc, char **argv){
    ROS_INFO_STREAM("Avvio server");
    ros::init(argc, argv, "forward_kinematics_server");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("forward_kinematics", fk);
    ROS_INFO_STREAM("Server pronto");
    ros::spin();
    return 0;
}