#!/usr/bin/env python3
import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg

moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node("move_group_python_interface_tutorial", anonymous=True)
robot = moveit_commander.RobotCommander()
scene = moveit_commander.PlanningSceneInterface()


group_name = "arm"
arm_group = moveit_commander.MoveGroupCommander(group_name)
arm_group.set_goal_position_tolerance(0.2)
arm_group.set_goal_orientation_tolerance(0.3)
arm_group.set_planning_time(10)
# arm_group.set_pose_reference_frame("base_link")
arm_group.set_planner_id("RRT")
arm_group.set_num_planning_attempts(5)

grip_group = moveit_commander.MoveGroupCommander("gripper")

grip_group.set_named_target("open")
grip_group.go()

# rospy.sleep(5)
print(arm_group.get_current_pose())
pose_goal = geometry_msgs.msg.PoseStamped()
pose_goal.header.frame_id = "base_link"
pose_goal.pose.orientation.w = 0.8752624535452355
pose_goal.pose.orientation.x = -4.60529057555765e-05
pose_goal.pose.orientation.y = 0.4836482550837122
pose_goal.pose.orientation.z = 2.5447689912895465e-05
pose_goal.pose.position.x = 0.7729116411322066
pose_goal.pose.position.y = 5.953213504478194e-05
pose_goal.pose.position.z = 0.23300877797660027

# arm_group.set_start_state(arm_group.get_current_state())
arm_group.set_joint_value_target(pose_goal,"sub_claw_part_1_link",True)
arm_group.go()

grip_group.set_named_target("close")
grip_group.go()

rospy.sleep(1)

arm_group.set_named_target("home")
arm_group.go()

#####################################
pose_goal = geometry_msgs.msg.PoseStamped()
pose_goal.header.frame_id = "base_link"
pose_goal.pose.orientation.w = 0.9558768777465041
pose_goal.pose.orientation.x = -6.224072738864655e-05
pose_goal.pose.orientation.y = 0.2937675787928178
pose_goal.pose.orientation.z = 1.912830848087055e-05
pose_goal.pose.position.x = 1.2558868954961118
pose_goal.pose.position.y = 5.953213504478194e-05
pose_goal.pose.position.z = 0.1821944996945782

# arm_group.set_start_state(arm_group.get_current_state())
arm_group.set_joint_value_target(pose_goal,"sub_claw_part_1_link",True)
arm_group.go()
# rospy.sleep(2)
#
grip_group.set_named_target("open")
grip_group.go()
#
rospy.sleep(3)
#
arm_group.set_named_target("home")
arm_group.go()

rospy.sleep(5)
moveit_commander.roscpp_shutdown()
