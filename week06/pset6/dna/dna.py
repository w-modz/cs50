import csv
import sys


def main() -> str:
    if not check_arguments(sys.argv):
        return "Usage: dna.py <STR counts path> <DNA sequence path>"
    dna_database = open(sys.argv[1])
    dna_file = open(sys.argv[2])
    data_reader = csv.DictReader(dna_database)
    STR_names = data_reader.fieldnames[1:]
    dna_sequence = dna_file.read()
    dna_file.close()
    STR_count = {}
    for STR in STR_names:
        STR_count[STR] = get_consecutive_repeats(STR, dna_sequence)
    for row in data_reader:
        if compare_dna_sequences(STR_names, STR_count, row):
            dna_database.close()
            return f'{row["name"]}'
    dna_database.close()
    return "No match found"


def check_arguments(argv: list[str]) -> bool:
    return len(argv) == 3


def get_consecutive_repeats(STR: str, dna: str) -> int:
    index = 0
    while (index + 1) * STR in dna:
        index += 1
    return index


def compare_dna_sequences(STR_names: list[str], STR_count: dict, row: dict) -> bool:
    for STR in STR_names:
        if int(row[STR]) != STR_count[STR]:
            return False
        return True


print(main())
