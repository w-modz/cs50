from cs50 import get_string

text = get_string('Input text: ')
sentenceCount = 1
wordCount = 1
letterCount = 1

index = 0
while index < (len(text) - 1):
    if text[index].isalpha():
        letterCount += 1
    elif text[index].isspace():
        wordCount += 1
    elif text[index] in ['.', '!', '?']:
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
