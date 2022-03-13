#include <iostream>
#include <fstream>
#include <vector>
#include "Array.h"
#include "List.h"
#include "BSTree.h"
#include "HashTable.h"
#include <chrono>
#include <string>

using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::vector;

void ADT_timed_insertions (vector<string> arrstr)
{
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;

    Array<string> a(arrstr.size());

    start_time = std::chrono::system_clock::now();
    for (int i = 0; i < arrstr.size(); ++i)
    {
        a[i] = arrstr[i];
    }
    end_time = std::chrono::system_clock::now();

    cout << "Array data structure insertion took: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " us" << endl;

    List<string> l;

    start_time = std::chrono::system_clock::now();
    for (int i = 0; i < arrstr.size(); ++i)
    {
        l.Prepend(arrstr[i]);
    }
    end_time = std::chrono::system_clock::now();

    cout << "List data structure insertion took: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " us" << endl;

    BSTree <string> t;

    start_time = std::chrono::system_clock::now();
    for (int i = 0; i < arrstr.size(); ++i)
    {
        t.Insert(arrstr[i]);
    }
    end_time = std::chrono::system_clock::now();

    cout << "Tree data structure insertion took: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " us" << endl;

    HashTable<string, string> h(21000);

    start_time = std::chrono::system_clock::now();
    for (int i = 0; i < arrstr.size(); ++i)
    {
        string number_to_string = to_string(i);
        h.Insert(number_to_string, arrstr[i]);
    }
    end_time = std::chrono::system_clock::now();

    cout << "Hash Table data structure insertion took: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " us" << endl;
}


int main()
{
    ifstream file("The Man Who Liked Lions.txt");
    vector<string> arrstr;

    string word;
    while (!(file.eof()))
    {
        file >> word;
        arrstr.push_back(word);
    }


    //ADT_timed_insertions(arrstr);
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;

    Array<string> a(arrstr.size());

    string start_data;
    string middle_data;
    string end_data;

    for (int i = 0; i < arrstr.size(); ++i)
    {
        a[i] = arrstr[i];
    }
    
    start_time = std::chrono::system_clock::now();
    cout << a[0] << " " << a[arrstr.size() / 2] << " " << a[arrstr.size() - 1] << endl;
    end_time = std::chrono::system_clock::now();

    cout << "Array data structure search took: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " us" << endl;
}

