//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3

#ifndef SAVINGSACCOUNTH
#define SAVINGSACCOUNTH

#include "BankAccount.h"

class SavingsAccount : public BankAccount {
public:
	//Constructors
	SavingsAccount();

	//Accessors
	virtual double maxBorrowable() const;
	double getMinimumBalance() const;

	//Mutators
	virtual ostream& putAccountDetailsInStream(ostream& os) const = 0;
	virtual istream& getAccountDataFromStream(istream& is) = 0;

	virtual const string prepareFormattedAccountDetails() const = 0;
	//Data Members
private:
	//Data Members
	double minimumBalance;
	//Functions

};

#endif // !SAVINGSACCOUNTH
