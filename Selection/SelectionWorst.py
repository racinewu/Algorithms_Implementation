import sys


def find_median(arr, start, n):
    arr[start:start + n] = sorted(arr[start:start + n])
    return arr[start + n // 2]


def partition(arr, low, high, pivot):
    i = next((idx for idx in range(low, high) if arr[idx] == pivot), high)
    arr[i], arr[high] = arr[high], arr[i]

    i = low
    for j in range(low, high):
        if arr[j] <= pivot:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
    arr[i], arr[high] = arr[high], arr[i]

    return i


def select(arr, low, high, k):
    if low == high:
        return arr[low]

    n = high - low + 1
    medians = [
        find_median(arr, low + i * 5, min(5, n - i * 5))
        for i in range((n + 4) // 5)
    ]

    med_of_med = select(medians, 0,
                        len(medians) - 1,
                        len(medians) // 2) if len(medians) > 1 else medians[0]

    pos = partition(arr, low, high, med_of_med)
    order = pos - low + 1

    if order == k:
        return arr[pos]
    elif k < order:
        return select(arr, low, pos - 1, k)
    else:
        return select(arr, pos + 1, high, k - order)


def main():
    if len(sys.argv) < 3:
        print("Usage: python SelectionWorst.py <input.txt> <i-th>")
        return

    input_file, k = sys.argv[1], int(sys.argv[2])

    try:
        with open(input_file, "r") as f:
            arr = list(map(int, f.read().strip().split()))
    except FileNotFoundError:
        print(f"Failed to open {input_file}")
        return

    if k < 1 or k > len(arr):
        print("Error: i-th number out of range.")
        return

    min_val = min(arr)
    max_val = max(arr)
    kth_element = select(arr, 0, len(arr) - 1, k)

    print(f"Min = {min_val} Max = {max_val}")
    print(f"The {k}-th = {kth_element}")


if __name__ == "__main__":
    main()
