def count_xmas(input: str) -> int:
    input_as_list = [list(line) for line in input.splitlines()]

    direction_indices = [[(0,1),(0,2),(0,3)], # Left
                         [(0,-1),(0,-2),(0,-3)], # right
                         [(1,0),(2,0),(3,0)], # Down
                         [(-1,0),(-2,0),(-3,0)], # Up
                         [(1,1),(2,2),(3,3)], # Down Left
                         [(1,-1),(2,-2),(3,-3)], # Down Right
                         [(-1,1),(-2,2),(-3,3)], #Up Left
                         [(-1,-1),(-2,-2),(-3,-3)], #Up Right
                        ]

    xmas_count = 0

    for i in range(len(input_as_list)):
        for j in range(len(input_as_list[i])):
            if input_as_list[i][j].upper() == 'X':
                for indices in direction_indices:
                    word_found = get_word_in_direction(input_as_list, indices, (i,j))
                    if word_found.upper() == "XMAS":
                        xmas_count += 1

    return xmas_count

def count_cross_mas(input: str) -> int:
    return 0

def get_word_in_direction(
        input: list[list[str]],
        indices: list[tuple[ int,int ]],
        startingpos: tuple[int, int]) -> str:

    word = "X"
    (i,j) = startingpos
    input_height = len(input)
    input_length = len(input[i])
    for (di, dj) in indices:
        (i_next, j_next) = i + di, j + dj
        if ( 0<= i_next < input_height ) and ( 0 <= j_next < input_length ):
            word += input[i_next][j_next]
        else:
            return word

    return word
