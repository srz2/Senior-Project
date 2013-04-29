//Senior Project Logic Code Simulation
//PersonProfile Class Header
//Steven Zilberberg

#include <iostream>
#include "Contact.h"
using namespace std;

const int kNumberOfContacts = 10;

class PersonProfile
{
	private:
		string firstName;
		string lastName;

		string birthday;

		string bloodType;
		string allergies;

		Contact listOfContacts[kNumberOfContacts];
		int contactIndex;
	public:
		PersonProfile();

		void setFirstName(string newFirst);
		void setLastName(string newLast);
		void setBirthdayString(string newBirthday);
		void setBloodType(string newBlood);
		void setAllergies(string newAllergies);

		string getName();
		string getBirthday();
		string getBloodType();
		string getAllergies();

		string toString();

		bool addNewContact(Contact newContact);
		bool hasContacts();
		int  getNumberOfContacts();
		Contact getContactAtIndex(int index);
		void viewAllContacts();

};
