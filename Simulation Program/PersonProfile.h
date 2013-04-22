#include <iostream>
using namespace std;

class PersonProfile
{
	private:
		string firstName;
		string lastName;

		string birthday;

		string bloodType;
		string allergies;
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
};
