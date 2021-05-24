class Chaining:
    class Node:
        def __init__(self, key, link):
            self.key = key
            self.next = link

    def __init__(self, size):
         self.M = size
         self.a = [None] * size
         self.quit_flag = False
         self.key_list = []

    def hash(self, key):
        return key % self.M
    
    #삽입
    def i(self, key):
        i = self.hash(key)
        p = self.a[i]
        if key not in self.key_list:
            self.key_list.append(key)
            while p != None:
                p = p.next
            self.a[i] = self.Node(key, self.a[i])
        else:
            print('The key value already exists.')

    #삭제
    def d(self, key):
        i = self.hash(key)
        p = self.a[i]
        #Key index calculation in the connected chane
        self.chane_index = 1
        
        #When index 1 of self.a[i] is the target of deletion
        if p != None:
            if key == p.key:
                self.a[i] = p.next
                print(self.chane_index)
                return 
        #If the above conditions are not satisfied, 
        #search and delete from index 2 of self.a[i]
            t = p.next
            while t != None:
                self.chane_index = self.chane_index + 1
                if key == t.key:
                    temp = p.next
                    p.next = temp.next
                    print(self.chane_index)
                    return 
                p = p.next
                t = t.next
            self.chane_index = 0
            print(self.chane_index)
        return  self.chane_index

    #search
    def s(self, key):
        i = self.hash(key)
        p = self.a[i]
        #Key index calculation in the connected chane
        self.chane_index = 0
        while p != None:
            self.chane_index = self.chane_index + 1
            if key == p.key:
                print(self.chane_index)
                return self.chane_index
            p = p.next
        self.chane_index = 0
        print(self.chane_index)
        return  self.chane_index

    #print
    def p(self):
        for i in range(self.M):
            p =self.a[i]
            while p != None:
                print(p.key, end=' ')
                p = p.next
        print()
    
    #quit
    def e(self):
        self.quit_flag = True
        print('quit the program.')

if __name__ == '__main__':

    input_M = input('Enter the M value : ')
    input_M = int(input_M)
    chaining = Chaining(input_M)
    while chaining.quit_flag == False:
        input_string = input('Enter the operation : ')
        input_string = str(input_string)

        if input_string[0]=='i':
            chaining.i(int(input_string[2:]))
        elif input_string[0]=='s':
            chaining.s(int(input_string[2:]))
        elif input_string[0]=='d':
            chaining.d(int(input_string[2:]))
        elif input_string[0]=='p':
            chaining.p()
        elif input_string[0]=='e':
            chaining.e()
        else:
            print('Please check the input value again.')
