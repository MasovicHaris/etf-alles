def binary_search(list, element):
    lo, hi = 0, len(list)
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if list[mid] <= element:
            lo = mid
        else:
            hi = mid
    if list[lo] == element:
        return lo
    else: 
        return -1

list = [1, 5, 10, 12, 43, 56]
print(binary_search(list, 56))
print(list.index(10))