#include "avl_tree.cpp"
#include "rb_tree.cpp"
#include <iostream>
#include <random>
#include <set>
#include <chrono>
#include <fstream>
#include <ctime>

template<class T>
class profiler
{
    private:
    int N = 1000, n = 10000;
    int *push_sequence = new int[N];
    int *test_sequence = new int[n];
    T tree;

    double get_time()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    int random(int min, int max)
    {
        int a;
        a = min + rand()/(max - min  + 1);
        return a;
    }

public:
    profiler()
    {
        for (int i = 0; i < n; i++)
        {
            test_sequence[i] = random(1, 1000000);
        }
        for (int i = 0; i < N; i++)
        {
            push_sequence[i] = random(1, 1000000);
        }
    }

    void test()
    {
        std::ofstream fout("data.txt");
        for (int i = 0; i < N; i++)
        {
            tree.insert(push_sequence[i]);
            double insert_time = 0;
            double find_time = 0;
            double erase_time = 0;
            for (int j = 0; j < n; j++)
            {
                double start_insert = get_time();
                tree.insert(test_sequence[j]);
                double end_insert = get_time();
                insert_time += end_insert - start_insert;
                double start_find = get_time();
                tree.find(test_sequence[j]);
                double end_find = get_time();
                find_time += end_find - start_find;
                double start_erase = get_time();
                tree.erase(test_sequence[j]);
                double end_erase = get_time();
                erase_time += end_erase - start_erase;
            }

            fout << i << " " << insert_time / n << " " << find_time / n << " " << erase_time / n << endl;
        }
        fout.close();

    }
    ~profiler()
    {
        delete [] push_sequence;
        delete [] test_sequence;
    }
};

int main()
{
    profiler<avl_tree> avl_tree;
    avl_tree.test();
}
