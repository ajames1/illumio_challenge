#include <string>
#include <iostream>
#include <cassert>
#include "NATTable.h"

using std::string;

using namespace std;

class testNATTable : public NATTable
{
    public:
    long long test_ip_to_ll(string IP)
    {
        return ip_to_ll(IP);
    }

    string test_ll_to_ip(long long val)
    {
        return ll_to_ip(val);
    }

};

int main(int argc, char *argv[])
{

    testNATTable tester;
    // Test ip_to_ll
    string IP = "12.15.9.0";

    IP = "12.15.9.0";
    assert(tester.test_ip_to_ll(IP) == 0xc0f0900);

    IP = "255.255.255.255";
    assert(tester.test_ip_to_ll(IP) == 0xffffffff);

    IP = "0.0.0.0";
    assert(tester.test_ip_to_ll(IP) == 0x0);

    // Test ll_to_ip
    assert(tester.test_ll_to_ip(0) == "0.0.0.0");

    assert(tester.test_ll_to_ip(0xff00ff0a) == "255.0.255.10");

    assert(tester.test_ll_to_ip(0x0a0b0c0d) == "10.11.12.13");


    // Test NATTable
    tester.insert("12.12.12.12:34", "23.54.23.53:12");
    tester.insert("2.2.2.2:*", "12.12.12.12:12");
    tester.insert("*:35", "13.13.13.13:10");
    assert(tester.find("12.12.12.12:34") == "23.54.23.53:12");
    assert(tester.find("2.2.2.2:89") == "12.12.12.12:12");
    assert(tester.find("2.2.2.2:100") == "12.12.12.12:12");
    assert(tester.find("2.2.2.2:35") == "12.12.12.12:12");
    assert(tester.find("2.2.2.4:35") == "13.13.13.13:10");

    return 0;
}
