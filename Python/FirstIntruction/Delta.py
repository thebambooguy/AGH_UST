import math

a, b, c = input('Podaj a,b,c oddzielone spacjami: ').split()
aa = float(a)
bb = float(b)
cc = float(c)
#a = int(input("Enter a number: ")) - w pythonie 3 nie ma funkcji raw_input(), a input() nie rozpoznaje typów danych
delta = bb*bb-4*aa*cc
if(delta < 0):
    print('Brak rzeczywistych rozwiazan rownania')
elif(delta == 0):
    x0 = -bb/(2*aa)
    print('Jest jedno rozwiązanie i x0= {}'.format(x0))
elif(delta > 0):
    x1 = (-bb+math.sqrt(delta))/(2*aa)
    x2 = (-bb-math.sqrt(delta))/(2*aa)
    print('Są dwa rozwiązania i x1= {} a x2= {}'.format(x1,x2))