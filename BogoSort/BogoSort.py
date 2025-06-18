import sys
import time
import random


def isSorted(arr):
    for i in range(1, len(arr)):
        if arr[i - 1] > arr[i]:
            return False
    return True


def bogoSort(arr):
    while not isSorted(arr):
        random.shuffle(arr)


def main():
    if len(sys.argv) < 3:
        print("Usage: python BogoSort.py <input.txt> <output.txt>")
        return

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    try:
        with open(input_file, 'r') as f:
            arr = [int(line.strip()) for line in f if line.strip()]
    except FileNotFoundError:
        print(f"Failed to open {input_file}")
        return

    start_time = time.time()
    bogoSort(arr)
    end_time = time.time()
    print(f"Execution: {int((end_time - start_time) * 1000)} ms")

    try:
        with open(output_file, 'w') as f:
            for num in arr:
                f.write(f"{num}\n")
    except FileNotFoundError:
        print(f"Failed to open {output_file}")
        return


if __name__ == "__main__":
    main()
