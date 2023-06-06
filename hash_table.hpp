#include <string>

struct ht_item {
    std::string key;
    std::string value;
};

struct ht_hash_table {
    int size;
    int count;
    ht_item** items;
};

ht_hash_table* ht_new();
void ht_del_hash_table(ht_hash_table* ht);
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
std::string ht_search(ht_hash_table* ht, const char* key);
