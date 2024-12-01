def create_lists(input: str) -> tuple[list[int], list[int]]:

    def create_list_items(line: str) -> list[int]:
        return list(map(lambda n: int(n), line.split()))

    left_list = list()
    right_list = list()
    for (l,r) in list(map(lambda line: create_list_items(line), input.splitlines())):
        left_list.append(l)
        right_list.append(r)

    return (left_list, right_list)

def calc_distance(input: str) -> int:
    (l_list, r_list) = create_lists(input)
    l_list.sort()
    r_list.sort()

    return sum([abs(l - r) for (l,r) in zip(l_list, r_list)])
