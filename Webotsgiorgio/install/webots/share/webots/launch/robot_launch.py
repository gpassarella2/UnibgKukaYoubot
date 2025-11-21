import os
import pathlib
import launch

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from webots_ros2_driver.webots_launcher import WebotsLauncher
from webots_ros2_driver.webots_controller import WebotsController



# from webots_ros2_driver.utils import get_wsl_ip_address, is_wsl

#Import per settare la porta
def generate_launch_description():
    package_dir = get_package_share_directory('webots')
    robot_description = pathlib.Path(os.path.join(package_dir, 'resource', 'Pioneer2.urdf')).read_text()

    webots = WebotsLauncher(
        
        # world=os.path.join(package_dir, 'worlds', 'progetto.wbt'),

        world=os.path.join(package_dir, 'worlds', 'progetto_level3.wbt'),
        #world=os.path.join(package_dir, 'worlds', 'progetto_level3_obstacle.wbt'),

    )

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': '<robot name=""><link name=""/></robot>'
        }],
    )

    odom_publisher_map = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        output='screen',
        arguments=['0', '0', '0', '0', '0', '0','odom', 'map'],
    )


    odom_publisher_base = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        output='screen',
        arguments=['0', '0', '0', '0', '0', '0','odom', 'base_link'],
    )

    footprint_publisher_laser = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        output='screen',
        arguments=['0.162', '0', '0.258', '0', '0', '0', 'base_link', 'lidar'],
    )

    base_publisher_foot = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        output='screen',
        arguments=['0', '0', '0', '0', '0', '0','base_link', 'base_footprint'],
    )

    
    pioneer2_driver = WebotsController(

        # robot_name= 'Pioneer%202',
        robot_name= 'Pioneer 2',
        parameters=[
            {'robot_description': robot_description},
            {'use_sim_time': True},
        ],
        respawn=True
    )
    

    return LaunchDescription([
        webots,
        robot_state_publisher,
        odom_publisher_map,
        odom_publisher_base,
        footprint_publisher_laser,
        base_publisher_foot,
        pioneer2_driver,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=webots,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )
        )
    ])
