using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUniver
{
    public class DifferentiationDoubleRecalc
    {
        static public double[] RungeKutt(ElemFun[] equation, List<double> termsX, double y0, double accuracy)
        {
            double step = termsX[1] - termsX[0];

            double[][] termsY = new double[2][];

            int countOperation = 0;
            while (true)
            {
                countOperation++;
                termsY[0] = new double[termsX.Count];
                termsY[1] = new double[termsX.Count];
                termsY[0][0] = y0;
                termsY[1][0] = y0;

                for (int i = 1; i < termsY[0].Length; i++)
                {
                    termsY[0][i] = CalculationY(equation, step, termsX[i - 1], termsY[0][i - 1]);
                }

                step /= 2;

                double a = termsX[0];
                double b = termsX[termsX.Count - 1];
                termsX.Clear();

                for (double i = a; i < b; i += step)
                {
                    termsX.Add(i);
                }

                for (int i = 1; i < termsY[1].Length; i++)
                {
                    termsY[1][i] = CalculationY(equation, step, termsX[i - 1], termsY[1][i - 1]);
                }

                if (VerifyToExit(termsY, accuracy))
                    break;
            }

            if (countOperation == 1)
                return termsY[0];
            else
                return termsY[1];
        }

        static private bool VerifyToExit(double[][] termsY, double accuracy)
        {
            for (int i = 0; i < termsY.Length - 1; i++)
            {
                if (Math.Abs(termsY[0][i] - termsY[1][i + 1]) > 15 * accuracy)
                {
                    return false;
                }
            }

            return true;
        }

        static public double CalculationY(ElemFun[] equation, double step, double x, double y)
        {
            double[] C = new double[4];

            C[0] = SubstitutionEquation(equation, x, y);
            C[1] = SubstitutionEquation(equation, x + step / 2, y + step * C[0] / 2);
            C[2] = SubstitutionEquation(equation, x + step / 2, y + step * C[1] / 2);
            C[3] = SubstitutionEquation(equation, x + step, y + step * C[2]);

            return y + step / 6 * (C[0] + 2 * C[1] + 2 * C[2] + C[3]);
        }

        static private double SubstitutionEquation(ElemFun[] equation, double x, double y)
        {
            double answer = 0;

            for (int i = 0; i < equation.Length; i++)
            {
                answer += equation[i].SubstitutionTermsXY(x, y);
            }

            return answer;
        }
    }
}
