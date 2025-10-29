class RoverInformation:

    # Parametri Standard della cinematica del Robot 
    def __init__(self):
        self.min_x = 0.35 #[m]
        self.max_x = 0.35 #[m]
        self.min_y = 0.35 #[m]
        self.max_y = 0.35 #[m]
        self.min_z = 0.0 #[m]
        self.max_z = 0.5 #[m]
        self.safety_margin = 0.5    #[m]
        self.min_lin_vel = 0.05      #[m/s]
        self.max_lin_vel = 0.1      #[m/s]  
        self.min_ang_vel = 0.05     #[rad/s]
        self.max_ang_vel = 0.21     #[rad/s]
        self.max_lin_acc = 3.2      #[m/s2]
        self.max_ang_acc = 2.5      #[rad/s2]
        self.max_cen_acc = 3.0      #[m/s2]
        self.lin_resolution = 0.10  #[m]
        self.ang_resolution = 0.15  #[rad]

    # Nel caso in cui si trovino altri parametri 
    def setup(  self,
                min_x,
                max_x,
                min_y,
                max_y,
                min_z,
                max_z,
                safety_margin,
                min_lin_vel,
                max_lin_vel,
                min_ang_vel,
                max_ang_vel,
                max_lin_acc,
                max_ang_acc,
                max_cen_acc,
                lin_resolution,
                ang_resolution
                  ):
        self.min_x = min_x
        self.max_x = max_x
        self.min_y = min_y
        self.max_y = max_y
        self.min_z = min_z 
        self.max_z = max_z
        self.safety_margin = safety_margin
        self.min_lin_vel = min_lin_vel
        self.max_lin_vel = max_lin_vel 
        self.min_ang_vel = min_ang_vel
        self.max_ang_vel = max_ang_vel
        self.max_lin_acc = max_lin_acc   
        self.max_ang_acc = max_ang_acc   
        self.max_cen_acc = max_cen_acc
        self.lin_resolution = lin_resolution
        self.ang_resolution = ang_resolution
        
