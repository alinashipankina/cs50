from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0:
        break

for i in range(n):
    print("#")

#print("?" * 4)

#for i in range(3):
#    for j in range(3):
#        print("#", end="")
#    print()
