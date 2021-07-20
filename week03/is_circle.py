#!/usr/bin/env python3

ALICE = 0
BOB = 1
JOHN = 2
ANNA = 3
JULIA = 4
ALISTER = 5
VICTOR = 6
BARTHOLOMEW = 7
PATRICK = 8

candidates = [ALICE, BOB, JOHN, ANNA, JULIA, ALISTER, VICTOR, BARTHOLOMEW, PATRICK]
locked = [
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [True, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, True, False, False, True, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
]

def is_circle(origin: int, someone: int):
    k = someone
    for i in range(0, 8):
        if locked[i][origin] and i != origin:
            return True
        if locked[i][k]:
            k = i
            i = 0
    return False

assert is_circle(ALICE, VICTOR) == True


locked = [
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
    [False, False, False, False, False, False, False, False, False],
]