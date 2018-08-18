//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3


#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

#include <list>
#include "Transaction.h"

#include <cassert> 	// for assert()
#include <sstream>
#include <type_traits>

class TransactionList {
public:
	void  addNewTransaction(const Transaction&);
    const Transaction newestTransaction() const;
    const TransactionList olderTransactions() const;
	const TransactionList getMostRecentTransactions(const int& nTransactions) const;
	const double getTotalTransactions() const;
	//TransactionList* getTransactionsForAmount(double amount) const;

	//getTransactionsForCriterion !
	const TransactionList getTransactionsForCriterion(double criterion) const;
	const TransactionList getTransactionsForCriterion(const string& criterion) const;
	const TransactionList getTransactionsForCriterion(const Date& criterion) const;


	void deleteFirstTransaction();
    void deleteGivenTransaction(const Transaction&);
	void deleteTransactionsUpToDate(const Date& date);
	const TransactionList getTransactionsUpToDate(const Date& date) const;
	int	size() const;

	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream(ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream(istream& is);	//receive TransactionList info from an input stream


private:
    list<Transaction> listOfTransactions_;	//list of transactions
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const TransactionList&);	//insertion operator
istream& operator>>(istream& is, TransactionList& trl); //extraction operator

#endif

