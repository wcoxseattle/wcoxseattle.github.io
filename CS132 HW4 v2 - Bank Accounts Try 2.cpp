// CS132 - Polymorphism Practice
// Assignment #5
// BASE FILE
// Version 2.0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


// INCLUDE YOUR FILES  HERE
// You need to have the following classes defined
//   1 SimpleSavings
//   2 AdvancedSavings
//   3 CreditAccount
//   4 CheckingAccount
//   5 BankAccount

#include "BankAccount.h"
// #include "Any other files you have"


using namespace std;


vector<BankAccount*> openFile(string);
void printList(const vector<BankAccount*>&);
void sortList(vector<BankAccount*>&);
bool updateAccount(vector<BankAccount*>&);


int main()
{
	vector<BankAccount*> myList;
	myList = openFile("Data.txt");
	if (myList.size() < 1) return -99;

	sortList(myList);
	printList(myList);

	bool keepGoing;
	do
	{
		keepGoing = updateAccount(myList);
		cout << endl << endl << endl;
		cout << "***********************************" << endl
			<< "*  Current Status                 *" << endl
			<< "***********************************" << endl
			<< endl;
		printList(myList);
	} while (keepGoing);



}

/*
 * This is the method that allows for the user to
 * do input into the file as neccessary.
 * loops while the user types in numbers between 1 and 5
 * then does what the user requests
 * this allows for 1 iteration,  the loop is controlled in
 * the main program.
 */

bool updateAccount(vector<BankAccount*>& theList)
{
	int choice = 0;
	while (choice < 1 || choice > 5)
	{

		cout << "***************************************************************" << endl;
		cout << "* Data Entry - First Bank of CS132 - Please input your choice *" << endl;
		cout << "***************************************************************" << endl;
		cout << "What would you like to do?" << endl
			<< "  1. Deposit             :" << endl
			<< "  2. Withdraw            :" << endl
			<< "  3. Roll over the month :" << endl
			<< "  4. End the Year        :" << endl
			<< "  5. Quit                :" << endl;
		//cout << " >> ";
		//cin >> choice;
		while ((cout << " >>") && (!(cin >> choice) || choice < 1 || choice > 5))
		{
			cout << "That's not a number between 1 and 5; ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	}
	// Choice 5 = I QUIT
	if (choice == 5)  return false;

	// Choice 4 = run endOfYear on all elements.
	if (choice == 4)
	{
		for (BankAccount* x : theList)
		{
			x->endOfYear();
		}
		return true;
	}

	// Choice 3 = run endOfMonth on all elements.
	if (choice == 3)
	{
		for (BankAccount* x : theList)
		{
			x->endOfMonth();
		}
		return true;
	}

	// Choice 2 = run withdraw
	if (choice == 2)
	{
		string acc;
		double amount;

		cout << "Which account? - > ";
		cin >> acc;
		cout << "How Much?      - > ";
		cin >> amount;

		for (BankAccount* x : theList)
		{
			if (x->getID() == acc)
			{
				x->withdraw(amount);
				return true;
			}
		}
		cout << "Account not found" << endl;
		return true;
	}

	// Choice 1 = run deposit
	if (choice == 1)
	{
		string acc;
		double amount;

		cout << "Which account? - > ";
		cin >> acc;
		cout << "How Much?      - > ";
		cin >> amount;

		for (BankAccount* x : theList)
		{
			if (x->getID() == acc)
			{
				x->deposit(amount);
				return true;
			}
		}
		cout << "Account not found" << endl;
		return true;
	}

	return false;
}

/*
 * sortList method to sort the data in the List by the
 * account name.  The comparePtr is a submethod
 * that allows the sort method to use the user defined
 * < operator.
 * this will not work if the neccessary < operator doesn't
 * work;
 */
bool comparePtr(BankAccount* a, BankAccount* b) { return (*a < *b); }
void sortList(vector<BankAccount*>& L)
{

	sort(L.begin(), L.end(), comparePtr);
}


/*
 * printList method to print the Vector of data in order.
 */
void printList(const vector<BankAccount*>& L)
{
	for (BankAccount* x : L)
	{
		x->printStatus();
	}
}

/*
 * This method opens up the provided file and reads
 * the data line by line creating the neccessary classes
 * as they are developed.
 * REQUIRES
 *   SimpleSavings
 *   AdvancedSavings
 *   CreditAccount
 *   CheckingAccount
 */
vector<BankAccount*> openFile(string fname)
{
	BankAccount* tmp;
	vector<BankAccount*> theList;

	ifstream dataFile(fname);
	if (!dataFile.is_open())
	{
		cerr << "ERROR OPENING FILE, PLEASE TRY AGAIN";
		return theList;
	}

	string type, ID;
	double z;
	while (dataFile >> type)
	{


		dataFile >> ID >> z;

		if (type == "Simple")   tmp = new SimpleSavings(ID, z);
		if (type == "Advanced") tmp = new AdvancedSavings(ID, z);
		if (type == "Credit")   tmp = new CreditAccount(ID, z);
		if (type == "Checking") tmp = new CheckingAccount(ID, z);
		theList.push_back(tmp);
	}

	return theList;
}

