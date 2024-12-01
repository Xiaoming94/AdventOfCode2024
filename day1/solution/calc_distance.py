from .common import create_lists as parse

def exec(input: str) -> int:
    (l_list, r_list) = parse(input)
    l_list.sort()
    r_list.sort()

    return sum([abs(l - r) for (l,r) in zip(l_list, r_list)])
