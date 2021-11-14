#ifndef __PERSON_H
#define __PERSON_H

#include <string> 
#include <iostream> 
using namespace std;//使用string必须加using namespace std 

class Person{

	public: 
		Person();	
		Person(string );
		Person(int , int , string n="gj");
	//	Person(const Person& p);
		~Person();
		
		int getAge();
		int getHeight();
		string getName(); 

			
	public:	
		static int age;
		int* height; 
		string name;	

		
};



#endif


