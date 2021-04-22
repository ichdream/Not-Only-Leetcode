
template<typename T>
void merge(std::vector<T>& v, int l, int r, int mid, std::vector<T>& tmp) {
    assert(v.size() == tmp.size());
    int i = l, j = mid + 1, k = 0;
    if(l > r) return;
    while(i <= mid && j <= r) {
        // tmp[k++] = v[i] <= v[j] ? v[i++] : v[j++];
        if(v[i] < v[j]) {
            tmp[k] = v[i];
            i++;
        }
        else {
            tmp[k] = v[j];
            j++;
        }
        k++;
    }
    while(i <= mid) tmp[k++] = v[i++];
    while(j <= r) tmp[k++] = v[j++];
    for(int i = l, k = 0; i <= r; ++i, ++k) v[i] = tmp[k];
}

template<typename T>
void _merge_sort(std::vector<T>& v, int l, int r, std::vector<T>& tmp) {
    if(l >= r) return;
    int mid = l + (r - l) / 2;
    _merge_sort(v, l, mid, tmp);
    _merge_sort(v, mid + 1, r, tmp);
    merge(v, l, r, mid, tmp);
}



template <typename T>
void merge_sort(vector<T>& A)
{
    std::vector<T> tmp(A.size());
    _merge_sort(A, 0, A.size() - 1, tmp);
}