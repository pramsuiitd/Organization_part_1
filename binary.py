import random

class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
class BT:
    def __init__(self):
        self.root = None
    
    def insert(self, val):
        if not self.root:
            self.root = Node(val)
            return
        q = []
        q.append(self.root)
        while len(q):
            a = random.randint(0,1)
            if(a):
                temp = q[0]
                q.pop(0)
                if not temp.left:
                    temp.left = Node(val)
                    break
                q.append(temp.left)
            else:
                temp = q[0]
                q.pop(0)
                if not temp.right:
                    temp.right = Node(val)
                    break
                q.append(temp.right)

def randBT(count:int = 1):
    bt = BT()
    for _ in range(1,count+1):
        rval = _
        bt.insert(rval)
    return bt.root


def inorder(temp, l):
    if (not temp):
        print(-1,end = " ")
        l.append(-1)
        return
    print(temp.val,end = " ")
    l.append(temp.val)
    inorder(temp.left, l)
    inorder(temp.right, l)
    return


a = random.randint(1024,2048)

headRand = randBT(a)
x = []
inorder(headRand,x)
y = x.copy()
try:
    while True:
        y.remove(-1)
except Exception as excess:
    print()
    
list_of_commands = ["level","diameter","distance",
                    "employees_at_same_level","immediate_team","boss","team_size"]

n = (1000-2) # Number of commands
print(n+2)
print("get_employees")
print(list_of_commands[1])
for i in range(n):
    k = random.randint(0,6)
    j = list_of_commands[k]
    if k == 1:
        continue
    elif k == 0 or k == 3 or k == 4 or k == 5 or k == 6:
        random_num = random.choice(y)
        print(j,random_num)
    else:
        num_1 = random.choice(y)
        num_2 = random.choice(y)
        print(j,num_1,num_2)
