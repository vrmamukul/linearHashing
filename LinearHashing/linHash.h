#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<unordered_set>

using namespace std;

class BucketPage
{
	public:
		list<int>page;		
};


class linearHashing
{
	int next,level,pageSize,initialBuckets,nBuckets;
	vector<BucketPage*>hashTable;
	public:
		void createHashTable(int bucketSize,int nBuckets);
		void insertElement(int val);
		bool searchElement(int val);
		int getBucketIndex(int val,int level);
		void splitBucket(int bucketIndex);
		int twoPower(int p);
		void printHashTable();
		bool deleteElement(int val);
};