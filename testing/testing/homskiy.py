import re
import sys
sys.dont_write_bytecode = True
old_print = print
file_output = open('output.txt', 'w')
do_print = False


def set_print(boolean):
    global do_print
    do_print = boolean
def print_result(boolean):
    if boolean:
        print('"%s" - ACCEPTED' % test)
    else:
        print('"%s" - REJECTED' % test)
    quit(0)
def print(*args, **kwargs):
    if do_print:
        old_print(*args, **kwargs)
        old_print(*args, **kwargs, file=file_output)
def format_matrix(header,lefter,matrix,top_format='{:^{}}',left_format='{:<{}}',cell_format='{:^{}}',row_delim='\n',col_delim=' | '):
    table = [[''] + header] + [[name] + row for name, row in zip(lefter, matrix)]
    table_format = [['{:^{}}'] + len(header) * [top_format]] \
                 + len(matrix) * [[left_format] + len(header) * [cell_format]]
    col_widths = [max(
                      len(format.format(cell, 0))
                      for format, cell in zip(col_format, col))
                  for col_format, col in zip(zip(*table_format), zip(*table))]
    return row_delim.join(
               col_delim.join(
                   format.format(cell, width)
                   for format, cell, width in zip(row_format, row, col_widths))
               for row_format, row in zip(table_format, table))
def get_sequence():
    i = 1
    while True:
        yield i
        i += 1
def get_index():
    for i in get_sequence():
        yield '\S%s' % i
def get_error_index():
    for i in get_sequence():
        yield 'ERROR %s:' % i
errors = {}
index = get_index()
index_error = get_error_index()
def add_error(identifier, string):
    errors[identifier] = next(index_error), string
def err(identifier, *args):
    set_print(True)
    err_num, string = errors[identifier]
    print('%s %s' % (err_num, string % args))
    quit(0)

def print_rules(rules):
    for key in sorted(rules):
        print( key + ' -> ' + ' | '.join(' '.join(i) for i in rules[key]))
    print()

#def print_rules(rules):
#    for key in sorted(rules):
#        print( key + ' ' + ' | '.join(' '.join(i) for i in rules[key]))
#    print()

def return_file(rules):
    fileGrammar = open('returnHomskiy.txt','w')
    string = ""
    for key in sorted(rules):
        string += ( key + ' ' + ' | '.join(' '.join(i) for i in rules[key]))
        string += "\n"
    fileGrammar.write(string)
    fileGrammar.close()
def enter_file(rules):
    fileGrammar = open('enterHomskiy.txt','w')
    string = ""
    for key in sorted(rules):
        string += ( key + ' -> ' + ' | '.join(' '.join(i) for i in rules[key]))
        string += "\n"
    fileGrammar.write(string)
    fileGrammar.close()

initial = open('grammarHom.txt').read()
test = open('test.txt').read()

specials = ['\eps', '\...']
eps, dots = specials
hidden_specials = ['\$']
end = hidden_specials[0]

escaped = ['\|', '\\\\']

def replace_escaped(string):
    for esc in escaped:
        string = string.replace(esc, esc[1:])
    return string
def make_grammar():
    all_rules = [i for i in initial.split('\n') if i != '']
    S0 = ''

    formatted_rules = []
    for rule in all_rules:
        old_rule = rule
        sp = rule.split('->', 1)
        if len(sp) < 2: err('no ->', old_rule)
        sp[0] = sp[0].strip()
        if len(sp[0].split()) > 1: err('two nons before ->', rule)
        if '\\' in sp[0]: err('\\ in nonterm', rule)
        if not S0: S0 = sp[0]
        formatted_rules += (sp[0], sp[1]),

    rules = {}
    for nonterm, right_side in formatted_rules:
        right_side = [i.strip() for i in re.split('(?<!\\\\)[|]{1}', right_side) if i.strip() != '']
        for i, t in enumerate(right_side):
            old_rules = rules.get(nonterm, [])
            if t not in old_rules:
                if '\\' in t and t not in specials and sum(t.count(j) for j in escaped) != t.count('\\') - t.count(
                        '\\\\'):
                    err('bad escape', t)
                if t == dots:
                    if i == 0:
                        err('empty before \...', '  |  '.join(right_side))
                    elif i == len(right_side) - 1:
                        err('empty after \...', '  |  '.join(right_side))
                    else:
                        if len(right_side[i - 1]) != 1:
                            err('mult symbols before \...', '  |  '.join(right_side))
                        elif len(right_side[i + 1]) != 1:
                            err('mult symbols after \...', '  |  '.join(right_side))
                        elif ord(right_side[i + 1]) - ord(right_side[i - 1]) < 1:
                            err('a \... b, a > b')
                        else:
                            dotted_symbols = [chr(i) for i in range(ord(right_side[i - 1]) + 1, ord(right_side[i + 1]))]
                            rules[nonterm] = old_rules + dotted_symbols
                else:
                    rules[nonterm] = old_rules + [replace_escaped(t)]

    terms = []
    nonterms = rules.keys()

    for key in sorted(rules):
        new_rules = []
        for rule in rules[key]:

            if rule == eps:
                new_rules += [eps],
                continue

            curr_rules = []

            curr_terms = rule.split()

            for curr_term in curr_terms:
                if curr_term in nonterms:
                    curr_rules += curr_term,

                else:
                    curr_rules += list(curr_term)

            new_rules += curr_rules,

        rules[key] = new_rules

    for key in sorted(rules):
        for rule in rules[key]:
            for term in rule:
                if term != eps and term not in nonterms and term not in terms:
                    terms += term,

    print('Recognized nonterms:', ', '.join(nonterms))
    print('Recognized terms:', ', '.join(terms))

    print()
    print('Parsed rules: ')
    print_rules(rules)

    return S0, terms, nonterms, rules
def to_homsky():

    S0, terms, nonterms, rules = make_grammar()

    print('Add new initial nonterm "\S0"')
    rules['\S0'] = [[S0]]
    print_rules(rules)

    print('Move terms into separate rules')

    separated_terms = {}

    for key in sorted(rules):
        for rule in rules[key]:
            if len(rule) > 1:
                for i, term in enumerate(rule):
                    if term in terms:
                        if term not in separated_terms:
                            new_key = next(index)
                            rules[new_key] = [[term]]
                            rule[i] = new_key
                            separated_terms[term] = new_key
                        else:
                            rule[i] = separated_terms[term]

    print_rules(rules)

    print('Break rules with length more than 2')
    for key in sorted(rules):
        for rule in rules[key]:
            if len(rule) > 2:
                new_key = next(index)
                rules[new_key] = [rule[1:]]
                del rule[1:]
                rule += new_key,
                old_key = new_key
                while len(rules[old_key][0]) > 2:
                    new_key = next(index)
                    rules[new_key] = [rules[old_key][0][1:]]
                    del rules[old_key][0][1:]
                    rules[old_key][0] += new_key,
                    old_key = new_key

    print_rules(rules)
    print('Delete epsilon - rules in rules with two nonterminals')

    something_changed = True
    while something_changed:
        something_changed = False

        for key in sorted(rules):
            for rule in rules[key]:

                if len(rule) == 2:
                    if rules[rule[0]] == [[eps]] and rules[rule[1]] == [[eps]]:
                        rule[:] = [eps]
                        something_changed = True

                    elif rules[rule[0]] != [[eps]] and rules[rule[1]] == [[eps]]:
                        rule[:] = [rule[0]]
                        something_changed = True

                    elif rules[rule[0]] == [[eps]] and rules[rule[1]] != [[eps]]:
                        rule[:] = [rule[1]]
                        something_changed = True

                elif len(rule) == 1 and rule != [eps] and rule[0] in nonterms and rules[rule[0]] == [[eps]]:
                    rule[:] = [eps]
                    something_changed = True

    print_rules(rules)
    print('Delete single epsilon - rules and move single epsilon rule from "%s" to "\S0" if it exists' % S0)

    something_changed = True
    while something_changed:
        something_changed = False
        for key in sorted(rules):
            if key != '\S0':
                if rules[key] == [[eps]]: del rules[key]
                else:
                    if [eps] in rules[key]:
                        something_changed = True
                        new_rules = []
                        for rule in rules[key]:
                            if rule == [eps]:
                                for other_key in sorted(rules):
                                    if key != other_key:
                                        other_new_rules = []
                                        for other_rule in rules[other_key]:
                                            if key in other_rule:
                                                if len(other_rule) == 1:
                                                    other_new_rules += [key],
                                                    if [eps] not in rules[other_key]:
                                                        other_new_rules += [eps],
                                                elif len(other_rule) == 2:
                                                    if other_rule[0] == key and other_rule[1] == key:
                                                        other_new_rules += [key, key],
                                                        if [key] not in rules[other_key]:
                                                            other_new_rules += [key],
                                                        if [eps] not in rules[other_key]:
                                                            other_new_rules += [eps],
                                                    elif other_rule[0] == key and other_rule[1] != key:
                                                        other_new_rules += other_rule,
                                                        if other_rule[1] not in rules[other_key]:
                                                            other_new_rules += [other_rule[1]],
                                                    elif other_rule[0] != key and other_rule[1] == key:
                                                        other_new_rules += other_rule,
                                                        if other_rule[0] not in rules[other_key]:
                                                            other_new_rules += [other_rule[0]],
                                            else:
                                                other_new_rules += other_rule,
                                        rules[other_key][:] = other_new_rules
                                break
                        for rule in rules[key]:
                            if rule != [eps]:
                                if key in rule:
                                    if len(rule) == 2:
                                        if rule[0] == key and rule[1] == key:
                                            new_rules += [key, key],
                                        elif rule[0] == key and rule[1] != key:
                                            new_rules += rule,
                                            if rule[1] not in rules[key]:
                                                new_rules += [rule[1]],
                                        elif rule[0] != key and rule[1] == key:
                                            new_rules += rule,
                                            if rule[0] not in rules[key]:
                                                new_rules += [rule[0]],
                                else:
                                    new_rules += rule,
                        rules[key][:] = new_rules

    print_rules(rules)
    print('Delete duplicates')

    for key in sorted(rules):
        new_rules = []
        for rule in rules[key]:
            if rule not in new_rules:
                new_rules += rule,
        rules[key][:] = new_rules

    print_rules(rules)

    def find_cycles(path, key, rules, nonterms):
        if key in path:
            err('recursion', ' -> '.join(list(path[path.index(key):]) + [key]))
        new_path = tuple(list(path) + [key])
        for rule in rules[key]:
            if len(rule) == 1 and rule[0] in nonterms:
                find_cycles(new_path, rule[0], rules, nonterms)

    for key in sorted(rules):
        rules[key][:] = [rule for rule in rules[key] if rule != [key]]

    for key in sorted(rules):
        find_cycles((), key, rules, nonterms)

    print('Delete unused rules')

    def depth_search(marked, key, rules):
        marked = tuple(list(marked) + [key])
        for rule in rules[key]:
            for term in rule:
                if term in nonterms and term not in marked:
                    marked = depth_search(marked, term, rules)
        return marked

    used_in_rules = depth_search((), '\S0', rules)

    for key in sorted(rules):
        if key not in used_in_rules:
            del rules[key]

    print_rules(rules)
    print('Remove chain rules')

    something_changed = True
    while something_changed:
        something_changed = False

        for key in sorted(rules):
            new_rules = []
            for rule in rules[key]:
                if len(rule) == 2:
                    new_rules += rule,
                elif len(rule) == 1:
                    if rule[0] in nonterms:
                        new_rules += rules[rule[0]]
                        something_changed = True
                    else:
                        new_rules += rule,
            rules[key][:] = new_rules

    rules[S0][:] = [i for i in rules[S0] if i != [eps]]

    used_in_rules = depth_search((), '\S0', rules)

    for key in sorted(rules):
        if key not in used_in_rules:
            del rules[key]

    print_rules(rules)
    return_file(rules)
    enter_file(rules)
    return_validator()
    return terms, list(nonterms), rules

def return_validator():
    fileGrammar = open("returnHomskiy.txt", "r")

    lines = fileGrammar.readlines()
    index = 0;
    NonTerminalCheck = []
    NonTerminalString = ""
    startSymbol = ""
    TerminalString = ""
    rulesString = ""

    for i,line in enumerate(lines):
        lineArr = line.split(" ")
        if lineArr[0][0] == "\\":
            lineArr[0] = lineArr[0].replace("\\", "")
        if lineArr[0] == "S" or lineArr[0] == "S0":
            startSymbol = "<" + lineArr[0] + ">"
        NonTerminalCheck.append(lineArr[0])
        if i != 0:
            NonTerminalString += " "
        NonTerminalString += "<" + lineArr[0] + ">"

    for line in lines:
        lineArr = line.rstrip().split(" ")     
        newLineArr = lineArr[1:]
        for el in newLineArr:
            
            if el[0] == "\\":
                el = el.replace("\\", "")
            if el in NonTerminalCheck:
                rulesString += "<" + el + ">"
            elif el == "|":
                rulesString += " "
            else:
                rulesString += el

        rulesString += "\n"
    fileGrammar.close
    fileGrammar = open("returnHomskiy.txt", "w")
    string = ""
    string += startSymbol + "\n"
    string += NonTerminalString + "\n"
    string += rulesString
    fileGrammar.write(string)
#if __name__ == '__main__':
#    set_print(True)
#    to_homsky()