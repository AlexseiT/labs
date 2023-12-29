#!/usr/bin/env python
# -*- coding: utf-8 -*-
import tkinter as tk
from tkinter import scrolledtext
from tkinter import ttk
from tkinter.tix import *
from tkinter.messagebox import askyesno
from dataclasses import dataclass
from typing import Dict, List

@dataclass
class Grammar:
    VT: List[str]
    VN: List[str]
    P: Dict[str, List[str]]
    S: str

def run_program():

    result_text.configure(state='normal')
    result_text.delete('1.0', tk.END)


    data = {"VT": ["a", "b", "c"],
            "VN": ["A", "B", "C"],
            "P": {"A": ["aBbbC"], "B": ["aaBb", ""], "C": ["cC", ""]},
            "S": "A"}
    
    def grammar_input():

        result = dict()
        
        # Получение терминальных символов
        VT_input = input_terminal_symbols.get()
        VT = VT_input.split()
        
        # Получение не терминальных символов
        VN_input = input_non_terminal_symbols.get()
        VN = VN_input.split()
        
        # Получение количества правил
        P = dict()

        for x in range(numberRules):
            nameRule = nameTerminalRule[x]
            inputRule = rulesInput[x].get().split()
            for i in range(len(inputRule)):
                if inputRule[i] == 'lam':
                    inputRule[i] = ""
            P[nameRule] = inputRule
        
        # Получение целевого символа
        S = input_target_symbol.get()
        VT.append("_")
        
        return {"VT": VT, "VN": VN, "P": P, "S": S}

    def count_non_term_sym(grammar, sequence):
        length = 0
        for sym in sequence:
            if sym in grammar.VT:
                length += 1
        return length

    def count_non_noterm_sym(grammar, chain):
        length = 0
        for sym in chain:
            if sym in grammar.NoTerminal:
                length += 1
        return length

    data = grammar_input()

    left_border, right_border = map(int, input_chain_range.get().split())

    grammar = Grammar(data["VT"], data["VN"], data["P"], data["S"])
    rules = list(grammar.S)
    used_sequence = set()
    step = 1
    while rules:
        sequence = rules.pop()
        if sequence in used_sequence:
            continue
        used_sequence.add(sequence)
        no_term = True
        for i, symbol in enumerate(sequence):
            if symbol in grammar.VN:
                no_term = False
                for elem in grammar.P[symbol]:
                    temp = sequence[:i] + elem + sequence[i + 1:]
                    if count_non_term_sym(grammar, temp) <= right_border and temp not in rules and count_non_noterm_sym(grammar,temp) <= right_border:
                        rules.append(temp)
                        result_text.insert(tk.END, f"Этап {step}: {temp}""\n")
                        step += 1
                step = 1
            elif symbol not in grammar.VT:
                no_term = False

                result_text.insert(tk.END, "Цепочка " + sequence + " не разрешима\n")

                break
        if no_term and left_border <= len(sequence) <= right_border:

            result_text.insert(tk.END, sequence if sequence else "lambda")
            result_text.insert(tk.END, "\n")


def createNext():
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
    for x in range(numberRules):
        input_rule = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
        input_rule_label = ttk.Label(window, text=str(index)+" Введите правила для " + str(nameTerminalRule[x]), style="styleLabel.TLabel")
        input_rule_label.pack()
        input_rule.pack()
        rulesInput.append(input_rule)
        index+=1

    input_target_symbol = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
    input_target_symbol_label = ttk.Label(window, text=str(index)+" Введите целевой символ", style="styleLabel.TLabel")
    input_target_symbol_label.pack()
    input_target_symbol.pack()

    index+=1

    input_chain_range = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
    input_chain_range_label = ttk.Label(window, text=str(index)+" Введите диапозон цепочек ОТ и ДО", style="styleLabel.TLabel")
    input_chain_range_label.pack()
    input_chain_range.pack()

    # Создание и настройка текстового поля для вывода результатов
    input_chain_range_label = ttk.Label(window, text="Полученные цепочки", style="styleLabel.TLabel")
    input_chain_range_label.pack()
    result_text = scrolledtext.ScrolledText(window, width=40, height=5, font ="helvetica 12")
    result_text.pack()

    # Создание и настройка кнопки для запуска программы
    run_button = tk.Button(window, text="ЗАПУСТИТЬ", command=run_program, font="helvetica 12", padx = 10, pady = 10, bg = "#CCFFFF", fg = "#004D40")
    run_button.pack()

# Создание основного окна


window = tk.Tk()
window.title("LAB1")
window.configure(bg='#D8BFD8')
label_style = ttk.Style()
entry_style = ttk.Style()

label_style.configure("styleLabel.TLabel", font="helvetica 12", foreground="#037360", padding=10, background="#CCFFFF", width=40)
entry_style.configure("Entry.TEntry", foreground="#004D40", background="#c7fcec")

# Создание и настройка виджетов для ввода данных
input_terminal_symbols = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
input_terminal_symbols_label = ttk.Label(window, text="1) Введите терминальные символы", style="styleLabel.TLabel")
input_terminal_symbols_label.pack()
input_terminal_symbols.pack()

input_non_terminal_symbols = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
input_non_terminal_symbols_label = ttk.Label(window, text="2) Введите не терминальные символы", style="styleLabel.TLabel")
input_non_terminal_symbols_label.pack()
input_non_terminal_symbols.pack()

input_rule_count = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
input_rule_count_label = ttk.Label(window, text="3) Введите количество правил", style="styleLabel.TLabel")
input_rule_count_label.pack()
input_rule_count.pack()

input_rule_terminal = ttk.Entry(window, style="Entry.TEntry", justify = "center", width=30, font ="helvetica 12")
input_rule_terminal_label = ttk.Label(window, text="4) Введите терминалы правил", style="styleLabel.TLabel")
input_rule_terminal_label.pack()
input_rule_terminal.pack()

nextButton = tk.Button(window, text="ДАЛЕЕ", command=createNext, font="helvetica 12", padx = 10, pady = 10, bg = "#CCFFFF", fg = "#037360")
nextButton.pack()



# Запуск главного цикла приложения
window.mainloop()