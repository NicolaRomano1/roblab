#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <cmath>


void print_rotmat_and_axis_angle(geometry_msgs::TransformStamped transformStamped){
    double w = transformStamped.transform.rotation.w;
    double x = transformStamped.transform.rotation.x;
    double y = transformStamped.transform.rotation.y;
    double z = transformStamped.transform.rotation.z;

    double R[3][3];
    R[0][0]= std::ceil((2*(w*w + x*x) - 1)*100)/100;
    R[0][1]= std::ceil((2*(x*y - w*z))*100)/100;
    R[0][2]= std::ceil((2*(x*z + w*y))*100)/100;
    R[1][0]= std::ceil((2*(x*y + w*z))*100)/100;
    R[1][1]= std::ceil((2*(w*w + y*y) - 1)*100)/100;
    R[1][2]= std::ceil((2*(y*z - w*x))*100)/100;
    R[2][0]= std::ceil((2*(x*z - w*y))*100)/100;
    R[2][1]= std::ceil((2*(y*z + w*x))*100)/100;
    R[2][2]= std::ceil((2*(w*w + z*z) - 1)*100)/100;

    ROS_INFO("Rotation matrix:\n");

    for (int i = 0; i < 3; i++){
        ROS_INFO_STREAM(R[i][0] << "\t" << R[i][1] << "\t" << R[i][2]);
    }


    double tetha = std::acos((R[0][0] + R[1][1] + R[2][2] - 1)/2);
    double r1 = (R[2][1] - R[1][2])/(2*std::sin(tetha));
    double r2 = (R[0][2] - R[2][0])/(2*std::sin(tetha));
    double r3 = (R[1][0] - R[0][1])/(2*std::sin(tetha));

    ROS_INFO("\n\nAxis-Angle:");
    ROS_INFO_STREAM("r: " << r1 << " " << r2 << " " << r3 << " tetha: " << tetha);
}

void print_euler(geometry_msgs::TransformStamped transformStamped){
    double w = transformStamped.transform.rotation.w;
    double x = transformStamped.transform.rotation.x;
    double y = transformStamped.transform.rotation.y;
    double z = transformStamped.transform.rotation.z;

    // roll (x-axis rotation)
    double sinr_cosp = 2 * (w * x + y * z);
    double cosr_cosp = 1 - 2 * (x * x + y * y);
    double roll = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double pitch;
    double sinp = 2 * (w * y - z * x);
    if (std::abs(sinp) >= 1)
        pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        pitch = std::asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);
    double yaw = std::atan2(siny_cosp, cosy_cosp);

    ROS_INFO_STREAM("\n\nEuler angles:\nroll: " << std::ceil(roll*100)/100 << " pitch: " << std::ceil(pitch*100)/100 << " yaw: " << std::ceil(yaw*100)/100);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "tf2_listener");
    ros::NodeHandle nodeHandle;
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);
    ros::Rate rate(1.0);

    while (nodeHandle.ok()) {
        geometry_msgs::TransformStamped transformStamped;
        try {
            transformStamped = tfBuffer.lookupTransform("base_link", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da base a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);

            transformStamped = tfBuffer.lookupTransform("link1", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da link1 a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);

            transformStamped = tfBuffer.lookupTransform("link2", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da link2 a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);

            transformStamped = tfBuffer.lookupTransform("link3", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da link3 a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);

            transformStamped = tfBuffer.lookupTransform("link4", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da link4 a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);

            transformStamped = tfBuffer.lookupTransform("link5", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da link5 a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);

            transformStamped = tfBuffer.lookupTransform("link6", "flange", ros::Time(0));
            ROS_INFO_STREAM("\n Da link6 a flangia: \n\n" << transformStamped.transform);
            print_rotmat_and_axis_angle(transformStamped);
            print_euler(transformStamped);
            
        } catch (tf2::TransformException &exception) {
            ROS_WARN("%s", exception.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        rate.sleep();
    }
    return 0;
};

