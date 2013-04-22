#include "PersonProfile.h"

PersonProfile::PersonProfile()
{
	
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
