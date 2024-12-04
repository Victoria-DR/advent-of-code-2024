def search_next_letter(word_search, i, j, letter, direction):
    if letter == 'X':
        next_letter = 'M'
    elif letter == 'M':
        next_letter = 'A'
    elif letter == 'A':
        next_letter = 'S'
    else:
        return 1
    
    if i + direction[0] >= 0 and i + direction[0] < len(word_search) and j + direction[1] >= 0 and j + direction[1] < len(word_search[i]):
        if word_search[i + direction[0]][j + direction[1]] == next_letter:
            return search_next_letter(word_search, i + direction[0], j + direction[1], next_letter, direction)
    
    return 0

def check_x_mas(word_search, i, j):
    if i == 0 or i == len(word_search) - 1 or j == 0 or j == len(word_search[i]) - 1:
        return 0
    elif word_search[i - 1][j - 1] == 'M' and word_search[i + 1][j + 1] == 'S' and word_search[i - 1][j + 1] == 'M' and word_search[i + 1][j - 1] == 'S':
        return 1
    elif word_search[i - 1][j - 1] == 'S' and word_search[i + 1][j + 1] == 'M' and word_search[i - 1][j + 1] == 'M' and word_search[i + 1][j - 1] == 'S':
        return 1
    elif word_search[i - 1][j - 1] == 'S' and word_search[i + 1][j + 1] == 'M' and word_search[i - 1][j + 1] == 'S' and word_search[i + 1][j - 1] == 'M':
        return 1
    elif word_search[i - 1][j - 1] == 'M' and word_search[i + 1][j + 1] == 'S' and word_search[i - 1][j + 1] == 'S' and word_search[i + 1][j - 1] == 'M':
        return 1
    else:
        return 0

with open('input.txt') as f:
    data = f.readlines()

word_search = [list(line) for line in data]
xmas_count = 0
x_mas_count = 0

for i in range(len(word_search)):
    for j in range(len(word_search[i])):
        if word_search[i][j] == 'X':
            for k in range(-1, 2):
                for l in range(-1, 2):
                    xmas_count += search_next_letter(word_search, i, j, 'X', (k, l))
        elif word_search[i][j] == 'A':
            x_mas_count += check_x_mas(word_search, i, j)

print(xmas_count, x_mas_count)
