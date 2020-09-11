#include <iostream>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

typedef visualization_msgs::Marker VM;
int main(int argc, char** argv){

    ros::init(argc, argv, "add_markers");
    ros::NodeHandle nh;
    ros::Rate r(5.0);
    ros::Publisher marker_publisher = nh.advertise<VM>("visualization_marker", 1);

    int count = 0;
    uint32_t shape = VM::CUBE;
    nh.setParam("/display_state", true);
    nh.setParam("/goal_x", -1.0);
    nh.setParam("/goal_y", 3.0);
    while(ros::ok()){
        VM marker;
        marker.header.frame_id = "/map";
        marker.header.stamp = ros::Time::now();
        marker.ns = "basic shapes";
        marker.id = 0;
        marker.type = shape;

        bool display;
        nh.getParam("/display_state", display);
        double goal_x, goal_y;
        nh.getParam("/goal_x", goal_x);
        nh.getParam("/goal_y", goal_y);

        if(display){
            marker.action = VM::ADD;

            marker.pose.position.x = goal_x;
            marker.pose.position.y = goal_y;
            marker.pose.position.z = 0;
        }
        else {
            marker.action = VM::DELETE;
        }

        marker.pose.orientation.x = 0;
        marker.pose.orientation.y = 0;
        marker.pose.orientation.z = 0;
        marker.pose.orientation.w = 1;

        marker.scale.x = 0.5;
        marker.scale.y = 0.5;
        marker.scale.z = 0.001;

        marker.color.r = 1.0f;
        marker.color.g = 0.647f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;
        
        marker.lifetime = ros::Duration(5.0);

        while(marker_publisher.getNumSubscribers() < 1){
            if(!ros::ok())
                return 0;
            ROS_WARN_ONCE ("Please create a subscriber to the marker");
            sleep(1.0);
        }
        if(count == 0)
            ROS_INFO("Received a subscriber");
        
        marker_publisher.publish(marker);
        count++;
        //sleep(5.0);
    }
}