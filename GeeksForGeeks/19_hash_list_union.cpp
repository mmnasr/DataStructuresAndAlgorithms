#include <iostream>
#include <map>
#include <vector>

std::vector<int> intersect_arrays(std::vector<int> v1, std::vector<int> v2) {
	std::map<int, int> m; 
	std::vector<int> intersect; 

	for (std::vector<int>::iterator it=v1.begin(); it != v1.end(); it++) {
		m[*it] = 1;
	}
	for (std::vector<int>::iterator it=v2.begin(); it != v2.end(); it++) {
		if (m.count(*it)) {
			intersect.push_back(*it);
		}
	}
	return intersect;
}

int main(int argc, char* argv[]) {

	std::vector<int> v1;
	std::vector<int> v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(0);
	v2.push_back(2);
	std::vector<int> res = intersect_arrays(v1, v2);
	for(std::vector<int>::iterator it=res.begin(); it != res.end(); it++)
		std::cout << *it << std::endl;

	return 0;
}