//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3


#ifndef ATMH
#define ATMH 

//---------------------------------------------------------------------------
//ATM: class declaration
//---------------------------------------------------------------------------

#include "Card.h"
#include "BankAccount.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "ISAAccount.h"
#include "UserInterface.h"
#include "ChildAccount.h"
#include "ListT.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

class ATM {
public:
	ATM();	//default constructor
	~ATM();	//destructor
    void activateCashPoint();
private:
	//data items
    BankAccount* p_theActiveAccount_;
    Card* p_theCard_;
    const UserInterface& theUI_;

	//support functions
    int  validateCard(const string&) const;
	void executeCardCommand(int);
	int  validateAccount(const string&) const;
	void executeAccountCommand();
	void searchTransactions() const;
	void attemptTransfer(BankAccount* receiveAccount);
	void recordTransfer(double transferAmount, BankAccount* receiveAccount);

	// search for transactions menus
	void m_trl1_showTransactionsForAmount() const;
	void sm2_showTransactionsForTitle() const;
	void sm3_showTransactionsForDate() const;
 
	//card menu commands
	void m_card1_manageIndividualAccount();
	void m_card2_showFundsAvailableOnAllAccounts();
	//account menu commands
    void m_acct1_produceBalance() const;
    void m_acct2_withdrawFromBankAccount();
    void m_acct3_depositToBankAccount();
    void m_acct4_produceStatement() const;
	void m_acct6_showMiniStatement() const;
	void m_acct7_searchForTransactions() const;
	void m_acct8_clearTransactionsUpToDate();
	void m_acct9_transferCashToAnotherAccount();	// Used from an account to transfer to a different account.


    //support file handling functions and creation of dynamic objects
    bool canOpenFile(const string&) const;
	static char getAccountTypeCode(const string&);
	bool accountsListedOnCard(const string&) const;

    void activateCard(const string&);
	void releaseCard();

	BankAccount* activateAccount(const string&);
	BankAccount* releaseAccount(BankAccount*, string);
};

#endif
