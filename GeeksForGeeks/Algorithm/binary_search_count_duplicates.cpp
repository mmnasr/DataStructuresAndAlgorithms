#include <iostream>

int getLeftIndexUtil(int* arr, int key, int left, int right) {
	while (right > left+1) {
		int mid = left + (right - left)/2;
		if (arr[mid] < key)
			left = mid;
		else
			right = mid;
	}
	return right;
}
int getLeftIndex(int* arr, int n, int key) {
	return getLeftIndexUtil(arr, key, 0-1, n-1);
}

int getRightIndexUtil(int* arr, int key, int left, int right) {
	while (right > left+1) {
		int mid = left + (right - left)/2;
		if (arr[mid] > key) 
			right = mid;
		else
			left = mid;
	}
	return left;
}

int getRightIndex(int* arr, int n, int key) {
	return getRightIndexUtil(arr, key, 0, n);
}

int countDuplicateKeys(int* arr, int n, int key) {
	int left = getLeftIndex(arr, n, key);
	int right = getRightIndex(arr, n, key);
	std::cout << "left: " << left << std::endl;
	std::cout << "right: " << right << std::endl;

	if (arr[right] == key && arr[left] == key)
		return (right - left + 1);
	return 0;
}
int main() {
	int d[5] = {2, 2, 2, 2, 2};
	std::cout << countDuplicateKeys(d, 5, 2);
	return 0;
}