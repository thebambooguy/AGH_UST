import threading
import time
import random


class Philosopher(threading.Thread):
    running = True
    def __init__(self, name, left_fork, right_fork):
        threading.Thread.__init__(self)
        self.name = name
        self.left_fork = left_fork
        self.right_fork = right_fork


    def run(self):
        while (self.running):
            time.sleep(random.uniform(1, 10))
            print("%s is thinking now" % self.name)
            self.try_to_eat()

    def try_to_eat(self):
        while self.running:
            self.left_fork.acquire(True) # with True the thread will wait for the lock to release
            locked = self.right_fork.acquire(False)
            if locked:
                break
            #self.left_fork.release() # uncomment this line and deadlock will disappear
        else:
            return

        print("%s has two forks - eating " % self.name)
        time.sleep(random.uniform(1, 10))
        print("%s has already eaten" % self.name)
        self.right_fork.release()
        self.left_fork.release()  # zwalniam ten watek

forks = [threading.Lock() for n in range(5)] #ile wątkow na raz moze leciec, przydzielanie zasobow
philosopherNames = ('Mistrz', 'Malgorzata', 'Korowiow', 'Behemot', 'Woland')

philosophers = [Philosopher(philosopherNames[i], forks[i % 5], forks[(i + 1) % 5]) \
                for i in range(5)]

for p in philosophers:
    p.start()




