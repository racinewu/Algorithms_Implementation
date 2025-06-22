import sys
import time


def counting_sort_by_digit(arr, exp):
    output = [0] * len(arr)
    count = [0] * 10  # 因為每個位數的數值範圍是 0~9

    for val in arr:
        index = (val // exp) % 10
        count[index] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    for i in range(len(arr) - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1

    for i in range(len(arr)):
        arr[i] = output[i]


def radixSort(arr):
    if not arr:
        return

    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        counting_sort_by_digit(arr, exp)
        exp *= 10


def main():
    if len(sys.argv) < 3:
        print("Usage: python RadixSort.py <input.txt> <output.txt>")
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
    radixSort(arr)
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
