# ROS2 SETUP
ROS_VERSION=2
ROS_PYTHON_VERSION=3
ROS_DISTRO=jazzy
# SET DOMAIN ID 
export ROS_DOMAIN_ID=44
export ROS_OS_OVERRIDE=ubuntu:24.04:jazzy
export PYTHONPATH=/home/serl/.local/share/pipx/venvs/pytransform3d/lib/python3.12/site-packages:/home/serl/.local/share/pipx/venvs/pyquaternion/lib/python3.12/site-packages:$PYTHONPATH
# export LOCALHOST_ONLY = 1 per comunicare con altri PC (default value)
# export LOCALHOST_ONLY = 0 per NON comunicare con altri PC


#pipx runpip pytransform3d install pyquaternion	 a quanto pare pipx e pytransform3d vengono installati in due diversi ambienti virtuali 
#ls /home/serl/.local/share/pipx/venvs/pytransform3d/lib/python3.12/site-packages controllo packages nell'ambiente virtuale di pipx


#rm -rf build install log
source /opt/ros/jazzy/setup.bash
source ./install/setup.bash

