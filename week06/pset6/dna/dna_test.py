import sys

import pytest
from dna import repeats
from dna import check_arguments
from dna import compare
from dna import main


@pytest.mark.parametrize('argv, expected', [
    (['dna/dna.py', "databases/large.csv", "sequences/1.txt"], True),
    (['dna/dna.py', "databases/small.csv", "sequences/1.txt"], True),
    (['dna/dna.py', "databases/smol.csv", "sequences/1.txt"], True),
    (['dna/dna.py', "databases/small"], False),
    (['dna/dna.py', "sequences/1.txt"], False),
    (['dna/dna.py', "foo"], False),
])
def test_check_arguments(argv: list[str], expected: bool) -> None:
    result = check_arguments(argv)
    assert result == expected


#TODO: fix test for repeats()
@pytest.mark.parametrize('STR, dna, expected', [
    (['AGATC'], ['AGATCAGATCAGATC\n'], 3),
    (['AATG'], ['AATGAATGTATC\n'], 2),
    (['AATG'], ['AATGTATCAATGAATGTATCAATG\n'], 2),
    (['TATC'], ['AGATCAATG\n'], 0),
])
def test_repeats(STR: str, dna: str, expected: int) -> None:
    result = repeats(STR, dna)
    assert result == expected


@pytest.mark.parametrize('STR_names, STR_count, row, expected', [
    (['AGATC', 'TTTTTTCT', 'AATG', 'TCTAG', 'GATA', 'TATC', 'GAAA', 'TCTG'],
     {'AGATC': 37, 'TTTTTTCT': 40, 'AATG': 10, 'TCTAG': 6, 'GATA': 5, 'TATC': 10, 'GAAA': 28, 'TCTG': 8},
     {'name': 'Fred', 'AGATC': '37', 'TTTTTTCT': '40', 'AATG': '10', 'TCTAG': '6', 'GATA': '5', 'TATC': '10',
      'GAAA': '28', 'TCTG': '8'}, True),
])
def test_compare(STR_names: list[str], STR_count: dict, row, expected: bool) -> None:
    result = compare(STR_names, STR_count, row)
    assert result == expected



@pytest.mark.parametrize('argv, expected', [
    (['C:/Users/vitom/Documents/programming/cs50/week06/pset6/dna/dna.py', 'databases/large.csv', 'sequences/19.txt'], 'Fred'),
])
def test_main(argv: list[str], expected: str) -> None:
    sys.argv = argv
    result = main()
    assert result == expected
