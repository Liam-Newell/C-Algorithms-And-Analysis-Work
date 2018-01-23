#include <utility>
#include <algorithm>
#include <iostream>
template <typename T>

class SortedList {
	friend class Polynomial;
	struct Node {
		T data_; // a templated value called data; is the basis of this whole applcation. This data will be compared organized and searched by to fullful the expectations of the main
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;

	int size_; //amount of members in sorted list

public:
	class const_iterator {
		friend class SortedList;
	protected:
		Node* it; // variable responsible for tracking the placement in the iterator
		const_iterator(Node* n) {
			it = n;
		}
	public:
		const_iterator() { it = nullptr; }
		//Prefix operator++
		//responsible for setting the node to the next node in list
		//then returns the node pointed to
		const_iterator operator++() {
			it = it->next_;
			return *this;
		}
		//Simple return of data inside the node using asterisk 
		const T& operator*()const{
			return it->data_;
		}
		//Postfix operator++
		//Node pointer takes on address of next node but returns the orginal current
		const_iterator operator++(int){
			const_iterator old = *this;
			++(*this);
			return old;
		}
		//Prefix operator--
		//responsible for setting the node to the previous node in list
		//then returns current the node pointed to
		const_iterator operator--(){
			it = it->prev_;
			return *this->it;
		}
		//Postfix operator--
		//Node pointer takes on address of prev node but returns orginal current one
		const_iterator operator--(int)
		{
			const_iterator* old = *this;
			--(*this);
			return old;
		}
		//Operator== checks if two nodes to the same location
		bool operator==(const_iterator rhs)
		{
			return it == rhs.it;
		}
		//the opposite of above
		bool operator!=(const_iterator rhs) {
			return it != rhs.it;
		}
		//My personal node return function using Ampersand
		Node* operator&()const{
			return it;
		}


	};
	class iterator :public const_iterator {
	public:
		//refers to inhereted function for auto creation
		iterator() :const_iterator() {
		}
		//  
		iterator(Node* n) :const_iterator(n) {}
		T& operator*(){
			return this->it->data_;
		}
		//Prefix operator++
		//responsible for setting the node to the next node in list
		iterator operator++()
		{
			this->it = this->it->next_;
			return *this;
		}
		//Postfix operator++
		//Node pointer takes on address of next node but returns the orginal current
		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}
		//Prefix operator--
		//responsible for setting the node to the previous node in list
		//then returns current the node pointed to
		iterator operator--()
		{
			this->it = this->it->prev_;
			return *this;
		}
		//Postfix operator--
		//Node pointer takes on address of prev node but returns orginal current one
		iterator operator--(int) {
			iterator old = *this;
			--(*this);
			return old;
		}
		//My personal node return function using Ampersand
		Node* operator&() {
			return const_iterator::operator&();
		}


	};
	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};
//Default constructor 
//prepares all data and pointers the sentenials to each other
template <typename T>
SortedList<T>::SortedList()
{
	front_ = new Node();
	back_ = new Node();
	size_ = 0;
	front_->next_ = back_;
	back_->prev_ = front_;
}
//removal of data using existing delete functions
template <typename T>
SortedList<T>::~SortedList()
{
	while (!empty()) {
		erase(begin());
	}
	delete front_;
	front_ = nullptr;
	delete back_;
	back_ = nullptr;
}
//Construtor receiving value of another sorted list
//deep copy with looping addition of data members
template <typename T>
SortedList<T>::SortedList(const SortedList& rhs)
{
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	size_ = 0;
	size_ = rhs.size_;
	for (auto it = rhs.begin(); it != rhs.end(); ++it) {
		Node* last = back_->prev_;
		Node* nn = new Node(*it, back_, last);
		back_->prev_ = nn;
		last->next_ = nn;
	}
}
//Operator= receives sorted list then using a iterator loops through the rhs till the end
//and applies the values to the current object
//the function then returns its current object to the operator
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs) {
	if (this != &rhs) {
		while (!empty()) {
			erase(begin());
		}
		delete front_;
		front_ = nullptr;

		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
		size_ = rhs.size_;
		for (auto i = rhs.begin(); i != rhs.end(); i++) { //loops through received linked list
			Node* last = back_->prev_;
			Node* nn = new Node(*i, back_, last);
			back_->prev_ = nn;
			last->next_ = nn;
		}
	}
	return *this;
}
// Move constructor
//Uses std::move to call the move assignment operator
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs) {
	*this = std::move(rhs);
}

//Move assignment operator
//Switch addresses between the imported sortedlist and the current
//set the old sorted list to default values
//can also be done with rhs.~SortedList();
template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs) {
	if (this != &rhs) {
		front_ = rhs.front_;
		back_ = rhs.back_;
		size_ = rhs.size_;


		rhs.front_ = new Node();
		rhs.back_ = new Node();
		rhs.size_ = 0;
		rhs.front_->next_ = rhs.back_;
		rhs.back_->prev_ = rhs.front_;
	}
	return *this;
}
//points to first data memeber in arraylist
template<typename T>
typename SortedList<T>::iterator SortedList<T>::begin()
{
	return iterator(front_->next_);
}
//points to rear sentinal
template<typename T>
typename SortedList<T>::iterator SortedList<T>::end()
{
	return iterator(back_);
}
//points to first member in datalist
template<typename T>
typename SortedList<T>::const_iterator SortedList<T>::begin() const
{
	return const_iterator(front_->next_);
}

template<typename T>
typename SortedList<T>::const_iterator SortedList<T>::end() const
{
	return const_iterator(back_);
}

//insertion function 
//takes in a new data member and inserts into existing arraylist
//function will loop from highest to lowest in order to find a place for the data to fit in
//this organizes the array as such
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data)
{
	Node* nn = new Node(data, nullptr, nullptr);//this variable will be sorted into the list
	bool breaker = false;
	if (!empty()) {
		for (auto it = begin(); breaker == false; it++) //from beginning to end of linked list
		{
			if (nn->data_ < (*it) || nn->data_ == (*it)) // checks if current node the iterator points to is lesser or equal to the new node 
			{
				nn->next_ = (&it);
				nn->prev_ = (&it)->prev_;

				(&it)->prev_->next_ = nn;
				(&it)->prev_ = nn;


				breaker = true;
				break;
			}
			else if ((&it) == back_) // if the loop hits the back assign it there
			{
				nn->prev_ = back_->prev_;
				nn->next_ = back_;


				back_->prev_->next_ = nn;
				back_->prev_ = nn;

				breaker = true;
				break;
			}
		}
	}
	else { // if the sorted list is empty place it between the sentinals
		front_->next_ = back_->prev_ = nn;
		nn->prev_ = front_;
		nn->next_ = back_;

	}
	size_++; 
	return nn;
}
//basic search function
//looks through all data members in list 
//if data cannot be found returns ending sentinal
template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data)
{

	Node* curr = front_;

	while (curr->next_ != nullptr) { // so begins the while loop, could've used a for loop here but i wanted to give while some love for once
		if (curr->next_->data_ == data)
		{
			return curr->next_;
		}
		curr = curr->next_;
	}
	return end();
}
//same styled search loop as the last except it uses const_iterator
//because of the different iterator i am required to return a iterator pointing to the location
//instead of the actual data member
template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const
{
	const_iterator it = begin();
	while ((&it) != back_)
	{
		if (*it == data) {
			return const_iterator(&it);
		}
		it++;
	}
	return end();
}
//Erase function is given the data member to erase than sucks it out and reassigns the nodes around it
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it) {

	if (&it != back_ || &it != front_) {
		size_--;
		Node* prev = (&it)->prev_;
		Node* next = (&it)->next_;
		prev->next_ = next;
		next->prev_ = prev;
		delete (&it);
		return iterator(next);
	}
	
	return iterator(it);
}
//using the original single erase function the first to last erase iterates through
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last) {
	for (auto it = first; it != last; )//from first to last node erase
	{
		it = erase(it); // return result to iterator to erase again
	}
	return last;
}
//simple check if empty funciton
template <typename T>
bool SortedList<T>::empty() const {
	return front_->next_ == back_;
}
//returns the size variable for various purposes
template <typename T>
int SortedList<T>::size() const
{
	return size_;
}

