from cs50 import get_float

owed = get_float('Change owed: ')
while owed < 0:
    owed = get_float('Change owed: ')
change = 0
change += int(owed / 0.25)
owed %= 0.25
owed = round(owed, 2)
change += int(owed / 0.10)
owed %= 0.10
owed = round(owed, 2)
change += int(owed / 0.05)
owed %= 0.05
owed = round(owed, 2)
change += int(owed / 0.01)
print(change)
