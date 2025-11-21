class ClassObject:
    def __init__(self):
        print()

    def setup(self,nome, model,type,size_x,size_y,size_z,translation,rotation,matrix_rototra, matrix_rototra_inv):

        self.nome = nome
        self.model = model
        self.type = type
        self.translation = translation
        self.size_x = size_x
        self.size_y = size_y
        self.size_z = size_z
        self.rotation = rotation
        self.matrix_rototra =  matrix_rototra
        self.matrix_rototra_inv = matrix_rototra_inv


