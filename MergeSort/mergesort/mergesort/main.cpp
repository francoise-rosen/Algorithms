/**
    Implementation of the MergeSort algorithm using iterators.
 */


#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>

/** Rewrite merge sort using iterators. done */
/** Rewrite merge sort using O(1) extra space. failed */

/** Very basic error handling, will terminate the program
     on the very first failed test.
 */
class SortError
{
public:
    SortError (const std::string& s, int i, int val, int val_exp)
    :message {s}, index {i}, value {val}, value_expected {val_exp}
    {}
    
    std::string what()
    {
        return message + std::to_string(index) + " value obtained " + std::to_string(value) +  " value expected " + std::to_string(value_expected);
    }
private:
    std::string message;
    int index;
    int value;
    int value_expected;
};

//============================================================================
// SFD_NAMESPACE BEGIN
//============================================================================
namespace syfo
{
    template <typename InputIterator, typename OutputIterator>
    void copy (InputIterator first, InputIterator last, OutputIterator result)
    {
        if (first == last)
            return;
        
        while (first != last)
        {
            *result = *first;
            ++result; ++first;
        }
    }
    
    /** Here last1 and last 2 are poining to the penultimate elem. */
    template <typename ForwardIterator>
    void merge (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2)
    {
        typename std::iterator_traits<ForwardIterator>::difference_type size_left, size_right, current;
        size_left = std::distance (first1, last1) + 1;
        size_right = std::distance (first2, last2) + 1;
        /** Create and fill temp arrays with the left side range
            and the right side range.
         */
        typename std::iterator_traits<ForwardIterator>::value_type left_array[size_left], right_array[size_right];
        syfo::copy (first1, last1 + 1, left_array);
        syfo::copy (first2, last2 + 1, right_array);
        
        /** Merge sorted ranges into the final range [first1, last2].
            Values are compared and added as per condition.
         */
        current = 0;
        int i {0}, j {0};
        while ( (i < size_left) && (j < size_right) )
        {
            if (left_array[i] < right_array[j])
            {
                *(first1 + current) = left_array[i];
                ++i;
            }
            else
            {
                *(first1 + current) = right_array[j];
                ++j;
            }
            ++current;
        }
        
        /** Append the reminder - either the left or the right range.
         */
        for (;i < size_left; ++i)
        {
            *(first1 + current) = left_array[i];
            ++current;
        }
        for (;j < size_right; ++j)
        {
            *(first1 + current) = right_array[j];
            ++current;
        }
    }
    
    /** Split and merge recursevly.
        @param first is begin()
        @param last is one elem before end()
     */
    template <typename ForwardIterator>
    void mergeSort (ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type count;
        count = std::distance(first, last);
        ForwardIterator middle = first;
        std::advance(middle, count / 2);
        /** The left side. */
        mergeSort (first, middle);
        /** The right side. */
        mergeSort (middle + 1, last);
        merge (first, middle, middle + 1, last);
    }
    
    /** Special case - 0 elem is ignored.
        The above algorithm does not use iterator to end()
     */
    template <typename ForwardIterator>
    void msort (ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return;
        mergeSort(first, last - 1);
    }
    
}

//============================================================================
// SFD_NAMESPACE END
//============================================================================

//============================================================================
// TESTS
//============================================================================

void testMERGE1 (int arr[], const int& size)
{
    int arrSorted[size];
    syfo::copy (arr, arr+size, arrSorted);
    std::sort(arrSorted, arrSorted+size);
    
    syfo::msort(arr, arr+size);
    
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == arrSorted[i])
            std::cout << arr[i] << " at index " << i << '\n';
        else
            std::cout << "FAILED at index " << i << " : " << arr[i]
            << " != " << arrSorted[i] << '\n';
    }
}

/** This test will not terminate the program,
    it will simply print out failed elements and their indecies.
 */
template <typename T>
void testMERGE2 (std::vector<T>& v)
{
    std::vector<T> v_copy (v);
    std::sort (v_copy.begin(), v_copy.end());
    syfo::msort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] == v_copy[i])
            std::cout << i << " : " << v[i] << '\n';
        else
            std::cout << "Failed at index " << i << " : " << v[i]
            << " != " << v_copy[i] << '\n';
    }
}

template <typename Container>
void testMERGE3 (Container& container)
{
    Container c_copy (container);
    std::sort (c_copy.begin(), c_copy.end());
    syfo::msort (container.begin(), container.end());
    for (int i = 0; i < container.size(); ++i)
    {
        if (container[i] != c_copy[i])
            throw SortError ("Wrong result at index ", i, container[i], c_copy[i]);
        std::cout << container[i] << '\n';
    }
}

template <typename ForwardIterator>
void testMERGE3 (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance(first, last)};
    typename std::iterator_traits<ForwardIterator>::value_type c_copy[size];
    syfo::copy (first, last, c_copy + 0);
    std::sort (c_copy + 0, c_copy + size);
    syfo::msort (first, last);
    int count = 0;
    while (count < size)
    {
        if (*(first + count) != c_copy[count])
            throw SortError ("Wrong result at index ", count, *(first + count), c_copy[count]);
        std::cout << *(first + count) << '\n';
        ++count;
    }
    std::cout << "Passed!\n";
}


void makeContainer()
{
    /** Special case - 1 item. */
    int one[1] {9};
    testMERGE1(one, 1);
    
    /** Two items. */
    int a[2] {1, 0};
    testMERGE1 (a, 2);
    
    /** Array with n items */
    int a2[4] {8, 17, -1, 0};
    int sz = sizeof (a2) / sizeof (a2[0]);
    testMERGE1 (a2, sz);
    int popArray[9] {9, 1, 0, -2, -10000, 10000, 6, 2, 256};
    testMERGE3(popArray, popArray + 9);
    
    /** Vector. */
    std::vector<double> v {0.0, 0.1, 9.0, 2.3444, 11.2, -4.3};
    testMERGE2(v);
    
    /** Sorted vector. */
    std::vector<float> vf {10.0f, 11.2f, 33.0f, 89.0f, 112.0f, 235.0f};
    testMERGE2 (vf);
    
    /** Reversed vector. */
    std::vector<int> vint {19, 17, 11, 7, 4, 2, 0};
    testMERGE2 (vint);
    
    /** Populated with repeated values. */
    std::vector<int> vint2 {2, 2, 2, 2, 0, 0, 0};
    testMERGE2 (vint2);
    
    /** std::array. */
    std::array<int, 10> arr {8, 16, 2, 4, 256, 128, 999, -999, 7, 14};
    testMERGE3 (arr);
    
    /** dynamic array. */
    int* dyn_array = new int[vint.size()];
    syfo::copy (vint.begin(), vint.end(), dyn_array + 0);
    testMERGE3(dyn_array, dyn_array+(vint.size()));
    delete[] dyn_array;
    
    /** std::map. */
    
    /** std::string. */
}

int main(int argc, const char * argv[]) {
    
    try {
        //testSFDmergeSort();
        makeContainer();
        
    }
    catch (SortError& se)
    {
        std::cerr << se.what() << '\n';
        return 1;
    }
    
    return 0;
}

