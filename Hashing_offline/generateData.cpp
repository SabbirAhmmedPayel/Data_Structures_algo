
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <chrono>
using namespace std::chrono;
using namespace std;


string randomWord()
{
    int len = 5 + rand() % 6;
    string word;

    for (int i = 0; i < len; ++i)
    {
        char c = 'a' + rand() % 26;
        word += c;
    }

    return word;
}

vector<string> generateRandomstrings(int counts)
{
    vector<string> v;
    for (int i = 0; i < counts; ++i)
    {
        v.push_back(randomWord());
    }

    return v;
}

std::vector<int> generateRandomNumbers(int maxVal, int s)
{
    std::vector<int> numbers;
    numbers.reserve(s);

    std::srand(std::time(nullptr));

    for (int i = 0; i < s; ++i)
    {
        int num = std::rand() % maxVal;
        numbers.push_back(num);
    }

    return numbers;
}

vector<string> getstrings(const vector<string>& all, const vector<int>& indices) {
    vector<string> result;
    result.reserve(indices.size());

    for (int i : indices) {
        result.push_back(all[i]);
    }

    return result;
}

void writeVectorToFile(const std::vector<std::string>& vec, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error opening file " << filename << " for writing.\n";
        return;
    }
    for (const auto& str : vec) {
        outfile << str << '\n';
    }
    outfile.close();
}

int main()
{
    srand(time(nullptr));

    int numberofdata = 10000;
   
    int searchcount = 1000;

    vector<string> alldata = generateRandomstrings(numberofdata);
    vector<int> tars = generateRandomNumbers(numberofdata, searchcount);
    vector<string> searchdata = getstrings(alldata, tars);


writeVectorToFile(alldata, "alldata.txt");
writeVectorToFile(searchdata, "searchdata.txt");

  


}
