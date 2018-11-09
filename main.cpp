#include <iostream>
#include "LinkedList.h"
#include "DynamicArray.h"

size_t lengthInteger(size_t num) {
	size_t count = 0;
	while (num) {
		num /= 10;
		count++;
	}

	return count;
}

int main() {
	char* input = new char[1000];
	bool getInput = true;

	//create dynamicArray
	DynamicArray array;
	
	//create linkedList
	LinkedList list;

	//put Integlacho in it
	Student integral;
	integral.name = "Integralcho";
	integral.uni = "fmi";
	list.PushBack(integral);
	

	while (getInput) {
		std::cin.getline(input, 1000);

		if (strstr(input, "append"))  { 
			size_t index;
			// append Name Uni LineIndex
		}

		else if (strstr(input, "removeLast")) {
			size_t index;
			input += 10;
			index = atoi(input);

			array[index].PopBack();
			//removeLast LineIndex
		}

		else if (strstr(input, "removeFirst")) {
			size_t index;
			input += 11;
			index = atoi(input);

			array[index].PopFront();
			//removeFirst LineIndex
		}

		else if (strstr(input, "remove")) {
			char *name;
			//seperate name from other

			size_t index;
			input += 6;
			index = atoi(input);

			array[index].PopByName(name);
			//remove Name LineIndex 
		}

		else if (strstr(input, "merge")) {
			size_t index1, index2;
			input += 6;
			index1 = atoi(input);
			input += lengthInteger(index1) + 1;
			index2 = atoi(input);
			//merge LineIndex LineIndex
			
			//Merge(array[index1], array[index2]);
			array.PopAt(index2);
		}

		else if (strstr(input, "print")) {
			//print
		}

		else if (!strcmp(input, "quit")) {
			getInput = false;
		}
	};
}

