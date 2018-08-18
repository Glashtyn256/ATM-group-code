//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3


#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
#include <cassert>
using namespace std;


class BankAccount {
public:
	// constructors & destructor
	BankAccount();
	virtual ~BankAccount();

	// Accessor functions
	const string getAccountNumber() const;
	const Date getCreationDate() const;
	double getBalance() const;
	const TransactionList getTransactions() const;
	bool	isEmptyTransactionList() const;
	const string prepareFormattedStatement() const;
	const string prepareFormattedTransactionList() const;
	void storeBankAccountInFile(const string& fileName) const;
	void produceNMostRecentTransactions(const int& nTransactions, string* const str, double* const size) const;
	void produceTransactionsUpToDate(const Date& d, string* const str, int* const size) const;

	// Update functions
	void recordWithdrawal(double amount);
	void recordTransferOut(double amount, const string& sentTo);
	void recordDeletionOfTransactionUpToDate(const Date& d);
	void readInBankAccountFromFile(const string& fileName);

	// Virtual operations
	virtual const string prepareFormattedAccountDetails() const = 0;
	virtual const string prepareFormattedMiniAccountDetails() const;
	virtual void recordDeposit(double amount);
	virtual void recordTransferIn(double amount, const string& inFrom);
	virtual bool canDeposit(double amount) const;

	virtual double maxBorrowable() const;
	virtual bool canWithdraw(double amount) const;
	
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	virtual ostream& putAccountDetailsInStream(ostream& os) const = 0;
	istream& getDataFromStream(istream& is);
	virtual istream& getAccountDataFromStream(istream& is) = 0;


	//void produceTransactionsForAmount(double amount, string* message) const;

	//! new template produceTransactionsForCriterion !
	template <class C>
	void produceTransactionsForCriterion(const C& criterion, string* const str, int* const size) const
	{
		TransactionList trl = transactions_.getTransactionsForCriterion(criterion);
		*size = trl.size();
		*str = trl.toFormattedString();
	}

	static const string getAccountType(const string& filename);
	static const string getAccountType(char n);

private:
	//data items
	string accountNumber_;
	Date   creationDate_;
	double balance_;
	TransactionList transactions_;

	//support functions
	void updateBalance(double amount);
	ostream& putTransactionInStream(ostream& os) const;
	istream& getTransactionsDataFromStream(istream& is);
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

#endif
