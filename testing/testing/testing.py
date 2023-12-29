#!/usr/bin/env python
import sys
import os
from homskiy import *
import tkinter as tk
from tkinter import scrolledtext
from tkinter import ttk
from tkinter.tix import *
from tkinter.messagebox import askyesno
from dataclasses import dataclass
from typing import Dict, List

checkEtap = False
firstChains = []
secondChains = []
@dataclass
class Grammar:
    Terminal: List[str]
    NoTerminal: List[str]
    P: Dict[str, List[str]]
    S: str
def restart_program():
    python = sys.executable
    os.execl(python, python, * sys.argv)

def etap_check():
    global checkEtap
    checkEtap = True

def etap_check_false():
    global checkEtap
    checkEtap = False

def run_program():
    result_text.configure(state='normal')
    result_text.delete('1.0', tk.END)

    def grammar_input():

        Terminal = input_terminal_symbols.get().split()
        NoTerminal = input_non_terminal_symbols.get().split()
        
        P = dict()

        for x in range(numberRules):
            nameRule = nameTerminalRule[x]
            inputRule = rulesInput[x].get().split()
            for i in range(len(inputRule)):
                if inputRule[i] == '\eps':
                    inputRule[i] = ""
            P[nameRule] = inputRule
        
        S = input_target_symbol.get()
        Terminal.append("_")
        global globalTerm
        globalTerm = Terminal

        return {"Terminal": Terminal, "NoTerminal": NoTerminal, "P": P, "S": S}

    def count_non_term_sym(grammar, chain):
        length = 0

        for sym in grammar.Terminal:
            count = chain.count(sym)
            length += count

        #for sym in chain:
        #    if sym in grammar.Terminal:
        #        length += 1
        return length

    def count_non_noterm_sym(grammar, chain):
        length = 0
        for sym in chain:
            if sym in grammar.NoTerminal:
                length += 1
        return length

    data = grammar_input()

    left_border, right_border = map(int, input_chain_range.get().split())

    grammar = Grammar(data["Terminal"], data["NoTerminal"], data["P"], data["S"])
    print(grammar.NoTerminal)
    print(grammar.Terminal)
    print(grammar.P)
    print(grammar.S)
    rules = list(grammar.S)
    used_chain = set()
    indexChain = 1
    step = 1
    path_to_terminal = []
    checkFirst = True;
    while rules:
        if checkFirst == True:
            chain = grammar.S
            checkFirst = False
        else:
            chain = rules.pop(0)

        print(rules)

        #result_text.insert(tk.END, chain if chain else "(lambda)")
        #result_text.insert(tk.END, "\n")
        if chain in used_chain:
            #path_to_terminal.append(chain)
            continue

        used_chain.add(chain)
        none_terminal = True
        #result_text.insert(tk.END, chain if chain else "(lambda)")
        #result_text.insert(tk.END, "\n")

        for i, symbol in enumerate(chain):

            counterNonTerm = 0

            if symbol == "<":
                temp = chain[i + 1:]
                for elementNonTerm in temp:
                    if elementNonTerm == ">":
                        break
                    else:
                        counterNonTerm+=1;
                        symbol+=elementNonTerm

                symbol += ">"
                counterNonTerm+=1;

            if symbol in grammar.NoTerminal:

                #path_to_terminal.append(chain)
                none_terminal = False
                for elem in grammar.P[symbol]:

                    temp = chain[:i] + elem + chain[i + counterNonTerm + 1:]
                    if (checkEtap == True):
                        path_to_terminal.append(temp)

                    if count_non_term_sym(grammar, temp) <= right_border and temp not in rules and count_non_noterm_sym(grammar,temp) <= right_border/2: #right_border+len(grammar.NoTerminal):
                        rules.append(temp)
                        #print(temp+"\n")
                        if (checkEtap == True):
                            1
                           #result_text.insert(tk.END, f"{step}: {temp}""\n")
                        step += 1
            elif symbol not in grammar.Terminal:
                none_terminal = False
                #result_text.insert(tk.END, "данная цепочка: " + chain + " не разрешима\n")
                break

        if none_terminal and left_border <= len(chain) <= right_border:

            result_text.insert(tk.END, str(indexChain)+") "+chain if chain else str(indexChain)+") "+"(lambda)",'warning')
            firstChains.append(chain)

            if (checkEtap == True):
                result_text.insert(tk.END, "  => ")

                for i in range(len(path_to_terminal)):

                   result_text.insert(tk.END, str(path_to_terminal[i])+"->")

                result_text.insert(tk.END, chain if chain else "(lambda)")

                #path_to_terminal.clear()
            indexChain+=1
            result_text.insert(tk.END, "\n")

    result_num = int(result_text.index('end').split('.')[0]) - 2
    run_program_hom()
def Load():
    fileGrammar = open("grammar.txt", "r")

    lines = fileGrammar.readlines()
    index = 0;

    for i,line in enumerate(lines):
        rulesInput[i].insert(0, line)
    input_target_symbol.insert(0, nameTerminalRule[0])
    fileGrammar.close
def run_program_hom():
    result_text2.configure(state='normal')
    result_text2.delete('1.0', tk.END)

    def grammar_input_hom():
            fileGrammar = open("returnHomskiy.txt", "r")
            lines = fileGrammar.readlines()

            Terminal = globalTerm
            NoTerminal = lines[1].rstrip().split(" ")
            S = lines[0].rstrip()

            P = dict()

            for x in range(len(lines)-2):
                nameRule = NoTerminal[x]
                inputRule = lines[x+2].rstrip().split(" ")
                for i in range(len(inputRule)):
                    if inputRule[i] == '\eps':
                        inputRule[i] = ""
                P[nameRule] = inputRule

            #result_text2.insert()

            return {"Terminal": Terminal, "NoTerminal": NoTerminal, "P": P, "S": S}

    def count_non_term_sym_hom(grammar, chain):
        length = 0

        for sym in grammar.Terminal:
            count = chain.count(sym)
            length += count
        return length

    def count_non_noterm_sym_hom(grammar, chain):
        length = 0
        for sym in chain:
            if sym in grammar.NoTerminal:
                length += 1
        return length

    data = grammar_input_hom()

    left_border, right_border = map(int, input_chain_range.get().split())

    grammar = Grammar(data["Terminal"], data["NoTerminal"], data["P"], data["S"])
    print(grammar.NoTerminal)
    print(grammar.Terminal)
    print(grammar.P)
    print(grammar.S)
    print("--------------------------------")
    rules = list(grammar.S)
    used_chain = set()
    indexChain = 1
    step = 1
    path_to_terminal = []
    checkFirst = True;
    while rules:
        if checkFirst == True:
            chain = grammar.S
            checkFirst = False
        else:
            chain = rules.pop(0)

        print(chain)

        if chain in used_chain:
            continue

        used_chain.add(chain)
        none_terminal = True

        for i, symbol in enumerate(chain):

            counterNonTerm = 0

            if symbol == "<":
                temp = chain[i + 1:]
                for elementNonTerm in temp:
                    if elementNonTerm == ">":
                        break
                    else:
                        counterNonTerm+=1;
                        symbol+=elementNonTerm

                symbol += ">"
                counterNonTerm+=1;

            if symbol in grammar.NoTerminal:

                none_terminal = False
                for elem in grammar.P[symbol]:
                    temp = chain[:i] + elem + chain[i + counterNonTerm + 1:]
                    if (checkEtap == True):
                        path_to_terminal.append(temp)
                    if count_non_term_sym_hom(grammar, temp) <= right_border and temp not in rules and count_non_noterm_sym_hom(grammar,temp) <= right_border: #right_border+len(grammar.NoTerminal):
                        rules.append(temp)
                        print(temp+"\n")
                        if (checkEtap == True):
                            1
                           #result_text.insert(tk.END, f"{step}: {temp}""\n")
                        step += 1
            elif symbol not in grammar.Terminal:
                none_terminal = False
                #result_text.insert(tk.END, "данная цепочка: " + chain + " не разрешима\n")
                break

        if none_terminal and left_border <= len(chain) <= right_border:

            result_text2.insert(tk.END, str(indexChain)+") "+chain if chain else str(indexChain)+") "+"(lambda)",'warning')
            secondChains.append(chain)

            if (checkEtap == True):
                result_text2.insert(tk.END, "  => ")

                for i in range(len(path_to_terminal)):

                   result_text2.insert(tk.END, str(path_to_terminal[i])+"->")

                result_text2.insert(tk.END, chain if chain else "(lambda)")
                #path_to_terminal.clear()

            indexChain+=1
            result_text2.insert(tk.END, "\n")

    result_num = int(result_text2.index('end').split('.')[0]) - 2
    #input_number_chain_label = ttk.Label(window, text="Всего цепочек: " + str(indexChain-1), style="styleLabel.TLabel")
    #input_number_chain_label.grid(row=0, column=3)
    #input_number_chain_label = ttk.Label(window, text="Всего этапов: " + str(step-1), style="styleLabel.TLabel")
    #input_number_chain_label.grid(row=1, column=3)
    checkResultsChains()

def checkResultsChains():
    resultChains = set(firstChains) & set(secondChains)
    print(firstChains)
    print(secondChains)
    print(resultChains)
    if len(resultChains) == len(set(firstChains)) and len(resultChains) == len(set(secondChains)):
        labelResult = ttk.Label(window, text="грамматики эквивалентны", style="styleLabel.TLabel")
        labelResult.grid(row=12, column=3)
    else:
        labelResult = ttk.Label(window, text="грамматики эквивалентны", style="styleLabel.TLabel")
        labelResult.grid(row=12, column=3)
def setHom():
    fileGrammar = open('grammarHom.txt','w')
    string = ""
    for x in range(numberRules):
        nameRule = nameTerminalRule[x]
        nameRule = nameRule.replace("<","")
        nameRule = nameRule.replace(">","")
        string += nameRule + " -> "
        Rules = rulesInput[x].get().split()
        for i,rule in enumerate(Rules):
            if i != 0:
                string+=" | "
            for j,symbol in enumerate(rule):
                if symbol == "<":
                    if j != 0:
                        symbol = " "
                    else:
                        symbol = ""
                if symbol == ">":
                    if j != len(rule)-1:
                        symbol = " "
                    else:
                        symbol = ""
                string+=symbol
        string += "\n"
    fileGrammar.write(string)

    set_print(True)
    to_homsky()

    result_text1.configure(state='normal')
    result_text1.delete('1.0', tk.END)

    fileGrammar = open('enterHomskiy.txt','r')
    lines = fileGrammar.readlines()
    for el in lines:
        result_text1.insert(tk.END, el)
def Perevod():
    run_button = tk.Button(window, text="ЗАПУСТИТЬ", command=run_program, font="helvetica 10", padx = 10, pady = 10, bg = "#B2DFDB", fg = "#004D40")
    run_button.grid(row=12, column=2)

    EtapButton = tk.Button(window, text="Вывод путей цепочек", command=etap_check, font="helvetica 10", padx = 10, pady = 10, bg = "#B2DFDB", fg = "#004D40")
    Etap2Button = tk.Button(window, text="Вывод без путей цепочек", command=etap_check_false, font="helvetica 10", padx = 10, pady = 10, bg = "#B2DFDB", fg = "#004D40")

    EtapButton.grid(row=13, column=2)
    Etap2Button.grid(row=14, column=2)

    global result_text2
    global result_text1

    result_text1 = scrolledtext.ScrolledText(window, width=40, height=10, font ="helvetica 14")
    result_text1.grid(row=0, rowspan=6,column=3)
    result_text1.tag_config('warning', background="#B2DFDB", foreground="#004D40")

    result_text2 = scrolledtext.ScrolledText(window, width=40, height=10, font ="helvetica 14")
    result_text2.grid(row=5, rowspan=6,column=3)
    result_text2.tag_config('warning', background="#B2DFDB", foreground="#004D40")

    setHom()

def createNext():

    if input_terminal_symbols.get() == "" or input_non_terminal_symbols.get() == "" or input_rule_count.get() == "" or input_rule_terminal.get() == "" or len(input_rule_terminal.get().split()) != int(input_rule_count.get()):
        return 0

    global input_target_symbol
    global input_chain_range
    global result_text
    global rulesInput
    global numberRules
    global nameTerminalRule

    nextButton.destroy()

    rulesInput = []
    numberRules = int(input_rule_count.get())
    nameTerminalRule = input_rule_terminal.get().split()
    index = 5
    load_button = tk.Button(window, text="ЗАГРУЗИТЬ", command=Load, font="helvetica 10", padx = 10, pady = 10, bg = "#B2DFDB", fg = "#004D40")
    load_button.grid(row=0, column=1)
    rows = 1
    for x in range(numberRules):
        input_rule = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
        input_rule_label = ttk.Label(window, text=str(index)+" Введите правила для " + str(nameTerminalRule[x]), style="styleLabel.TLabel")
        input_rule_label.grid(row=rows, column=1)
        rows+=1
        input_rule.grid(row=rows, column=1)
        rows+=1
        rulesInput.append(input_rule)
        index+=1

    input_target_symbol = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
    input_target_symbol_label = ttk.Label(window, text=str(index)+" Введите целевой символ", style="styleLabel.TLabel")
    input_target_symbol_label.grid(row=rows, column=1)
    rows+=1
    input_target_symbol.grid(row=rows, column=1)

    index+=1

    input_chain_range = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
    input_chain_range_label = ttk.Label(window, text=str(index)+" Введите диапозон через пробел", style="styleLabel.TLabel")
    input_chain_range_label.grid(row=0, column=2)
    input_chain_range.grid(row=1, column=2)

    input_chain_range_label = ttk.Label(window, text="Полученные цепочки", style="styleLabel.TLabel")
    input_chain_range_label.grid(row=2, column=2)
    result_text = scrolledtext.ScrolledText(window, width=40, height=10, font ="helvetica 14")
    result_text.grid(row=3, rowspan=6,column=2)

    result_text.tag_config('warning', background="#B2DFDB", foreground="#004D40")

    perevod_button = tk.Button(window, text="Перевод в норм. форм. Хомского", command=Perevod, font="helvetica 10", padx = 10, pady = 10, bg = "#B2DFDB", fg = "#004D40")
    perevod_button.grid(row=10, column=2)

window = tk.Tk()
window.title("TLP_LAB1")
window.configure(bg='#f0ffff')
label_style = ttk.Style()
entry_style = ttk.Style()

label_style.configure("styleLabel.TLabel", font="helvetica 10", foreground="#004D40", padding=5, background="#B2DFDB", width=40)
entry_style.configure("Entry.TEntry", foreground="#004D40", background="#c7fcec")



input_terminal_symbols = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
input_terminal_symbols_label = ttk.Label(window, text="1) Введите терминальные символы", style="styleLabel.TLabel")
input_terminal_symbols_label.grid(row=0, column=0)
input_terminal_symbols.grid(row=1, column=0)

input_non_terminal_symbols = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
input_non_terminal_symbols_label = ttk.Label(window, text="2) Введите не терминальные символы *", style="styleLabel.TLabel")
input_non_terminal_symbols_label.grid(row=2, column=0)
input_non_terminal_symbols.grid(row=3, column=0)

input_rule_count = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
input_rule_count_label = ttk.Label(window, text="3) Введите количество правил *", style="styleLabel.TLabel")
input_rule_count_label.grid(row=4, column=0)
input_rule_count.grid(row=5, column=0)

input_rule_terminal = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 10")
input_rule_terminal_label = ttk.Label(window, text="4) Введите терминалы правил *", style="styleLabel.TLabel")
input_rule_terminal_label.grid(row=6, column=0)
input_rule_terminal.grid(row=7, column=0)

nextButton = tk.Button(window, text="ДАЛЕЕ", command=createNext, font="helvetica 10", padx = 1, pady = 1, bg = "#B2DFDB", fg = "#004D40")
newButton = tk.Button(window, text="ПЕРЕСОЗДАТЬ", command=restart_program, font="helvetica 10", padx = 1, pady = 1, bg = "#B2DFDB", fg = "#004D40")
nextButton.grid(row=8, column=0)
newButton.grid(row=9, column=0)

window.mainloop()
