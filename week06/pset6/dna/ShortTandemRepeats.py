from typing import Union


class ShortTandemRepeats:
    _value: dict[str, Union[int, str]] = {}

    def __init__(self, db_row: dict[str, str]) -> None:
        # But why? ¯\_(ツ)_/¯ https://stackoverflow.com/q/1132941
        if self._value is not None:
            self._value = {}
        for key, value in db_row.items():
            self[key] = value if key == 'name' else int(value)

    def __getitem__(self, key) -> Union[int, str]:
        return self._value[key]

    def __setitem__(self, key, value) -> None:
        self._value[key] = value

    def __hash__(self) -> int:
        return hash(self._value)

    def __eq__(self, other) -> bool:
        return isinstance(other, ShortTandemRepeats) and self._value == other._value

    def __str__(self) -> str:
        return str(self._value)

    def equals_ignoring_name(self, other) -> bool:
        return isinstance(other, ShortTandemRepeats) \
               and are_dicts_equal_ignoring_keys(self._value, other._value, {'name'})

    @staticmethod
    def from_sequence(str_labels: list[str], dna_sequence: str):
        str_count = {}
        for label in str_labels:
            str_count[label] = str(get_consecutive_str_repeats(label, dna_sequence))
        return ShortTandemRepeats(str_count)


# https://stackoverflow.com/a/10480904
def are_dicts_equal_ignoring_keys(d1: dict, d2: dict, ignored_keys: set[str]):
    for k1, v1 in d1.items():
        if k1 not in ignored_keys and (k1 not in d2 or d2[k1] != v1):
            return False
    for k2, v2 in d2.items():
        if k2 not in ignored_keys and k2 not in d1:
            return False
    return True


def get_consecutive_str_repeats(str_label: str, dna_sequence: str) -> int:
    count = 0
    while (count + 1) * str_label in dna_sequence:
        count += 1
    return count
