import pytest

import ShortTandemRepeats
from ShortTandemRepeats import ShortTandemRepeats as STR


@pytest.mark.parametrize('str1, str2, expected', [
    (
        STR({'name': 'Bar', 'AGATC': 18}),
        STR({'name': 'Foo', 'AGATC': 18}),
        True,
    ),
    (
        STR({'name': 'Foo', 'AGATC': 18}),
        STR({'name': 'Foo', 'AGATC': 4}),
        False,
    ),
    (
        STR({'name': 'Bar', 'AGATC': 18}),
        STR({'name': 'Foo', 'AGATC': 4}),
        False,
    ),
])
def test_equals_ignoring_name(str1: STR, str2: STR, expected: bool) -> None:
    assert str1.equals_ignoring_name(str2) == expected


@pytest.mark.parametrize('str_label, dna_sequence, expected', [
    ('AGATC', 'AGATCAGATCAGATC', 3),
    ('AATG', 'AATGAATGTATC', 2),
    ('AATG', 'AATGTATCAATGAATGTATCAATG', 2),
    ('TATC', 'AGATCAATG', 0),
])
def test_get_consecutive_repeats(str_label: str, dna_sequence: str, expected: int) -> None:
    result = ShortTandemRepeats.get_consecutive_str_repeats(str_label, dna_sequence)
    assert result == expected
