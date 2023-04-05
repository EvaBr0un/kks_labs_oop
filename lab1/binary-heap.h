#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <iostream>

template <typename T, template <class...> class container = std::vector>
//класс, описывающий двоичную кучу
	class binary_heap
	{
	private:
		unsigned int size;
		container<T> heap;
		
	public:
//конструкторы
        	binary_heap(){
            		this->heap = container<T>();
            		this->size = 0;
        	}
        	binary_heap(T data){
			this->size = 1;
            		this->heap = container<T>();
            		this->heap.push_back(data);
        	}
//пирамидальная сортировка
		void heapsort(){
			for(int i = size - 1; i >= 0; i--){
				T tmp = heap[0];
				heap[0] = heap[i];
				heap[i] = tmp;
				heapify(0);
			}
		}
//восстановление свойств кучи (Olog(n))
        	void heapify(unsigned int index){
            		unsigned int left = 2*index + 1; 	//левый потомок извлечённого элемента
            		unsigned int right = 2*index + 2;	//правый потомок извлечённого элемента
			T tmp = this->heap[index];			

            		if (left <= this->size && this->heap[left] > this->heap[index]){
                    		this->heap[index] = this->heap[left];
                    		this->heap[left] = tmp;
                    		this->heapify(left); 
            		}

            		if (right <= this->size && this->heap[right] > this->heap[index]){
                    			this->heap[index] = this->heap[right];
                    			this->heap[right] = tmp;
                    			this->heapify(right); 
            		}
        	}
//добавление элемента двоичной кучи (Olog(n))
        	void push(T data){
			int curr_index = this->size;

            		this->size++;

            		this->heap.push_back(data);
            		int parent_index = (curr_index-1)/2;

            		while (curr_index > 0 && this->heap[parent_index] < this->heap[curr_index]){
                		T tmp = this->heap[curr_index];
                		this->heap[curr_index] = this->heap[parent_index];
                		this->heap[parent_index]=tmp;

                		curr_index = parent_index;
                		parent_index = (curr_index-1)/2;
            		}
        	}
//извлечение корневого элемента кучи (Olog(n))
		T pop(){
            		T top = this->heap[0];
            		this->heap[0] = this->heap[ this->size - 1 ];
            		this->heap.pop_back();
            		this->size--;
            		this->heapify(0);

            		return top;
        	}
//получить кол-во элементов кучи
		unsigned int getSize() const{
			return this->size;
		}
//получить корневой элемент
		const T& getKernel() const{
			return this->heap[0];
		}
//вывод двоичной кучи		
		void printHeap(){
			std::cout << "binary_heap: ";
			
            		for (int i = 0; i < this->size; i++){
                		std::cout << this->heap[i] << " ";
            		}
            		std::cout << std::endl;
        	}
	};
#endif