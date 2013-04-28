//Senior Project Logic Code Simulation
//Contact Class Header
//Steven Zilberberg

#include <iostream>
using namespace std;

class Contact
{
private:
	string relation;
	string phoneNumber;
	string firstName;
	string lastName;
public:
	Contact();
	Contact(string contactData);
	Contact(string newRelation, string newPhone, string newFirst, string newLast);

	void setRelation(string newRelation);
	void setPhoneNumber(string newPhone);
	void setFirstName(string newFirst);
	void setLastName(string newLast);

	string getRelation();
	string getPhoneNumber();
	string getFirstName();
	string getLastName();

	string getContact();
};