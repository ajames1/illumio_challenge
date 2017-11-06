#include "NATTable.h"
#include <iostream>
using std::cout;
using std::cout;

long long NATTable::ip_to_ll(string str)
{
    long long result = 0;
    for (int i = 0; i < 4; i++)
    {
        auto p = str.find('.');
        int x;
        if (p != string::npos)
        {
            x = stoi(str.substr(0, p));
        }
        else
        {
            x = stoi(str);
        }
        result <<= 8;
        result += x;
        str = str.substr(p + 1, str.length());
    }
    return result;
}

string NATTable::ll_to_ip(long long ip)
{
    string str = "";
    for (int i = 0; i < 4; i++)
    {
        int x = ip & 0xff;
        str = std::to_string(x) + str;
        if (i == 3)
            break;
        ip >>= 8;
        str = "." + str;
    }
    return str;
}

unsigned int NATTable::get_port(string str)
{
    auto p = str.find(':');
    str = str.substr(p + 1, str.length());
    return std::stoi(str);
}

string NATTable::table_entry_to_str(long long val)
{
        string result = "";
        int port = val & 0xffff;
        result = std::to_string(port);
        val >>= 16;
        result = ll_to_ip(val) + ":" + result;
        return result;
}

void NATTable::insert(string src, string dest)
{
    auto pos = src.find(':');
    string src_ip = src.substr(0, pos);
    string src_port = src.substr(pos + 1, src.length());

    pos = dest.find(':');
    string dest_ip = dest.substr(0, pos);
    string dest_port = dest.substr(pos + 1, dest.length());

    long long destval = ip_to_ll(dest_ip);
    destval <<= 16;
    destval += std::stoi(dest_port);

    if (src_ip == "*")
    {
        short int srcval = std::stoi(src_port);
        port_only[srcval] = destval;
    }
    else if (src_port == "*")
    {
        int srcval = ip_to_ll(src_ip);
        ip_only[srcval] = destval;
    }
    else
    {
        long long srcval = ip_to_ll(src_ip);
        srcval <<= 16;
        srcval += std::stoi(src_port);
        nat_entries[srcval] = destval;
    }
}

string NATTable::find(string src)
{
    auto pos = src.find(':');
    string src_ip = src.substr(0, pos);
    string src_port = src.substr(pos + 1, src.length());

    long long target = ip_to_ll(src_ip);
    target <<= 16;
    target += get_port(src_port);

    if (nat_entries.count(target))
    {
        long long destval = nat_entries[target];
        return table_entry_to_str(destval);
    }

    int check_ip = ip_to_ll(src_ip);
    if (ip_only.count(check_ip))
    {
        long long destval = ip_only[check_ip];
        return table_entry_to_str(destval);
    }

    short int check_port = get_port(src);
    if (port_only.count(check_port))
    {
        long long destval = port_only[check_port];
        return table_entry_to_str(destval);
    }

    return "";
}
