
//***********************//
// Student Report Card //
//***********************//

#include<bits/stdc++.h>
using namespace std;

class Student{
    private:
        string name;
        int roll;
        int mark_cs;
        int mark_physics;
        int mark_math;
        int mark_english;
        int mark_chemistry;
        float percent;
        char grade;
        void calculate(); // Function for calculate grede
        
    public:
        void get_data(); // Function for getting information from student
        void show_data(); // Function for showing a student's data
        void show_tabular(); // Function for showing data in one line
        int return_roll(); // Function for returing a student's roll
    }; // Class ends here

// Global declaretion for stream object
fstream fp;
Student st;

// Function to write in file
void write_student();

// Function to read all record from file
void display_all();

// Function to read specific file from record
void display_sp();

// Function to modify record of file
void modify_record();

// Function to delete record
void delete_record();

// Function to displaly all students record
void class_result();

// Function to display result menu
void view_result();

// Entry & edit menu function
void entry_edit();

int main(){
     int choice{0};
    do{
        cout << "\n\n\n\tMAIN MENU" << endl << endl;
        cout << "\t1. RESULT MENU" << endl;
        cout << "\t2. ENTRY/EDIT MENU" << endl;
        cout << "\t3. EXIT" << endl << endl;
        here:
        cout << "\tEnter your option: ";
        cin >> choice;
        switch(choice){
        case 1:
            view_result();
            break;
        case 2:
            entry_edit();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\tInvalid input!" << endl << endl;
            goto here;
    }
    }while(choice != 3);
}

void Student :: calculate(){
    percent = (mark_cs + mark_physics + mark_math + mark_english + mark_chemistry) / 5.0;
    grade = (percent >= 60) ? 'A' : (percent >= 50) ? 'B' : (percent >= 33) ? 'C' : 'F';
}

void Student :: get_data(){
            cout << "\tEnter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "\tEnter Roll: ";
            cin >> roll;
            cout << "\tEnter marks in computer science: ";
            cin >> mark_cs;
            cout << "\tEnter marks in physics: ";
            cin >> mark_physics;
            cout << "\tEnter marks in math: ";
            cin >> mark_math;
            cout << "\tEnter marks in english: ";
            cin >> mark_english;
            cout << "\tEnter marks in chemistry: ";
            cin >> mark_chemistry;
            calculate();
    }
        
void Student :: show_data(){
    cout << "\n\tStudent's Name: " << name << endl;
    cout << "\tStudent's Roll: " << roll << endl;
    cout << "\tMark Obtained in Computer Science: " << mark_cs << endl;
    cout << "\tMark Obtained in Physics: " << mark_physics << endl;
    cout << "\tMark Obtained in Math: " << mark_math << endl;
    cout << "\tMark Obtained in English: " << mark_english << endl;
    cout << "\tMark Obtained in Chemistry: " << mark_chemistry << endl;
    cout << "\tPercentage of Student: " << setprecision(2) << percent << endl;
    cout << "\tGrade: " << grade << endl;
}
    
void Student :: show_tabular(){
    cout << "\t" << roll << setw(12) << name << setw(15) << mark_cs << setw(5) << mark_physics << setw(5) << mark_math << setw(5) << mark_english << setw(5) << mark_chemistry << setw(6) << setprecision(3) << percent << "    " << grade << endl;
}

int Student :: return_roll(){
    return roll;
}

void write_student(){
    fp.open("student.dat", ios :: out | ios :: app);
    st.get_data();
    fp.write((char*) & st, sizeof(Student));
    fp.close();
    cout << "\n\tStudent record has been created..." << endl; 
}

void display_all(){
    cout << "\n\n\t____________________________________________" << endl;
    cout << "\tShowing All Records..." << endl;
    fp.open("student.dat", ios :: in);
    while(fp.read((char*) & st, sizeof(Student))){
        st.show_data();
        cout << "\n\n\t_________________________________________" << endl;
    }
    fp.close();
}

void display_sp(int n){
    int flug{0};
    fp.open("student.dat", ios :: in);
    while(fp.read((char*) & st, sizeof(Student))){
        if(st.return_roll() == n){
            st.show_data();
            flug = 1;
        }
    }
    fp.close();
    if(flug == 0){
        cout << "\n\n\tRecord not exist..." << endl;
    }
}

void modify_record(){
    int found{0};
    cout << "\tEnter your roll: ";
    int no{};
    cin >> no;
    fp.open("student.dat", ios :: in | ios :: out);
    while(fp.read((char*) & st, sizeof(Student) && found == 0)){
        if(st.return_roll() == no){
            st.show_data();
            cout << "\tPlease enter the new details of the student: " << endl;
            st.get_data();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios :: cur);
            fp.write((char*) & st, sizeof(Student));
            cout << "\n\tRecord Updated." << endl;
            found = 1;
        }
    }
    fp.close();
    if(found == 0){
        cout << "\n\tRecord not found." << endl;
    }
}

void delete_record(){
    cout << "\n\tDelete record." << endl;
    cout << "\tPlease enter the roll no. of the student you want to delete: ";
    int no{};
    cin >> no;
    fp.open("student.dat", ios :: in | ios :: out);
    fstream fp2;
    fp2.open("temp.dat", ios :: out);
    fp.seekg(0, ios :: beg);
    while(fp.read((char*) & st, sizeof(Student))){
        if(st.return_roll() != no){
            fp.write((char*) & st, sizeof(Student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    cout << "\n\n\tRecord deleted." << endl;
}

void class_result(){
    fp.open("student.dat", ios :: in);
    if(!fp){
        cout << "\n\n\tFile couldn't be open. \n\nGo to entry menu to create file." << endl;
        cout << "\tProgram closing..." << endl;
        exit(0);
    }
    cout << "\n\n\tAll students result: "<< endl;
    cout << "\t____________________________________________________________" << endl;
    cout << "\tRoll        Name             CS   Phy  Mat  Eng  Che   %   Grade" << endl;
    while(fp.read((char*) & st, sizeof(Student))){
        st.show_tabular();
    }
    fp.close();
}

void entry_edit(){
    int choice{0};
    cout << "\n\tENTRY/EDIT MENU" << endl << endl;
    cout << "\t1. CREATE STUDENT RECORD" << endl;
    cout << "\t2. DISPLAY ALL STUDENTS RECORD" << endl;
    cout << "\t3. SEARCH FOR A STUDENT RECORD" << endl;
    cout << "\t4. MODIFY STUDENT RECORD" << endl;
    cout << "\t5. DELETE STUDENT RECORD" << endl;
    cout << "\t6. BACK TO MAIN MENU" << endl << endl;
    this_place:
    cout << "\tEnter your option: ";
    cin >> choice;
    switch(choice){
        case 1:
            write_student();
            break;
        case 2:
            display_all();
            break;
        case 3:
            int no;
            cout << "\tPlease enter roll no.: ";
            cin >> no;
            display_sp(no);
            break;
        case 4:
            modify_record();
            break;
        case 5:
            delete_record();
            break;
        case 6:
            break;
        default:
            cout << "\tInvalid input!" << endl << endl;
            goto this_place;
    }
}

void  view_result(){
    int choice{0};
    char ch;
    cout << "\n\n\tRESULT MENU" << endl << endl;
    cout << "\t1. CLASS RESULT" << endl;
    cout << "\t2. STUDENT REPORT CARD" << endl;
    cout << "\t3. BACK TO MAIN MENU" << endl;
    place:
    cout << "\tEnter your option: ";
    cin >> choice;
    switch(choice){
        case 1:
            class_result();
            break;
        case 2:
            do{
                cout << "\tEnter the roll of the student you want to know the result: ";
                int no;
                cin >> no;
                display_sp(no);
                cout << "\tDo you want to see more result?(y/n): ";
                cin >> ch;
            }while(ch == 'y' || ch == 'y');
            break;
        case 3:
            break;
        default:
            cout << "\tInvalid input!" << endl << endl;
            goto place;
    }
}
