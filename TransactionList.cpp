//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction(const Transaction& tr) {
    listOfTransactions_.push_front(tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.front());
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist(*this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.pop_front();
}
// This function is not used in the program
void TransactionList::deleteGivenTransaction(const Transaction& tr) {
	list<Transaction>::iterator it = find(listOfTransactions_.begin(), listOfTransactions_.end(), tr);
	listOfTransactions_.erase(it);
}
// Non Recursive Version - deleteTransactionsUpToDate
/*
void TransactionList::deleteTransactionsUpToDate(const Date & date)
{
	TransactionList temp;
	int _size = size();

	for (size_t i = 0; i < _size; i++)
	{
		if (!(newestTransaction().getDate() <= date))
			temp.addNewTransaction(newestTransaction());
		deleteFirstTransaction();
	}

	(*this) = temp;
}
*/
// Recursive Version
void TransactionList::deleteTransactionsUpToDate(const Date & date) {
	
	// Base Case - Get to a point with no Transactions.
	if (size() == 0) {
		return;
	}
	
	Transaction frontOfMe = newestTransaction();			// Store the transaction in scope. If it's needed, we'll return it later.
	deleteFirstTransaction();								// Reduce the list to it's own tail
	deleteTransactionsUpToDate(date);						// Run the recursive function on that tail.

	if (frontOfMe.getDate() > date)							// From the Base Case, check each transaction is valid... 
	{	
		addNewTransaction(frontOfMe);						// Only return valid transactions to the Transaction List
	}
}

// NON RECURSIVE VERSION - getTransactionsUpToDate
/*
const TransactionList TransactionList::getTransactionsUpToDate(const Date & date) const
{
	TransactionList temp;
	TransactionList copy = (*this);

	for (int i = 0; i < size(); i++)
	{
		if (copy.newestTransaction().getDate() <= date)
			temp.addNewTransaction(copy.newestTransaction());
		copy.deleteFirstTransaction();
	}

	return temp;
}
*/

// RECURSIVE VERSION - getTransactionsUpToDate
const TransactionList TransactionList::getTransactionsUpToDate(const Date & date) const
{
	// Base Case - Empty Transaction List
	if (size() == 0)
		return *this;
	else {
		Transaction frontOfMe = newestTransaction();									// Store latest transaction in Scope
		TransactionList newList = olderTransactions().getTransactionsUpToDate(date);	// Call function on Tail.

		if (frontOfMe.getDate() <= date)												// Add the latest transaction, if it's valid
		{
			newList.addNewTransaction(frontOfMe);
		}

		return newList;
	}
}

const TransactionList TransactionList::getTransactionsForCriterion(double criterion) const
{
	//create new list
	TransactionList r_list;
	//copy all transactions
	//list<Transaction> temp = listOfTransactions_;

	TransactionList temp = *this;

	int tempLen = temp.size();
	//go through the list, add first transaction if it matches criterion
	//else delete first and repeat until entire list has been searched
	for (int i = 0; i < tempLen; i++)
	{
		if (temp.newestTransaction().getAmount() == criterion)
			r_list.listOfTransactions_.push_back(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	//return the the list transactions matching criterion
	return r_list;
}
const TransactionList TransactionList::getTransactionsForCriterion(const string& criterion) const
{
	//create new list
	TransactionList r_list;
	//copy all transactions
	//list<Transaction> temp = listOfTransactions_;
	
	TransactionList temp = *this;
	int tempLen = temp.size();
	//go through the list, add first transaction if it matches criterion
	//else delete first and repeat until entire list has been searched
	for (int i = 0; i < tempLen; i++)
	{
		if (temp.newestTransaction().getTitle() == criterion)
			r_list.listOfTransactions_.push_back(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	//return the the list transactions matching criterion
	return r_list;
}

const TransactionList TransactionList::getTransactionsForCriterion(const Date& criterion) const
{
	//create new list
	TransactionList r_list;
	//copy all transactions
	TransactionList temp = *this;
	//list<Transaction> temp = listOfTransactions_;
	//added temp len ass length of list was recalculated each loop, skipping last element
	int tempLen = temp.size();
	//go through the list, add first transaction if it matches criterion
	//else delete first and repeat until entire list has been searched
	for (int i = 0; i < tempLen; i++)
	{
		if (temp.newestTransaction().getDate() == criterion)
			r_list.listOfTransactions_.push_back(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	//return the the list transactions matching criterion
	return r_list;
}

int TransactionList::size() const {
    return (listOfTransactions_.size());
}

const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList(*this);
	while (!(tempTrList.size() == 0))
    {
		os_transactionlist << endl << tempTrList.newestTransaction().toFormattedString();
        tempTrList.deleteFirstTransaction();
    }
	return (os_transactionlist.str());
}

ostream& TransactionList::putDataInStream(ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream(istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while (is) 	//while not end of file
	{
		listOfTransactions_.push_back(aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}

 const TransactionList TransactionList::getMostRecentTransactions(const int& nTransactions) const {
	assert(nTransactions > 0);


	//create new list
	TransactionList r_list;

	//if desired number of transactions is within list length
	if (nTransactions < listOfTransactions_.size()) {

		TransactionList buffer_list = *this;
		//add the first item of temp list to r_list, delete temp's first item, repeat until done
		for (int i = 0; i < nTransactions; i++)
		{
			r_list.listOfTransactions_.push_back(buffer_list.newestTransaction());
			buffer_list.deleteFirstTransaction();
			//r_list.deleteFirstTransaction();
		}
		//return the the list with specified number of transactions
		return r_list;
	}
	// else return list of all transactions
	else {
		//return all of the transactions
		return *this;
	}
}

const double TransactionList::getTotalTransactions() const {
	//copy the list
	
	TransactionList temp = *this;
	double total(0);

	//go through each aspect of the list and add the value to a running total
	while (temp.size() != 0) {
		total += temp.newestTransaction().getAmount();
		temp.deleteFirstTransaction();
	}

	return total;
}

//TransactionList* TransactionList::getTransactionsForAmount(double amount) const
//{
//	// Use templates
//	return nullptr;
//}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const TransactionList& aTransactionList) {
    return (aTransactionList.putDataInStream(os));
}
istream& operator>>(istream& is, TransactionList& aTransactionList) {
	return (aTransactionList.getDataFromStream(is));
}
