#include <cstdlib>
#include "dStack.h" //for featured look
#include <fstream>
#include <iomanip> //setprecision
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct product{
	string name;
	double price;
	int stock;
};

void loadStock(product* a, int &b, string c); //opens a product list and fills array with content
void outputStock(product* list, int& listSize);
void addArray(product* list1, int& listSize1, product* list2, int& listSize2); //adds list 2 onto list 1
void sortPrice(product* list, int& listSize);
void sortName(product* list, int& listSize);
void specificSearch(product* largeList, int& largeListsize, product* list1, int& listSize1, product* list2, int& listSize2, product* list3, int& listSize3);
void checkout(product* list, int& listSize);
void shopping(product* list, int& listSize, product* cart, int& cartSize);

int main() {
	//initializing product list
	product officeChairs[50];
	int chairSize = 0;
	product officeTable[50];
	int tableSize = 0;
	product officeShelves[50];
	int shelfSize = 0;
	//end product list

	//variables for main program
	int choice = 0;
	product cart[100]; //shopping cart
	int cartSize = 0;
	product* largeList;
	int largeListSize = 0;

	//start initializing array of products
	loadStock(officeChairs, chairSize, "chairlist.txt");
	loadStock(officeTable, tableSize, "tablelist.txt");
	loadStock(officeShelves, shelfSize, "bookcaselist.txt");

	//main program
	while(choice != 8){
		system("CLS");
		cout << "____________________________________________________________";
		cout << "\nWhat would you like to purchase?\n\n";
		cout << "1. Office Chairs\n2. Office Tables\n3. Office Bookcases\n4. All Products\n5. Specific Search\n6. Featured Products\n7. Checkout\n8. Exit Store\n";
		cin >> choice;
		cin.ignore(1000,10);

		switch(choice){
		case 1:
			shopping(officeChairs, chairSize, cart, cartSize);
			break;
		case 2:
			shopping(officeTable, tableSize, cart, cartSize);
			break;
		case 3:
			shopping(officeShelves, shelfSize, cart, cartSize);
			break;
		case 4:
			addArray(largeList, largeListSize, officeChairs, chairSize);
			addArray(largeList, largeListSize, officeTable, tableSize);
			addArray(largeList, largeListSize, officeShelves, shelfSize);
			shopping(largeList, largeListSize, cart, cartSize);
			delete [] largeList; //empty the memory
			largeListSize = 0;
			break;
		case 5:
			//TODO specific search
			specificSearch(largeList, largeListSize, officeChairs, chairSize, officeTable, tableSize, officeShelves, shelfSize);
			shopping(largeList, largeListSize, cart, cartSize);
			delete [] largeList; //empty the memory
			largeListSize = 0;
			break;
		case 6:
			//TODO featured product search
		case 7:
			checkout(cart, cartSize); //TODO
			break;
		case 8:
		default: continue;
		}
	}
	cout << "Have a Nice Day";
	return 0;
}

void loadStock(product* a, int &b, string c){
	ifstream text;
	string line;
	product temp;
	text.open(c.c_str());
	if(!text){
		cout << "File not opened";
	}
	else{//parse file
		while(1){
			getline(text, line);
			if(line == "ListStart") continue;
			else if(line == "ListEnd") break;
			else{
				temp.name = line;
				getline(text, line);
				temp.price = atof(line.c_str());
				getline(text, line);
				temp.stock = atoi(line.c_str());
				a[b] = temp;
				b++;
			}
		}
	}
	text.close();
}

void outputStock(product* list, int& listSize){
	for(int i = 0; i < listSize; i++){
		cout << "____________________________________________________________\n";
		cout << "Product " << i + 1;
		cout << "\nName: " << list[i].name;
		cout << "\nPrice: " << fixed << setprecision(2) << list[i].price;
		cout << "\nIn Stock: " << list[i].stock << endl;
	}
	cout << "____________________________________________________________\n";
}

void addArray(product* list1, int& listSize1, product* list2, int& listSize2){
	product* temp = new product[listSize1 + listSize2];
	product* del = list1;
	for(int i = 0; i < listSize1; i++){//add list 1
		temp[i] = list1[i];
	}
	for(int i = 0; i < listSize2; i++){//add list 2
		temp[listSize1+i] = list2[i];
	}
	list1 = temp;
	delete [] del;
}

void sortPrice(product* list, int& listSize){}

void sortName(product* list, int& listSize){}

void specificSearch(product* largeList, int& largeListsize, product* list1, int& listSize1, product* list2, int& listSize2, product* list3, int& listSize3){}

void checkout(product* list, int& listSize){}

void shopping(product* list, int& listSize, product* cart, int& cartSize){
	int choice = 0;
	int purchase = 1;
	int dummy = 0; //press enter to continue
	product temp; //what you might buy

	while(choice < 1 || choice > 3){
		system("CLS");
		cout << "Sort by: 1. Price\n2. Name\n3. Exit Section\n";
		cin >> choice;
		cin.ignore(1000,10);
	}

	//sort list here
	if(choice == 1) sortPrice(list, listSize);// sort by Price
	else if(choice == 2) sortName(list, listSize); // sort by Name

	if(choice != 3){
		while(purchase != 0){
			system("CLS");
			outputStock(list, listSize);
			cout << "What would you like to buy? (enter 0 to exit to store front)";
			cin >> purchase;
			cin.ignore(1000,10);
			if(purchase == 0) break;
			if(purchase > 0 && purchase  < listSize + 1){
				if(purchase-1 < listSize){
					if(list[purchase-1].stock == 0){
						cout << "\n\nSorry Out of Stock, press enter to continue";
						cin.ignore();
					}
					else{
						cart[cartSize] = list[purchase-1];
						cartSize++;
						list[purchase-1].stock--;
					}
				}
			}

		}
	}
}
