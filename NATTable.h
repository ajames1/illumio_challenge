#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

class NATTable
{
    protected:
    unordered_map<long long, long long> nat_entries;
    unordered_map<int, long long> ip_only;
    unordered_map<short int, long long> port_only;

    long long ip_to_ll(string str);
    string ll_to_ip(long long ip);
    unsigned int get_port(string str);
    string table_entry_to_str(long long val);

    public:
    void insert(string src, string dest);
    string find(string src);
};

