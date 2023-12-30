using Microsoft.VisualStudio.TestTools.UnitTesting;
using labs;
using _5lab;
using System;
using System.Collections.Generic;
using System.Linq;
using metriclab;

namespace TestProject1
{
   // [TestClass]
    public class UnitTest1
    {
        //lab1 C0
        //[TestMethod]
        //public void TestSum()
        //{
        //    int[] expected = {10,20,30,40,50};
        //    int[] a = { 5, 10, 15, 20, 25 };
        //    int[] result = Program.Sum(a, a);
        //    for(int i = 0; i < expected.Length; i++)
        //        Assert.AreEqual(expected[i], result[i]);
        //}

        //[TestMethod]
        //public void TestShift()
        //{
        //    double[] expected = { 8, 0, 5, 6, 7 };
        //    double[] a = { 5, 6, 7, 8, 0 };
        //    double[] result = Program.Shift(3, a);
        //    for (int i = 0; i < expected.Length; i++)
        //        Assert.AreEqual(expected[i], result[i]);
        //}


        //[TestMethod]
        //public void TestFindIndex()
        //{
        //    int[] seq = { 1, 22, 33 };
        //    int[] vec = { 5, 6, 7, 8, 123, 1, 22, 33, 1, 22, 33 };
        //    int expected = 5;
        //    int result = Program.FindIndex(seq, vec);
        //    Assert.AreEqual(expected, result);
        //}
        ////lab2 C1
        //[TestMethod]
        //public void TestMax1()
        //{
        //    int expected = 100;
        //    int result = Program.Max(10, 100);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestMax2()
        //{
        //    int expected = 100;
        //    int result = Program.Max(100, 10);
        //    Assert.AreEqual(expected, result);
        //}


        //[TestMethod]
        //public void TestFindSumValue1()
        //{
        //    double[] list1 = new double[3] { 2.5, 3.4, 4.3 };
        //    double[] list2 = new double[3] { 1.5, 2.4, 5.3 };
        //    double[] list3 = new double[3] { 6.1, 7.1, 8.1 };

        //    double[][] a = { list1, list2, list3 };
        //    double expected = 5.3+7.1;
        //    double result = Program.FindSumValue(a);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestFindSumValue2()
        //{
        //    double[] list1 = new double[4] { 2.5, 3.4, 4.3 , 22.1};
        //    double[] list2 = new double[4] { 1.5, 2.4, 5.3 , 9.6};

        //    double[][] a = { list1, list2};
        //    double expected = 9.6;
        //    double result = Program.FindSumValue(a);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestFindMin1()
        //{
        //    double[] list1 = new double[3] { 2.5, 3.4, 4.3 };
        //    double[] list2 = new double[3] { 1.5, 2.4, 5.3 };
        //    double[] list3 = new double[3] { 6.1, 7.1, 8.1 };

        //    double[][] a = { list1, list2, list3 };
        //    double expected = 1.5;
        //    double result = Program.FindMin(a);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestFindMin2()
        //{
        //    double[] list1 = new double[3] { 0, 3.4, 4.3 };
        //    double[] list2 = new double[3] { 1.5, 2.4, 5.3 };
        //    double[] list3 = new double[3] { 6.1, 7.1, 8.1 };

        //    double[][] a = { list1, list2, list3 };
        //    double expected = 0;
        //    double result = Program.FindMin(a);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestFindMin3()
        //{
        //    double[] list1 = new double[3] { 5, 3.4, 4.3 };
        //    double[] list2 = new double[3] { 1.5, 2.4, 5.3 };
        //    double[] list3 = new double[3] { 0, 7.1, 8.1 };

        //    double[][] a = { list1, list2, list3 };
        //    double expected = 0;
        //    double result = Program.FindMin(a);
        //    Assert.AreEqual(expected, result);
        //}
        ////lab3 C2
        ////1
        //[TestMethod]
        //public void TestRankFinder1()
        //{
        //    int expected = 5;
        //    int result = Program.RankFinder(12543);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestRankFinder2()
        //{
        //    int expected = 0;
        //    int result = Program.RankFinder(3);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestRankFinder3()
        //{
        //    int expected = 1;
        //    int result = Program.RankFinder(12);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestRankFinder4()
        //{
        //    int expected = 3;
        //    int result = Program.RankFinder(123);
        //    Assert.AreEqual(expected, result);
        //}

        ////2

        //[TestMethod]
        //public void TestShiftInt1()
        //{
        //    int expected = 345612;
        //    int result = Program.ShiftInt(123456, 2);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestShiftInt2()
        //{
        //    int expected = 123456;
        //    int result = Program.ShiftInt(123456, 0);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestShiftInt3()
        //{
        //    int expected = 345612;
        //    int result = Program.ShiftInt(561234, -2);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestShiftInt4()
        //{
        //    int expected = 123456;
        //    int result = Program.ShiftInt(123456, 6);
        //    Assert.AreEqual(expected, result);
        //}

        ////3

        //[TestMethod]
        //public void TestInsertInt1()
        //{
        //    int expected = 1234567;
        //    int result = Program.InsertInt(123457, 6, 5);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestInsertInt2()
        //{
        //    int expected = 123457;
        //    int result = Program.InsertInt(123457, 6, 8);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestInsertInt3()
        //{
        //    int expected = 123457;
        //    int result = Program.InsertInt(123457, 6, -1);
        //    Assert.AreEqual(expected, result);
        //}
        //[TestMethod]
        //public void TestInsertInt4()
        //{
        //    int expected = 123457;
        //    int result = Program.InsertInt(123457, -6, 5);
        //    Assert.AreEqual(expected, result);
        //}

        //4

        //[TestMethod]
        //public void TestFindSumValueSecond1()
        //{
        //    double expected = 20;

        //    double[] list = new double[5] { 0, 1, 2, 3, 4 };

        //    double[][] a = { list, list, list, list, list };

        //    double result = Program.FindSumValueSecond(a);
        //    Assert.AreEqual(expected, result);
        //}

        //[TestMethod]
        //public void TestFindSumValueSecond2()
        //{
        //    double expected = 0;

        //    double[] list = new double[5] { 1, 3, 7, 9, 11 };

        //    double[][] a = { list, list, list, list, list };

        //    double result = Program.FindSumValueSecond(a);
        //    Assert.AreEqual(expected, result);
        //}

        //[TestMethod]
        //public void TestFindSumValueSecond3()
        //{
        //    double expected = 20;

        //    double[] list = new double[5] { 2, 2, 2, 2, 2 };

        //    double[][] a = { list, list, list, list, list };

        //    double result = Program.FindSumValueSecond(a);
        //    Assert.AreEqual(expected, result);
        //}

        //// lab4
        //[TestMethod]
        //[ExpectedException(typeof(ClassException))]

        //public void MatrixOutBorderTest1()
        //{
        //    MyMatrix a = new MyMatrix(0, 4);
        //}

        //[TestMethod]
        //[ExpectedException(typeof(ClassException))]

        //public void MatrixOutBorderTest2()
        //{
        //    MyMatrix a = new MyMatrix(4, -2);
        //}

        //[TestMethod]
        //public void MatrixSumTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 1;
        //    a[0, 1] = 1;
        //    a[1, 0] = 1;
        //    a[1, 1] = 1;
        //    MyMatrix b = new MyMatrix(2, 2);
        //    b[0, 0] = 2;
        //    b[0, 1] = 2;
        //    b[1, 0] = 2;
        //    b[1, 1] = 2;
        //    MyMatrix expect = new MyMatrix(2, 2);
        //    expect[0, 0] = 3;
        //    expect[0, 1] = 3;
        //    expect[1, 0] = 3;
        //    expect[1, 1] = 3;
        //    MyMatrix actual = new MyMatrix(2, 2);
        //    actual = a + b;
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixDiffTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 1;
        //    a[0, 1] = 1;
        //    a[1, 0] = 1;
        //    a[1, 1] = 1;
        //    MyMatrix b = new MyMatrix(2, 2);
        //    b[0, 0] = 2;
        //    b[0, 1] = 2;
        //    b[1, 0] = 2;
        //    b[1, 1] = 2;
        //    MyMatrix expect = new MyMatrix(2, 2);
        //    expect[0, 0] = 1;
        //    expect[0, 1] = 1;
        //    expect[1, 0] = 1;
        //    expect[1, 1] = 1;
        //    MyMatrix actual = new MyMatrix(2, 2);
        //    actual = b - a;
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixMultiplicationTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 3;
        //    a[0, 1] = 3;
        //    a[1, 0] = 3;
        //    a[1, 1] = 3;
        //    MyMatrix b = new MyMatrix(2, 2);
        //    b[0, 0] = 2;
        //    b[0, 1] = 2;
        //    b[1, 0] = 2;
        //    b[1, 1] = 2;
        //    MyMatrix expect = new MyMatrix(2, 2);
        //    expect[0, 0] = 12;
        //    expect[0, 1] = 12;
        //    expect[1, 0] = 12;
        //    expect[1, 1] = 12;
        //    MyMatrix actual = new MyMatrix(2, 2);
        //    actual = a * b;
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixEqualTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 1;
        //    a[0, 1] = 2;
        //    a[1, 0] = 3;
        //    a[1, 1] = 4;
        //    MyMatrix b = new MyMatrix(2, 2);
        //    b[0, 0] = 1;
        //    b[0, 1] = 2;
        //    b[1, 0] = 3;
        //    b[1, 1] = 4;
        //    bool res = a == b;
        //    Assert.IsTrue(res);
        //}

        //[TestMethod]
        //public void MatrixTranspositionTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 1;
        //    a[0, 1] = 2;
        //    a[1, 0] = 3;
        //    a[1, 1] = 4;
        //    MyMatrix actual = a.Transposition();
        //    MyMatrix expect = new MyMatrix(2, 2);
        //    expect[0, 0] = 1;
        //    expect[0, 1] = 3;
        //    expect[1, 0] = 2;
        //    expect[1, 1] = 4;
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixGetMinElementTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 4;
        //    a[0, 1] = 3;
        //    a[1, 0] = 2;
        //    a[1, 1] = 1;
        //    int actual = a.GetMinElement();
        //    int expect = 1;
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixGetStringTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 1;
        //    a[0, 1] = 2;
        //    a[1, 0] = 3;
        //    a[1, 1] = 4;
        //    string actual = a.GetMatrixString();
        //    string expect = "{{ 1 2 }{ 3 4 }}";
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixGetElementTest()
        //{
        //    MyMatrix a = new MyMatrix(2, 2);
        //    a[0, 0] = 4;
        //    a[0, 1] = 3;
        //    a[1, 0] = 2;
        //    a[1, 1] = 1;
        //    int actual = a.GetElement(1, 0);
        //    int expect = 2;
        //    Assert.IsTrue(actual == expect);
        //}

        //[TestMethod]
        //public void MatrixWriteElementTest()
        //{
        //    MyMatrix actual = new MyMatrix(2, 2);
        //    actual[0, 0] = 1;
        //    actual[0, 1] = 2;
        //    actual[1, 0] = 3;
        //    actual[1, 1] = 4;
        //    actual.WriteElement(1, 0, 8);
        //    MyMatrix expect = new MyMatrix(2, 2);
        //    expect[0, 0] = 1;
        //    expect[0, 1] = 2;
        //    expect[1, 0] = 8;
        //    expect[1, 1] = 4;
        //    Assert.IsTrue(actual == expect);
        //}

        //lab5
       [TestMethod]
        public void TestTFracInt()
        {
            TFraction frc = new Fraction(10, 5);

            Assert.AreEqual(2, frc.Numerator);
            Assert.AreEqual(1, frc.Denominator);
        }

        [TestMethod]
        public void TestTFracInt2()
        {
            void Action1()
            {
                new Fraction(113, 0);
            }

            Action action = new Action(Action1);

            Assert.ThrowsException<ClassException>(action);
        }

        [TestMethod]
        public void TestTFracStr1()
        {
            var frc = new Fraction("24/36");

            Assert.AreEqual(2, frc.Numerator);
            Assert.AreEqual(3, frc.Denominator);
        }
        [TestMethod]
        public void TestTFracStr2()
        {
            Action action = new Action(Action2);

            Assert.ThrowsException<ClassException>(action);
        }
        private void Action2()
        {
            new Fraction("1/0");
        }

        [TestMethod]
        public void TestCopy()
        {
            var a = new Fraction(11, 12);
            var fCopy = a.Copy();

            Assert.AreEqual(a.Numerator, fCopy.Numerator);
            Assert.AreEqual(a.Denominator, fCopy.Denominator);
        }

        [TestMethod]
        public void TestAdd()
        {
            var a = new Fraction(1, 2);
            var b = new Fraction(1, 3);
            var res = a + b;

            Assert.AreEqual(5, res.Numerator);
            Assert.AreEqual(6, res.Denominator);
        }

        [TestMethod]
        public void TestDifference()
        {
            var a = new Fraction(1, 2);
            var b = new Fraction(1, 3);
            var res = a - b;

            Assert.AreEqual(1, res.Numerator);
            Assert.AreEqual(6, res.Denominator);
        }

        [TestMethod]
        public void TestMultiplication()
        {
            var a = new Fraction(11, 2);
            var b = new Fraction(13, 7);
            var res = a * b;

            Assert.AreEqual(143, res.Numerator);
            Assert.AreEqual(14, res.Denominator);
        }

        [TestMethod]
        public void TestDivision()
        {
            var a = new Fraction(1, 2);
            var b = new Fraction(13, 7);
            var res = a / b;

            Assert.AreEqual(7, res.Numerator);
            Assert.AreEqual(26, res.Denominator);
        }

        [TestMethod]
        public void TestSquare()
        {
            var a = new Fraction(3, 2);
            var res = a.Square();

            Assert.AreEqual(9, res.Numerator);
            Assert.AreEqual(4, res.Denominator);
        }

        [TestMethod]
        public void TestReverse()
        {
            var a = new Fraction(3, 2);
            var res = a.Reverse();

            Assert.AreEqual(2, res.Numerator);
            Assert.AreEqual(3, res.Denominator);
        }

        [TestMethod]
        public void TestMinus()
        {
            var a = new Fraction(3, 2);
            var res = a.Minus();

            Assert.AreEqual(-3, res.Numerator);
            Assert.AreEqual(2, res.Denominator);
        }

        [TestMethod]
        public void TestRavn()
        {
            var a = new Fraction(1, 2);
            var b = new Fraction(1, 2);
            var res = a == b;

            Assert.IsTrue(res);
        }

        [TestMethod]
        public void TestMore()
        {
            var a = new Fraction(2, 3);
            var b = new Fraction(1, 2);
            var res = a > b;

            Assert.IsTrue(res);
        }

        [TestMethod]
        public void TestGetNumeratorNumber()
        {
            var a = new Fraction(2, 3);
            var res = a.GetNumeratorNumber();

            Assert.AreEqual(2, res);
        }

        [TestMethod]
        public void TestGetDenominatorNumber()
        {
            var a = new Fraction(2, 3);
            var res = a.GetDenominatorNumber();

            Assert.AreEqual(3, res);
        }

        [TestMethod]
        public void TestGetNumeratorString()
        {
            var a = new Fraction(2, 3);
            var res = a.GetNumeratorString();

            Assert.AreEqual("2", res);
        }

        [TestMethod]
        public void TestGetDenominatorString()
        {
            var a = new Fraction(2, 3);
            var res = a.GetDenominatorString();

            Assert.AreEqual("3", res);
        }

        [TestMethod]
        public void TestGetString()
        {
            var a = new Fraction(2, 3);
            var res = a.GetString();

            Assert.AreEqual("2/3", res);
        }
    }
    // 6 lab
    //[TestClass]
    public class UnitTestComplex
    {
        [TestMethod]
        public void ComplexDoubleTesting()
        {
            var testClass = new MyComplex(66.99, 44.44);

            Assert.AreEqual(testClass.Real, 66.99);
            Assert.AreEqual(testClass.Imaginary, 44.44);
        }
        [TestMethod]
        public void ComplexStringTesting1()
        {
            string output = "66,99 + i * 44,44";
            var testClass = new MyComplex(output);

            Assert.AreEqual(testClass.Real, 66.99);
            Assert.AreEqual(testClass.Imaginary, 44.44);
        }
        [TestMethod]
        public void ComplexStringTesting2()
        {
            Action action = new Action(Action);

            Assert.ThrowsException<ClassException>(action);
        }
        private void Action()
        {
            string output = "7,5te +t i * 3,1";
            new MyComplex(output);
        }
        [TestMethod]
        public void CopyTesting()
        {
            var test1 = new MyComplex(55.89, 44.44);
            var test2 = test1.Copy();

            Assert.AreEqual(test1.Real, test2.Real);
            Assert.AreEqual(test1.Imaginary, test2.Imaginary);
        }
        [TestMethod]
        public void AdditionTesting()
        {
            var test1 = new MyComplex(3, 4);
            var test2 = new MyComplex(4, -1);
            var resulr = test1.Addition(test2);

            Assert.AreEqual(resulr.Real, 7);
            Assert.AreEqual(resulr.Imaginary, 3);
        }
        [TestMethod]
        public void MultiplyTesting()
        {
            var test1 = new MyComplex(3, 4);
            var test2 = new MyComplex(4, -1);
            var resulr = test1.Multiplication(test2);

            Assert.AreEqual(resulr.Real, 16);
            Assert.AreEqual(resulr.Imaginary, 13);
        }
        [TestMethod]
        public void SubtractionTesting()
        {
            var test1 = new MyComplex(3, 4);
            var test2 = new MyComplex(4, -1);
            var resulr = test1.Subtraction(test2);

            Assert.AreEqual(resulr.Real, -1);
            Assert.AreEqual(resulr.Imaginary, 5);
        }
        [TestMethod]
        public void DivisionTesting()
        {
            var test1 = new MyComplex(3, 4);
            var test2 = new MyComplex(4, -1);
            var resulr = test1.Division(test2);

            Assert.AreEqual(resulr.Real, 0.470588, 5);
            Assert.AreEqual(resulr.Imaginary, 1.117647, 5);
        }
        [TestMethod]
        public void SquareTesting()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Square();

            Assert.AreEqual(resulr.Real, -7);
            Assert.AreEqual(resulr.Imaginary, 24);
        }
        [TestMethod]
        public void ReverseTesting()
        {
            var test1 = new MyComplex(0, -3);
            var resulr = test1.Reverse();

            Assert.AreEqual(resulr.Real, 0);
            Assert.AreEqual(resulr.Imaginary, 0.333333, 5);
        }
        [TestMethod]
        public void MinusTesting()
        {
            var test1 = new MyComplex(0, 4);
            var resulr = test1.Minus();

            Assert.AreEqual(resulr.Real, 0);
            Assert.AreEqual(resulr.Imaginary, -4);
        }
        [TestMethod]
        public void AbsTesting()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Abs();

            Assert.AreEqual(resulr, 5);
        }
        [TestMethod]
        public void RadianTesting()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Radian();

            Assert.AreEqual(0.927295, resulr, 5);
        }
        [TestMethod]
        public void DegreeTesting()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Degree();

            Assert.AreEqual(53.1301, resulr, 4);
        }
        [TestMethod]
        public void PowTesting()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Pow(5);

            Assert.AreEqual(resulr.Real, -237, 4);
            Assert.AreEqual(resulr.Imaginary, -3116, 4);
        }
        [TestMethod]
        public void RootTesting()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Sqrt(3, 4);

            Assert.AreEqual(resulr.Real, 2.567133, 5);
            Assert.AreEqual(resulr.Imaginary, 2.142468, 5);
        }
        [TestMethod]
        public void EqualTesting1()
        {
            var test1 = new MyComplex(3, 4);
            var test2 = new MyComplex(4, -1);
            var resulr = test1.Equal(test2);

            Assert.IsFalse(resulr);
        }
        [TestMethod]
        public void EqualTesting2()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.Equal(test1);

            Assert.IsTrue(resulr);
        }
        [TestMethod]
        public void EqualTesting3()
        {
            var test1 = new MyComplex(3, 4);
            var test2 = new MyComplex(4, -1);
            var resulr = test1.NotEqual(test2);

            Assert.IsTrue(resulr);
        }
        [TestMethod]
        public void EqualTesting4()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.NotEqual(test1);

            Assert.IsFalse(resulr);
        }
        [TestMethod]
        public void GetNumberTesting1()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.GetRealNumber();

            Assert.AreEqual(resulr, 3);
        }
        [TestMethod]
        public void GetNumberTesting2()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.GetImaginaryNumber();

            Assert.AreEqual(resulr, 4);
        }
        [TestMethod]
        public void GetNumberTesting3()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.GetRealString();

            Assert.AreEqual(resulr, "3");
        }
        [TestMethod]
        public void GetNumberTesting4()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.GetImaginaryString();

            Assert.AreEqual(resulr, "4");
        }
        [TestMethod]
        public void GetNumberTesting5()
        {
            var test1 = new MyComplex(3, 4);
            var resulr = test1.GetString();

            Assert.AreEqual(resulr, "3 + i * 4");
        }

    }
    // 7 lab
   // [TestClass]
    public class UnitTestPNumber
    {
        [TestMethod]
        public void ConstructorTesting1()
        {
            double a = 1011.1011;
            int b = 2;
            int c = 4;

            double extend = 1011.1011;
            PNumber iP = new PNumber(a, b, c);
            double result = iP.GetPNumber();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructorTesting2()
        {
            double a = 1011.1010;
            int b = 2;
            int c = -1;

            double extend = 0.0;
            PNumber iP = new PNumber(a, b, c);
            double result = iP.GetPNumber();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructorTesting3()
        {
            double a = 1011.1010;
            int b = 2;
            int c = -1;

            double extend = 0.0;
            PNumber iP = new PNumber(a, b, c);
            double result = iP.GetPNumber();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructorTesting4()
        {
            double a = 1011.1010;
            int b = 1;
            int c = 4;

            double extend = 0.0;
            PNumber iP = new PNumber(a, b, c);
            double result = iP.GetPNumber();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructorTesting5()
        {
            string a = "ABC123,435DC";
            string b = "16";
            string c = "5";

            string extend = "ABC123,435D2";
            PNumber iP = new PNumber(a, b, c);
            string result = iP.GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructorTesting6()
        {
            string a = "ABC123,435DC";
            string b = "16";
            string c = "6";

            string extend = "0,0";
            PNumber iP = new PNumber(a, b, c);
            string result = iP.GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructorTesting7()
        {
            string a = "ABC123,435DC";
            string b = "12";
            string c = "5";

            string extend = "0,0";
            PNumber iP = new PNumber(a, b, c);
            string result = iP.GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ConstructoTestingr8()
        {
            string a = "abc123,435ac";
            string b = "12";
            string c = "5";

            string extend = "0,0";
            PNumber iP = new PNumber(a, b, c);
            string result = iP.GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void AdditionSimpleTesting1()
        {
            string a = "1110101,110101";
            string b = "2";
            string c = "6";
            string a1 = "111101,100001";
            string b1 = "2";
            string c1 = "6";

            string extend = "10110011,01011";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Addition(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void AdditionSimpleTesting2()
        {
            string a = "1837A,342B";
            string b = "15";
            string c = "4";
            string a1 = "34C01,DDA1";
            string b1 = "15";
            string c1 = "4";

            string extend = "4D07C,22C6";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Addition(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void AdditionDiffBaseNumberTesting()
        {
            string a = "1837A,342B";
            string b = "16";
            string c = "4";
            string a1 = "34C01,DDA1";
            string b1 = "15";
            string c1 = "4";

            string extend = "0,0";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Addition(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void AdditionDiffCNumberTesting()
        {
            string a = "1837A,342B";
            string b = "16";
            string c = "4";
            string a1 = "34C01,DDA1A";
            string b1 = "15";
            string c1 = "5";

            string extend = "0,0";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Addition(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void MultiplicationTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";
            string a1 = "34,34";
            string b1 = "15";
            string c1 = "2";

            string extend = "3C877,E8";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Multiplication(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void SubstractTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";
            string a1 = "34,34";
            string b1 = "15";
            string c1 = "2";

            string extend = "124D,DE";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Substraction(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void DivisionTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";
            string a1 = "34,34";
            string b1 = "15";
            string c1 = "2";

            string extend = "55,36";
            PNumber iP = new PNumber(a, b, c);
            PNumber iP1 = new PNumber(a1, b1, c1);
            string result = iP.Division(iP1).GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void ReversNumberTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";

            string extend = "0,0";
            PNumber iP = new PNumber(a, b, c);

            string result = iP.Revers().GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void SqrtTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";

            string extend = "157D924,6D";
            PNumber iP = new PNumber(a, b, c);

            string result = iP.Sqr().GetPString();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void SetGetBaseTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";

            int extend = 15;
            PNumber iP = new PNumber(a, b, c);

            iP.SetBaseNumber(2);
            int result = iP.GetBaseNumber();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void SetGetConcTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";

            int extend = 2;
            PNumber iP = new PNumber(a, b, c);

            iP.SetCorrectnessNumber(4);
            int result = iP.Get—orrectnessNumber();
            Assert.AreEqual(extend, result);
        }
        [TestMethod]
        public void SetBaseTesting()
        {
            string a = "1283,22";
            string b = "15";
            string c = "2";

            int extend = 16;
            PNumber iP = new PNumber(a, b, c);

            iP.SetBaseNumber(16);
            int result = iP.GetBaseNumber();
            Assert.AreEqual(extend, result);
        }
    }
    // 8 lab
   // [TestClass]
    public class UnitTestPNumberEditor
    {
        [TestMethod]
        public void ConstructorTesting()
        {
            double a = 1011.1011;
            int b = 2;
            int c = 4;
            PNumber pnum = new PNumber(a, b, c);

            PNumberEditor edit = new PNumberEditor(pnum);
            string expected = "1011,1011";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ConstructorTesting1()
        {
            PNumberEditor edit = new PNumberEditor();
            string expected = "0,0";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ConstructorTesting2()
        {
            PNumberEditor edit = new PNumberEditor(16, 0);
            string expected = "0,0";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ConstructorTesting3()
        {
            PNumberEditor edit = new PNumberEditor("16,16", 16, 2);
            string expected = "16,16";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ZeroTesting1()
        {
            PNumberEditor edit = new PNumberEditor();
            bool expected = true;
            bool result = edit.IsZero();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void AddTesting1()
        {
            PNumberEditor edit = new PNumberEditor("16,16", 16, 2);
            string expected = "-16,16";
            string result = edit.AddSign();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void AddTesting2()
        {
            PNumberEditor edit = new PNumberEditor("16,0", 16, 1);
            string expected = "163,0";
            string result = edit.Add(3);
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void AddTesting3()
        {
            PNumberEditor edit = new PNumberEditor("16,0", 16, 1);
            string expected = "160,0";
            string result = edit.AddZero();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void BackSpaceTesting1()
        {
            PNumberEditor edit = new PNumberEditor("16,3", 16, 1);
            string expected = "16,0";
            string result = edit.BackSpace();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ClearTesting1()
        {
            PNumberEditor edit = new PNumberEditor("16,3", 16, 1);
            string expected = "0,0";
            string result = edit.Clear();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void GetNumberTesting1()
        {
            PNumberEditor edit = new PNumberEditor("16,3", 16, 1);
            string expected = "16,3";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void GetNumberTesting2()
        {
            
            PNumber pnum = new PNumber(16.3, 16, 1);
            PNumberEditor edit = new PNumberEditor(pnum);

            PNumber result = edit.ReturnEditPnumber();
            Assert.AreEqual(pnum.GetPNumber(), result.GetPNumber());
        }
        [TestMethod]
        public void SetNumberTesting1()
        {
            PNumberEditor edit = new PNumberEditor("16,3", 16, 1);
            string expected = "124,5324";
            edit.SetNumber("124,5324");
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ConstructurTesting4()
        {
            PNumberEditor edit = new PNumberEditor(17, 1);
            string expected = "0,0";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ConstructurTesting5()
        {
            PNumberEditor edit = new PNumberEditor("16,3", 1, 1);
            string expected = "0,0";
            string result = edit.GetNumber();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ZeroTesting2()
        {
            PNumberEditor edit = new PNumberEditor("16,3", 16, 1);
            bool expected = false;
            bool result = edit.IsZero();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void AddTesting4()
        {
            PNumberEditor edit = new PNumberEditor("-16,3", 16, 1);
            string expected = "16,3";
            string result = edit.AddSign();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void AddTesting5()
        {
            PNumberEditor edit = new PNumberEditor("-16,3", 16, 1);
            string expected = "-16,3";
            string result = edit.Add(4);
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void AddTesting6()
        {
            PNumberEditor edit = new PNumberEditor("-16,3", 16, 1);
            string expected = "-16,3";
            string result = edit.AddZero();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void BackSpaceTestin2()
        {
            PNumberEditor edit = new PNumberEditor("-16,3345", 16, 4);
            string expected = "-16,334";
            string result = edit.BackSpace();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void ClearTesting2()
        {
            PNumberEditor edit = new PNumberEditor("0,0", 16, 1);
            string expected = "0,0";
            string result = edit.BackSpace();
            Assert.AreEqual(expected, result);
        }
        [TestMethod]
        public void SetNumberTesting2()
        {
            PNumberEditor edit = new PNumberEditor("110,0", 10, 1);
            string expected = "110,0";
            string result = edit.SetNumber("1A,2B");
            Assert.AreEqual(expected, result);
        }
    }
    // 9 lab
    //[TestClass]
    public class UnitTestFractionEditor
    {
        [TestMethod]
        public void InitTesting()
        {
            Fraction frac = new Fraction(3, 4);
            FractionEditor testClass = new FractionEditor(frac);
            string output = frac.ToString();
            Assert.AreEqual(output, testClass.ReadString());
        }
        [TestMethod]
        public void InitTesting1()
        {
            FractionEditor testClass = new FractionEditor();
            string output = "3/4";
            testClass.WriteString(output);
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void InitTesting2()
        {
            FractionEditor testClass = new FractionEditor();
            string output = "-16/3";
            testClass.WriteString(output);
            Assert.AreEqual(output, testClass.ReadString());
        }
        [TestMethod]
        public void WriteFractionTesting()
        {
            Fraction frac = new Fraction(3, 4);
            FractionEditor testClass = new FractionEditor();
            testClass.WriteFraction(frac);
            string output = frac.ToString();
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void ZeroTesting1()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("14/3");
            Assert.IsFalse(testClass.IsZero());
        }

        [TestMethod]
        public void ZeroTesting2()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("0/11");
            Assert.IsTrue(testClass.IsZero());
        }

        [TestMethod]
        public void MinusTesting1()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("3/4");
            testClass.Minus();
            string output = "-3/4";
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void MinusTesting2()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("-3/4");
            testClass.Minus();
            string output = "3/4";
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void AddTesting1()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("-3/4");
            testClass.AddNumber(4);
            string output = "-43/4";
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void AddTesting2()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("0/1");
            testClass.AddNumber(4);
            string output = "4/1";
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void DivisionSymbolTesting1()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("42/3");
            testClass.DivisionSymbol();
            string output = "42/3";
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void DivisionSymbolTesting2()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("42/34");
            testClass.DivisionSymbol();
            string output = "42/3";
            Assert.AreEqual(output, testClass.ReadString());
        }

        [TestMethod]
        public void ClearTesting()
        {
            FractionEditor testClass = new FractionEditor();
            testClass.WriteString("42/34");
            testClass.Clear();
            string output = "0/1";
            Assert.AreEqual(output, testClass.ReadString());
        }

    }
    // 10 lab
    //[TestClass]
    public class UnitTestComplexEditor
    {
        [TestMethod]
        public void InitTesting()
        {
            MyComplex pnum = new MyComplex(10.3, 0.8);
            ComplexEditor testClass = new ComplexEditor(pnum);
            string output = "10,3+i*0,8";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void InitTesting1()
        {
            ComplexEditor testClass = new ComplexEditor();
            string output = "10,3+i*0,8";
            testClass.WriteNumber(output);
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void InitTesting2()
        {
            ComplexEditor testClass = new ComplexEditor();
            string output = "-12,6-i*66,2";
            testClass.WriteNumber(output);
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void InitTesting3()
        {
            ComplexEditor testClass = new ComplexEditor();
            string output = "0,3+i*0,0";
            testClass.WriteNumber(output);
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void WriteComplexTesting()
        {
            MyComplex pnum = new MyComplex(10.3, 0.8);
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteComplex(pnum);
            string output = "10,3+i*0,8";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void ZeroTesting1()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("12,36+i*12,35");
            Assert.IsFalse(testClass.IsZero());
        }
        [TestMethod]
        public void ZeroTesting2()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("0,+i*0,");
            Assert.IsTrue(testClass.IsZero());
        }
        [TestMethod]
        public void MinusTesting1()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("12,36+i*12,35");
            testClass.ToggleMinus();
            string output = "-12,36+i*12,35";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void MinusTesting2()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("-12,36+i*12,35");
            testClass.ToggleMinus();
            string output = "12,36+i*12,35";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void AddTesting1()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("0,36+i*1,4");
            testClass.AddNumber(4);
            string output = "4,36+i*1,4";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void AddTesting2()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("-25,6-i*44,44");
            testClass.AddNumber(0);
            string output = "-250,6-i*44,44";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void DelTesting1()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("0,4+i*44,44");
            testClass.DelNumber();
            string output = "0,4+i*44,44";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void DelTesting2()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("55,55-i*3,3");
            testClass.ToggleMode();
            testClass.DelNumber();
            string output = "55,55-i*0,3";
            Assert.AreEqual(output, testClass.ReadNumber());
        }
        [TestMethod]
        public void ClearTesting()
        {
            ComplexEditor testClass = new ComplexEditor();
            testClass.WriteNumber("55,55-i*3,3");
            testClass.Clear();
            string output = "0,+i*0,";
            Assert.AreEqual(output, testClass.ReadNumber());
        }

    }
    // 11 lab
    //[TestClass]
    public class UnitTestTMemory
    {
        [TestMethod]
        public void ComplexTesting()
        {
            TSet<MyComplex> tset1 = new TSet<MyComplex>();

            tset1.Add(new MyComplex(66.99, 44.44));
            tset1.Add(new MyComplex(66.99, 44.44));
            tset1.Add(new MyComplex(66.99, 44.44));

            Assert.AreEqual(tset1.ElementAt(0).Real, 66.99);
            Assert.AreEqual(tset1.ElementAt(1).Real, 66.99);
            Assert.AreEqual(tset1.ElementAt(2).Real, 66.99);

            Assert.AreEqual(tset1.ElementAt(0).Imaginary, 44.44);
            Assert.AreEqual(tset1.ElementAt(1).Imaginary, 44.44);
            Assert.AreEqual(tset1.ElementAt(2).Imaginary, 44.44);
        }
        [TestMethod]
        public void PNumberTesting()
        {
            TSet<PNumber> tset1 = new TSet<PNumber>();

            double a = 1011.1011;
            int b = 2;
            int c = 4;

            double extend = 1011.1011;

            tset1.Add(new PNumber(a,b,c));
            tset1.Add(new PNumber(a, b, c));
            tset1.Add(new PNumber(a, b, c));
            Assert.AreEqual(tset1.ElementAt(0).GetPNumber(), extend);
            Assert.AreEqual(tset1.ElementAt(1).GetPNumber(), extend);
            Assert.AreEqual(tset1.ElementAt(2).GetPNumber(), extend);
        }
        [TestMethod]
        public void FractionTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            Assert.AreEqual(tset1.ElementAt(0), new Fraction(1, 2));
            Assert.AreEqual(tset1.ElementAt(1), new Fraction(2, 3));
            Assert.AreEqual(tset1.ElementAt(2), new Fraction(3, 4));
        }
        [TestMethod]
        public void ClearTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            Assert.AreEqual(tset1.Show(), "1/2 2/3 3/4 ");

            tset1.Clear();
            Assert.AreEqual(tset1.Show(), "");
        }
        [TestMethod]
        public void RemoveTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            tset1.Remove(new Fraction(2, 3));
            Assert.AreEqual(tset1.Show(), "1/2 3/4 ");
        }
        [TestMethod]
        public void IsClearTesting1()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.IsClear(), false);
        }
        [TestMethod]
        public void IsClearTesting2()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            tset1.Clear();

            Assert.AreEqual(tset1.IsClear(), true);
        }
        [TestMethod]
        public void ContainsTesting1()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.Contains(new Fraction(2, 3)), true);
        }
        [TestMethod]
        public void ContainsTesting2()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.Contains(new Fraction(2, 30)), false);
        }
        [TestMethod]
        public void UnionTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            TSet<Fraction> tset2 = new TSet<Fraction>();
            tset2.Add(new Fraction(1, 2));
            tset2.Add(new Fraction(2, 3));
            tset2.Add(new Fraction(5, 5));


            Assert.AreEqual(tset1.Union(tset2).Show(), "1/2 2/3 3/4 1/1 ");
        }
        [TestMethod]
        public void ExceptTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            TSet<Fraction> tset2 = new TSet<Fraction>();
            tset2.Add(new Fraction(1, 2));
            tset2.Add(new Fraction(2, 3));
            tset2.Add(new Fraction(5, 5));


            Assert.AreEqual(tset1.Except(tset2).Show(), "3/4 ");
        }
        [TestMethod]
        public void IntersectTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            TSet<Fraction> tset2 = new TSet<Fraction>();
            tset2.Add(new Fraction(1, 2));
            tset2.Add(new Fraction(2, 3));
            tset2.Add(new Fraction(5, 5));


            Assert.AreEqual(tset1.Intersect(tset2).Show(), "1/2 2/3 ");
        }
        [TestMethod]
        public void CountTesting()
        {
            TSet<Fraction> tset1 = new TSet<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.Count(), 3);
        }

    }
    // 12 lab
   //[TestClass]
    public class UnitTestProcessor
    {
        [TestMethod]
        public void OperationsFractionTesting()
        {
            Processor<Fraction> processor = new Processor<Fraction>(new Fraction(1, 3), new Fraction(1, 3));
            processor.OperationSet(1);
            processor.OperationRun();
            var otvet = new Fraction(2, 3);
            Assert.AreEqual(otvet.Denominator, processor.Lop_Res.Denominator);
            Assert.AreEqual(otvet.Numerator, processor.Lop_Res.Numerator);

            processor.OperationSet(2);
            processor.OperationRun();
            otvet = new Fraction(1, 3);
            Assert.AreEqual(otvet.Denominator, processor.Lop_Res.Denominator);
            Assert.AreEqual(otvet.Numerator, processor.Lop_Res.Numerator);

            processor.OperationSet(3);
            processor.OperationRun();
            otvet = new Fraction(1, 9);
            Assert.AreEqual(otvet.Denominator, processor.Lop_Res.Denominator);
            Assert.AreEqual(otvet.Numerator, processor.Lop_Res.Numerator);

            processor.OperationSet(4);
            processor.OperationRun();
            otvet = new Fraction(1, 3);
            Assert.AreEqual(otvet.Denominator, processor.Lop_Res.Denominator);
            Assert.AreEqual(otvet.Numerator, processor.Lop_Res.Numerator);
        }
        [TestMethod]
        public void FunctionsFractionTesting()
        {
            Processor<Fraction> processor = new Processor<Fraction>(new Fraction(1, 3), new Fraction(1, 3));
            processor.FunctionSet(1);
            processor.FunctionRun();
            var otvet = new Fraction(3, 1);
            Assert.AreEqual(otvet.Denominator, processor.Rop.Denominator);
            Assert.AreEqual(otvet.Numerator, processor.Rop.Numerator);
            processor.FunctionSet(2);
            processor.FunctionRun();
            otvet = new Fraction(9, 1);
            Assert.AreEqual(otvet.Denominator, processor.Rop.Denominator);
            Assert.AreEqual(otvet.Numerator, processor.Rop.Numerator);
        }
        [TestMethod]
        public void OperationsIntTesting()
        {
            Processor<int> processor = new Processor<int>(2, 5);
            processor.OperationSet(1);
            processor.OperationRun();
            Assert.AreEqual(7, processor.Lop_Res);
            processor.OperationSet(2);
            processor.OperationRun();
            Assert.AreEqual(2, processor.Lop_Res);
            processor.OperationSet(3);
            processor.OperationRun();
            Assert.AreEqual(10, processor.Lop_Res);
            processor.OperationSet(4);
            processor.OperationRun();
            Assert.AreEqual(2, processor.Lop_Res);
        }
        [TestMethod]
        public void FunctionsIntTesting()
        {
            Processor<int> processor = new Processor<int>(2, 1);
            processor.FunctionSet(1);
            processor.FunctionRun();
            Assert.AreEqual(1, processor.Rop);
            processor.FunctionSet(2);
            processor.FunctionRun();
            Assert.AreEqual(1, processor.Rop);
        }
    }
    // 13 lab
   // [TestClass]
    public class UnitTestPlenty
    {
        [TestMethod]
        public void OperationsFractionTesting()
        {
            Plenty<Fraction> obj = new Plenty<Fraction>();
            obj.Add(new Fraction(1, 2));
            obj.Add(new Fraction(2, 3));
            obj.Add(new Fraction(3, 4));
            Assert.AreEqual(obj.ElementAt(0), new Fraction(1, 2));
            Assert.AreEqual(obj.ElementAt(1), new Fraction(2, 3));
            Assert.AreEqual(obj.ElementAt(2), new Fraction(3, 4));
        }

        [TestMethod]
        public void ClearTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            Assert.AreEqual(tset1.Show(), "1/2 2/3 3/4 ");

            tset1.Clear();
            Assert.AreEqual(tset1.Show(), "");
        }

        [TestMethod]
        public void RemoveTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            tset1.Remove(new Fraction(2, 3));
            Assert.AreEqual(tset1.Show(), "1/2 3/4 ");
        }

        [TestMethod]
        public void IsClearTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.IsClear(), false);
        }

        [TestMethod]
        public void IsClearTesting2()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));
            tset1.Clear();

            Assert.AreEqual(tset1.IsClear(), true);
        }

        [TestMethod]
        public void ContainsTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.Contains(new Fraction(2, 3)), true);
        }

        [TestMethod]
        public void ContainsTesting2()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.Contains(new Fraction(2, 30)), false);
        }

        [TestMethod]
        public void UnionTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Plenty<Fraction> tset2 = new Plenty<Fraction>();
            tset2.Add(new Fraction(1, 2));
            tset2.Add(new Fraction(2, 3));
            tset2.Add(new Fraction(5, 5));


            Assert.AreEqual(tset1.Union(tset2).Show(), "1/2 2/3 3/4 1/1 ");
        }

        [TestMethod]
        public void ExceptTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Plenty<Fraction> tset2 = new Plenty<Fraction>();
            tset2.Add(new Fraction(1, 2));
            tset2.Add(new Fraction(2, 3));
            tset2.Add(new Fraction(5, 5));


            Assert.AreEqual(tset1.Except(tset2).Show(), "3/4 ");
        }

        [TestMethod]
        public void IntersectTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Plenty<Fraction> tset2 = new Plenty<Fraction>();
            tset2.Add(new Fraction(1, 2));
            tset2.Add(new Fraction(2, 3));
            tset2.Add(new Fraction(5, 5));


            Assert.AreEqual(tset1.Intersect(tset2).Show(), "1/2 2/3 ");
        }

        [TestMethod]
        public void CountTesting()
        {
            Plenty<Fraction> tset1 = new Plenty<Fraction>();
            tset1.Add(new Fraction(1, 2));
            tset1.Add(new Fraction(2, 3));
            tset1.Add(new Fraction(3, 4));

            Assert.AreEqual(tset1.Count(), 3);
        }
    }
    // 14 lab
    [TestClass]
    public class UnitTestPolynom
    {
        [TestMethod]
        public void AddTesting()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(1, 0));
            Assert.AreEqual(objPoly.Show(), "1x^0");
        }
        [TestMethod]
        public void AddTesting2()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(1, 0));
            objPoly.Members.Add(new Member(1, 1));
            Assert.AreEqual(objPoly.Show(), "1x^1+1x^0");
        }
        [TestMethod]
        public void MulTesting1()
        {
            Polynom objPoly1 = new Polynom();
            Polynom objPoly2 = new Polynom();
            objPoly1.Members.Add(new Member(1, 0));
            objPoly1.Members.Add(new Member(1, 1));
            objPoly2.Members.Add(new Member(1, 0));
            objPoly2.Members.Add(new Member(1, 1));

            Polynom addpoly = objPoly1.Add(objPoly2);
            addpoly = objPoly1.Mul(objPoly2);

            Assert.AreEqual(addpoly.Show(), "1x^2+2x^1+1x^0");
        }
        [TestMethod]
        public void MulTesting2()
        {
            Polynom objPoly = new Polynom();
            Polynom newtpoly = new Polynom();
            objPoly.Members.Add(new Member(1, 0));
            objPoly.Members.Add(new Member(1, 2));
            newtpoly.Members.Add(new Member(2, 0));
            newtpoly.Members.Add(new Member(1, 1));

            Polynom addpoly = objPoly.Add(newtpoly);
            addpoly = objPoly.Mul(newtpoly);

            Assert.AreEqual(addpoly.Show(), "1x^3+2x^2+1x^1+2x^0");
        }
        [TestMethod]
        public void ClearTesting()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(1, 0));
            objPoly.Clear();
            Assert.AreEqual(objPoly.Show(), "");
        }
        [TestMethod]
        public void CalcTesting1()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(1, 2));
            objPoly.Members.Add(new Member(3, 3));
            objPoly.Members.Add(new Member(4, 2));

            Assert.AreEqual(objPoly.Calculate(2), 44);
        }
        [TestMethod]
        public void CalcTesting2()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(1, 2));
            objPoly.Members.Add(new Member(3, 0));
            objPoly.Members.Add(new Member(4, 0));

            Assert.AreEqual(objPoly.Calculate(2), 11);
        }
        [TestMethod]
        public void EqualsTesting1()
        {
            Polynom objPoly1 = new Polynom();
            objPoly1.Members.Add(new Member(1, 2));
            Polynom objPoly2 = new Polynom();
            objPoly2.Members.Add(new Member(1, 2));
            Assert.AreEqual(objPoly1.Equals(objPoly2), true);
        }
        [TestMethod]
        public void EqualsTesting2()
        {
            Polynom objPoly1 = new Polynom();
            objPoly1.Members.Add(new Member(1, 2));
            Polynom objPoly2 = new Polynom();
            objPoly2.Members.Add(new Member(0, 2));
            Assert.AreEqual(objPoly1.Equals(objPoly2), false);
        }
        [TestMethod]
        public void DiffTesting1()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(1, 3));
            Assert.AreEqual(objPoly.Diff().Show(), "3x^2");
        }
        [TestMethod]
        public void ElementAtTesting()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(11, 11));
            objPoly.Members.Add(new Member(22, 22));

            Assert.AreEqual(new System.Tuple<int, int>(11, 11), objPoly.ElementAt(1));
        }
        [TestMethod]
        public void RetDegreeTesting()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(11, 11));
            objPoly.Members.Add(new Member(22, 22));

            Assert.AreEqual(objPoly.RetDegree(), 22);
        }
        [TestMethod]
        public void RetCoeffTesting1()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(11, 11));
            objPoly.Members.Add(new Member(22, 33));

            Assert.AreEqual(objPoly.RetCoeff(33), 22);
        }
        [TestMethod]
        public void RetCoeffTesting2()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(11, 11));
            objPoly.Members.Add(new Member(22, 33));
            objPoly.Members.Add(new Member(20, 33));

            Assert.AreEqual(objPoly.RetCoeff(33), 42);
        }
        [TestMethod]
        public void RevTesting()
        {
            Polynom objPoly = new Polynom();
            objPoly.Members.Add(new Member(11, 1));
            objPoly.Members.Add(new Member(22, 3));
            objPoly.Members.Add(new Member(20, 2));

            Assert.AreEqual(objPoly.Rev().Show(), "-22x^3-20x^2-11x^1");
        }
    }


    //13 lab new
}