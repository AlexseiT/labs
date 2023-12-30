class Number(object):
    def __init__(self, coef = 0, degreeX = 0):
        self.coef = coef
        self.degreeX = degreeX

    def substitution_x(self, x):
        return pow(x, self.degreeX)

