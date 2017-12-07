#include <cstdlib>
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

struct node
{
	product item;
	node* left;
	node* right;
};

class dStack {
private:
	int size;
	int top;
	node** list;

public:
	dStack(int = 100);
	~dStack();
	void push(node*);
	node* pop();
	bool isEmpty();
};

dStack::dStack(int a) {
	list = new node*[a];
	size = a;
	top = -1; //-1 indicates empty stack
}

dStack::~dStack() {
	delete[] list;
}

void dStack::push(node* a) {
	if (top == size) {
		return;
	} else {
			top++;
			list[top] = a;
	}
}
node* dStack::pop() {
	if (top == -1) {
		return 0;
	} else {
		node* a = list[top];
		top--;
		return a;
	}
}

bool dStack::isEmpty() {
	if (top == -1)
		return 1;
	else
		return 0;
}


void loadStock(product* a, int &b, string c); //opens a product list and fills array with content
void outputStock(product* list, int& listSize);
product* addArray(product* list1, int& listSize1, product* list2, int& listSize2, int& listSize3); //adds list 2 onto list 1
void sortPrice(product* list, int start, int end);
void sortName(product* list, int start, int end);
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
			largeList = addArray(officeChairs, chairSize, officeTable, tableSize, largeListSize);
			largeList = addArray(largeList, largeListSize, officeTable, tableSize, largeListSize);
			sortPrice(largeList, 0, largeListSize-1);
			featuredSearch(largeList, largeListSize, cart, cartSize);
			delete [] largeList; //empty the memory
			largeListSize = 0;
			break;
		case 7:
			checkout(cart, cartSize);
			cartSize = 0;
			break;
		default: continue;
		}
	}
	cout << "Have a Nice Day";
	cin.ignore();
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

void outputCart(product* list, int& listSize){
	for(int i = 0; i < listSize; i++){
		cout << "\n____________________________________________________________\n";
		cout << "Product " << i + 1;
		cout << "\nName: " << list[i].name;
		cout << "\nPrice: " << fixed << setprecision(2) << list[i].price;
	}
	cout << "\n____________________________________________________________\n";
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

void swapName (product &first, product &second) //helper function to swap values in array
{                                   //can change int to class Item or whatever type is needed
	product start = first;
    first = second;
    second = start;
}

int partitionName (product * arr, int low, int high) //arr[] is sorted array, low is start index, and high is end index
{
    product pivot = arr[high];  //set pivot as high element
    int index = (low - 1);          //set index to start at lower element

    for (int i = low; i <= high - 1; i++)
    {
        if (arr[i].name <= pivot.name)            //if element is smaller than pivot
        {
            index++;                    //increment index
            swapName(arr[index], arr[i]);
        }
    }
    swapName(arr[index + 1], arr[high]);
    return (index + 1);
}

void sortName(product* list, int start, int end){
	if (start < end)                     //if unsorted array
    {
        int partitionIndex = partitionName(list, start, end);

        sortName(list, start, end - 1);
        sortName(list, partitionIndex + 1, end);
    }
}

void swapPrice (product* list, int first, int second) //helper function to swap values in array
{                                   //can change int to class Item or whatever type is needed
	product start = list[first];
    list[first] = list[second];
    list[second] = start;
}

int partitionPrice (product* arr, int low, int high) //arr[] is sorted array, low is start index, and high is end index
{
	product pivot = arr[high];  //set pivot as high element
    int index = (low - 1);          //set index to start at lower element

    for (int i = low; i <= high - 1; i++)
    {
        if (arr[i].price <= pivot.price)            //if element is smaller than pivot
        {
            index++;                    //increment index
            swapPrice(arr, index, i);
        }
    }
    swapPrice(arr, index+1, high);
    return (index + 1);
}

void sortPrice(product* list, int start, int end){
	if (start < end)                     //if unsorted array
    {
        int partitionIndex = partitionPrice(list, start, end);
        sortPrice(list, start, end - 1);
        sortPrice(list, partitionIndex + 1, end);
    }
}

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
		cout << "\nWhat Product are you interested in\n1. Office Chairs\n2. Office Tables\n3. Office Shelves\n4. Exit selection\nSelect the Chosen selection to deselect\n";
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

node* insert(product a)//creates instance of a node
{
	node* prdt = new node;
	prdt->item = a;
	prdt->left = NULL;
	prdt->right = NULL;

	return prdt;
}

node* arrToBST(product* list, int begin, int end)//creates BST similar to a binary search (O)n since it must make a tree with all new nodes
{
	if(begin > end) return NULL;
	int mid = (begin + end)/2;
	node* root = insert(list[mid]);
	root->left = arrToBST(list, begin, mid-1);
	root->right = arrToBST(list, mid+1, end);
	return root;
}

void removeStock(node* index, product* list, int begin, int end)//implements binary search
{
	while(begin <= end)
	{
		int mid = (begin + end) / 2;
		if(list[mid].price == index->item.price){
			list[mid].stock--;
			return;
		}

		if(list[mid].price < index->item.price){
			begin = mid + 1;
		}

		else end = mid - 1;
	}

	return;
}

void featuredSearch(product* list, int& listSize, product* cart, int& cartSize){
	node* head; //create the BST
	head = arrToBST(list, 0, listSize-1);
	int choice = 0;
	node* index = head; //itterator
	dStack indexStack(100); //indexes paths not chosen
	while(choice != 4){
		system("CLS");
		cout << "____________________________________________________________\n";
		cout << "\nName: " << index->item.name;
		cout << "\nPrice: " << fixed << setprecision(2) << index->item.price;
		cout << "\nIn Stock: " << index->item.stock << endl;
		cout << "____________________________________________________________\n";
		cout << "Are you:\n1. Interested in buying the product, or are you looking for\n2. Budget Friendly\n3. Quality\n4. Exit\n";
		cin >> choice;
		cin.ignore(1000,10);
		switch(choice){
			case 1:
				if(index->item.stock == 0){
					cout << "\n\nSorry Out of Stock, press enter to continue";
					cin.ignore();
				}
				else{
					cart[cartSize] = index->item;
					cartSize++;
					index->item.stock--;
					removeStock(index, list, 0, listSize);
				}
				break;
			case 2:
				if(index->right != NULL) indexStack.push(index->right); //possibly pushes unchosen path if it exists
				if(index->left != NULL) index = index->left; //if left child exist thats cheaper, go to it
				else if(indexStack.isEmpty()) choice = 4; //you traversed the entire tree, exit loop
				else index = indexStack.pop();
				break;
			case 3:
				if(index->left != NULL) indexStack.push(index->left); //possibly pushes unchosen path if it exists
				if(index->right != NULL) index = index->right; //if left child exist thats cheaper, go to it
				else if(indexStack.isEmpty()) choice = 4; //you traversed the entire tree, exit loop
				else index = indexStack.pop();
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
	outputCart(list, listSize);
	cout << "\n\n The total is " << cost << endl << endl;
	cout << "Press enter to continue";
	cin.ignore();

}

void shopping(product* list, int& listSize, product* cart, int& cartSize){
	int choice = 0;
	int purchase = 1;
	product temp; //what you might buy

	while(choice < 1 || choice > 3){
		system("CLS");
		cout << "Sort by: \n1. Price\n2. Name\n3. Exit Section\n";
		cin >> choice;
		cin.ignore(1000,10);
	}

	//sort list here
	if(choice == 1) sortPrice(list, 0, listSize-1);// sort by Price
	else if(choice == 2) sortName(list, 0, listSize-1); // sort by Name

	if(choice != 3){
		while(purchase != 0){
			system("CLS");
			outputStock(list, listSize);
			cout << "What would you like to buy? (enter 0 to exit to store front)\n";
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
