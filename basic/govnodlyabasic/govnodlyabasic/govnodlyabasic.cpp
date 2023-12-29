#include <iostream>
#include <stack>
#include <cctype>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <set>

using namespace std;

void removeSpaces(string& row)
{
    while (row.find(" ") != -1)
    {
        row.erase(row.find(" "), 1);
    }
}

void convenientForm(string& row)
{
    string temp = row;
    string rowResult = "";
    string historyTemp;
    int count = 0;
    while (temp != "")
    {
        if (temp.substr(0, 1) == " " || isalpha(temp[0]) || isdigit(temp[0]))
        {
            rowResult += temp.substr(0, 1);
            historyTemp = temp.substr(0, 1);
            temp.erase(0, 1);
        }
        else
        {
            if (historyTemp != " ") rowResult += " ";
            rowResult += temp.substr(0, 1);
            temp.erase(0, 1);
        }
    }
    temp = rowResult;
    rowResult = "";

    count = 0;

    while (temp != "")
    {
        if (temp.substr(0, 1) != " ")
        {
            rowResult += temp.substr(0, 1);
            temp.erase(0, 1);
        }
        else
        {
            while (temp.substr(0, 1) == " ")
            {
                temp.erase(0, 1);
            }
            rowResult += " ";
        }
    }
    row = rowResult;
}
int calculateCountChar(string row, char element)
{
    int count = 0;
    while (true)
    {
        int findBracket = row.find(element);
        if (findBracket == -1)
            break;
        else
            row.erase(findBracket, 1);
        count++;
    }
    return count;
}
vector <string> RPN(string str)
{
    string str_rpn;
    string::size_type ind;
    removeSpaces(str);

    for (int i = 0; i < str.size(); ++i)
    {
        if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
        {
            auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c); });
            str.insert(it, ')');
            str.insert(i, "(0");
            int nnn = 0;
        }
    }

    map<char, size_t> priority;
    priority.insert(std::make_pair('*', 3));
    priority.insert(std::make_pair('/', 3));
    priority.insert(std::make_pair('+', 2));
    priority.insert(std::make_pair('-', 2));
    priority.insert(std::make_pair('(', 1));
    stack<char> stack;
    for (auto str_element : str)
    {
        if (!isalnum(str_element) && ('.' != str_element))
        {
            str_rpn += ' ';
            if (')' == str_element)
            {
                while (stack.top() != '(')
                {
                    str_rpn += stack.top();
                    stack.pop();
                    str_rpn += ' ';
                }
                stack.pop();
            }
            else if ('(' == str_element)
            {
                stack.push(str_element);
            }
            else if (stack.empty() || (priority[stack.top()] < priority[str_element]))
            {
                stack.push(str_element);
            }
            else
            {
                do
                {
                    str_rpn += stack.top();
                    str_rpn += ' ';
                    stack.pop();
                } while (!(stack.empty() || (priority[stack.top()] < priority[str_element])));
                stack.push(str_element);
            }
        }
        else
        {
            str_rpn += str_element;
        }
    }
    while (!stack.empty())
    {
        str_rpn += stack.top();
        str_rpn += ' ';
        stack.pop();
    }

    convenientForm(str_rpn);
    cout << str_rpn << endl;
    vector <string> strRpnVector;

    int j = 1;
    for (int i = 0; i < str_rpn.size(); i++)
    {
        if (isdigit(str_rpn[i]))
        {
            string elementStrRpn = "";
            j = i;
            while (isdigit(str_rpn[j]))
            {
                elementStrRpn += str_rpn.substr(j, 1);
                str_rpn.erase(j, 1);
            }
            strRpnVector.push_back(elementStrRpn);
        }
        else if (str_rpn.substr(i, 1) != " ")
        {
            strRpnVector.push_back(str_rpn.substr(i, 1));
            str_rpn.erase(i, 1);
        }
    }

    return strRpnVector;
}
#define POS_COMMAND_LINE 1
vector <string> lineProgram = {"500", "IF", "A", "+", "1", "+", "7", "<=", "B" , "+", "1", "GOTO", "103"};

void handleLineIfCommand()
{
    vector <string> comparingSigns = { "<", ">", "<=", ">=", "==" };
    vector <string> lineProgramIF;
    string temp = "";
    auto it = comparingSigns.end();
    for (int i = 0; i < lineProgram.size(); i++)
    {

        lineProgramIF.push_back(lineProgram[i]);
        if (i == POS_COMMAND_LINE + 1)
        {
            for (int j = i; find(comparingSigns.begin(), comparingSigns.end(), lineProgram[j]) == comparingSigns.end(); j++)
            {
                temp += lineProgram[j];
                //cout << temp << endl;
                i = j;
            }
            lineProgramIF.push_back(temp);
        }
    }
    lineProgram = lineProgramIF;
}
int main(int argc, int* argv[])
{
    //string row = "500 IF  A + 1 + 7 <= B + 1 GOTO 103";
    //cout << row << endl;;
    string row = "01";
   // for (int i = 0; i < lineProgram.size(); i++)
    //{
    //    cout << lineProgram[i] << endl;
   // }
    int i = 1 + stoi(row);
    cout << i << endl;
   // handleLineIfCommand();
   // for (int i = 0; i < lineProgram.size(); i++)
   // {
   //     cout << lineProgram[i] << endl;
   // }
}
    //
    // 50 IF C - B < 0 (A = (A + B))
    // 
    // array:
    // 0 = C
    // 1 = <
    // 2 = 0
    // 
    // <
    // >
    // =
    // 
    // if array[1] = "<"
    //        map ("0" 96)  map("C" 97)
    // ...
    //      05 LOAD 97
    //      06 SUB 96
    //      07 JNEG 09
    //      08 JUMP 13
    //      09 .....
    //      ...
    //      12 ....
    //      13 WRITE 97
    //



    // if array[1] = ">"
    //                                       // ("array[2]" mapsize - 1)          map ("0" 96)  map("C" 97)
    //      05 LOAD 96
    //      06 SUB 97
    //      07 JNEG 09
    //      08 JUMP 13
    //      09 .....
    //      ...
    //      12 
    //      13 WRITE 97

    // if array[1] = "="
    //                                // ("array[2]" mapsize - 1)          map ("0" 96)  map("C" 97)
    //      05 LOAD 96
    //      06 SUB 97
    //      07 JZ 09
    //      08 JUMP 13
    //      09 .....
    //      ...
    //      12 
    //      13 WRITE 97


//      ... 
//      05 LOAD 97
//      ...
//      06 SUB 96
//      07 JNEG 09
//      08 JUMP 13
//      09
//      ...
//      12 
//      13 WRITE 97