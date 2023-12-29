using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace CurseWorkVichMat
{
    internal class Differential_Equation
    {
        double X0;
        double Y0;
        double Xn;
        double Yn;
        double a;
        double b;
        double h;
        List<double> result = new List<double>();
        double E;
        public Differential_Equation(double X0, double Y0, double Xn, double Yn, double a, double b, double h, double E) 
        {
            this.X0 = X0;
            this.Y0 = Y0;
            this.Xn = Xn;
            this.Yn = Yn;
            this.a = a;
            this.b = b;
            this.h = h;
            this.E = E;
        }
        public double F1(double X, double Y, double dY)
        {
            return (Math.Exp(X) + Y + dY)/3;
        }
        public double F(double X, double Y, double dY) 
        {
            return Math.Cos(3*X) - 4*Y;
        }
        public double G(double X, double Y, double dY)
        {
            return dY;
        }
        public double[] Runge_Cutt(double X, double Y, double dY)
        {
            double ResultK = dY;
            double ResultQ = Y;

            double K1 = h * F(X, Y, dY);
            double Q1 = h * G(X, Y, dY);

            double K2 = h * F(X + h / 2, Y + Q1 / 2, dY + K1 / 2);
            double Q2 = h * G(X + h / 2, Y + Q1 / 2, dY + K1 / 2);

            double K3 = h * F(X + h / 2, Y + Q2 / 2, dY + K2 / 2);
            double Q3 = h * G(X + h / 2, Y + Q2 / 2, dY + K2 / 2);

            double K4 = h * F(X + h, Y + Q3, dY + K3);
            double Q4 = h * G(X + h, Y + Q3, dY + K3);

            ResultK += (K1 + 2 * K2 + 2 * K3 + K4) / 6;
            ResultQ += (Q1 + 2 * Q2 + 2 * Q3 + Q4) / 6;

            double[] result = { ResultK, ResultQ };
            return result;
        }

        public double[] Solution_Equation(double[] Y0)
        {
            this.result.Clear();

            double Xi = 0;
            double Temp = 0;
            double Y = Y0[0];
            double dY = Y0[1];
            int counter = 0;

            while (Temp < Xn)
            {
                double[] result = Runge_Cutt(Temp, Y, dY);
                Temp += h;
                dY = result[0];
                Y = result[1];
                this.result.Add(Temp);
                this.result.Add(Y);
                this.result.Add(dY);
            }

            double Diff = 100;
            while (Diff > 15 * E)
            {
                h = h / 2;
                Temp = 0;
                this.result.Clear();
                Y = Y0[0];
                dY = Y0[1];
                while (Temp < Xn)
                {
                    double[] result = Runge_Cutt(Temp, Y, dY);
                    Temp += h;
                    dY = result[0];
                    Y = result[1];
                    this.result.Add(Temp);
                    this.result.Add(Y);
                    this.result.Add(dY);
                }
                counter++;
                Diff = this.result[this.result.Count - 1] - this.result[this.result.Count - 4];
            }
           // Console.WriteLine("Iteration =", counter);
            h = 0.05;
            double[] Result_Y_dY = {Y, dY};
            return Result_Y_dY;
        }

        public void Print()
        {
            double[] dataX = new double[] { 1, 2, 3, 4, 5 };
            double[] dataY = new double[] { 1, 4, 9, 16, 25 };
            formsPlot1.Plot.AddScatter(dataX, dataY);
            formsPlot1.Refresh();

            for (int i = 0; i < result.Count; i++) 
            {
                Console.Write(result[i]);
                Console.Write("    ");
                if ((i + 1) % 3 == 0)
                {
                    Console.WriteLine();
                }
            }
        }
        public void Calculate()
        {
            double[] Y0 = { this.Y0, a };
            double Ya = Solution_Equation(Y0)[0];
            Y0[0] = this.Y0;
            Y0[1] = b;
            double Yb = Solution_Equation(Y0)[0];
            double Temp;
            while (Math.Abs(Yb - Ya) > E)
            {
                Temp = (b + a) / 2;
                Y0[0] = this.Y0;
                Y0[1] = Temp;
                double TempY = Solution_Equation(Y0)[0];
                if (Yn - TempY < 0)
                {
                    b = Temp;
                    Yb = TempY;
                }
                else
                {
                    a = Temp;
                    Ya = TempY;
                }
                Print();
            }
        }
    }
}
