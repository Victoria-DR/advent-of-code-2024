orderings = {}
updates = []

with open('input.txt') as f:
    line = f.readline().strip()
    while line != '':
        x, y = [int(z) for z in line.split('|')]
        if x not in orderings:
            orderings[x] = [[], [y]]
        else:
            orderings[x][1].append(y)
        if y not in orderings:
            orderings[y] = [[x], []]
        else:
            orderings[y][0].append(x)
        line = f.readline().strip()
    
    line = f.readline().strip()
    while line != '':
        updates.append([int(z) for z in line.split(',')])
        line = f.readline().strip()

middle_pages_sum = 0
reordered_middle_pages_sum = 0

for update in updates:
    correct_order = True
    for i in range(len(update)):
        for j in range(0, i):
            if update[j] in orderings[update[i]][1]:
                correct_order = False
                break
        for k in range(i + 1, len(update)):
            if update[k] in orderings[update[i]][0]:
                correct_order = False
                break
        if not correct_order:
            break
    
    if correct_order:
        middle_pages_sum += update[len(update) // 2]
    else:
        reordered_update = []
        for i in range(len(update)):
            if i == 0:
                reordered_update.append(update[i])
            else:
                insert_index = None
                for j in range(len(reordered_update)):
                    if update[i] in orderings[reordered_update[j]][0]:
                        reordered_update.insert(j, update[i])
                        insert_index = None
                        break
                    elif update[i] in orderings[reordered_update[j]][1]:
                        insert_index = j + 1
                if insert_index is not None:
                    reordered_update.insert(insert_index, update[i])
        reordered_middle_pages_sum += reordered_update[len(reordered_update) // 2]

print(middle_pages_sum, reordered_middle_pages_sum)
