class LinearProbing:
    def __init__(self, size):
        self.M = size
        #Initialize empty bucket to 0
        self.a = [0] * size
        self.quit_flag = False
    
    def hash(self, key):
        return key % self.M
    
    #insert
    def i(self, key):
        initial_position = self.hash(key)
        i = initial_position
        j = 0
        output_C = ''
        while True:
            if self.a[i] == 0:
                self.a[i] = key
                output_C = output_C + str(i)
                print(output_C)
                return
            j += 1
            #Accumulate C strings as many times as the number of collisions occurred
            output_C = output_C + 'C'
            i = (initial_position + j) % self.M
            if i == initial_position:
                break
        if i  != initial_position:
            print(output_C)
        else:
            print('Input is not possible.')

    #search
    def s(self, key):
        initial_position = self.hash(key)
        i = initial_position
        j = 1
        output_S = ''
        while self.a[i] != 0:
            if self.a[i] == key:
                output_S = output_S + str(i) + ' ' + str(key)
                print(output_S)
                return
            i = (initial_position + j) % self.M
            j += 1
            if i == initial_position:
                output_S = str(-1)
                print(output_S)
                return
        output_S = str(-1)
        print(output_S)        
        return None
    
    #quit
    def e(self):
        self.quit_flag = True
        print('quit the program.')

if __name__ == '__main__':

    input_M = input('Enter the M value : ')
    input_M = int(input_M)
    linearProbing = LinearProbing(input_M)

    while linearProbing.quit_flag == False:
        input_string = input('Enter the operation : ')
        input_string = str(input_string)

        if input_string[0]=='e':
            linearProbing.e()
        elif 9 > len(input_string[2:]) >= 6:
            if input_string[0]=='i':
                linearProbing.i(int(input_string[2:]))
            elif input_string[0]=='s':
                linearProbing.s(int(input_string[2:]))
            else:
                print('Please check the input value again.')
        else:
            print('Enter the key value with 6-8 digits..')