#include <iostream>
#include <map>
#include <vector>

bool isSubset(std::vector<int> vsub, std::vector<int> v) {
/* check if an array is a subset of another array */
	std::map<int, int> m;
	for (std::vector<int>::iterator it=v.begin(); it != v.end(); it++) {
		m[*it] = 1;
	}
	for (std::vector<int>::iterator it=vsub.begin(); it != vsub.end(); it++) {
		if (m.count(*it) == 0) 
			return false;
	}
	return true;
}

bool findSumPair(std::vector<int> v, int sum) {
	std::map<int, int> m;
	for (std::vector<int>::iterator it=v.begin(); it != v.end(); it++) {
		int temp = sum - *it;
		if ( (m.count(temp)) ) {
			std::cout << "Found pair " << *it << "," << temp<< " with sum: " << sum << std::endl;
			return true;
		}
		m[*it] = 1;
	}
	return false;
}

int countSumPair(std::vector<int> v, int sum) {
	std::map<int, int> m;
	for (std::vector<int>::iterator it=v.begin(); it != v.end(); it++) {
		m[*it]++;
	}
	int twice_count = 0;
	for (std::vector<int>::iterator it=v.begin(); it != v.end(); it++) {
		twice_count += m[sum - *it];
		if (*it == sum - *it) { /* ignore pairs (val,val) */
			twice_count--;
		}
	}
	std::cout << "here: " << twice_count << std::endl;
	return twice_count / 2;
}

bool hasDuplicatesInKDistance(std::vector<int> v, int k) {
	std::map<int, int> m;
	int idx = 0;
	for (std::vecttor<int>::iterator it=v.begin(); it != v.end(); it++) {
		if (m[*it].count()) 
			return true;
		m[*it] = 1;
		if (idx >= k) > 
			m[*it]

	}
}

int main(int argc, char* argv[]) {
	std::vector<int> v1, v2;
	v1.push_back(0);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(0);
	//std::cout << isSubset(v2, v1) << std::endl;
	std::cout << findSumPair(v1, 0) << std::endl;
	std::cout << countSumPair(v1, 3) << std::endl;

	return 0;
}