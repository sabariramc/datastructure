import random

with open("input.txt", "w") as fp:
    for i in range(1, 100):
        option = random.choice([1, 3])
        number = random.randrange(1, 100, 2)
        fp.write(f"{option} {number}\n")
    fp.write("4")
