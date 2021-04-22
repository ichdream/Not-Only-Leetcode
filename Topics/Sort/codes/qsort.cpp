#include<iostream>
#include<vector>


template<typename T>
int partition(std::vector<T> &v, int l, int r, int p) {
    if(r - l <= 0) return r;
    while(l < r) {
        while(v[l] <= v[p]) l++;
        while(v[r] > v[p]) r--;
        if(r - l <= 0) {
            std::cout << "p, r: " << p << "," << r << "\n";
            std::swap(v[p], v[r]);
            return r;
        }
        std::cout << "swap l and r: " << l << " " << r << std::endl;
        std::swap(v[l], v[r]);
    }
    // std::swap(v[p], v[r]);
    return r;
}

template<typename T>
void qsort(std::vector<T>& v, int l, int r) {
    if(r - l <= 0) return;
    int p = l;
    std::cout << "start partition." << "\n";
    int mid = partition(v, l, r, p);
    std::cout << "qsort left parts." << "\n";
    qsort(v, l, mid);
    std::cout << "qsort right parts" << "\n";
    qsort(v, mid + 1, r);
    std::cout << "next qsort" << "\n";
}


template<typename T>
void quickSort(std::vector<T>& s, int l, int r)
{
    if (l< r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] > x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i] <= x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1); // 递归调用
        quickSort(s, i + 1, r);
    }
}

template<typename T>
int partitionHelper(std::vector<T>& v, int l , int r) {
    int pivot = v[r], i = l;
    for(int j = l; j < r; ++j) {
        if(v[j] > pivot) std::swap(v[i++], v[j]);
    }
    std::swap(v[i], v[r]);
    return i;
}


template<typename T>
int getTopK(std::vector<T>& v, int l, int r, int k, int& cnt) {
    int p = partitionHelper(v, l, r);
    cnt++;
    if(k - 1 == p) return v[p];
    else if(k - 1 < p) return getTopK(v, l, p - 1, k, cnt);
    else return getTopK(v, p + 1, r, k, cnt);
}

int main() {
    std::vector<int> v{2,3,3,4,5,76,8,90,0,7,6,5,4,4,9,23,45,6,7,7,87,8,6,54,4,3,3,5,6,87,8,5,4,34,3,5,6,6,6};
    // std::vector<int> v{12, 34, 5, 7 , 9, 6, 3};
    // qsort(v, 0, v.size() - 1);
    // quickSort(v, 0, v.size() - 1);
    int cnt = 0;
    std::cout << "kth num: " << getTopK(v, 0, v.size() - 1, 26, cnt) << "\n";
    std::cout << "find cnt: " << cnt << "\n";
    for(auto num : v)
        std::cout << num << " ";
    std::cout << std::endl;
}