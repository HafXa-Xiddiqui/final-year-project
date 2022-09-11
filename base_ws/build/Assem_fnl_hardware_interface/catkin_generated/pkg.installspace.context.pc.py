# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "hardware_interface;controller_manager;roscpp;control_msgs;trajectory_msgs;urdf;joint_limits_interface;transmission_interface;control_toolbox;std_msgs;sensor_msgs;rosparam_shortcuts".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lgeneric_hw_control_loop;-lgeneric_hw_interface;-lsim_hw_interface".split(';') if "-lgeneric_hw_control_loop;-lgeneric_hw_interface;-lsim_hw_interface" != "" else []
PROJECT_NAME = "Assem_fnl_hardware_interface"
PROJECT_SPACE_DIR = "/home/hafsa/base_ws/install"
PROJECT_VERSION = "0.5.0"
