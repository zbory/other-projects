#include <iostream>
#include <vector>

bool
binarySearch(const std::vector<int> &vector, int element, std::vector<int>::iterator begin,
             std::vector<int>::iterator end);

int main()
{
    //Binary search
    //Check whether an element is part of a sorted vector


    int element = -50;
    std::vector<int> sortedVector = {-1001, -543, -39, 4, 5, 6, 7, 13, 25, 99, 153, 1223};

    bool result = binarySearch(sortedVector, element, sortedVector.begin(), sortedVector.end());
    std::cout << element << " is" << (result ? " IN " : " NOT IN ") << "the list!";

    return 0;
}

bool
binarySearch(const std::vector<int> &vector, int element, std::vector<int>::iterator begin,
             std::vector<int>::iterator end)
{
    if ((end - begin) <= 1) {
        if (*begin == element || *end == element)
            return true;
        else
            return false;
    }
//    std::cout << "begin: " << (begin + (end - begin) / 2).base() << ", end: " << vector.end().base() << ", end-begin: "
//              << (end - begin) << std::endl;
    if (*(begin + (end - begin) / 2) == element) return true;
    else if (*(begin + (end - begin) / 2) < element)
        return true && binarySearch(vector, element, begin + (end - begin) / 2, end);
    else
        return true && binarySearch(vector, element, begin, begin + (end - begin) / 2);
}