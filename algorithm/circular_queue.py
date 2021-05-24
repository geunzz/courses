
class CircularQueue:
    def __init__(self, q):
        self.MAX_QSIZE = q
        self.front = 0
        self.rear = 0
        self.items = [0]*self.MAX_QSIZE

    def isEmpty(self): return self.front == self.rear
    def isFull(self): return self.front == (self.rear+1) % self.MAX_QSIZE

    def I(self, item):
        global flag_quit
        if not self.isFull():
            self.rear = (self.rear + 1) % self.MAX_QSIZE
            self.items[self.rear] = item
        else: #Program is terminated with flag in case of overflow
            print('Overflow ', self.items)
            flag_quit = True

    def D(self):
        global flag_quit
        if not self.isEmpty():
            self.front = (self.front + 1) % self.MAX_QSIZE
            self.items[self.front] = 0
        else: #Program is terminated with flag in case of uverflow
            print('Underflow')
            flag_quit = True

    def P(self):
        print(self.items)

q_size = input('Enter the size of the circular cue : ')
q_size = int(q_size)
n_cal_lim = input('Enter the number of operations : ')
n_cal_lim = int(n_cal_lim)

global flag_quit
flag_quit = False
q = CircularQueue(q_size)

n = 0
while (n < n_cal_lim) and (flag_quit == False):
    cal_string = input('Enter the operation : ')
    cal_string = str(cal_string)
    if cal_string[0] == 'I':
        q.I(int(cal_string[2:]))
    elif cal_string[0] == 'D':
        q.D()
    elif cal_string[0] == 'P':
        q.P()
    else:
        print('Please enter the calculation correctly.')
    n = n + 1