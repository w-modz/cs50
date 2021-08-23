import liau_index
import pytest


@pytest.mark.parametrize('char, expected', [
    ('a', False),
    ('|', False),
    ('7', False),
    ("'", False),
    ('!', True),
    ('?', True),
    ('.', True),
])
def test_is_punctuation(char: str, expected: bool) -> None:
    result = liau_index.is_punctuation(char)
    assert result is expected


test_text1 = 'Would you like them here or there? I would not like them here or there. I would not like them anywhere.'
test_text2 = "Congratulations! Today is your day. You're off to Great Places! You're off and away!"
test_text3 = "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since."
test_text4 = 'There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy.'


@pytest.mark.parametrize('text, expected', [
    (test_text1, 2.0),
    (test_text2, 3.0),
    (test_text3, 7.0),
    (test_text4, 9.0),
])
def test_calculate_index(text: str, expected: float) -> None:
    result = liau_index.calculate_index(text)
    assert result == expected
