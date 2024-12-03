with open('input.txt') as f:
    data = ''.join(f.readlines())

multiplications_sum = 0
enabled_multiplications_sum = 0
enabled = True

index = data.find('mul(')
do = data.find('do()')
dont = data.find('don\'t()')
if dont > do and dont < index:
    enabled = False

while index != -1 and index < len(data):
    start = index + 4
    end = data.find(')', start)
    numbers = data[start:end].split(',')

    if len(numbers) == 2:
        try:
            x = int(numbers[0])
            y = int(numbers[1])
            if x < 1000 and y < 1000:
                multiplications_sum += x * y
                if enabled:
                    enabled_multiplications_sum += x * y
                index = data.find('mul(', end + 1)
            else:
                index = data.find('mul(', start)
        except ValueError:
            index = data.find('mul(', start)
    else:
        index = data.find('mul(', start)
    
    do = data.rfind('do()', 0, index)
    dont = data.rfind('don\'t()', 0, index)
    if dont > do:
        enabled = False
    else:
        enabled = True

print(multiplications_sum, enabled_multiplications_sum)
