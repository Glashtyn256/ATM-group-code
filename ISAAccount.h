//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3

#ifndef ISAACCOUNTH
#define ISAACCOUNTH

#include "SavingsAccount.h"

class ISAAccount : public SavingsAccount {
public:
	//Constructors
	ISAAccount();
	//Accessors
	double getMaximumYearlyDeposit();
	double getCurrentYearlyDeposit();
	const Date& getEndDepositPeriod() const;
	//Mutators
	virtual void recordDeposit(double amount);
	virtual bool canDesposit(double amount) const;

	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual istream& getAccountDataFromStream(istream& is);

	virtual const string prepareFormattedAccountDetails() const;

	//Data Members
private:
	//Data Members
	double maximumYearlyDeposit;
	double currentYearlyDeposit;
	Date endDepositPeriod;
	//Functions
	void updateCurrentYearlyDeposit(double a);
};

#endif // !ISAACCOUNTH

