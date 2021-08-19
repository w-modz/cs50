import sys


def main() -> None:
    if not check_arguments(sys.argv):
        print("Usage: dna.py <STR counts path> <DNA sequence path>")
        return


def check_arguments(argv: list[str]) -> bool:
    return len(argv) == 3


main()
