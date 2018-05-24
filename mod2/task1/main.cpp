#include <iostream>
#include <string>

const size_t A = 31;

size_t hash1(const std::string key, size_t size) {
    size_t hash = 0;
    for (auto i : key) {
        hash = (hash * A + i) % size;
    }
    return hash;
}

size_t hash2(const std::string key, size_t size) {
    size_t hash = 0;
    for (auto i = key.end() - 1; i >= key.begin(); i--) {
        hash = (hash * A + *i) % size;
    }
    if (hash <= 2) {
        hash = 3;
    }
    if (hash % 2 == 0) {
        hash--;
    }
    return hash;
}

class HashTable {
public:
    HashTable() : _size(0), _buffSize(8) {
        _data = new std::string[_buffSize];
        for (size_t i = 0; i < _buffSize; i++) {
            _data[i] = _empty;
        }
    }

    HashTable(size_t buffSize): _size(0), _buffSize(buffSize) {
        _data = new std::string[_buffSize];
        for (size_t i = 0; i < _buffSize; i++) {
            _data[i] = _empty;
        }
    }

    ~HashTable() {
        delete [] _data;
    }

    bool has(const std::string key);
    bool add(const std::string key);
    bool del(const std::string key);

private:
    void reAdd(std::string* newData, std::string key);
    void reHash();

    std::string* _data;
    size_t _size;
    size_t _buffSize;

    const std::string _empty = "ba2b45bdc11e2a4a6e86aab2ac693cbb";
    const std::string _del = "63c2867fdcae0e8e8413d7ac21b69b59";
};

void HashTable::reAdd(std::string* newData, std::string key) {
    size_t h2 = hash2(key, _buffSize * 2);
    size_t i = 0;
    size_t h = hash1(key, _buffSize * 2) % (_buffSize * 2);
    while (newData[h] != _empty && i < _buffSize * 2) {
        i++;
        h = (h + h2) % (_buffSize * 2);
    }
    newData[h] = key;
}

void HashTable::reHash() {
    std::string* newData = new std::string[_buffSize * 2];
    for (size_t i = 0; i < _buffSize * 2; i++) {
        newData[i] = _empty;
    }

    for (size_t i = 0; i < _buffSize; i++) {
        if (_data[i] != _empty && _data[i] != _del) {
            reAdd(newData, _data[i]);
        }
    }

    delete [] _data;
    _data = newData;
    _buffSize *= 2;
}

bool HashTable::has(const std::string key) {
    size_t i = 0;
    size_t h2 = hash2(key, _buffSize);
    size_t h = hash1(key, _buffSize) % _buffSize;

    while (_data[h] != _empty && i < _buffSize) {
        if (_data[h] == key) {
            return true;
        }
        i++;
        h = (h + h2) % _buffSize;
    }
    return false;
}


bool HashTable::add(const std::string key) {
    if ((double)_size / _buffSize - (double)3/4 > 0.001) {
        reHash();
    }

    size_t i = 0;
    size_t h2 = hash2(key, _buffSize);
    size_t h = hash1(key, _buffSize) % _buffSize;
    size_t firstDeleted = 0;
    bool findDeleted = false;
    while (_data[h] != _empty && i < _buffSize) {
        if (_data[h] == key) {
            return false;
        }
        if (_data[h] == _del) {
            firstDeleted = h;
            findDeleted = true;
        }
        i++;
        h = (h + h2) % _buffSize;
    }
    if (_data[h] != _empty) {
        if (findDeleted) {
            _data[firstDeleted] = key;
            _size++;
            return true;
        }
        return false;
    }
    _data[h] = key;
    _size++;
    return true;
}

bool HashTable::del(const std::string key) {
    size_t i = 0;
    size_t h2 = hash2(key, _buffSize);
    size_t h = hash1(key, _buffSize) % _buffSize;
    while (_data[h] != key && i < _buffSize) {
        if (_data[h] == _empty) {
            return false;
        }
        i++;
        h = (h + h2) % _buffSize;
    }
    if (_data[h] == key) {
        _data[h] = _del;
        _size--;
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    HashTable dict = HashTable(2);
    char c;
    std::string str, answ;

    while (std::cin.get(c)) {
        std::cin >> str;
        switch (c) {
            case '+':
                std::cout << (dict.add(str) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (dict.del(str) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (dict.has(str) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                break;
        }
        std::cin.get();
    }

    return 0;
}