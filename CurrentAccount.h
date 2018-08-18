//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3


#ifndef CURRENTACCOUNTH
#define CURRENTACCOUNTH

#include "BankAccount.h"

class CurrentAccount : public BankAccount {
public:
	//Constructors
	CurrentAccount();

	//Accessors
	virtual double maxBorrowable() const;
	double getOverdraftLimit() const;

	//functions to put data into and get data from streams
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is);
	
	virtual const string prepareFormattedAccountDetails() const;

	//Data Members
private:
	double overdraftLimit;

};

#endif // !CURRENTACCOUNTH

