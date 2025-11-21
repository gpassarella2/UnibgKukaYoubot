class RoverInformation:
    def __init__(self):
        self.length = 0.47
        self.width = 0.31
        self.height = 0.085
        self.wheel_radius = 0.0475
        self.l = 0.235
        self.w = 0.158

        self.min_x = self.l
        self.max_x = self.l
        self.min_y = self.w
        self.max_y = self.w
        self.min_z = 0.0
        self.max_z = 0.3
        self.safety_margin = 0.20

        self.min_lin_vel = 0.01
        self.max_lin_vel = 0.8
        self.max_side_vel = 0.8
        self.min_ang_vel = 0.05
        self.max_ang_vel = 1.57

        self.max_lin_acc = 1.5
        self.max_ang_acc = 2.0
        self.max_cen_acc = 1.2

        self.lin_resolution = 0.01
        self.ang_resolution = 0.05

        self.num_wheels = 4
        self.roller_angle = 45.0

    def setup(
        self,
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
        ang_resolution,
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
