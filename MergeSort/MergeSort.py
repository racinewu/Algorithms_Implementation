import sys
import time


def merge(arr, l, m, r):
    left = arr[l:m + 1]
    right = arr[m + 1:r + 1]
    i, j, k = 0, 0, l

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1

    while i < len(left):
        arr[k] = left[i]
        i += 1
        k += 1

    while j < len(right):
        arr[k] = right[j]
        j += 1
        k += 1


def mergeSort(arr, l, r):
    if l >= r:
        return
    m = (l + r) // 2
    mergeSort(arr, l, m)
    mergeSort(arr, m + 1, r)
    merge(arr, l, m, r)


def main():
    if len(sys.argv) < 3:
        print("Usage: python MergeSort.py <input.txt> <output.txt>")
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
    mergeSort(arr, 0, len(arr) - 1)
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
