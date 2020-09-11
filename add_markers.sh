#!/bin/sh

xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 10

xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" & 

sleep 5

xterm -e " roslaunch my_robot rviz_config.launch" & 

sleep 10

xterm -e " rosrun add_markers add_markers_node"
