# python3

import sys
import threading


def compute_height(n, parents):
    # Replace this code with a faster implementation
    max_height = 0
    for vertex in range(n):
        height = 0
        current = vertex
        heights = [0 for i in range(len(parents))]
        while current != -1:
            location = current - 0
            if heights[location] != 0:
                break 
            height += 1
            
            current = parents[current]
        heights[vertex] = height + heights[location]
        max_height = max(max_height, heights[vertex])
    return max_height


def main():
    n = int(input())
    parents = list(map(int, input().split()))
    print(compute_height(n, parents))


# In Python, the default limit on recursion depth is rather low,
# so raise it here for this problem. Note that to take advantage
# of bigger stack, we have to launch the computation in a new thread.
sys.setrecursionlimit(10**7)  # max depth of recursion
threading.stack_size(2**27)   # new thread will get stack of such size
threading.Thread(target=main).start()
