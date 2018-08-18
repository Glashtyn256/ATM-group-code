//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "Card.h"

//---------------------------------------------------------------------------
//CashCard: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

Card::Card()
	: cardNumber_("null")
{}
Card::Card(const string& cardNum, const List<string>& accList)
	: cardNumber_(cardNum),
	accountsList_(accList)
{}

//____other public member functions

const string Card::getCardNumber() const {
	return cardNumber_;
}
const List<string> Card::getAccountsList() const {
	return accountsList_;
}
bool Card::onCard(const string& accFileName) const {
	//e.g., data\account_001
	string accName = accFileName.substr(13, 3);	//account identifier
	return (accountsList_.member(accName)); //check if member of the card account list
}
void Card::readInCardFromFile(const string& accFileName) {
	ifstream fromFile;
	fromFile.open(accFileName.c_str(), ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		fromFile >> (*this);   //read all info from card file
//  fromFile.close();			//close file: optional here
}
const string Card::toFormattedString() const
{
	ostringstream os_card;
	if (accountsList_.isEmpty())
	{
		os_card << "\n      LIST OF ACCOUNTS IS EMPTY!!!";
	}
	else
	{
		List<string> tempAccList(accountsList_); //make a copy of the list of accounts on card
		while (!(tempAccList.isEmpty()))
		{
			os_card << "\n      ACCOUNT NUMBER: " << tempAccList.first();
			tempAccList.deleteFirst();
		}
	}
	return (os_card.str());
}

ostream& Card::putDataInStream(ostream& os) const {
	//put (formatted) CashCard details in stream
	os << cardNumber_ << "\n";	//store card number
	List<string> tempAccounts(accountsList_);
	while (!(tempAccounts.isEmpty())) 	//while not empty
	{
		os << tempAccounts.first() << endl; 	//copy each account name & <Return> in file
		tempAccounts.deleteFirst();	//delete account reference from history of transactions
	}
	return os;
}
istream& Card::getDataFromStream(istream& is) {
	//get CashCard details from stream
	is >> cardNumber_;	//read card number
	string anAccountName;
	is >> anAccountName;	//read first account name
	while (is) 	//while not end of file
	{
		accountsList_.addAtEnd(anAccountName);   //add account
		is >> anAccountName;	//read next account name
	}
	return is;
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Card& aCashCard) {
	//Card formatted output
	return (aCashCard.putDataInStream(os));
}
istream& operator>>(istream& is, Card& aCashCard) {
	//read in CashCard details
	return (aCashCard.getDataFromStream(is));
}
