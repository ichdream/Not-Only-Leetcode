#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <cassert>

using namespace std;

namespace sort_helper {
    /*
    * 随机生成 n 个[l, r]的数组
    */
    template <typename T>
    void generate_array(vector<T>& A, int n, int l, int r)
    {
        assert(l <= r);
        A.clear();
        A.reserve(n);
        srand(time(nullptr));
        for (int i = 0; i < n; ++i)
        {
            int e = rand() % (r - l + 1) + l;
            A.push_back(e);
        }
    }

    /*
    * 随机生成近乎有序的 n 个[0, n-1]的数组
    */
    template <typename T>
    void generate_nearly_sorted_array(vector<T>&A, int n, int swap_count)
    {
        for (int i = 0; i < n; ++i)
        {
            A.push_back(i);
        }

        srand(time(nullptr));
        for (int i = 0; i < swap_count; ++i)
        {
            int l = rand() % n;
            int r = rand() % n;
            swap(A[l], A[r]);
        }
    }

    /*
    * 检测数组是否有序
    */
    template <typename T>
    bool is_sorted(vector<T>& A)
    {
        for (int i = 0; i < A.size()-1; ++i) {
            if (A[i] > A[i+1])
                return false;
        }
        return true;
    }

    /*
    * 测试排序算法，打印算法效率
    */
    template <typename T>
    void testsort(const string& sortname, vector<T>& A,
                  function<void(vector<T>&)> sort_func)
    {
        clock_t start_time = clock();
        sort_func(A);
        clock_t end_time = clock();
        assert(is_sorted(A));
        cout << sortname << ": "
             << double(end_time - start_time) / CLOCKS_PER_SEC
             << "s" << endl;
    }
}