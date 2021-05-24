
class Stack_list():
    def __init__(self):
        self.stack_slice = []
        global stack

    def PUSH(self, stack, item):
        stack.append(item)
        return stack

    def POP(self, stack):
        if not stack:
            print("Stack Empty")
            item_pop = None
            stack = []
        else:
            item_pop = stack.pop(len(stack)-1)
        return stack, item_pop

    def PEEK(self, stack):
        if not stack:
            print("Stack Empty")
            item_top = None
        else:
            item_top = stack[len(stack)-1]
        return stack, item_top

    def DUP(self, stack):
        if not stack:
            print("Stack Empty")
        else:
            item_pop = stack.pop(len(stack) - 1)
            stack.append(item_pop)
            stack.append(item_pop)
        return stack

    def UpR(self, stack, n):
        if not n > len(stack):
            stack_slice = stack[len(stack) - n : len(stack)]
            stack = stack[:len(stack) - n]
            item_pop = stack_slice.pop(len(stack_slice) - 1)
            stack_slice.insert(0, item_pop)
            stack = stack + stack_slice
        return stack

    def DownR(self, stack, n):
        if not n > len(stack):
            stack_slice = stack[len(stack) - n : len(stack)]
            stack = stack[:len(stack) - n]
            item_pop = stack_slice.pop(0)
            stack_slice.insert(n - 1, item_pop)
            stack = stack + stack_slice
        return stack

    def PRINT(self, stack):
        stack_temp = stack.copy()
        stack_temp.reverse()
        stack_string = ''.join(stack_temp)
        print('stack print: ', stack_string)

stack_list = Stack_list()

global stack
stack = []

while True:
    cal_string = input('Enter the operation : ')
    cal_string = str(cal_string)

    if (cal_string[0:4] == 'PUSH') or (cal_string[0:4] == 'push'):
        if len(cal_string) == 6:
            item = cal_string[5]
            stack = stack_list.PUSH(stack, item)
        else:
            print('Check your input again.')
    elif (cal_string[0:3] == 'POP'):
        stack, item_pop = stack_list.POP(stack)
    elif (cal_string[0:4] == 'PEEK'):
        stack, item_pop = stack_list.PEEK(stack)
        print(item_pop)
    elif (cal_string[0:3] == 'UpR'):
        if len(cal_string) == 5:
            n = int(cal_string[4])
            stack = stack_list.UpR(stack, n)
        else:
            print('Check your input again.')
    elif (cal_string[0:5] == 'DownR'):
        if len(cal_string) == 7:
            n = int(cal_string[6])
            stack = stack_list.DownR(stack, n)
        else:
            print('Check your input again.')
    elif (cal_string[0:3] == 'DUP'):
        stack = stack_list.DUP(stack)
    elif (cal_string[0:5] == 'PRINT'):
        stack_list.PRINT(stack)
    else:
        print('Check your input again.')


