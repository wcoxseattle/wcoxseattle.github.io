

//Weston Cox
//CS132 Spring 2021
//Homework Assignment 4

//This is the header file for the BankAccount class. It contains constructors and methods for Bank Account, and several child classes (savings, checking etc.)
//All of the child classes inherit some parts from the parent BankAccount class. Each child class tacks on some extra information or special rules


#pragma once
#include <string>
using namespace std;

class BankAccount
{
private:
	string accountID;
protected:					
	double balance;
	int withdrawalCount;
	int depositCount;

public:
	//*****CONSTRUCTORS***************************
	BankAccount();
	BankAccount(string, double);

	//*******METHODS*****************************
	//GETTERS / ACCESSOR FUNCTIONS
	string getID();

	//SETTERS / MUTATOR FUNCTIONS
	void deposit(double);
	void withdraw(double);

	//OTHERS
	virtual void endOfMonth();
	virtual void endOfYear();
	virtual void printStatus();
	bool operator<(const BankAccount) const;		
};


//***********************************************************************
//*							SUB CLASSES									*
//***********************************************************************

class SimpleSavings : public BankAccount
{
	//VARIABLES
protected:
	double monthlyInterest;
	double yearlyFee;

public:
	//CONSTRUCTORS
	SimpleSavings();
	SimpleSavings(string, double);

	//METHODS
	void endOfMonth();
	void endOfYear();
	void printStatus();

};



class AdvancedSavings : public BankAccount
{
protected:
	double monthlyInterest;
	double yearlyFee;
	double withdrawPenalty;

public:
	//CONSTRUCTORS
	AdvancedSavings();
	AdvancedSavings(string, double);

	//METHODS
	virtual void endOfMonth();
	virtual void endOfYear();
	void printStatus();
	void withdraw(double);
};

class CheckingAccount : public BankAccount
{
protected:
	double yearlyFee;

public:
	//CONSTRUCTORS
	CheckingAccount();
	CheckingAccount(string, double);

	//METHODS
	void withdraw(double);
	void endOfMonth();
	void endOfYear();
	void printStatus();
};

class CreditAccount : public BankAccount
{
protected:
	double yearlyFee;
	int lateMonths;
	double runningTotal;
	bool late;
	bool closed;

public:
	//CONSTRUCTORS
	CreditAccount();
	CreditAccount(string, double);

	//METHODS
	void deposit(double);
	void withdraw(double);
	void endOfMonth();
	void endOfYear();
	void printStatus();
};


