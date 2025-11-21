from setuptools import setup

package_name = 'webots'
data_files = []
data_files.append(('share/ament_index/resource_index/packages', ['resource/' + package_name]))
data_files.append(('share/' + package_name + '/launch', ['launch/robot_launch_open.py', 'launch/robot_launch.py', 'launch/robot_launch_obstacle.py']))
data_files.append(('share/' + package_name + '/worlds', ['worlds/progetto.wbt',
                                                         'worlds/progetto_monza.wbt',
                                                         'worlds/progetto_canada.wbt',
                                                         'worlds/progetto_silverstone.wbt',
                                                         'worlds/progetto_spa.wbt',
                                                         'worlds/progetto_final_path.wbt',
                                                         'worlds/progetto_level3.wbt',
                                                         'worlds/progetto_level3_obstacle.wbt'
                                                         
                                                         ]))
# Qui introduco tutti le 'risorse' che utilizzo durante la simulazione 
data_files.append(('share/' + package_name + '/resource', ['resource/Pioneer2.urdf',
                                                           'resource/tinker.obj',
                                                           'resource/canada.obj',
                                                           'resource/monza.obj',
                                                           'resource/silverstone.obj',
                                                           'resource/spa.obj',
                                                           'resource/final_path.obj',
                                                           'resource/level1.obj',
                                                           'resource/level2.obj'                                                         
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
    #entry_points={
    #    'console_scripts': [
    #        'pioneer3_driver= odometria_test.pioneer2_driver:main',
            #'tiago_line_follower = odometria_test.tiago_line_follower:main',
    #        ],
        
   # },
)
