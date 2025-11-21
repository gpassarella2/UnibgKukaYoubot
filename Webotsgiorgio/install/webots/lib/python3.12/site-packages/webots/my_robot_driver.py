import rclpy

from geometry_msgs.msg import Twist,TransformStamped
from std_msgs.msg import Float64
from sensor_msgs.msg import Range,LaserScan
from nav_msgs.msg import Odometry
from tf2_ros import StaticTransformBroadcaster
# COSTANTI DI SIMULAZIONE

TIME_STEP = 32 # milliseconds
HALF_DISTANCE_BETWEEN_WHEELS = 0.1603 # (Distanza ruote)/2 [m]
D = 0.3206 # Distanza ruote [m]0,3206
R = 0.0825 # Raggio ruota   [m]
WHEEL_RADIUS = 0.0825 #R

# I motori vanno da 10.0 a 0.0
max_speed_motor = 10.0
min_speed_motor = 0.0

motor_left_name = 'left wheel'
motor_right_name = 'right wheel'

sensor_left_name = 'left wheel sensor'
sensor_right_name = 'right wheel sensor'

# Tipi di messaggi che devono essere pubblicati
messaggio_ir_right = Float64()
messaggio_ir_left = Float64()
messaggio_odometria = Odometry()
messaggio_scan = LaserScan()

# Velocità lineare e angolare del robot
forward_speed = 0.0
angular_speed = 0.0
#comandi di velocità da settare ai motori
command_motor_left = 0.0
command_motor_right = 0.0

inizio = True
yaw_iniziale = 0.0


class Pioneer2Driver:
        
    def init(self, webots_node, properties): 
        
        rclpy.init(args=None)
        self.__robot = webots_node.robot
        self.__timestep = TIME_STEP
        self.__node = rclpy.create_node('pioneer_driver')
        self.__node.get_logger().info('Inizzializzazione del driver ')

        # Pubblicazione dei TF
        self.static_broadcaster = StaticTransformBroadcaster(self.__node)

        # Setto un messaggio di twist
        self.target_twist = Twist() 
            
        # salvo i device motors & sensors & lidar & imu
        self.__motor_left = self.__robot.getDevice(motor_left_name)
        self.__sensor_left = self.__robot.getDevice(sensor_left_name)

        self.__motor_right = self.__robot.getDevice(motor_right_name)
        self.__sensor_right = self.__robot.getDevice(sensor_right_name)

        self.__lidar = self.__robot.getDevice('lidar')
        self.__lidar.enable(self.__timestep)
        self.__lidar.enablePointCloud()
        
        # Sensore che mi da l'orientamento del Robot
        self.__imu = self.__robot.getDevice('inertial unit')
        self.__imu.enable(self.__timestep)

        # Inizializzo le posizione e le velocità dei motori 
        self.__motor_left.setPosition(float('inf'))
        self.__motor_left.setVelocity(0.0)

        self.__motor_right.setPosition(float('inf'))
        self.__motor_right.setVelocity(0.0) 

        # Abilitazione dei sensori 
        self.__sensor_left.enable(self.__timestep)
        self.__sensor_right.enable(self.__timestep)

        # Setto i device ad infrarossi per il segui linea 
        self.__sensor_LEFTIR = self.__robot.getDevice('distance sensor left')
        self.__sensor_LEFTIR.enable(self.__timestep)
               
        self.__sensor_RIGHTIR = self.__robot.getDevice('distance sensor right')
        self.__sensor_RIGHTIR.enable(self.__timestep)


        # Definizione dei publisher per pubblicare i dati sensoriale dei sensori ad infrarossi
        self.left_ir_publisher = self.__node.create_publisher(Float64,'ir_left',1)
        self.right_ir_publisher = self.__node.create_publisher(Float64,'ir_right',1)

        # Publisher per la creazione della mappa 
        # self.scan_publisher = self.__node.create_publisher(LaserScan,'scan',1)
        self.odom_publisher = self.__node.create_publisher(Odometry,'odom',1)

        
        # Definizione del subscriber per settare il TWIST 
        self.__node.create_subscription(Twist,'rover_twist',self.__cmd_vel_callback,1)


        # Verifica che il nodo sia supervisor  --> da valutare se toglierlo 
        self.__node.get_logger().info('  TIAGo Base is supervisor? ' + str(self.__robot.getSupervisor()))
        
        # Set delle velocità del robot all'inizio della simulazione cmr, cml = 0.0 
        global command_motor_left, command_motor_right
        self.__motor_right.setVelocity(command_motor_right)
        self.__motor_left.setVelocity(command_motor_left)

        # Setto i frame statici 

        self.odom_trasfrom = TransformStamped()
        self.odom_trasfrom.header.stamp = self.__node.get_clock().now().to_msg()
        self.odom_trasfrom.header.frame_id = 'odom'
        self.odom_trasfrom.child_frame_id = 'base_link'

    def __cmd_vel_callback(self,twist): 
        
        global forward_speed,angular_speed
        
        forward_speed = twist.linear.x
        angular_speed = twist.angular.z

               
    def step(self): 
        
        global command_motor_left, command_motor_right, forward_speed,angular_speed,inizio
        
        rclpy.spin_once(self.__node, timeout_sec=0)

        yaw   = self.__imu.getRollPitchYaw()[2]

        # if(inizio):
            
        #     yaw_iniziale = yaw
        # Lettura valore del sensore 'distance sensor left' al tempo tk
        messaggio_ir_left.data = self.__sensor_LEFTIR.getValue()

        # Pubblicazione messaggio 'ir_left' al tempo tk
        self.left_ir_publisher.publish(messaggio_ir_left) 

        # Lettura valore del sensore 'distance sensor right' al tempo tk
        messaggio_ir_right.data = self.__sensor_RIGHTIR.getValue()

        # Pubblicazione messaggio 'ir_right' al tempo tk
        self.right_ir_publisher.publish(messaggio_ir_right)

        # Modifica equazione calcolo velocità ruote
        command_motor_left = (forward_speed - angular_speed*HALF_DISTANCE_BETWEEN_WHEELS)/R
        command_motor_right = (forward_speed + angular_speed*HALF_DISTANCE_BETWEEN_WHEELS)/R


        self.__motor_left.setVelocity(command_motor_left)
        self.__motor_right.setVelocity(command_motor_right)

        # pubblicazione delle misure laser 
        # self.scan_publisher.publish(messaggio_scan)

        # Calcolo odometrico 
        phi_robot = yaw # - yaw_iniziale

        messaggio_odometria.header.stamp = self.__node.get_clock().now().to_msg()
        messaggio_odometria.header.frame_id = "odom"
        messaggio_odometria.child_frame_id = "base_link"

        messaggio_odometria.pose.pose.position.x =  self.__robot.getSelf().getPosition()[0] # x_robot 
        messaggio_odometria.pose.pose.position.y =  self.__robot.getSelf().getPosition()[1] # y_robot 
        messaggio_odometria.pose.pose.position.z = 0.0        
        messaggio_odometria.pose.pose.orientation.z =  phi_robot 
        messaggio_odometria.twist.twist.linear.x = forward_speed
        messaggio_odometria.twist.twist.linear.y = 0.0
        messaggio_odometria.twist.twist.angular.z = angular_speed
        
        self.odom_publisher.publish(messaggio_odometria)


    
