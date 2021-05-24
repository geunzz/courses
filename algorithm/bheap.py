class BHeap():
    def __init__(self, a):
        self.a = a
        #Do not use index 0 as dummy
        self.a.insert(0, 0)
        self.N = len(a) - 1

    #Create a bottom-up heap with input elements
    def create_heap(self):
        for i in range(self.N//2, 0, -1):
            self.downheap(i)

    #Rearrangement to the maximum heap using the downheap method
    def downheap(self, i):
        while 2*i <= self.N:
            k = 2*i
            if k < self.N and self.a[k] < self.a[k+1]:
                k += 1
            if self.a[i] > self.a[k]:
                break
            self.a[i], self.a[k] = self.a[k], self.a[i]
            i = k

    #Excluding the 0th dummy, print
    def print_heap(self):
            print(self.a[1:])

if __name__ == '__main__':
    key_num = input('Please enter the number of keys : ')
    #Limit the maximum size of the heap to 100
    if int(key_num) < 100:
        keys = input('Enter the keys : ')
        key_list = list(map(int, keys.split()))
        if len(key_list) == int(key_num):
            bheap = BHeap(key_list)
            bheap.create_heap()
            bheap.print_heap()
        else:
            print('The number of keys entered does not match.')
    else:
        print('Please enter less than 100 keys.')