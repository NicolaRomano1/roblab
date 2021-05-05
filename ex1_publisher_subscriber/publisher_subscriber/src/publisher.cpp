#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdlib>
#include <trajectory_msgs/JointTrajectory.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    ros::Publisher chatterPublisher = nh.advertise<trajectory_msgs::JointTrajectory>("joints_chatter", 1);
    ros::Rate loopRate(10);

    while (ros::ok()) {
        trajectory_msgs::JointTrajectory message; //creo messaggio

        message.joint_names.resize(6);  //il messaggio contiene i dati di 6 giunti
        message.points.resize(6);

        for(int i=0; i<6; i++){  //la posizione è identificata da 6 componenti
            message.points[i].positions.resize(6);
        }

        for(int i=0; i<6; i++){  //nomino i giunti
            message.joint_names[i] = "giunto " + std::to_string(i);
        }

        for(int i=0; i<6; i++){  //assegno i valori di posizione
            message.points[i].positions[0] = rand();
            message.points[i].positions[1] = rand();
            message.points[i].positions[2] = rand();
            message.points[i].positions[3] = rand();
            message.points[i].positions[4] = rand();
            message.points[i].positions[5] = rand();
        }
    
        ROS_INFO_STREAM(message);  //uso lo stream per verificare l'output
        chatterPublisher.publish(message);  //pubblico il messaggio

        ros::spinOnce();
        loopRate.sleep();
}
return 0;
}


