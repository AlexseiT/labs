def remove_empty_rules(grammar):
    new_grammar = []
    empty_symbols = set()
    for rule in grammar:
        if rule[1] == 'ε':
            empty_symbols.add(rule[0])
        else:
            new_grammar.append(rule)
    while True:
        updated = False
        for rule in new_grammar:
            for symbol in rule[1]:
                if symbol in empty_symbols:
                    new_rule = (rule[0], rule[1].replace(symbol, ''))
                    if new_rule not in new_grammar:
                        new_grammar.append(new_rule)
                        updated = True
        if not updated:
            break
    return new_grammar


def remove_unit_rules(grammar):
    new_grammar = []
    unit_rules = []
    for rule in grammar:
        if len(rule[1]) == 1 and rule[1].isupper():
            unit_rules.append(rule)
        else:
            new_grammar.append(rule)
    while unit_rules:
        rule = unit_rules.pop(0)
        for unit_rule in grammar:
            if unit_rule[0] == rule[1]:
                new_rule = (rule[0], unit_rule[1])
                if new_rule not in new_grammar:
                    new_grammar.append(new_rule)
                    unit_rules.append(new_rule)
    return new_grammar


def convert_long_rules(grammar):
    new_grammar = []
    for rule in grammar:
        if len(rule[1]) > 2:
            new_symbols = []
            for symbol in rule[1]:
                if symbol.islower():
                    new_nonterminal = symbol.upper()
                    new_grammar.append((new_nonterminal, symbol))
                    new_symbols.append(new_nonterminal)
                else:
                    new_symbols.append(symbol)
            new_grammar.append((rule[0], ''.join(new_symbols)))
        else:
            new_grammar.append(rule)
    return new_grammar


def get_alphabet(grammar):
    terminals = set()
    nonterminals = set()
    for rule in grammar:
        nonterminals.add(rule[0])
        for symbol in rule[1]:
            if symbol.islower():
                terminals.add(symbol)
            else:
                nonterminals.add(symbol)
    return terminals, nonterminals


def remove_terminals(grammar, terminals):
    new_grammar = []
    for rule in grammar:
        if len(rule[1]) > 1:
            new_symbols = []
            for symbol in rule[1]:
                if symbol in terminals:
                    new_nonterminal = symbol.upper()
                    new_grammar.append((new_nonterminal, symbol))
                    new_symbols.append(new_nonterminal)
                else:
                    new_symbols.append(symbol)
            new_grammar.append((rule[0], ''.join(new_symbols)))
        else:
            new_grammar.append(rule)
    return new_grammar


def convert_to_chomsky_bnf(grammar):
    terminals, nonterminals = get_alphabet(grammar)
    grammar = remove_empty_rules(grammar)
    grammar = remove_unit_rules(grammar)
    grammar = convert_long_rules(grammar)
    grammar = remove_terminals(grammar, terminals)

    # Удаление дубликатов правил
    grammar = list(set(grammar))

    return grammar



# Пример использования
#grammar = [
#    ('S', 'olA'),
#    ('S', 'ooB'),
#    ('S', 'llB'),
#    ('S', 'loA'),
#    ('A', 'loB'),
#    ('A', 'olS'),
#    ('A', 'loS'),
#    ('A', 'olB'),
#    ('B', 'S'),
#    ('B', 'ε'),
#]
grammar = [
    ('S', 'ASB'),
    ('S', 'ε'),
    ('A', 'aA'),
    ('A', 'ε'),
    ('B', 'bB'),
    ('B', 'b'),
]
chomsky_bnf_grammar = convert_to_chomsky_bnf(grammar)
for rule in chomsky_bnf_grammar:
    print(rule[0] + ' -> ' + rule[1])