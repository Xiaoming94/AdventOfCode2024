from .common import create_lists as parse

def exec(input: str) -> int:
    (l_list, r_list) = parse(input)

    def find_num_occurence(num: int, r_list: list[int]) -> int:
        indices = [i for i, x in enumerate(r_list) if x == num]
        return len(indices)

    return sum([n * find_num_occurence(n, r_list) for n in l_list])
