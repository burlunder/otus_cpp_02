#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &str, char d) {
  vector<string> r;

  string::size_type start = 0;
  string::size_type stop = str.find_first_of(d);
  while (stop != string::npos) {
    r.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
  }

  r.push_back(str.substr(start));

  return r;
}

template <typename T> void output_pool(T ip_pool) {
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

int main(int argc, char const *argv[]) {
  try {
    vector<vector<int>> ip_pool;

    for (string line; getline(cin, line);) {
      vector<string> v = split(line, '\t');

      /* for (auto i : v) { */
      /*   cout << "." << i; */
      /* } */
      /* cout << endl; */

      vector<int> vi;
      for (string s : (split(v.at(0), '.'))) {
        vi.push_back(stoi(s));
      }
      ip_pool.push_back(vi);
    }

    // TODO reverse lexicographically sort
    /* sort(ip_pool.begin(), ip_pool.end(), greater<vector<string>>()); */
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

    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output
    // ip = filter_any(46)

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
  } catch (const exception &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
