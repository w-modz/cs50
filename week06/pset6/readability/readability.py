from cs50 import get_string


def main():
    text: str = ''
    while len(text) < 1:
        text = get_string('Input text: ')
    sentenceCount = 1
    wordCount = 1
    letterCount = 1

    for index in range(len(text) - 1):
        current_char = text[index]
        if current_char.isalpha():
            letterCount += 1
        elif text[index].isspace():
            wordCount += 1
        elif is_punctuation(text[index]):
            sentenceCount += 1
        index += 1
    L = letterCount / wordCount * 100
    S = sentenceCount / wordCount * 100
    LiauIndex = 0.0588 * L - 0.296 * S - 15.8
    grade = round(LiauIndex, 0)

    if grade < 1:
        print('Before Grade 1')
    elif grade <= 16:
        print('Grade ' + str(int(grade)))
    else:
        print('Grade 16+')


def is_punctuation(char: str) -> bool:
    symbols = {'.', '!', '?'}
    return char in symbols


main()
