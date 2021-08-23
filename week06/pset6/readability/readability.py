import liau_index


def main():
    text: str = ''
    while len(text) < 1:
        text = input('Input text: ')

    grade = liau_index.calculate_index(text)
    if grade < 1:
        print('Before Grade 1')
    elif grade <= 16:
        print('Grade ' + str(int(grade)))
    else:
        print('Grade 16+')


if __name__ == "__main__":
    main()
