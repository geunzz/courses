
check_string = input('Please enter the parenthesis check formula : ')
check_string = str(check_string)

def bracket_check(check_string):
    stack = []
    flag = True
    counter = 0
    while len(check_string) > 0:
        check_string, stack, flag, counter = \
        del_character(check_string, stack, flag, counter)        
    if not len(stack) == 0:
        flag = False
    return flag, counter
    
def del_character(check_string, stack, flag, counter):
    #Processing from the end of the string to reduce the amount of computation for rewriting the string
    if check_string[-1] in (']', '}', ')'):
        counter = counter + 1
        stack.append(check_string[-1])
        check_string = check_string[:-1]
    elif check_string[-1] in ('(', '{', '['):
        counter = counter + 1
        if len(stack) == 0:
            flag = False
            check_string = check_string[:-1]
        else:
            top = stack.pop()
            if (top == ')' and check_string[-1]=='(') or\
               (top == '}' and check_string[-1]=='{') or\
               (top == ']' and check_string[-1]=='['):
                flag = True
                check_string = check_string[:-1]
            else:
                flag = False
                check_string = check_string[:-1]
    else:
    # When a non-bracket string is encountered, 
    # the number of loop repetitions is reduced by deleting all the strings from within the string.   
        check_string = check_string.replace(check_string[-1], '')
    
    return check_string, stack, flag, counter

if 1000 >= len(check_string):
    flag, counter = bracket_check(check_string)
    if flag == True:
        result_string = 'OK_' + str(counter)
    else:
        result_string = 'Wrong_' + str(counter)
    print(result_string)
else:
    print('The formula is too long. Please enter again.')


