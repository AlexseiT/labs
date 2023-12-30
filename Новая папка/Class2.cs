using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using labs;
using _5lab;
using System.Threading.Tasks;

namespace metriclab
{
    // 13 lab metric Вероятностное моделирование метрических характеристик программ
    public class ProgrammSimulator
    {
        private Random _randomNumber;
        private int[] _dictSizes;
        public ProgrammSimulator(int[] dict)
        {
            _randomNumber = new Random();
            _dictSizes = dict;
        }
        public ProgrammSimulator()
        {
            _randomNumber = new Random();
            int[] dict = { 16, 32, 64, 128 };
            _dictSizes = dict;
        }
        public List<string> GenerateVocabulary(int dictionarySize)
        {
            var vocabulary = new List<string>();
            for (int i = 0; i < dictionarySize; i++)
            {
                vocabulary.Add("op" + i);
                vocabulary.Add("operand" + i);
            }
            return vocabulary;
        }
        public Tuple<List<string>, int> SimulateProgramGeneration(int dict)
        {
            var vocabulary = GenerateVocabulary(dict);
            var program = new List<string>();

            while (vocabulary.Count > 0)
            {
                int index = _randomNumber.Next(vocabulary.Count);
                string selected = vocabulary[index];
                program.Add(selected);
                vocabulary.RemoveAt(index);
            }

            int programLength = program.Count;
            return Tuple.Create(program, programLength);
        }
        public void ProgrammCalc()
        {
            foreach (int dict in _dictSizes)
            {
                var result = SimulateProgramGeneration(dict);
                var program = result.Item1;
                int programLength = result.Item2;

                double expectedLength = 0.9 * dict * Math.Log2(dict);
                double variance = (Math.PI * Math.PI * dict * dict) / 6;
                double standardDeviation = Math.Sqrt(variance);
                double relativeError = 1.0 / (2 * Math.Log2(dict));

                Console.WriteLine($"1) размер словаря (n): {dict}");
                Console.WriteLine($"2) длина программы (L): {programLength}");
                Console.WriteLine($"3) теоретическая ожидаемая продолжительность программы: {expectedLength:F2}");
                Console.WriteLine($"4) разница в продолжительности программы: {variance:F2}");
                Console.WriteLine($"5) стандартное отклонение длины программы: {standardDeviation:F2}");
                Console.WriteLine($"6) относительная ожидаемая погрешность: {relativeError:F2}\n");
            }
        }
    }
    // 14 lab metric Вычисление метрических характеристик реализаций алгоритмов
    public class MetricCharacteristics{

        private int[] _dimensional1 = { 5, 3, 9, 1, 7 };
        private int[,] _dimensional2 = { { 5, 3, 9 }, { 1, 7, 2 } };
        private int _target = 1;

        public MetricCharacteristics()
        {

        }
        public MetricCharacteristics(int[] dimensional1, int[,] dimensional2, int target)
        {
        _dimensional1 = dimensional1;
        _dimensional2 = dimensional2;
        _target = target;
    }
        public static (int, int) Min(int[] array)
        {
            int minValue = int.MaxValue;
            int minIndex = -1;

            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] < minValue)
                {
                    minValue = array[i];
                    minIndex = i;
                }
            }
            return (minValue, minIndex);
        }
        public static void SortBubble(int[] array)
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                for (int j = 0; j < array.Length - 1 - i; j++)
                {
                    if (array[j] > array[j + 1])
                    {
                        int temp = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = temp;
                    }
                }
            }
        }
        public static int SearchBinary(int[] sortedArray, int target)
        {
            int left = 0;
            int right = sortedArray.Length - 1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if (sortedArray[mid] == target)
                    return mid;

                if (sortedArray[mid] < target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }

            return -1;
        }
        public static (int, int, int) MinMatrix(int[,] array)
        {
            int minValue = int.MaxValue;
            int minRow = -1;
            int minCol = -1;

            for (int row = 0; row < array.GetLength(0); row++)
            {
                for (int col = 0; col < array.GetLength(1); col++)
                {
                    if (array[row, col] < minValue)
                    {
                        minValue = array[row, col];
                        minRow = row;
                        minCol = col;
                    }
                }
            }

            return (minValue, minRow, minCol);
        }
        public static void ReverseArray(int[] array)
        {
            Array.Reverse(array);
        }
        public static void RotateArrayLeft(int[] array, int positions)
        {
            int n = array.Length;
            positions %= n;

            int[] temp = new int[n];

            for (int i = 0; i < n; i++)
            {
                int newPosition = (i - positions + n) % n;
                temp[newPosition] = array[i];
            }

            for (int i = 0; i < n; i++)
            {
                array[i] = temp[i];
            }
        }
        public static void ReplaceAll(int[] array, int oldValue, int newValue)
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] == oldValue)
                {
                    array[i] = newValue;
                }
            }
        }
        public static void Calculate(string taskName, int[] array, string[] operands, string[] operators)
        {
            int etaStar2 = operands.Length + operators.Length;
            int eta1 = operators.Length;
            int eta2 = operands.Length;

            var vocabulary = new Dictionary<int, int>();
            foreach (int item in array)
            {
                if (!vocabulary.ContainsKey(item))
                {
                    vocabulary[item] = 1;
                }
                else
                {
                    vocabulary[item] += 1;
                }
            }

            int N1 = 0;
            int N2 = array.Length;
            foreach (int operand in vocabulary.Keys)
            {
                N1 += vocabulary[operand];
            }

            int N = eta1 + eta2;
            double NHat = etaStar2 * Math.Log(2 + etaStar2, 2);
            double VStar = (2 + etaStar2) * Math.Log(2 + etaStar2, 2);
            double V = VStar * N * Math.Log(2, Math.E);
            double L = V / VStar;
            double LHat = (2 / 3.0) * (N1 + N2) * Math.Log(2 + (N1 + N2) / 2, 2);
            double I = (2 / 3.0) * (N1 / N2) * (eta1 + eta2) * Math.Log(2 + (N1 / N2) * (eta1 + eta2), 2);

            double T1Hat = V / VStar;
            double T2Hat = (Math.Log(Math.Log(2 + eta1, 2) * Math.Log(2 + eta2, 2), 2) / 2);
            double T3Hat = Math.Log(2 + eta1, 2) * Math.Log(2 + eta2, 2) * N1 * N2 / 2;

            Console.WriteLine("метрики для " + taskName + ":");
            Console.WriteLine("------------------------------");
            Console.WriteLine($"значение (n*2): {etaStar2}");
            Console.WriteLine($"значение (n1): {eta1}");
            Console.WriteLine($"значение (n2): {eta2}");
            Console.WriteLine($"объем словарного запаса (n): {vocabulary.Count}");
            Console.WriteLine("------------------------------");
            Console.WriteLine($"значение (N1): {N1}");
            Console.WriteLine($"значение (N2): {N2}");
            Console.WriteLine($"значение (N): {N}");
            Console.WriteLine($"значение (N^): {NHat}");
            Console.WriteLine("------------------------------");
            Console.WriteLine($"значение (V*): {VStar}");
            Console.WriteLine($"значение (V): {V}");
            Console.WriteLine("------------------------------");
            Console.WriteLine($"значение (L): {L}");
            Console.WriteLine($"значение (L)^: {LHat}");
            Console.WriteLine("------------------------------");
            Console.WriteLine($"значение (I): {I}");
            Console.WriteLine("------------------------------");
            Console.WriteLine($"значение (T^1): {T1Hat}");
            Console.WriteLine($"значение (T^2): {T2Hat}");
            Console.WriteLine($"значение (T^3): {T3Hat}");
            Console.WriteLine("------------------------------");
            Console.WriteLine();

            
            double lambda1 = L * V;// Вычисление уровня программы через потенциальный объем (λ1)

            Console.WriteLine($"(lambda)1 для {taskName} = {lambda1}");
        }
        public void ProgrammCalc()
        {
            // Выполнение задачи 1
            var minResult = Min(_dimensional1);
            Console.WriteLine($"Минимальное значение в одномерном массиве: {minResult.Item1}");
            Console.WriteLine($"Индекс минимального значения: {minResult.Item2}");
            string[] task1Operands = { "minValue", "minIndex", "array", "i" };
            string[] task1Operators = { "for", "if" };
            Calculate("Задачи 1", _dimensional1, task1Operands, task1Operators);
            // Выполнение задачи 2
            SortBubble(_dimensional1);
            Console.WriteLine("Сортировка одномерного массива:");
            foreach (var num in _dimensional1)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine();
            string[] task2Operands = { "temp", "i", "j" };
            string[] task2Operators = { "for" };
            Calculate("Задачи 2", _dimensional1, task2Operands, task2Operators);
            // Выполнение задачи 3
            int binarySearchResult = SearchBinary(_dimensional1, _target);
            if (binarySearchResult != -1)
            {
                Console.WriteLine($"Нашел {_target} по индексу {binarySearchResult}");
            }
            else
            {
                Console.WriteLine($"{_target} не найден в одномерном массиве");
            }
            string[] task3Operands = { "left", "right", "mid" };
            string[] task3Operators = { "if", "while" };
            Calculate("Задачи 3", _dimensional1, task3Operands, task3Operators);
            // Выполнение задачи 4
            var minResult2D = MinMatrix(_dimensional2);
            Console.WriteLine($"Минимальное значение в двумерном массиве: {minResult2D.Item1}");
            Console.WriteLine($"Строка минимального значения: {minResult2D.Item2}");
            Console.WriteLine($"Столбец с минимальным значением: {minResult2D.Item3}");
            string[] task4Operands = { "minValue", "minRow", "minCol", "array", "row", "col" };
            string[] task4Operators = { "if", "for", "nested for" };
            Calculate("Задачи 4", _dimensional1, task4Operands, task4Operators);
            // Выполнение задачи 5
            ReverseArray(_dimensional1);
            Console.WriteLine("Обратный одномерный массив:");
            foreach (var num in _dimensional1)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine();
            string[] task5Operands = { "temp", "i", "j" };
            string[] task5Operators = { "for" };
            Calculate("Задачи 5", _dimensional1, task5Operands, task5Operators);
            // Выполнение задачи 6
            int positions = 2;
            RotateArrayLeft(_dimensional1, positions);
            Console.WriteLine($"Вращающийся одномерный массив {positions} позиции слева:");
            foreach (var num in _dimensional1)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine();
            string[] task6Operands = { "positions", "n", "temp", "i", "newPosition" };
            string[] task6Operators = { "for" };
            Calculate("Задачи 6", _dimensional1, task6Operands, task6Operators);
            // Выполнение задачи 7
            int oldValue = 3;
            int newValue = 8;
            ReplaceAll(_dimensional1, oldValue, newValue);
            Console.WriteLine($"Одномерный массив со всеми вхождениями {oldValue} заменен на {newValue}:");
            foreach (var num in _dimensional1)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine();
            string[] task7Operands = { "oldValue", "newValue", "i" };
            string[] task7Operators = { "for", "if" };
            Calculate("Задачи 7", _dimensional1, task7Operands, task7Operators);
        }

    }
    // 15 lab metric Порядок расчета метрических характеристик ПС (Часть 1)
    public class MetricCharacteristicsPS
    {
        private int[] _val = { 300, 400, 512 };
        private int _programistsNumber = 5;
        private int _assemblerCommands = 20;
        public MetricCharacteristicsPS()
        {

        }
        public MetricCharacteristicsPS(int [] val, int programistsNumber, int assemblerCommands)
        {
            _val = val;
            _programistsNumber = programistsNumber;
            _assemblerCommands = assemblerCommands;
        }
        public void ProgrammCalc()
        {
            foreach (int eta2 in _val)
            {
                int i = 0;
                double totalModules = 0;
                double k = eta2 / 8;

                if (k > 8)
                {
                    i = 1;
                    while (k > 8)
                    {
                        k /= 8;
                        i++;
                    }
                    totalModules = k * Math.Pow(8, i);
                }
                else
                {
                    totalModules = eta2;
                }

                double N = Math.Pow(2, totalModules);
                double V = N * eta2;
                double P = N * Math.Log(eta2, 2) / 8;

                double Tk = V / (_programistsNumber * _assemblerCommands);
                double tau = 0.5 * Tk;
                double B = tau / Tk;

                double t_n = Math.Exp(-B);

                Console.WriteLine($"метрические характеристики для eta_2 = {eta2}:");
                Console.WriteLine("-----------------------------------------------");
                Console.WriteLine($"1) число уровней иерархии: {i}");
                Console.WriteLine($"2) общее число модулей в ПС: {totalModules}");
                Console.WriteLine($"3) длина N программы: {N}");
                Console.WriteLine($"5) объем V ПС: {V}");
                Console.WriteLine($"6) длина ПС в количестве команд ассемблера P: {P}");
                Console.WriteLine($"7) календарное время программирования Tk: {Tk}");
                Console.WriteLine($"8) начальное количество ошибок B: {B}");
                Console.WriteLine($"9) начальная надежность ПС tн: {t_n}");
            }
        }
    }
}
