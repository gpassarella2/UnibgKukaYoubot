class LaserObject:
    def __init__(self):
        pass

    def setup(self,nome, model, range_max, range_min,horizontal_resolution,field_of_view):

        self.nome = nome
        self.model = model
        self.range_max = range_max
        self.range_min = range_min
        self.horizontal_resolution = horizontal_resolution
        self.field_of_view = field_of_view 

        if(self.model == 'URG'):    
            self.angle_min = -(self.field_of_view/2)
            self.angle_max = (self.field_of_view/2)


        elif(self.model == 'SLAMTEC'):
            self.angle_min = 0.0
            self.angle_max = self.field_of_view

        
        else: 
            self.angle_min = -(self.field_of_view/2)
            self.angle_max = (self.field_of_view/2)

        self.angle_increment = (self.field_of_view)/(self.horizontal_resolution -1)
    



