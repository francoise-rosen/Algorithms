# based on Coursera Randomized Selection Algorithm
# https://www.coursera.org/learn/algorithms-divide-conquer/lecture/aqUNa/randomized-selection-algorithm
import array as arr
import random

def partition (array, begin, end):
    pivot_index = random.randrange (begin, end)
    res_index = begin
    for it in range (begin, end):
        if (array[it] < array[pivot_index]):
            if (it != res_index):
                # res_index can reach end only if all elements are smaller than the pivot
                # and the pivot is not the last elem (so pivot_index is on the left)
                if (res_index == pivot_index):
                    res_index += 1
                array[it], array[res_index] = array[res_index], array[it]
            res_index += 1
    if (res_index > pivot_index):
        # res_index is to the right from pivot_index,
        # so we ought to swap the pivot with the one element
        # before the res_index
        # therefore we're safe in case res_index has reached the end in the for loop
        res_index -= 1
    if (res_index >= end):
        raise IndexError (f'Index {res_index} is out of range, must be smaller than {end}'.format (res_index, end))
    array[pivot_index], array[res_index] = array[res_index], array[pivot_index]
    return res_index

def nOrderStatistic (array, begin, end, index):
    pivot_index = partition (array, begin, end)
    if (pivot_index > index):
        return nOrderStatistic (array, begin, pivot_index, index)
    elif (pivot_index < index):
        return nOrderStatistic (array, pivot_index + 1, end, index)
    return array[pivot_index]

def nthSmallest (array, n):
    n -= 1
    return nOrderStatistic (array, 0, len (array), n)

def test1():
    seq1 = arr.array("i", [2, 0, 12, 8])
    seq2 = arr.array("i", [2, 22, 12, 8])
    seq3 = arr.array("i", [2, 1, 12, 28])
    seq4 = arr.array("i", [102, 1, 12])
    index1 = nthSmallest (seq1, 3)
    index2 = nthSmallest (seq2, 3)
    index3 = nthSmallest (seq3, 1)
    index4 = nthSmallest (seq4, random.randrange(1, 4))
    print (index1)
    print (index2)
    print (index3)
    print (index4)

def testRand (numRolls, size):
    for _ in range (numRolls):
        temp = list (map (lambda _: random.randrange(0, 50), range (size)))
        temp_index = random.randrange (1, size)
        temp_value = nthSmallest (temp, temp_index)
        print (sorted (temp))
        print (f'{temp_index} smallest index has value {temp_value}'.format (temp_index, temp_value))

if __name__=="__main__":
    test1()
    testRand (10, 10)