#include "NATTable.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

    NATTable nt;
    string line;

    ifstream natfile;
    ifstream flowfile;
    ofstream ofile;
    flowfile.open("FLOW", ios::in);
    natfile.open("NAT", ios::in);

    if (!flowfile.is_open() || !natfile.is_open())
    {
        cout << "Unable to open input files.";
        return -1;
    }

    while (getline(natfile, line))
    {
        auto pos = line.find(',');
        nt.insert(line.substr(0, pos), line.substr(pos + 1, line.length()));
    }

    ofile.open("OUTPUT", ios::trunc);
    if (!ofile.is_open())
    {
        cout << "Unable to open output files.";
        return -1;
    }

    while (getline(flowfile, line))
    {
        string result = nt.find(line);
        if (result != "")
        {
            ofile << line << " -> " << result << endl;
        }
        else
        {
            ofile << "no nat match for " << line << endl;
        }
    }

    return 0;
}
