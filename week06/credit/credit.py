from cs50 import get_string


def main():
    number = get_string('Provide card number: ')
    card_number = parse_card_number(number)
    # Store credit card length in a variable
    global ccn_length
    ccn_length = len(card_number)

    if is_visa(card_number):
        if validate(card_number):
            print('VISA')
            return
        else:
            print('INVALID')
            return
    elif is_amex(card_number):
        if validate(card_number):
            print('AMEX')
            return
        else:
            print('INVALID')
            return
    elif is_mastercard(card_number):
        if validate(card_number):
            print('MASTERCARD')
            return
        else:
            print('INVALID')
            return
    else:
        print('INVALID')


def parse_card_number(number):
    card_number = []
    j = 0
    while j < len(number):
        card_number.append(int(number[j]))
        j += 1
    return card_number


def is_visa(card: list[int]) -> bool:
    return card[0] == 4 and (ccn_length == 16 or ccn_length == 13)


def is_amex(card: list[int]) -> bool:
    return card[0] == 3 and (card[1] == 4 or card[1] == 7) and ccn_length == 15


def is_mastercard(card: list[int]) -> bool:
    return card[0] == 5 and (card[1] == 1 or card[1] == 2 or card[1] == 3 or card[1] == 4 or card[1] == 5) and \
           ccn_length == 16


def validate(cardnumber):
    cardnumber_len = len(cardnumber)
    index = cardnumber_len / 2
    position = 1
    sum = 0
    while index > 0:
        cardnumber[cardnumber_len - (position * 2)] = int(cardnumber[cardnumber_len - (position * 2)]) * 2
        if int(cardnumber[cardnumber_len - (position * 2)]) > 9:
            sum += int(cardnumber[cardnumber_len - (position * 2)]) % 10
            sum += int(cardnumber[cardnumber_len - (position * 2)]) / 10
        else:
            sum += int(cardnumber[cardnumber_len - (position * 2)])
        index -= 1
        position += 1
        sum = int(sum)
    reverse = 1
    while True:
        if reverse > ccn_length:
            break
        sum += cardnumber[-reverse]
        reverse += 2
    print(int(sum))
    if sum % 10 == 0:
        return True
    else:
        print('here')
        return False


main()
