from threading import Thread
import math

class IncrementaThread(Thread):
    def __init__(self, id, sizeThreads, limit):
        super().__init__()
        self.idThreads = id
        self.sizeThreads = sizeThreads
        self.limit = limit
        self.sum = 0

    def run(self):
        for i in range(self.idThreads, self.limit, self.sizeThreads):
            self.sum += math.pow(-1, i) / (2 * i + 1)

    def getSum(self):
        return self.sum

pivot = 1
for i in range(1, 6):
    value = 0
    sizeThreads = pivot
    n = int(math.pow(5, pivot))

    threads = []
    for i in range(sizeThreads):
        threads.append(IncrementaThread(i, sizeThreads, n))

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

    value = 0
    for i in range(sizeThreads):
        value += threads[i].getSum()

    pi = 4 * value
    marginOfError = (pi - math.pi) / math.pi;

    pivot += 1

    print("Value of N = ", n)
    print("Value of Pi = ", round(pi, 4))
    print("Margin of error: " + str(round(marginOfError * 100, 4)) + " %");
    print("End of Test\n\n")
