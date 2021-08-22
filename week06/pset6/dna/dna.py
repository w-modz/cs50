import csv
import sys

from ShortTandemRepeats import ShortTandemRepeats


def main() -> None:
    if not check_arguments(sys.argv):
        print("Usage: dna.py <STR counts path> <DNA sequence path>")
        sys.exit(1)

    dna_database, str_labels = read_dna_database(sys.argv[1])
    dna_sequence = read_dna_sequence(sys.argv[2])
    searched = ShortTandemRepeats.from_sequence(str_labels, dna_sequence)

    print(find_match(searched, dna_database))


def check_arguments(argv: list[str]) -> bool:
    return len(argv) == 3


def read_dna_database(file_path: str) -> tuple[list[ShortTandemRepeats], list[str]]:
    with open(file_path) as dna_database:
        reader = csv.DictReader(dna_database)
        strs = []
        for row in reader:
            strs.append(ShortTandemRepeats(row))
        return strs, reader.fieldnames[1:]


def read_dna_sequence(file_path: str) -> str:
    with open(file_path) as dna_file:
        return dna_file.read()


def find_match(searched: ShortTandemRepeats, database: list[ShortTandemRepeats]) -> str:
    for person in database:
        if searched == person:
            return f"{person['name']}"
    return 'No match found'


if __name__ == "__main__":
    main()
