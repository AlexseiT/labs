using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using labs;
using System.Threading.Tasks;

namespace _5lab
{
    public abstract class TFraction
    {
        private int numerator;
        private int denominator;
        public int Numerator
        {
            get
            {
                return numerator;
            }
            set
            {
                numerator = value;
            }
        }
        public int Denominator
        {
            get
            {
                return denominator;
            }
            set
            {
                denominator = value;
            }
        }
        public TFraction()
        {
            Numerator = 0;
            Denominator = 1;
        }
        public TFraction(int a, int b)
        {
            if (b == 0)
            {
                throw new ClassException("Деление на ноль невозможно!");
            }
            Numerator = a;
            Denominator = b;
            Normalized(this);
        }
        public TFraction(string str)
        {
            var index = str.IndexOf("/");
            if (index < 0)
            {
                throw new ClassException("Строка пуста!");
            }

            var num = str.Substring(0, index);
            var den = str.Substring(index + 1);
            var numInt = Convert.ToInt32(num);
            var denInt = Convert.ToInt32(den);
            if (denInt == 0)
            {
                throw new ClassException("Деление на ноль невозможно!");
            }
            Numerator = numInt;
            Denominator = denInt;
            Normalized(this);
        }
        public TFraction Copy()
        {
            return (TFraction)this.MemberwiseClone();
        }
        public TFraction Add(TFraction b)
        {
            TFraction res = b.Copy();
            if (this.Denominator == b.Denominator)
            {
                res.denominator = this.Denominator;
                res.numerator = this.Numerator + b.Numerator;
            }
            else
            {
                int nok = NOK(Convert.ToInt32(this.Denominator), Convert.ToInt32(b.Denominator));
                res.denominator = nok;
                res.numerator = this.Numerator * (nok / this.Denominator) + b.Numerator * (nok / b.Denominator);
            }
            return Normalized(res);
        }
        public TFraction Difference(TFraction B)
        {
            if (B.Numerator == 0) return Normalized(this);
            TFraction res = this.Copy();
            TFraction a = Normalized(this), b = Normalized(B);
            if (a.Denominator == b.Denominator)
            {
                res.Denominator = a.Denominator;
                res.Numerator = a.Numerator - b.Numerator;
            }
            else
            {
                int nok = NOK(Convert.ToInt32(a.Denominator), Convert.ToInt32(b.Denominator));
                res.Denominator = nok;
                res.Numerator = a.Numerator * (nok / a.Denominator) - b.Numerator * (nok / b.Denominator);
            }
            return Normalized(res);
        }    
        public TFraction Multiplication(TFraction b)
        {
            TFraction res = this.Copy();
            res.Denominator = this.Denominator * b.Denominator;
            res.Numerator = this.Numerator * b.Numerator;
            return res;
        }
        public TFraction Division(TFraction b)
        {
            TFraction res = this.Copy();
            res.Denominator = this.Denominator * b.Numerator;
            res.Numerator = this.Numerator * b.Denominator;
            return Normalized(res);
        }
        public TFraction Square()
        {
            return this.Multiplication(this);
        }
        public TFraction Reverse()
        {
            TFraction res = this.Copy();
            res.Denominator = this.Numerator;
            res.Numerator = this.Denominator;
            return res;
        }
        public TFraction Minus()
        {
            TFraction res = this.Copy();
            res.Denominator = this.Denominator;
            res.Numerator = 0 - this.Numerator;
            return res;
        }
        public bool Equal(TFraction b)
        {
            if ((b.Numerator == this.Numerator) && (this.Denominator == b.Denominator))
            {
                return true;
            }
            else return false;
        }
        public bool More(TFraction d)
        {
            TFraction otv = this.Difference(d);
            if ((otv.Numerator > 0 && otv.Denominator > 0)
                || (otv.Numerator < 0 && otv.Denominator < 0))
            {
                return true;
            }

            return false;
        }
        public int GetNumeratorNumber()
        {
            return numerator;
        }
        public int GetDenominatorNumber()
        {
            return denominator;
        }
        public string GetNumeratorString()
        {
            return numerator.ToString();
        }
        public string GetDenominatorString()
        {
            return denominator.ToString();
        }
        public string GetString()
        {
            return numerator + "/" + denominator;
        }
        private int NOK(int a, int b)
        {
            return (a * b) / Gcd(a, b);
        }
        private int Gcd(int a, int b)
        {
            return a != 0 ? Gcd(b % a, a) : b;
        }
        public int NOD(List<int> list)
        {
            if (list.Count == 0) return 0;
            int i;
            int gcd = list[0];
            for (i = 0; i < list.Count - 1; i++)
                gcd = NOD(gcd, list[i + 1]);
            return gcd;
        }
        static int NOD(int a, int b)
        {
            while (b != 0)
            {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }
        private TFraction Normalized(TFraction SimpleFractions)
        {
            TFraction fractions = SimpleFractions;
            if (fractions.Numerator == 0) { fractions.Denominator = 1; return fractions; }
            fractions = Reduction(fractions);
            if (NOD(new List<int> { fractions.Numerator, fractions.Denominator }) != 0)
            {
                int nod = NOD(new List<int> { fractions.Numerator, fractions.Denominator });
                fractions.Numerator /= nod;
                fractions.Denominator /= nod;
            }
            if (fractions.Denominator < 0)
            {
                fractions.Numerator *= -1;
                fractions.Denominator *= -1;
            }
            return fractions;
        }
        public TFraction Reduction(TFraction SimpleFractions)
        {
            TFraction a = SimpleFractions;
            if ((SimpleFractions.Numerator >= 0 && SimpleFractions.Denominator < 0) || (SimpleFractions.Numerator < 0 && SimpleFractions.Denominator < 0))
            {
                SimpleFractions.Numerator *= -1;
                SimpleFractions.Denominator *= -1;
            }
            var nod = NOD(new List<int> { a.Numerator, a.Denominator });
            if (nod != 1)
            {
                a.Denominator /= nod;
                a.Numerator /= nod;
            }
            return a;
        }
    }
    public class Fraction : TFraction
    {
        public Fraction(int a, int b) : base(a, b)
        {

        }
        public Fraction(string str) : base(str)
        {

        }
        public Fraction() : base()
        {

        }
        public static Fraction operator +(Fraction a, Fraction b)
        {
            return (Fraction)a.Add(b);
        }
        public static Fraction operator *(Fraction a, Fraction b)
        {
            return (Fraction)a.Multiplication(b);
        }
        public static Fraction operator -(Fraction a, Fraction b)
        {
            return (Fraction)a.Difference(b);
        }
        public static Fraction operator /(Fraction a, Fraction b)
        {
            return (Fraction)a.Division(b);
        }
        public static Fraction operator /(int a, Fraction b)
        {
            return (Fraction)(new Fraction(a, 1)).Division(b);
        }
        public override bool Equals(object obj)
        {
            Fraction fracton = (Fraction)obj;
            if ((fracton.Numerator == this.Numerator) && (this.Denominator == fracton.Denominator))
            {
                return true;
            }
            else return false;
        }
        public static bool operator ==(Fraction a, Fraction b)
        {
            return (a.Numerator == b.Numerator) && (a.Denominator == b.Denominator);
        }
        public static bool operator !=(Fraction a, Fraction b)
        {
            return (a.Numerator != b.Numerator) || (a.Denominator != b.Denominator);
        }
        public static bool operator >(Fraction a, Fraction b)
        {
            return ((double)a.Numerator / (double)a.Denominator) > ((double)b.Numerator / (double)b.Denominator);
        }
        public static bool operator <(Fraction a, Fraction b)
        {
            return ((double)a.Numerator / (double)a.Denominator) < ((double)b.Numerator / (double)b.Denominator);
        }
        public override int GetHashCode()
        {
            return this.Numerator.GetHashCode() + this.Denominator.GetHashCode();
        }
        public override string ToString()
        {
            return GetString();
        }
    }
    //-------------------------------------------------------------


    //7 lab
    public abstract class T_PNumber
    {
        private double number;          
        private int baseNumber;         
        private int сorrectNumber;    
        public T_PNumber()
        {
            this.number = 0f;
            this.baseNumber = 10;
            this.сorrectNumber = 0;
        }
        public T_PNumber(double a, int b, int c)
        {
            try
            {
                if (b < 10 && b > 1 && c >= 0 && check(a, b, c))
                {
                    this.baseNumber = b;
                    this.сorrectNumber = c;
                    number = ConvertToDouble(a);
                }
                else if (b == 10)
                {
                    this.baseNumber = b;
                    this.сorrectNumber = c;
                    number = a;
                }
                else
                {
                    this.number = 0f;
                    this.baseNumber = 10;
                    this.сorrectNumber = 0;
                }
            }
            catch (ClassException e)
            {
                this.number = 0f;
                this.baseNumber = 10;
                this.сorrectNumber = 0;
                Console.WriteLine(e.Message);
            }

        }
        public T_PNumber(string a, string b, string c)
        {
            this.baseNumber = Convert.ToInt32(b);
            this.сorrectNumber = Convert.ToInt32(c);
            try
            {
                if (this.baseNumber < 17 && this.baseNumber > 1 && this.baseNumber != 10 && this.сorrectNumber >= 0 && check(a, b, c))
                {
                    number = ConvertStringToDouble(a);
                }
                else if (this.baseNumber == 10)
                {
                    number = Convert.ToDouble(a);
                }
            }
            catch (ClassException e)
            {
                this.number = 0;
                this.baseNumber = 10;
                this.сorrectNumber = 0;
                Console.WriteLine(e.Message);
            }
        }
        public T_PNumber(T_PNumber d)
        {
            number = d.number;
            baseNumber = d.baseNumber;
            сorrectNumber = d.сorrectNumber;
        }
        public T_PNumber Copy()
        {
            return (T_PNumber)this.MemberwiseClone();
        }
        public T_PNumber Addition(T_PNumber d)
        {
            T_PNumber tmp = d.Copy();
            if (d.baseNumber != this.baseNumber || d.сorrectNumber != this.сorrectNumber)
            {
                tmp.number = 0.0;
                return tmp;
            }
            tmp.number = this.number + d.number;
            return tmp;
        }
        public T_PNumber Multiplication(T_PNumber d)
        {
            T_PNumber tmp = d.Copy();
            if (d.baseNumber != this.baseNumber || d.сorrectNumber != this.сorrectNumber)
            {
                tmp.number = 0.0;
                return tmp;
            }
            tmp.number = this.number * d.number;
            return tmp;
        }
        public T_PNumber Substraction(T_PNumber d)
        {
            T_PNumber tmp = d.Copy();
            if (d.baseNumber != this.baseNumber || d.сorrectNumber != this.сorrectNumber)
            {
                tmp.number = 0.0;
                return tmp;
            }
            tmp.number = this.number - d.number;
            return tmp;
        }
        public T_PNumber Division(T_PNumber d)
        {
            T_PNumber tmp = d.Copy();
            if (d.baseNumber != this.baseNumber || d.сorrectNumber != this.сorrectNumber)
            {
                tmp.number = 0.0;
                return tmp;
            }
            tmp.number = this.number / d.number;
            return tmp;
        }
        public T_PNumber Revers()
        {
            T_PNumber tmp = this.Copy();
            tmp.number = 1 / this.number;
            return tmp;
        }
        public T_PNumber Sqr()
        {
            T_PNumber tmp = this.Copy();
            tmp.number = this.number * this.number;
            return tmp;
        }
        public double GetPNumber()
        {
            return ConvertDoubleToBaseDouble(number);
        }
        public string GetPString()
        {
            return ConvertStringToBaseDouble(number);
        }
        public int GetBaseNumber()
        {
            return this.baseNumber;
        }
        public string GetBaseString()
        {
            return this.baseNumber.ToString();
        }
        public int GetСorrectnessNumber()
        {
            return this.сorrectNumber;
        }
        public string GetCorrectnessString()
        {
            return this.сorrectNumber.ToString();
        }
        public void SetBaseNumber(int b)
        {
            if (check(this.number, b, this.сorrectNumber))
            {
                this.baseNumber = b;
            }
            else
            {
                return;
            }
        }
        public void SetBaseString(string b)
        {
            if (check(this.number, Convert.ToInt32(b), this.сorrectNumber))
            {
                this.baseNumber = Convert.ToInt32(b);
            }
            else
            {
                return;
            }

        }
        public void SetCorrectnessNumber(int c)
        {
            if (check(this.number, this.baseNumber, c))
            {
                this.сorrectNumber = c;
            }
            else
            {
                return;
            }

        }
        public void SetCorrectnessString(string c)
        {
            if (check(this.number, this.baseNumber, Convert.ToInt32(c)))
            {
                this.сorrectNumber = Convert.ToInt32(c);
            }
            else
            {
                return;
            }

        }
        private double ConvertToDouble(double a)
        {
            double num_int = (a * Math.Pow(10, сorrectNumber));
            int left = (int)(num_int / Math.Pow(10, сorrectNumber));
            int right = (int)(num_int % (int)Math.Pow(10, сorrectNumber));
            double result = 0;

            int i = 0;
            while (left > 0)
            {
                int tmp = left % 10;
                result += tmp * Math.Pow(baseNumber, i);
                left /= 10;
                i++;
            }

            i = сorrectNumber - 1;
            int j = -1;
            while (i > -1)
            {
                int tmp = right / (int)Math.Pow(10, i);
                result += tmp * Math.Pow(baseNumber, j);
                right %= (int)Math.Pow(10, i);
                i--;
                j--;
            }

            return Math.Floor(result * Math.Pow(10, сorrectNumber)) / Math.Pow(10, сorrectNumber); ;
        }
        private double ConvertStringToDouble(string str)
        {
            string left, right;
            int tmp;
            double result = 0;

            if (сorrectNumber == 0)
            {
                for (int i = str.Length - 1; i >= 0; i--)
                {
                    if (str[i] >= 'A' && str[i] <= 'Z')
                    {
                        int move = Math.Abs('A' - str[i]);
                        tmp = 10 + move;
                    }
                    else
                    {
                        tmp = str[i] - '0';
                    }
                    result += tmp * Math.Pow(baseNumber, str.Length - i - 1);
                }
                return result;
            }
            else if (сorrectNumber > 0)
            {
                string[] substr = str.Split(",");
                left = substr[0];
                right = substr[1];

                for (int i = left.Length - 1; i >= 0; i--)
                {
                    if (left[i] >= 'A' && left[i] <= 'Z')
                    {
                        int move = Math.Abs('A' - left[i]);
                        tmp = 10 + move;
                    }
                    else
                    {
                        tmp = left[i] - '0';
                    }
                    result += tmp * Math.Pow(baseNumber, left.Length - i - 1);
                }

                for (int i = 0; i < right.Length; i++)
                {
                    if (right[i] >= 'A' && right[i] <= 'Z')
                    {
                        int move = Math.Abs('A' - right[i]);
                        tmp = 10 + move;
                    }
                    else
                    {
                        tmp = right[i] - '0';
                    }
                    result += tmp * Math.Pow(baseNumber, -(i + 1));
                }


                return Math.Floor(result * Math.Pow(10, сorrectNumber)) / Math.Pow(10, сorrectNumber);
            }
            else
            {
                return -1;
            }
        }
        private double ConvertDoubleToBaseDouble(double a)
        {
            if (baseNumber > 1 && baseNumber < 10 && a != 0)
            {
                string num_10_str = a.ToString();
                int j;
                for (j = 0; j < num_10_str.Length && num_10_str[j] != ','; j++) { }

                if (j < num_10_str.Length)
                {
                    string[] num_10_str_split = num_10_str.Split(",");
                    int left = Convert.ToInt32(num_10_str_split[0]);
                    double right;
                    if (num_10_str_split[1].Length < сorrectNumber)
                    {
                        right = Convert.ToDouble(num_10_str_split[1].Substring(0, this.сorrectNumber - 1));
                    }
                    else
                    {
                        right = Convert.ToDouble(num_10_str_split[1].Substring(0, this.сorrectNumber));
                    }
                    string result = "";

                    while (left > 0)
                    {
                        int tmp = left % baseNumber;
                        result += tmp;
                        left = left / baseNumber;
                    }

                    result = Revers(result);

                    result += ",";
                    string sub_res = "";
                    string right_str = "0," + right;
                    int i = 0;
                    while (i < сorrectNumber + 1)
                    {
                        right = Convert.ToDouble(right_str);
                        right *= (double)baseNumber;
                        right_str = right.ToString();
                        for (j = 0; j < right_str.Length && right_str[j] != ','; j++) { }
                        if (j < right_str.Length)
                        {
                            string[] sp = right_str.Split(",");
                            sub_res += sp[0];
                            right_str = "0," + right_str.Substring(2);
                        }
                        else
                        {
                            sub_res += right_str;
                            right_str = "0,0";
                        }

                        i++;
                    }
                    result += sub_res;
                    double res_double = Convert.ToDouble(result);
                    res_double = Math.Round(res_double, сorrectNumber, MidpointRounding.ToZero);

                    return res_double;
                }
                else
                {
                    int left = Convert.ToInt32(num_10_str);

                    string result = "";

                    while (left > 0)
                    {
                        int tmp = left % baseNumber;
                        result += tmp;
                        left = left / baseNumber;
                    }

                    result = Revers(result);

                    return Convert.ToDouble(result);
                }
            }
            else if (a == 0)
            {
                return 0.0;
            }
            else
            {
                return -1;
            }
        }
        private string ConvertStringToBaseDouble(double n)
        {
            try
            {
                if (baseNumber > 1 && baseNumber < 10)
                {
                    string result = ConvertDoubleToBaseDouble(n).ToString();
                    return result;
                }
                else if (baseNumber > 10 && baseNumber < 17)
                {
                    if (Math.Abs(n - 0.0) < 0.001)
                    {
                        return "0,0";
                    }
                    string number = n.ToString();
                    if (checkPoint(number))
                    {
                        string[] spliter = number.Split(',');
                        int left = Convert.ToInt32(spliter[0]);
                        double right = Convert.ToDouble(spliter[1]);
                        string result = "";

                        while (left > 0)
                        {
                            double tmp = left % this.baseNumber;
                            char tmp_char = tmp.ToString().ToCharArray()[0];
                            if (tmp > 9)
                            {
                                tmp_char = (char)('A' + tmp - 10);
                            }
                            result += tmp_char;
                            left /= baseNumber;
                        }
                        result = Revers(result) + ",";

                        int iter = 0;
                        double tmp_right = right, iter_right = 0;
                        for (; Math.Truncate(tmp_right) > 0; iter_right++)
                        {
                            tmp_right /= 10;
                        }
                        right = right / Math.Pow(10, iter_right);
                        while (iter < сorrectNumber)
                        {
                            right *= baseNumber;
                            int add = (int)Math.Truncate(right);
                            char add_char = add.ToString().ToCharArray()[0];
                            if (add > 9)
                            {
                                add_char = (char)('A' + add - 10);
                            }
                            result += add_char;
                            right = right - Math.Truncate(right);
                            iter++;
                        }

                        return result;
                    }
                    else
                    {
                        int left = Convert.ToInt32(number);
                        string result = "";
                        while (left > 0)
                        {
                            double tmp = left % this.baseNumber;
                            char tmp_char = tmp.ToString().ToCharArray()[0];
                            if (tmp > 9)
                            {
                                tmp_char = (char)('A' + tmp - 10);
                            }
                            result += tmp_char;
                            left /= baseNumber;
                        }
                        result = Revers(result);
                        return result;
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            return null;
        }
        private bool checkPoint(string n)
        {
            int i;
            for (i = 0; i < n.Length && n[i] != ','; i++) { }
            if (i < n.Length)
            {
                return true;
            }
            return false;
        }
        private bool checkPoint(double n)
        {
            string n_str = n.ToString();
            int i;
            for (i = 0; i < n_str.Length && n_str[i] != ','; i++) { }
            if (i < n_str.Length)
            {
                return true;
            }
            return false;
        }
        private string Revers(string str)
        {
            char[] sub_char = str.ToCharArray();
            for (int j = 0; j < str.Length / 2; j++)
            {
                char tmp = sub_char[j];
                sub_char[j] = sub_char[sub_char.Length - j - 1];
                sub_char[sub_char.Length - j - 1] = tmp;
            }

            string result = "";
            for (int j = 0; j < sub_char.Length; j++)
            {
                result += sub_char[j];
            }
            return result;
        }
        private bool checkOnBase(string a, int b)
        {
            foreach (char iter in a)
            {
                int move = Math.Abs('A' - iter);
                int iter_int = iter - '0';
                if (iter >= 'A' && iter <= 'Z')
                {
                    iter_int = 10 + move;
                }
                if (iter == ',')
                {
                    continue;
                }
                if (iter_int >= b)
                {
                    return false;
                }
            }
            return true;
        }
        private bool checkOnC(string a, int c)
        {
            if (checkPoint(a) && c > 0)
            {
                string[] spliter = a.Split(',');
                if (spliter[1].Length == c)
                {
                    return true;
                }
            }
            return false;
        }
        private bool checkOnSymbol(string a)
        {
            foreach (char iter in a)
            {
                if (iter >= 'a' && iter <= 'z')
                {
                    return false;
                }
            }
            return true;
        }
        private bool check(double a, int b, int c)
        {
            string a_str = a.ToString();
            if (!checkOnBase(a_str, b))
            {
                return false;
            }
            if (!checkOnC(a_str, c))
            {
                return false;
            }
            if (!checkOnSymbol(a_str))
            {
                return false;
            }
            return true;
        }
        private bool check(string a, string b, string c)
        {
            int b_int = Convert.ToInt32(b);
            int c_int = Convert.ToInt32(c);
            if (!checkOnBase(a, b_int))
            {
                return false;
            }
            if (!checkOnC(a, c_int))
            {
                return false;
            }
            if (!checkOnSymbol(a))
            {
                return false;
            }
            return true;
        }
    }
    public class PNumber : T_PNumber
    {
        public PNumber() : base()
        {

        }
        public PNumber(double a, int b, int c) : base(a, b, c)
        {

        }
        public PNumber(string a, string b, string c) : base(a, b, c)
        {

        }
        public PNumber(T_PNumber d) : base(d)
        {

        }
    }
    //6 lab
    public abstract class ComplexNumber
    {
        private double real;
        private double imaginary;

        public double Real
        {

            get
            {
                return real;
            }
            set
            {
                real = value;
            }
        }
        public double Imaginary
        {

            get
            {
                return imaginary;
            }
            set
            {
                imaginary = value;
            }
        }
        public ComplexNumber()
        {
            real = 0;
            imaginary = 0;
        }
        public ComplexNumber(double a, double b)
        {
            real = a;
            imaginary = b;
        }
        public ComplexNumber(string str)
        {
            try
            {
                str = str.Replace(" ", "");
                var indexPlus = str.IndexOf("+");
                var astr = str.Substring(0, indexPlus);
                var bstr = str.Substring(indexPlus + 3);
                real = Double.Parse(astr);
                imaginary = Double.Parse(bstr);
            }
            catch
            {
                throw new ClassException("Error string");
            }
        }
        public ComplexNumber Copy()
        {
            return (ComplexNumber)this.MemberwiseClone();
        }
        public ComplexNumber Addition(ComplexNumber b)
        {
            ComplexNumber res = this.Copy();
            res.real += b.real;
            res.imaginary += b.imaginary;
            return res;
        }
        public ComplexNumber Multiplication(ComplexNumber b)
        {
            ComplexNumber res = this.Copy();
            res.real = this.real * b.real - this.imaginary * b.imaginary;
            res.imaginary = this.real * b.imaginary + this.imaginary * b.real;
            return res;
        }
        public ComplexNumber Square()
        {
            ComplexNumber res = this.Copy();
            res.real = this.real * this.real - this.imaginary * this.imaginary;
            res.imaginary = this.real * this.imaginary + this.real * this.imaginary;
            return res;
        }
        public ComplexNumber Reverse()
        {
            ComplexNumber res = this.Copy();
            res.real = this.real / (this.real * this.real + this.imaginary * this.imaginary);
            res.imaginary = -this.imaginary / (this.real * this.real + this.imaginary * this.imaginary);
            return res;
        }
        public ComplexNumber Subtraction(ComplexNumber b)
        {
            ComplexNumber res = this.Copy();
            res.real -= b.real;
            res.imaginary -= b.imaginary;
            return res;
        }
        public ComplexNumber Division(ComplexNumber b)
        {
            ComplexNumber res = this.Copy();
            res.real = (this.real * b.real + this.imaginary * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);
            res.imaginary = (b.real * this.imaginary - this.real * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);
            return res;
        }
        public ComplexNumber Minus()
        {
            ComplexNumber res = this.Copy();
            res.real = 0 - res.real;
            res.imaginary = 0 - res.imaginary;
            return res;
        }
        public double Abs()
        {
            return Math.Sqrt(this.real * this.real + this.imaginary * this.imaginary);
        }
        public double Radian()
        {
            if (this.real > 0)
                return Math.Atan(this.imaginary / this.real);

            if (this.real == 0 && this.imaginary > 0)
                return (Math.PI / 2);

            if (this.real < 0)
                return (Math.Atan(this.imaginary / this.real) + Math.PI);

            if (this.real == 0 && this.imaginary < 0)
                return (-Math.PI / 2);

            return 0;
        }
        public double Degree()
        {
            return Radian() * 180 / Math.PI;
        }
        public ComplexNumber Pow(int n)
        {
            ComplexNumber res = this.Copy();
            res.real = Math.Pow(Abs(), n) * Math.Cos(n * Radian());
            res.imaginary = Math.Pow(Abs(), n) * Math.Sin(n * Radian());
            return res;
        }
        public ComplexNumber Sqrt(int powN, int rootI)
        {
            if (powN == 0)
            {
                ComplexNumber res0 = this.Copy();
                res0.real = 1;
                res0.imaginary = 0;
                return res0;

            }

            if (rootI == 0)
                new ClassException("Error zero division");

            ComplexNumber new1 = Pow(powN);

            ComplexNumber res = this.Copy();
            res.real = Math.Pow(new1.Abs(), 1 / (double)rootI) * Math.Cos((new1.Radian() + 2 * Math.PI * rootI) / rootI);
            res.imaginary = Math.Pow(new1.Abs(), 1 / (double)rootI) * Math.Sin((new1.Radian() + 2 * Math.PI * rootI) / rootI);

            return res;
        }
        public bool Equal(ComplexNumber anClass)
        {
            return (this.real == anClass.real && this.imaginary == anClass.imaginary);
        }
        public bool NotEqual(ComplexNumber anClass)
        {
            return (this.real != anClass.real || this.imaginary != anClass.imaginary);
        }
        public double GetRealNumber()
        {
            return this.real;
        }
        public double GetImaginaryNumber()
        {
            return this.imaginary;
        }
        public string GetRealString()
        {
            return this.real.ToString();
        }
        public string GetImaginaryString()
        {
            return this.imaginary.ToString();
        }
        public string GetString()
        {
            return this.real.ToString("##,###") + ' ' + (this.imaginary >= 0 ? '+' : '-') + " i * " + this.imaginary.ToString("##,###");
        }
        public string String()
        {
            return GetRealString() + (this.imaginary >= 0 ? '+' : '-') + "i*" + GetImaginaryString();
        }

    }
    public class MyComplex : ComplexNumber
    {
        public MyComplex(double a, double b) : base(a, b)
        {
        }
        public MyComplex(string str) : base(str)
        {
        }
        public MyComplex() : base()
        {
        }
    }
    //8 lab
    public class PNumberEditor
    {
        public const string zeroString = "0,0";
        private string number;
        private int baseNumberEdit;
        private int сorrectNumber;
        public PNumberEditor()
        {
            number = zeroString;
            baseNumberEdit = 10;
            сorrectNumber = 1;
        }
        public PNumberEditor(PNumber pnum)
        {
            number = pnum.GetPString();
            baseNumberEdit = pnum.GetBaseNumber();
            сorrectNumber = pnum.GetСorrectnessNumber();
        }
        public PNumber ReturnEditPnumber()
        {
            PNumber pnum = new PNumber(number, Convert.ToString(baseNumberEdit), Convert.ToString(сorrectNumber));
            return pnum; 
        }
        public PNumberEditor(int b, int c)
        {
            if (checkOnCountBaseAndC(b, c))
            {
                this.baseNumberEdit = b;
                this.сorrectNumber = c;
                number = zeroString;
            }
            else
            {
                number = zeroString;
                b = 10;
                c = 1;
            }
        }
        public PNumberEditor(string number, int b, int c)
        {
            if (check(number, b, c))
            {
                this.number = number;
                this.baseNumberEdit = b;
                this.сorrectNumber = c;
            }
            else
            {
                this.number = zeroString;
                this.baseNumberEdit = 10;
                this.сorrectNumber = 1;
            }
        }
        public bool IsZero()
        {
            return (number.Equals(zeroString));
        }
        public string AddSign()
        {
            if (number[0].Equals('-'))
            {
                number = number.Substring(1);
            }
            else
            {
                number = "-" + number;
            }
            return number;
        }
        public string Add(int a)
        {
            if (checkPoint(number) && сorrectNumber == 1 && number[number.Length - 1] == '0')
            {
                number = number.Substring(0, number.Length - 2);
                number += a;
                number += ",0";
            }
            return number;
        }
        public string AddZero()
        {
            if (checkPoint(number) && сorrectNumber == 1 && number[number.Length - 1] == '0')
            {
                number = number.Substring(0, number.Length - 2);
                number += 0;
                number += ",0";
            }
            return number;
        }
        public string BackSpace()
        {
            if (!number.Equals(zeroString) && number.Length > 2)
            {
                number = number.Substring(0, number.Length - 1);
                if (number[number.Length - 1].Equals(','))
                {
                    number += "0";
                    сorrectNumber++;
                }
                сorrectNumber--;
            }
            return number;
        }
        public string Clear()
        {
            number = zeroString;
            сorrectNumber = 1;
            return number;
        }
        public string GetNumber()
        {
            return number;
        }
        public string SetNumber(string a)
        {
            if (checkOnBase(a, baseNumberEdit) && countC(a) > 0)
            {
                number = a;
                сorrectNumber = countC(a);
            }
            return number;
        }
        public String Edit(int a)
        {

            switch (a)
            {
                case 0:
                    AddSign();
                    break;
                case 1:
                    AddZero();
                    break;
                case 2:
                    BackSpace();
                    break;
                case 3:
                    Clear();
                    break;
                case 4:
                    GetNumber();
                    break;
            }

            return number;
        }
        private bool check(string a, int b, int c)
        {
            if (!checkOnBase(a, b))
            {
                return false;
            }
            if (!checkOnC(a, c))
            {
                return false;
            }
            if (!checkOnSymbol(a))
            {
                return false;
            }
            if (!checkOnCountBaseAndC(b, c))
            {
                return false;
            }
            return true;
        }
        private bool checkOnC(string a, int c)
        {
            if (checkPoint(a) && c > 0)
            {
                string[] spliter = a.Split(',');
                if (spliter[1].Length == c)
                {
                    return true;
                }
            }
            if (!checkPoint(a) && c == 0)
            {
                return true;
            }
            return false;
        }
        private bool checkOnSymbol(string a)
        {
            foreach (char iter in a)
            {
                if (iter >= 'a' && iter <= 'z')
                {
                    return false;
                }
            }
            return true;
        }
        private bool checkPoint(string n)
        {
            int i;
            for (i = 0; i < n.Length && n[i] != ','; i++) { }
            if (i < n.Length)
            {
                return true;
            }
            return false;
        }
        private bool checkOnBase(string a, int b)
        {
            foreach (char iter in a)
            {
                int move = Math.Abs('A' - iter);
                int iter_int = iter - '0';
                if (iter >= 'A' && iter <= 'Z')
                {
                    iter_int = 10 + move;
                }
                if (iter == ',')
                {
                    continue;
                }
                if (iter_int >= b)
                {
                    return false;
                }
            }
            return true;
        }
        private bool checkOnCountBaseAndC(int b, int c)
        {
            if (b > 1 && b < 17 && c > 0)
            {
                return true;
            }
            return false;
        }
        public int getC()
        {
            return сorrectNumber;
        }
        public int getB()
        {
            return baseNumberEdit;
        }
        private int countC(string a)
        {
            string[] split = a.Split(",");
            return split[1].Length;
        }
    }
    //9 lab
    public abstract class FractionTEditor
    {
        private const string zeroString = "0/1";
        private string fractionString;

        public FractionTEditor()
        {
            fractionString = zeroString;
        }
        public FractionTEditor(Fraction frac)
        {
            this.fractionString = frac.ToString();
        }
        public void WriteFraction(Fraction frac)
        {
            this.fractionString = frac.ToString();
        }
        public bool IsZero()
        {
            if (fractionString[0] == zeroString[0] || (fractionString[0] == '-' && fractionString[1] == zeroString[0]))
                return true;
            else return false;
        }
        public string Minus()
        {
            if (fractionString[0] == '-')
                fractionString = fractionString.Substring(1);
            else
                fractionString = '-' + fractionString;
            return fractionString;
        }
        public string AddNumber(int a)
        {
            if (a < 0 || a > 9)
                return fractionString;
            if (fractionString[0] != '-' && fractionString[0] != '0')
                fractionString = a + fractionString.Substring(2);
            else if (fractionString[0] == '-' && fractionString[1] != '0')
                fractionString = "-" + a + fractionString.Substring(1);
            else if (fractionString[0] == '-' && fractionString[1] == '0')
                fractionString = "-" + a + fractionString.Substring(2);
            else if (fractionString[0] == '0')
                fractionString = a + fractionString.Substring(1);
            return fractionString;
        }
        public string AddZero()
        {
            return AddNumber(0);
        }
        public string DivisionSymbol()
        {
            if (fractionString[fractionString.Length - 2] != '/')
            {
                fractionString = fractionString.Substring(0, fractionString.Length - 1);
            }

            return fractionString;
        }
        public string Clear()
        {
            fractionString = zeroString;
            return fractionString;
        }
        string Edit(int command)
        {
            switch (command)
            {
                case 0:
                    this.Minus();
                    break;
                case 1:
                    {
                        Console.Write("Enter number to add:");
                        int num;
                        num = Console.Read();
                        AddNumber(num);
                        break;
                    }
                case 2:
                    this.AddZero();
                    break;
                case 3:
                    this.DivisionSymbol();
                    break;
                case 4:
                    this.Clear();
                    break;
                case 5:
                    {
                        Console.Write("Enter string to write:");
                        string inp;
                        inp = Console.ReadLine();
                        this.WriteString(inp);
                        break;
                    }
                default:
                    return fractionString;
            }
            return fractionString;
        }
        public string ReadString()
        {
            return fractionString;
        }
        public string WriteString(string otherStr)
        {
            fractionString = otherStr;
            return fractionString;
        }
    }
    public class FractionEditor : FractionTEditor
    {
        public FractionEditor() : base()
        {

        }
        public FractionEditor(Fraction frac) : base(frac)
        {

        }
    }
    //10 lab
    public enum PartEdit
    {
        real, imaginary
    };
    public enum NumberEdit
    {
        left, right
    };
    public abstract class ComplexTEditor
    {
        string pnum;
        PartEdit part;
        NumberEdit partMode;
        string zeroNumber = "0,+i*0,";

        public ComplexTEditor()
        {
            pnum = zeroNumber;
            part = PartEdit.real;
            partMode = NumberEdit.left;
        }
        public ComplexTEditor(MyComplex pnum)
        {
            this.pnum = pnum.String();
            part = PartEdit.real;
            partMode = NumberEdit.left;
        }
        public void WriteComplex(MyComplex pnum)
        {
            this.pnum = pnum.String();
            part = PartEdit.real;
            partMode = NumberEdit.left;
        }
        public bool IsZero()
        {
            string tmp = pnum;
            if (tmp[0] == '-')
                tmp = tmp.Substring(1);
            tmp = tmp.Replace('-', '+');
            if (tmp == zeroNumber)
                return true;
            else
                return false;
        }
        public string ToggleMinus()
        {
            if (part == PartEdit.real)
            {
                if (pnum[0] == '-')
                    pnum = pnum.Substring(1);
                else
                    pnum = '-' + pnum;
            }
            else
            {
                pnum = pnum.Substring(0, pnum.IndexOf("i*")) + "-" +
                       pnum.Substring(pnum.IndexOf("i*"));
            }
            return pnum;
        }
        public PartEdit ToggleMode()
        {
            if (part == PartEdit.real)
                part = PartEdit.imaginary;
            else
                part = PartEdit.real;
            return part;
        }
        public NumberEdit ToggleNumberMode()
        {
            if (partMode == NumberEdit.left)
                partMode = NumberEdit.right;
            else
                partMode = NumberEdit.left;
            return partMode;
        }
        public string AddNumber(int a)
        {
            if (a < 0 || a > 9)
                return pnum;
            int ind = pnum.IndexOf("i*");
            if (part == PartEdit.real)
            {
                if (partMode == NumberEdit.left)
                {
                    if (pnum[0] == '0')
                        pnum = a + pnum.Substring(1);
                    else if (pnum[0] == '-' && pnum[1] == '0')
                        pnum = '-' + a + pnum.Substring(2);
                    else
                    {
                        int frstNumbSep = pnum.IndexOf(",");
                        pnum = pnum.Insert(frstNumbSep, a.ToString());
                    }
                }
                else
                    pnum.Insert(ind - 1, a.ToString());
            }
            else
            {
                if (partMode == NumberEdit.left)
                {
                    ind += 2;
                    if (pnum[ind] == '0')
                        pnum = pnum.Substring(0, ind - 1) + a + pnum.Substring(ind + 1);
                    else
                    {
                        int lastNumbSep = pnum.LastIndexOf(',');
                        pnum.Insert(lastNumbSep, a.ToString());
                    }
                }
                else
                    pnum += '0' + a;
            }
            return pnum;
        }
        public string AddZero()
        {
            return AddNumber(0);
        }
        public string DelNumber()
        {
            int ind = pnum.IndexOf("i*");
            if (part == PartEdit.real)
            {
                if (partMode == NumberEdit.left)
                {
                    if (pnum[0] == '0')
                        return pnum;
                    else if (pnum[0] == '-' && pnum[1] == '0')
                        return pnum;
                    else
                    {
                        int frstNumbSep = pnum.IndexOf(",");
                        pnum = pnum.Remove(frstNumbSep - 1, 1);
                        if (pnum[0] == ',')
                            pnum = '0' + pnum;
                    }
                }
                else
                {
                    int r = 0;
                    if (!int.TryParse(pnum[ind - 2].ToString(), out r))
                        return pnum;
                    pnum = pnum.Remove(ind - 2, 1);
                }
            }
            else
            {
                if (partMode == NumberEdit.left)
                {
                    ind += 2;
                    if (pnum[ind] == '0')
                        return "0";
                    else
                    {
                        int lastNumbSep = pnum.LastIndexOf(',');
                        if (pnum[lastNumbSep - 2] == '*')
                            pnum = pnum.Substring(0, lastNumbSep - 1) + '0' + pnum.Substring(lastNumbSep);
                        else
                            pnum.Remove(lastNumbSep - 1, 1);
                    }
                }
                else
                {
                    if (pnum[pnum.Length - 1] == ',')
                        return pnum;
                    else
                        pnum.Remove(pnum.Length - 1);
                }
            }
            return pnum;
        }
        public string Clear()
        {
            pnum = zeroNumber;
            part = PartEdit.real;
            partMode = NumberEdit.left;
            return pnum;
        }
        public string Edit(int command)
        {
            switch (command)
            {
                case 0:
                    ToggleMinus();
                    break;
                case 1:
                    {
                        Console.Write("Enter number to add: ");
                        int num;
                        num = Console.Read();
                        AddNumber(num);
                        break;
                    }
                case 2:
                    AddZero();
                    break;
                case 3:
                    DelNumber();
                    break;
                case 4:
                    Clear();
                    break;
                case 5:
                    {
                        Console.WriteLine("Enter string to write: ");
                        string inp;
                        inp = Console.ReadLine();
                        WriteNumber(inp);
                        break;
                    }
                default:
                    break;
            }
            return pnum;
        }
        public string WriteNumber(string otherNumber)
        {
            pnum = otherNumber;
            return pnum;
        }
        public string ReadNumber()
        {
            return pnum;
        }
    }
    public class ComplexEditor : ComplexTEditor
    {
        public ComplexEditor() : base()
        {

        }
        public ComplexEditor(MyComplex pnum) : base(pnum)
        {

        }
    }
    //11 lab
    public abstract class TMemory<T>
    {
        public HashSet<T> number;

        public TMemory()
        {
            number = new HashSet<T>();
        }
        public void Clear()
        {
            number.Clear();
        }
        public void Add(T item)
        {
            number.Add(item);
        }
        public void Remove(T item)
        {
            number.Remove(item);
        }
        public bool IsClear()
        {
            try { number.Last(); }
            catch (InvalidOperationException) { return true; }
            return false;
        }
        public bool Contains(T item)
        {
            return number.Contains(item);
        }
        public int Count()
        {
            return this.number.Count();
        }
        public T ElementAt(int i)
        {
            object ret = this.number.ElementAt(i);
            return (T)ret;
        }
        public String Show()
        {
            StringBuilder sb = new StringBuilder();
            foreach (T t in this.number)
            {
                sb.Append($"{t.GetType().GetMethod("Show")?.Invoke(t, null) ?? t} ");
            }
            return sb.ToString();

        }
        public override bool Equals(object obj)
        {
            if (this.number.Count == ((TMemory<T>)obj).number.Count)
            {
                for (int i = 0; i < number.Count; i++)
                {
                    if (!(this.number.ElementAt(i).Equals(((TMemory<T>)obj).number.ElementAt(i))))
                        return false;
                }
            }
            return true;
        }
        public TMemory<T> Copy()
        {
            return (TMemory<T>)this.MemberwiseClone();
        }
    }
    public class TSet<T> : TMemory<T> where T : new()
    {
        public TSet() : base()
        {

        }
        public TSet<T> Union(TMemory<T> ts)
        {
            TSet<T> newtset = new TSet<T>();
            foreach (T t in this.number)
            {
                newtset.Add(t);
            }
            foreach (T t in ts.number)
            {
                newtset.Add(t);
            }
            return newtset;
        }
        public TSet<T> Except(TSet<T> ts)
        {
            TSet<T> newtset = new TSet<T>();
            foreach (T t in this.number)
            {
                newtset.Add(t);
            }
            foreach (T t in ts.number)
            {
                newtset.Remove(t);
            }
            return newtset;
        }
        public TSet<T> Intersect(TSet<T> ts)
        {
            TSet<T> newtset = new TSet<T>();
            foreach (T t in this.number)
            {
                if (ts.Contains(t))
                    newtset.Add(t);
            }
            return newtset;
        }
    }
    //12 lab
    public enum operation
    {
        None,
        Add,
        Sub,
        Mul,
        Div
    }
    public enum function
    {
        None,
        Rev,
        Sqr
    }
    public abstract class TProcessor<T> where T : new()
    {
        public operation Operation;
        public function Function;
        public T Lop_Res, Rop;

        public TProcessor()
        {
            Operation = operation.None;
            Function = function.None;
            Lop_Res = new T();
            Rop = new T();
        }
        public TProcessor(T lop_res, T rop)
        {
            Operation = operation.None;
            Function = function.None;
            Lop_Res = lop_res;
            Rop = rop;
        }
        public void OperationClear()
        {
            Operation = operation.None;
        }
        public void OperationRun()
        {
            switch (Operation)
            {
                case operation.Add:
                    {
                        Lop_Res = (dynamic)Lop_Res + (dynamic)Rop;
                        break;
                    }
                case operation.Sub:
                    {
                        Lop_Res = (dynamic)Lop_Res - (dynamic)Rop;
                        break;
                    }
                case operation.Mul:
                    {
                        Lop_Res = (dynamic)Lop_Res * (dynamic)Rop;
                        break;
                    }
                case operation.Div:
                    {
                        Lop_Res = (dynamic)Lop_Res / (dynamic)Rop;
                        break;
                    }
            }
        }
        public void OperationSet(int newop)
        {
            try
            {
                Operation = (operation)newop;
            }
            catch
            {
                throw new ArgumentException();
            }
        }
        public operation OperationGet()
        {
            return this.Operation;
        }
        public void FunctionClear()
        {
            Function = function.None;
        }
        public void FunctionRun()
        {
            switch (Function)
            {
                case function.Rev:
                    {
                        if (Rop.GetType().GetMethod("Rev")?.Invoke(Rop, null) == null)
                        {
                            Rop = 1 / (dynamic)Rop;
                        }
                        else Rop = (T)Rop.GetType().GetMethod("Rev")?.Invoke(Rop, null);
                        break;
                    }
                case function.Sqr:
                    {
                        if (Rop.GetType().GetMethod("Sqr")?.Invoke(Rop, null) == null)
                        {
                            Rop = (dynamic)Rop * (dynamic)Rop;
                        }
                        else Rop = (T)Rop.GetType().GetMethod("Sqr")?.Invoke(Rop, null);
                        break;
                    }
            }
        }
        public void FunctionSet(int newfunc)
        {
            try
            {
                Function = (function)newfunc;
            }
            catch
            {
                throw new ArgumentException();
            }
        }
        public function FunctionGet()
        {
            return this.Function;
        }
        public void Lop_Res_Set(T newlopres)
        {
            Lop_Res = newlopres;
        }
        public void Rop_Set(T newrop)
        {
            Rop = newrop;
        }
        public void ReSet()
        {
            Lop_Res = new T();
            Rop = new T();
        }
        public string RetLop_Res()
        {
            object str = Lop_Res.GetType().GetMethod("Show")?.Invoke(Lop_Res, null) ?? Lop_Res;
            return str.ToString();
        }
        public T RetTLop_Res()
        {
            object str = Lop_Res.GetType().GetMethod("Copy")?.Invoke(null, new object[] { Lop_Res }) ?? Lop_Res;
            return (T)str;
        }
        public string RetRop()
        {
            object str = Rop.GetType().GetMethod("Show")?.Invoke(Rop, null) ?? Rop;
            return str.ToString();
        }
        public T RetTRop()
        {
            object str = Rop.GetType().GetMethod("Copy")?.Invoke(null, new object[] { Rop }) ?? Rop;
            return (T)str;
        }
        public override bool Equals(object obj)
        {
            if (((this.Lop_Res.Equals(((TProcessor<T>)obj).Lop_Res))) && (this.Rop.Equals(((TProcessor<T>)obj).Rop)))
            {
                return true;
            }
            else return false;
        }
    }
    public class Processor<T> : TProcessor<T> where T : new()
    {
        public Processor() : base()
        {

        }
        public Processor(T lop_res, T rop) : base(lop_res, rop)
        {

        }
    }
    // 13 lab
    public abstract class TPlenty<T>
    {
        public HashSet<T> hash;

        public TPlenty()
        {
            hash = new HashSet<T>();
        }
        public void Clear()
        {
            hash.Clear();
        }
        public void Add(T item)
        {
            hash.Add(item);
        }
        public void Remove(T item)
        {
            hash.Remove(item);
        }
        public bool IsClear()
        {
            try { hash.Last(); }
            catch (InvalidOperationException) { return true; }
            return false;
        }
        public bool Contains(T item)
        {
            return hash.Contains(item);
        }
        public int Count()
        {
            return this.hash.Count();
        }
        public T ElementAt(int i)
        {
            object ret = this.hash.ElementAt(i);
            return (T)ret;
        }
        public String Show()
        {
            StringBuilder sb = new StringBuilder();
            foreach (T t in this.hash)
            {
                sb.Append($"{t.GetType().GetMethod("Show")?.Invoke(t, null) ?? t} ");
            }
            //sb.Append("\n");
            return sb.ToString();
            //Console.WriteLine();
        }
        public override bool Equals(object obj)
        {
            if (this.hash.Count == ((TPlenty<T>)obj).hash.Count)
            {
                for (int i = 0; i < hash.Count; i++)
                {
                    if (!(this.hash.ElementAt(i).Equals(((TPlenty<T>)obj).hash.ElementAt(i))))
                        return false;
                }
            }
            return true;
        }
        public TPlenty<T> Copy()
        {
            return (TPlenty<T>)this.MemberwiseClone();
        }
    }
    public class Plenty<T> : TPlenty<T> where T : new()
    {
        public Plenty() : base()
        {

        }
        public Plenty<T> Union(TPlenty<T> obj)
        {
            Plenty<T> newtset = new Plenty<T>();
            foreach (T t in this.hash)
            {
                newtset.Add(t);
            }
            foreach (T t in obj.hash)
            {
                newtset.Add(t);
            }
            return newtset;
        }
        public Plenty<T> Except(Plenty<T> obj)
        {
            Plenty<T> newtset = new Plenty<T>();
            foreach (T t in this.hash)
            {
                newtset.Add(t);
            }
            foreach (T t in obj.hash)
            {
                newtset.Remove(t);
            }
            return newtset;
        }
        public Plenty<T> Intersect(Plenty<T> obj)
        {
            Plenty<T> newtset = new Plenty<T>();
            foreach (T t in this.hash)
            {
                if (obj.Contains(t))
                    newtset.Add(t);
            }
            return newtset;
        }
    }
    // 14 lab
    public class Member : IComparable<Member>
    {
        private int coefficient;
        private int degree;
        public int Coeff
        {
            get { return coefficient; }
            set
            {
                if (value == 0)
                    degree = 0;
                coefficient = value;
            }
        }
        public int Degree
        {
            get { return degree; }
            set
            {
                if (coefficient == 0)
                    degree = 0;
                else degree = value;
            }
        }
        public Member(int coeff = 0, int degree = 0)
        {
            Coeff = coeff;
            Degree = degree;
        }
        public override bool Equals(object tmem)
        {
            if ((((Member)tmem).Coeff == this.Coeff) && (((Member)tmem).Degree == this.Degree))
                return true;
            else
                return false;
        }
        public Member Diff()
        {
            return new Member() { Coeff = (this.Coeff * this.Degree), Degree = this.Degree - 1 };
        }
        public double Calculate(double a)
        {
            return this.Coeff * Math.Pow(a, this.Degree);
        }
        public string TMember2Str()
        {
            return this.Coeff == 0 ? "" : $"{this.Coeff}x^{this.Degree}";
        }
        public int CompareTo(Member other)
        {
            if (this.Degree.CompareTo(other.Degree) != 0)
                return this.Degree.CompareTo(other.Degree);
            else
            {
                other.Coeff += this.Coeff;
                return 0;
            }
        }
    }
    public class Polynom
    {
        public SortedSet<Member> Members;
        public Polynom()
        {
            Members = new SortedSet<Member>();
            Members.Add(new Member(0, 0));
        }
        public Polynom Add(Polynom obj)
        {
            Polynom newtpoly = new Polynom();
            foreach (Member mem in obj.Members)
            {
                newtpoly.Members.Add(new Member(mem.Coeff, mem.Degree));
            }
            foreach (Member mem in this.Members)
            {
                newtpoly.Members.Add(new Member(mem.Coeff, mem.Degree));
            }
            return newtpoly;
        }
        public Polynom Mul(Polynom obj)
        {
            Polynom newtpoly = new Polynom();
            foreach (Member mem in obj.Members)
            {
                foreach (Member newmem in this.Members)
                {
                    newtpoly.Members.Add(new Member(newmem.Coeff * mem.Coeff, newmem.Degree + mem.Degree));
                }
            }
            return newtpoly;
        }
        public Polynom Res(Polynom obj)
        {
            Polynom newtpoly = new Polynom();
            foreach (Member mem in obj.Members)
            {
                newtpoly.Members.Add(new Member(-mem.Coeff, mem.Degree));
            }
            foreach (Member mem in this.Members)
            {
                newtpoly.Members.Add(new Member(mem.Coeff, mem.Degree));
            }
            return newtpoly;
        }
        public Polynom Rev()
        {
            Polynom newtpoly = new Polynom();
            foreach (Member mem in this.Members)
            {
                newtpoly.Members.Add(new Member(-mem.Coeff, mem.Degree));
            }
            return newtpoly;
        }
        public int RetDegree()
        {
            return Members.Last().Degree;
        }
        public int RetCoeff(int n)
        {
            try { return Members.Single(x => x.Degree == n).Coeff; }
            catch (InvalidOperationException) { return 0; }
        }
        public override bool Equals(object tp)
        {
            if (((Polynom)tp).Members.SequenceEqual(this.Members)) return true;
            else return false;
        }
        public Polynom Diff()
        {
            Polynom newtpoly = new Polynom();
            foreach (Member mem in this.Members)
            {
                newtpoly.Members.Add(new Member(mem.Coeff, mem.Degree).Diff());
            }
            return newtpoly;
        }
        public double Calculate(double a)
        {
            double an = 0.0;
            foreach (Member mem in this.Members)
            {
                an += mem.Calculate(a);
            }
            return an;
        }
        public void Clear()
        {
            Members = new SortedSet<Member>
            {
                new Member(0, 0)
            };
        }
        public Tuple<int, int> ElementAt(int i)
        {
            try { return Tuple.Create(this.Members.Reverse().ElementAt(i).Coeff, this.Members.Reverse().ElementAt(i).Degree); }
            catch (ArgumentOutOfRangeException) { return Tuple.Create(0, 0); }

        }
        public string Show()
        {
            string str = "";
            foreach (Member x in Members.Reverse())
            {
                str += (x.Coeff > 0) ? "+" : "";
                str += x.TMember2Str();
            }
            return str.TrimStart('+');
        }
    }
}
