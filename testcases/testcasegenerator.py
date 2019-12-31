import random

with open("input.txt", "w") as fp:
    for i in range(1, 100):
        option = random.choice([1, 3, 4])
        if (option in [1, 3]):
            number = random.randrange(1, 100, 2)
            fp.write(f"{option} {number}\n")
        else:
            fp.write(f"{option}\n")
    fp.write("5")
