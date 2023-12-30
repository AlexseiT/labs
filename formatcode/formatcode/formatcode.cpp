void temp(
        vector<double>& elements,
        const char* input_char,
        int position_of_element)
{
    string str = input_char;
    if (check_strock(str) == 1 && !str.empty()) {
        double input_element = stod(str);
        elements.resize(3);
        switch (position_of_element) {
        case 0: {
            elements[0] = input_element;
            elements[1] = Kelvin_Celsius(input_element, false);
            elements[2] = In_Fahrenheit(input_element, false);
            break;
        }
        case 1: {
            elements[0] = Kelvin_Celsius(input_element, true);
            elements[1] = input_element;
            elements[2] = In_Fahrenheit(input_element, true);
            break;
        }
        case 2: {
            elements[0] = From_Fahrenheit(input_element, false);
            ;
            elements[1] = From_Fahrenheit(input_element, true);
            elements[2] = input_element;
            break;
        }
        }
    }
}

CTEST(Check, check_strock_true)
{
    for (double input = 0.01; input <= 5; input = input + 0.01) {
        std::string str;
        str += std::to_string(input);
        char i = check_strock(str);
        ASSERT_EQUAL(1, i);
        str.clear()
    }
}
