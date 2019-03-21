#include<bits/stdc++.h>

using namespace std;

class Bucket{
public:
	// int localDepth;
	list<int> bucket;
};

class LinearHashing{
	int level,bucketSize,next,noOfBuckets;
	vector<Bucket*> dir;
public:
	void createHashTable(int, int);
	void insertElement(int val);
	bool searchElement(int val);
	bool deleteElement(int val);
	int getBucketIndex(int val);
	// void doubleHashTable();
	void splitBucket(int bucketIndex);
	int twoPower(int p);
	void printHashTable();
    int getCloset2Power(int val);
    void increaseBuckets();
};

int LinearHashing::twoPower(int p){
	return 1<<p;
}

int LinearHashing::getCloset2Power(int val){
    int i=1;
	for(i=0;i<32;i++){
        if(val < 1<<i){
            break;
        }
    }
    i--;
    return 1<<i;
}

void LinearHashing::createHashTable(int noOfBuckets, int bucketSize){
	// int buckets = twoPower(globalDepth);
	this->noOfBuckets = noOfBuckets;
	this->dir.resize(noOfBuckets);
	this->bucketSize=bucketSize;
    this->level=0;
    // int closet2Power = this->getCloset2Power(noOfBuckets);
    // this->next=noOfBuckets%closet2Power;
    this->next=0;
	for(int i=0;i<noOfBuckets;i++){
		this->dir[i] = new Bucket();
	}
}

int LinearHashing::getBucketIndex(int val){
	// int lsbOfOnes = twoPower(this->globalDepth)-1;
	// return val & lsbOfOnes;  
    if(val%(this->twoPower(this->level)*this->noOfBuckets) >= this->next){
        return val%(this->twoPower(this->level)*this->noOfBuckets);
    }
    else{
        return val%(2*(this->noOfBuckets)*(this->twoPower(this->level)));
    }
}

void LinearHashing::insertElement(int val){
	int bucketIndex = this->getBucketIndex(val);
	if((this->dir[bucketIndex]->bucket.size())%(this->bucketSize) == 0 && this->dir[bucketIndex]->bucket.size()>0){
        // if(bucketIndex==this->next){
            this->increaseBuckets();
            this->splitBucket(this->next);
        // }
        // else{
        //     this->increaseBuckets();
        // }
    }
    int newIndex = this->getBucketIndex(val);
    this->dir[newIndex]->bucket.push_back(val);
}

bool LinearHashing::searchElement(int val){
	int bucketIndex = this->getBucketIndex(val);
	cout<<bucketIndex<<endl;
	for(auto itr = this->dir[bucketIndex]->bucket.begin(); itr!=this->dir[bucketIndex]->bucket.end(); itr++)
		if(*itr==val)
			return true;
	return false;
}

bool LinearHashing::deleteElement(int val){
	int bucketIndex = this->getBucketIndex(val);
	for(auto itr = this->dir[bucketIndex]->bucket.begin(); itr!=this->dir[bucketIndex]->bucket.end(); itr++){
		if(*itr==val){
			this->dir[bucketIndex]->bucket.erase(itr);
			return true;
		}
	}
	return false;
}
// void LinearHashing::doubleHashTable(){
// 	int size = this->dir.size();
// 	this->globalDepth++;
// 	this->dir.resize(2*size);
// 	for(int i=size;i<2*size;i++)
// 		this->dir[i]=this->dir[i-size];
// }

void LinearHashing::increaseBuckets(){
    int size = this->dir.size();
    this->dir.resize(size+1);
    this->dir[size]=new Bucket();
}

void LinearHashing::splitBucket(int bucketIndex){
	// int localDepthPower = twoPower(this->dir[bucketIndex]->localDepth);
	// int firstBucketIndex = bucketIndex & (localDepthPower-1);
	// int secondBucketIndex = firstBucketIndex + localDepthPower;
	/*creating new bucket and updating local depths*/
	// this->dir[secondBucketIndex] = new  Bucket();
	// this->dir[secondBucketIndex]->localDepth = ++this->dir[firstBucketIndex]->localDepth;
	
	list<int> &firstBucket = this->dir[bucketIndex]->bucket;
	list<int> &secondBucket = this->dir[this->dir.size()-1]->bucket;
	/*distributing values to two buckets*/
	for(auto itr=firstBucket.begin();itr!=firstBucket.end();){
		int bIndex=(*itr)%(2*this->twoPower(this->level)*this->noOfBuckets);
		cout<<bIndex<<" "<<*itr<<endl;
		if(bIndex == this->dir.size()-1){
			secondBucket.push_back(*itr);
			itr = firstBucket.erase(itr);
		}
		else itr++;
	}
	this->next = (this->next+1)%((twoPower(level))*(this->noOfBuckets));
    if(this->next == 0){
        this->level++;
    }
	/*pointing to proper buckets after spliting*/
	// localDepthPower = 2*localDepthPower;
	// for(int i=secondBucketIndex+localDepthPower; i < this->dir.size(); i=i+localDepthPower)
	// 	this->dir[i] = this->dir[secondBucketIndex];
}

void LinearHashing::printHashTable(){
	cout<<"\n ***** Hash Table ***** \n"<<endl;
	cout<<"noOfBuckets :: " << this->noOfBuckets<<endl;
	cout<<"level :: " << this->level<<endl;
	cout<<"next pointer :: " << this->next<<endl;
	unordered_set<Bucket*> uset;
	cout<<"| Elements |"<<endl;
	for(int i=0; i<this->dir.size(); i++){
		if(uset.find(this->dir[i])!=uset.end())
			continue;
		// cout<<this->dir[i]->localDepth<<" :: | ";
		uset.insert(this->dir[i]);
		for(auto l:this->dir[i]->bucket)
			cout<<" | "<<l<<" ";
		cout<<"|" <<endl;
	}
	cout<<endl;
}


int main(){
	
	int choice;
	LinearHashing *d=NULL;
	do{
		cout<<"1. Create new ExtendibleHashTable"<<endl;
		cout<<"2. Add an element to the HashTable"<<endl;
		cout<<"3. Search an element to the HashTable"<<endl;
		cout<<"4. Delete an element from the HashTable"<<endl;
		cout<<"5. Print HashTable"<<endl;

		cout<<"Any other choice to exit"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cout<<"You entered "<<choice<<endl;
		switch(choice){
			case 1:
				if(d!=NULL)
					delete d;
				d= new LinearHashing();
				int globalDepth;
				cout<<"Enter global depth: ";
				cin>>globalDepth;
				int bucketSize;
				cout<<"Enter number of entries in bucket: ";
				cin>>bucketSize;
				d->createHashTable(globalDepth,bucketSize);
				break;
			case 2:
				int add;
				cout<<"Enter element to add: ";
				cin>>add;
				d->insertElement(add);
				break;
			case 3:
				int search;
				cout<<"Enter element to search: ";
				cin>>search;
				if(d->searchElement(search))
					cout<<"Element is found"<<endl;
				else
					cout<<"Element is not found"<<endl;
				break;
			case 4:
				int del;
				cout<<"Enter element to delete: ";
				cin>>del;
				if(d->deleteElement(del))
					cout<<"Element is deleted"<<endl;
				else
					cout<<"Element is not found"<<endl;
				break;
			case 5:
				d->printHashTable();
				break;
			default:
				return 0;
		}
	}while(true);
}