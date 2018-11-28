class Stack:
    def __init__(self):
        self.stack = []

    def push(self,key):
        self.stack.append(key)

    def pop(self):
        if self.stack == []:
            return "Underflow error"

        else:
            return self.stack.pop()

    def __str__(self):
        return str(self.stack)

S = Stack()
exp = raw_input().split()

for var in exp:
    try:
        S.push(int(var))
    except:
        S.push(var)

priority = {'(':7, ')':6, '^':5, '/':4, '*':3, '+':2, '-':1 }

def infixToPostfix(S):
    stack = S.stack
    temp = []
    operator = []
    for var in stack:
        if type(var) != int:
            if (operator != [] and priority[var] < priority[operator[-1]]):
                while(operator != []):
                    if operator[-1] == ")" or operator[-1] == "(": break
                    else: temp.append(operator.pop())
            if(var != ")"):
                operator.append(var)
            else:
                i = -1
                while i > -(len(operator)):
                    if operator[i] == "(":
                        operator.pop()
                        break
                    else:
                        temp.append(operator.pop())
        else:
            temp.append(var)

    if operator[0] == "(":
        operator.pop(0)

    while (operator != []) :
        temp.append(operator.pop())

    return temp

def evaluationOfPostfix(exp):
    temp = []
    i = 0
    while i < len(exp):
        if type(exp[i]) == int:
            temp.append(exp[i])
        else:
            op = exp[i]
            b = temp.pop()
            a = temp.pop()
            if op == '*':r = a * b
            elif op == '^':r = a ** b
            elif op == '/':r = float(a)/b
            elif op == '+':r = a + b
            elif op == '-':r = a - b
            temp.append(r)
        i += 1

    return temp[0]


print infixToPostfix(S)
print evaluationOfPostfix(infixToPostfix(S))




        