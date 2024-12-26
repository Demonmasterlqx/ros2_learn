from launch import LaunchDescription
from launch_ros.actions import Node

import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container=ComposableNodeContainer(
        name='my_container_of_composable_PLUGIN',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='composable_node',
                plugin='MessageCallMe::GetMessageCallme',
                name='GET'
            ),
            ComposableNode(
                package='composable_node',
                plugin='MessageCallMe::SendMessage',
                name='PUT'
            )
        ],
        output='screen',
    )
    return launch.LaunchDescription([container])