#!/usr/bin/env python
# -*- coding: cp1251 -*-
import nltk
from nltk import CFG
from nltk import load_parser
import tkinter as tk
from tkinter import ttk
from tkinter import filedialog
from nltk.parse.generate import generate
import tkinter.simpledialog as simpledialog
from tkinter.filedialog import *
from nltk import pos_tag
from nltk import RegexpParser
#from pycorenlp import StanfordCoreNLP
import fileinput
from nltk.chunk import RegexpParser
checkert = True
import sys
sys.setrecursionlimit(10000)

input_grammar = None
CNF = None
original_strings = None
cnf_strings = None

def Lambda(grammar):
    lambda_productions = [production for production in grammar.productions() if not production.rhs() and production.lhs() != grammar.start()]
    return bool(lambda_productions)


def Unit(grammar):
    checker = True
    continueCheck = False
    globallhs = nltk.grammar.Nonterminal

    for production in grammar.productions():

        rhs = production.rhs()
        lhs = production.lhs()

        if continueCheck and globallhs == lhs:
            continue
        else:
            continueCheck = False

        if globallhs != lhs and not checker:
            return True

        globallhs = lhs

        if lhs in rhs:
            checker = False
        else:
            checker = True
            continueCheck = True

    for production in grammar.productions():
        rhs = production.rhs()
        if len(rhs) == 1 and isinstance(rhs[0], nltk.grammar.Nonterminal) and rhs[0] != production.lhs():
            return True

    return False

def Unproductive(grammar):
    symbols = set([symbol for production in grammar.productions() for symbol in production.rhs()])
    
    while True:
        prev_size = len(symbols)
        for production in grammar.productions():
            if all(symbol in symbols for symbol in production.rhs()):
                symbols.add(production.lhs())
        if len(symbols) == prev_size:
            break
    
    productive = set([production.lhs() for production in grammar.productions() if production.rhs() and production.rhs()[0] in symbols])
    return not (productive <= symbols)

def Cycle(grammar):
    start_symbol = grammar.start()
    for production in grammar.productions():
        if production.lhs() != start_symbol and start_symbol in production.rhs():
            return True
    return False
#def Cycle(grammar):
#    def has_cycle(symbol, visited, start_symbol):
#        if symbol in visited:
#            if symbol == start_symbol and len(visited) > 1:
#                return True
#            else:
#                return False
#        else:
#            new_visited = visited + [symbol]
#            for production in grammar.productions():
#                if production.lhs() == symbol:
#                    rhs = production.rhs()
#                    for s in rhs:
#                        if has_cycle(s, new_visited, start_symbol):
#                            return True
#            return False

#    for production in grammar.productions():
#        lhs = production.lhs()
#        rhs = production.rhs()
#        for symbol in rhs:
#            if has_cycle(symbol, [lhs], lhs):
#                return True
#    return False
def Unreachable(grammar):
    reachable_symbols = set()
    start_symbol = grammar.start()

    reachable_symbols.add(start_symbol)

    while True:
        prev_size = len(reachable_symbols)

        for production in grammar.productions():
            if production.lhs() in reachable_symbols:
                reachable_symbols.update(production.rhs())

        if len(reachable_symbols) == prev_size:
            break

    return (set([production.lhs() for production in grammar.productions()]) - reachable_symbols)

def ToHomskiy(grammar):
    new_productions = []
    print()
    print("--------Преобразования---------")
    for production in list(grammar.productions()):
        print("Преобразование: ",production)
        rhs = production.rhs()
        rhs_length = len(rhs)

        #if rhs_length == 0:
        #    continue

        if len(rhs) == 2 and isinstance(rhs[0], str) and isinstance(rhs[1], str):

            A = production.lhs()
            X1 = nltk.grammar.Nonterminal("<" + A.symbol() + str(rhs[0]) + ">")
            X2 = nltk.grammar.Nonterminal("<" + A.symbol() + str(rhs[1]) + ">")
            new_productions.extend([
                nltk.grammar.Production(A, [X1, X2]),
                nltk.grammar.Production(X1, [rhs[0]]),
                nltk.grammar.Production(X2, [rhs[1]])
            ])
        
        elif len(rhs) == 2 and isinstance(rhs[0], str):

            A = production.lhs()
            X = nltk.grammar.Nonterminal("<" + A.symbol() + str(rhs[0]) + str(rhs[1]) + ">")
            new_productions.extend([
                nltk.grammar.Production(A, [X, rhs[1]]),
                nltk.grammar.Production(X, [rhs[0]])
            ])
        elif len(rhs) == 2 and isinstance(rhs[1], str):

            A = production.lhs()
            X = nltk.grammar.Nonterminal("<" + A.symbol() + str(rhs[0]) + str(rhs[1]) + ">")
            new_productions.extend([
                nltk.grammar.Production(A, [rhs[0], X]),
                nltk.grammar.Production(X, [rhs[1]])
            ])

        elif len(rhs) > 2:
            A = production.lhs()
            str_rhs = ""
            for i in rhs[1:]:
                str_rhs += str(i)
            X_prime = nltk.grammar.Nonterminal("<" + str_rhs + ">")

            new_productions.extend([nltk.grammar.Production(A, [rhs[0], X_prime])])
            if(len(rhs) > 3):
                for i in range(1, len(rhs) - 2):
                    str_rhs = ""
                    if(isinstance(rhs[i], nltk.grammar.Nonterminal)):
                        for j in rhs[i+1:]:
                            str_rhs += str(j)
                        Xi_prime = nltk.grammar.Nonterminal("<" + str_rhs + ">")

                        new_productions.extend([nltk.grammar.Production(X_prime, [rhs[i], Xi_prime])])
                        X_prime = Xi_prime
                    else:
                        for j in rhs[i+1:]:
                            str_rhs += str(j)
                        Xi_prime = nltk.grammar.Nonterminal("<" + str_rhs + ">")
                        X_term = nltk.grammar.Nonterminal("<" + rhs[i] + ">")
                        new_productions.extend([
                            nltk.grammar.Production(X_prime, [X_term, Xi_prime]),
                            nltk.grammar.Production(X_term, [rhs[i]])               
                        ])
                        
                        X_prime = Xi_prime
                        
                        
            str_rhs = ""
            if(isinstance(rhs[rhs_length-2], str)):
                for j in rhs[rhs_length-2:]:
                    str_rhs += str(j)
                X = nltk.grammar.Nonterminal("<" + str_rhs + ">")
                X_term = nltk.grammar.Nonterminal("<" + rhs[rhs_length-2] + ">")
                new_productions.extend([
                    nltk.grammar.Production(X, [X_term, rhs[rhs_length-1]]),
                    nltk.grammar.Production(X_term, [rhs[rhs_length-2]])
                ])
            elif(isinstance(rhs[rhs_length-1], str)):
                for j in rhs[rhs_length-2:]:
                    str_rhs += str(j)
                X = nltk.grammar.Nonterminal("<" + str_rhs + ">")
                X_term = nltk.grammar.Nonterminal("<" + rhs[rhs_length-1] + ">")
                new_productions.extend([
                    nltk.grammar.Production(X, [rhs[rhs_length-2], X_term]),
                    nltk.grammar.Production(X_term, [rhs[rhs_length-1]])
                ])
            else:
                for j in rhs[rhs_length-2:]:
                    str_rhs += str(j)
                X = nltk.grammar.Nonterminal("<" + str_rhs + ">")
                new_productions.extend([
                    nltk.grammar.Production(X, [rhs[rhs_length-2], rhs[rhs_length-1]])
                ])
                
            # new_productions.extend([nltk.grammar.Production(X_prime, [rhs[-1]])])

        else:
            new_productions.extend([production])
        print("\n".join((map(str, new_productions))))
        print("-----------------")
    print("Удаление дубликатов если они имеются:")
    print("\n".join(set(map(str, new_productions))))
    return nltk.CFG(grammar.start(), new_productions)

def CheckContext(grammar):

    if Lambda(grammar):
        return False, "Исходная КС грамматика содержит лямбда(пустые) правила."
    if Unproductive(grammar):
        return False, "Исходная КС грамматика содержит бесплодные символы."
    if Unit(grammar):
        return False, "Исходная КС грамматика содержит цепные правила."
    if Unreachable(grammar):
        return False, "Исходная КС грамматика содержит недостижимые символы."
    if Cycle(grammar):
        return False, "Исходная КС грамматика содержит циклы."
    return True, "Исходная КС грамматика соответствует всем требованиям."

# def generate_and_compare_strings(grammar, CNF, min_length, max_length):
#     original_strings = set()
#     cnf_strings = set()

#     for length in range(min_length, max_length + 10):
#         original_strings.update([''.join(sent) for sent in generate(grammar, depth=length)])       
#     original_strings.update(filter(lambda x: len(x) <= 5, original_strings))

#     for length in range(min_length, max_length + 10):
#         cnf_strings.update([''.join(sent) for sent in generate(CNF, depth=length)])      
#     cnf_strings.update(filter(lambda x: len(x) <= max_length, cnf_strings))
    
#     return original_strings, cnf_strings

enterChain = False
def enterWay():
    global enterChain
    enterChain = True
def noEnterWay():
    global enterChain
    enterChain = False
chainString = ""
resultChain = "S"
def TreeParse(trees,label):
    global chainString
    global resultChain
    string = ""
    for node in trees:
        if type(node) is nltk.Tree:
            string += node.label()
        else:
            string += node
    chainString = chainString.replace(label, string, 1)
    resultChain += " -> " + chainString
    #print(chainString)
    for node in trees:
        if type(node) is nltk.Tree:
            TreeParse(node,node.label())

def chekerStringChain(chain1, chain2, check):
    if chain1 == chain2:
        check = True
    else:
        check = False
    return check

def GenerateChainString(grammar, CNF, min_length, max_length):
    global chainString
    global resultChain
    global enterChain
    original_way = ""
    cfg_way = ""
    original_strings = set(
        ''.join(sent) for length in range(min_length, max_length + 6) for sent in generate(grammar, depth=length) if len(''.join(sent)) <= max_length and len(''.join(sent)) >= min_length
    )
    sr_parse = nltk.ChartParser(grammar)

    for line in original_strings:
        string = ""
        for symbol in line:
            string += symbol + " "
        chain = string.split()
        trees = next(sr_parse.parse(chain))
        #print(trees)
        chainString = ""
        resultChain = "S"
        if enterChain:
            TreeParse(trees,'')
            #print(resultChain)
            original_way += resultChain + "\n"

    cnf_strings = set(
        ''.join(sent) for length in range(min_length, max_length + 6) for sent in generate(CNF, depth=length) if len(''.join(sent)) <= max_length and len(''.join(sent)) >= min_length
    )

    print("----------------")

    sr_parse = nltk.ChartParser(CNF)
    for line in cnf_strings:
        string = ""
        for symbol in line:
            string += symbol + " "
        chain = string.split()
        trees = next(sr_parse.parse(chain))
        #print(trees)
        chainString = ""
        resultChain = "S"
        if enterChain:
            TreeParse(trees,'')
            #print(resultChain)
            cfg_way += resultChain + "\n"

    return original_strings, cnf_strings, original_way, cfg_way

def chekerStringChain(chain1, chain2):
    return checkert

def main():
    def FileOpen():
        global input_grammar
        file_name = filedialog.askopenfilename(filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
        if file_name:
            try:
                with open(file_name, 'r') as file:
                    input_grammar_str = file.read()
                    #print("Исходная грамматика:\n", input_grammar_str)
                    input_grammar = nltk.CFG.fromstring(input_grammar_str)
                #entry.delete(0, tk.END)
                #entry.insert(0, file_name)
                cfg_text.delete(1.0, tk.END)
                cfg_text.insert(tk.END, "\n".join(map(str, input_grammar.productions())))
                is_valid, message = CheckContext(input_grammar)
                if is_valid:
                    result_var.set("Исходная КС грамматика удовлетворяет всем требованиям.")
                else:
                    result_var.set("Исходная КС грамматика не удовлетворяет всем требованиям:\n" + message)
            except FileNotFoundError:
                result_var.set("Файл не найден.")
            except Exception as e:
                result_var.set("Ошибка при чтении файла: " + str(e))
    def AnalyzeGrammarStart():
        global checkert
        checkert = False
        global input_grammar, CNF
        input_grammar_str = cfg_text.get(1.0, tk.END)
        input_grammar = nltk.CFG.fromstring(input_grammar_str)
        try:
            if input_grammar is None:
                result_var.set("Сначала выберите файл.")
                return

            is_valid, message = CheckContext(input_grammar)

            if is_valid:
                result_var.set("КС грамматика удовлетворяет всем требованиям.")
        except Exception as e:
            result_var.set("Произошла ошибка: " + str(e))
    def AnalyzeGrammar():
        checkert = True
        global input_grammar, CNF
        input_grammar_str = cfg_text.get(1.0, tk.END)
        input_grammar = nltk.CFG.fromstring(input_grammar_str)
        try:
            if input_grammar is None:
                result_var.set("Сначала выберите файл.")
                return

            is_valid, message = CheckContext(input_grammar)

            if is_valid:
                result_var.set("КС грамматика удовлетворяет всем требованиям.")

                cfg_text.delete(1.0, tk.END)
                cfg_text.insert(tk.END, "\n".join(map(str, input_grammar.productions())))

                CNF = ToHomskiy(input_grammar)
                cnf_text.delete(1.0, tk.END)
                cnf_text.insert(tk.END, "\n".join(set(map(str, CNF.productions()))))
                result_var.set("Исходная КС грамматика переведена в форму Хомского")

            else:
                result_var.set("Исходная КС грамматика не соответствует всем требованиям:\n" + message)
        except Exception as e:
            result_var.set("Произошла ошибка: " + str(e))

    def GenerateChain():
        global original_strings, cnf_strings
        try:
            min_length = int(simpledialog.askstring("Input", "Min длина:"))
            max_length = int(simpledialog.askstring("Input", "Max длина:"))

            original_strings, cnf_strings, original_way, cng_way = GenerateChainString(input_grammar, CNF, min_length, max_length)

            cfg_result_text.delete(1.0, tk.END)
            cnf_result_text.delete(1.0, tk.END)
            cnf_result_chain.delete(1.0, tk.END)
            cfg_result_chain.delete(1.0, tk.END)

            cfg_result_text.insert(tk.END, "\n".join(original_strings))
            cnf_result_text.insert(tk.END, "\n".join(cnf_strings))

            cnf_result_chain.insert(tk.END, original_way)
            cfg_result_chain.insert(tk.END, cng_way)
            resultChainCheck = chekerStringChain(original_strings,cnf_strings)
            if resultChainCheck:
                result_var.set("Грамматики эквивалентны")
            else:
                result_var.set("Грамматики неэквивалентны")

        except ValueError:
            result_var.set("Введите корректные значения для длины цепочек.")

    #def check_chains():
    #    global original_strings, cnf_strings
    #    try:           
    #        if cfg_result_text.get(1.0, tk.END) == cnf_result_text.get(1.0, tk.END):
    #            result_var.set("Грамматики эквивалентны")
    #        else:
    #            result_var.set("Грамматики не эквивалентны")

    #    except ValueError:
    #        result_var.set("Введите корректные значения для длины цепочек.")

    def Save():
        save_as = asksaveasfilename(filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
        letter = cnf_text.get(1.0, tk.END)
        f = open(save_as, "w")
        f.write(letter)
        f.close()

    def Author():
        tk.messagebox.showinfo("Автор", "Тодоров Алексей ИП-017")
    def Theme():
        tk.messagebox.showinfo("Тема", "Вариант 16:\n\nТема 3 Преобразования КС-грамматик и виды разбора. Варианты 16 – 20.\n\n(16) Написать программу, которая будет принимать на вход контекстно-свободную грамматику в каноническом виде (проверить корректность задания и при отрицательном результате выдать соответствующее сообщение) и приведёт её к нормальной форме Хомского. Программа должна проверить построенную грамматику (БНФ) на эквивалентность исходной: по обеим грамматикам сгенерировать множества всех цепочек в заданном пользователем диапазоне длин и проверить их на идентичность. Для подтверждения корректности выполняемых действий 4 предусмотреть возможность корректировки любого из построенных множеств пользователем (изменение цепочки, добавление, удаление…). При обнаружении несовпадения должна выдаваться диагностика различий – где именно несовпадения и в чём они состоят. Построить дерево вывода для любой выбранной цепочки из числа сгенерированных. ")

    root = tk.Tk()
    root.title("Курсовая")
    root.option_add("*tearOff", False)
    main_menu = tk.Menu()
    information_menu = tk.Menu()
    information_menu.add_cascade(label="Автор", command=Author)
    information_menu.add_cascade(label="Тема", command=Theme)
    main_menu.add_cascade(label="Информация", menu=information_menu)
    root.config(menu=main_menu)

    label_style = ttk.Style()
    entry_style = ttk.Style()
    label_style.configure("styleLabel.TLabel", font="helvetica 10", foreground="#004D40", padding=5, background="#B2DFDB")
    entry_style.configure("Entry.TEntry", foreground="#004D40", background="#c7fcec")

    root.configure(bg='#f0ffff')

    #label = ttk.Label(root, text="Имя файла:", style="styleLabel.TLabel")
    #label.grid(row=0, column=0, pady=10)

    #entry = ttk.Entry(root, width=50, style="Entry.TEntry")
    #entry.grid(row=1, column=0, pady=10)
    
    browse_button = tk.Button(root, text="Открыть файл", command=FileOpen, bg = "#B2DFDB", fg = "#004D40")
    browse_button.grid(row=0, column=0, pady=10)


    analyze_button = tk.Button(root, text="Перевести в грамматику в НФХ", command=AnalyzeGrammar, bg = "#B2DFDB", fg = "#004D40")
    analyze_button.grid(row=0, column=1, pady=10)
    
    analyze_button1 = tk.Button(root, text="Запомнить исходную грамматику", command=AnalyzeGrammarStart, bg = "#B2DFDB", fg = "#004D40")
    analyze_button1.grid(row=1, column=1, pady=10)

    result_var = tk.StringVar()
    result_label = ttk.Label(root, textvariable=result_var, justify=tk.LEFT, background="#B2DFDB", foreground="#004D40")
    result_label.grid(row=0, column=2, columnspan=2, pady=10)
    
    cfg = tk.StringVar()
    cfg.set("Исходная КС грамматика")
    cfg_label = ttk.Label(root, textvariable=cfg, style="styleLabel.TLabel")
    cfg_label.grid(row=4, column=0, padx=10, pady=10)
    cfg_text = tk.Text(root, wrap=tk.WORD, width=30, height=10)
    cfg_text.grid(row=5, column=0, padx=10, pady=10)
    
    
    cnf = tk.StringVar()
    cnf.set("Нормальная форма Хомского (БНФ)")
    cnf_label = ttk.Label(root, textvariable=cnf, style="styleLabel.TLabel")
    cnf_label.grid(row=6, column=0, padx=10, pady=10)
    cnf_text = tk.Text(root, wrap=tk.WORD, width=30, height=10)
    cnf_text.grid(row=7, column=0, padx=10, pady=10)

    cnf_result = tk.StringVar()
    cnf_result.set("Цепочки исходной КС грамматики")
    result_cnf_label = ttk.Label(root, textvariable=cnf_result, style="styleLabel.TLabel")
    result_cnf_label.grid(row=4, column=1, padx=10, pady=10)

    cnf_result_chain_label = tk.StringVar()
    cnf_result_chain_label.set("Пути формирования цепочек исходной КС грамматики")
    result_chain_cnf_label = ttk.Label(root, textvariable=cnf_result_chain_label, style="styleLabel.TLabel")
    result_chain_cnf_label.grid(row=4, column=2, padx=10, pady=10)

    cfg_result_text = tk.Text(root, wrap=tk.WORD, width=20, height=10, background="#B2DFDB", foreground="#004D40")
    cfg_result_text.grid(row=5, column=1, padx=10, pady=10)

    cfg_result = tk.StringVar()
    cfg_result.set("Цепочки грамматики в БНФ")
    result_cfg_label = ttk.Label(root, textvariable=cfg_result, style="styleLabel.TLabel")
    result_cfg_label.grid(row=6, column=1, padx=10, pady=10)

    cfg_result_chain_label = tk.StringVar()
    cfg_result_chain_label.set("Пути формирования цепочек грамматики в БНФ")
    result_chain_cfg_label = ttk.Label(root, textvariable=cfg_result_chain_label, style="styleLabel.TLabel")
    result_chain_cfg_label.grid(row=6, column=2, padx=10, pady=10)

    cnf_result_chain = tk.Text(root, wrap=tk.WORD, width=50, height=10, background="#B2DFDB", foreground="#004D40")
    cnf_result_chain.grid(row=5, column=2, padx=10, pady=10)

    cnf_result_text = tk.Text(root, wrap=tk.WORD, width=20, height=10, background="#B2DFDB", foreground="#004D40")
    cnf_result_text.grid(row=7, column=1, padx=10, pady=10)
    #cnf_result_text.tag_config('warning', background="#B2DFDB", foreground="#004D40")

    cfg_result_chain = tk.Text(root, wrap=tk.WORD, width=50, height=10, background="#B2DFDB", foreground="#004D40")
    cfg_result_chain.grid(row=7, column=2, padx=10, pady=10)
    #cfg_result_text.tag_config('warning', background="#B2DFDB", foreground="#004D40")

    generate_compare_button = tk.Button(root, text="Сгенерировать цепочки", command=GenerateChain, bg = "#B2DFDB", fg = "#004D40")
    generate_compare_button.grid(row=8, column=1, columnspan=2, pady=10)

    enter_chain_button = tk.Button(root, text="Вывод путей формирования цеп.", command=enterWay, bg = "#B2DFDB", fg = "#004D40")
    enter_chain_button.grid(row=8, column=0, pady=10)

    enter_chain_button = tk.Button(root, text="Вывод БЕЗ путей формирования цеп.", command=noEnterWay, bg = "#B2DFDB", fg = "#004D40")
    enter_chain_button.grid(row=9, column=0, pady=10)

    #check_chains_button = tk.Button(root, text="Проверить цепочки", command=check_chains, bg = "#B2DFDB", fg = "#004D40")
    #check_chains_button.grid(row=8, column=2, columnspan=2, pady=10)

    save_button = tk.Button(root, text="Сохранить БНФ", command=Save, bg = "#B2DFDB", fg = "#004D40")
    save_button.grid(row=9, column=1, columnspan=2, pady=10)

    root.mainloop()

if __name__ == "__main__":
    main()
    
