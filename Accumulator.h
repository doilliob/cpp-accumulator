#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>

namespace Accumulator {

template <typename T> class Accumulator {
private:
  T sum;
  bool is_empty = true;

public:
  bool Empty() { return is_empty; }
  Accumulator<T> &operator+(T value) {
    if (is_empty) {
      is_empty = false;
      sum = value;
    } else {
      sum += value;
    }
    return *this;
  }

  T Value() {
    if (is_empty) {
      throw std::runtime_error("Accumulator is empty!");
    }
    return sum;
  }
};

template <> class Accumulator<std::string> {
private:
  std::unordered_map<std::string, int> values;
  int last_index = 0;

public:
  bool Empty() { return values.empty(); }
  Accumulator<std::string> &operator+(std::string value) {
    if (values.find(value) == values.end()) {
      last_index++;
      values[value] = last_index;
    }
    return *this;
  }

  std::string Value() {
    if (Empty())
      throw std::runtime_error("Accumulated data is empty!");
    // Set with sorted pairs
    std::set<std::pair<int, std::string>> flipped;
    for(auto const &kv : values) {
        flipped.emplace(kv.second, kv.first);
    }
    // Make sum
    std::string sum = "";
    for (auto const &p : flipped) {
      sum += p.second;
    }
    return sum;
  }
};

template <typename T>
std::istream &operator>>(std::istream &in, Accumulator<T> &acc) {
  T value;
  in >> value;
  acc + value;
  return in;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Accumulator<T> &acc) {
  if (!acc.Empty()) {
    out << acc.Value();
  }
  return out;
}

enum FileType { INT, FLOAT, STRING };

class Counter {
private:
  template <typename T>
  void ReadAndPrint(std::string filename) {
    Accumulator<T> acc;
    std::ifstream f(filename);
    while (f >> acc) {
    }
    std::cout << acc << std::endl;
  }

public:
  void Count(FileType ftype, std::string filename) {
    switch (ftype) {
    case FileType::INT:
      ReadAndPrint<int>(filename);
      break;
    case FileType::FLOAT:
      ReadAndPrint<float>(filename);
      break;
    case FileType::STRING:
      ReadAndPrint<std::string>(filename);
      break;
    }
  }
};

} // namespace Accumulator