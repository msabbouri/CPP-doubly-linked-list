#pragma once
/*
  dlist.h
  Doubly-linked lists of ints
 */
class dlist {
  public:
    dlist() { }

    struct node {
        int value;
        node* next;
        node* prev;
    };

    node* head() const { return _head; }
    node* tail() const { return _tail; }

    // Returns the node at a particular index (0 is the head). If n >= size()
    // return nullptr; if n < 0, return the head of the list.
    // Must run in O(n) time.
    node* at(int n) const{
    	node* m = _head;

		if(n >= sz){
			return _head;
		}

		else if(n < 0){
			return nullptr;
		}    	

		else{

			while(m != nullptr && n > 0){
				m = m->next;
				n--;	
			}	
		}

		return m;
    	
    }

    // Insert a new value, after an existing one. If previous == nullptr, then
    // the list is assumed to be empty.
    // Must run in O(1) time.
    void insert(node *previous, int value){

    	if(previous == nullptr || previous == _tail){
    		push_back(value);

 		//no ++sz; because push_back has ++sz;
    		}
    		
    	else{
    	
    		node* n = new node{value, previous->next, previous};

			previous->next->prev = n;
    		previous->next = n;

    		++sz;
    		
    	}
    	
    }

    // Delete the given node. Should do nothing if which == nullptr.
    // Must run in O(1) time.
    void remove(node* which){

		if(which == nullptr){
			return;
		}

    	else if(which == _head){
    		pop_front();
    		return;
    	}

    	else if(which == _tail){
    		pop_back();
    		return;
    	}

    	else{
			node* n = which->prev;

			n->next = which->next;
			which->next->prev = n;

			delete which;
			which = nullptr;

			--sz;
			return;
    	}
    	
    }

    // Add a new element to the *end* of the list
    // Must run in O(1) time.
    void push_back(int value){
    	_tail = new node{value, nullptr, _tail};
    	
    	if(_head == nullptr){
    		_head = _tail;
    	}
    		
    	else{
    		_tail->prev->next = _tail;
    	}

    	++sz;
    }

    // Add a new element to the *beginning* of the list
    // Must run in O(1) time.
    void push_front(int value){
    	_head = new node{value, _head, nullptr};
    	
		if(_tail == nullptr){
			_tail = _head;
			}

		else{
			_head->next->prev = _head;
			}

		++sz;
    }

    // Remove the first element
    // Must run in O(1) time 
    void pop_front(){
		if(_head != nullptr && _tail != nullptr){
			if(_head == _tail){
				delete _head;
		    	_head = nullptr;
		    	_tail = nullptr;
				    }
				    
			else{
				node* n = _head->next;
		    	delete _head;
		    	_head = nullptr;
		    	_head = n;
		    	_head->prev = nullptr;
		    	}
		    --sz;
	    	}
	    	    
	    else{
	    	return;
	    }
    }

    // Remove the last element
    // Must run in O(1) time
    void pop_back(){
	    if(_head != nullptr && _tail != nullptr){
	    	if(_head == _tail){
	    		delete _tail;
	    		_head = nullptr;
	    		_tail = nullptr;
	    	}

	    	else{
		    	node* n = _tail->prev;
		    	delete _tail;
		    	_tail = nullptr;
		    	_tail = n;
		    	_tail->next = nullptr;
				}
				
		    	--sz;
	    	}
	
	    	else{
	    		return;
	    	}
    }
    
    // Get the size of the list
    // Should run in O(n) time at the worst
    int size() const{
    	return sz;
    }

    // Returns true if the list is empty
    // Must run in O(1) time
    bool empty() const{
    	if(_head == nullptr && _tail == nullptr){
    		return true;
    	}
    	else{
    		return false;
    	}
    }

  private:
    node* _head = nullptr;
    node* _tail = nullptr; 
    int sz = 0;
};

/* a == b
   Compares two lists for equality, returning true if they have the same
   elements in the same positions. (Hint: it is *not* enough to just compare
   pointers! You have to compare the values stored in the nodes.)

   Runs in O(m) time, where m is the length of the shorter of the two lists.
*/ 
bool operator== (const dlist& a, const dlist& b){

	dlist::node* x = a.head();
	dlist::node* y = b.head();

	if(a.size() == b.size()){
		for(int i = 0 ; i < a.size() ; ++i){
			if(x->value != y->value){
				return false;
				}
			else{
				x = x->next;
				y = y->next;
			}
		}
	}

	else{
		return false;

	}
		return true;
}

/* a + b
   Returns a new list consisting of all the elements of a, followed by all the
   elements of b (i.e., the list concatenation).

   Runs in O(n) time in the length of the result.
*/
dlist operator+ (const dlist& a, const dlist& b){
	dlist e;

	dlist::node* x = a.head();
	dlist::node* y = b.head();

//for list b
	for(int i = 0 ; i < a.size() ; ++i){

		e.push_back(x->value);
		x = x->next;

		}

	for(int j = 0 ; j < b.size() ; ++j){

		e.push_back(y->value);
		y = y->next;
		
	}

	return e;
}

/* reverse(l)
   Returns a new list that is the *reversal* of l; that is, a new list 
   containing the same elements as l but in the reverse order.

   Runs in O(n) time. 
*/
dlist reverse(const dlist& l){

	dlist rev;
	dlist::node* z = l.tail();

	for(int i = 0 ; i < l.size() ; ++i){
		rev.push_back(z->value);
		z = z->prev;
	}

	return rev;	
}
