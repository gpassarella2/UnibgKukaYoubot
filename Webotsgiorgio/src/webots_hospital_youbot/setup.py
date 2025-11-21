from setuptools import setup

package_name = 'webots_hospital_youbot'
data_files = []
data_files.append(('share/ament_index/resource_index/packages', ['resource/' + package_name]))
data_files.append(('share/' + package_name + '/launch', [    
                                                          'launch/slam_launch.py',
                                                          'launch/localization_launch.py'
                                                          ]))

data_files.append(('share/' + package_name + '/worlds', [
                                                          'worlds/webots_hospital_youbot.wbt'
                                                          ]))

# Per rendere visibile i file presente nei resource e poi utilizzarli nel launch file 

data_files.append(('share/' + package_name + '/resource', ['resource/YoubotBase_localization.urdf',
                                                          'resource/YoubotBase_slam.urdf',
                                                          'resource/human.urdf'

                                                          ]))
data_files.append(('share/' + package_name, ['package.xml']))


setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=data_files,
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='user',
    maintainer_email='raul01597@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
    'console_scripts': [
        'driver = webots_hospital_youbot.driver:main',
        'human_driver = webots_hospital_youbot.human_driver:main',
        'teleop_keyboard = webots_hospital_youbot.teleop_keyboard:main'
        ],
    },

)
