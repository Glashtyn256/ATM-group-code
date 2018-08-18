//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3


#ifndef CHILDACCOUNTH
#define CHILDACCOUNTH

#include "SavingsAccount.h"

class ChildAccount : public SavingsAccount {
public:
	//Constructors
	ChildAccount();

	//Accessors
	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;
	virtual bool canWithdraw(double amount) const;
	//Mutators
	virtual bool canDeposit(double amount) const;
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is);

	virtual const string prepareFormattedAccountDetails() const;
	//Data Members
private:
	//Functions
	double maximumPaidIn;
	double minimumPaidIn;
};

#endif // !CHILDACCOUNTH

