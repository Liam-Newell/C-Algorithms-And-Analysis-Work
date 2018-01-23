template <typename T>
class Stack {
	T* theStack_;
	int capacity_;  //how much can the array hold
	int used_;  //how much of array is used
	void grow() {
		T* newStack = new T[capacity_ * 2];
		for (int i = 0; i<used_; i++) {
			newStack[i] = theStack_[i];
		}
		delete theStack_;
		theStack_ = newStack;
		capacity_ = capacity_ * 2;
	}
public:
	Stack() {
		capacity_ = 50;
		theStack_ = new T[capacity_];
			used_ = 0;
	}
	void push(const T& data) {
		if (used_ == capacity_) {
			grow();
		}
		theStack_[used_++] = data;
	}
	void pop() {
		if (!empty())
			used_--;
	}
	T top() const {
		return theStack_[used_ - 1];
	}
	bool empty() const {
		return used_ == 0;
	}
	~Stack() {
		delete[] theStack_;
	}
	int getSize() {
		return used_;
	}
};