from primePy import primes

class LinearProbing:
    def __init__(self, size, sizeq):
        self.M = size
        self.q = sizeq
        #Initialize empty bucket to 0
        self.a = [0] * size
        self.quit_flag = False
        self.N = 0
    
    def hash(self, key):
        return key % self.M

    def hash_2(self, key, q):
        return self.q - (key % self.q)
    
    #insert
    def i(self, key):
        initial_position = self.hash(key)
        i = initial_position
        j = 0
        output_C = ''
        while True:
            if self.a[i] == 0:
                self.a[i] = key
                self.N += 1
                output_C = output_C + str(i)
                print(output_C)
                return
            j += 1
            #Accumulate C strings as many times as the number of collisions occurred
            output_C = output_C + 'C'
            i = (initial_position + j * self.hash_2(key, self.q)) % self.M
            if self.N > self.M:
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
            i = (initial_position + j * self.hash_2(key, self.q)) % self.M
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
        self.p()

    def p(self):
        for i in range(self.M):
            print(self.a[i], ' ', end='')
        print()

if __name__ == '__main__':
    while True:
        input_M = input('Enter the M value : ')
        input_M = int(input_M)
        input_Q = input('Enter the Q value : ')
        input_Q = int(input_Q)

        if primes.check(input_M) and primes.check(input_Q):
            if input_M > input_Q:
                break
            else:
                print('Enter the Q value as a decimal fraction less than the M value..')
        else:
            print('Enter the M and Q values ​​as decimals.')
            
    linearProbing = LinearProbing(input_M, input_Q)

    while linearProbing.quit_flag == False:
        input_string = input('Enter the operation : ')
        input_string = str(input_string)

        if input_string[0]=='i':
            linearProbing.i(int(input_string[2:]))
        elif input_string[0]=='s':
            linearProbing.s(int(input_string[2:]))
        elif input_string[0]=='e':
            linearProbing.e()
        elif input_string[0]=='p':
            linearProbing.p()
        else:
            print('Please check the input value again.')