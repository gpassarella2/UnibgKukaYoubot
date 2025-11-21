import rclpy

import math
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Illuminance

import numpy as np

# PER OTTENERE LE ROTO-TRASLAZIONI 
from pyquaternion import Quaternion  
from pytransform3d import transformations,rotations


TIME_STEP = 32 # milliseconds

BODY_PARTS_NUMBER = 13
WALK_SEQUENCES_NUMBER = 8
ROOT_HEIGHT = 1.27
CYCLE_TO_DISTANCE_RATIO = 0.05


class Pedestrian:
        
    def init(self, webots_node, properties): 
        
        rclpy.init(args=None)
                
        self.__robot = webots_node.robot

        self.__node = rclpy.create_node('human_driver')
        self.__node.get_logger().info('     Human is supervisor? ' + str(self.__robot.getSupervisor()))
        
        self.contenuto = dir(webots_node.robot)
        
        self.root_children_field = webots_node.robot.getRoot().getField('children')
        self.n =  self.root_children_field.getCount()
        

        # Initial values for instance variables
        self.speed = 0.5
        self.current_height_offset = 0
        self.speed_x = 0.0
        self.speed_old_x = 0.0
        self.speed_old_y = 0.0
        self.speed_old_angular = 0.0
        self.speed_angular = 0.0
        self.angle = 0.0
        self.fermo = True
        self.rotazione = False
        self.point_list = ["12.4 6", "12.4 6.2"]
        self.tempo = 0.0


        #   VARIABILE PER CONTROLLARE LA LUCE AMBIENTALE
        
        self.illuminazione = 14.0       # VALORE DI ILLUMINAZIONE 
    

        # questi coefficienti sono coefficienti empirici che risultano in un'andatura realistica
        self.height_offsets = [-0.02, 0.04, 0.08, -0.03, -0.02, 0.04, 0.08, -0.03]

        self.angles = [
                    [-0.52, -0.15, 0.58, 0.7, 0.52, 0.17, -0.36, -0.74],    # 0     left arm
                    [0.0, -0.16, -0.7, -0.38, -0.47, -0.3, -0.58, -0.21],   # 1     left lower arm
                    [0.12, 0.0, 0.12, 0.2, 0.0, -0.17, -0.25, 0.0],         # 2     left hand
                    
                    [0.52, 0.17, -0.36, -0.74, -0.52, -0.15, 0.58, 0.7],    # 3     right arm
                    [-0.47, -0.3, -0.58, -0.21, 0.0, -0.16, -0.7, -0.38],   # 4     right lower arm
                    [0.0, -0.005, -0.05, 0.0, 0.05, 0.0, 0.05, 0.005],         # 5     right hand


                    [-0.52, -0.52, -0.52, -0.52, -0.52, 0.12, 0.24, 0.4],    # 6     left leg
                    [0.05, 0.05, 0.05, 0.05, 0.05, 0.0, 0.05, 0.05],         # 7     left lower leg
                    [0.05, 0.05, -0.05, -0.05, 0.0, 0.0, 0.05, -0.05],      # 8     left foot


                    [-0.52, 0.12, 0.24, 0.4, -0.52, -0.52, -0.52, -0.7],    # 9     right leg
                    [0.05, 0.0, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05],         # 10    right lower leg
                    [0.0, 0.0, 0.005, -0.05, 0.05, 0.05, -0.05, -0.05],      # 11    right foot

                    [0.18, 0.09, 0.0, 0.09, 0.18, 0.09, 0.0, 0.09]          # 12    head
                ]

        self.joint_rotation_objects = []
        self.joint_translation_objects = []
        self.joint_name_objects = []
        self.human_xyz = []

        #   HUMAN

        self.speed_x = 0.0
        self.speed_angular = 0.0
        self.delta_t = 0.0
        self.timestep = 0.0
        self.position_x = 0.0
        self.position_y = 0.0
        self.position_theta = 0.0

        #   OBJECT

        self.speed_object_x = 0.0
        self.speed_object_angular = 0.0
        self.object_xyz = [] 
        self.position_object_x = 0.0
        self.position_object_y = 0.0
        self.position_object_theta = 0.0

        for k in range(self.n):
            
            nodo_livello_1 = self.root_children_field.getMFNode(k)
            self.__node.get_logger().info(str(nodo_livello_1.getTypeName())+ '  ' + str(k))
            
            if(nodo_livello_1.getTypeName() == 'Robot'):    # CERCO IL TIPO NODO ROBOT DENTRO LA GRAFICA DI WEBOTS 
                
                uomo_name = nodo_livello_1.getField('name')

                if(uomo_name.getSFString() == 'human_1'):   # TROVO NODO DI TIPO ROBOT --> UMANO
                    children_1 = nodo_livello_1.getField('children') # CERCO IL FIELD CHILDENTRO IN ROBOT
                    count_children_1 = children_1.getCount()
                    rotation_human = nodo_livello_1.getField('rotation')
                    translation_human = nodo_livello_1.getField('translation')
                    self.human_xyz.append(rotation_human)
                    self.human_xyz.append(translation_human)
                                                            
                    for l in range(count_children_1):                 # ITERO I NODI WEBOTS DI CHILDREN 

                        nodo_livello_2 = children_1.getMFNode(l) #

                        self.__node.get_logger().info( 'nodo_l : ' + str(nodo_livello_2.getTypeName()))
                        
                        if(nodo_livello_2.getTypeName() == 'Solid'):    # Cerco il nodo di tipo SOLID, che ha dentro un'altro CHILDREN 
                
                            children_2 = nodo_livello_2.getField('children')
                            count_children_2 = children_2.getCount()

                            for z in range(count_children_2):          # ITERO I NODI NEL SECONDO CHILDREN 
                                
                                nodo_livello_3 = children_2.getMFNode(z)

                                if(nodo_livello_3.getTypeName() == 'Solid'):    # ogni Solid in questo livello coincide un giunto che posso pilotare
                                    
                                    if(nodo_livello_3.getField('name').getSFString() == 'left arm'):    # LEFT_UPPER_ARM

                                        rotation_left_upper_arm = nodo_livello_3.getField('rotation')
                                        translation_left_upper_arm = nodo_livello_3.getField('translation')
                                        children_left_arm =  nodo_livello_3.getField('children')
                                        count_children_left_arm = children_left_arm.getCount()
                                        self.joint_rotation_objects.append(rotation_left_upper_arm)   # elemento 1
                                        self.joint_translation_objects.append(translation_left_upper_arm)
                                        self.joint_name_objects.append(nodo_livello_3.getField('name'))

                                        
                                        for x in range(count_children_left_arm):
                                            
                                            nodo_livello_4 = children_left_arm.getMFNode(x)

                                            if(nodo_livello_4.getTypeName() == 'Solid'):    # LEFT_LOWER_ARM
                                            
                                                # Qui sono dentro LEFT_LOWER_ARM
                                                rotation_left_arm = nodo_livello_4.getField('rotation')
                                                translation_left_arm = nodo_livello_4.getField('translation')
                                                children_left_hand =  nodo_livello_4.getField('children')  # LEFT_LOWER_ARM HA UN ALTRO CHILDREN 
                                                count_children_left_hand = children_left_hand.getCount()
                                                self.joint_rotation_objects.append(rotation_left_arm)    # elemento 2
                                                self.joint_translation_objects.append(translation_left_arm)
                                                self.joint_name_objects.append(nodo_livello_4.getField('name'))


                                                
                                                for c in range(count_children_left_hand):
                                                        nodo_livello_5 = children_left_hand.getMFNode(c)

                                                        if(nodo_livello_5.getTypeName() == 'Solid'):        # SO
                                                            rotation_left_hand = nodo_livello_5.getField('rotation')
                                                            translation_left_hand = nodo_livello_5.getField('translation')
                                                            self.joint_rotation_objects.append(rotation_left_hand)   # elemento 3
                                                            self.joint_translation_objects.append(translation_left_hand)
                                                            self.joint_name_objects.append(nodo_livello_5.getField('name'))

                                        
                                    elif(nodo_livello_3.getField('name').getSFString() == 'right arm'):

                                        # Qui sono dentro RIGHT_UPPER_ARM
                                        rotation_right_upper_arm = nodo_livello_3.getField('rotation')
                                        translation_right_upper_arm = nodo_livello_3.getField('translation')
                                        children_right_arm =  nodo_livello_3.getField('children')
                                        count_children_right_arm = children_right_arm.getCount()
                                        self.joint_rotation_objects.append(rotation_right_upper_arm)  # elemento 4
                                        self.joint_translation_objects.append(translation_right_upper_arm)
                                        self.joint_name_objects.append(nodo_livello_3.getField('name'))

                                        for x in range(count_children_right_arm):
                                            
                                            nodo_livello_4 = children_right_arm .getMFNode(x)

                                            if(nodo_livello_4.getTypeName() == 'Solid'):    # Cerco il nodo Solid in base al nome
                                                                
                                                # Qui sono dentro RIGHT_LOWER_ARM
                                                rotation_right_arm = nodo_livello_4.getField('rotation')
                                                translation_right_arm = nodo_livello_4.getField('translation')
                                                children_right_hand =  nodo_livello_4.getField('children')
                                                count_children_right_hand = children_right_hand.getCount()
                                                self.joint_rotation_objects.append(rotation_right_arm)   # elemento 5
                                                self.joint_translation_objects.append(translation_right_arm)
                                                self.joint_name_objects.append(nodo_livello_4.getField('name'))


                                                
                                                for c in range(count_children_right_hand):
                                                        
                                                        nodo_livello_5 = children_right_hand.getMFNode(c)

                                                        if(nodo_livello_5.getTypeName() == 'Solid'):
                                                            rotation_right_hand = nodo_livello_5.getField('rotation')
                                                            translation_right_hand = nodo_livello_5.getField('translation')
                                                            self.joint_rotation_objects.append(rotation_right_hand)  # elemento 6
                                                            self.joint_translation_objects.append(translation_right_hand)
                                                            self.joint_name_objects.append(nodo_livello_5.getField('name'))

                                        
                                    elif(nodo_livello_3.getField('name').getSFString() == 'left leg'):
                                        # Qui sono dentro LEFT_UPPER_LEG
                                        
                                        rotation_left_upper_leg = nodo_livello_3.getField('rotation')
                                        translation_left_upper_leg = nodo_livello_3.getField('translation')
                                        children_left_leg =  nodo_livello_3.getField('children')
                                        count_children_left_leg= children_left_leg.getCount()
                                        self.joint_rotation_objects.append(rotation_left_upper_leg)   # elemento 7
                                        self.joint_translation_objects.append(translation_left_upper_leg) 
                                        self.joint_name_objects.append(nodo_livello_3.getField('name'))
                                        
                                        for x in range(count_children_left_leg):
                                            
                                            nodo_livello_4 = children_left_leg.getMFNode(x)

                                            if(nodo_livello_4.getTypeName() == 'Solid'):    # Cerco il nodo Solid in base al nome
                                                # Qui sono dentro LEFT_LOWER_LEG
                                                rotation_left_leg = nodo_livello_4.getField('rotation')
                                                translation_left_leg = nodo_livello_4.getField('translation')
                                                children_left_foot =  nodo_livello_4.getField('children')
                                                count_children_left_foot = children_left_foot.getCount()
                                                self.joint_rotation_objects.append(rotation_left_leg)    # elemento 8  
                                                self.joint_translation_objects.append(translation_left_leg )
                                                self.joint_name_objects.append(nodo_livello_4.getField('name'))

                                                
                                                for c in range(count_children_left_foot):
                                                        nodo_livello_5 = children_left_foot.getMFNode(c)

                                                        if(nodo_livello_5.getTypeName() == 'Solid'):
                                                            
                                                            rotation_left_foot = nodo_livello_5.getField('rotation')
                                                            translation_left_foot = nodo_livello_5.getField('translation')
                                                            self.joint_rotation_objects.append(rotation_left_foot)   # elemento 9
                                                            self.joint_translation_objects.append(translation_left_foot) 
                                                            self.joint_name_objects.append(nodo_livello_5.getField('name'))



                                        
                                    elif(nodo_livello_3.getField('name').getSFString() == 'right leg'):

                                        # Qui sono dentro RIGHT_UPPER_LEG
                                        rotation_right_upper_leg = nodo_livello_3.getField('rotation')
                                        translation_right_upper_leg = nodo_livello_3.getField('translation')
                                        children_right_leg =  nodo_livello_3.getField('children')
                                        count_children_right_leg= children_right_leg.getCount()
                                        self.joint_rotation_objects.append(rotation_right_upper_leg)  # elemento 10
                                        self.joint_translation_objects.append(translation_right_upper_leg)
                                        self.joint_name_objects.append(nodo_livello_3.getField('name'))


                                        
                                        for x in range(count_children_right_leg):
                                            
                                            nodo_livello_4 = children_right_leg.getMFNode(x)

                                            if(nodo_livello_4.getTypeName() == 'Solid'):    # Cerco il nodo Solid in base al nome

                                                # Qui sono dentro RIGHT_LOWER_LEG
                                                rotation_right_leg = nodo_livello_4.getField('rotation')
                                                translation_right_leg = nodo_livello_4.getField('translation')
                                                children_right_foot =  nodo_livello_4.getField('children')
                                                count_children_right_foot = children_right_foot.getCount()
                                                self.joint_rotation_objects.append(rotation_right_leg)   # elemento 11
                                                self.joint_translation_objects.append(translation_right_leg)
                                                self.joint_name_objects.append(nodo_livello_4.getField('name'))

                                                
                                                for c in range(count_children_right_foot):
                                                        nodo_livello_5 = children_right_foot.getMFNode(c)

                                                        if(nodo_livello_5.getTypeName() == 'Solid'):
                                                            
                                                            rotation_right_foot = nodo_livello_5.getField('rotation')
                                                            translation_right_foot = nodo_livello_5.getField('translation')
                                                            self.joint_rotation_objects.append(rotation_right_foot)  # elemento 12
                                                            self.joint_translation_objects.append(translation_right_foot)
                                                            self.joint_name_objects.append(nodo_livello_5.getField('name'))

                                        
                                    elif(nodo_livello_3.getField('name').getSFString() == 'head'):
                                        
                                        rotation_head =  nodo_livello_3.getField('rotation')
                                        translation_head =  nodo_livello_3.getField('translation')
                                        
                                        # self.__node.get_logger().info('trovato rotation in head: ' + str(rotation_head.getSFRotation()))
                                        # self.__node.get_logger().info('trovato translation in head: ' + str(translation_head.getSFVec3f()))
                                        
                                        self.joint_rotation_objects.append(rotation_head)    # elemento 13
                                        self.joint_translation_objects.append(translation_head)
                                        self.joint_name_objects.append(nodo_livello_3.getField('name'))
        

                if(uomo_name.getSFString() == 'object_1'):
                # QUI POSSO FARE UN CHECK SE E' UN PEDESTRIAN OPPURE UN OBJECT 
                    rotation_object = nodo_livello_1.getField('rotation')
                    translation_object = nodo_livello_1.getField('translation')
        
                    self.object_xyz.append(rotation_object)
                    self.object_xyz.append(translation_object)

            #   QUI CERCO I POINTLIGHT IN SIMULAZIONE 

            if(nodo_livello_1.getTypeName() == 'PointLight'):    # CERCO IL NODO PointLight in base al nome 

                self.__node.get_logger().info('trovato PointLight dentro webots ')
                light_position = nodo_livello_1.getField('intensity')
                light_position.setSFFloat(self.illuminazione)
                self.__node.get_logger().info('settata la luce ad illuminazione: ' + str(self.illuminazione))

                # Faccio un check sull'illuminazione 

        # PRINT DI CONTROLLO 

        self.__node.get_logger().info('rotazione object: ' + str(self.object_xyz[0].getSFRotation()))
        self.__node.get_logger().info('traslazione object: ' + str(self.object_xyz[1].getSFVec3f()))

        self.position_object_theta = self.object_xyz[0].getSFRotation()[3]
        self.position_object_x = self.object_xyz[1].getSFVec3f()[0]
        self.position_object_y = self.object_xyz[1].getSFVec3f()[1]
        self.position_object_z = self.object_xyz[1].getSFVec3f()[2]

        self.__node.get_logger().info('position_object_theta: ' + str( self.position_object_theta))
        self.__node.get_logger().info('position_object_x: ' + str( self.position_object_x))
        self.__node.get_logger().info('position_object_y: ' + str( self.position_object_y))
 

    #           -------------------------- Fino a qua ho solo preso i giunti di interesse per muovere l'uomo in simulazione ------------------------------


        self.__node.get_logger().info('Inizio print del vettore joint_rotation_objects ')
            
        for indice in range(0,BODY_PARTS_NUMBER):
            self.__node.get_logger().info( '[' + str(indice) +'] ' + str(self.joint_name_objects[indice].getSFString() + '    '+ str(self.joint_rotation_objects[indice].getSFRotation())))

        # NUOVA MODIFICA 
        self.__node.create_subscription(Twist,'human_twist',self.__cmd_vel_callback,1)
        
        self.__node.create_subscription(Twist,'object_twist',self.__cmd_vel_object_callback,1)

        self.__node.create_subscription(Illuminance,'illuminazione',self.__illuminance_callback,1)


    # TWIST CALLBACK 
    def __cmd_vel_callback(self,twist): # Idea cambiare i valori ad ogni chiamata di questa funzione
        
        self.speed_x = twist.linear.x
        self.speed_angular = twist.angular.z
        
        if(self.speed_x == 0.0 and self.speed_angular == 0.0):  
            self.fermo = True  
            self.rotazione = False

        elif(self.speed_x == 0.0 and self.speed_angular != 0.0):
            self.rotazione = True  
            self.fermo = False  
        
        else:
            self.fermo = False
            self.rotazione = False  

    def __cmd_vel_object_callback(self,twist): # Idea cambiare i valori ad ogni chiamata di questa funzione

        self.speed_object_x = twist.linear.x
        self.speed_object_angular = twist.angular.z

    def __illuminance_callback(self,illuminazione):
        
        print('sei dentro la callback di illuminazione')

        #illuminazione.illuminance  --> double 
        #illuminazione.variance --> double  per non non lo utilizzo 
        self.illuminazione = illuminazione.illuminance
        self.__node.get_logger().info('Nuovo valore di illuminazione:' + str(self.illuminazione))

        for k in range(self.n):
            
            nodo_livello_1 = self.root_children_field.getMFNode(k)
                    
            if(nodo_livello_1.getTypeName() == 'PointLight'):  # Cerco il nodo PointLihgt in base al nome
                
                self.__node.get_logger().info('trovato PointLight alla posizione  '+ str(k))
                light_position = nodo_livello_1.getField('intensity')
                light_position.setSFFloat(self.illuminazione)
                self.__node.get_logger().info('settata la luce a: ' + str(self.illuminazione))


    def step(self):       
        
        global  speed, current_height_offset

        rclpy.spin_once(self.__node, timeout_sec=0)
        
        self.delta_t = self.__robot.getTime()                                                       # TEMPO DI SIMULAZIONE  
        self.timestep = int(self.__robot.getBasicTimeStep())    

        # TRATTO UMANO COME UN ROBOT:   

        delta_orientation = self.speed_angular*(self.timestep/1000)                                 # CALCOLO ORIENTAMENTO RICHIESTO
        delta_position = self.speed_x*(self.timestep/1000)                                          # CALCOLO SPOSTAMENTO RICHIESTO
        aa_delta = [0,0,1, delta_orientation]                                                       # COSTRUZIO AXIS_ANGLE GOAL
        #   x,y,z   
        translation_delta = [delta_position,0,0]                                                    # COSTRUZIONE VETTORE TRASLAZIONE DELTA 
        R_robot_delta = rotations.matrix_from_axis_angle(aa_delta)                                  # COSTRUTZIONE MATRICE DI ROTAZIONE DELTA 
        M_robot_delta = matrix_from_axis_translation(R_robot_delta,translation_delta )              # COSTRUZIONE DELLA MATRICE DI ROTO-TRASLAZIONE DELTA 

        M_robot = build_matrix(self.__robot.getSelf().getPose())                                    # MATRICE ROTO-TRASLAZIONE ROBOT RISPETTO A SISTEMA DI RIFERIMENTO WORLD 
        M_robot_goal = transformations.concat(M_robot_delta,M_robot)                                # MATRICE DI ROTO-TRASLAZIONE GOAL
        R_robot_goal =    axis_translation_from_matrix(M_robot_goal)                                # MATRICE DI ROTAZIONE GOAL
        aa_robot_goal = rotations.axis_angle_from_matrix(R_robot_goal)                              # AXIS_ANGLE GOAL 

        aa_robot_goal_clean = [aa_robot_goal[0], aa_robot_goal[1], aa_robot_goal[2], aa_robot_goal[3]]
        translation_robot_goal = [M_robot_goal[0][3],M_robot_goal[1][3],M_robot_goal[2][3]]

        self.human_xyz[1].setSFVec3f(translation_robot_goal)                                        # SET TRANSLATION
        self.human_xyz[0].setSFRotation(aa_robot_goal_clean)                                        # SET ROTATION 


        if(self.fermo == False):
            current_sequence = int(((self.delta_t * self.speed_x) / CYCLE_TO_DISTANCE_RATIO) % WALK_SEQUENCES_NUMBER)
            ratio = (self.delta_t * self.speed_x) / CYCLE_TO_DISTANCE_RATIO - int(((self.delta_t * self.speed_x) / CYCLE_TO_DISTANCE_RATIO))

            for i in range(0,BODY_PARTS_NUMBER):
                    
                current_angle = self.angles[i][current_sequence] * (1 - ratio) + \
                self.angles[i][(current_sequence + 1) % WALK_SEQUENCES_NUMBER] * ratio
                rotazione_i = [0, 1, 0, current_angle] # rotazione intorno all'asse y 
                self.joint_rotation_objects[i].setSFRotation(rotazione_i)

        if(self.rotazione == True):
            
            for i in range(0,BODY_PARTS_NUMBER):
                rotation = [0, 1, 0, 0]
                self.joint_rotation_objects[i].setSFRotation(rotation)

        # TRATTO OBJECT COME UN ROBOT:   


        delta_object_orientation = self.speed_object_angular*(self.timestep/1000)                                 # CALCOLO ORIENTAMENTO RICHIESTO
        delta_object_position = self.speed_object_x*(self.timestep/1000)                                          # CALCOLO SPOSTAMENTO RICHIESTO
        aa_object_delta = [0,0,1, delta_object_orientation]                                                       # COSTRUZIO AXIS_ANGLE GOAL
        #   x,y,z   
        translation_object_delta = [delta_object_position,0,0]                                                    # COSTRUZIONE VETTORE TRASLAZIONE DELTA 
        R_object_delta = rotations.matrix_from_axis_angle(aa_object_delta)                                  # COSTRUTZIONE MATRICE DI ROTAZIONE DELTA 
        M_object_delta = matrix_from_axis_translation(R_object_delta,translation_object_delta )              # COSTRUZIONE DELLA MATRICE DI ROTO-TRASLAZIONE DELTA 
        
        #   self.object_xyz.append(rotation_object)
        #   self.object_xyz.append(translation_object)
        aa_object = [   self.object_xyz[0].getSFRotation()[0],
                        self.object_xyz[0].getSFRotation()[1],
                        self.object_xyz[0].getSFRotation()[2],
                        self.object_xyz[0].getSFRotation()[3]]
        R_object = rotations.matrix_from_axis_angle(aa_object)                                  # COSTRUTZIONE MATRICE DI ROTAZIONE DELTA 
        M_object= matrix_from_axis_translation(R_object, self.object_xyz[1].getSFVec3f())                     # COSTRUZIONE DELLA MATRICE DI ROTO-TRASLAZIONE DELTA 

        
        # M_object = build_matrix(self.__robot.getSelf().getPose())                                    # MATRICE ROTO-TRASLAZIONE ROBOT RISPETTO A SISTEMA DI RIFERIMENTO WORLD 
        M_object_goal = transformations.concat(M_object_delta,M_object)                                # MATRICE DI ROTO-TRASLAZIONE GOAL
        R_object_goal =    axis_translation_from_matrix(M_object_goal)                                # MATRICE DI ROTAZIONE GOAL
        aa_object_goal = rotations.axis_angle_from_matrix(R_object_goal)                              # AXIS_ANGLE GOAL 

        aa_object_goal_clean = [aa_object_goal[0], aa_object_goal[1], aa_object_goal[2], aa_object_goal[3]]
        translation_object_goal = [M_object_goal[0][3],M_object_goal[1][3],M_object_goal[2][3]]


        self.object_xyz[1].setSFVec3f(translation_object_goal)                                        # SET TRANSLATION
        self.object_xyz[0].setSFRotation(aa_object_goal_clean)      




# DA UN VETTORE 1X16, COSTRUISCE UNA MATRICE 4X4
def build_matrix(vettore_matrice):
    
    matrice = np.array(
        [[vettore_matrice[0], vettore_matrice[1], vettore_matrice[2], vettore_matrice[3]],
        [vettore_matrice[4], vettore_matrice[5], vettore_matrice[6], vettore_matrice[7]],
        [vettore_matrice[8], vettore_matrice[9], vettore_matrice[10], vettore_matrice[11]],
        [vettore_matrice[12],vettore_matrice[13],vettore_matrice[14],vettore_matrice[15]]
        ])
    return matrice

# COSTRUISCE LA MATRICE DI ROTO-TRASLAZIONE DATA LA MATRICE DI ROTAZIONE ED IL VETTORE DI TRASLAZIONE 
def matrix_from_axis_translation(matrice_rotazione, traslazione):
    
    matrice = np.array(
        [
        [matrice_rotazione[0][0], matrice_rotazione[0][1], matrice_rotazione[0][2], traslazione[0]],
        [matrice_rotazione[1][0], matrice_rotazione[1][1], matrice_rotazione[1][2], traslazione[1] ],
        [matrice_rotazione[2][0], matrice_rotazione[2][1], matrice_rotazione[2][2], traslazione[2]],
        [0.0, 0.0, 0.0, 1.0]
        ])
    return matrice

# COSTRUISCE LA MATRICE DI ROTAZIONE 3X3 DA UNA MATRICE DI ROTO-TRASLAZIONE 4X4
def axis_translation_from_matrix(matrice_rotazione):
    
    matrice = np.array(
        [
        [matrice_rotazione[0][0], matrice_rotazione[0][1], matrice_rotazione[0][2]],
        [matrice_rotazione[1][0], matrice_rotazione[1][1], matrice_rotazione[1][2]],
        [matrice_rotazione[2][0], matrice_rotazione[2][1], matrice_rotazione[2][2]]
        ]
    )
    return matrice