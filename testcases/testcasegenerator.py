import random


def test_v1():
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


def test_v2():
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


test_v1()
