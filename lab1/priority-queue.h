#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

template <typename T, class container = std::vector<T>>
	class priority_queue
	{
	private:

//класс, описывающий двоичную кучу
		class binary_heap
		{
		private:
			unsigned int size;
			container heap;
			
		public:
	//конструкторы
			binary_heap(){
		    		this->heap = container();
		    		this->size = 0;
			}
			binary_heap(T data){
				this->size = 1;
		    		this->heap = container();
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

		binary_heap data;	
	public:
//конструкторы
		priority_queue(){};
		priority_queue(T orig){
			data = binary_heap(orig);
		}
//удаление элемента из очереди
        	T pop(){
           		return this->data.pop();
        	}
//добавление элемента в очередь
        	void push(T element){
            		this->data.push(element);
        	}
//доступ к максимальному элементу очереди
        	const T& getKernel() const{
            		return this->data.getKernel();
        	}
//получение числа элементов в очереди
        	unsigned int len() const{
            		return this->data.getSize();
        	}
//проверка очереди на пустоту
        	bool isEmpty(){
            		return (this->len() == 0);
        	}
	};
#endif