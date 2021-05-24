class DNode:
    def __init__ (self, elem, prev=None, next=None):
        self.data = elem
        self.prev = prev
        self.next = next
          
class Deque:
    def __init__ (self):
        self.front = None
        self.rear = None
        self.flag_quit = False

    def isEmpty(self): return self.front == None
    def clear(self): self.front = self.rear = None

    #Add element item before deque
    def add_front(self, item):
        node = DNode(item, None, self.front)
        if self.isEmpty():
            self.front = self.rear = node
        else:
            self.front.prev = node
            self.front = node
    
    #Add element item after deque
    def add_rear(self, item):
        node = DNode(item, self.rear, None)
        if self.isEmpty():
            self.front = self.rear = node
        else:
            self.rear.next = node
            self.rear = node
    
    #Delete and return the element before deque
    def delete_front(self):
        if not self.isEmpty():
            data = self.front.data
            self.front = self.front.next
            if self.front == None:
                self.rear = None
            else:
                self.front.prev = None

        #If deque is empty, output underflow and set end flag to true
        else:
            data = None
            print('Underflow')
            self.flag_quit = True
            return data
    
    #Delete and return the element after deque
    def delete_rear(self):
        #if deque is not empty
        if not self.isEmpty():
            data = self.rear.data
            self.rear = self.rear.prev
            if self.rear == None:
                self.front = None
            else:
                self.rear.next = None
        #If deque is empty, output underflow and set end flag to true
        else:
            data = None
            print('Underflow')
            self.flag_quit = True
            return data

    def print(self):
        p = self.front
        while p:
            if p.next != None:
                print(p.data, ' ', end='')
            else:
                print(p.data)
            p = p.next

deque = Deque()

calc_num = input('Enter the number of operations : ')
calc_num = int(calc_num)

while (deque.flag_quit == False) and (calc_num > 0):
    calc_string = input('Enter the operation : ')
    calc_string = str(calc_string)

    if calc_string[0:2] == 'AF':
        deque.add_front(int(calc_string[3:5]))
    elif calc_string[0:2] == 'AR':
        deque.add_rear(int(calc_string[3:5]))
    elif calc_string[0:2] == 'DF':
        deque.delete_front()
    elif calc_string[0:2] == 'DR':
        deque.delete_rear()
    elif calc_string[0] == 'P':
        deque.print()
    else:
        print('Enter the operation again')

    calc_num = calc_num - 1