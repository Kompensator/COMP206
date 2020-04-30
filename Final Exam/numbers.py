import random

s = 0
with open('numbers.txt', 'w') as handle:
    for i in range(100):
        r = random.randint(-100, 100)
        s += r
        handle.write(str(r)+'\n')

print("Sum = ", s)