import pytest

import ShortTandemRepeats


@pytest.mark.parametrize('str_label, dna_sequence, expected', [
    ('AGATC', 'AGATCAGATCAGATC', 3),
    ('AATG', 'AATGAATGTATC', 2),
    ('AATG', 'AATGTATCAATGAATGTATCAATG', 2),
    ('TATC', 'AGATCAATG', 0),
])
def test_get_consecutive_repeats(str_label: str, dna_sequence: str, expected: int) -> None:
    result = ShortTandemRepeats.get_consecutive_str_repeats(str_label, dna_sequence)
    assert result == expected
