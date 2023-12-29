#!/usr/bin/env python
# -*- coding: cp1251 -*-
import PySimpleGUI as sg
# минимальная длина цепочки не должна быть меньше чем кратность


def build_core(s):
    global separator
    out_str = ''
    for i in s:
        out_str += f"{''.join(k for k in i)}"
        out_str += separator
    out_str_out = f"({out_str[:-1]})"
    return out_str_out

def main(alphabet, kratnost, subchain):
    global separator
    a = alphabet
    k = kratnost
    s = subchain

    sub_len = len(s)  # длина подцепочки
    to_krat = k - (sub_len % k)  # сколько не хватает до кратности
    add = ""  # добавлеяем до кратности

    if k != sub_len and k != 1:
        #while to_krat != 0:
            #add += f"({'+'.join(i for i in a)})"
            #to_krat -= 1
        #core = f"({add}{s}+{s}{add})"  # минимальное РВ

        to_krat += 1
        str_list = [[] for i in range(to_krat)]

        add += f"({separator.join(i for i in a)})"
        for i in range(to_krat):
            for j in range(to_krat):
                if j == i:
                    str_list[i].append(s)
                else:
                    str_list[i].append(add)
        print(str_list)

        core = build_core(str_list)
    else:
        core = f"({s})"


    additional_part = "("
    for i in range(k):
        additional_part += f"({separator.join(i for i in a)})"
    additional_part += ")*"

    res = additional_part
    res += core
    res += additional_part

    return res


#main(['0','1','a'], 3, 'a' )


def SplitByPlus(chain):
    global separator
    scobki = 0
    SpPlus = []
    str = ""
    for i in range(len(chain)):
        if chain[i] == '(':
            scobki += 1
        elif chain[i] == ')':
            scobki -= 1
        if chain[i] != separator or scobki != 0:
            str += chain[i]
        elif scobki == 0:
            SpPlus.append(str)
            str = ""
    SpPlus.append(str)
    print("SpPlus", SpPlus)
    return SpPlus


def SplitByBrackets(chain):
    scobki = 0
    Split = []
    str = ""
    j = 0
    for i in range(len(chain)):
        if j >= len(chain):
            break
        if chain[j] == '(':
            scobki += 1
        elif chain[j] == ')':
            scobki -= 1
            if len(chain) > (j + 1) and chain[j + 1] == '*':
                str += chain[j]
                j += 1
        str += chain[j]
        if scobki == 0:
            Split.append(str)
            str = ""
        j += 1
    print("SplitBrackets", Split)
    return Split


def BuildBricks(s, max):
    SpScob = SplitByBrackets(s)
    Mas = []
    newinf = False
    for i in range(len(SpScob)):
        if SpScob[i][0] == '(':
            tmp = ""
            if SpScob[i][-1] == '*':
                tmp = SpScob[i][1:-2]
                #print("TMP1", tmp)
                newinf = True
            elif SpScob[i][-1] == ')':
                tmp = SpScob[i][1:-1]
                #print("TMP2", tmp)
            merge = MergeBlocks(tmp, max, newinf)
            Mas.append(merge)
        else:
            str = [SpScob[i]]
            Mas.append(str)
    set_ = set()
    ConcatenateBricks(Mas, max, 0, "", set_)
    NewBrick = list(set_)
    #print("BuildBricks", NewBrick)
    return NewBrick


def ConcatenateBricks(Mas, max, index, s, set_):
    if index == len(Mas):
        set_.add(s)
        return
    for i in range(len(Mas[index])):
        newS = s + Mas[index][i]
       # print("ConcatenateBricks", newS)
        if len(newS) > max:
            continue
        ConcatenateBricks(Mas, max, index + 1, newS, set_)


def MergeBlocks(s, max, inf):
    t = 0
    MergeList = []
    SpPlus = SplitByPlus(s)
    for i in range(len(SpPlus)):
        buildB = BuildBricks(SpPlus[i], max)
        print("MergeList: ", MergeList)
        print("buildB: ", buildB)
        for j in range(len(buildB)):
            t = 0
            for k in range(len(MergeList)):
                print('k: ', k)
                print('t: ', t)
                #if t > len(MergeList) or t < 0:
                    #break
                if MergeList[t] == buildB[j]:
                    MergeList.pop(t)
                    t -= 1
                t += 1
        for j in range(len(buildB)):
            MergeList.append(buildB[j])
    if inf:
        set_ = set()
        generator(MergeList, max, "", set_)
        MergeList.clear()
        MergeList.extend(set_)
        MergeList.append("")
        print("INF MergeList: ", MergeList)
    #print("MergeBlocks", MergeList)
    return MergeList


def generator(merge_list, max, s, set_):
    for i in range(len(merge_list)):
        new_s = s + merge_list[i]
        set__list = list(set_)
        if len(new_s) > max or new_s in set__list:
            continue
        set_.add(new_s)
        generator(merge_list, max, new_s, set_)


#def find_params(s):
#    spl_brackets = SplitByBrackets(s)
#    erase = spl_brackets[0][1:-2]
#    print(erase)
#    xx = SplitByBrackets(erase)
#    alphabet = SplitByPlus(xx[0][1:-1])
#    right_border = erase.count('(')
#    left_border = erase.count(')')
#    if right_border != left_border:
#        krat = 1
#    else:
#        krat = right_border

#    spliPlus = spl_brackets[1][1:-1]
#    if spliPlus.find(')') != -1 and spliPlus.find('+') != -1:
#        spliPlus = spliPlus[spliPlus.find(')'):spliPlus.find('+')]

#    return alphabet, krat, spliPlus
separator = '+'
if __name__ == '__main__':


    #main(['0', '1', 'a'], 1, '0')
    sg.theme('LightBlue2')  # Add a touch of color
    # All the stuff inside your window.
    menu_def = [['Меню', ['Автор работы', 'Тема курсовой', 'Вывод в файл']], ]

    layout = [[sg.Menubar(menu_def)],
              [sg.Text('Алфавит выражения'), sg.Input(key="-ALPHABET-", size=(8, 10)) , sg.Text('Кратность длины'), sg.Input(key="-KRATNOST-", size=(8, 10)),sg.Text('Подцепочка'), sg.Input(key="-SUBCHAIN-", size=(8, 10))],
              [sg.Text('Разделитель (или)'),  sg.Input(key="-SEPARATE-", size=(8, 10)) ,sg.Button('Регулярное выражение')],
              [sg.Multiline(key="-REGEX-", size=(60, 10))],
              [sg.Text('Мин. длина цепочек'),sg.Input(key="-LEFTBORDER-", size=(8, 10)),
               sg.Text('Макс. длина цепочек'), sg.Input(key="-RIGHTBORDER-", size=(8, 10))],
              [sg.Multiline(key="-CHAINS-", size=(60, 10)),sg.Button('Сгенерировать цепочки')]]
  

    # Create the Window
    window = sg.Window('ТЯП Курсовая', layout)
    # Event Loop to process "events" and get the "values" of the inputs
    while True:
        event, values = window.read()

        if event != sg.WIN_CLOSED:
            if values[0] == 'Вывод в файл':
                res = sg.popup_get_file("Select or create file to save")
                if res:
                    try:
                        file = open(res, 'r+')
                    except FileNotFoundError:
                        file = open(res, 'w+')
                    file.writelines(str(values["-CHAINS-"]))
                    file.close()

            if values[0] == 'Тема курсовой':
                sg.popup_ok("(2) Написать программу, которая по предложенному описанию языка построит регулярную грамматику (ЛЛ или ПЛ – по заказу пользователя),задающую этот язык, и позволит сгенерировать с её помощью все цепочки языка в заданном диапазоне длин. Предусмотреть возможность поэтапного отображения на экране процесса генерации цепочек. Варианты задания языка:(7) Алфавит, кратность длины и заданная фиксированная подцепочка всех цепочек языка.")

            if values[0] == 'Автор работы':
                sg.popup_ok('Копытина Татьяна ИП-013 Вариант работы N-7')

            #if values[0] == 'Ввести свое регулярное выражение':
            #    regex = sg.popup_get_text("Enter regex:")
            #    a, k, subc = find_params(regex)
            #    window["-ALPHABET-"].update(','.join(i for i in a))
            #    window["-KRATNOST-"].update(k)
            #    window["-SUBCHAIN-"].update(subc)
            #    window["-REGEX-"].update(regex)



        if event == 'Регулярное выражение':
            if values["-ALPHABET-"] == '':
                sg.popup_error("Алфавит не введен")
            elif values["-KRATNOST-"] == '':
                sg.popup_error("Кратность цепочки не введена")
            elif values["-SUBCHAIN-"] == '':
                sg.popup_error("Обязательная подцепочка не введена")
            #regex = main(['0', '1', 'a'], 2, '0')
            else:
                if values["-SEPARATE-"] != '':
                    separator = str(values["-SEPARATE-"])
                alphabet = str(values["-ALPHABET-"]).split(' ')
                kratnost = int(values["-KRATNOST-"])
                subchain = str(values["-SUBCHAIN-"])
                check = True
                for el in subchain:
                    if el not in alphabet:
                        check = False
                if check:
                    regex = main(alphabet, kratnost, subchain)
                    window['-REGEX-'].update(regex)
                else:
                    sg.popup_error("В подцепочке есть символы не из алфавита")

        if event == 'Сгенерировать цепочки':
            if values["-REGEX-"] == '':
                sg.popup_error("Регулярное выражение не сформировано!")
            else:
                res_str = ''
                res_list = []
                all_list = MergeBlocks(values['-REGEX-'], int(values["-RIGHTBORDER-"]), False)
                for i in all_list:
                    if int(values["-KRATNOST-"]) == 0:
                        window["-CHAINS-"].update('lambda')
                        break
                    if len(i) >= int(values["-LEFTBORDER-"]) and len(i) % int(values["-KRATNOST-"]) == 0 and str(values["-SUBCHAIN-"]) in i:
                        res_list.append(i)
                res_list.sort(key=lambda x: len(x))
                if len(res_list) == 0:
                    window["-CHAINS-"].update('lambda')
                else:
                    for i in res_list:
                        res_str += i + '\n'
                    window["-CHAINS-"].update(res_str)

        if event == sg.WIN_CLOSED:  # if user closes window or clicks cancel
            break


    window.close()

'''
def SplitByBrackets(chain):
    scobki = 0
    Split = []
    str = ""
    j = 0
    for i in range(len(chain)):
        if j >= len(chain):
            break
        if chain[j] == '(':
            scobki += 1
        elif chain[j] == ')':
            scobki -= 1
            if len(chain) > (j + 1) and chain[j + 1] == '*':
                str += chain[j]
                j += 1
        str += chain[j]
        if scobki == 0:
            Split.append(str)
            str = ""
        j += 1
    return Split

def SplitByPlus(chain):
    scobki = 0
    SpPlus = []
    str = ""
    for i in range(len(chain)):
        if chain[i] == '(':
            scobki += 1
        elif chain[i] == ')':
            scobki -= 1
        if chain[i] != '+' or scobki != 0:
            str += chain[i]
        elif scobki == 0:
            SpPlus.append(str)
            str = ""
    SpPlus.append(str)
    return SpPlus

def find_params(s):
    spl_brackets = SplitByBrackets(s)
    erase = spl_brackets[0][1:-2]
    print(erase)
    xx = SplitByBrackets(erase)
    alphabet = SplitByPlus(xx[0][1:-1])
    print(alphabet)
    right_border = erase.count('(')
    left_border = erase.count(')')
    if right_border != left_border:
        pass
    else:
        krat = right_border
    print(krat)
    
    spliPlus = spl_brackets[1][1:-1]
    if spliPlus.find(')') != -1 and spliPlus.find('+') != -1:
        spliPlus = spliPlus[spliPlus.find(')'):spliPlus.find('+')]

    print(spliPlus)

    return alphabet, krat, spliPlus

#(0+1+a)aa+aa(0+1+a)
s = '((0+1+a)(0+1+a))*(aa)((0+1+a)(0+1+a))*'
find_params(s)
'''
