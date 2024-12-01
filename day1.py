with open('input.txt') as f:
    data = f.readlines()

left_list = []
right_list = []

for line in data:
    left_list.append(int(line.split()[0]))
    right_list.append(int(line.split()[1]))

left_list.sort()
right_list.sort()

distance = 0
similarity = 0

for i in range(len(left_list)):
    left = left_list[i]
    right = right_list[i]
    distance += abs(left - right)

    left_in_right = right_list.count(left)
    similarity += left * left_in_right

print(distance, similarity)
