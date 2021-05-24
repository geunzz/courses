class DList:
    class Node:
        def __init__(self, item, prev, link):
            self.item = item
            self.prev = prev
            self.next = link
    
    def __init__(self):
        self.head = self.Node(None, None, None)
        self.tail = self.Node(None, self.head, None)
        self.head.next = self.tail
        self.size = 0
    
    #def size(self): return self.size

    def is_empty(self): return self.size == 0

    def insert_before(self, p, item):
        t = p.prev
        n = self.Node(item, t, p)
        p.prev = n
        t.next = n
        self.size += 1

    def insert_after(self, p, item):
        t = p.next
        n = self.Node(item, p, t)
        t.prev = n
        p.next = n
        self.size += 1

    def delete(self, x):
        f = x.prev
        r = x.next
        f.next = r
        r.prev = f
        self.size -= 1
        return x.item

    def print_list(self):
        if self.is_empty():
            print('empty list')
        else:
            p = self.head.next
            while p != self.tail:
                if p.next != self.tail:
                    print(p.item, ' <=> ', end='')
                else:
                    print(p.item)
                p = p.next

    def add_r(self, r, e):
        if self.is_empty():
            if r == 1:
                self.insert_after(self.head, e)
            else:
                print('invalid position')
        elif (r > self.size + 1 ) or (r == 0):
            print('invalid position')
        else:
            p = self.head
            for i in range(1, r):
                p = p.next
            self.insert_after(p, e)

    def delete_r(self, r):
        if self.is_empty():
            print('empty list')
        elif (self.size < r) or (r == 0):
            print('invalid position')
        else:
            p = self.head
            for i in range(1, r + 1):
                p = p.next
            self.delete(p)

    def get_r(self, r):
        if self.is_empty():
            print('empty list')
        elif (self.size < r) or (r == 0):
            print('invalid position')
        else:
            p = self.head
            for i in range(1, r + 1):
                p = p.next
            self.get_item = p.item
            print(self.get_item)

    def print_without_space(self):
        if self.is_empty():
            print('empty list')
        else:
            string = []
            p = self.head.next
            while p != self.tail:
                if p.next != self.tail:
                    string.append(str(p.item))
                else:
                    string.append(str(p.item))
                p = p.next
            string_sum = ''.join(string)
            print(string_sum)

class EmptyError(Exception):
    pass

s = DList()

cal_num = input('type the caculation number : ')
cal_num = int(round(float(cal_num)))

while cal_num > 0:
    calculation = input('Enter the operation type, rank, and element order : ')
    calculation = str(calculation)
    if (calculation[0] == 'A') or (calculation[0] == 'a'):
        s.add_r(int(calculation[1]), calculation[2])
    elif (calculation[0] == 'D') or (calculation[0] == 'd'):
        s.delete_r(int(calculation[1]))
    elif (calculation[0] == 'G') or (calculation[0] == 'g'):
        s.get_r(int(calculation[1]))
    elif (calculation[0] == 'P') or (calculation[0] == 'p'):
        s.print_without_space()
    else:
        print('wrong input.')
        break
    cal_num = cal_num - 1
