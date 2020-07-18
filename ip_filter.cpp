#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ip_t = array<int, 4>;
using ip_pool_t = vector<array<int, 4>>;

// directly getting ip substring into ip_t
static ip_t split(const string &str, char d) {
  ip_t r;
  string::size_type start = 0;
  string::size_type stop = str.find_first_of(d);

  auto it = 0;
  while (it < 4) { // assume 4 as ip consists of 4 octets
    r.at(it) = stoi(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
    it++;
  }

  return r;
}

template <typename T> void const output_pool(const T &ip_pool) {
  for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
    for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
      if (ip_part != ip->cbegin()) {
        cout << ".";
      }
      cout << *ip_part;
    }
    cout << endl;
  }
}

bool match_ip(const ip_t &ip, const int &ip_oct) {
  if (ip.front() == ip_oct) {
    /* std::cout << "ip.front(): " << ip.front() << std::endl; */
    return true;
  }
  return false;
};

template <typename... Args> bool match_ip(ip_t ip, int ip_oct, Args... args) {
  if (match_ip(ip, ip_oct)) {
    std::rotate(ip.begin(), ip.begin() + 1, ip.end());

    if (match_ip(ip, args...)) {
      std::rotate(ip.rbegin(), ip.rbegin() + 1, ip.rend());
      return true;
    }
    return false;
  };
  return false;
}

ip_pool_t filter_any(const ip_pool_t &pool, const int &ip_oct) {
  ip_pool_t new_pool;
  for (auto ip = pool.cbegin(); ip != pool.cend(); ++ip) {
    for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {

      auto ip_part_v = *ip_part;
      if (ip_part_v == ip_oct) {
        new_pool.push_back(*ip);
        break;
      }
    }
  }
  return new_pool;
}

ip_pool_t filter(const ip_pool_t &pool, const int &ip_oct) {
  ip_pool_t new_pool;
  for (auto ip : pool) {
    if (match_ip(ip, ip_oct)) {
      new_pool.push_back(ip);
    }
  }
  return new_pool;
}

template <typename... Args>
ip_pool_t filter(const ip_pool_t &pool, const int &ip_oct, Args... args) {
  ip_pool_t new_pool;
  for (auto ip : pool) {
    if (match_ip(ip, ip_oct, args...)) {
      new_pool.push_back(ip);
    }
  }
  return new_pool;
}

int main(int argc, char const *argv[]) {
  try {
    ip_pool_t ip_pool;

    for (string line; getline(cin, line);) {
      auto ip_s = split(line, '.');
      ip_pool.push_back(ip_s);
    }

    // TODO reverse lexicographically sort
    // is it really lexicographical ?
    sort(ip_pool.begin(), ip_pool.end(), greater<ip_t>());
    output_pool(ip_pool);

    // TODO filter by first byte and output
    // ip = filter(1)
    output_pool(filter(ip_pool, 1));

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)
    output_pool(filter(ip_pool, 46, 70));

    // TODO filter by any byte and output
    // ip = filter_any(46)
    output_pool(filter_any(ip_pool, 46));

  } catch (const exception &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
