import rclpy
from sensor_msgs.msg import LaserScan, JointState
from nav_msgs.msg import Odometry
import numpy as np
from geometry_msgs.msg import Twist, Quaternion,TransformStamped
# RIVEDERE DOVE UTILIZZARE I FRAME CHE VADO A PUBBLICARE
from tf2_ros import StaticTransformBroadcaster,TransformBroadcaster
from rover_msgs.msg import RoverInfo
from aurora_msgs.msg import Object3D, Object3DArray
from pyquaternion import Quaternion  # for quaternion operations
from pytransform3d import transformations,rotations
import math
from util import RoverInformation, ClassObject, LaserObject

########## Dichiarazione dimensioni KUKA Youbot ##########
raggioRuote = 0.05
rotationRatio = 1
slideRatio = 1
distanzaFrontale = 0.3
distanzaLaterale = 0.471
HALF_DISTANCE_BETWEEN_WHEELS = 0.15  # L/2
R = raggioRuote  

########## Inizializzazione Dati iniziali ##########
TIME_STEP = 32 # milliseconds

##########  costruzione messaggi ##########
position = [0.0, 0.0, 0.0]
orientation = [0.0, 0.0, 0.0, 0.0]


matrice_postsetup = []
matrice_post_setup_inversa = []

########## Fine costruzione messaggi ##########
TIME_STAMP_SCAN = 0.5
TIME_STAMP_ODOMETRY = 0.5
TIME_STAMP_OBJECTS = 0.5


class YoubotDriver:

    #********************** INIZIALIZATION OF YoubotDriver ****************************

    def init(self, webots_node, properties):  
        
        rclpy.init(args=None)
        self.__robot = webots_node.robot
        self.__timestep = TIME_STEP
        self.__node = rclpy.create_node('Youbot_base_driver')
        self.__node.get_logger().info('Inizio di Youbot_base_driver')

        self.init_components()
        self.coordinate_assolute = []
        self.objects_vector = []
        self.inizio = True

        # INIZIALIZZAZIONE DI TF 
        self.init_tf_odom()

        # SCELTA DEL LASER DA UTILIZZARE
        self.init_laser(properties) 
        
        # INIZIALIZZAZIONE DEI DEVICE IN SIMULAZIONE
        self.setup_robot_devices(properties)

        # INIZIALIZZAZIONE DEI PUBLISHER E DEI SUBSCRIBER 
        self.setup_publishers_and_subscribers()

        # INIZIALIZZAZION DEI MESSAGGI
        self.init_messages()

        # SETUO LASER MSG
        self.setup_laser_msg()

        #SETUP ROVER MSG 
        self.setup_rover_msg()

        #SETUP INFO FOR CAMERA 
        self.init_info_camera()

        # ********************* CHECK SUPERVISOR PERMISSION TO TAKE DATA FROM SIMULATORE *******************
        self.__node.get_logger().info('  Youbot Base is supervisor? ' + str(self.__robot.getSupervisor()))
        
        ''' TAKE DATA THANKS SUPERVISOR PERMISSIONS'''
        self.posizione_robot = self.__robot.getSelf().getPosition() # Vector 1x3        
        self.orientazione_robot = self.__robot.getSelf().getOrientation() # Vector 3x3    
        self.rototraslazione_robot = self.__robot.getSelf().getPose() # Matrix roto-traslantion 

        # self.__node.get_logger().info('matrice di roto_traslazione: ' + str(self.rototraslazione_robot))
        
        # BUILD MATRIX OF ROTO-TRANSLATION

        # self.matrice_presetup = build_matrix(self.rototraslazione_robot)
        # self.__node.get_logger().info('print della matrice costruita pre-setup: ' + str(self.matrice_presetup))

        # TAKE DATA AND SAVE DATA FROM WEBOTS NODES
        self.take_data_from_Webots_node(properties,webots_node)
        
        self.init_tf_camera()
    
    def update_odom_tf(self, conversione_o2r_xq,current_time):

        self.odom_trasfrom.header.stamp = current_time
        self.odom_trasfrom.transform.rotation.w = conversione_o2r_xq[3] 
        self.odom_trasfrom.transform.rotation.x = conversione_o2r_xq[4]
        self.odom_trasfrom.transform.rotation.y = conversione_o2r_xq[5] 
        self.odom_trasfrom.transform.rotation.z = conversione_o2r_xq[6] 
        self.odom_trasfrom.transform.translation.x = conversione_o2r_xq[0]  
        self.odom_trasfrom.transform.translation.y = conversione_o2r_xq[1] 
        self.odom_trasfrom.transform.translation.z = conversione_o2r_xq[2] 


        self.static_broadcaster.sendTransform(self.odom_trasfrom) # PRIMA  ERA DIAMICO/ ORA STATICO


    def build_odom(self, conversione_o2r_xq,current_time):
        # PUBLIC ODOMETRY MESSAGE 
                       
        #self.messaggio_odometria.header.stamp = current_time
        self.messaggio_odometria.header.stamp =  self.__node.get_clock().now().to_msg()
        self.messaggio_odometria.header.frame_id = "odom"
        self.messaggio_odometria.child_frame_id = "base_link"
        self.messaggio_odometria.pose.pose.position.x =   conversione_o2r_xq[0]
        self.messaggio_odometria.pose.pose.position.y = conversione_o2r_xq[1] 
        self.messaggio_odometria.pose.pose.position.z = conversione_o2r_xq[2]     
        self.messaggio_odometria.pose.pose.orientation.x =   conversione_o2r_xq[4]
        self.messaggio_odometria.pose.pose.orientation.y = conversione_o2r_xq[5] 
        self.messaggio_odometria.pose.pose.orientation.z =  conversione_o2r_xq[6] 
        self.messaggio_odometria.pose.pose.orientation.w =  conversione_o2r_xq[3] 
   
        self.messaggio_odometria.twist.twist.linear.x = self.forward_speed
        self.messaggio_odometria.twist.twist.linear.y = 0.0
        self.messaggio_odometria.twist.twist.angular.z = self.angular_speed

        
#        print("Odometry time stamp sec  = ",  self.messaggio_odometria.header.stamp.sec)
#        print("Odometry time stamp nsec = ",  self.messaggio_odometria.header.stamp.nanosec)


    # TWIST CALLBACK 
    def __cmd_vel_callback(self,twist): # ad ogni chiamata di questa funzione i valori cambiano
        
        self.forward_speed = twist.linear.x
        self.angular_speed = twist.angular.z

    # def __camera_callback(self, twist):
        
    #     self.pan_speed = twist.linear.x
    #     self.tilt_speed =   twist.angular.z
    def __camera_callback(self, jointstate):
	    # joint_msg.velocity()[1] = tilt_speed;
        self.pan_speed =    jointstate.velocity[0]

        self.tilt_speed =    jointstate.velocity[1]

    # ********************************* BEGIN SIMULATION CYCLE ******************************+
    def step(self): 
    
        global matrice_postsetup, matrice_post_setup_inversa

        rclpy.spin_once(self.__node, timeout_sec=0)

        # PRENDO DALLA BASE INERZIALE RPY
        vettore_rpy = self.imu.getRollPitchYaw() # roll =[0] pitch = [1] yaw = [2]
        '''x y,z, w'''
        # PRENDO DALLA BASE INERZIALE I QUATERNIONI
        vettore_quaternion = self.imu.getQuaternion()

        # TIMESTAMP
        current_time = self.__node.get_clock().now().to_msg()

        # SETUP MATRICE DI ROTO-TRASLAZIONE
        if self.inizio: 
            
            #  MATRICE DI ROTO-TRASLAZIONE RESTITUISCE UN VETTORE 1X16
            self.rototraslazione_post_robot = self.__robot.getSelf().getPose() 

            # DA 1X16 A 4X4
            matrice_postsetup = build_matrix(self.rototraslazione_post_robot)
            
            # PRINT MATRICE DI ROTO-TRASLAZIONE POST SETUP 
            # self.__node.get_logger().info('print della matrice costruita post-setup: ' + str(matrice_postsetup))

            # UTILIZZO LOBRERIA PYTRANSFORM3D PER OPERAZIONI CON MATRICE DI ROTO-TRASLAZIONE
            matrice_post_setup_inversa = transformations.invert_transform(matrice_postsetup)

            # PRINT MATRICE POST-SETUP INVERSA 
            # self.__node.get_logger().info('print della matrice costruita post-setup inversa: ' + str(matrice_post_setup_inversa))

            self.inizio = False

        '''PUBLISH ROVER DRIVER INFO '''
        self.rover_info_publisher.publish(self.messaggio_rover_info)

       
        '''FROM TWIST TO WHEEL VELOCITIES (KUKA Youbot differenziale)'''
        self.command_motor_left = (self.forward_speed - self.angular_speed*HALF_DISTANCE_BETWEEN_WHEELS)/raggioRuote
        self.command_motor_right = (self.forward_speed + self.angular_speed*HALF_DISTANCE_BETWEEN_WHEELS)/raggioRuote
                        
        # ************************ BEGIN ODOMETRY ********************************
                
        self.__motor_left.setVelocity(self.command_motor_left)
        self.__motor_right.setVelocity(self.command_motor_right)

        '''
        AXIS ANGLE VALUES
        CALCOLO QUATERNIONI DAI VALORI AXIS ANGLES DI WEBOTS 
        '''
        
        self.coordinate_assolute[0].getSFRotation()[0] #x
        self.coordinate_assolute[0].getSFRotation()[1] #y 
        self.coordinate_assolute[0].getSFRotation()[2] #z 
        self.coordinate_assolute[0].getSFRotation()[3] #w 

        # Definizione di un Quaternione con la libreria pyquaternion   w, x, y, z 
        
        '''UPDATE vettore_quaternion_wxyz from IMU SENSOR '''
        # vettore_quaternion_wxyz = np.array([vettore_quaternion[3], vettore_quaternion[0] , vettore_quaternion[1] , vettore_quaternion[2]]) 
        roto_now = build_matrix(self.__robot.getSelf().getPose())

        self.detect_markers(roto_now)

        '''
            COMPUTE  TRANSFORMATION ODOM -> BASE_LINK
            DALLA MATRICE DI ROTAAZIONE RICAVO X,Y,THETHA, QUATERNIONI 
        '''
        matrice_o2r  = transformations.concat(roto_now,matrice_post_setup_inversa)
        conversione_o2r_xq = transformations.pq_from_transform(matrice_o2r)

        self.update_odom_tf(conversione_o2r_xq, current_time)
        self.build_odom(conversione_o2r_xq, current_time)

        # PUBBLICAZIONE DEI MESSAGGI 
        
        ''' TIMESTEP'''

        self.count_time_stamp_scan+= self.__timestep / 1000.0
        self.count_time_stamp_odometry+= self.__timestep / 1000.0
        self.count_time_stamp_marker+= self.__timestep / 1000.0

        if self.count_time_stamp_scan >= TIME_STAMP_SCAN:
            self.messaggio_webots_scanner.header.stamp = self.__node.get_clock().now().to_msg()
            del self.messaggio_webots_scanner.ranges[:]
            ranges_ = self.__lidar.getRangeImage()

            self.messaggio_webots_scanner.ranges = list(reversed(ranges_))

            # Qui devo resettare alcuni angoli, valido per il lidar a 360 gradi
            # Angolo 169 -- 190
            if( self.laser_object.model == 'SLAMTEC'): 
                for i in range(len(self.messaggio_webots_scanner.ranges)):
                        
                        angolo =  (360.0/self.__lidar.getHorizontalResolution())*i
                        # if(angolo >= 90.0 and angolo<=270.0):
                        if(angolo >= 165.0 and angolo<=195.0):
                            self.messaggio_webots_scanner.ranges[i] = 0.0


                        
            self.laser_publisher.publish(self.messaggio_webots_scanner)
            self.count_time_stamp_scan = 0.0

        if self.count_time_stamp_odometry >= TIME_STAMP_ODOMETRY:
            self.odometry_publisher.publish(self.messaggio_odometria)

        if self.count_time_stamp_marker >= TIME_STAMP_OBJECTS:
            self.objects_publisher.publish(self.messaggio_objects) 
 
        
        #self.__node.get_logger().info( 'pubblica:  ' + str(pubblica) )

        # CALCOLO SPOSTAMENTO CAMERA:

        # CALCOLO SPOSTAMENTO ANGOLARE
        delta_pan = self.pan_speed*(self.__timestep/1000)
        delta_tilt = self.tilt_speed*(self.__timestep/1000)

        new_pan = self.pan_link[0].getSFRotation()[3] + delta_pan      
        new_tilt = self.tilt_link[0].getSFRotation()[3] + delta_tilt    

        axis_angle_pan = [self.pan_link[0].getSFRotation()[0], self.pan_link[0].getSFRotation()[1], self.pan_link[0].getSFRotation()[2], new_pan]

        R_pan_link = rotations.matrix_from_axis_angle(axis_angle_pan)   #   VARIABILI 
        M_pan_link = build_matrix_from_R(R_pan_link)                    #   VARIABILI
        M_pan_relativo = transformations.concat(self.M_visual_link,M_pan_link)  # ROTO-TRASLAZIONE DA VISUAL_LINK A  PAN_LINK
        quaternion_pan = transformations.pq_from_transform(M_pan_relativo) 

        axis_angle_tilt = [self.tilt_link[0].getSFRotation()[0], self.tilt_link[0].getSFRotation()[1], self.tilt_link[0].getSFRotation()[2], new_tilt]   # ROTAZIONE SU ASSE Z 

        # self.__node.get_logger().info('new axis_angle_tilt: ' + str(axis_angle_tilt))

        R_tilt_link = rotations.matrix_from_axis_angle(axis_angle_tilt)         # VARIABILI
        M_tilt_link = build_matrix_from_R(R_tilt_link)                            # VARIABILI 
        # M_tilt_relativo = transformations.concat(self.M_pan_tilt_link,M_tilt_link) # ROTO-TRASLAZIONE DA PANT_TILT_LINK A  PAN_TILT 
        M_tilt_relativo = transformations.concat(M_tilt_link,self.M_tilt_odom) # ROTO-TRASLAZIONE DA PANT_TILT_LINK A  PAN_TILT 

        self.pan_link[0].setSFRotation(axis_angle_pan)
        self.tilt_link[0].setSFRotation(axis_angle_tilt)

        quaternion_tilt = transformations.pq_from_transform(M_tilt_relativo)

        # ******************* PAN_LINK ******************

        self.TF_pan_link.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_pan_link.transform.rotation.w = quaternion_pan[3]
        self.TF_pan_link.transform.rotation.x = quaternion_pan[4]
        self.TF_pan_link.transform.rotation.y = quaternion_pan[5]
        self.TF_pan_link.transform.rotation.z = quaternion_pan[6]
        self.TF_pan_link.transform.translation.x = 0.0
        self.TF_pan_link.transform.translation.y = 0.0
        self.TF_pan_link.transform.translation.z = 0.0

        self.static_broadcaster.sendTransform(self.TF_pan_link) 


        # ******************* TILT_LINK ******************
        self.TF_pan_2_tilt.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_pan_2_tilt.transform.rotation.w = quaternion_tilt[3]
        self.TF_pan_2_tilt.transform.rotation.x = quaternion_tilt[4]
        self.TF_pan_2_tilt.transform.rotation.y = quaternion_tilt[5]
        self.TF_pan_2_tilt.transform.rotation.z = quaternion_tilt[6]
        self.TF_pan_2_tilt.transform.translation.x = 0.0
        self.TF_pan_2_tilt.transform.translation.y = 0.0
        self.TF_pan_2_tilt.transform.translation.z = 0.0

        self.static_broadcaster.sendTransform(self.TF_pan_2_tilt) 

    '''   FUNZIONI DENTRO STEP()    '''

    def detect_markers(self,roto_now):
        
        self.messaggio_objects = Object3DArray()
        num_objects = self.__camera.getRecognitionNumberOfObjects()
       
        if(num_objects > 0):

            # self.__node.get_logger().info('number of objects: ' + str(num_objects) )
            objects = self.__camera.getRecognitionObjects()

            vettore_models = []

            for obj in objects:
                oggetto_id = obj.getId()
                oggetto_model = obj.getModel()
                marker_position = obj.getPosition()
                marker_orientation  = obj.getOrientation()
                size = obj.getSize()
                

                for i in range(len(self.objects_vector)):
                                    
                    if(str(oggetto_model) == self.objects_vector[i].model):

                        # Calcolo la roto-traslazione tra marcatore e posizione attuale del robot 
                        roto_now_inv = transformations.invert_transform(roto_now)
                        matrice_mark2robot = transformations.concat( self.objects_vector[i].matrix_rototra,roto_now_inv)
                        conversione_mark2robot_xq = transformations.pq_from_transform(matrice_mark2robot)
                        
                        # COSTRUZIONE ELEMENTO DELLA LISTA DI MARKER 
                        object_i =  Object3D()
                        object_i.header.frame_id = "base_link"
                        object_i.header.stamp = self.__node.get_clock().now().to_msg()
                        # stringa_senza_virgolette = stringa_con_virgolette.replace("'", "")

                        # NUOVA MODIFICA 
                        marker_axis_angle = [marker_orientation[0], marker_orientation[1], marker_orientation[2], marker_orientation[3]]
                        marker_quaternion = rotations.quaternion_from_axis_angle(marker_axis_angle)


                        #.replace("'","")
                        #str(oggetto_id)
                        object_i.id = oggetto_model
                        # object_i.id.strip('"')
                        # object_i.id .replace("'","")
                        object_i.type = self.objects_vector[i].type

                        object_i.pose.pose.position.x = marker_position[0]
                        object_i.pose.pose.position.y = marker_position[1]
                        object_i.pose.pose.position.z = marker_position[2]

                        object_i.pose.pose.orientation.w = marker_quaternion[0]
                        object_i.pose.pose.orientation.x = marker_quaternion[1]
                        object_i.pose.pose.orientation.y = marker_quaternion[2]
                        object_i.pose.pose.orientation.z = marker_quaternion[3]

                        object_i.confidence = 1.0
                        self.messaggio_objects.objects.append(object_i)


    # FUNZIONI DI SETUP 
    ''' FUNZIONI DI SETUP DENTRO INIT()'''
    def init_components(self):

        self.forward_speed = 0.0
        self.angular_speed = 0.0
        self.command_motor_left = 0.0
        self.command_motor_right = 0.0
        self.count_time_stamp_scan = 0.0
        self.count_time_stamp_odometry = 0.0
        self.count_time_stamp_marker = 0.0

    def init_info_camera(self): 
        # VETTORE PER IL CONTROLLO DEL MOVIMENTO DELLA TELECAMERA:  VETTORI 1X2 CON ROTAZIONE E TRASLAZIONE

        self.R_visual_link = []  
        self.M_visual_link = [] 
        self.quaternion_visual = []

        self.R_pan_odom  = []
        self.M_pan_odom = []   

        self.visual_link = []
        self.pan_link = []

        self.R_pan_tilt_link = []
        self.M_pan_tilt_link = []
        self.pan_tilt_link = []
        self.quaternion_pan_tilt = []

        self.R_tilt_odom  = []
        self.M_tilt_odom = []   
        self.tilt_link = []
        self.tilt_link_odom = []    
        self.quaternion_tilt_odom = []

        self.R_camera_link  = []
        self.M_camera_link = []   

        self.R_tiago_M  = []
        self.M_tiago_M = []   
        self.M_tiago_finale_M = [] 
        self.quaternion_camera = []

        self.camera_link_odom= []    
        self.camera_link= []    
        self.tiago_M = []

        self.pan_speed = 0.0
        self.tilt_speed = 0.0


    # INITZIALIZZAZIONE TF
    def init_tf_odom(self):

        self.static_broadcaster = StaticTransformBroadcaster(self.__node)
        self.broadcaster = TransformBroadcaster(self.__node)
        self.odom_trasfrom = TransformStamped()
        self.odom_trasfrom.header.frame_id = 'odom'
        self.odom_trasfrom.child_frame_id = 'base_link'

        #   PER LA TELEMERA      

    # SCELTA DEL LASER DA UTILIZZARE DA FILE DI CONFIGURAZIONE 
    def init_laser(self, properties):
        """Configura il laser (URG o SLAMTEC) in base alle proprietà."""


        self.laser_name = 'laser_link'
        #   POSIZIONE DEL LASER 
        self.laser_x = 0.0
        self.laser_y = 0.0
        self.laser_z = 0.0  

        tipo_laser = properties.get('laser')

        if tipo_laser == 'urg':
            self.__node.get_logger().info('Laser selezionato: URG')
            self.laser_name = 'laser_urg'

            self.laser_x = float(properties.get('laser_urg_x'))
            self.laser_y = float(properties.get('laser_urg_y'))
            self.laser_z = float(properties.get('laser_urg_z'))

            self.__node.get_logger().info('LASER_URG_X' + str(self.laser_x))
            self.__node.get_logger().info('LASER_URG_Y' + str(self.laser_y))
            self.__node.get_logger().info('LASER_URG_Z' + str(self.laser_z))


        elif tipo_laser == 'slamtec':
            self.__node.get_logger().info('Laser selezionato: SLAMTEC')
            self.laser_name = 'laser_slamtec'

            self.laser_x = float(properties.get('laser_slamtec_x'))
            self.laser_y = float(properties.get('laser_slamtec_y'))
            self.laser_z = float(properties.get('laser_slamtec_z'))

            self.__node.get_logger().info('LASER_SLAMTEC_X' + str(self.laser_x))
            self.__node.get_logger().info('LASER_SLAMTEC_Y' + str(self.laser_y))
            self.__node.get_logger().info('LASER_SLAMTEC_Z' + str(self.laser_z))

        else:
            self.__node.get_logger().info('Tipo di laser non specificato.')
            return 

    # SETUP DEVICES IN SIMULAZIONE 
    def setup_robot_devices(self, properties):

        """Configura i dispositivi del robot (motori, sensori, lidar, ecc.)."""
        self.__motor_left = self.__robot.getDevice('wheel_left_joint')
        self.__motor_right = self.__robot.getDevice('wheel_right_joint')
        self.__sensor_left = self.__robot.getDevice('wheel_left_joint_sensor')
        self.__sensor_right = self.__robot.getDevice('wheel_right_joint_sensor')
        self.__lidar = self.__robot.getDevice(self.laser_name)

        self.gps = self.__robot.getDevice('gps')
        self.imu = self.__robot.getDevice('inertial unit')
        self.__camera = self.__robot.getDevice('YoubotCamera')


        for device in [self.__sensor_left, self.__sensor_right, self.gps, self.imu]:
            device.enable(self.__timestep)

        self.__motor_left.setPosition(float('inf'))
        self.__motor_right.setPosition(float('inf'))
        self.__motor_left.setVelocity(0.0)
        self.__motor_right.setVelocity(0.0)

        self.__lidar.enable(self.__timestep)
        self.__lidar.enablePointCloud()
        self.__camera.enable(self.__timestep)
        self.__camera.recognitionEnable(self.__timestep)

    #   SETUP PUBLISHER E SUBSCRIBERS 
    def setup_publishers_and_subscribers(self):
        """Crea i publisher e i subscriber ROS necessari."""

        #********************* SET QoS for STRESA connection***********************
        # qos_profile = QoSProfile(
        #     reliability=QoSReliabilityPolicy.RELIABLE,
        #     history=QoSHistoryPolicy.KEEP_LAST,
        #     durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
        #     depth=10
        # )
        #***************************************************************************

        self.odometry_publisher = self.__node.create_publisher(Odometry, 'odom', 1)
        self.laser_publisher = self.__node.create_publisher(LaserScan, 'scan_webots', 1)
        self.rover_info_publisher = self.__node.create_publisher(RoverInfo, 'rover_info', 1)
        self.objects_publisher = self.__node.create_publisher(Object3DArray, 'visual_objects', 1)
        
        self.__node.create_subscription(Twist, 'rover_twist', self.__cmd_vel_callback, 1)
        # self.__node.create_subscription(Twist,'camera_vel_sim',self.__camera_callback,1) 
        self.__node.create_subscription(JointState,'camera_vel',self.__camera_callback,1) 



    # DEFINIZIONE MESSAGGI ROS 
    def init_messages(self):
        """Inizializza i messaggi ROS."""
        self.target_twist = Twist()
        self.messaggio_objects = Object3DArray()
        self.messaggio_odometria = Odometry()
        self.messaggio_webots_scanner = LaserScan()
        self.messaggio_rover_info = RoverInfo()

        self.pan_twist = Twist() 
        self.tilt_twist = Twist() 

    #   SETUP MESSAGGIO LASER 
    def setup_laser_msg(self):
        """LASERSCAN MESSAGE"""
        self.laser_object = LaserObject.LaserObject()
        self.laser_object.setup('laser_link',
                                self.__lidar.getModel(),
                                self.__lidar.getMaxRange(),
                                self.__lidar.getMinRange(),
                                self.__lidar.getHorizontalResolution(),
                                self.__lidar.getFov()
                                )
        
        self.__node.get_logger().info('Laser Object \n')
        self.__node.get_logger().info('nome: ' + self.laser_object.nome)
        self.__node.get_logger().info('model: ' + self.laser_object.model)
        self.__node.get_logger().info('range_max: ' + str(self.laser_object.range_max))
        self.__node.get_logger().info('range_min: ' + str(self.laser_object.range_min))
        self.__node.get_logger().info('horizontal_resolution: ' + str(self.laser_object.horizontal_resolution))
        self.__node.get_logger().info('field_of_view: ' + str(self.laser_object.field_of_view))
        self.__node.get_logger().info('angle_min: ' + str(self.laser_object.angle_min))
        self.__node.get_logger().info('angle_max: ' + str(self.laser_object.angle_max))
        self.__node.get_logger().info('angle_increment: ' + str(self.laser_object.angle_increment))

        self.messaggio_webots_scanner.header.frame_id ="laser_link"
        self.messaggio_webots_scanner.angle_max = self.laser_object.angle_max
        self.messaggio_webots_scanner.angle_min = self.laser_object.angle_min

        self.messaggio_webots_scanner.range_max = self.laser_object.range_max
        self.messaggio_webots_scanner.range_min = self.laser_object.range_min
        # messaggio_webots_scanner.scan_time = scanner.scan_time
        self.messaggio_webots_scanner.time_increment = 0.0
        self.messaggio_webots_scanner.scan_time =  0.0032
        self.messaggio_webots_scanner.angle_increment = self.laser_object.angle_increment

    # SETUP ROVERS MESSAGE 
    def setup_rover_msg(self):

        self.rover_info =  RoverInformation.RoverInformation()

        self.messaggio_rover_info.footprint[0] = self.rover_info.min_x
        self.messaggio_rover_info.footprint[1] = self.rover_info.max_x
        self.messaggio_rover_info.footprint[2] = self.rover_info.min_y
        self.messaggio_rover_info.footprint[3] = self.rover_info.max_y
        self.messaggio_rover_info.footprint[4] = self.rover_info.min_z
        self.messaggio_rover_info.footprint[5] = self.rover_info.max_z
                
        self.messaggio_rover_info.safety_margin =  self.rover_info.safety_margin
        self.messaggio_rover_info.min_lin_vel = self.rover_info.min_lin_vel
        self.messaggio_rover_info.max_lin_vel = self.rover_info.max_lin_vel
        self.messaggio_rover_info.min_ang_vel = self.rover_info.min_ang_vel
        self.messaggio_rover_info.max_ang_vel = self.rover_info.max_ang_vel
        self.messaggio_rover_info.max_lin_acc = self.rover_info.max_lin_acc
        self.messaggio_rover_info.max_ang_acc = self.rover_info.max_ang_acc
        self.messaggio_rover_info.max_cen_acc = self.rover_info.max_cen_acc
        self.messaggio_rover_info.lin_resolution = self.rover_info.lin_resolution
        self.messaggio_rover_info.ang_resolution =self.rover_info.ang_resolution


    #   PRENDO LE INFORMAZIONI DAI NODI WEBOTS IN SIMULAZIONE 
    def take_data_from_Webots_node(self,properties,webots_node):

        ############################## TAKE INFO THANKS SUPERVISOR PERMISSIONS  #########################
        self.root_children_field = webots_node.robot.getRoot().getField('children')
        self.n =  self.root_children_field.getCount()
        
        '''ITERATION OF WEBOTS NODES'''
        for k in range(self.n):
                    
                    nodo_livello_1 = self.root_children_field.getMFNode(k)
                    # self.__node.get_logger().info(str(nodo_livello_1.getTypeName())+ '  ' + str(k))
                    if(nodo_livello_1.getTypeName() == 'Robot'):    # Cerco il nodo Door in base al nome
                        
                        self.__node.get_logger().info('trovato Robot alla posizione  '+ str(k))
                        robot_name = nodo_livello_1.getField('name')
                        
                        if(robot_name.getSFString() == 'Youbot base'):
                            self.__node.get_logger().info('è stato trovato il nodo Youbot base')
                            rotation_oggetto = nodo_livello_1.getField('rotation')
                            translation_oggetto = nodo_livello_1.getField('translation')

                            self.coordinate_assolute.append(rotation_oggetto)
                            self.coordinate_assolute.append(translation_oggetto)
                            self.__node.get_logger().info('trovato rotation Youbot base: ' + str(rotation_oggetto.getSFRotation()))
                            
                            self.__node.get_logger().info('trovato translation Youbot base: ' + str(translation_oggetto .getSFVec3f()))

                            children_1 = nodo_livello_1.getField('children')  

                            # SCELTA DEI LASER DA UTILIZZARE 

                            #   URG
                            nodo_laser_1 = children_1.getMFNode(0) 
                            laser_1_position = nodo_laser_1.getField('translation') 
                            self.__node.get_logger().info('Laser Position: ' + str(laser_1_position.getSFVec3f()[0]) + ', ' + str(laser_1_position.getSFVec3f()[1]) + ', ' + str(laser_1_position.getSFVec3f()[2]))
                            
                            #   SLAMTEC
                            nodo_laser_2 = children_1.getMFNode(1)
                            laser_2_position = nodo_laser_2.getField('translation') 
                            self.__node.get_logger().info('Laser Position: ' + str(laser_2_position.getSFVec3f()[0]) + ', ' + str(laser_2_position.getSFVec3f()[1]) + ', ' + str(laser_2_position.getSFVec3f()[2]))


                            if(self.laser_name == 'laser_urg'):
                                
                                posizione_laser_1 = [self.laser_x, self.laser_y, self.laser_z]
                                laser_1_position.setSFVec3f(posizione_laser_1)

                                # posizione_laser_2 = [0.0, 0.0, laser_2_position.getSFVec3f()[2]]
                                posizione_laser_2 = [0.0, 0.0, 0.0]
                                laser_2_position.setSFVec3f(posizione_laser_2)

                            elif(self.laser_name == 'laser_slamtec'):

                                # posizione_laser_1 = [0.0, 0.0, laser_1_position.getSFVec3f()[2]]
                                posizione_laser_1 = [0.0, 0.0, 0.0]

                                laser_1_position.setSFVec3f(posizione_laser_1)

                                posizione_laser_2 = [self.laser_x, self.laser_y, self.laser_z]
                                laser_2_position.setSFVec3f(posizione_laser_2)

                            #   FINE SCELTA DEI LASER 
                        
                            #   INIZIO MODIFICA 

                            nodo_livello_2 = children_1.getMFNode(2)
                            children_2 = nodo_livello_2.getField('children')
                            nodo_livello_3 = children_2.getMFNode(0)      
                            children_3 = nodo_livello_3.getField('children') 
                            nodo_livello_4 = children_3.getMFNode(0)            
                            children_4 = nodo_livello_4.getField('children')     
                            nodo_livello_5 = children_4.getMFNode(0)                                                                              # LIVELLO 8       VISUAL_LINK
                            self.__node.get_logger().info('visual_link')
                            visual_link_rot = nodo_livello_5.getField('rotation')       #   Da inserire in un vettore 
                            visual_link_tra = nodo_livello_5.getField('translation')    #   Da inserire in un vettore 
                            self.__node.get_logger().info('rotation_visual_link: ' + str(visual_link_rot.getSFRotation()))
                            self.__node.get_logger().info('translation_visual_link: ' + str(visual_link_tra.getSFVec3f()))                         

                            self.visual_link.append(visual_link_rot)    # APPEND ROTATION VISUAL LINK 
                            self.visual_link.append(visual_link_tra)    # APPEND TRANSLATION VISUAL_LINK             
                            # MATRICI DI ROTAZIONE VISUAL_LINK 

                            self.R_visual_link = rotations.matrix_from_axis_angle(visual_link_rot.getSFRotation())
                            self.M_visual_link = build_matrix_from_R(self.R_visual_link)
                            self.quaternion_visual = transformations.pq_from_transform(self.M_visual_link) # Quaternione VISUAL_LINK

                            self.__node.get_logger().info('R_visual_link: \n' + str(self.R_visual_link))
                            self.__node.get_logger().info('M_visual_link: \n' + str(self.M_visual_link))

                            children_5 = nodo_livello_5.getField('children')                                                                      # LIVELLO 9       CHILDREN                                                    
                            nodo_livello_6 = children_5.getMFNode(0)                                                                              # LIVELLO 10      PAN_LINK        
                            self.__node.get_logger().info('Sono dentro pan_link')
                            pan_link_rot = nodo_livello_6.getField('rotation') 
                            pan_link_tra = nodo_livello_6.getField('translation')  
                            self.__node.get_logger().info('rotation_pan_link: ' + str(pan_link_rot.getSFRotation()))
                            self.__node.get_logger().info('translation_pan_link: ' + str(pan_link_tra.getSFVec3f()))

                            self.pan_link.append(pan_link_rot)
                            self.pan_link.append(pan_link_tra)

                            children_6 = nodo_livello_6.getField('children')                                                                      # LIVELLO 11      CHILDREN
                            nodo_livello_7 = children_6.getMFNode(0)                                                                              # LIVELLO 12      PANT_TILT_LINK

                            self.__node.get_logger().info('Sono dentro pan_tilt_link')
                            pan_tilt_link_rot = nodo_livello_7.getField('rotation') #   Da inserire in un vettore 
                            pan_tilt_link_tra = nodo_livello_7.getField('translation')   #   Da inserire in un vettore 
                            self.__node.get_logger().info('rotation_pan_tilt_link: ' + str(pan_tilt_link_rot.getSFRotation()))
                            self.__node.get_logger().info('translation_pan_tilt_link: ' + str(pan_tilt_link_tra.getSFVec3f()))

                            self.pan_tilt_link.append(pan_tilt_link_rot)
                            self.pan_tilt_link.append(pan_tilt_link_tra)

                            # MATRICI DI ROTAZIONE PAN_TILT_LINK

                            self.R_pan_tilt_link = rotations.matrix_from_axis_angle(pan_tilt_link_rot.getSFRotation())
                            self.M_pan_tilt_link = build_matrix_from_R(self.R_pan_tilt_link)
                            self.quaternion_pan_tilt = transformations.pq_from_transform(self.M_pan_tilt_link)

                            self.__node.get_logger().info('R_pan_tilt_link: \n' + str(self.R_pan_tilt_link))
                            self.__node.get_logger().info('M_pan_tilt_link: \n' + str(self.M_pan_tilt_link))

                            children_7 = nodo_livello_7.getField('children')                                                                      # LIVELLO 13      CHILDREN
                            nodo_livello_8 = children_7.getMFNode(0)    

                            self.__node.get_logger().info('Sono dentro tilt_link')
                            tilt_link_rot = nodo_livello_8.getField('rotation') 
                            tilt_link_tra = nodo_livello_8.getField('translation')  

                            self.__node.get_logger().info('rotation_tilt_link: ' + str(tilt_link_rot.getSFRotation()))
                            self.__node.get_logger().info('translation_tilt_link: ' + str(tilt_link_tra.getSFVec3f()))

                            # SALVATAGGIO TILT_LINK --> MOBILE 
                            self.tilt_link.append(tilt_link_rot)
                            self.tilt_link.append(tilt_link_tra)

                            self.R_tilt_odom = rotations.matrix_from_axis_angle(pan_tilt_link_rot.getSFRotation())
                            self.M_tilt_odom = build_matrix_from_R(self.R_pan_tilt_link)
                            self.quaternion_tilt_odom = transformations.pq_from_transform(self.M_pan_tilt_link)

                            children_8 = nodo_livello_8.getField('children') # CERCO IL FIELD CHILDENTRO IN ROBOT                                 # LIVELLO 15      CHILDREN
                            nodo_livello_9 = children_8.getMFNode(0)   

                            self.__node.get_logger().info('Sono dentro camera_link')
                            camera_link_rot = nodo_livello_9.getField('rotation')        
                            camera_link_tra = nodo_livello_9.getField('translation')  
                            self.__node.get_logger().info('rotation_camera_link: ' + str(camera_link_rot.getSFRotation()))
                            self.__node.get_logger().info('translation_camera_link: ' + str(camera_link_tra.getSFVec3f()))

                            # SALVATAGGIO CAMERA_LINK
                            self.camera_link.append(camera_link_rot)
                            self.camera_link.append(camera_link_tra)

                            self.R_tilt_2_tiltcamera_link = rotations.matrix_from_axis_angle(camera_link_rot.getSFRotation())
                            self.M_tilt_2_tiltcamera_link  = build_matrix_from_R(self.R_tilt_2_tiltcamera_link)

                            # self.R_camera_link = rotations.matrix_from_axis_angle(camera_link_rot.getSFRotation())
                            # self.M_camera_link = build_matrix_from_R(self.R_camera_link)

                            children_9 = nodo_livello_9.getField('children')                                                                      # LIVELLO 17      CHILDREN
                            nodo_livello_10 = children_9.getMFNode(0)   

                            self.__node.get_logger().info('Sono dentro YoubotCamera')
                            tiago_camera_rot = nodo_livello_10.getField('rotation') 
                            tiago_camera_tra = nodo_livello_10.getField('translation')   
                            self.__node.get_logger().info('rotation_YoubotCamera: ' + str(tiago_camera_rot.getSFRotation()))
                            self.__node.get_logger().info('translation_YoubotCamera: ' + str(tiago_camera_tra.getSFVec3f()))
                            
                            self.tiago_M.append(tiago_camera_rot)
                            self.tiago_M.append(tiago_camera_tra)

                            self.R_tiltcamera_2_camera_link = rotations.matrix_from_axis_angle(tiago_camera_rot.getSFRotation())
                            self.M_tiltcamera_2_camera_link = build_matrix_from_R(self.R_tiltcamera_2_camera_link)

                            self.M_tilt_2_camera = transformations.concat(self.M_tiltcamera_2_camera_link,self.M_tilt_2_tiltcamera_link)
                            self.quaternion_camera = transformations.pq_from_transform(self.M_tilt_2_camera)

                            # FINE MODIFICA 

                        if(robot_name.getSFString().__contains__("human_")):

                                self.__node.get_logger().info('è stato trovato il nodo human')
                                field_name = nodo_livello_1.getField('name')

                                self.__node.get_logger().info('Il campo contiene la parola human ' + str(k))
                                self.__node.get_logger().info('Trovato ' + field_name.getSFString() + 'alla posizione ' + str(k))
                                human_name = nodo_livello_1.getField('name')
                                human_model = nodo_livello_1.getField('model')
                                human_type = "human" # Tipo di oggetto
                                human_size_x = 0.1
                                human_size_y = 0.1
                                human_size_z = 0.001

                                human_translation = nodo_livello_1.getField('translation')
                                human_rotation = nodo_livello_1.getField('rotation')
                                self.__node.get_logger().info("nome human: " + human_name.getSFString() )
                                self.__node.get_logger().info("model human: " + human_model.getSFString() )
                                self.__node.get_logger().info('Posizione assoluta ' + human_name.getSFString() + ' ' + str(human_translation.getSFVec3f()))
                                self.__node.get_logger().info('Rotazione assoluta ' + human_name.getSFString() + ' ' + str(human_rotation.getSFRotation())+ '\n')   

                                #############################

                                umano = ClassObject.ClassObject()

                                matrice_human = build_matrix(nodo_livello_1.getPose())
                                matrice_human_inv = transformations.invert_transform(matrice_human)

                                umano.setup(    human_name.getSFString(),
                                                    human_model.getSFString(),
                                                    human_type,
                                                    human_size_x,
                                                    human_size_y,
                                                    human_size_z,
                                                    human_translation.getSFVec3f(),
                                                    human_rotation.getSFRotation(),
                                                    matrice_human,
                                                    matrice_human_inv)


                                self.objects_vector.append(umano)



                    if(nodo_livello_1.getTypeName() == 'Solid'):    # Cerco il nodo Door in base al nome
                        field_name = nodo_livello_1.getField('name')                        

                        if (field_name.getSFString().__contains__("marker_")):
                            self.__node.get_logger().info('Il campo contiene la parola marker ' + str(k))
                            self.__node.get_logger().info('Trovato ' + field_name.getSFString() + 'alla posizione ' + str(k))
                            marker_name = nodo_livello_1.getField('name')
                            marker_model = nodo_livello_1.getField('model')
                            marker_type = "marker" # Tipo di oggetto
                            marker_size_x = 0.1
                            marker_size_y = 0.1
                            marker_size_z = 0.001

                            marker_translation = nodo_livello_1.getField('translation')
                            marker_rotation = nodo_livello_1.getField('rotation')
                            self.__node.get_logger().info("nome marker: " + marker_name.getSFString() )
                            self.__node.get_logger().info("model marker: " + marker_model.getSFString() )
                            self.__node.get_logger().info('Posizione assoluta ' + field_name.getSFString() + ' ' + str(marker_translation.getSFVec3f()))
                            self.__node.get_logger().info('Rotazione assoluta ' + field_name.getSFString() + ' ' + str(marker_rotation.getSFRotation())+ '\n')   

                            #############################

                            marcatore = ClassObject.ClassObject()

                            matrice_marker = build_matrix(nodo_livello_1.getPose())
                            matrice_marker_inv = transformations.invert_transform(matrice_marker)

                            marcatore.setup(    marker_name.getSFString(),
                                                marker_model.getSFString(),
                                                marker_type,
                                                marker_size_x,
                                                marker_size_y,
                                                marker_size_z,
                                                marker_translation.getSFVec3f(),
                                                marker_rotation.getSFRotation(),
                                                matrice_marker,
                                                matrice_marker_inv)


                            self.objects_vector.append(marcatore)

                        # FINE OPERAZIONI SU NOD1 

        # Ordinamento della objects_vector tramite attributo model
        self.objects_vector.sort(key = lambda x : x.model)

        # PRINT DATA GIVEN BY SUPERVISOR PERMISSIONS  
        self.__node.get_logger().info( 'Lettura parametri da file .urdf')
        self.__node.get_logger().info( 'posizione_x letta: ' + (properties.get('translation_x')))
        self.__node.get_logger().info( 'posizione_y letta: ' + (properties.get('translation_y')))
        self.__node.get_logger().info( 'posizione_z letta: ' + (properties.get('translation_z')))
        self.__node.get_logger().info( 'rotation_x letta: ' + (properties.get('rotation_x')))
        self.__node.get_logger().info( 'rotation_y letta: ' + (properties.get('rotation_y')))
        self.__node.get_logger().info( 'rotation_z letta: ' + (properties.get('rotation_z')))
        self.__node.get_logger().info( 'rotation_w letta: ' + (properties.get('rotation_w')))
        self.x_robot = float(properties.get('translation_x'))
        self.y_robot = float(properties.get('translation_y'))
        self.z_robot = float(properties.get('translation_z'))

        posizioni_iniziale = [self.x_robot,self.y_robot, self.z_robot]
        self.coordinate_assolute[1].setSFVec3f(posizioni_iniziale)

        # READ CONFIGURATION FILE FOR SET THE INIZIAL POSE OF THE ROBOT IN THE WORLD SIMULATION (QUATERNIONS)
        self.rotation_x = float(properties.get('rotation_x'))
        self.rotation_y = float(properties.get('rotation_y'))
        self.rotation_z = float(properties.get('rotation_z'))
        self.rotation_w = float(properties.get('rotation_w'))

        # CONVERSION FROM QUATERNION TO AXIS_ANGLES 
        quat_input= np.array([self.rotation_w, self.rotation_x, self.rotation_y, self.rotation_z])
        axis = []
        angle = 0.0
        #x,y,z
        axis, angle = quaternion_to_axis_angle(quat_input)
        self.__node.get_logger().info( 'axis: ' + str(axis)) 
        self.__node.get_logger().info( 'angle: ' + str(angle)) 
        orientamento_iniziale = [float(axis[0]),float(axis[1]),float(axis[2]),angle]
        self.__node.get_logger().info( 'prima: ' + str(self.coordinate_assolute[0].getSFRotation()))
        self.coordinate_assolute[0].setSFRotation(orientamento_iniziale)

        # USING METHOD OF PYQUATERNION LIBRARIE
        '''w, x, y, z '''  
        self.quaternione_iniziale = Quaternion(self.rotation_w,self.rotation_x,self.rotation_y,self.rotation_z)
        self.quaternione_iniziale_inverso = self.quaternione_iniziale.inverse


    def init_tf_camera(self):

        # ******************* VISUAL_TILT_LINK ******************

        self.TF_visual_link = TransformStamped()
        self.TF_visual_link.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_visual_link.header.frame_id = 'base_link'
        self.TF_visual_link.child_frame_id = 'visual_link'

        self.TF_visual_link.transform.rotation.w = self.quaternion_visual[3] 
        self.TF_visual_link.transform.rotation.x = self.quaternion_visual[4]
        self.TF_visual_link.transform.rotation.y = self.quaternion_visual[5] 
        self.TF_visual_link.transform.rotation.z = self.quaternion_visual[6] 
        self.TF_visual_link.transform.translation.x = 0.14   
        self.TF_visual_link.transform.translation.y = 0.0
        self.TF_visual_link.transform.translation.z = 0.343

        self.static_broadcaster.sendTransform(self.TF_visual_link)  # VALORI COSTANTI 


        # ******************* PAN_LINK_TILT_LINK ******************
        self.TF_pan_link = TransformStamped()
        self.TF_pan_link.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_pan_link.header.frame_id = 'visual_link'
        self.TF_pan_link.child_frame_id = 'pan_link'

        # ******************* PAN_LINK   TILT_LINK ******************     ANGOLO VARIABILE 

        self.TF_pan_2_tilt = TransformStamped()
        self.TF_pan_2_tilt.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_pan_2_tilt.header.frame_id = 'pan_link'
        self.TF_pan_2_tilt.child_frame_id = 'tilt_link'


        axis_angle_tilt = [self.tilt_link[0].getSFRotation()[0], self.tilt_link[0].getSFRotation()[1], self.tilt_link[0].getSFRotation()[2], self.tilt_link[0].getSFRotation()[3]]   # ROTAZIONE SU ASSE Z 

        # self.__node.get_logger().info('new axis_angle_tilt: ' + str(axis_angle_tilt))

        R_tilt_link = rotations.matrix_from_axis_angle(axis_angle_tilt)         # VARIABILI
        M_tilt_link = build_matrix_from_R(R_tilt_link)                            # VARIABILI 
        # M_tilt_relativo = transformations.concat(self.M_pan_tilt_link,M_tilt_link) # ROTO-TRASLAZIONE DA PANT_TILT_LINK A  PAN_TILT 
        M_tilt_relativo = transformations.concat(self.M_tilt_odom,M_tilt_link) # ROTO-TRASLAZIONE DA PANT_TILT_LINK A  PAN_TILT 

        self.tilt_link[0].setSFRotation(axis_angle_tilt)

        quaternion_tilt = transformations.pq_from_transform(M_tilt_relativo)

        #   VALORI DA SETTARE 

        self.TF_pan_2_tilt.transform.rotation.w = quaternion_tilt[3]
        self.TF_pan_2_tilt.transform.rotation.x = quaternion_tilt[4]
        self.TF_pan_2_tilt.transform.rotation.y = quaternion_tilt[5]
        self.TF_pan_2_tilt.transform.rotation.z = quaternion_tilt[6]

        self.TF_pan_2_tilt.transform.translation.x = 0.0
        self.TF_pan_2_tilt.transform.translation.y = 0.0
        self.TF_pan_2_tilt.transform.translation.z = 0.0  


        #******************* TILT_LINK CAMERA_LINK  FISSO ******************

        self.TF_camera_link = TransformStamped()
        self.TF_camera_link.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_camera_link.header.frame_id = 'tilt_link'
        self.TF_camera_link.child_frame_id = 'camera_link'

        self.TF_camera_link.header.stamp = self.__node.get_clock().now().to_msg()
        self.TF_camera_link.transform.rotation.w = self.quaternion_camera[3]
        self.TF_camera_link.transform.rotation.x = self.quaternion_camera[4]
        self.TF_camera_link.transform.rotation.y = self.quaternion_camera[5]
        self.TF_camera_link.transform.rotation.z = self.quaternion_camera[6]
        self.TF_camera_link.transform.translation.x = 0.0
        self.TF_camera_link.transform.translation.y = 0.0
        self.TF_camera_link.transform.translation.z = 0.0

        self.static_broadcaster.sendTransform(self.TF_camera_link) 


#   FUNZIONI DI CONVERSIONE 

def quaternion_to_axis_angle(quaternion):
    # Ensure quaternion is normalized
    quaternion = quaternion / np.linalg.norm(quaternion)

    # Extract angle of rotation
    angle = 2 * np.arccos(quaternion[0]) 
    if(angle == 0):
             x_aa = 0.0 
             y_aa = 0.0
             z_aa = 1.0
    else: 

        x_aa = quaternion[1] / np.sin(angle / 2)
        y_aa = quaternion[2] / np.sin(angle / 2)
        z_aa = quaternion[3] / np.sin(angle / 2)

    axis = np.array([x_aa,y_aa,z_aa])

    return axis, angle

def quat2eulers(q0:float, q1:float, q2:float, q3:float) -> tuple:

    roll = math.atan2( 2 * ((q2 * q3) + (q0 * q1)), q0**2 - q1**2 - q2**2 + q3**2 ) # radians
    pitch = math.asin(2 * ((q1 * q3) - (q0 * q2)))
    yaw = math.atan2( 2 * ((q1 * q2) + (q0 * q3)), q0**2 + q1**2 - q2**2 - q3**2 )
    
    return (roll, pitch, yaw)


# Provo ado ottimizzare qualche funzione per redere il codice più leggibile 

def build_matrix(vettore_matrice):
    
    matrice = np.array(
        [[vettore_matrice[0], vettore_matrice[1], vettore_matrice[2] , vettore_matrice[3]],
        [vettore_matrice[4], vettore_matrice[5], vettore_matrice[6], vettore_matrice[7]],
        [vettore_matrice[8], vettore_matrice[9], vettore_matrice[10], vettore_matrice[11]],
        [vettore_matrice[12],vettore_matrice[13],vettore_matrice[14],vettore_matrice[15]]
        ])
    return matrice

def build_matrix_from_R(vettore_matrice):
    
    matrice = np.array(
        [[vettore_matrice[0][0], vettore_matrice[0][1], vettore_matrice[0][2], 0],
        [vettore_matrice[1][0], vettore_matrice[1][1], vettore_matrice[1][2], 0],
        [vettore_matrice[2][0], vettore_matrice[2][1], vettore_matrice[2][2], 0],
        [0,0,0,1]
        ])
    return matrice

