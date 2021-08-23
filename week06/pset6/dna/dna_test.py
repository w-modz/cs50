import pytest
import dna

from ShortTandemRepeats import ShortTandemRepeats


@pytest.mark.parametrize('argv, expected', [
    (['dna/dna.py', "databases/large.csv", "sequences/1.txt"], True),
    (['dna/dna.py', "databases/small.csv", "sequences/1.txt"], True),
    (['dna/dna.py', "databases/smol.csv", "sequences/1.txt"], True),
    (['dna/dna.py', "databases/small"], False),
    (['dna/dna.py', "sequences/1.txt"], False),
    (['dna/dna.py', "foo"], False),
])
def test_check_arguments(argv: list[str], expected: bool) -> None:
    result = dna.check_arguments(argv)
    assert result == expected


@pytest.mark.parametrize('searched, database, expected', [
    (
            ShortTandemRepeats({'name': 'Foo', 'AGATC': 4}),
            [
                ShortTandemRepeats({'name': 'Bar', 'AGATC': 18}),
                ShortTandemRepeats({'name': 'Foo', 'AGATC': 4}),
            ],
            'Foo'
    ),
    (
            ShortTandemRepeats({'name': 'Baz', 'AGATC': 32}),
            [
                ShortTandemRepeats({'name': 'Bar', 'AGATC': 18}),
                ShortTandemRepeats({'name': 'Foo', 'AGATC': 4}),
            ],
            'No match found'
    ),
])
def test_find_match(searched: ShortTandemRepeats, database: list[ShortTandemRepeats], expected: str) -> None:
    assert dna.find_match(searched, database) == expected
