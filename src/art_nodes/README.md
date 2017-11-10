# Compiling

The node you created should be in art_nodes/src.

The file you created for the node has to be declared as an executable.

`add_executable(<executable> src/<corresponding node>.cpp)`  
`target_link_libraries(<executable> ${catkin_LIBRARIES})`

replace` <executable>` for whatever name you choose for the executable and `<corresponding node>` with the node you created.

Build our workspace using catkin_make command in the workspace directory

`cd your_workspace`  
`catkin_make`

To start the node, 
`rosrun art_nodes <executable>`   
Where executable is the name you chose for the executable
