class ClassMarker:
    def __init__(self):
        print()

    def setup(self,nome, model,translation,rotation,matrix_rototra, matrix_rototra_inv):

        self.nome = nome
        self.model = model
        self.translation = translation
        self.rotation = rotation
        self.matrix_rototra =  matrix_rototra
        self.matrix_rototra_inv = matrix_rototra_inv


