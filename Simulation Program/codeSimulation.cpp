//Senior Project Logic Code Simulation
//Steven Zilberberg

#include <iostream>
#include <fstream>
#include "PersonProfile.h"
using namespace std;

//Constants
const int kNumberOfUserItems = 10;
const string kUserProfile = "UserData.txt";

	//Error Codes
const int kError_NoErrors = 0;
const int kError_AccelerometerRead = 1;
const int kError_HeartRateRead = 2;

//System Check
bool systemCheck();
bool checkGSMSensor();
bool checkGPSSensor();
bool checkHeartRateSensor();

//User Information
bool loadUserInformation(PersonProfile&);
void displayUser(PersonProfile);
void getUserLocation();

//Get Data Functions
int getData();
bool readAccelerometer();
bool readHeartRate();

//File I/O
bool check();

int main()
{
	PersonProfile newPerson = PersonProfile();
	bool systemOK = false, userLoaded = false, programRunning = false; 


	cout << "System Check....";
	systemOK = systemCheck();
	cout << "Complete" << endl;

	cout << "Loading user information...";
	userLoaded = loadUserInformation(newPerson);
	cout << "Complete" << endl << endl;

	cout << "User Information Succesfully Loaded" << endl;
	displayUser(newPerson);
	cout << "--------------------------------------" << endl;

	if(systemOK && userLoaded)
	{
		programRunning = true;
		cout << "********************************************************" << endl;
		cout << "Program Started Succesfully. Now Running" << endl;
		cout << "********************************************************" << endl;
	}
	else
	{
		programRunning = false;
		cout << "********************************************************" << endl;
		cout << "Error. Program Terminated" << endl;
		cout << "********************************************************" << endl;
	}

	while(programRunning)
	{
		sleep(3);
		int errorFlag = getData();
		if(errorFlag != kError_NoErrors)
			programRunning = false;

		//Might want to look into multithreading...
		switch (errorFlag)
		{
			case kError_NoErrors:
			{
				//No Errors
				break;
			}
			case kError_AccelerometerRead:
			{
				cout << "Send Information for Fall emergency" << endl;
				cout << newPerson.getName() << " has experienced a fall and can't get up!\n" << endl;
				cout << "They are located at ";
				getUserLocation();
				cout << endl;
				break;
			}
			case kError_HeartRateRead:
			{
				cout << "Send Information for heart rate emergency" << endl;
				cout << newPerson.getName() << " is experiencing a heart related emergency. Current BPM: 28\n";
				cout << "They are located at ";
				getUserLocation();
				cout << endl;
				break;
			}
		}
	}
}

bool systemCheck()
{
	bool gsmOK = checkGSMSensor();
	bool gpsOK = checkGPSSensor();
	bool heartOK = checkHeartRateSensor();
	if(gsmOK && gpsOK && heartOK)
		return true;
	else
		return false;
}

bool checkGSMSensor()
{
	return true;
}

bool checkGPSSensor()
{
	return true;
}

bool checkHeartRateSensor()
{
	return true;
}

bool loadUserInformation(PersonProfile& person)
{
	bool userProfileFound = check();
	if(userProfileFound)
	{
		ifstream inFile(kUserProfile.c_str());
		string token;
		inFile >> token;				//get first name
		person.setFirstName(token);
		inFile >> token;				//Get last name
		person.setLastName(token);
		getline(inFile, token);			//Dummy Pull
		getline(inFile, token);			//Get birthday
		person.setBirthdayString(token);
		inFile >> token;				//get blood type
		person.setBloodType(token);
		getline(inFile, token);			//Dummy Pull
		getline(inFile, token);			//Get Allergies
		person.setAllergies(token);

		return true;
	}
	else
	{
		return false;
	}
}

void displayUser(PersonProfile person)
{
	cout << "User: " << person.getName() << endl;
	cout << "DOB: " << person.getBirthday() << endl;
	cout << "Blood Type: " << person.getBloodType() << endl;
	cout << "Allergies: " << person.getAllergies() << endl;
}

bool check()
{
	ifstream inFile(kUserProfile.c_str());
	if(inFile)
		return true;
	else
		return false;
}

int getData()
{
	bool accelerometerRead = readAccelerometer();
	bool heartRateRead = readHeartRate();

	if(!accelerometerRead)
		return kError_AccelerometerRead;
	if(!heartRateRead)
		return kError_HeartRateRead;

	return 0;
}

bool readAccelerometer()
{
	ifstream inFile("AccelData.txt");
	int val = -1;
	inFile >> val;
	if(val == 0)
		return true;
	else
		return false;
}

bool readHeartRate()
{
	ifstream inFile("HeartData.txt");
	int val = -1;
	inFile >> val;
	if(val == 0)
		return true;
	else
		return false;
}

void getUserLocation()
{
	cout << "\n25.64374\n56.65874";
}

