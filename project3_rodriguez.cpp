/*
Title: Project 3
Abstract: This program will read a file that reads a student's name, id, five quiz scores, two midterm scores, and one final scores. This program and calculate the numeric average, letter grade, and ranking of each student. After that,
your program should display the course result in order of numeric averages and first names respectively. This program will display results in a histogram. 
Author: Alex Rodriguuez
Date: 5/6/15
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

class Student
{
private:
    string name;
    int id;
    double avg;
    double final_scor;
    char grade_lttr;
    int rank;
public:
    Student();
    void summary();
    
    //get functions
    double getavg();
    char getgrade_lttr();
    int getid();
    string get_name();
    
    //set function
    void setstudentinfo(string newName, int newID, double newAvg);
    void setrank(int newRank);
    void setGrade_Lttr();
};

//Prototype
int read_file(Student students[]);
void numericalavg_header();
void s_sort(Student students[], int size);
void abc_sort(Student x[], int n);
void search_name(Student students[],int size,string name);

//main function
int main(void)
{
    Student students[30];
    
	int size = read_file(students);
    //sorts student ranks
    s_sort(students,size);
    //prints out numerical average header
    //Header
    cout <<"-------------------------------------------------\n"
    << "Course Report: Numerical Average Order\n"
    <<"-------------------------------------------------\n";
    //format and alignment
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.setf(ios::left);
    cout.precision(2);
    
    //assigns ranks to private varibale "rank"
    int r=1;
    int count=1;
    for(int i=0; i < size; i++)									//assigns ranks
    {
        if (students[i].getavg()==students[i+1].getavg())
        {
            r=count;
            students[i].setrank(r);
            count++;
        }
        else if (students[i].getavg()!=students[i+1].getavg())
        {
            students[i].setrank(r);
            r++;
            count++;
        }
    }
    //for loop that prints out students in order of rank
    for(int i=0; i < size; i++)
    {
        students[i].summary();
    }
    cout << "-------------------------------------------------\n\n"
    <<"-------------------------------------------------\n"
    <<"Course Report: First Name Order\n"
    <<"-------------------------------------------------\n";
    //call abc sorting function
    abc_sort(students,size);
    for (int i=0; i < size; i++)
    {
        students[i].summary();
    }
	cout <<"-------------------------------------------------\n\n";
	//Statistics header
	cout <<"-------------------------------------------------\n"
		 << "Statistics\n"
		 <<"-------------------------------------------------\n";
		//Number of Students
	cout << "Number of Students: " << size<<endl;
		//Class Average Calculations
	double class_total=0, class_avg=0;
	for (int i=0;i<size;i++)
	{
		class_total= class_total+students[i].getavg();
	}
	class_avg=class_total/size;

	cout << "Class Average: " << class_avg <<endl;
	//Histogram
	cout<< "Grade Average Distribution\n";
		//counts number of grades for each student
	int letter_counts[5]={0};
	int count_a=0, count_b=0, count_c=0, count_d=0,count_f=0;
	//grade letter conditionals
		for (int i=0;i<size;i++)
		{
			if (students[i].getavg() >= 90)
			  { //A value goes up by one
				letter_counts[0]++;
			   }
		   if ( students[i].getavg()< 90 && students[i].getavg() >= 80)
				{//B Value goes up
				  letter_counts[1]++;
			   }
			 if (students[i].getavg() < 80 && students[i].getavg()>= 70)
				{//C value goes up
					letter_counts[2]++;
			     }
			 if (students[i].getavg() < 70 && students[i].getavg() >= 60)
			{//D value goes up
			    letter_counts[3]++;
			 }
			if (students[i].getavg() <60&& students[i].getavg()>=0)
			 {//F value goes up
			   letter_counts[4]++;
			  }
		}
	
		//code for histogram
	double heights[5]={0};			
	int x,y;					//set histogram variables 
	for (x=0; x<5; x++) 
	{
		heights[x]=letter_counts[x];	//grade counts get placed into heights array
	}
	
	for (y=size; y>=0; y--)				//prints out stars vertically
	 {
		  for (x=0; x<5; x++)
			{
				if (heights[x]<=y)
				{	cout << "   ";} 
				else 
				{   cout << " * ";}
					//sets width
		    }
		
        cout << endl;
	}
	cout<<" A  B  C  D  F" <<endl;
	cout<<"-------------------------------------------------\n"
	//Record Finder Part
		<<"-------------------------------------------------\n";
		string student_name;
	cout<<"Record Finder: Enter the name of a student: "; cin>> student_name; 
	cout<<"-------------------------------------------------\n";
		//program that searches for user's input 
	search_name(students,size,student_name);
	// User is asked if he/she would like to continue
	cout<<"-------------------------------------------------\n";
		char answer;
	cout << "Do you want to continue? (y/n): ";  cin >> answer; 
	cout<<"-------------------------------------------------\n";
	//if yes 
	while (answer=='y'||answer=='Y')
	{
		cout << "Record Finder: Enter the name of a student: "; cin >> student_name; 
		cout <<"-------------------------------------------------\n";
		search_name(students,size,student_name);
		cout <<"-------------------------------------------------\n"
			<<"Do you want to continue? (y/n): ";  cin >> answer;
		cout<<"-------------------------------------------------\n";
		  if (answer=='n'||answer=='N')
			break;
	}
	//if no 
	if (answer=='n'||answer=='N')
	{
		cout <<"Done.\n";
	}
    return 0;
}

char Student::getgrade_lttr()
{
    char newGrade_Lttr=grade_lttr;
    return newGrade_Lttr;
}

void Student::setGrade_Lttr()
{
    //grade letter conditionals
    if (avg >= 90)
    {
        grade_lttr = 'A';
    }
    if (avg < 90 && avg >= 80)
    {
        grade_lttr = 'B';
    }
    if (avg < 80 && avg >= 70)
    {
        grade_lttr = 'C';
    }
    if (avg < 70 && avg >= 60)
    {
        grade_lttr = 'D';
    }
    if (avg < 60)
    {
        grade_lttr = 'F';
    }
}

void Student::summary()				//summary function definition
{	cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.setf(ios::left);
    cout.precision(2);
    cout.width(6);
    cout << name << id << " - " << avg << "  (" << grade_lttr << ")  (rank: " << rank << ")" << endl;
}

Student::Student()						//default constructor
{
    name = "Alex";
    id=0000;
    avg=00;
    
}

int read_file(Student students[])
{
    ifstream in_file;
    string name;
    int id;
    double quiz_scor[5];
    double midterm_scor[2];
    double final_scor;
    double numeric_avg=0;
    
    
    //ask user to input file
    string filepath;
    cout<< "Enter an input file: ";
    cin>> filepath;
    
    in_file.open(filepath);
    //in_file.open("studentinfo.txt");
    
    if(in_file.fail())
    { 
        cout << "Error, file could not open.\n";
    }
    int i=0;
    while (!in_file.eof())
    {
        
        in_file>> name >> id >> quiz_scor[0] >> quiz_scor[1] >> quiz_scor[2] >> quiz_scor[3] >> quiz_scor[4] >> midterm_scor[0] >> midterm_scor[1] >> final_scor;
        
        //sort quiz scores from least to greatest
        int quiz_size=5;
        //sorts through wach element of the array
        for (int start_indx=0; start_indx<quiz_size; start_indx++)
        {
            //temp variable for smallest value
            int smallestindx=  start_indx;
            //sorts through quiz scores array atarting at quizstart+1
            for (int currentindx=start_indx+1;currentindx <quiz_size; currentindx++)
            {
                if (quiz_scor[currentindx]< quiz_scor[smallestindx])
                    smallestindx=currentindx;
                
            }
            //swap smallest number from inner-most for loop with the new smallest index
            swap(quiz_scor[start_indx], quiz_scor[smallestindx]);
        }
        
        //disregards first quiz score and calculates quiz average
        double quiz_total=0;
        double quiz_avg=0;
        for ( int g=1; g< quiz_size; g++)
        {
            quiz_total= quiz_total+quiz_scor[g];
        }
        quiz_avg=quiz_total/4;
        quiz_avg=quiz_avg*10;
        
        // Calculates total mid-term average
        double midterm_total, midterm_avg;
        midterm_total=midterm_scor[0]+midterm_scor[1];
        midterm_avg=midterm_total/2;
        
        //Calculates Overall Student Average
        numeric_avg=(quiz_avg*.20)+(midterm_avg*.40)+(final_scor*.40);
        students[i].setstudentinfo(name, id, numeric_avg);
        
        i++;
    
	}
    
    return i;
}

void Student::setrank(int newRank)
{
    rank=newRank;
}

void Student::setstudentinfo(string newName, int newID, double newAvg)
{
    name = newName;
    id = newID;
    avg = newAvg;
    setGrade_Lttr();
    
}

double Student::getavg()
{
    double student_avg =avg;
    return student_avg;
}

string Student::get_name()
{
    string student_name=name;
    return student_name;
    
}

void s_sort(Student students[], int size)			//sorts ranks from greatest to least
{
    int m; // keep the index of current largest value
    Student hold;
    for (int k=0; k<=size-2; k++) 
    {
        m = k;
        for (int j=k+1; j <= size; j++) 
        {
            if (students[j].getavg() > students[m].getavg())
            {
                m = j;
            }
            
        }
        hold = students[m];
        students[m] = students[k];
        students[k] = hold;
    }
}

void abc_sort(Student x[], int n)						//sorts names alphabetically
{
    int m; // keep the index of current smallest value
    Student hold;
    
    for (int k = 0; k <= n - 2; k++) 
	{
        m = k;
        for (int j = k + 1; j <= n - 1; j++) {
            if (x[j].get_name() < x[m].get_name())		//if 
                m = j;
            if (x[j].get_name() == x[m].get_name())		//if same name
            {
                if(x[j].getid() < x[m].getid())
                    m = j;
            }
        }
        swap(x[m], x[k]);
    }
    
    return;
}

int Student::getid()
{
    return id;
}

void search_name(Student students[],int size,string name) 
{
 int index=0 ;		              //index array in case of duplicates				
 //while loop that searches through names 
 int name_count=0;
for (index;index<size;index++)
{   //if names are found
	if  (students[index].get_name() == name)
	{    cout << "Name: " << students[index].get_name() << endl;
		 cout << "ID: " << students[index].getid() << endl;
		 cout << "Average: " << students[index].getavg() << " (" << students[index].getgrade_lttr() << ")" << endl;
		 name_count++;
	}	
}
//if not found
 if(name_count<1)
	{
		 cout<< "Fail. " << name << " is not enrolled in this class.\n" ;
	}
}	