# Driver 
## simulation_launch.py
File che contiene la logica del controllore ```TIAGO```

## Commento del codice


## Variabili globali 

Posizioni iniziali assolute: 
```
x_robot = 0.0  #posizione x assoluta iniziale del robot   
y_robot = 0.0  #posizione y assoluta iniziale del robot 
z_robot = 0.0  #posizione z assoluta iniziale del robot 
```
Valore iniziale delle ruote 
```
wl_robot = 0.0  #velocità iniziale ruota sinistra del robot 
wr_robot = 0.0  #velocità iniziale ruota destra del robot 
```
Dati strutturali del robot:
```
HALF_DISTANCE_BETWEEN_WHEEELS = 0.202  #(distanza tra le ruote)/2 (m)
D = 0.404 #distanza tra le ruote (m)
R = 0.0985  #raggio ruote motrici (m)
```
Limiti di velocià:
```
max_speed_motor = 10.0  #velocità massima in modulo delle ruote motrici 
min_speed_motor = 0.0   #velocità minima in modulo delle ruote motrici
```
Nomi sensori e motori ruote:
```
motor_left_name = 'wheel_left_joint'  #nome motore sinistro in simulazione 
motor_right_name = 'wheel_right_joint'  #nome motore destro in simulazione 

sensor_left_name = 'wheel_left_joint_sensor'  #nome sensore su motore sinistro in simulazione 
sensor_right_name = 'wheel_right_joint_sensor'  #nome sensore su motore destro in simulazione 
```
Time step di simulazione:
```
TIME_STEP = 32 
```
TWist iniziale:
```
forward_speed = 0.0  #velocità lineare del robot  TWIST.V
angular_speed = 0.0  #velocità angolare del robot  TWIST.W
```
Messaggi per sensori ad infrarossi:
```
messaggio_ir_right = Float64()  #messaggio per l'infrarosso destro
messaggio_ir_left = Float64() #messaggio per l'infrarosso sinistro
```
Messaggi per lo SLAM e LOCALIZATION:
```
messaggio_map_2_odom = Transform()  #messaggio per definire TF da map a odom
messaggio_odometria = Odometry()  #messaggio per definire l'odometria
w2o_transform_iniziale =  Transform()  #messaggio per definire TF iniziale tra world e odom
w2o_transform_iniziale_inversa = Transform() #messaggio per definire TF iniziale tra odom e world
messaggio_webots_scanner = LaserScanner() #messaggio per le scanzioni laser
messaggio_rover_info = RoverInfo()  #messaggio per informazioni del robot
```
Variabile per il primo step di simulazione:
```
inizio = True   #Variabile booleana per eseguire codice al primo ciclo di iterazione
```
Lista dei dati presi dal LaserScanner:
```
ranges = list()  #lista dei range misurati dal laser 
```
Matrici di rotazione e quaternioni:
```
position = [0.0, 0.0, 0.0]  #vettore delle posizioni
orientation = [0.0, 0.0, 0.0, 0.0]  #vettore orientamenti (espresso in quaternioni)
matrice_postsetup = []  #matrice di rotazione post_setup tra world e odom
matrice_post_setup_inversa = []  #matrice di rotazione post_setup tra odom e world
```
Posizioni e orientamento iniziali del robot:
```
yaw_iniziale = 0.0  #orientamento iniziale del robot
x_iniziale = 0.0    #posizione x iniziale del robot
y_iniziale = 0.0    #posizione y iniziale del robot 

```
## TIAGO Init 

```Funzione di init
def init(self, webots_node, properties)
```
- webots_node = nodo webots che fa riferimento al robot
- properties = parametri che inserisco nel file .urdf 

```
self.__ robot  #variabile che fa riferimento al robot node
self.__timestep #variabile che tiene conto del time step
self.__node  #nodo ROS associato al robot
self.target_twist #twist target del robot
self.static_broadcaster #TF Static Broadcaster
self.broadcaster   #TF Broadcaster 
self.ma2odom  #TF da map a odom 
self.odom_transform  #TF  da base a odom
```
Inizializzazione device ruote ed encoder: 

```
self.__motor_left = self.__robot.getDevice(motor_left_name)
self.__sensor_left = self.__robot.getDevice(sensor_left_name)
self.__sensor_left.enable(self.__timestep)
self.__motor_left.setPosition(float('inf'))
self.__motor_left.setVelocity(0.0)

self.__motor_right = self.__robot.getDevice(motor_right_name)
self.__sensor_right = self.__robot.getDevice(sensor_right_name)
self.__sensor_right.enable(self.__timestep)
self.__motor_right.setPosition(float('inf'))
self.__motor_right.setVelocity(0.0)
```
Inizializzazione e abilitazione sensori  aggiuntivi a TIAGo:
```
self.gps= self.__robot.getDevice('gps')
self.gps.enable(self.__timestep)
       
self.__sensor_LEFTIR = self.__robot.getDevice('base_sonar_03_link')
self.__sensor_LEFTIR.enable(self.__timestep)
             
self.__sensor_RIGHTIR = self.__robot.getDevice('base_sonar_01_link')
self.__sensor_RIGHTIR.enable(self.__timestep)

self.__sensor_MIDDLE = self.__robot.getDevice('base_sonar_02_link')
self.__sensor_MIDDLE.enable(self.__timestep)

self.imu = self.__robot.getDevice('inertial unit')
self.imu.enable(self.__timestep)

self.__lidar = self.__robot.getDevice('lidar')
self.__lidar.enable(self.__timestep)
self.__lidar.enablePointCloud()
```
Set QoS per la comunicazione con STRESA:
```
qos_profile = QoSProfile(
reliability=QoSReliabilityPolicy.RELIABLE,
history=QoSHistoryPolicy.KEEP_LAST,
durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
depth=10
)
```
Inizializzaztion Publishers
```
self.left_ir_publisher = self.__node.create_publisher(Float64,'tiago_ir_left',1)
self.right_ir_publisher = self.__node.create_publisher(Float64,'tiago_ir_right',1)
self.middle_distance_publisher = self.__node.create_publisher(Range,'middle_sensor',1)
self.odometry_publisher = self.__node.create_publisher(Odometry,'odom',qos_profile)
self.laser_publisher = self.__node.create_publisher(LaserScan, 'scan_webots',qos_profile)
self.rover_info_publisher = self.__node.create_publisher(RoverInfo,'rover_info',qos_profile) 
```
Inizializzazione Publisher per visualizzazione in RVIZ
```
self.tf_odom_publisher = self.__node.create_publisher(Transform,'rt/frame_odom',qos_profile)
```
Inizializzazione Subscribers
```
self.laser_subscriber = self.__node.create_subscription(LaserScan,'scan',self.__scan_callback,1)
self.__node.create_subscription(Twist,'cmd_vel',self.__cmd_vel_callback,qos_profile)
self.__node.create_subscription(PoseWithCovariance,'pose_with_covariance',self.__pose_covariance_callback,qos_profile)
```
Inizializzazione Subscriber per la visualizzazione in RVIZ
```
self.__node.create_subscription(Transform,'map_2_odom',self.__map_to_odom_callback,qos_profile) 
```
Controllo se il robot ha i permessi di Supervisor
```
self.__robot.getSupervisor()  #deve restituirmi true 
```
Prendo dati dalla simulazione grazie ai permessi di Supervisor 
```
self.posizione_robot = self.__robot.getSelf().getPosition() # Vector 1x3        
self.orientazione_robot = self.__robot.getSelf().getOrientation() # Vector 3x3    
self.rototraslazione_robot = self.__robot.getSelf().getPose() # Matrix roto-traslantion
```
Costruzione matrice di rototraslazione 
```

self.matrice_presetup = np.array(
  [ [ self.rototraslazione_robot[0],
      self.rototraslazione_robot[1],
      self.rototraslazione_robot[2],
      self.rototraslazione_robot[3]
    ],
    [ self.rototraslazione_robot[4],
      self.rototraslazione_robot[5],
      self.rototraslazione_robot[6],
      self.rototraslazione_robot[7]
    ],
    [ self.rototraslazione_robot[8],
      self.rototraslazione_robot[9],
      self.rototraslazione_robot[10],
      self.rototraslazione_robot[11]
    ],
    [ self.rototraslazione_robot[12],
      self.rototraslazione_robot[13],
      self.rototraslazione_robot[14],
      self.rototraslazione_robot[15]]
    ])
        
```
Setto le velocità iniziali delle ruote del robot 
```
command_motor_left = 0.0
command_motor_right = 0.0 
self.__motor_right.setVelocity(command_motor_right)
self.__motor_left.setVelocity(command_motor_left)
```
Metodo per accedere ai nodi webots di simulazione:
```
self.root_children_field = webots_node.robot.getRoot().getField('children')
self.n =  self.root_children_field.getCount()

for k in range(self.n):            
  nodo_k = self.root_children_field.getMFNode(k)
  if(nodo_k.getTypeName() == 'Robot'):    # Cerco il nodo Door in base al nome           
    uomo_name = nodo_k.getField('name')         
  if(uomo_name.getSFString() == 'TIAGo Base'):
    rotation_oggetto = nodo_k.getField('rotation')
    translation_oggetto = nodo_k.getField('translation')

    coordinate_assolute.append(rotation_oggetto)
    coordinate_assolute.append(translation_oggetto)         
```
Lettura dei parametri dal file di configurazione .urdf:

```
self.x_robot = float(properties.get('translation_x'))
self.y_robot = float(properties.get('translation_y'))
self.z_robot = float(properties.get('translation_z'))
self.rotation_x = float(properties.get('rotation_x'))
self.rotation_y = float(properties.get('rotation_y'))
self.rotation_z = float(properties.get('rotation_z'))
self.rotation_w = float(properties.get('rotation_w'))
```
Conversione dati file di configurazione da quaternioni ad axis angles:

```
quat_input= np.array([self.rotation_w, self.rotation_x, self.rotation_y, self.rotation_z])
axis = []
angle = 0.0
axis, angle = quaternion_to_axis_angle(quat_input)
orientamento_iniziale = [float(axis[0]),float(axis[1]),float(axis[2]),angle]
coordinate_assolute[0].setSFRotation(orientamento_iniziale)
```
Inizializzazione TF world to odom:

```
self.w2o_transform = TransformStamped()
self.w2o_transform.header.stamp = self.__node.get_clock().now().to_msg()
self.w2o_transform.header.frame_id = 'world'
self.w2o_transform.child_frame_id = 'odom'

self.w2o_transform.transform.rotation.x = self.rotation_x
self.w2o_transform.transform.rotation.y = self.rotation_y
self.w2o_transform.transform.rotation.z = self.rotation_z
self.w2o_transform.transform.rotation.w = self.rotation_w
self.w2o_transform.transform.translation.x = self.x_robot
self.w2o_transform.transform.translation.y = self.y_robot
self.w2o_transform.transform.translation.z = 0.0
```
Utilizzo libreria PYQUATERNION
 ```
 self.quaternione_iniziale = Quaternion(self.rotation_w,self.rotation_x,self.rotation_y,self.rotation_z)
 self.quaternione_iniziale_inverso = self.quaternione_iniziale.inverse
```

## TIAGO Callbacks
Callback twist:
```
def __cmd_vel_callback(self,twist):
global forward_speed,angular_speed
forward_speed = twist.linear.x
angular_speed = twist.angular.z
```
Callback PoseWithCovariance:
```
def __pose_covariance_callback(self,pose_covariance):
  print()
```
Callback map 2 odom: 

```
def __map_to_odom_callback(self,transform):
  global messaggio_map_2_odom 

  messaggio_map_2_odom.translation.x = transform.translation.x
  messaggio_map_2_odom.translation.y = transform.translation.y
  messaggio_map_2_odom.translation.z = transform.translation.z
  messaggio_map_2_odom.rotation.x = transform.rotation.x
  messaggio_map_2_odom.rotation.y = transform.rotation.y
  messaggio_map_2_odom.rotation.z = transform.rotation.z
  messaggio_map_2_odom.rotation.w = transform.rotation.w

  self.map2odom_transform.transform._translation.x = transform.translation.x
  self.map2odom_transform.transform._translation.y  = transform.translation.y
  self.map2odom_transform.transform._translation.z  = transform.translation.z

  self.map2odom_transform.transform.rotation.x = transform.rotation.x
  self.map2odom_transform.transform.rotation.y = transform.rotation.y
  self.map2odom_transform.transform.rotation.z = transform.rotation.z
  self.map2odom_transform.transform.rotation.w = transform.rotation.w

  self.static_broadcaster.sendTransform(self.map2odom_transform)
```

Callback scan:

```
def __scan_callback(self,scanner):
  global ranges, messaggio_webots_scanner
  messaggio_webots_scanner.header.frame_id ="lidar"
  messaggio_webots_scanner.header.stamp = self.__node.get_clock().now().to_msg()
  messaggio_webots_scanner.range_max = scanner.range_max
  messaggio_webots_scanner.range_min = scanner.range_min
  messaggio_webots_scanner.time_increment = scanner.time_increment
  messaggio_webots_scanner.scan_time = 0.032
  messaggio_webots_scanner.angle_increment = scanner.angle_increment
  messaggio_webots_scanner.angle_max = scanner.angle_max
  messaggio_webots_scanner.angle_min = scanner.angle_min

  ranges_local = list()
  for i in range(len(scanner.ranges)):
    ranges_local.insert(i,scanner.ranges[i])
  ranges = ranges_local
  messaggio_webots_scanner.ranges = ranges_local
```

## TIAGO step 
Richiamo le variabili globali:
```
global command_motor_left, command_motor_right, forward_speed,angular_speed,
global ranges, messaggio_webots_scanner, messaggio_rover_info
global coordinate_assolute, matrice_postsetup, matrice_post_setup_inversa,
global yaw_iniziale, inizio,x_robot,y_robot, x_iniziale, y_iniziale
```

Prendo le variabili globali della posizione:
```
vettore_rpy = self.imu.getRollPitchYaw() # roll =[0] pitch = [1]
yaw   = vettore_rpy[2]  # prendo l'angolo iniziale del robot 
x_robot = self.__robot.getSelf().getPosition()[0] # prendo la posizione x inziiale del robot 
y_robot = self.__robot.getSelf().getPosition()[1] # prendo la posizione y iniziale del robot    
vettore_quaternion = self.imu.getQuaternion()
current_time = self.__node.get_clock().now().to_msg()
```
Esecuzione del primo ciclo

```
if inizio: 
  self.rototraslazione_post_robot = self.__robot.getSelf().getPose() # MAtrice di rototraslazione me lo restituisce in un vettore 1x16
  matrice_postsetup = np.array(
    [
    [  self.rototraslazione_post_robot[0],
       self.rototraslazione_post_robot[1],
       self.rototraslazione_post_robot[2],
       self.rototraslazione_post_robot[3]
    ],
    [  self.rototraslazione_post_robot[4],
       self.rototraslazione_post_robot[5],
       self.rototraslazione_post_robot[6],
       self.rototraslazione_post_robot[7]
    ], 
    [  self.rototraslazione_post_robot[8],
       self.rototraslazione_post_robot[9],
       self.rototraslazione_post_robot[10],
       self.rototraslazione_post_robot[11]
    ],
    [  self.rototraslazione_post_robot[12],
       self.rototraslazione_post_robot[13],
       self.rototraslazione_post_robot[14],
       self.rototraslazione_post_robot[15]]
    ])
  matrice_post_setup_inversa = transformations.invert_transform(matrice_postsetup)
  self.static_broadcaster.sendTransform(self.w2o_transform) 
  vettore_quaternion_wxyz = np.array([vettore_quaternion[3], vettore_quaternion[0] , vettore_quaternion[1] , vettore_quaternion[2]]) 
  prova = rotations.matrix_from_quaternion(vettore_quaternion_wxyz) 
  yaw_iniziale = yaw
  x_iniziale = x_robot
  y_iniziale = y_robot
  inizio = False
```
Pubblicazione dei primi messaggi: 
```
messaggio_ir_left.data = self.__sensor_LEFTIR.getValue()
messaggio_ir_right.data = self.__sensor_RIGHTIR.getValue()
self.right_ir_publisher.publish(messaggio_ir_right) #IR RIGHT
messaggio_distanza_middle.range  = self.__sensor_MIDDLE.getValue()
self.middle_distance_publisher.publish(messaggio_distanza_middle) 
```
Conversione da twist a velocità delle ruote:
```
command_motor_left = (forward_speed - angular_speed*HALF_DISTANCE_BETWEEN_WHEELS)/R
command_motor_right = (forward_speed + angular_speed*HALF_DISTANCE_BETWEEN_WHEELS)/R
```

Setup velocità delle ruote: 

```
wl_robot = self.__motor_left.getVelocity()
wr_robot = self.__motor_right.getVelocity()     
self.__motor_left.setVelocity(command_motor_left)
self.__motor_right.setVelocity(command_motor_right)
```
Setup orientamento in quaternioni del robot:
```
coordinate_assolute[0].getSFRotation()[0] #x
coordinate_assolute[0].getSFRotation()[1] #y 
coordinate_assolute[0].getSFRotation()[2] #z 
coordinate_assolute[0].getSFRotation()[3] #w 
```
Dati per l'odometria:
```
phi_robot = yaw - yaw_iniziale
x_robot_final = x_robot - x_iniziale
y_robot_final = y_robot - y_iniziale
```
Pubblicazione misure laser:
```
self.laser_publisher.publish(messaggio_webots_scanner)
```
Errore globale: 
```
global errore_globale
errore = random.uniform(0,0.05) * forward_speed
errore_globale = errore_globale + errore
```
Aggiornamento vettore quaternioni dai dati del sensore IMU:
```
 vettore_quaternion_wxyz = np.array([vettore_quaternion[3], vettore_quaternion[0] , vettore_quaternion[1] , vettore_quaternion[2]]) 
```
Utilizzo delle matrici di rotazione e utilizzo della libreria pytransform3d:
```
roto_now = np.array(
  [
    [ self.__robot.getSelf().getPose()[0],
      self.__robot.getSelf().getPose()[1],
      self.__robot.getSelf().getPose()[2],
      self.__robot.getSelf().getPose()[3]
    ],
    [ self.__robot.getSelf().getPose()[4],
      self.__robot.getSelf().getPose()[5],
      self.__robot.getSelf().getPose()[6],
      self.__robot.getSelf().getPose()[7]
    ],
    [ self.__robot.getSelf().getPose()[8],
      self.__robot.getSelf().getPose()[9],
      self.__robot.getSelf().getPose()[10],
      self.__robot.getSelf().getPose()[11]
    ],
    [ self.__robot.getSelf().getPose()[12],
      self.__robot.getSelf().getPose()[13],
      self.__robot.getSelf().getPose()[14],
      self.__robot.getSelf().getPose()[15]]
    ])

  conversione_roto_now_xq = transformations.pq_from_transform(roto_now)
  matrice_o2r  = transformations.concat(roto_now,matrice_post_setup_inversa)
  conversione_o2r_xq = transformations.pq_from_transform(matrice_o2r)
```
Pubblicazione tramite Broadcaster della Transfrom odom to base_link:
```
self.odom_trasfrom.header.stamp = current_time
self.odom_trasfrom.transform.rotation.w = conversione_o2r_xq[3] 
self.odom_trasfrom.transform.rotation.x = conversione_o2r_xq[4]
self.odom_trasfrom.transform.rotation.y = conversione_o2r_xq[5] 
self.odom_trasfrom.transform.rotation.z = conversione_o2r_xq[6] 
self.odom_trasfrom.transform.translation.x = conversione_o2r_xq[0]  
self.odom_trasfrom.transform.translation.y = conversione_o2r_xq[1] 
self.odom_trasfrom.transform.translation.z = conversione_o2r_xq[2] 
self.broadcaster.sendTransform(self.odom_trasfrom)    
```
Pubblicazione messaggio di Odometria:
```
messaggio_odometria.header.stamp = current_time
messaggio_odometria.header.frame_id = "odom"
messaggio_odometria.child_frame_id = "base_link"
messaggio_odometria.pose.pose.position.x =  x_robot_final 
messaggio_odometria.pose.pose.position.y =  y_robot_final
messaggio_odometria.pose.pose.position.z = 0.0        
messaggio_odometria.pose.pose.orientation.z =  phi_robot#self.imu.getRollPitchYaw()[2]# phi_robot 
messaggio_odometria.twist.twist.linear.x = forward_speed
messaggio_odometria.twist.twist.linear.y = 0.0
messaggio_odometria.twist.twist.angular.z = angular_speed 
self.odometry_publisher.publish(messaggio_odometria)
```
Pubblicazione map to odom Transform:
```
self.static_broadcaster.sendTransform(self.map2odom_transform)
```
## Altre funzioni
Conversione da quaternione ad axis angles:
```
def quaternion_to_axis_angle(quaternion):
    quaternion = quaternion / np.linalg.norm(quaternion)
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
```
