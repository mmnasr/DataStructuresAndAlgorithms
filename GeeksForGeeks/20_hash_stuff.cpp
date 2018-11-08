#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>

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
	return twice_count / 2;
}

bool hasDuplicatesInKDistance(std::vector<int> v, int k) {
	/* check if array has duplicates within a distance k */
	std::set<int> m;
	int idx = 0;
	for (std::vector<int>::iterator it=v.begin(); it != v.end(); it++) {
		if (m.find(*it) != m.end()) 
			return true;
		m.insert(*it);
		if (idx >= k) 
			m.erase(it[idx-k]);
		idx++;
	}
	return false;
}

void printTravelItinerary(std::map<std::string, std::string> data) {
	std::map<std::string, std::string> toFrom;
	std::map<std::string, std::string>::iterator it;
	for (it=data.begin(); it != data.end(); it++) {
		/* key */
		std::string fromCity = it->first;
		/* value */
		std::string toCity = it->second;
		toFrom[toCity] = fromCity;
	} /* for */

	std::string startCity;
	for (it=data.begin(); it != data.end(); it++) {
		/* found city of origin, since it does not appear in the 'to' list of keys */
		if (toFrom.find(it->first) == toFrom.end() ) { 
			startCity = it->first;
			break;
		}
	} /* for */
	std::cout << "Start city found:" << startCity << std::endl;

	std::string fromCity = startCity;
	while (data.find(fromCity) != data.end()) {
		std::string toCity = data[fromCity];
		std::cout << "From: " << fromCity << " " << "To: " << toCity << std::endl;
		fromCity = toCity;
	}
}

// TODO NOT CORRECT
int countEmployeeManagerPrivate(std::map<char, std::vector<char> > data, char manager, std::map<char, int> employeeCountUnderManager) {
	/* data[manager] = vector of direct employees reporting tom manager */
	if (data.count(manager) == 0) {
		employeeCountUnderManager[manager] = 0;
		return 0;
	}
	if 	(employeeCountUnderManager.count(manager)) {
		return employeeCountUnderManager[manager];
	}

	std::vector<char>::iterator it;
	int count = employeeCountUnderManager[manager];
	for (it = data[manager].begin(); it != data[manager].end(); it++) {
		//std::cout << "manager: " << manager << " count:" << employeeCount << std::endl;
		char employeeName = *it;
		count += countEmployeeManagerPrivate(data, employeeName, employeeCountUnderManager);
	}
	employeeCountUnderManager[manager] = count;
	return count;
}

// TODO NOT CORRECT
void printEmployeeManagerCount(std::map<char, char> data) {
	/* data[employeeName] = managerName */
	std::map<char, std::vector<char> > reverseMap;
	std::map<char, char>::iterator it;

	for (it = data.begin(); it != data.end(); it++) {
		char employee = it->first; 
		char manager = it->second;
		if (employee == manager) /* CEO */
			continue;
		reverseMap[manager].push_back(employee);
	}
	std::map<char, int> employeeCountUnderManager;
	for (it = data.begin(); it != data.end(); it++) {
		std::cout << "Manager name: " << it->first << " # Employees: " 
			<< countEmployeeManagerPrivate(reverseMap, it->first, employeeCountUnderManager) << std::endl;
	}
}

int main(int argc, char* argv[]) {
	std::vector<int> v1, v2;
	v1.push_back(1);
	v1.push_back(0);
	v1.push_back(2);
	v1.push_back(1);
	v2.push_back(0);
	//std::cout << isSubset(v2, v1) << std::endl;
	std::cout << findSumPair(v1, 0) << std::endl;
	std::cout << countSumPair(v1, 3) << std::endl;
	std::cout << "has duplicates: " << hasDuplicatesInKDistance(v1, 3) << std::endl;
	std::map<std::string, std::string> fromToCity;

	fromToCity["Isfahan"] = "Tehran";
	fromToCity["Tehran"] = "Shiraz";
	fromToCity["Shiraz"] = "Mashhad";

	printTravelItinerary(fromToCity);

	std::map<char, char> employeeManager;
	employeeManager['A'] = 'C';
	employeeManager['B'] = 'C';
	//employeeManager['C'] = 'C';
	employeeManager['C'] = 'F';
	employeeManager['D'] = 'E';
	employeeManager['E'] = 'F';
	employeeManager['F'] = 'F';

	printEmployeeManagerCount(employeeManager);
	return 0;
}