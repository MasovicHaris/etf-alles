def helper_permutacije(list, index, result):
    if index == len(list) - 1:
        result.append(list[:])
    else:
        for i in range(index, len(list)):
            list[i], list[index] = list[index], list[i]
            helper_permutacije(list, index + 1, result)
            list[i], list[index] = list[index], list[i]


def permutacije(list):
    result = []
    helper_permutacije(list, 0, result)
    return result

print(len(permutacije([1, 2, 3, 4, 5])))
