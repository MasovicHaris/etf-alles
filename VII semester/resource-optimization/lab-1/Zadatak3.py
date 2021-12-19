import random
chars = ['A', 'B', 'C', 'D', 'E']
def generate(M):
    list = []
    for i in range(0, M):
        list.append(random.choice(chars))
    return list

def slicnost(list1, list2):
    s = 0
    for i in range(0, len(list1)):
        if list1[i] == list2[i]:
            s += 1
    return s

def najslicnije(lists):
    list1, list2, s = lists[0], lists[1], slicnost(lists[0], lists[1])
    for i in range(0, len(lists)):
        for j in range(0, i):
            if slicnost(lists[i], lists[j]) > s:
                list1, list2, s = lists[i], lists[j], slicnost(lists[i], lists[j])
    return (list1, list2)

N, M  = 2, 4
lists = []
for i in range(0, N):
    lists.append(generate(M))
    
print(lists)
print(najslicnije(lists))
