#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using ippool_t = std::vector<std::vector<std::string>>;
using ip_t = std::vector<std::string>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

std::vector<std::string> split(const std::string &str, char d) {
  std::vector<std::string> r;

  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of(d);
  while (stop != std::string::npos) {
    r.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
  }

  r.push_back(str.substr(start));

  return r;
}

void output_pool(ippool_t ip_pool) {
  for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
    for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
      if (ip_part != ip->cbegin()) {
        std::cout << ".";
      }
      std::cout << *ip_part;
    }
    std::cout << std::endl;
  }
}

/* void output_ip(std::vector<std::string> ip) { */
/*   std::cout << "* "; */
/*   for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) { */
/*     if (ip_part != ip.cbegin()) { */
/*       std::cout << "."; */
/*     } */
/*     std::cout << *ip_part; */
/*   } */
/*   std::cout << std::endl; */
/* } */

bool match_ip(ip_t ip, std::string ip_oct) {
  if (ip.front() == ip_oct) {
    /* std::cout << "ip.front(): " << ip.front() << std::endl; */
    return true;
  }
  return false;
};

template <typename... Args>
bool match_ip(ip_t ip, std::string ip_oct, Args... args) {
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

ippool_t filter_any(ippool_t pool, std::string ip_oct) {
  //
  ippool_t new_pool;
  for (auto ip = pool.cbegin(); ip != pool.cend(); ++ip) {
    for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {

      auto ip_part_v = *ip_part;
      if (ip_part_v.compare(ip_oct) == 0) {
        new_pool.push_back(*ip);
      }
    }
  }
  return new_pool;
}

ippool_t filter(ippool_t pool, std::string ip_oct) {
  ippool_t new_pool;
  for (auto ip : pool) {
    if (match_ip(ip, ip_oct)) {
      new_pool.push_back(ip);
    }
  }
  return new_pool;
}

template <typename... Args>
ippool_t filter(ippool_t pool, std::string ip_oct, Args... args) {
  ippool_t new_pool;
  for (auto ip : pool) {
    if (match_ip(ip, ip_oct, args...)) {
      new_pool.push_back(ip);
    }
  }
  return new_pool;
}

int main(int argc, char const *argv[]) {
  try {
    std::vector<std::vector<std::string>> ip_pool;

    for (std::string line; std::getline(std::cin, line);) {
      auto v = split(line, '\t');
      ip_pool.push_back(split(v.at(0), '.'));
    }

    // TODO reverse lexicographically sort
    std::sort(ip_pool.begin(), ip_pool.end(),
              std::greater<std::vector<std::string>>());
    output_pool(ip_pool);

    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first byte and output
    // ip = filter(1)
    output_pool(filter(ip_pool, "1"));

    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)
    output_pool(filter(ip_pool, "46", "70"));

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output
    // ip = filter_any(46)
    output_pool(filter_any(ip_pool, "46"));

    // 186.204.34.46
    // 186.46.222.194
    // 185.46.87.231
    // 185.46.86.132
    // 185.46.86.131
    // 185.46.86.131
    // 185.46.86.22
    // 185.46.85.204
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.223.254.56
    // 46.223.254.56
    // 46.182.19.219
    // 46.161.63.66
    // 46.161.61.51
    // 46.161.60.92
    // 46.161.60.35
    // 46.161.58.202
    // 46.161.56.241
    // 46.161.56.203
    // 46.161.56.174
    // 46.161.56.106
    // 46.161.56.106
    // 46.101.163.119
    // 46.101.127.145
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 46.55.46.98
    // 46.49.43.85
    // 39.46.86.85
    // 5.189.203.46
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
