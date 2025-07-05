import sys
import time


def countingSort(arr):
    if not arr:
        return

    max_val = max(arr)
    count = [0] * (max_val + 1)
    for val in arr:
        count[val] += 1

    idx = 0
    for i in range(len(count)):
        while count[i] > 0:
            arr[idx] = i
            idx += 1
            count[i] -= 1


def main():
    if len(sys.argv) < 3:
        print("Usage: python CountingSort.py <input.txt> <output.txt>")
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
    countingSort(arr)
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
