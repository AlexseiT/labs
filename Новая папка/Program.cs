using System;
using _5lab;
using metriclab;

namespace labs // 2 Вариант
{
    public class Program
    {
        

        static void Main(string[] args)
        {

            // 13 lab
            Console.WriteLine("13 lab");
            ProgrammSimulator calculator1 = new ProgrammSimulator();
            calculator1.ProgrammCalc();
            Console.WriteLine();

            // 14 lab
            Console.WriteLine("14 lab");
            MetricCharacteristics calculator2 = new MetricCharacteristics();
            calculator2.ProgrammCalc();
            Console.WriteLine();

            // 15 lab
            Console.WriteLine("15 lab");
            MetricCharacteristicsPS calculator3 = new MetricCharacteristicsPS();
            calculator3.ProgrammCalc();
            Console.WriteLine();

        }


        // lab1 C0
        public static int[] Sum(int[] a, int[] b)
        {
            int[] c = new int [a.Length];
            for(int i  = 0; i < a.Length; i++)
            {
                c[i] = a[i] + b[i];
            }
            return c;
        }
        public static double[] Shift(int parametr, double[] a)
        {
            double[] c = new double[a.Length];
            for (int i = 0; i < a.Length; i++)
            {
                c[i] = a[ (i + parametr) % a.Length ];
            }
            return c;
        }
        public static int FindIndex(int[] seq, int[] vec)
        {
            if (seq.Length > vec.Length) 
                return -1;
            for (int i = 0; i <= vec.Length - seq.Length; i++)
            {
                if (vec[i] == seq[0])
                {
                    int counter = 1;
                    for(int j = 1; j < seq.Length; j++)
                    {
                        if (vec[i + j] == seq[j]) 
                            counter++;
                    }
                    if (counter == seq.Length) 
                        return i;
                } 
            }
            return -1;
        }

        // lab2 C1
        public static int Max(int a, int b)
        {
            if (a >= b) 
                return a;
            return b;
        }
        public static double FindSumValue(double[][] a)
        {
            int maxIndex = a[0].Length;
            double sum = 0;
            //for (int i = 0; i < a.Length; i++)
            //{
            //    if (a[i].Length > maxIndex) maxIndex = a[i].Length;
            //}
            for (int i = 0; i < a.Length; i++)
                for (int j = 0; j < a[i].Length; j++)
                    if (j + i == maxIndex) 
                        sum += a[i][j];
            return sum;
        }
        public static double FindMin(double[][] a)
        {
            double min = a[0][0];
            for (int i = 0; i < a.Length; i++)    
                for (int j = 0; j < a.Length - i; j++) 
                    if (a[i][j] < min) 
                        min = a[i][j];
            return min;
        }

        // lab3 C2
        public static int RankFinder(int a)
        {
            string line = a.ToString();
            int min = int.MaxValue;
            int len = line.Length;
            int minIndex = 0;
            if (len < 2) 
                return 0;
            for (int i = len - 1; i >= 0; i -= 2)
            { 
                if (line[i] < min)
                {
                    min = line[i];
                    minIndex = i;
                }
            }
            return len - minIndex;
        }
        public static int ShiftInt(int a, int b)
        {
            string line = a.ToString();
            if(b < 0)
                b = line.Length - (Math.Abs(b) % line.Length);
            b %= line.Length;
            return int.Parse(line.Substring(b) + line.Substring(0,b)); ;
        }
        public static int InsertInt(int a, int b, int n)
        {
            string line = a.ToString();
            if (line.Length < n 
                || n < 0 
                || b < 0)
                return a;
            return int.Parse(line.Substring(0,n) + b.ToString() + line.Substring(n));
        }
        public static double FindSumValueSecond(double[][] mas)
        {
            double result = 0;
            int n = mas.Length;
            int m = mas[0].Length;
            for (int i = 0; i < n; i++)
            {
                for (int j = m - 1; j > m - 1 - i; j--)
                {
                    if ((int)(mas[i][j]) % 2 == 0)
                        result += mas[i][j];
                }
            }
            return result;
        }
    }
    public class ClassException : Exception
    {
        public ClassException(string str) : base(str) { }
    }
    public class MyMatrix
    {
        private int[,] matrix;
        private int inum { get; set; }
        private int jnum { get; set; }

        public MyMatrix(int i, int j)
        {
            if (i <= 0) throw new ClassException(string.Format("Исключение выход за пределы матрицы {0}", i));
            if (j <= 0) throw new ClassException(string.Format("Исключение выход за пределы матрицы {0}", j));
            inum = i;
            jnum = j;
            matrix = new int[i, j];
        }

        private static int ExceptionBorder(int index, int border)
        {
            if (index < 0 | index > border - 1)
            {
                throw new ClassException(string.Format("Исключение выход за пределы матрицы {0}", index));
                return -1;
            }
            return 0;
        }
        private static int ExceptionDimension(MyMatrix matrixFirst, MyMatrix matrixSecond)
        {
            if (matrixFirst.inum != matrixSecond.inum | matrixFirst.jnum != matrixSecond.jnum)
            {
                throw new ClassException(string.Format("Исключение разная размерность"));
                return -1;
            }
            return 0;
        }

        public int this[int i, int j]
        {
            get
            {
                ExceptionBorder(i, inum);
                ExceptionBorder(j, jnum);
                return matrix[i, j];
            }
            set
            {
                ExceptionBorder(i, inum);
                ExceptionBorder(j, jnum);
                matrix[i, j] = value;
            }
        }
        public static MyMatrix operator +(MyMatrix matrixFirst, MyMatrix matrixSecond)
        {
            ExceptionDimension(matrixFirst, matrixSecond);

            MyMatrix matrixResult = new MyMatrix(matrixFirst.inum, matrixFirst.jnum);
            for (int i = 0; i < matrixFirst.inum; i++)
            {
                for (int j = 0; j < matrixFirst.jnum; j++)
                {
                    matrixResult.matrix[i, j] = matrixFirst.matrix[i, j] + matrixSecond.matrix[i, j];
                }
            }
            return matrixResult;
        }
        public static bool operator ==(MyMatrix matrixFirst, MyMatrix matrixSecond)
        {
            ExceptionDimension(matrixFirst, matrixSecond);
            bool flag = true;
            for (int i = 0; i < matrixFirst.jnum; i++)
            {
                for (int j = 0; j < matrixFirst.jnum; j++)
                {
                    if (matrixFirst.matrix[i, j] != matrixSecond.matrix[i, j])
                    {
                        flag = false;
                        break;
                    }
                }
            }
            return flag;
        }
        public static bool operator !=(MyMatrix matrixFirst, MyMatrix matrixSecond)
        {
            return !(matrixFirst.matrix == matrixSecond.matrix);
        }
        public static MyMatrix operator -(MyMatrix matrixFirst, MyMatrix matrixSecond)
        {
            ExceptionDimension(matrixFirst, matrixSecond);
            MyMatrix c = new MyMatrix(matrixFirst.inum, matrixFirst.jnum);
            for (int i = 0; i < matrixFirst.inum; i++)
            {
                for (int j = 0; j < matrixFirst.jnum; j++)
                {
                    c.matrix[i, j] = matrixFirst.matrix[i, j] - matrixSecond.matrix[i, j];
                }
            }
            return c;
        }
        public static MyMatrix operator *(MyMatrix matrixFirst, MyMatrix matrixSecond)
        {
            ExceptionDimension(matrixFirst, matrixSecond);
            MyMatrix c = new MyMatrix(matrixFirst.inum, matrixFirst.jnum);
            for (int i = 0; i < matrixFirst.inum; i++)
            {
                for (int j = 0; j < matrixSecond.jnum; j++)
                {
                    for (int k = 0; k < matrixFirst.jnum; k++)
                    {
                        c.matrix[i, j] += matrixFirst.matrix[i, k] * matrixSecond.matrix[k, j];
                    }
                }
            }
            return c;
        }
        public MyMatrix Transposition()
        {
            if (inum != jnum) throw new ClassException(string.Format("Исключение не квадратная матрица"));
            int tempValue = 0;
            for (int i = 0; i < inum; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    tempValue = this[i, j];
                    this[i, j] = this[j, i];
                    this[j, i] = tempValue;
                }
            }
            return this;
        }
        public int GetMinElement()
        {
            int minimum = this[0, 0];
            for (int i = 0; i < inum; i++)
            {
                for (int j = 0; j < jnum; j++)
                {
                    if (this[i, j] < minimum)
                    {
                        minimum = this[i, j];
                    }
                }
            }
            return minimum;
        }
        public string GetMatrixString()
        {
            string resultLine = "{";
            string tempString = "";
            for (int i = 0; i < inum; i++)
            {
                tempString += "{ ";
                for (int j = 0; j < jnum; j++)
                {
                    tempString = tempString + this[i, j].ToString() + " ";
                }
                tempString = tempString + "}";
            }
            resultLine = resultLine + tempString + "}";
            return resultLine;
        }
        public int GetElement(int n, int m)
        {
            ExceptionBorder(n, inum);
            ExceptionBorder(m, jnum);
            int value = 0;
            for (int i = 0; i < inum; i++)
            {
                for (int j = 0; j < jnum; j++)
                {
                    if (i == n && j == m)
                    {
                        value = this[i, j];
                    }
                }
            }
            return value;
        }
        public void WriteElement(int i, int j, int value)
        {
            ExceptionBorder(i, inum);
            ExceptionBorder(j, jnum);
            this[i, j] = value;

        }
        public void Show()
        {
            for (int i = 0; i < inum; i++)
            {
                for (int j = 0; j < jnum; j++)
                {
                    Console.Write("\t" + this[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
        public override bool Equals(object obj)
        {
            return (this as MyMatrix) == (obj as MyMatrix);
        }
    }

}
