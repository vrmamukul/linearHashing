#include "linHash.h"
using namespace std;

int main(){
	
	int choice;
	linearHashing *d=NULL;
	do{
		cout<<"1. Create new ExtendibleHashTable"<<endl;
		cout<<"2. Add an element to the HashTable"<<endl;
		cout<<"4. Search an element to the HashTable"<<endl;
		// cout<<"4. Delete an element from the HashTable"<<endl;
		cout<<"5. Print HashTable"<<endl;

		cout<<"Any other choice to exit"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cout<<"You entered "<<choice<<endl;
		switch(choice){
			case 1:
				if(d!=NULL)
					delete d;
				d= new linearHashing();
				int level;
				cout<<"Enter initial number of Buckets: ";
				cin>>level;
				int bucketSize;
				cout<<"Enter number of entries in bucket: ";
				cin>>bucketSize;
				d->createHashTable(bucketSize,level);
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
					cout<<"\n\nElement is found\n\n"<<endl;
					
				else
					cout<<"\n\nElement is not found\n\n"<<endl;
					
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