import math

class Complex:
    def __init__(self, x,y):
        self.x = x
        self.y = y
        self.z = complex(x,y)

    def module(self):
        return math.sqrt(pow(self.x,2) + pow(self.y,2))

    def complex_add(self,z1,z2):
        z3_real  = z1.x + z2.x
        z3_imag = z1.y + z2.y
        z3 = complex(z3_real, z3_imag)
        return z3

    def complex_subtract(self,z1,z2):
        z3_real  = z1.x - z2.x
        z3_imag = z1.y - z2.y
        z3 = complex(z3_real, z3_imag)
        return z3


z = Complex(3,4)
w = Complex(5,6)
print(z.module())

print(z.complex_add(w,z))
