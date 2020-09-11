#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){

    ros::init(argc, argv, "pick_objects");

    MoveBaseClient ac("move_base", true);

    bool display = true;
    double goal_x = -1.0, goal_y = 3.0;

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO_STREAM("Waiting for move-base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    {
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = goal_x;
        goal.target_pose.pose.position.y = goal_y;
        goal.target_pose.pose.orientation.w = 1.0;

        ros::param::set("/goal_x", goal_x);
        ros::param::set("/goal_y", goal_y);
        ros::param::set("/display_state", true);

        ROS_INFO("Sending Goal1 as pick-up location");
        ac.sendGoal(goal);
        ac.waitForResult();

        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO_STREAM("Hurray, Robot moved to the Pick-Up Spot");
            ros::param::set("/display_state", false);
        }
        else
        {
            ROS_INFO("The Base failed to move to Pick-up location for some reason");
        }
    }
    ROS_INFO("Waiting for 5 seconds");
    ros::Duration(5.0).sleep();

    {
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal_x = -3.0;
        goal_y = -1.0;

        goal.target_pose.pose.position.x = goal_x;
        goal.target_pose.pose.position.y = goal_y;
        goal.target_pose.pose.orientation.w = 1.0;


        ros::param::set("/goal_x", goal_x);
        ros::param::set("/goal_y", goal_y);
        ros::param::set("/display_state", false);

        ROS_INFO("Sending Goal2 as the drop-off location");
        ac.sendGoal(goal);
        ac.waitForResult();

        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO_STREAM("Hurray, Robot moved to the Drop-off Area");
            ros::param::set("/display_state", true);
        }
        else
        {
            ROS_INFO("The Base failed to move to drop-off zone for some reason");
        }
    }
    
    return 0;
}