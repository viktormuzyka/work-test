#include <iostream>
#include <string>
#include <windows.h> 
#include <vector>
//Task 1
class FILEGuard {
	public:
		FILEGuard(FILE* f):file(f) {};
		~FILEGuard() {
			if (file != nullptr)
				fclose(file);
		}

	private:
		FILE* file;
};
//Task 1**
template<typename T, typename deleter>
class CustomGuard {
	public:
		CustomGuard(T* t, deleter del) :obj(t) {
			customdeleter = del;
		};
		~CustomGuard() {
			customdeleter();
		}

	private:
		T* obj;  //for anyone
		deleter* customdeleter;
};
//Task 2
void foo(std::vector<int>& data) {
	//your code
	std::vector<int> temp = data;
	try {
		temp.push_back(2022);
	} catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		temp = data;
	} catch (...) {
		std::cout << "A problem occured while adding new element to vector" << std::endl;
		temp = data;
	}
	data = temp;
}

int main() {
	std::vector<int> test_data;
	test_data.push_back(5);
	foo(test_data);

	return 0;
}
