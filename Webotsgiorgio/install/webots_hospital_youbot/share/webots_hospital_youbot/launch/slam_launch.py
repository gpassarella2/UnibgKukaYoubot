import os
import pathlib
import launch
from launch_ros.actions import Node
from launch import LaunchDescription

from ament_index_python.packages import get_package_share_directory
from webots_ros2_driver.webots_launcher import WebotsLauncher

from webots_ros2_driver.webots_controller import WebotsController
from webots_ros2_driver.utils import controller_url_prefix
from launch_ros.actions import Node #cancella
# from webots_ros2_driver.utils import get_wsl_ip_address, is_wsl



def generate_launch_description():
    package_dir = get_package_share_directory('webots_hospital_youbot')

    ''' SLAM SIMULATION'''
    robot_description = pathlib.Path(os.path.join(package_dir, 'resource', 'YoubotBase_slam.urdf')).read_text()
    human_description = pathlib.Path(os.path.join(package_dir, 'resource', 'human.urdf')).read_text()

    
    webots = WebotsLauncher(
        world=os.path.join(package_dir, 'worlds', 'webots_hospital_youbot.wbt'),
    )

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': '<robot name="Youbot%20base"><link name=""/></robot>'
        }],
    )


    ''' WEBOTS CONTROLLER'''
    Youbot_base_driver = WebotsController(
        robot_name= 'Youbot base',
        # additional_env={'WEBOTS_CONTROLLER_URL':controller_url_prefix() +'Youbot'},  Youbot Base
        parameters=[
            {'robot_description': robot_description,
            'use_sim_time': True,
            'set_robot_state_publisher': True}
            ] ,
        port="1234",
        respawn=True
    )

    # Si lancia anche il driver human 
    human_driver = WebotsController(
        robot_name= 'human_1',
        parameters=[
            {'robot_description': human_description,
            'use_sim_time': True}
            ] ,
        port="1234",
        respawn=True
    )

    return LaunchDescription([
        # WORLD SIMULATION
        webots,  
        Youbot_base_driver,
        human_driver,

        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=webots,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )
        )
    ])
