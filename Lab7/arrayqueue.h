template <typename T>
class Queue {
	T* data_;
	int capacity_;
	int used_;
	int front_; //index of first item in queue
	int back_;  //index of the element after the last item in queue
	void grow() {
		T* tmp = new T[capacity_ * 2];
		int j = front_;
		for (int i = 0;i<used_;i++) {
			tmp[i] = data_[j];
			j = (j + 1) % capacity_;
		}
		delete data_;
		data_ = tmp;
		capacity_ = capacity_ * 2;
		front_ = 0;
		back_ = used_ + 1;
	}

public:
	Queue() {
		capacity_ = 50;
		data_ = new T[capacity_];
		used_ = 0;
		front_ = 0;
		back_ = 0;
	}
	void enqueue(const T& data) {
		if (used_ == capacity_) {
			grow();
		}
		data_[back_] = data;
		used_++;
		back_ = (back_ + 1) == capacity_ ? 0 : back_ + 1;
	}
	void dequeue() {
		if (!empty()) {
			front_ = (front_ + 1) % capacity_;
			used_--;
		}

	}
	T front() const {
		return data_[front_];
	}
	bool empty() {
		return used_ == 0;
	}

	~Queue() {
		delete[] data_;
	}
};