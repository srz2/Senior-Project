//Senior Project Logic Code Simulation
//Steven Zilberberg

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include "PersonProfile.h"
using namespace std;

//Constants
const int kNumberOfUserItems = 10;
const string kUserProfileFile = "UserData.txt";
const string kHeartDataFile = "HeartData.txt";
const string kAccelDataFile = "AccelData.txt";

	//Error Codes
const int kError_NoErrors = 0;
const int kError_AccelerometerRead = 1;
const int kError_HeartRateRead = 2;

//System Check
bool systemCheck();
bool checkGSMSensor();
bool checkGPSSensor();
bool checkHeartRateSensor();
bool checkFiles();

//User Information
bool loadUserInformation(PersonProfile&);
void displayUser(PersonProfile);
void getUserLocation();

//Get Data Functions
int getData();
bool readAccelerometer();
bool readHeartRate();

//File I/O
bool check(string file);

//Housekeeping Functions
void flush();
void waitForEnter();

//MultithreadFunctions
void * programUserMenu(void* passedPerson);
PersonProfile newPerson = PersonProfile();

int main()
{

	bool systemOK = false, userLoaded = false, programRunning = false; 


	cout << "System Check....";
	systemOK = systemCheck();
	if(systemOK)
		cout << "Complete" << endl;
	else
		cout << "Fail" << endl;

	if(systemOK)
	{
		cout << "Loading user information...";
		userLoaded = loadUserInformation(newPerson);
		if(userLoaded)
			cout << "Complete" << endl << endl;
		else
			cout << "Fail" << endl << endl;
	}

	if(systemOK && userLoaded)
	{
		cout << "User Information Succesfully Loaded" << endl;
		displayUser(newPerson);
		cout << "--------------------------------------" << endl;

		programRunning = true;
		cout << "********************************************************" << endl;
		cout << "Program Started Succesfully. Now Running" << endl;
		cout << "********************************************************" << endl;

		pthread_t menuThread;
		pthread_create( &menuThread, NULL, programUserMenu, &newPerson);

		while(programRunning)
		{
			sleep(1);
			int errorFlag = getData();
			if(errorFlag != kError_NoErrors)
				programRunning = false;

			//NEED to look into multithreading...DONE :D
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
					exit(kError_AccelerometerRead);
					break;
				}
				case kError_HeartRateRead:
				{
					cout << "Send Information for heart rate emergency" << endl;
					cout << newPerson.getName() << " is experiencing a heart related emergency. Current BPM: 28\n";
					cout << "They are located at ";
					getUserLocation();
					cout << endl;
					exit(kError_HeartRateRead);
					break;
				}
			}
		}
	}
	else
	{
		programRunning = false;
		cout << "********************************************************" << endl;
		cout << "Error. Program Terminated" << endl;
		cout << "********************************************************" << endl;
	}
}

void * programUserMenu(void* passedPerson)
{
	int option;
	while(true)
	{
		cout << "Brofsky Shield Simulator Console" << endl;
		cout << "1 - View User" << endl;
		cout << "2 - View Emergency Contacts" << endl;
		cout << "3 - View user information" << endl;
		cout << "0 - Exit Program" << endl;
		cin >> option;

		switch (option)
		{
			case 0:
			{
				cout << "Program now Terminated" << endl;
				exit(kError_NoErrors);
				break;
			}
			case 1:
			{
				cout << "User: " << newPerson.getName() << endl;
				waitForEnter();
				break;
			}
			case 2:
			{
				newPerson.viewAllContacts();
				waitForEnter();
				break;
			}
			case 3:
			{
				cout << newPerson.toString() << endl;
				waitForEnter();
				break;
			}
			default:
			{
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
	bool filesFound = checkFiles();
	if(gsmOK && gpsOK && heartOK && filesFound)
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

bool checkFiles()
{
	bool userData = check(kUserProfileFile);
	bool accelData = check(kAccelDataFile);
	bool heartData = check(kHeartDataFile);

	if(userData && accelData && heartData)
		return true;
	else
		return false;
}

bool loadUserInformation(PersonProfile& person)
{
	bool userProfileFound = check(kUserProfileFile);

	if(userProfileFound)
	{
		ifstream inFile(kUserProfileFile.c_str());
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
		while(getline(inFile, token))	//Get Emergency Contacts
		{
			person.addNewContact(Contact(token));
		}
		inFile.close();

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
	cout << "Emergency Contacts: " << person.getNumberOfContacts() << endl;
}

bool check(string file)
{
	ifstream inFile(file.c_str());
	if(inFile)
		return true;
	else
	{
		cout << file << " Not Found" << endl;
		return false;
	}
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
	check(kAccelDataFile);

	ifstream inFile(kAccelDataFile.c_str());
	int val = -1;
	inFile >> val;
	if(val == 0)
		return true;
	else
		return false;
}

bool readHeartRate()
{
	check(kHeartDataFile);

	ifstream inFile(kHeartDataFile.c_str());
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

void flush()
{
	int ch;
	while ((ch = cin.get()) != '\n' && ch != EOF);
}

void waitForEnter()
{
	string dummy;
	flush();
	getline(cin, dummy);
}

