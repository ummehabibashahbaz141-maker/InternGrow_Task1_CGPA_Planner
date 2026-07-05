#include<iostream>
#include<string>
#include<vector>
#include <iomanip>
using namespace std;

bool isValidGrade(string grade){
    return grade=="A"  || grade=="A-" ||
           grade=="B+" || grade=="B"  || grade=="B-" ||
           grade=="C+" || grade=="C"  || grade=="C-" ||
           grade=="D+" || grade=="D"  ||
           grade=="F";
}

// function for chnge gare into gradepoints
double gradeToPoint(string grade){
    if(grade=="A"){
        return 4.0;
    }
    else if(grade=="A-"){
        return 3.7;
    }
    else if(grade=="B+"){
        return 3.3;
    }
    else if(grade=="B"){
        return 3.0;
    }
    else if(grade=="B-"){
        return 2.7;
    }
    else if(grade=="C+"){
        return 2.3;
    }
    else if(grade=="C"){
        return 2.0;
    }
    else if(grade=="C-"){
        return 1.7;
    }
    else if(grade=="D+"){
        return 1.3;
    }
    else if(grade=="D"){
        return 1.0;
    }
    else if(grade=="F"){
        return 0.0;
    }
    else{
        cout << "Invalid Grade Entered!" << endl;
        return 0.0;
    }
}

int main(){
    string student_name, temp, cname, gd, registration_no;
    vector<string> semester_names;
    vector<double> semester_gpa;
    vector<vector<string>> courses_name;
    vector<vector<int>> credit_hours;
    vector<vector<string>> grades;
    vector<vector<double>> grade_points;
    vector<vector<string>> status;
    int semester_number, course_number, ch, grand_total_credits=0;
    double  grand_total_points=0;
    double target_cgpa, required_gpa;
    int remaining_credits;

    // input for student name
    cout<<"Enter the student name: ";
    getline(cin, student_name);

    // input for stident registration_no
    cout<<"Enter the Registration no. : ";
    getline(cin, registration_no);
    // input for semester number
    cout<<"enter the number of the semester: ";
    cin>>semester_number;

    // loop for input for the semester names
    cin.ignore();
    for(int i=1;i<=semester_number;i++){
        int total_credits = 0;
        double total_points = 0;
        cout<<"Enter the Name of the semester "<<i<<" : ";
        getline(cin, temp);
        semester_names.push_back(temp);
        vector<string> temp_courses;
        vector<int> temp_ch;
        vector<string> temp_gd;
        vector<string> temp_status;
        vector<double> temp_gp;
        cout<<"Enter the number of the courses in "<<i<<" semester: ";
        cin>>course_number;
        cin.ignore();
        // nested loop for couses detaits in per semester
        for(int j=1;j<=course_number;j++){
            cout<<"Enter the name of course "<<j<<" in semester "<<i<<" : ";
            getline(cin, cname);
            cout<<"Enter the credit_hours and grade: ";
            cin>>ch>>gd;
            while(!isValidGrade(gd)){
                cout<<"Invalid Grade! Please enter a valid grade: ";
                cin>>gd;
            }
            cin.ignore();
            temp_courses.push_back(cname);
            temp_ch.push_back(ch);
            temp_gd.push_back(gd);
            double point = gradeToPoint(gd);
            total_points += point * ch;
            total_credits += ch;
            temp_gp.push_back(point * ch);
            temp_status.push_back("Confirmed");
        }
        double gpa = 0;
        if(total_credits != 0){
           gpa = total_points / total_credits;
        }

        courses_name.push_back(temp_courses);
        credit_hours.push_back(temp_ch);
        grades.push_back(temp_gd);
        semester_gpa.push_back(gpa); 
        grade_points.push_back(temp_gp);
        status.push_back(temp_status);
        grand_total_points += total_points;
        grand_total_credits += total_credits;
    }
    double cgpa = 0;
    if(grand_total_credits != 0){
       cgpa = grand_total_points / grand_total_credits;
    }
    // Predictive Simulation Feature

    cout << "\n========== CGPA PREDICTION ==========\n";

    cout << "Enter your target CGPA: ";
    cin >> target_cgpa;

    cout << "Enter remaining credit hours: ";
    cin >> remaining_credits;

    required_gpa =((target_cgpa * (grand_total_credits + remaining_credits))- grand_total_points)/ remaining_credits;

    if(required_gpa > 4.0){
       cout << "\nTarget CGPA is not achievable.\n";
    }
    else if(required_gpa <= 0){
     cout << "\nYou have already achieved your target CGPA.\n";
    }
    else{
        cout << "\nTo achieve a CGPA of "
             << target_cgpa
             << ", you need a GPA of "
             << fixed << setprecision(2)
             << required_gpa
             << " in your remaining semesters.\n";
    }

// print all the data
cout << "\n================================================================================================================\n";
cout << "                                     STUDENT RESULT CARD\n";
cout << "================================================================================================================\n";
cout << fixed << setprecision(2);
cout << "Student Name: " << student_name << endl;
cout << "Registration No: " << registration_no << endl;
cout << "Final CGPA : " << cgpa << endl;


cout << "\n================================================================================================================\n";
cout << left
     << setw(15) << "Semester"
     << setw(60) << "Course Name"
     << setw(8)  << "CH"
     << setw(10) << "GP"
     << setw(10) << "Grade"
     << setw(15) << "Status"
     << endl;

cout << "================================================================================================================\n";

for(int i = 0; i < semester_names.size(); i++)
{
    for(int j = 0; j < courses_name[i].size(); j++)
    {
        cout << left
             << setw(15) << semester_names[i]
             << setw(35) << courses_name[i][j]
             << setw(8)  << credit_hours[i][j]
             << setw(10) << grade_points[i][j]
             << setw(10) << grades[i][j]
             << setw(15) << status[i][j]
             << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "Semester GPA: " << semester_gpa[i] << endl;
    cout << "---------------------------------------------------------------------------------------------------------------\n";
}

cout << "\n================================================================================================================\n";
cout << "FINAL CGPA: " << cgpa << endl;
cout << "================================================================================================================\n";


return 0;
}