#ifndef _QSORT_V2_HPP
#define _QSORT_V2_HPP

template <typename T>
int partiton2(vector<T>& A, int l, int r)
{
    std::swap(A[r], A[rand()%(r-l+1) + l]);
    T pivot = A[r];
    int i = l, j = r-1;
    while (true) {
        while (i < r && A[i] < pivot) i++;  // 不能 <=，有等于有可能平衡会倾斜一边
        while (j >= l && A[j] > pivot) j--; // 不能 >=
        if (i > j) break;
        std::swap(A[i++], A[j--]);   // 等于pivot的数据需要平均分配到两边
    }
    std::swap(A[r], A[i]);
    return i;
}

template <typename T>
void _quicksort2(vector<T>& A, int l, int r)
{
    if (l >= r)
        return;

    int p = partiton2(A, l, r);
    _quicksort2(A, l, p-1);
    _quicksort2(A, p+1, r);
}

template <typename T>
void quicksort2(vector<T>& A)
{
    _quicksort2(A, 0, A.size()-1);
}

#endif