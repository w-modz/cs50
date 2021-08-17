from cs50 import get_string


def main():
    number = get_string('Provide number: ')
    card = []
    j = 0
    while j < len(number):
        card.append(int(number[j]))
        j += 1
    print(len(card))
    print(card)
    if card[0] == 4 and (len(card) == 16 or len(card) == 13):
        if validate(card):
            print('VISA')
        else:
            print('INVALID')
    elif card[0] == 3 and (card[1] == 4 or card[1] == 7) and len(card) == 15:
        if validate(card):
            print('AMEX')
        else:
            print('INVALID')
    elif card[0] == 5 and (card[1] == 1 or card[1] == 2 or card[1] == 3 or card[1] == 4 or card[1] == 5) \
            and len(card) == 16:
        if validate(card):
            print('MASTERCARD')
        else:
            print('INVALID')
    else:
        print('INVALID')


def validate(cardnumber):
    index = len(cardnumber) / 2
    position = 1
    sum = 0
    while index > 0:
        cardnumber[len(cardnumber) - (position * 2)] = int(cardnumber[len(cardnumber) - (position * 2)]) * 2
        if int(cardnumber[len(cardnumber) - (position * 2)]) > 9:
            sum += int(cardnumber[len(cardnumber) - (position * 2)]) % 10
            sum += int(cardnumber[len(cardnumber) - (position * 2)]) / 10
        else:
            sum += int(cardnumber[len(cardnumber) - (position * 2)])
        index -= 1
        position += 1
        sum = int(sum)
    sum += cardnumber[-1] + cardnumber[-3] + cardnumber[-5] + cardnumber[-7] + cardnumber[-9] + cardnumber[-11] + \
           cardnumber[-13] + cardnumber[-15]
    print(int(sum))
    if sum % 10 == 0:
        return True
    else:
        print('here')
        return False


main()
