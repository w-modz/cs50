import sys
import pytest
import dna
import subprocess


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


#TODO: fix test for repeats()
@pytest.mark.parametrize('STR, dna_sequence, expected', [
    ('AGATC', 'AGATCAGATCAGATC', 3),
    ('AATG', 'AATGAATGTATC', 2),
    ('AATG', 'AATGTATCAATGAATGTATCAATG', 2),
    ('TATC', 'AGATCAATG', 0),
])
def test_get_consecutive_repeats(STR: str, dna_sequence: str, expected: int) -> None:
    result = dna.get_consecutive_repeats(STR, dna_sequence)
    assert result == expected


@pytest.mark.parametrize('STR_names, STR_count, row, expected', [
    (['AGATC', 'TTTTTTCT', 'AATG', 'TCTAG', 'GATA', 'TATC', 'GAAA', 'TCTG'],
     {'AGATC': 37, 'TTTTTTCT': 40, 'AATG': 10, 'TCTAG': 6, 'GATA': 5, 'TATC': 10, 'GAAA': 28, 'TCTG': 8},
     {'name': 'Fred', 'AGATC': '37', 'TTTTTTCT': '40', 'AATG': '10', 'TCTAG': '6', 'GATA': '5', 'TATC': '10',
      'GAAA': '28', 'TCTG': '8'}, True),
])
def test_compare_dna_sequences(STR_names: list[str], STR_count: dict, row: dict, expected: bool) -> None:
    result = dna.compare_dna_sequences(STR_names, STR_count, row)
    assert result == expected



@pytest.mark.parametrize('argv, expected', [
    (['C:/Users/vitom/Documents/programming/cs50/week06/pset6/dna/dna.py', 'databases/large.csv', 'sequences/19.txt'], 'Fred'),
])
def test_output(argv: list[str], expected: str) -> None:
    sys.argv = argv
    exec('dna')
    subprocess = subprocess.Popen("dna.py", shell=True, stdout=subprocess.PIPE)
    subprocess_return = subprocess.stdout.read()
    assert subprocess_return == expected
