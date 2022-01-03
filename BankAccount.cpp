#include "BankAccount.h"
//Weston Cox
//CS132 Spring 2021
//Homework Assignment 4 - Bank Accounts
//05-14-2021

//This is the cpp file for the Bank Accounts class

//This should use polymorphism more. Everyone should inhereit ID and balance from BankAccount, for example.
//Pointers for polymorphism are handled in the main function
//ID should be private, balance should be protected

//Tried making functions virtual

#include "BankAccount.h"
#include <string>
#include <iostream>
using namespace std;

//*******************************************************************************************
//*							PARENT CLASS													*
//*******************************************************************************************
//CONSTRUCTORS
BankAccount::BankAccount()
{
	accountID = "";
	balance = 0;
	depositCount = 0;
	withdrawalCount = 0;
}
BankAccount::BankAccount(string inputID, double inputBalance)
{
	accountID = inputID;
	balance = inputBalance;
	depositCount = 0;
	withdrawalCount = 0;
	}

//METHODS
string BankAccount::getID()
{	
	//Grab accountID and return it
	return accountID;
}
void BankAccount::deposit(double depositAmount)
{
	//Add deposit to account balance
	balance += depositAmount;
	//Add to deposit count
	depositCount++;
}
void BankAccount::withdraw(double withdrawalAmount)					//Verify balance check
{
	//Withdraw funds IF the balance is sufficient
	if ((balance - withdrawalAmount > 0))
	{
		balance -= withdrawalAmount;
		withdrawalCount++;
	}
	else cout << "Insufficient balance for requested withdrawal";
}
void BankAccount::endOfMonth()
{
	//I'm not sure this one does anything at all. Virtual?
	
}
void BankAccount::endOfYear()
{
	//Same as end of Month
	
}
void BankAccount::printStatus()
{
	//Print account ID and balance
	string ID = getID();
	cout << "Account ID #" << ID << " has balance $" << balance;
}
bool BankAccount::operator<(const BankAccount rhs) const
{
	return this->accountID < rhs.accountID;
}


//***********************************************************************************
//*							SUB CLASSES												*
//***********************************************************************************

//*****************SIMPLE SAVINGS

	//CONSTRUCTOR
SimpleSavings::SimpleSavings() : BankAccount()
{
	yearlyFee = 0;
	monthlyInterest = 0;
}
SimpleSavings::SimpleSavings(string inputID, double inputBalance) : BankAccount(inputID, inputBalance)
{
	yearlyFee = 5.0;
	monthlyInterest = 0.005;
}

void SimpleSavings::endOfMonth()
{
	double interestPayment = monthlyInterest * balance;
	balance += interestPayment;
}

void SimpleSavings::endOfYear()
{
	withdraw(yearlyFee);
	depositCount = 0;
	withdrawalCount = 0;
}
void SimpleSavings::printStatus()
{
	BankAccount::printStatus();
	cout << endl;
}

//*********************ADVANCED SAVINGS

	//CONSTRUCTOR
AdvancedSavings::AdvancedSavings() : BankAccount()
{

	monthlyInterest = 0.0;
	yearlyFee = 0.0;
	withdrawPenalty = 0.0;
}
AdvancedSavings::AdvancedSavings(string inputID, double inputBalance) : BankAccount(inputID, inputBalance)
{
	
	monthlyInterest = 0.01;
	yearlyFee = 15.0;
	withdrawPenalty = 0.0;
}

void AdvancedSavings::endOfMonth()
{
	if (balance >= 10000) monthlyInterest = 0.02;
	else monthlyInterest = 0.01;
	double interestPayment = (monthlyInterest + 1) * balance;
	balance += interestPayment;
}
void AdvancedSavings::endOfYear()
{
	if (withdrawalCount == 0) yearlyFee = 15;
	else yearlyFee = 100;
	balance -= yearlyFee;
	depositCount = 0;
	withdrawalCount = 0;
}
void AdvancedSavings::withdraw(double withdrawalAmount)
{
	//Calculate Withdraw Penalty
	if (withdrawalCount == 0) withdrawPenalty = 0;
	else withdrawPenalty = 1.0 + static_cast<double>((10.0 * withdrawalCount));				//NEEDS A LOOK

	if ((balance - (withdrawalAmount + withdrawPenalty) > 0))
	{
		withdraw((withdrawalAmount + withdrawPenalty));
	}
	else cout << "Insufficient balance for requested withdrawal and penalty fee";
}

void AdvancedSavings::printStatus()
{
	BankAccount::printStatus();
	cout << " with " << withdrawalCount << " withdrawals this year.";
	cout << endl;
}


//**********************CHECKING ACCOUNT

//CONSTRUCTOR
CheckingAccount::CheckingAccount() : BankAccount()
{
	
	withdrawalCount = 0;
	depositCount = 0;
	yearlyFee = 0.0;

}

CheckingAccount::CheckingAccount(string inputID, double inputBalance) : BankAccount(inputID, inputBalance)
{
	withdrawalCount = 0;
	depositCount = 0;
	yearlyFee = 5.0;

}
void CheckingAccount::withdraw(double withdrawalAmount)
{
	if ((balance - withdrawalAmount > 0.0))
	{
		BankAccount::withdraw(withdrawalAmount);
	}
	else
	{
		balance -= (withdrawalAmount + 15);
		withdrawalCount++;
	}
}

void CheckingAccount::endOfMonth()
{
	BankAccount::endOfMonth();
}

void CheckingAccount::endOfYear()
{
	if (balance < 0)
	{
		double penalty = balance * 0.1;
		balance -= penalty;
	}
	balance -= (yearlyFee + (0.1 * withdrawalCount));
}

void CheckingAccount::printStatus()
{
	BankAccount::printStatus();
	cout << " with " << withdrawalCount << " withdrawals this year" << endl;
}


//*********************CREDIT ACCOUNT


	//CONSTRUCTOR
CreditAccount::CreditAccount() : BankAccount()
{
	
	withdrawalCount = 0;
	depositCount = 0;
	yearlyFee = 0.0;
	runningTotal = 0;
	lateMonths = 0;
	late = false;
	closed = false;
}
CreditAccount::CreditAccount(string inputID, double inputBalance) : BankAccount(inputID, inputBalance)
{
	withdrawalCount = 0;
	depositCount = 0;
	yearlyFee = 25.0;
	runningTotal = 0;
	lateMonths = 0;
	late = false;
	closed = false;
}


//METHODS
void CreditAccount::deposit(double depositAmount)			
{
	if ((balance + depositAmount) <= 0)			//Add the payment as long as there will still be debt on the account
	{
		balance += depositAmount;
		runningTotal += depositAmount;
	}
	else cout << "No adding money to a paid off account!" << endl;
}
void CreditAccount::withdraw(double withdrawalAmount)
{
	if (closed == false) 
	{
		balance -= withdrawalAmount;		
		withdrawalCount++;
	}
}
void CreditAccount::endOfMonth()
{
	//Check for account closure
	if (balance < 0 && runningTotal < 100.0)
	{
		late = true;						
		lateMonths++;
	}
	//Charge interest on debt
	if (balance <= 0)
	{
		balance += (balance * 0.05);		//Interest on debt
	}
	//Remove late status if payments were sufficient
	if (runningTotal >= 100)
	{
		late = false;
		lateMonths = 0;
	}
	//Reset monthly payment total
	runningTotal = 0;
}

	void CreditAccount::endOfYear()
	{
		//Check for closure
		if (lateMonths >= 2) closed = true;
		//Charge fee
		balance -= yearlyFee;
		//Reset late months
		lateMonths = 0;
	}
	void CreditAccount::printStatus()
	{
		string accountID = getID();
		cout << "Credit Account #" << accountID << " owes $" << -balance;
		if (lateMonths > 0) cout << " and is late " << lateMonths << " months.";
		if (closed == true) cout << " and is currently closed.";
		cout << endl;

	};

