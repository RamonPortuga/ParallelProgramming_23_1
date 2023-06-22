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
print("Tests varying value of N and number of Threads")
#Variando a quantidade de threads e de N
for i in range(1, 4):
    if(i == 3):
      i += 1

    start_time = time.time()
    print("Starting test: ", pivot)

    value = 0
    sizeThreads = i
    n = int(math.pow(100, pivot))

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
    print("Margin of error: " + str(round(marginOfError * 100, 8)) + " %")
    print("Time: " + str(round(execution_time, 4)))
    print("End of Test\n\n")

#Extraindo as médias de tempo com N = 100000
#Variando a quantidade de threads e de N
n = 100000
sum_time = 0
print("Setting N equal to 100000 and varying the number of threads at 1, 2 and 4: ")
for i in range(1, 4):
    pivot = i

    if(i == 3):
      i += 1
    
    print("Starting test: ", pivot)
    for j in range (1, 6):

      start_time = time.time()

      value = 0
      sizeThreads = i

      threads = []
      for j in range(sizeThreads):
          threads.append(IncrementaThread(j, sizeThreads, n))

      for thread in threads:
          thread.start()

      for thread in threads:
          thread.join()

      value = 0
      for j in range(sizeThreads):
          value += threads[j].getSum()

      pi = 4 * value
      marginOfError = (pi - math.pi) / math.pi;

      pivot += 1

      end_time = time.time()
      execution_time = end_time - start_time

      sum_time += execution_time

    print("Quantify of Threads: ", sizeThreads)
    print("Average time with 5 runs: " + str(round(sum_time / 5, 5)))
    print("End of Test\n\n")
    sum_time = 0
