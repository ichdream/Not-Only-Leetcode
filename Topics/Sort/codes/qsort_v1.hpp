#ifndef _QSORT_V1_HPP                                                                        
#define _QSORT_V1_HPP

/**
* @param:
* @rerturn: note we return the index of the pivot, not the value ifself
*/
template <typename T>
int partition(vector<T>& A, int l, int r)
{
    std::swap(A[r], A[rand() % (r-l+1)+l]);  // 基准点随机
    T pivot = A[r];
    int i = l;
    for (int j = l; j < r; ++j)
    {
        if (A[j] < pivot) {
            std::swap(A[i++], A[j]);
        }
    }
    std::swap(A[i], A[r]);
    return i;
}

/**
* recursively divide the vector into two parts
*/
template <typename T>
void _quicksort(vector<T>& A, int l, int r)
{
    if (l >= r)
        return;

    int p = partition(A, l, r);
    _quicksort(A, l, p-1);
    _quicksort(A, p+1, r);
}

template <typename T>
void quicksort1(vector<T>& A)
{
    srand(time(nullptr));
    _quicksort(A, 0, A.size()-1);
}

#endif