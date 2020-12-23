#include <iostream>

/** Rewrite merge sort using iterators. */
/** Rewrite merge sort using O(1) extra space. */

//============================================================================
// SFD_NAMESPACE BEGIN
//============================================================================
namespace SFD_Algorithm
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
        
        std::cout << "size left: " << size_left << " size right: " << size_right << '\n';
        
        /** Using additional space. */
//        typename std::iterator_traits<ForwardIterator>::value_type left_array[size_left], right_array[size_right];
        current = 0;
        while ( (size_left > 0) && (size_right > 0))
        {
            if (*(first1 + current) < *first2)
            {
                --size_left;
               // ++first1;
            }
            else
            {
                std::swap(*(first1 + current), *first2);
                --size_right; --size_left;
                ++first2;
            }
            ++current;
        }
        
        while (size_right > 0)
        {
            *(first1 + current) = *first2;
            ++current; ++first2;
            --size_right;
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
    SFD_Algorithm::copy (arr, arr + size, arr2);
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
    SFD_Algorithm::msort(array, array+size);
    printArray(array, size);
    //mergeSort (array, 0, size - 1);
//    for (int i = 0; i < size; ++i)
//        std::cout << array[i] << ',';
//    std::cout << '\n';
}

void testMERGE1(int arr[], const int& size)
{
    int arrSorted[size];
    SFD_Algorithm::copy (arr, arr+size, arrSorted);
    std::sort(arrSorted, arrSorted+size);
    
    SFD_Algorithm::msort(arr, arr+size);
    
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == arrSorted[i])
            std::cout << arr[i] << " at index " << i << '\n';
        else
            std::cout << "FAILED at index " << i << " : " << arr[i] << " != " << arrSorted[i] << '\n';
    }
}


void makeContainer()
{
    int a[2] {1, 0};
    //testMERGE1(a, 2);
    
    /** this fails! */
    int a2[3] {8, 17, 0};
    testMERGE1(a2, 3);
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

