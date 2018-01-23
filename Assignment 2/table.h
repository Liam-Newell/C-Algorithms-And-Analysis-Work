/*************************************************************/
/*    V 1.1:                                                 */
/*      - added prototypes for numRecords() and isEmpty()    */
/*      - coded isEmpty() and numRecords() in SimpleTable    */
/*      - created empty functions for isEmpty() and          */
/*        numRecords() in LPTable                            */
/*************************************************************/
/*
	Modifed functions
		-search
		- Copy constructor
		- Copy assignment
		- sort
		- update
		- destructor
		- remove
*/

#include <string>
#include <utility>
using namespace std;

template <class TYPE>
class Table{
public:
	Table(){}
	virtual bool update(const string& key, const TYPE& value)=0;
	virtual bool remove(const string& key)=0;
	virtual bool find(const string& key, TYPE& value)=0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

	struct Record{
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data){
			key_=key;
			data_=data;
		}

	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int search(const string& key);
	void sort();
	void grow();
	void MergeSort(Record** tmp, int start, int end);
	void Merge(Record** tmp, int startA, int startB, int endB);

public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const{return size_==0;}
	virtual int numRecords() const{return size_;}
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key){
	int rc=-1; // 1
	int low = 0; //2
	int high = size_ - 1; //4
	int mid = high / 2; //6
	if(size_ > 0)//8
		if (records_[mid]->key_ != key)//10
			while (low <= high) { //11 Dynamic 1
				if (records_[mid]->key_ == key) //Dynamic 3
					return rc = mid;
				else if (records_[mid]->key_ < key)// Dyn 5
					low = mid + 1;
				else
					high = mid - 1; //dyn 7
				mid = (high + low) / 2; // dyn 9
			}
		else
			return rc = mid;
	return rc;//12
}// (9n /2n) + 12

//sort the according to key in table using a merge sort
template <class TYPE>
void SimpleTable<TYPE>::sort(){
	Record** temp= new Record*[size_];
	MergeSort(temp, 0, size_ - 1);
	if (temp) {
		int sz = size_;
		for (int i = 0;i<sz;i++) {
			temp[i] = nullptr;
		}
		delete temp;
	}
} //7n(3n + 1) + 2 == 21n2 + 7n + 2

template <class TYPE>
void SimpleTable<TYPE>::MergeSort(Record** tmp, int start, int end) {
	//if the array is more than one element big
	if (start<end) {
		int mid = (start + end) / 2;
		MergeSort(tmp, start, mid);
		MergeSort(tmp, mid + 1, end);
		Merge(tmp, start, mid + 1, end);
	}
}

template <class TYPE>
void SimpleTable<TYPE>::Merge(Record** tmp, int startA, int startB, int endB) {
	int indexA = startA;
	int indexB = startB;
	int index = startA;

	while (indexA < startB && indexB < endB + 1) {
		//small sort for each block section of the merge(repeated)
		if (records_[indexA]->key_ < records_[indexB]->key_){
			tmp[index++] = records_[indexA++];
		}
		else {
			tmp[index++] = records_[indexB++];
		}
	}
	//only one of these loops are used
	while (indexA < startB)
	{
		tmp[index++] = records_[indexA++];
	}
	while (indexB < endB + 1) {
		tmp[index++] = records_[indexB];
		indexB++;
	}
	//copy into main array records_
	for (size_t i = startA; i <= endB; i++)
	{
		records_[i] = tmp[i];
	}
}


//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow(){
	Record** newArray=new Record*[max_*2]; //3
	max_=max_*2; //2
	for(int i=0;i<size_;i++){//1
		newArray[i]=records_[i];
	}//3
	delete [] records_;//1
	records_=newArray;//1
}//(3n + 8)

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected): Table<TYPE>(){
	records_=new Record*[maxExpected];
	max_=maxExpected;
	size_=0;
}
//copy constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	records_=new Record*[other.max_];//2
	max_=other.max_;//3
	size_=0;//4
	for(int i=0;i<other.size_;i++){ //5
		records_[size_++] = new Record(other.records_[i]->key_, other.records_[i]->data_);
	}//5 dynamic n times
}//5n + 5
//move constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	size_=other.size_;
	max_=other.max_;
	records_=other.records_;
	other.records_=nullptr;
	other.size_=0;
	other.max_=0;
}
//fixed update 
template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value){
	int idx=search(key); //1 O(logn)
	if(idx==-1){ // 3
		if(size_ == max_){ // 5
			grow(); // (3n + 8)
		}
		records_[size_++]=new Record(key,value); //7
		if(size_ > 1)//9
			
			sort(); //(nlogn)
	}
	else{
		records_[idx]->data_=value;
	}
	return true; // 10
} //search of O(logn) + grow of(3n + 8) + sort of O(nlogn) comes out to a worst case of T(n) = O(n)


template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx=search(key); //1 static plus search O(logn)
	if(idx!=-1){ //3
		delete records_[idx];//4
		for(int i=idx;i<size_-1;i++){ //5 
			records_[i]=records_[i+1];
		}//5 dynamic
		size_--;//6
		return true;//7
	} // 5n + 7 + logn
	else{
		return false; // (5n + 3) + 4 = (5n + 7)
	}
}

//find uses search to find the key the evaluates for it
template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx=search(key); // 1 search(5n + 3)
	if(idx==-1) // 2
		return false;
	else{
		value=records_[idx]->data_; //1
		return true;//1
	}
} // 5 static search of 5n + 3 // 5n + 7

//copy constructor
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if(this!=&other){ // 2
		if(records_){ // 4
			int sz=size_; // 5
			for(int i=0;i<sz;i++){//6
				delete records_[i]; // 3n
			}// two dynamic and the remove(assmed found) 10n + 10
			delete [] records_;//7
		}
		records_=new Record*[other.max_]; //9
		max_=other.max_; //10
		size_=0;//11
		for(int i=0;i<other.size_;i++){//12
			records_[size_++] = new Record(other.records_[i]->key_, other.records_[i]->data_);
		}// 3n first loop 5n second with 12 constants 3n + 5c + 12

	}
	return *this;
}
//move constructor
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	swap(records_,other.records_);
	swap(size_,other.size_);
	swap(max_,other.max_);
	return *this;
}
//destructor loops through array removes all and sets all to delete
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){//2
		int sz=size_;//3
		for(int i=0;i<sz;i++){//4
			delete records_[i];
			//remove(records_[0]->key_);
		}//3n
		delete [] records_;//5
	}
}//3n + 5

template <class TYPE>
class LPTable:public Table<TYPE>{
	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}

	};

	Record** records_;   //the table
	size_t maxExpected_;
	size_t size_;
	size_t capacity_;
	double percentOpen_;
	std::hash<std::string> hashFunction;
	int hashvalue(string a) const { return hashFunction(a) % this->capacity_; }
public:
	LPTable(int maxExpected,double percentOpen);
	LPTable(const LPTable& other);
	LPTable(LPTable&& other);
	int search(const string& key);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const LPTable& operator=(const LPTable& other);
	virtual const LPTable& operator=(LPTable&& other);
	virtual ~LPTable();
	virtual bool isEmpty() const { return 0; }
	virtual int numRecords() const { return size_; }
	
};
template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected,double percentOpen): Table<TYPE>(){
	size_ = 0;
	maxExpected_ = maxExpected;
	percentOpen_ = percentOpen;
	capacity_ = maxExpected*(percentOpen + 1);
	records_ = new Record*[capacity_];
	for (size_t i = 0; i < capacity_; i++)
	{
		records_[i] = nullptr;
	}
}
//basic copy constr
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){
	this->size_ = other.numRecords();
	maxExpected_ = other.maxExpected_;
	percentOpen_ = other.percentOpen_;
	capacity_ = other.capacity_;
	records_ = new Record*[other.capacity_];
	this->hashFunction = other.hashFunction;
	for (size_t i = 0; i < other.capacity_; i++)
	{
		if (other.records_[i])
			records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
		else
			records_[i] = nullptr;
	}
	
}
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other)
{
	*this = move(other);
}
template<class TYPE>
int LPTable<TYPE>::search(const string & key){
	
}
template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value){

		//orginal placement of item
		int place = this->hashvalue(key);
		int curr = place;
		
		while (1) {
			//check to see if item already exists at location
			if (curr != (this->capacity_)) {
				//iterate low key
				if (!this->records_[curr] ) {
					if (!(this->size_ < this->maxExpected_)) {
						return false;
					}
					records_[curr] = new Record(key, value);
					size_++;
					return true;
				}
				else if (this->records_[curr]->key_ == key) {
					records_[curr]->data_ = value;
					return true;
				}
			}
			else {
				curr = 0;
			}
			curr++;
		}
	
	return false;
}
//the remove function will loop through the array once to remove the element then loop near the element removed to find a hash to replace it
template <class TYPE>
bool LPTable<TYPE>::remove(const string& key){
	int hashLocation = this->hashvalue(key);
	int curr = hashLocation;
	int empty;
	bool circled = false;
	//round for element to remove
	while (1) {
		if (records_[curr]) {
			if (records_[curr]->key_ == key)
			{
				delete records_[curr];
				records_[curr] = nullptr;
				empty = curr++;
				if (curr == this->capacity_)
				{
					circled == true;
					curr = 0;
				}
				break;
			}
		}
		else {
			return false;
		}
		curr++;
		if (curr == this->capacity_)
		{
			circled == true;
			curr = 0;
		}
	}
	//checks to see if the records is between the empty and curr spot
	while (records_[curr]) {
		if ((this->hashvalue(records_[curr]->key_)) < curr && ((this->hashvalue(records_[curr]->key_)) <= empty)) {
			records_[empty] = records_[curr];
			empty = curr;
			records_[curr++] = nullptr;
		}
		else{

			curr++;
		}
		if (curr == this->capacity_) {
			circled == true;
			curr = 0;

		}
	}
	size_--;
	return true;
}
//will loop for the element or a nullptr
template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value){
	int curr = this->hashvalue(key);
	//search for the key and return if found otherwise loop the array or return false
	while (records_[curr]) {
		if (records_[curr]->key_ == key)
		{
			value = records_[curr]->data_;
			return true;
		}
		else {
			curr++;
		}
		if (curr == (this->capacity_)) {
			curr = 0;
		}
	}
	return false;
}
//copy assignment operator
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other){
	size_ = other.numRecords();
	maxExpected_ = other.maxExpected_;
	percentOpen_ = other.percentOpen_;
	capacity_ = other.capacity_;
	records_ = new Record*[other.capacity_];
	this->hashFunction = other.hashFunction;
	for (size_t i = 0; i < other.capacity_; i++)
	{
		if (other.records_[i])
			records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
		else
			records_[i] = nullptr;
	}
	return *this;
}
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other){
	*this = move(other);
	return *this;
}
template <class TYPE>
LPTable<TYPE>::~LPTable(){
	if (records_) {//2
		int sz = size_;//3
		for (int i = 0; i < sz; i++) {//4
			delete records_[i];
			//remove(records_[0]->key_);
		}//3n
		delete[] records_;//5
	}
}


