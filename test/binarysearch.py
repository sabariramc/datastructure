x = [10]


def binary_search(value):
    end = len(x)-1
    start = 0
    mid = (end+start)//2
    i = 0
    while(start < end):
        i += 1
        diff = end-start
        mid = (end+start)//2
        if x[mid] == value:
            break
        elif diff == 1:
            if x[mid] < value:
                mid += 1
            break
        elif x[mid] > value:
            end = mid
        else:
            start = mid
    return x[mid], i


search_list = list(range(5, 15))

with open("output.txt", "w") as fp:
    for i in search_list:
        value, iteration = binary_search(i)
        fp.write(f"{i},{value},{iteration}\n")
