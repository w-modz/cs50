from cs50 import get_int

height = 9
while height < 1 or height > 8:
    height = get_int('Height: ')
row = 0
while height > 0:
    print(' ' * (height - 1), end='')
    print('#' * (row + 1))
    row += 1
    height -= 1
