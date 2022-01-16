fPin = '1'
sPin = '2'
tPin = '3'


def solveHanoi(n, pin1, pin2, pin3):
    if n == 0:
        return

    solveHanoi(n - 1, pin1, pin3, pin2)
    print(pin1, "->", pin3)
    solveHanoi(n - 1, pin2, pin1, pin3)


if __name__ == '__main__':
    n = int(input("Discs: "))

    solveHanoi(n, fPin, sPin, tPin)