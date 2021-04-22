#include <vector>
#include "sortHelper.hpp"
#include "mergeSort.hpp"
#include "qsort_v1.hpp"
#include "qsort_v2.hpp"
#include "qsort_v3.hpp"
#include "stlSort.hpp"
#include<algorithm>

int main()
{
    int n = 1000000;
    vector<int> arr1;
    // 生成含 1000000 个数据在 [0, 1000000] 的数组
    sort_helper::generate_array(arr1, n, 0, n);
    sort_helper::testsort<int>("mergesort", arr1, merge_sort<int>);
    sort_helper::generate_array(arr1, n, 0, n);
    sort_helper::testsort<int>("quicksort", arr1, quicksort<int>);
    sort_helper::generate_array(arr1, n, 0, n);
    sort_helper::testsort<int>("quicksort2", arr1, quicksort2<int>);
    sort_helper::generate_array(arr1, n, 0, n);
    sort_helper::testsort<int>("quicksort3", arr1, quicksort3<int>);
    sort_helper::generate_array(arr1, n, 0, n);
    sort_helper::testsort<int>("stl sort", arr1, stlSort<int>);

    // 生成含 1000000 个数据在 [0, 1000000] 近乎有序的数组
    // vector<int> arr3;
    sort_helper::generate_nearly_sorted_array(arr1, n, 10);
    sort_helper::testsort<int>("mergesort", arr1, merge_sort<int>);
    sort_helper::generate_nearly_sorted_array(arr1, n, 10);
    sort_helper::testsort<int>("quicksort", arr1, quicksort<int>);
    sort_helper::generate_nearly_sorted_array(arr1, n, 10);
    sort_helper::testsort<int>("quicksort2", arr1, quicksort2<int>);
    sort_helper::generate_nearly_sorted_array(arr1, n, 10);
    sort_helper::testsort<int>("quicksort3", arr1, quicksort3<int>);
    sort_helper::generate_nearly_sorted_array(arr1, n, 10);
    sort_helper::testsort<int>("stl sort", arr1, stlSort<int>);

    // 生成含 1000000 个数据在 [0, 10] 的数组
    sort_helper::generate_array(arr1, n, 0, 10);
    sort_helper::testsort<int>("mergesort", arr1, merge_sort<int>);
    sort_helper::generate_array(arr1, n, 0, 10);
    sort_helper::testsort<int>("quicksort", arr1, quicksort<int>);
    sort_helper::generate_array(arr1, n, 0, 10);
    sort_helper::testsort<int>("quicksort2", arr1, quicksort2<int>);
    sort_helper::generate_array(arr1, n, 0, 10);
    sort_helper::testsort<int>("quicksort3", arr1, quicksort3<int>);
    sort_helper::generate_array(arr1, n, 0, 10);
    sort_helper::testsort<int>("stl sort", arr1, stlSort<int>);
}