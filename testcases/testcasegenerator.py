import random


def test_tree():
    x = {0}
    with open("input.txt", "w") as fp:
        for i in range(1, 10000, 10):
            for j in range(i, i+10):
                option = random.choice([1, 3])
                number = random.randrange(1, 10000, 2)
                if option == 1:
                    while number in x:
                        number = random.randrange(1, 10000, 2)
                    x.add(number)
                else:
                    if len(x) > 0:
                        number = x.pop()
                fp.write(f"{option} {number}\n")
            # fp.write("4\n")
        fp.write("5")


def test_tree_v2():
    x = {0}
    with open("input.txt", "w") as fp:
        for i in range(1, 10000, 10):
            for j in range(i, i+10):
                option = random.choice([1, 3])
                number = random.randrange(1, 10000, 2)
                if option == 1:
                    while number in x:
                        number = random.randrange(1, 10000, 2)
                    x.add(number)
                else:
                    if number in x:
                        x.remove(number)
                fp.write(f"{option} {number}\n")
            # fp.write("4\n")
        fp.write("5")


def test_tree_old_v1():
    x = {0}
    with open("input.txt", "w") as fp:
        for i in range(1, 50):
            for j in range(i, i+10):
                number = random.randrange(1, 1000, 2)
                while number in x:
                    number = random.randrange(1, 1000, 2)
                x.add(number)
                fp.write(f"1 {number}\n")
        fp.write("5")


def test_heap():
    with open("input.txt", "w") as fp:
        for _ in range(0, 100):
            option = random.choice([1, 2])
            number = random.randrange(1, 100, 2)
            if option == 1:
                fp.write(f"{option} {number}\n")
            else:
                fp.write(f"{option}\n")
        fp.write("5")


def test_indexed_priority_queue():
    with open("input.txt", "w") as fp:
        key_set = set()
        for _ in range(1, 20):
            key = random.randrange(1, 200)
            priority = random.randrange(1, 100)
            fp.write(f"1 {key} {priority}\n")
            key_set.add(key)
        for _ in range(0, 200):
            option = random.choice([1, 2, 4, 5])
            if option in {4, 5}:
                key = random.choice(list(key_set))
            else:
                key = random.randrange(1, 200)
            priority = random.randrange(1, 200)
            if option in {1, 4}:
                fp.write(f"{option} {key} {priority}\n")
            elif option == 5:
                fp.write(f"{option} {key}\n")
            else:
                fp.write(f"{option}\n")
        fp.write("6")


test_indexed_priority_queue()
