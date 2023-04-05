#include <iostream>
#include "priority-queue.h"

int main(){
	
    	priority_queue<int> test(1);
    	test.push(4); test.push(5); test.push(2); test.push(9); test.push(3); 

    	std::cout <<"Head: "<< test.getKernel() << " len: " << test.len() << std::endl;

	return 0;
}
