#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

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

int output(std::vector<std::vector<std::string>> ip_pool) {
  for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
    for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
      if (ip_part != ip->cbegin()) {
        std::cout << ".";
      }
      std::cout << *ip_part;
    }
    std::cout << std::endl;
  }

  return 0;
}

int main() {
  try {
    std::vector<std::vector<std::string>> ip_pool;
    std::vector<std::vector<std::string>> ip_pool_1;
    std::vector<std::vector<std::string>> ip_pool_70;
    std::vector<std::vector<std::string>> ip_pool_46;

    for (std::string line; std::getline(std::cin, line);) {
      auto v = split(line, '\t');
      ip_pool.push_back(split(v.at(0), '.'));
    }

    // if I understand lexicographical sort correctly
    std::sort(ip_pool.begin(), ip_pool.end(),
              std::greater<std::vector<std::string>>());

    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
      auto oct2ndflg = false; // flag to match 2nd octet

      for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {

        auto ip_part_v = *ip_part;

        if (ip_part_v.compare("1") == 0 and ip_part == ip->cbegin()) {
          ip_pool_1.push_back(*ip); // grab all oct1 == 1
        }

        if (ip_part_v.compare("46") == 0) {
          ip_pool_46.push_back(*ip); // grab all any oct == 46

          if (ip_part == ip->cbegin()) {
            oct2ndflg = true;
          }
        }

        if (oct2ndflg and (ip_part_v.compare("70") == 0) and
            (ip_part - ip->cbegin() == 1)) {

          ip_pool_70.push_back(*ip); // grab all 46.70.*
        }

        if (ip_part != ip->cbegin()) {
          std::cout << ".";
        }
        std::cout << *ip_part;
      }
      std::cout << std::endl;
    }

    // second iteration over ip_pool_1
    output(ip_pool_1);
    output(ip_pool_70);
    output(ip_pool_46);

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
