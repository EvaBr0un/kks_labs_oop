#include <iostream>
#include "map.h"

int main(){

	map<int, int> mp(1, 120);

	mp.insert(2, 160); mp.insert(3, 50); mp.insert(5, 30); mp.insert(4, 40);
	

	map<int, int> newMp(mp);


	std::cout << "RootHeight: " << newMp.getRootHeight() << std::endl;
	std::cout << "RootData: " << newMp.getRootData() << std::endl;
	std::cout << "Search elem by key '1': " << newMp.searchByKey(1) << std::endl;
	std::cout << "Search elem by key '2': " << newMp.searchByKey(2) << std::endl;
	std::cout << "Search elem by key '3': " << newMp.searchByKey(3) << std::endl;
	std::cout << "Search elem by key '4': " << newMp.searchByKey(4) << std::endl;
	std::cout << "Search elem by key '5': " << newMp.searchByKey(5) << std::endl;


	map<int, int>::MapIterator itr = newMp.initIter();

	itr.next(); itr.next(); itr.next();  

	newMp.removeByIter(itr);
	std::cout << "Search elem by key '3' after removeByIter(): " << newMp.searchByKey(3) << std::endl;


	newMp.remove(2);
	std::cout << "Search elem by key '2' after delete(2): " << newMp.searchByKey(2) << std::endl;


	newMp.deleteMap();
	std::cout << "Search elem by key '4' after deleteMap(): " << newMp.searchByKey(4) << std::endl;
	
	return 0;
}