from cs50 import get_int

answer = 9
while answer < 1 or answer > 8:
    answer = get_int('Height: ')
index = 0
while answer > 0:
    print(' ' * (answer - 1), end='')
    print('#' * (index + 1))
    index += 1
    answer -= 1
