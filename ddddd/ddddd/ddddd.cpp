#include <ctest.h>
#include <libconverter/converter.h>
#define UI_FILE ".. ../src/converter/Unit_converter.glade"

CTEST(Conversion, length_conversion)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        int position = 0;

        std::vector<double> real_elements;

        coeff_param(real_elements, input, position, 0);

        std::vector<double> elements
            = { input / 1e+0,
               input / 1e+0 / 1e+3,
               input / 1e+0 / 1e+3 / 1e-5,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3 / 1e-3,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3 / 1e-3
                       / 1609350000000e+0,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3 / 1e-3
                       / 1609350000000e+0 / 5681797e-10,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3 / 1e-3
                       / 1609350000000e+0 / 5681797e-10 / 3333333333e-10,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3 / 1e-3
                       / 1609350000000e+0 / 5681797e-10 / 3333333333e-10
                       / 833333333e-10,
               input / 1e+0 / 1e+3 / 1e-5 / 1e-1 / 1e-3 / 1e-3
                       / 1609350000000e+0 / 5681797e-10 / 3333333333e-10
                       / 833333333e-10 / 3724669291e+8 };

        for (int j = 0; j < 10; j++) {
            ASSERT_DBL_NEAR(elements[j], real_elements[j]);
        }
    }
}

CTEST(Conversion, temp_conversion)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        int position = 0;
        std::vector<double> real_elements;
        std::stringstream str;
        str << input;
        const char* input_char = str.str().c_str();
        temp(real_elements, input_char, position);

        std::vector<double> elements
            = { input, input + 273.15, (input * 1.8) + 32 };

        for (int j = 0; j < 2; j++) {
            ASSERT_DBL_NEAR(elements[j], real_elements[j]);
        }
    }
}

CTEST(Conversion, volume_conversion)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        int position = 0;

        std::vector<double> real_elements;

        coeff_param(real_elements, input, position, 3);

        std::vector<double> elements
            = { input / 1e+0,
               input / 1e+0 / 1e+9,
               input / 1e+0 / 1e+9 / 9999999999e-25,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3 / 5e-1,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3 / 5e-1
                       / 3333333333e-10,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3 / 5e-1
                       / 3333333333e-10 / 8456579974e+6,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3 / 5e-1
                       / 3333333333e-10 / 8456579974e+6 / 1834265453e-19,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3 / 5e-1
                       / 3333333333e-10 / 8456579974e+6 / 1834265453e-19
                       / 37037037e-9,
               input / 1e+0 / 1e+9 / 9999999999e-25 / 1e-3 / 1e+6 / 1e-3
                       / 378541e-3 / 25e-2 / 5e-1 / 5e-1 / 125e-3 / 5e-1
                       / 3333333333e-10 / 8456579974e+6 / 1834265453e-19
                       / 37037037e-9 / 5787037e-10 };

        for (int j = 0; j < 16; j++) {
            ASSERT_DBL_NEAR(elements[j], real_elements[j]);
        }
    }
}

CTEST(Conversion, area_conversion)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        int position = 0;

        std::vector<double> real_elements;

        coeff_param(real_elements, input, position, 2);

        std::vector<double> elements = {
                input / 1e+0,
                input / 1e+0 / 1e+6,
                input / 1e+0 / 1e+6 / 1e-10,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6 / 1e+16,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6 / 1e+16 / 258999e-3,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6 / 1e+16 / 258999e-3
                        / 3228303429e-16,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6 / 1e+16 / 258999e-3
                        / 3228303429e-1 / 1111111111e-10,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6 / 1e+16 / 258999e-3
                        / 3228303429e-1 / 1111111111e-10 / 69444444e-10,
                input / 1e+0 / 1e+6 / 1e-10 / 1e-2 / 1e-6 / 1e+16 / 258999e-3
                        / 3228303429e-1 / 1111111111e-10 / 69444444e-10
                        / 6272640e+0 };

        for (int j = 0; j < 10; j++) {
            ASSERT_DBL_NEAR(elements[j], real_elements[j]);
        }
    }
}

CTEST(Conversion, time_conversion)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        int position = 0;

        std::vector<double> real_elements;

        coeff_param(real_elements, input, position, 5);

        std::vector<double> elements = {
                input / 1e+0,
                input / 1e+0 / 1e-3,
                input / 1e+0 / 1e-3 / 1e-3,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3 / 6e+13,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3 / 6e+13 / 6e+1,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3 / 6e+13 / 6e+1 / 24e+0,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3 / 6e+13 / 6e+1 / 24e+0
                        / 7e+0,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3 / 6e+13 / 6e+1 / 24e+0
                        / 7e+0 / 4e+0,
                input / 1e+0 / 1e-3 / 1e-3 / 1e-3 / 1e-3 / 6e+13 / 6e+1 / 24e+0
                        / 7e+0 / 4e+0 / 12e+0 };

        for (int j = 0; j < 10; j++) {
            ASSERT_DBL_NEAR(elements[j], real_elements[j]);
        }
    }
}

CTEST(Conversion, weight_conversion)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        int position = 0;

        std::vector<double> real_elements;

        coeff_param(real_elements, input, position, 4);

        std::vector<double> elements
            = { input / 1e+0,
               input / 1e+0 / 1e-3,
               input / 1e+0 / 1e-3 / 1e-3,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9 / 101604608e-8,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9 / 101604608e-8
                       / 8928571429e-10,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9 / 101604608e-8
                       / 8928571429e-10 / 5e-4,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9 / 101604608e-8
                       / 8928571429e-10 / 5e-4 / 625e-4,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9 / 101604608e-8
                       / 8928571429e-10 / 5e-4 / 625e-4 / 70547981e-10,
               input / 1e+0 / 1e-3 / 1e-3 / 1e+9 / 101604608e-8
                       / 8928571429e-10 / 5e-4 / 625e-4 / 70547981e-10
                       / 8302700999e-33 };

        for (int j = 0; j < 9; j++) {
            ASSERT_DBL_NEAR(elements[j], real_elements[j]);
        }
    }
}

CTEST(Check, check_strock_false)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        std::string str = "abc";
        str += std::to_string(input);
        char i = check_strock(str);
        ASSERT_EQUAL(0, i);
    }
}

CTEST(Check, check_strock_true)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        ASSERT_EQUAL(1, input);
    }
}