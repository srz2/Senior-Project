//Senior Project Logic Code Simulation
//Contact Class Cpp
//Steven Zilberberg

#include "Contact.h"

Contact::Contact()
{
	relation = "";
	phoneNumber = "";
	firstName = "";
	lastName = "";
}

Contact::Contact(string data)
{
	relation = data.substr(0,data.find(' '));
	data = data.substr(data.find(' ') + 1);
	firstName = data.substr(0,data.find(' '));
	data = data.substr(data.find(' ') + 1);
	lastName = data.substr(0,data.find(' '));
	data = data.substr(data.find(' ') + 1);
	phoneNumber = data.substr(0,data.find(' '));
	data = data.substr(data.find(' ') + 1);
}

Contact::Contact(string newRelation, string newPhone, string newFirst, string newLast)
{
	relation = newRelation;
	phoneNumber = newPhone;
	firstName = newFirst;
	lastName = newLast;
}

void Contact::setRelation(string newRelation)
{
	relation = newRelation;
}

void Contact::setPhoneNumber(string newPhone)
{
	phoneNumber = newPhone;
}

void Contact::setFirstName(string newFirst)
{
	firstName = newFirst;
}

void Contact::setLastName(string newLast)
{
	lastName = newLast;
}

string Contact::getRelation()
{
	return relation;
}

string Contact::getPhoneNumber()
{
	return phoneNumber;
}

string Contact::getFirstName()
{
	return firstName;
}

string Contact::getLastName()
{
	return lastName;
}

string Contact::getContact()
{
	string output = "";
	output += getLastName() + ", " + getFirstName() + "\n";
	output += getRelation() + "\n";
	output += getPhoneNumber() + "\n";

	return output;
}

