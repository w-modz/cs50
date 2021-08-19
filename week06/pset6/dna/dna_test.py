import pytest
import dna


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
