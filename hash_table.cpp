#include <iostream>
#include <string>
#include <cstring>

#include "hash_table.hpp"

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = new ht_item;
    i->key = std::string(k);
    i->value = std::string(v);
    return i;
}

ht_hash_table* ht_new() {
    ht_hash_table* ht = new ht_hash_table;
    ht->size = 53;
    ht->count = 0;
    ht->items = new ht_item*[ht->size]();
    return ht;
}

static void ht_del_item(ht_item* i) {
    delete i;
}

void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != nullptr) {
            ht_del_item(item);
        }
    }
    delete[] ht->items;
    delete ht;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    int index = std::hash<std::string>{}(key) % ht->size;
    ht_item* item = ht->items[index];
    if (item == nullptr) {
        ht->items[index] = ht_new_item(key, value);
        ht->count++;
    } else {
        if (item->key == key) {
            item->value = value;
        } else {
            while (item != nullptr) {
                index = (index + 1) % ht->size;
                item = ht->items[index];
            }
            ht->items[index] = ht_new_item(key, value);
            ht->count++;
        }
    }
}

std::string ht_search(ht_hash_table* ht, const char* key) {
    int index = std::hash<std::string>{}(key) % ht->size;
    ht_item* item = ht->items[index];
    while (item != nullptr) {
        if (item->key == key) {
            return item->value;
        }
        index = (index + 1) % ht->size;
        item = ht->items[index];
    }
    return "";
}