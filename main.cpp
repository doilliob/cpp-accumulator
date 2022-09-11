#include<fstream>
#include "Accumulator.h"

using namespace std;

int main() {
    Accumulator::Counter cnt;
    string filename = "file.txt";
    {   
        ofstream out(filename);
        out << "AAA" << endl
            << "BBB" << endl
            << "BBB" << endl
            << "CCC" << endl;
    }
    cnt.Count(Accumulator::FileType::STRING, filename);

    {   
        ofstream out(filename);
        out << 1 << endl
            << 2 << endl
            << 3 << endl;
    }
    cnt.Count(Accumulator::FileType::INT, filename);

    {   
        ofstream out(filename);
        out << 1.2 << endl
            << 2.0 << endl
            << 3.2 << endl;
    }
    cnt.Count(Accumulator::FileType::FLOAT, filename);

    return 0;
}