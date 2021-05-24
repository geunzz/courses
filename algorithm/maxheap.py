class MaxHeap:
    def __init__(self):
        self.heap = []
        #Do not use index 0 as dummy
        self.heap.append(0)
        self.quit_flag = False

    def size(self): return len(self.heap) - 1
    def isEmpty(self): return self.size() == 0
    def Parent(self, i): return self.heap[i//2]
    def Left(self, i): return self.heap[i*2]
    def Right(self, i): return self.heap[i*2+1]

    #print heap
    def p(self):
        #Output if size is 1 or more
        #If the size is 2 or more, including the 0th index dummy value, output
        if len(self.heap) >= 2:
            print(self.heap[1:])
        else:
            print('No value exists.')

    #insert
    def i(self, n):
        #Limit the maximum size of the heap to 100
        if len(self.heap) < 100:
            self.heap.append(n)
            i = self.size()
            while (i != 1 and n > self.Parent(i)):
                self.heap[i] = self.Parent(i)
                i = i//2
            self.heap[i] = n
            print('0')
        else:
            print('Heap size limit exceeded')
            
    #delete
    def d(self):
        parent = 1
        child = 2
        if not self.isEmpty():
            hroot = self.heap[1]
            last = self.heap[self.size()]
            while (child <= self.size()):
                if child < self.size() and self.Left(parent) < self.Right(parent):
                    child += 1
                if last >= self.heap[child]:
                    break
                self.heap[parent] = self.heap[child]
                parent = child
                child *= 2

            self.heap[parent] = last
            self.heap.pop(-1)
            return hroot

    #quit program
    def q(self):
        self.quit_flag = True
        print('quit program')

if __name__ == '__main__':

    maxHeap = MaxHeap()

    while maxHeap.quit_flag == False:
        input_string = input('Enter the operation : ')
        input_string = str(input_string)
        if input_string[0] == 'i':
            n = int(input_string[2:5])
            maxHeap.i(n)
        elif input_string[0] == 'd':
            hroot = maxHeap.d()
            print(hroot)
        elif input_string[0] == 'p':
            maxHeap.p()
        elif input_string[0] == 'q':
            maxHeap.q()
        else:
            print('The operation is not correct.')