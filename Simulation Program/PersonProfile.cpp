//Senior Project Logic Code Simulation
//PersonProfile Class Cpp
//Steven Zilberberg

#include "PersonProfile.h"

PersonProfile::PersonProfile()
{
	contactIndex = -1;
}

void PersonProfile::setFirstName(string newFirst)
{
	firstName = newFirst;
}

void PersonProfile::setLastName(string newLast)
{
	lastName = newLast;
}

void PersonProfile::setBirthdayString(string newBirthday)
{
	birthday = newBirthday;
}

void PersonProfile::setBloodType(string newBlood)
{
	bloodType = newBlood;
}

void PersonProfile::setAllergies(string newAllergies)
{
	allergies = newAllergies;
}

string PersonProfile::getName()
{
	return (lastName + ", " + firstName);
}

string PersonProfile::getBirthday()
{
	return birthday;
}

string PersonProfile::getBloodType()
{
	return bloodType;
}

string PersonProfile::getAllergies()
{
	return allergies;
}

string PersonProfile::toString()
{
	string output = "";

	output += getName() + "\n";
	output += getBirthday() + "\n";
	output += "Blood Type: " + getBloodType() + "\n";
	output += "Allergies: " + getAllergies() + "\n";

	return output;
}

bool PersonProfile::addNewContact(Contact newContact)
{
	if(contactIndex < kNumberOfContacts - 1)
	{
		contactIndex++;
		listOfContacts[contactIndex] = newContact;
		return true;
	}
	else
	{
		return false;
	}
}

bool PersonProfile::hasContacts()
{
	if(contactIndex >= 0)
		return true;
	else 
		return false;
	//return contactIndex >= 0 ? true : false;
}

int  PersonProfile::getNumberOfContacts()
{
	return contactIndex + 1;
}

Contact PersonProfile::getContactAtIndex(int index)
{
	return listOfContacts[index];
}

void PersonProfile::viewAllContacts()
{
	if(contactIndex == -1)
		return;
	for(int c = 0; c <= contactIndex; c++)
	{
		Contact current = getContactAtIndex(c);
		cout << current.getContact() << endl;
	}
}
