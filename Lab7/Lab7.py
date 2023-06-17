from threading import Thread
import math
import time

class IncrementaThread(Thread):
    def __init__(self, id, sizeThreads, limit):
        super().__init__()
        self.idThreads = id
        self.sizeThreads = sizeThreads
        self.limit = limit
        self.sum = 0

    def run(self):
        for i in range(self.idThreads, self.limit):
          if (i % self.sizeThreads == self.idThreads):
            self.sum += math.pow(-1, i) / (2 * i + 1)

    def getSum(self):
        return self.sum

pivot = 1
for i in range(1, 4):
    if(i == 3):
      i += 1

    start_time = time.time()
    print("Starting test: ", pivot)

    value = 0
    sizeThreads = i
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

    end_time = time.time()
    execution_time = end_time - start_time

    print("Value of N = ", n)
    print("Quantify of Threads: ", sizeThreads)
    print("Value of Pi = ", round(pi, 4))
    print("Margin of error: " + str(round(marginOfError * 100, 4)) + " %")
    print("Time: " + str(round(execution_time, 4)))
    print("End of Test\n\n")
