#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <cstring>
using namespace std;

const char FILE_DIR[] = "contacts.dat";

struct Contact{
	char name[30];
	char last_name[45];
	int age;
	char email[45];
};

/**************** PROGRAM FUNCTIONS ****************/
void loadContact(Contact c);
Contact readContact();
bool existingContact(char name[], char last_name[]);
Contact searchContact(char name[], char last_name[]);
void showContacts(Contact c);
void contactList();
void eraseContact(char name[], char last_name[]);
void updateContact(char name[], char last_name[]);

/********************************************************/

/************** MENU FUNCTION **************/
void menuLoadContact();
void menuSearchContact();
void menuContactList();
void menuEraseContact();
void menuUpdateContact();

/********************** MAIN ************************/
int main(int argc, char *argv[]) {
	int opc;
	do{
		system("CLS");
		cout<<"\t\tCONTACT BOOK"<<endl;
		cout<<"\t\t1)_ Add a contact"<<endl;
		cout<<"\t\t2)_ Search for a contact"<<endl;
		cout<<"\t\t3)_ Show contacts"<<endl;
		cout<<"\t\t4)_ Delete a contact"<<endl;
		cout<<"\t\t5)_ Modify a contact"<<endl;
		cout<<"\t\t0)_ Exit"<<endl;
		cout<<"\t\tEnter option: ";
		cin>>opc;
		cin.ignore();
		system("CLS");
		switch(opc){
		case 1: menuLoadContact();
				break;
		case 2: menuSearchContact();
				break;
		case 3: menuContactList();
				break;
		case 4: menuEraseContact();
				break;
		case 5: menuUpdateContact();
				break;
		default:cout<<"\t\tINVALID OPTION"<<endl;
		}
	} while(opc!=0);
	return 0;
}

/*	Write a contact in the file */
void loadContact(Contact c){
	ofstream output;
	output.open(FILE_DIR, ios::binary | ios::app);//Opens in binary mode and writes at the end
	output.write((char*)&c,sizeof(Contact));
	output.close();
}

/*	Read a contact entered by the user */
Contact readContact(){
	Contact c;
	
	cout<<"\t\tName   : ";
	cin.getline(c.name, 30);
	cout<<"\t\tLast name : ";
	cin.getline(c.last_name, 45);
	cout<<"\t\tAge     : ";
	cin>>c.age;
	cin.ignore();//Delete the "\n" in the input buffer
	cout<<"\t\te-mail   : ";
	cin.getline(c.email, 45);
	
	return (c);
}

/*	Check if a contact exists in the file	*/
bool existingContact(char name[], char last_name[]){
	Contact c;
	ifstream input;
	input.open(FILE_DIR, ios::binary);
	if(input.good()){
		while(input.read((char*)&c,sizeof(Contact))){
			if(strcmp(name,c.name) == 0 && strcmp(last_name,c.last_name) == 0){
				input.close();
				return true;
			}
		}
		input.close();
		return false;
	}
	else{
		input.close();
		return false;
	}
}

/*	Find if a contact exists in the file	*/
Contact searchContact(char name[], char last_name[]){
	Contact c;
	ifstream input;
	input.open(FILE_DIR, ios::binary);
	if(input.good()){
		while(input.read((char*)&c,sizeof(Contact))){
			if(strcmp(name,c.name) == 0 && strcmp(last_name,c.last_name) == 0){
				input.close();
				return c;
			}
		}
	}
	input.close();
	return c;
}

/*	Show a contact	*/
void showContacts(Contact c){
	cout<<"\t\tName   : "<<c.name<<endl;
	cout<<"\t\tLast name : "<<c.last_name<<endl;
	cout<<"\t\tAge     : "<<c.age<<endl;
	cout<<"\t\te-mail   : "<<c.email<<endl;
}

/*	Show contact list	*/
void contactList(){
	ifstream input;
	input.open(FILE_DIR, ios::binary);
	Contact c;
	if(input.good()){
		while(input.read((char*)&c,sizeof(Contact))){
			showContacts(c);
			cout<<endl;
		}
	}
	else{
		cout<<"The file could not be read."<<endl;
	}
	input.close();
}

/*	Delete a contact in the file */
void eraseContact(char name[], char last_name[]){
	ifstream input;
	ofstream temp;
	input.open(FILE_DIR, ios::binary);
	temp.open("temp.dat", ios::binary);
	Contact c;
	if(input.good()){
		while(input.read((char*)&c,sizeof(Contact))){
			if(strcmp(name,c.name) != 0 || strcmp(last_name,c.last_name) != 0){
				temp.write((char*)&c,sizeof(Contact));
			}
		}
	}
	input.close();
	temp.close();
	remove(FILE_DIR);
	rename("temp.dat",FILE_DIR);
}

/*	Update a contact in the file */
void updateContact(char name[], char last_name[]){
	ifstream input;
	ofstream temp;
	input.open(FILE_DIR, ios::binary);
	temp.open("temp.dat", ios::binary);
	Contact c;
	if(input.good()){
		while(input.read((char*)&c,sizeof(Contact))){
			if(strcmp(name,c.name) == 0 && strcmp(last_name,c.last_name) == 0){
				Contact actualizado = readContact();
				temp.write((char*)&actualizado,sizeof(Contact));
			}
			else{
				temp.write((char*)&c,sizeof(Contact));
			}
		}
	}
	input.close();
	temp.close();
	remove(FILE_DIR);
	rename("temp.dat",FILE_DIR);
}

/*************	FUNCTIONS THAT DISPLAY DIFFERENT MENUS	**************/
void menuLoadContact(){
	cout<<"\t\tADD A NEW CONTACT"<<endl;
	Contact newContact = readContact();
	loadContact(newContact);
	cout<<"\t\tCONTACT ADDED SUCCESSFULLY"<<endl;
}
void menuSearchContact(){
	cout<<"\t\tSEARCH CONTACT"<<endl;
	char name[30], last_name[45];
	cout<<"\t\tENTER CONTACT DATA"<<endl;
	cout<<"\t\tName: ";
	cin.getline(name, 30);
	cout<<"\t\tLast name: ";
	cin.getline(last_name, 45);
	cout<<endl;
	if(existingContact(name,last_name)){
		Contact find_Contact = searchContact(name,last_name);
		showContacts(find_Contact);
		getch();
	}
	else{
		cout<<"\t\tCONTACT NOT FOUND"<<endl;
	}
}
void menuContactList(){
	cout<<"\t\tCONTACT LIST"<<endl<<endl;
	contactList();
	getch();
}
void menuEraseContact(){
	cout<<"\t\tDELETE CONTACT"<<endl;
	char name[30], last_name[45];
	cout<<"\t\tENTER CONTACT DATA"<<endl;
	cout<<"\t\tName: ";
	cin.getline(name, 30);
	cout<<"\t\tLast name: ";
	cin.getline(last_name, 45);
	if(existingContact(name,last_name)){
		Contact deleted_contact = searchContact(name,last_name);
		int opc;
		cout<<"Are you sure you want to delete this contact?"<<endl;
		showContacts(deleted_contact);
		do{
			cout<<"\t\t\tSI[1]....NO[2]:";
			cin>>opc;
				switch(opc){
				case 1:
					eraseContact(name,last_name);
					cout<<"\t\tCONTACT DELETED SUCCESSFULLY"<<endl;
					break;
				case 2: break;
				default: cout<<"\t\tINVALID OPTION"<<endl;
			}
		} while(opc!=1 && opc!=2);
	}
	else{
		cout<<"\t\tTHE CONTACT DOES NOT EXIST"<<endl;
	}
}
void menuUpdateContact(){
	cout<<"\t\tUPDATE CONTACT"<<endl;
	char name[30], last_name[45];
	cout<<"\t\tENTER CONTACT DATA"<<endl;
	cout<<"\t\tname: ";
	cin.getline(name, 30);
	cout<<"\t\tlast_name: ";
	cin.getline(last_name, 45);
	if(existingContact(name,last_name)){
		Contact find_contact = searchContact(name,last_name);
		cout<<"\t\tFinded contact:"<<endl;
		showContacts(find_contact);
		updateContact(name,last_name);
		cout<<"\t\tTHE CONTACT WAS UPDATED"<<endl;
	}
	else{
		cout<<"\t\tTHE CONTACT DOES NOT EXIST"<<endl;
	}
}
