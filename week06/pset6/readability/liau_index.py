import math

SYMBOLS = {'.', '!', '?'}


def calculate_index(text: str) -> float:
    sentence_count = 1
    word_count = 1
    letter_count = 1

    for index in range(len(text) - 1):
        current_char = text[index]
        if current_char.isalpha():
            letter_count += 1
        elif text[index].isspace():
            word_count += 1
        elif is_punctuation(text[index]):
            sentence_count += 1
        index += 1

    L = letter_count / word_count * 100
    S = sentence_count / word_count * 100
    LiauIndex = 0.0588 * L - 0.296 * S - 15.8

    grade = math.floor(LiauIndex)
    return grade


def is_punctuation(char: str) -> bool:
    return char in SYMBOLS
