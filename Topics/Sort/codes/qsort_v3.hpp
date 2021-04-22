template <typename T>
void _quicksort3(vector<T>& A, int l, int r)
{
    if (l >= r)
        return;

    int lt = l, gt = r, i = l;

    /*
    *  [l, lt)    < pivot
    *  [it, i)   == pivot
    *  [gt, r-1]  > pivot
    */
    std::swap(A[r], A[rand()%(r-l+1) + l]);
    T pivot = A[r];
    while (i < gt) {
        if (A[i] < pivot)
            std::swap(A[i++], A[lt++]);
        else if (A[i] > pivot)
            std::swap(A[i], A[--gt]);
        else
            i++;
    }
    std::swap(A[r], A[gt]);

    _quicksort3(A, l, lt-1);
    _quicksort3(A, gt+1, r);
}

template <typename T>
void quicksort3(vector<T>& A)
{
    srand(time(nullptr));
    _quicksort3(A, 0, A.size()-1);
}