#include <iostream>
#include <fstream>
using namespace std;

void shift(unsigned int& registr, int n) {
    unsigned int value = 0;
    for (int i = 0; i < n - 1; i++) {
        value |= ((registr >> i) & 1);
        value = value << 1;
    }
    value |= ((registr >> (n - 1)) & 1);
    registr = value;
}

int CRC32(unsigned int polinom, unsigned int registr, string file) {
    char ch;
    ifstream stream;
    stream.open(file, ifstream::in);
    if (!stream.is_open()) {
        return -1;
    }
    while (stream.get(ch)) {
        if (stream.eof()) exit;
        for (int i = 0; i < 8; i++) {
            int bit = ((ch >> i) & 1) ^ ((registr >> 31) & 1);
            registr = registr << 1;
            if (bit) {
                registr ^= polinom;
            }
        }
    }




    cout << registr << endl;
    shift(registr, 32);
    cout << registr << endl;
    registr ^= 0xffffffff;

    return registr;
}

int main()
{

    unsigned int init = 0xFFFFFFFF;
    unsigned int polynom = 0x04C11DB7;

    unsigned int check = CRC32(polynom, init, "crc.txt");
    cout << std::hex;
    cout << "--------------" << endl;
    cout << "CRC32" << endl;
    cout << "Polynom: " << polynom << endl;
    cout << "Check Sum: " << check << endl;
    unsigned int i = 1;
    shift(i, 32);
    cout << dec << i;
    return 0;
}
