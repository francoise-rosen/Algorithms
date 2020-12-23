#include <iostream>
#include <vector>

/** Rewrite merge sort using iterators. */
/** Rewrite merge sort using O(1) extra space. */

//============================================================================
// SFD_NAMESPACE BEGIN
//============================================================================
namespace syfo
{
    template <typename ForwardIterator>
    void copy (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2)
    {
        if (first1 == last1)
            return;
        
        while (first1 != last1)
        {
            *first2 = *first1;
            ++first2; ++first1;
        }
    }
    
    /** Here last1 and last 2 are poining to the penultimate elem. */
    template <typename ForwardIterator>
    void merge (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2)
    {
        typename std::iterator_traits<ForwardIterator>::difference_type size_left, size_right, current;
        size_left = std::distance (first1, last1) + 1;
        size_right = std::distance (first2, last2) + 1;
        typename std::iterator_traits<ForwardIterator>::value_type left_array[size_left], right_array[size_right];
        copy (first1, last1 + 1, left_array);
        copy (first2, last2 + 1, right_array);
        
        std::cout << "size left: " << size_left << " size right: " << size_right << '\n';
        
        /** The problem here is that after the left_size
         exosted, it just copies the reminder of the right size
         Look into split pairs and qsort algos!
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
    
    //template <typename ForwardIterator>
    
    /** @param first is begin()
        @param last is one elem before end()
     */
    template <typename ForwardIterator>
    void mergeSort (ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type count;
        count = std::distance(first, last);
        std::cout << "count: " << count << '\n';
        ForwardIterator middle = first;
        std::advance(middle, count / 2);
        mergeSort (first, middle);
        mergeSort (middle + 1, last);
        merge (first, middle, middle + 1, last);
   
    }
    
    /** Special case - 1 elem. */
    template <typename ForwardIterator>
    void msort (ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return;
        mergeSort(first, last-1);
    }
    
}

//============================================================================
// SFD_NAMESPACE END
//============================================================================

//============================================================================
// CASUAL ALGO
//============================================================================
template <typename T>
void merge (T array[], int left, int mid, int right);

template <typename T>
void mergeSortProto (T array[], int leftIndex, int rightIndex)
{
    int middleIndex = (rightIndex + leftIndex) / 2;
    merge(array, leftIndex, middleIndex, rightIndex, true);
}

// 1. Find the middle point
template <typename T>
void mergeSort (T array[], int leftIndex, int rightIndex)
{
    if ( leftIndex >= rightIndex)
        return;
    int middleIndex = (rightIndex + leftIndex) / 2;
    // split
    // right side
    
    // 3. call mergeSort for the second half
    mergeSort (array, leftIndex, middleIndex);
    // 2. call mergeSort for the first half
    mergeSort (array, middleIndex + 1, rightIndex);
    //std::cout << middleIndex << '\n';
    // merge
    merge (array, leftIndex, middleIndex, rightIndex);
    
}

// 4. merge the 2 halves sorted in 2 and 3.
template <typename T>
void merge (T array[], int left, int mid, int right)
{
    //    std::cout << "left: " << left << '\n';
    //    std::cout << "mid: " << mid << '\n';
    //    std::cout << "right: " << right << '\n';
    
    /** create temp arrays. */
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;
    
    int currentIndex {left};
    int currentRIndex {mid + 1};
    
    int leftArrayIndex {0};
    int rightArrayIndex {0};
    
    while ( (leftArrayIndex < sizeLeft) && (rightArrayIndex < sizeRight))
    {
        if (array[currentIndex] < array[currentRIndex])
        {
            //std::cout << "left array item: " << rightArray[rightArrayIndex] << '\n';
            //array[currentIndex] = leftArray[leftArrayIndex];
            ++leftArrayIndex;
        }
        else
        {
            std::swap (array[currentIndex], array[currentRIndex]);
            ++leftArrayIndex;
            ++rightArrayIndex;
        }
        ++currentIndex;
    }
    
    if (rightArrayIndex < sizeRight)
    {
        while (rightArrayIndex < sizeRight)
        {
            array [currentIndex] = array [currentRIndex];
            ++currentRIndex; ++currentIndex; ++rightArrayIndex;
        }
    }
    
}

void testCopy (int arr[], const int& size)
{
    int arr2[size];
    syfo::copy (arr, arr + size, arr2);
    for (int i = 0; i < size; ++i)
    {
        assert (arr[i] == arr2[i]);
    }
    std::cout << "passed!\n";
}

template <typename T>
void printArray (T array[], const int& size)
{
    std::cout << "{ ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i];
        if (i == size - 1)
            std::cout << " }\n";
        else if ((i%10 == 0) && (i != 0))
            std::cout << '\n';
        else
            std::cout << " ,";
        
    }
}

void simpleRecursion (int array[], int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    simpleRecursion (array, mid + 1, right);
    std::cout << "mid: " << array[mid] << "\nright: " << array[right] << '\n';
}

void testSimpleRecursion()
{
    int array[] {0, 1, 12, 2, 3, 4};
    simpleRecursion (array, 0, 4);
}

void testSFDmergeSort()
{
    int array[] {10, 1, 19, 2, 13, 4, 29, 17, 5};
    std::cout << "Original Array:\n";
    int size = sizeof (array) / sizeof (array[0]);
    printArray(array, size);
    //SFD_Algorithm::mergeSort(array, array+size-1);
    syfo::msort(array, array+size);
    printArray(array, size);
    //mergeSort (array, 0, size - 1);
//    for (int i = 0; i < size; ++i)
//        std::cout << array[i] << ',';
//    std::cout << '\n';
}

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
    
    /** Vector. */
    std::vector<double> v {0.0, 0.1, 9.0, 2.3444, 11.2, -4.3};
    testMERGE2(v);
    
    /** Sorted vector. */
    std::vector<float> vf {10.0f, 11.2f, 33.0f, 89.0f, 112.0f, 235.0f};
    testMERGE2 (vf);
    
    /** Reversed vector. */
    std::vector<int> vint {19, 17, 11, 7, 4, 2, 0};
    testMERGE2 (vint);
    
    /** std::array. */
    
    /** std::map. */
    
    /** std::string. */
}

int main(int argc, const char * argv[]) {
    
    try {
        //testSFDmergeSort();
        makeContainer();
        
    } catch (std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
    
    return 0;
}

