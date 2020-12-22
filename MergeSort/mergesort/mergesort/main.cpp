#include <iostream>

/** Rewrite merge sort using iterators. */
/** Rewrite merge sort using O(1) extra space. */
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
    
    /** use merge helper function. */
    template <typename ForwardIterator>
    void merge (ForwardIterator first, ForwardIterator left, ForwardIterator mid, ForwardIterator right)
    {
        //        std::cout << *first << '\n';
        //        std::cout << *last << '\n';
        
        // create 2 arrays with size
        typename std::iterator_traits<ForwardIterator>::difference_type sizeLeft, sizeRight, beginLeft, beginRight, currentIndex;
        sizeLeft = std::distance (left, mid);
        sizeRight = std::distance (mid + 1, right);
        beginLeft = std::distance (first, left);
        beginRight = std::distance (first, mid + 1);
        
        typename std::iterator_traits<ForwardIterator>::value_type leftArray[sizeLeft], rightArray[sizeRight];
        
        /** copy subarrays to temp arrays. */
        copy (first + beginLeft, first + beginRight - 1, leftArray);
        copy (first + beginRight, right, rightArray);
        
        for (int i = 0; i < sizeLeft; ++i)
            std::cout << leftArray[i] << '\n';
        
        currentIndex = std::distance(first, left);
        int i {0};
        int j {0};
        
        while ( (i < sizeLeft) && (j < sizeRight))
        {
            if ( leftArray[i] < rightArray[j])
            {
                *(first + currentIndex) = leftArray[i];
                //std::cout << "leftarray: " << leftArray[i] << '\n';
                ++i;
            }
            else if ( leftArray[i] > rightArray[j])
            {
                *(first + currentIndex) = rightArray[j];
                std::cout << "rightarray: " << rightArray[j] << '\n';
                ++j;
            }
            ++currentIndex;
        }
        
        /** Merge the residue array. */
        if (i < sizeLeft)
        {
            copy (leftArray + i, leftArray + sizeLeft, first + currentIndex);
        }
        else if (j < sizeRight)
        {
            copy (rightArray + j, rightArray + sizeRight, first + currentIndex);
        }
        
    }
    
    /** @param first1 is begin() of the
     */
    template <typename ForwardIterator>
    void mergeSort (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2)
    {
        if (first1 == last1)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type count;
        count = std::distance (first1, last1);
        ForwardIterator mid = first1;
        std::advance (mid, count/2);
        mergeSort(first1, mid, first2);
        mergeSort(mid + 1, last1, first2);
        merge(first2, first1, mid, last1);
    }
    
}
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
    int array[] {0, 1, 12, 20, 3, 4};
    int size = sizeof (array) / sizeof (array[0]);
    //SFD_Algorithm::mergeSort(array, array+size, array);
    mergeSort (array, 0, size - 1);
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << ',';
    std::cout << '\n';
}

int main(int argc, const char * argv[]) {
    
    try {
        int testArray[] { 38, 27, 43, 3, 192};
        int testArraySize = sizeof (testArray) / sizeof (testArray[0]);
        //std::cout << testArraySize << '\n';
        //mergeSortProto<int> (testArray, 0, testArraySize - 1);
        //mergeSort<int> (testArray, 0, testArraySize - 1);
        //testCopy(testArray, testArraySize);
        testSFDmergeSort();
        //printArray(testArray, testArraySize);
        
        //testSimpleRecursion();
        
    } catch (std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
    
    return 0;
}

