#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <iterator>

#define _MAX_STACK_SIZE_ 256

template <class T>
	class Comparator
	{
	public:
		bool compare( const T& a, const T& b ) const{
			return a < b;
		}
	};

//класс map
template <typename TKey, typename TData, class Compare = Comparator<TKey>>
	class map
	{
	private:

		Compare cmp;

// структура для представления узлов дерева
		struct node{
			TKey key;
			TData data;
			unsigned int height;
			node* left;
			node* right;
			node(TKey k, TData d) { key = k; data = d; left = right = 0; height = 1; }
		};
//корень дерева
		node* root;
//получить высоту узла	
		unsigned int height(node* p){
			return p?p->height:0;
		}
//вычислить разницу высот левого и правого поддеревьев
		int balanceFactor(node* p){
			return height(p->right)-height(p->left);
		}
//вычислить новую высоту узла
		void fixHeight(node* p){
			unsigned int hl = height(p->left);
			unsigned int hr = height(p->right);
			p->height = (hl>hr?hl:hr)+1;
		}
//правый поворот вокруг p
		node* rotateright(node* p){
			node* q = p->left;
			p->left = q->right;
			q->right = p;
			fixHeight(p);
			fixHeight(q);
			return q;
		}
//левый поворот вокруг q
		node* rotateleft(node* q){
			node* p = q->right;
			q->right = p->left;
			p->left = q;
			fixHeight(q);
			fixHeight(p);
			return p;
		}
//балансировка узла p
		node* balance(node* p){
			fixHeight(p);
			if( balanceFactor(p) == 2 ){
				if( balanceFactor(p->right) < 0 ){
					p->right = rotateright(p->right);
				}
				return rotateleft(p);
			}
			if( balanceFactor(p)==-2 ){
				if( balanceFactor(p->left) > 0  ){
					p->left = rotateleft(p->left);
				}
				return rotateright(p);
			}
			return p;
		}
//вставка ключа k в дерево с корнем p
		node* addNode(node* p, TKey k, TData d){
			if(p == NULL){
				p = new node(k,d);
			}
			else if( cmp.compare(k, p->key) ){
				p->left = addNode(p->left, k, d);
			}
			else if ( !cmp.compare(k, p->key) ){
				p->right = addNode(p->right, k, d);
			}
			return balance(p);
		}
// поиск узла с минимальным ключом в дереве с корнем p 
		node* findMin(node* p){
			return p->left?findMin(p->left):p;
		}
// удаление узла с минимальным ключом из дерева с корнем p
		node* removeMin(node* p){
			if( p->left == 0 ){
				return p->right;
			}
			p->left = removeMin(p->left);

			return balance(p);
		}
// удаление узла по ключу k из дерева с корнем p
		node* removeNode(node* p, int k) {
			if( p == NULL ) return NULL;

			if( k < p->key ){
				p->left = removeNode(p->left,k);
			}
			else if( k > p->key ){
				p->right = removeNode(p->right,k);
			}	
			else{
				node* q = p->left;
				node* r = p->right;
				delete p;
				if( r == NULL ) return q;
				node* min = findMin(r);
				min->right = removeMin(r);
				min->left = q;
				return balance(min);
			}
			return balance(p);
		}
//поиск по ключу в дереве с корнем p
        	node *search(node *p, TKey k){
            		if(p == NULL) return NULL;

            		if(p->key == k) return p;
            		if(p->key > k) return search(p->left, k);
            		if(p->key < k) return search(p->right, k);
			return NULL;
        	}
		node* copyMap(const node* other){
			node* newMap = nullptr;
			
			 if (other!=nullptr){
           			newMap = new node(other->key, other->data);
          			newMap->height = other->height;

           			newMap->left = copyMap(other->left);
          			newMap->right = copyMap(other->right);
       		 	}

       		  return newMap;
   		}
	public:
//конструктор
		map(){
			root = NULL;
			
		}
		map(TKey key, TData data){
			root = new node(key, data);	
		}
//конструктор копирования
	 	map(const map<TKey, TData>& other){		
			this->root = copyMap(other.root);
		}
//копирующий оператор присваивания
		map& operator=(const map<TKey, TData>* anotherMap);
//деструктор
		void DestroyRecursive(node* p){
    			if (p){
        			DestroyRecursive(p->left);
        			DestroyRecursive(p->right);
        			free(p);
				p = NULL;
    			}
		}

		~map(){
    			DestroyRecursive(root);
		}

		void deleteMap(){
			DestroyRecursive(root);
			root->height = 0;
			root=NULL;	
		}
		
//высота корня
		unsigned int getRootHeight(){
			return root->height;
		}
//данные корня
		TData getRootData(){
			return root->data;
		}
//добавление по ключу
		void insert(TKey k, TData d){
			root = addNode(root, k, d);
		}
//удаление по ключу
		void remove(TKey k){
			root = removeNode(root, k);
		}
//поиск по ключу
		TData searchByKey(TKey key){
			node* currNode = search(root, key);
			if (currNode == NULL){
				return 0;
			}else return currNode->data;
		}
//вывод по итератору
		/*void iterOut(){
			MapIterator iter = MapIterator(root);
			
			while (iter.current != NULL){
				std::cout << iter.Data()<<"\n";
				iter.Next();	
			}

		}*/

		class MapIterator
		{
		friend class map;

  		private:	
			class Stack
			{
    			private:
        			node* stacklist[_MAX_STACK_SIZE_];
        			int top;
    			public:
        		//конструктор
        			Stack(){
					top = -1;
				}
        		//добавление элемента в стек
        			void push(node* item){				
   					if (top ==  _MAX_STACK_SIZE_ - 1){
      						std::cerr << "Переполнение стека!" << std::endl;
      						exit(-1);
   					}
   					top++;
   					stacklist[top] = item;
				}
			//удаление элемента из стека
        			node* pop(){
  					if (top == -1){
    						return NULL;
  					}

  					top--;
  					return stacklist[top+1];
				}			
			};

    			node *root, *current;
    			Stack S;
    	//заполнение стека
    			void fillStack(node* p){
				if (p == NULL) return;
				
  				while (p != NULL){
					if (p->right != NULL) fillStack(p->right);

    					S.push(p);
					current = p;
    					p = p->left;
  				}		
			}
  		public:
    	//конструктор
    			MapIterator(node* tree){
				root = tree;	
  				fillStack(tree);
			}
    	//реализации базовых операций
    			void next(){			
				current = S.pop();
			}
    			void reset(){
				fillStack(root);	
			}
    			TData data(){
				return current->data;	
			}
			TKey key(){
				return current->key;	
			}	
		};
//инициализация итератора
		MapIterator initIter(){
				MapIterator iter = MapIterator(root);
			return iter;
		}
//удаление по итератору
		void removeByIter(MapIterator iter){
			remove(iter.key());
		}
	};
#endif 