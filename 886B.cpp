#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

int main(){

	int n = 0;
	std::map<int, int> a = {};
	std::set<int> keys = {};
	std::cin >> n;
	int cur = -1;
	
	for(int i = 0; i < n; i += 1){
		std::cin >> cur;
		a[cur] = i;
		keys.insert(cur);
	}

	std::cout << *std::min_element(keys.begin(), keys.end(), [&a](int fst, int scnd){return a[fst] < a[scnd];});

}
