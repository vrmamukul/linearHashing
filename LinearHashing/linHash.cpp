#include "linHash.h"

void linearHashing::createHashTable(int pageSize,int nBuckets){
	this->nBuckets = nBuckets;
	this->initialBuckets = nBuckets;
	this->pageSize = pageSize;
	this->level = 0;
	this->next = 0;
	cout<<"YOOO\n"<<nBuckets<<" "<<pageSize<<endl;
	this->hashTable.resize(this->nBuckets);
	
	for (int i = 0; i < this->nBuckets; ++i)
	{
		this->hashTable[i] = new BucketPage();
		// cout<<"yeyy"<<endl;
	}
}



void linearHashing::insertElement(int val){
	// printf("yooooo\n");
	int bucketIndex = this->getBucketIndex(val,this->level);
	if(bucketIndex < this->next){
		bucketIndex = this->getBucketIndex(val,this->level+1);
	}
	if(this->hashTable[bucketIndex]->page.size()%this->pageSize == 0 && this->hashTable[bucketIndex]->page.size()>0){
		splitBucket(this->next);
		this->next = (this->next+1)%((twoPower(this->level))*(this->initialBuckets));
		if(this->next==0)
			this->level++;
	}	
	bucketIndex = this->getBucketIndex(val,this->level);
	if(bucketIndex < this->next){
		bucketIndex = this->getBucketIndex(val,this->level+1);
	}
	this->hashTable[bucketIndex]->page.push_back(val);
}



void linearHashing::splitBucket(int bucketIndex){
	this->hashTable.resize(this->nBuckets+1);
	this->nBuckets +=1;
	this->hashTable[nBuckets-1] = new BucketPage();

	list<int>&originalBucket = this->hashTable[bucketIndex]->page;

	for(auto itr = originalBucket.begin(); itr!=originalBucket.end();){
		int bucket = getBucketIndex(*itr,this->level+1);
		if(bucket!=bucketIndex){
			this->hashTable[bucket]->page.push_back(*itr);
			itr = originalBucket.erase(itr);
		}
		else{
			itr++;
		}
	}
}


bool linearHashing::searchElement(int val){
	int bucketIndex = this->getBucketIndex(val,this->level);
	if(bucketIndex < this->next) bucketIndex = this->getBucketIndex(val,this->level+1);
	for(auto itr = this->hashTable[bucketIndex]->page.begin(); itr!=this->hashTable[bucketIndex]->page.end(); itr++)
		if(*itr==val)
			return true;
	
	return false;
}


int linearHashing::getBucketIndex(int val,int level){
	return val % (this->initialBuckets*twoPower(level));  

}


int linearHashing::twoPower(int p){
	return 1<<p;
}


void linearHashing::printHashTable(){
	cout<<"\n ***** Hash Table ***** \n"<<endl;
	cout<<"Level: "<<this->level<<endl;
	unordered_set<BucketPage*> uset;
	cout<<"Next bucket to split : "<<this->next<<endl;
	cout<<"Bucket_No  "<<" 		::| Elements |"<<endl;
	for(int i=0; i<this->hashTable.size(); i++){
		if(uset.find(this->hashTable[i])!=uset.end())
			continue;
		cout<<i<<" 			"<<" 		:: | ";
		uset.insert(this->hashTable[i]);
		for(auto l:this->hashTable[i]->page)
			cout<<l<<" ";
		cout<<"|" <<endl;
	}
	cout<<endl;
}

bool linearHashing::deleteElement(int val){
	int bucketIndex = this->getBucketIndex(val,this->level);
	if(bucketIndex < this->next) bucketIndex = this->getBucketIndex(val,this->level+1);
	for(auto itr = this->hashTable[bucketIndex]->page.begin(); itr!=this->hashTable[bucketIndex]->page.end(); itr++){
		if(*itr==val){
			this->hashTable[bucketIndex]->page.erase(itr);
			return true;
		}
	}
	return false;
}