from cs50 import get_float

owed = get_float('Change owed: ')
while owed < 0:
    owed = get_float('Change owed: ')
print(owed)
change = 0
while owed >= 0.25:
    owed -= 0.25
    change += 1
    round(owed, 2)
while owed >= 0.10:
    owed -= 0.10
    change += 1
    round(owed, 2)
while owed >= 0.05:
    owed -= 0.05
    change += 1
    round(owed, 2)
while owed > 0:
    owed -= 0.01
    change += 1
    round(owed, 2)
print(change)
