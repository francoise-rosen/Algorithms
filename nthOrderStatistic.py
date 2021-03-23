# based on Coursera Randomized Selection Algorithm, find nth order statistic, the nth smallest value
# https://www.coursera.org/learn/algorithms-divide-conquer/lecture/aqUNa/randomized-selection-algorithm
import array as arr
import random
import unittest

def partition (array, begin, end):
    # end must not be included included 
    # randrange is [min, max)
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
    """
    Array must not be empty
    Index must be between 1 (first smallest) and N (size) (Nth smallest)
    """
    if len(array) < 1:
        raise ValueError ("Array length must be positive")
    if (n < 0 or n > len(array)):
        raise IndexError (str(n) + " index is out of range")
    n -= 1
    return nOrderStatistic (array, 0, len (array), n)

def testRand (numRolls, size):
    for roll in range (numRolls):
        temp = list (map (lambda _: random.randrange(0, 50), range (size)))
        temp_index = random.randrange (1, size)
        temp_value = nthSmallest (temp, temp_index)
        print (sorted (temp))
        print (f'{temp_index} smallest index has value {temp_value}'.format (temp_index, temp_value))

# Unit Test

class NthOrderStatisticTest (unittest.TestCase):

    def setUp (self):
        self.seq1 = arr.array("i", [2, 0, 12, 8])
        self.seq2 = arr.array("i", [9, 5, 2, 1, 6, 11, 7, 3, 10, 4])
    
    def test_empty (self):
        temp = arr.array ('i', [])
        with self.assertRaises (ValueError):
            nthSmallest (temp, 1)

    def test_index_out_of_range (self):
        with self.assertRaises (IndexError):
            nthSmallest (self.seq1, 5)

    def test_range (self):
        value = nthSmallest (self.seq2, 1)
        self.assertEqual (value, 1)
        self.assertEqual (nthSmallest (self.seq2, 10), 11)

if __name__=="__main__":
    #testRand (10, 10)
    unittest.main()