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
product* addArray(product* list1, int& listSize1, product* list2, int& listSize2, int& listSize3); //adds list 2 onto list 1
void sortPrice(product* list, int& listSize);
void sortName(product* list, int& listSize);
void specificSearch(product* list1, int& listSize1, product* list2, int& listSize2, product* list3, int& listSize3, product* cart, int& cartSize);
void featuredSearch(product* list, int& listSize, product* cart, int& cartSize);
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
			largeList = addArray(officeChairs, chairSize, officeTable, tableSize, largeListSize);
			largeList = addArray(largeList, largeListSize, officeTable, tableSize, largeListSize);
			shopping(largeList, largeListSize, cart, cartSize);
			delete [] largeList; //empty the memory
			largeListSize = 0;
			break;
		case 5:
			specificSearch(officeChairs, chairSize, officeTable, tableSize, officeShelves, shelfSize, cart, cartSize);
			break;
		case 6:
			//TODO featured product search
			largeList = addArray(officeChairs, chairSize, officeTable, tableSize, largeListSize);
			largeList = addArray(largeList, largeListSize, officeTable, tableSize, largeListSize);
			//insert quick sort
			featuredSearch(largeList, largeListSize, cart, cartSize);
			delete [] largeList; //empty the memory
			largeListSize = 0;
			break;

		case 7:
			checkout(cart, cartSize);
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

product* addArray(product* list1, int& listSize1, product* list2, int& listSize2, int& listSize3){
	product* temp = new product[listSize1 + listSize2];
	for(int i = 0; i < listSize1; i++){//add list 1
		temp[i] = list1[i];
	}

	for(int i = 0; i < listSize2; i++){//add list 2
		temp[listSize1+i] = list2[i];
	}

	listSize3 = listSize1 + listSize2;
	return temp;
}

void sortPrice(product* list, int& listSize){}

void sortName(product* list, int& listSize){}

void specificSearch(product* list1, int& listSize1, product* list2, int& listSize2, product* list3, int& listSize3, product* cart, int& cartSize)
{
	bool l1 = 0, l2 =  0, l3 = 0;
	int choice = 0;
	while(choice != 4){
		system("CLS");
		printf("Current Categories selected:");
		if(l1) printf(" Office Chairs");
		if(l2) printf(" Office Tables");
		if(l3) printf( " Office Shelves");
		if(l1 == 0 && l2 == 0 && l3 == 0) printf(" none");
		cout << "\nWhat Product are you interested in\n1. Office Chairs\n2. Office Tables\n3. Office Shelves\n4. Exit selection\nSelect the Chosen selection to deselect";
		cin >> choice;
		cin.ignore(1000,10);
		if(choice == 1) l1 = l1 ^ 1;
		if(choice == 2) l2 = l2 ^ 1;
		if(choice == 3) l3 = l3 ^ 1;
	}

	product* largeList;
	int largeListSize = 0;

	if(l1 == 0 && l2 == 0 && l3 == 0) return;//none were selected, return
	else if(l1 == 1 && l2 == 0 && l3 == 0){
		shopping(list1, listSize1, cart, cartSize);
	}
	else if(l1 == 0 && l2 == 1  && l3 == 0){
		shopping(list2, listSize2, cart, cartSize);
	}
	else if(l1 == 0 && l2 == 0 && l3 == 1){
		shopping(list3, listSize3, cart, cartSize);
	}
	else if(l1 == 1 && l2 == 1 && l3 == 0){
		largeList = addArray(list1, listSize1, list2, listSize2, largeListSize);
	}
	else if(l1 == 1 && l2 == 0 && l3 == 1){
		largeList = addArray(list1, listSize1, list3, listSize3, largeListSize);
	}
	else if(l1 == 0 && l2 == 1 && l3 == 1){
		largeList = addArray(list3, listSize3, list2, listSize2, largeListSize);
	}
	else{
		largeList = addArray(list1, listSize1, list2, listSize2, largeListSize);
		largeList = addArray(largeList, largeListSize, list3, listSize3, largeListSize);
	}

	shopping(largeList, largeListSize, cart, cartSize);
	delete [] largeList;
}

void featuredSearch(product* list, int& listSize, product* cart, int& cartSize){
		int choice = 0;
		int index = (listSize - 1) / 2;
		int begin = 0;
		int end = listSize - 1;
		while(choice != 4){
			system("CLS");
			cout << "____________________________________________________________\n";
			cout << "\nName: " << list[index].name;
			cout << "\nPrice: " << fixed << setprecision(2) << list[index].price;
			cout << "\nIn Stock: " << list[index].stock << endl;
			cout << "____________________________________________________________\n";
			cout << "Are you:\n1. Interested in buying the product, or are you looking for\n2. Budget Friendly\n3. Quality\n4. Exit";
			cin >> choice;
			cin.ignore(1000,10);
			switch(choice){
			case 1:
				if(list[index].stock == 0){
					cout << "\n\nSorry Out of Stock, press enter to continue";
					cin.ignore();
				}
				else{
					cart[cartSize] = list[index];
					cartSize++;
					list[index].stock--;
				}
				break;
			case 2:
				end = index-1;
				index = (end + begin) / 2;
				break;
			case 3:
				begin = index+1;
				index = (end + begin) / 2;
				break;
			case 4:
				return;
			default: continue;
			}
		}
}

void checkout(product* list, int& listSize)
{
	double cost = 0;
	for(int i = 0; i < listSize; i++){
		cost += list[i].price;
	}
	system("CLS");
	cout << "Products in cart:\n\n";
	outputStock(list, listSize);
	cout << "\n\n The total is " << cost << endl << endl;

}

void shopping(product* list, int& listSize, product* cart, int& cartSize){
	int choice = 0;
	int purchase = 1;
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
