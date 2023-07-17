import threading

class FibonacciThread(threading.Thread):
    def run(self):
        p, q = 0, 1
        while p <= 10000:
            print("Fibonacci:", p)
            p, q = q, p + q

class SquareThread(threading.Thread):
    def run(self):
        for x in range(1, 10001):
            print("Square:", x * x)

class CubeThread(threading.Thread):
    def run(self):
        for x in range(1, 10001):
            print("Cube:", x * x * x)

def main():
    fibonacci_thread = FibonacciThread()
    square_thread = SquareThread()
    cube_thread = CubeThread()

    fibonacci_thread.start()
    square_thread.start()
    cube_thread.start()

    fibonacci_thread.join()
    square_thread.join()
    cube_thread.join()

if __name__ == '__main__':
    main()

