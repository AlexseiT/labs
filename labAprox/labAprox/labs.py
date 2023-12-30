import numpy as np
import matplotlib.pyplot as plt

import IntegrationDoubleRecalculation as idr
import Approximation as ap
import GoldSection as gs

def main():
    # Integration with double recalculation

    n = 3

    termsX = [num for num in range(1, n + 1)]
    termsY = [1 / num for num in termsX] # 1 / x

    print('Trazoid 1 / x =', idr.double_recalc(idr.form_trapezoid, idr.fun1_x, termsX, termsY))
    print('Simpson 1 / x =', idr.double_recalc(idr.form_simpsona, idr.fun1_x, termsX, termsY))
    print()

    termsX = [num for num in range(1, n + 1)]
    termsY = [pow(num, 2) for num in termsX] # x ^ 2

    print('Trazoid x^2 =', idr.double_recalc(idr.form_trapezoid, idr.funx_2, termsX, termsY))
    print('Simpson x^2 =', idr.double_recalc(idr.form_simpsona, idr.funx_2, termsX, termsY))
    print()

    termsX = [num for num in range(1, n + 1)]
    termsY = [num + 4 for num in termsX] # x + 4

    print('Trazoid x + 4 =', idr.double_recalc(idr.form_trapezoid, idr.funx_4, termsX, termsY))
    print('Simpson x + 4 =', idr.double_recalc(idr.form_simpsona, idr.funx_4, termsX, termsY))
    print()

    # Approximation

    #termsX = np.array([0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8])
    #termsY = np.array([3.03, 3.142, 3.358, 3.463, 3.772, 3.251, 3.17, 3.665])
    #equation = np.array([0, 1, 2])

    #pointsY = ap.calculation_approximation(equation, termsX, termsY)
    
    #plt.plot(termsX, termsY, 'ro')
    #plt.plot(termsX, pointsY)
    #plt.show()

    # Gold section

    #equation = [ 1, 2, 3, 4, 5 ]
    #accuracy = 0.0001
    #a = 2
    #b = 3

    #for i in range(len(equation)):
    #    print(f'{equation[i]}x^{i} ',end='')
    #    if i < len(equation) - 1:
    #        print('+ ',end='')
    #print('\nMin function:', gs.calculation_min(equation, accuracy, a, b))

def calculation_points(function, termsX, termsY):
    listY = []
    listX = np.arange(termsX[0], termsX[-1], 0.1)

    for x in listX: 
        listY.append(function(x, termsX, termsY))

    plt.plot(listX, listY)
    plt.show()

if __name__ == '__main__':
    main()
