import numpy as np

accuracy = 0.00000001

def fun1_x(x):
    return 1 / x

def funx_2(x):
    return pow(x, 2)

def funx_4(x):
    return x + 4

def double_recalc(funFormula, function, termsX, termsY):
    step = termsX[1] - termsX[0]

    while True:
        integral1 = funFormula(step, termsY)

        step /= 2

        termsX = np.arange(termsX[0], termsX[-1] + step, step)
        termsY = [function(num) for num in termsX] # 1 / x

        integral2 = funFormula(step, termsY)

        if verify_exit(integral1, integral2):
            break

    return integral2

def form_trapezoid(step, termsY):
    answer = (termsY[0] + termsY[len(termsY) - 1]) / 2
    for i in range(1, len(termsY) - 1):
        answer += termsY[i]
    answer *= step

    return answer

def form_simpsona(step, termsY):
    answer = termsY[0] + termsY[len(termsY) - 1]
    for i in range(1, len(termsY) - 1):
        if i % 2 == 0:
            answer += 2 * termsY[i]
        else:
            answer += 4 * termsY[i]
    answer *= step / 3

    return answer

def verify_exit(answer_h, answer_h_2):
    if abs(answer_h - answer_h_2) < 3 * accuracy:
        return True
    return False