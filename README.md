# utra_master_node

This repo contains catkin workspace and the packages located in utra\_master\_node\src


## For Future Reference

#### creating a workspace & package

Creating a workspace directory

`mkdir/myworkspace`

The next code contains all the src code for the packages

`mkdir/myworkspace/src`

Initialize workspace

`cd myworkspace/src`  
`catkin_init_workspace`

Create package. 

`catkin_create_pkg your_package_name roscpp std_msgs`

roscpp and std_msgs are dependencies added to CMakeList.txt and package.xml


#### compiling the node

After you created a node\_file.cpp in your\_package\_name, declare our node as a executable. In myworkspace/src/your\_package\_name Add:

`add_executable(desired_name src/node_file.cpp)`
`target_link_libraries(desired_name ${catkin_LIBRARIES})`  

First line creates executable called desired_name, directs ROS to its source files. Second line specifies what libraries will be used. Always source your setup.bash file in the workspace you have created. This script allows ROS to find the packages that are contained in your workspace.  

`source ./devel/setup.bash` 

start your node  

`rosrun your_package_name desired_name`



