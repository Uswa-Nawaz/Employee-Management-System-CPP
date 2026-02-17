#include<iostream>
#include<windows.h> //to add delays, and colours
#include<iomanip>   //required to set width in view tables
#include<fstream>
#include<string>    
using namespace std;

//Global, for colours
const int HEADER_COLOR = 11;  // Cyan
const int INFO_COLOR = 14;    // Yellow
const int ERROR_COLOR = 12;   // Red
const int SUCCESS_COLOR = 10; // Green
const int RESET_COLOR = 7;    // White
const int SUBHEADER_COLOR = 13; // Purple

//function prototype
//headers
void welcomesceen();
void signupheader();
void signup_ending_header();
void signinheader();
void admin_dashboard_header();
void employee_dashboard_header();
void emp_password_update();
void add_employee_header();
void search_employee_header();
void delete_employee_header();
void update_employee_header();
void globalHeader();

//for better visuals
void loadingEffect(string message);
void successMessage(string message);
void errorMessage(string message);
//------------------------------ 
void showInterface(string mode);  // instuctions 
void setColor(int color);         //For colours
//------------------------------
//for file handling
void saveEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int empCount);
bool loadEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int &empCount);
void saveAdmin(string username, string password);
bool loadAdmin(string &user, string &pass);
//------------------------------
int roleSelection_and_validation();
int admin_choice_dashboard(); 
int employee_choice_dashboard();
//------------------------------
//mutual validation
bool isEmpty(string text);
bool hasSpace(string text); //for passwords (REGISTRATION, LOGIN, ID )
void pause(); //For employee side
int findEmployeeIndex(string empID[], int empCount, string targetID);
bool isStorageEmpty(int empCount);
//---------------------------
//Validations for signin signup
bool userNameChecker(string u);
bool passwordChecker(string p);
//signup and login function's prototype
void signUp(string &username,string &password);
bool signIn(string username,string password);
int emp_signIn(string empID[], string empPassword[], int empCount);
//------------------------------
//Validations for data of admin and employee side
bool validempID(string id, string empID[], int empCount);
bool validName(string name);
bool validsalary(int salaryValue);
//-----------------------------
//Working of admin 
void addEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int &empCount,int MAX_EMP);
void viewEmployee(string empID[], string empName[], string empDepartment[], int empsalary[],int empCount);
void searchEmployee(string empID[], string empName[], string empDepartment[], int empsalary[], int empCount);
void deleteEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int &empCount);
void updateEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int empCount);
//working of employee
void displayIDCard(string empName[], string empID[], string empDepartment[], int index);
void displayCompanyRoster(string empName[], string empDepartment[], int empCount);
void salaryCalculator(string empName[], string empID[], int empsalary[], int index);
void UpdatePassword(string empID[], string empPassword[],string empName[],string empDepartment[],int empsalary[],int empCount,int index);


int main()
{

    const int MAX_EMP=50; // maximum no. of employees we can store
    //arrays storing employee data
    string empID[MAX_EMP];
    string empName[MAX_EMP];
    string empDepartment[MAX_EMP];
    string empPassword[MAX_EMP];
    int empsalary[MAX_EMP];
    int empCount=0;   //tracks how many employees are added

    //Seperate variables to store data of admin
    string saved_Admin_UserName="";
    string saved_Admin_Password="";

    //function call of file handling
    loadAdmin(saved_Admin_UserName, saved_Admin_Password);
    loadEmployee(empID, empPassword, empName, empDepartment, empsalary, empCount);
    //function calling for welcome
    welcomesceen();
    cout<<"----------------------------------"<<endl;
    cout<<"    Press Enter to continue...    "<<endl;
    cin.get();
    while(true)
    {
        int role;
        role=roleSelection_and_validation();
        if(role==1)
        {
            if(saved_Admin_UserName=="")
            {
            signUp(saved_Admin_UserName, saved_Admin_Password);
            }
            if(signIn(saved_Admin_UserName, saved_Admin_Password))
            {
                setColor(SUCCESS_COLOR);
                cout << "\n--- ADMIN GRANTED ACCESS ---"<<endl;
                setColor(RESET_COLOR);
                Sleep(500);
                //it runs until the use chooses logout
                while(true)
                {
                    int action=admin_choice_dashboard();
                    if(action==1)
                    {
                        addEmployee(empID, empPassword, empName, empDepartment, empsalary, empCount, MAX_EMP);
                    }
                    else if(action==2)
                    {
                        viewEmployee(empID, empName, empDepartment, empsalary, empCount);
                    }
                    else if(action==3)
                    {
                        searchEmployee(empID, empName, empDepartment, empsalary, empCount);
                    }
                    else if(action==4)
                    {
                        deleteEmployee(empID, empPassword, empName, empDepartment, empsalary, empCount);
                    }
                    else if(action==5)
                    {
                        updateEmployee(empID,empPassword, empName, empDepartment, empsalary, empCount);
                    }
                    else if(action==6)
                    {
                        cout << "\n==========================================" << endl;
                        Sleep(50);
                        cout << "       SHUTTING DOWN SECURE SESSION       " << endl;
                        Sleep(50);
                        cout << "==========================================" << endl;
                        Sleep(50);
                        loadingEffect("Syncing data and clearing cache");
                        Sleep(1500);
                        break; //goes back to role selection
                    }
                }
                //clear screen after logout
                system("cls");
            }
            else
            {
                setColor(ERROR_COLOR);
                cout << "\n--- ADMIN ACCESS DENIED---"<<endl;
                setColor(RESET_COLOR);
                pause();
            }
        }
        else if(role==2)
        {
            if(empCount==0)
            {
                setColor(ERROR_COLOR);
                cout<<"\n[ERROR]: No employees are currently registered in the system"<<endl;
                setColor(RESET_COLOR);
                cout<<"Please Contact Admin to register your account."<<endl;
                Sleep(1500);
            }
            else
            {
               int index=emp_signIn(empID, empPassword, empCount);
                if(index!=-1)
                {
                    while(true)
                    {
                        int action=employee_choice_dashboard();
                        if(action==1)
                        {
                            displayIDCard(empName, empID, empDepartment, index);
                        }
                        else if(action==2)
                        {
                            displayCompanyRoster(empName, empDepartment, empCount);
                        }
                        else if(action==3)
                        {
                            salaryCalculator(empName, empID, empsalary, index);
                        }
                        else if(action==4)
                        {
                            UpdatePassword(empID, empPassword, empName, empDepartment,empsalary, empCount,index);
                        }
                        else if(action==5)
                        {
                            cout<<"Logging out... returning to Role selection."<<endl;
                            cout<<"--------------------------------------------"<<endl;
                            Sleep(500);
                            break;
                        }
                    }
                }
            }
        }
        else if(role==3)
        {
            char confirm;
            setColor(INFO_COLOR);
            cout<<"Are you sure? (Y/N): ";
            setColor(RESET_COLOR);
            cin>>confirm;
            if(confirm == 'Y' || confirm == 'y')
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
}
//function that shows the admin functionalities and validate input
int admin_choice_dashboard()
{
    int choice=0;
    while(true)
    {
        system("cls");
        globalHeader();
        //function calling of header
        admin_dashboard_header();
        cout<<"1. Add Employee\n";
        cout<<"2. View Employee\n";
        cout<<"3. Search Employee\n";
        cout<<"4. Delete Employee\n";
        cout<<"5. Update Employee\n";
        cout<<"6. logout\n";
        cout<<"Enter your choice: ";
        
        //(validation here) the input should be a number 1-6
        if(cin>>choice)
        {
            if(choice==1 || choice==2 || choice==3 || choice==4 || choice==5 || choice==6)
            {
                return choice;
            }
            else
            {
                setColor(ERROR_COLOR);
                cout<<"[Error]: Invalid menu option selected. Please enter a valid choice (1-6)."<<endl;
                Sleep(2000);
                setColor(RESET_COLOR);
            }
        }
        else 
        {
            setColor(ERROR_COLOR);
            cout<<"[Error]: Letters or symbols are not accepted. Please enter a number (1-6).";
            setColor(RESET_COLOR);
            Sleep(2000);
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
}

//function that shows the employee functionalities and validate input
int employee_choice_dashboard()
{
    int choice=0;
    while(true)
    {   system("cls");
        globalHeader();
        employee_dashboard_header();
        cout<<"\n1. View Digital ID Card"<<endl;
        cout<<"2. View Company Roster\n"; //only entered people's name and departments
        cout<<"3. Salary slip\n";
        cout<<"4. Update Secuity Password\n";
        cout<<"5. Logout\n";
        cout<<"Enter Choice: ";
        //(validation here) the input should be a number 1-5
        if(cin>>choice)
        {
            if(choice==1 || choice==2 || choice==3 || choice==4 || choice==5)
            {
                return choice;
            }
            else
            {
                setColor(ERROR_COLOR);
                cout<<"[Error]: Invalid menu option selected. Please enter a valid choice (1-5)."<<endl;
                setColor(RESET_COLOR);
            }
        }
        else 
        {
            setColor(ERROR_COLOR);
            cout<<"[Error]: Letters or symbols are not accepted. Please enter a number (1-5).";
            setColor(RESET_COLOR);
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
}


//Role selection, if user is admin or an employee
int roleSelection_and_validation()
{
    int choice;
    while(true) //keeps the user traped here until the valid input in given, i used it for validation
    {
    system ("cls"); //clear screen everytime error happen
    globalHeader();
    cout<<"\n";
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    cout<<"           R O L E  S E L E C T I O N           "<<endl;
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);

    setColor(INFO_COLOR);
    cout<<"1. Admin "<<endl; //he has full access
    cout<<"2. Employee"<<endl; //gets limited access
    cout<<"3. Exit system "<<endl;
    cout<<"\n"<<endl;
    cout<<"Enter your choices (1-3): ";
    //(validation here) the number should be between 1-3
    if(cin>>choice)
    {
        if(choice==1 || choice==2 || choice==3)
        {
        return choice;
        }
        else
        {
            setColor(ERROR_COLOR);
            cout<<"[Error]: Invalid menu option selected. Please enter a valid choice (1-3)."<<endl;
            setColor(RESET_COLOR);
            Sleep(1000);
        }
    }
    else 
    {
        setColor(ERROR_COLOR);
        cout<<"[Error]: Letters or symbols are not accepted. Please enter a number (1-3).";
        setColor(RESET_COLOR);
        Sleep(1000);
        cin.clear();
        cin.ignore(100,'\n');
    }
    }

}

//Now two functions that are gonna check the password and username correctness
//function to check if the username is valid
bool userNameChecker(string u)
{
    //To check of the if the length is between 4 and 15
    if(!(u.length()>=4 && u.length()<15))
    {
        return false;
    }
    //To check if the first letter is capital
    if(!(u[0]>='A' && u[0]<='Z'))
    {
        return false;
    }
    //to check if it has space
    if(hasSpace(u)==true)
    {
        return false;
    }
    //to check if the entered name has no. or special character
    if(!(validName(u)==true))
    {
        return false;
    }
        //If it get past the above all conditions, then it will return true
        return true;
}

//function to check if the entered password is valid 
bool passwordChecker(string p)
{
    //to check of the if the length is geater than 8
    if(p.length()<8)
    {
       return false;
    }
    bool have_number=false;
    bool have_letter=false;
    bool have_specialChar=false;

    string specialChar="!@#$%^&*()-_=+[{]};:,.<>/?";
    for(int i=0; i<p.length(); i++)
    {
        //spaces are not allowed
        if(hasSpace(p)==true)
        {
            return false; 
        }
        //To check if it has atleast one number
        if(p[i]>='0' && p[i]<='9')
        {
            have_number=true;
        }

        //To check of it has atleast one letter
        if((p[i]>='A' && p[i]<='Z') || (p[i]>='a' && p[i]<='z'))
        {
            have_letter=true;
        }

        //to check if there is a special character in the password
        for(int j=0; j<specialChar.length(); j++) //compare that password character with each special character from string in this function
        {
            if(p[i]==specialChar[j])
            {
                have_specialChar=true;
            }
        }
    }
    return(have_letter && have_number && have_specialChar);
}

//signup function
void signUp(string &username,string &password)
{
    //local variables to temporarily store values
    string tempU;
    string tempPw;

    bool flag=false;
    cin.ignore();

    //------USERNAME SECTION------
    while(flag==false)
    {
        system("cls");
        //function calling of global header
        globalHeader(); 
        //function calling of entering signup header
        signupheader();
        //function calling of instuctions
        showInterface("ADMIN_SIGNUP");
        cout<<"Enter Username: ";
        getline(cin, tempU);
        if(userNameChecker(tempU)==true)
        {
            username=tempU;
            flag=true;
            break;
        }
        else
        {
            setColor(ERROR_COLOR);
            cout<<"Error: Invalid Fomat."<<endl;
            setColor(RESET_COLOR);
            cout<<"You entered "<<tempU<<". Please try again..."<<endl;
            Sleep(1000);
        }
    }

     //from the previous loop the flag is true, so reseting it to false for the next loop execution
    flag=false;

    //------PASSWORD SECTION-----
    while(flag==false)
    {
        system("cls");  //clears the sceen
        //---(reprint so it feels static)---
        globalHeader();
        signupheader(); //reprint the header
        showInterface("ADMIN_SIGNUP"); //reprint instruction
        cout<<"Username: "<<username<<"  [SAVED]"<<endl; //Reprinting this too
        //----------------------------------
        cout<<"Enter Password: "; // so this become visually nice, and stay in the same spot  
        getline(cin, tempPw);
        if(passwordChecker(tempPw)==true)
        {
            password=tempPw;
            flag=true;
            cout<<"\nRegistration Complete." << endl;
            //function calling of exiting signup header
            signup_ending_header();
            cout<<"----------------------------------"<<endl;
            cout<<"    Press Enter to continue...    "<<endl;
            cin.get();

        }
        else
        {
            setColor(ERROR_COLOR);
            cout<<"Error: Invalid Format."<<endl;
            setColor(RESET_COLOR);
            cout<<"You entered "<<tempPw<<". Please try again..."<<endl;
            Sleep(1500);  // Without this cls at the top wipes the error instantly
        }

    }
    saveAdmin(username, password);
}

//signIn function for admin it return bool type value
//checks two vaiables
bool signIn(string username,string password)
{
    string inputU;
    string inputPw;

    int tries=0;
    cin.ignore(100, '\n'); 
    while(tries<3)
    {
    system("cls");
    globalHeader();
    //function calling of signin header
    signinheader();
    //calling fo instructions 
    showInterface("ADMIN_LOGIN");
    cout<<"Enter Username: ";
    getline(cin, inputU);
    cout<<"Enter password: ";
    getline(cin, inputPw);

        if(inputU==username && inputPw==password)
        {
            loadingEffect("Authenticating Credentials");
            successMessage("Admin Identity Verified. Welcome !");
            Sleep(1000);
            return true;
        }
        else
        {
            loadingEffect(" Please Try Again");
            errorMessage("Incorrect Username or Password !!");
            tries++;
            cout<<"(Attempts remaining: "<<3-tries<<" )"<<endl;
            Sleep(2000);
        }
        
    }
    return false;
}

//signin function for employee it return index
//checks two arrays
int emp_signIn(string empID[], string empPassword[], int empCount)
{
    string req_ID;
    string req_pass;
    int tries=0;

    cin.ignore(); //when it was inside the while it ignored the 1st char of ID i 2,3..attempt
    while(tries<3)
    {
        system("cls");
        globalHeader();
        //calling the header
        signinheader();
        //function calling for instuctions
        showInterface("EMP_LOGIN");
        cout<<"Enter your ID:";
        getline(cin, req_ID);
        cout<<"Enter your Password: ";
        getline(cin, req_pass);
        int found_index=findEmployeeIndex(empID, empCount, req_ID);
        if(found_index!=-1 && req_pass == empPassword[found_index])
        {
            loadingEffect("Authenticating Credentials");
            successMessage("Employee Identity Verified. Welcome !");
            Sleep(1000);
            return found_index;
        }
        else
        {
            loadingEffect(" Please Try Again...");
            errorMessage("Incorrect ID or Password !!");
            tries++;
            cout<<"(Attempts remaining: "<<3-tries<<" )"<<endl;
            Sleep(2500);
        }
    }
    return -1; //failed after 3 tries
}

//---------------------------
//---------------------------
void pause()
{
    //This function for employee side
    cout<<"----------------------------------"<<endl;
    cout<<"    Press Enter to continue...    "<<endl;
    cout<<"-----------------------------------"<<endl;
    cin.ignore(100, '\n'); //important
    cin.get();    // Waits for a single Enter key press
}
//It checks if there is any employee records
bool isStorageEmpty(int empCount)
{
    if(empCount==0)
    {
        setColor(ERROR_COLOR);
        cout << "[ERROR]: No employee records found in the system!\n";
        setColor(RESET_COLOR);
        cout << "Press Enter to go back...";
        cin.ignore(100, '\n');
        cin.get();
        return true;
    }
    return false;
}
//Function that return the index for the required employee
int findEmployeeIndex(string empID[], int empCount, string targetID)
{
    for(int i=0; i<empCount; i++)
    {
        if(empID[i]==targetID)
        {
            return i; //because we want the no. we found this id at
        }
    }
    return -1; 
}
//--------validation functions---------

//space validation
bool hasSpace(string text) //for Passwords
{
    if(text=="")
    {
        return false;
    }
    for(int i=0; i<text.length(); i++)
    {
        if(text[i]==' ')
        {
            return true; //found a space
        }
    }
    return false; //No spaces found
}

bool isEmpty(string text)
{
    //check if the string is totally empty
    if(text=="")
    {
        return true;
    }
    //check if the string is ONLY SPACEs
    for(int i=0; i< text.length(); i++)
    {
        if(text[i]!=' ')
        {
            return false;
        }
    }
    return true;
}
//Validation (letters only)
bool validName(string name)  //allow space
{
    //check if it is empty
    if(isEmpty(name))
    {
        return false;
    }
    //check it should be only alphabet, allows a-z and A-Z
    bool isletter;
    bool isSpace;
    for(int i=0; i<name.length(); i++)
    {
        bool isletter=(name[i]>='A' && name[i]<='Z') || (name[i]>='a' && name[i]<='z');
        bool isSpace=(name[i] == ' ');
        //if its not a capital or small letter, its definitely a special character or a number
        if(!isletter && !isSpace)
        {
            return false;
        }
    }
    //If it get past the above conditions, then it will return true,
    return true; //means all letters
}

bool validempID(string id, string empID[], int empCount)
{
    //should not be empty
    if(isEmpty(id))
    {
        
        errorMessage("ID cannot be empty!");
        return false;
    }
    //should have no space
    if(hasSpace(id))
    {
        errorMessage("ID cannot contain spaces!");
        return false;
    }
    //to check if it is unique
    if(findEmployeeIndex(empID, empCount, id)!=-1)
    {
        setColor(ERROR_COLOR);
        cout<<"[ERROR]: ID '"<<id<<"' is already assigned to another employee."<<endl;
        setColor(RESET_COLOR);
        return false;
    }
    return true;
}
bool validsalary(int salaryValue)
{

    if(salaryValue<0)
    {
        setColor(ERROR_COLOR);
        cout<<"Number cannot be negative !!"<<endl;
        setColor(RESET_COLOR);
        return false;
    }
    return true;
}
//FOR ADMIN, this function just display the menu and check its input validation

void addEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int &empCount,int MAX_EMP)
{
    string checkID;
    if(empCount>=MAX_EMP)
    {
        setColor(ERROR_COLOR);
        cout<<"[ERROR]: Storage full !!\n";
        setColor(RESET_COLOR);
        pause();
        return;
    }
    string tempID, tempPass, tempName, tempDept;
    cin.ignore();
    //INPUT AND VALIDATION CALLING + reprinting to make it visually nice
    while(true)
    {
        //-------------ID SECTION------------
        system("cls");
        globalHeader();
        //function calling for adding new employee header 
         add_employee_header();
         //function fall of instructions
        showInterface("ADD_EMP");
        cout<<"Enter employee ID: ";
        getline(cin, tempID);
        if(validempID(tempID, empID, empCount))
        {
            empID[empCount]=tempID;
            break;
        }
        else
        {
            Sleep(1000);  // Wait so user sees the error from validempID function
        }
    }
    while(true)
    {
        //------------PASSWORD SECTION------------

        //-----------(reprinting to make it stationary)-----------
        system("cls");
        globalHeader();
        add_employee_header();
        //function fall of instructions
        showInterface("ADD_EMP");
        cout<<"\nEmployee ID: "<<tempID<<"  [SAVED]"<<endl;
        //--------------------------------------------------------
        cout<<"Enter employee login Password: ";
        getline(cin, tempPass);
        if(passwordChecker(tempPass))
        {
           empPassword[empCount]=tempPass;
            break;
        }
        else
        {
            errorMessage("Invalid Password Format.");
            Sleep(1000);
        }
    }
    while(true)
    {
        //-----------NAME SECTION-------------
        //-----------(reprinting to make it stationary)-----------
        system("cls");
        globalHeader();
        add_employee_header();
        //function fall of instructions
        showInterface("ADD_EMP");
        cout<<"\nEmployee ID: "<<tempID<<"  [SAVED]"<<endl;
        cout<<"Password: ********  [SAVED]"<<endl;
        //--------------------------------------------------------
        cout<<"Enter employee name: ";
        getline(cin, tempName);
        if(validName(tempName))
        {
            empName[empCount]=tempName;
            break;
        }
        else
        {
            setColor(ERROR_COLOR);
            cout << "[Error]: Name should only contain letters." << endl;
            setColor(RESET_COLOR);
            Sleep(1000);
        }
    }
    while(true)
    {
        //----------DEPARTMENT SECTION------------
        //-----------(reprinting to make it stationary)-----------
        system("cls");
        globalHeader();
        add_employee_header();
        //function fall of instructions
        showInterface("ADD_EMP");
        cout<<"\nEmployee ID: "<<tempID<<"  [SAVED]"<<endl;
        cout<<"Password: ********  [SAVED]"<<endl;
        cout<<"Name: "<<tempName<<"  [SAVED]"<<endl;
        //-------------------------------------------------------
        cout<<"Enter employee Department: ";
        getline(cin, tempDept);
        if(validName(tempDept))
        {
            empDepartment[empCount]=tempDept;
            break;
        }
        else
        {
            setColor(ERROR_COLOR);
            cout<<"[Error]: Invalid Department name."<<endl;
            setColor(RESET_COLOR);
            Sleep(1000);
        }
    }
    while(true)
    {
        //-----------SALARY SECTION-----------
        //-----------(reprinting to make it stationary)-----------
        system("cls");
        globalHeader();
        add_employee_header();
        //function fall of instructions
        showInterface("ADD_EMP");
        cout<<"\nEmployee ID: "<<tempID<<"  [SAVED]"<<endl;
        cout<<"Password: ********  [SAVED]"<<endl;
        cout<<"Name:"<<tempName<<"  [SAVED]"<<endl;
        cout<<"Dept:"<<tempDept<<" [SAVED]"<<endl;
        //-------------------------------------------------------
        cout<<"Enter salary: ";
        if(cin>>empsalary[empCount])
        {
            if(validsalary(empsalary[empCount])==true)
            {
                break;
            }
            else
            {
                setColor(ERROR_COLOR);
                cout << "[Error]: Salary cannot be negative!" << endl;
                setColor(RESET_COLOR);
                Sleep(1000);
            }

        }
        else 
        {
            setColor(ERROR_COLOR);
            cout<<"[Error]: Letters or symbols are not accepted. Please enter a number.";
            setColor(RESET_COLOR);
            Sleep(1000);
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
    loadingEffect("Uploading to Database");
    successMessage("Employee Record Created Successfully");
    Sleep(1500);
    empCount++;  //most impotant part
    cin.ignore(); // Clears the newline from salary input
    cout<<"----------------------------------"<<endl;
    cout<<"    Press Enter to continue...    "<<endl;
    cin.get();

    saveEmployee(empID, empPassword, empName, empDepartment, empsalary, empCount);
}

void viewEmployee(string empID[], string empName[], string empDepartment[], int empsalary[], int empCount)
{
    system("cls");
    globalHeader();
    if(isStorageEmpty(empCount))
    {
        return;
    }
    cout<<"\n";
    setColor(INFO_COLOR);
    cout << "========================================================================\n";
    cout << "                    E M P L O Y E E   D A T A B A S E                   \n";
    cout << "========================================================================\n";
    cout<<"Total employees: "<<empCount<<"\n\n";
    cout << "------------------------------------------------------------------------" << endl;
    //using setw() to define the heades with fixed width, so make the table aligned
    cout<<left<<setw(8)<<"S.No"<<setw(12)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Department"<<setw(10)<<"Salary"<<endl;
    cout << "------------------------------------------------------------------------" << endl;
    for(int i=0; i<empCount; i++)
    {
        cout<<left<<setw(8)<<i+1<<setw(12)<<empID[i]<<setw(20)<<empName[i]<<setw(20)<<empDepartment[i]<<setw(10)<<empsalary[i]<<"\n";
    }
    cout << "========================================================================\n";
    setColor(RESET_COLOR);

    cin.ignore(100, '\n'); 
    cout << "Press Enter to return to Dashboard...";
    cin.get();
}

void searchEmployee(string empID[], string empName[], string empDepartment[], int empsalary[], int empCount)
{
    system("cls");
    globalHeader();
    //function calling of header
    search_employee_header();
    if(isStorageEmpty(empCount))
    {
        return;
    }
    string id;
    cin.ignore(100,'\n');
    cout<<"Enter employee ID to search: ";
    getline(cin,id);

    int index=findEmployeeIndex(empID, empCount, id); 
    if(index!=-1)
    {
        setColor(INFO_COLOR);
       cout<<"\n--- EMPLOYEE FOUND ---\n";
       cout<<"Name: "<<empName[index]<<endl;
       cout<<"ID: "<<empID[index]<<endl;
       cout<<"Dept: "<<empDepartment[index]<<endl;
       cout<<"Salary: "<<empsalary[index]<<endl;
       cout << "----------------------\n";
       setColor(RESET_COLOR);
    }
    else
    {
        errorMessage("ID is not in the system.");
    }
    cout<<"----------------------------------"<<endl;
    cout<<"    Press Enter to continue...    "<<endl;
    cin.get();
}

void deleteEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int &empCount)
{
    system("cls");
    globalHeader();
    delete_employee_header();
    if(isStorageEmpty(empCount))
    {
        return;
    }

    string id;
    cin.ignore();
    cout<<"Enter employee ID to delete: ";
    getline(cin,id);
    int victim=findEmployeeIndex(empID, empCount, id);
    if(victim!=-1)
    {
        setColor(ERROR_COLOR);
        cout<<"\n [WARNING]: Deleting record for "<<empName[victim]<<"..."<<endl;
        loadingEffect("Wiping Data Clusters");
        setColor(RESET_COLOR);

        for(int j=victim; j< empCount-1; j++)
        {
            empID[j]=empID[j+1];
            empName[j]=empName[j+1];
            empDepartment[j] = empDepartment[j+1];
            empsalary[j]=empsalary[j+1];
            empPassword[j]=empPassword[j+1];
        }
        empCount--;
        //function caling of file handling
        saveEmployee(empID, empPassword, empName, empDepartment, empsalary, empCount);
        successMessage("Record Deleted Permanently");

    }
    else
    {
       errorMessage("Employee ID not found in system");
    }
    cin.ignore();
    cout<<"----------------------------------"<<endl;
    cout<<"    Press Enter to continue...    "<<endl;
    cin.get();
}
void updateEmployee(string empID[], string empPassword[], string empName[], string empDepartment[], int empsalary[], int empCount)
{
    system("cls");
    globalHeader();
    //function calling of header
    update_employee_header();
    //data is only being edited not resized so thats why & in not used here with empCount
    if(isStorageEmpty(empCount))
    {
        return;
    }

    string id;
    cin.ignore(100, '\n');

    cout << "Enter employee ID to Update: ";
    getline(cin, id);

    int index = findEmployeeIndex(empID, empCount, id);
    if(index != -1)
    {
        setColor(INFO_COLOR);
        cout << "\n-----Employee found-----\n";
        cout << "Current name: " << empName[index] << endl;
        cout << "Current Dept: " << empDepartment[index] << endl;
        cout << "Current salary: " << empsalary[index] << endl;
        setColor(RESET_COLOR);
        cout<<"-------------------------"<<endl;
        cout<<"Press enter to continue"<<endl;
        cin.ignore();
        //updating data
        while(true)
        {
            //---------NAME UPDATE-------
            //----(reprinting to the data stay on top)----
            system("cls");
            globalHeader();
            update_employee_header();
            cout << "\n>>> UPDATING RECORD FOR ID: " << empID[index] << " <<<" << endl;
            cout << "Current Name: " << empName[index] << endl;
            cout << "------------------------------------------------" << endl;
            //----------------------------------------------
            string tempName;
            cout << "\nEnter new name: ";
            getline(cin, tempName);
            if(validName(tempName))
            {
                empName[index] = tempName;
                break;
            }
            else
            {
                setColor(ERROR_COLOR);
                cout << "[Error]: Invalid Format. Try again..." << endl;
                setColor(RESET_COLOR);
                Sleep(1500);
            }
        }
        
        while(true)
        {
            //------DEPARTMENT UPDATE-------
            //----(reprinting to the data stay on top)----
            system("cls");
            globalHeader();
            update_employee_header();
            cout << "\n>>> UPDATING RECORD FOR ID: " << empID[index] << " <<<" << endl;
            cout << "Name updated to: " << empName[index] << "  [SAVED]" << endl; // Show progress
            cout << "Current Dept: " << empDepartment[index] << endl;
            cout << "------------------------------------------------" << endl;
            //---------------------------------------------
            string tempDept;
            cout << "\nEnter new department: ";
            getline(cin, tempDept);
            if(validName(tempDept)) // Reusing validName for department
            {
                empDepartment[index] = tempDept;
                break;
            }
            else
            {
                cout << "[Error]: Invalid Format. Try again..." << endl;
                Sleep(1000);
            }
        }

        while(true)
        {
            //-------SALARY UPDATE----------
            //--------(reprinting to the data stay on top)------
            system("cls");
            globalHeader();
            update_employee_header();
            cout << "\n>>> UPDATING RECORD FOR ID: " << empID[index] << " <<<" << endl;
            cout << "Name updated to: " << empName[index] << "  [SAVED]" << endl; // Show progress
            cout << "Dept Updated to: " << empDepartment[index] <<"  [SAVED]" << endl;
            cout << "Current Salary: " << empsalary[index] << endl;
            cout << "------------------------------------------------" << endl;
            //---------------------------------------------
            cout << "\nEnter new Salary: ";
            if(cin >> empsalary[index])
            {
                // Passing the actual value to your validation
                if(validsalary(empsalary[index]) == true)
                {
                    break;
                }
                else
                {

                    Sleep(1000);
                }
            }
            else 
            {
                cout << "[Error]: Letters or symbols are not accepted. Please enter a number." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                Sleep(1000);
            }
        } // End of salary while loop

        successMessage("Employee Profile Updated Successfully!");
        cin.ignore(100, '\n'); 
    }
    else
    {
        errorMessage("Employee ID not found.");
        cin.ignore(100, '\n');
    }
    cout<<"----------------------------------"<<endl;
    cout<<"    Press Enter to continue...    "<<endl;
    cin.get();
    saveEmployee(empID, empPassword, empName, empDepartment, empsalary, empCount);
}



void displayIDCard(string empName[], string empID[], string empDepartment[], int index)
{
    system("cls");
    globalHeader();
    cout<<"\n";
    setColor(HEADER_COLOR);
    cout<<"\n\t+---------------------------------------+"<<endl;
    cout<<"\t|            OFFICIAL ID CARD           |"<<endl;
    cout<<"\t+---------------------------------------+"<<endl;
    setColor(RESET_COLOR);
    cout<<"\t| NAME: " << left << setw(32)<<empName[index]<<"|"<<endl;
    cout<<"\t| ID:   " << left << setw(32)<< empID[index] << "|"<<endl;
    cout<<"\t| DEPT: " << left << setw(32)<<empDepartment[index]<<"|"<<endl;
    cout<<"\t| STATUS: ACTIVE                        |"<<endl;
    setColor(HEADER_COLOR);
    cout<<"\t+---------------------------------------+"<<endl;
    pause();
}

void displayCompanyRoster(string empName[], string empDepartment[], int empCount)
{
    system("cls");
    globalHeader();
    cout<<"\n";
    setColor(SUBHEADER_COLOR);
    cout << "====================================================================\n";
    cout << "                C O M P A N Y   D I R E C T O R Y                   \n";
    cout << "====================================================================\n";
    setColor(RESET_COLOR);
    // Table Headers
    cout << left << setw(10) << "S.No" << setw(22) << "Employee Name" << setw(20) << "Department" << setw(15) << "Status" << endl;
    setColor(SUBHEADER_COLOR);
    cout << "--------------------------------------------------------------------\n";
    setColor(RESET_COLOR);
    for(int i=0; i<empCount; i++)
    {
        string status;
        //enhancement for this table
        if(i%2==0)
        {
            status="Available";
        }
        else
        {
            status="In Meeting";
        }
        cout<<left<<setw(10)<<i+1<<setw(22)<<empName[i]<<setw(20)<<empDepartment[i]<<setw(15)<<status<<endl;
    }
     setColor(SUBHEADER_COLOR);
    cout << "====================================================================\n";
    cout << "Total Staff Members: " << empCount << endl;
    setColor(RESET_COLOR);
    pause();
}

void salaryCalculator(string empName[], string empID[], int empSalary[], int index)
{
    system("cls");
    globalHeader();
    cout<<"\n";
    double tax;
    tax=empSalary[index]*0.07;
    double netPay = empSalary[index] - tax;
    setColor(SUBHEADER_COLOR);
    cout<<"\n===================================================="<<endl;
    cout<<"              OFFICIAL SALARY RECEIPT               "<<endl;
    cout<<"===================================================="<<endl;
    setColor(RESET_COLOR);
    cout<<" Employee Name : " << left << setw(32) << empName[index]<<endl;
    cout<<" Employee ID   : " << left << setw(32) << empID[index]<<endl;
    setColor(SUBHEADER_COLOR);
    cout<<"----------------------------------------------------"<<endl;
    cout<<left << setw(30) << " DESCRIPTION" << " | " << "AMOUNT (PKR)"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    setColor(RESET_COLOR);
    cout<<" " << left << setw(29) << "Monthly Gross Salary" << " | "<<empSalary[index] << endl;
    setColor(ERROR_COLOR);
    cout<<" " << left << setw(29) << "Income Tax (7%)" << " | "<<tax<<endl;
    setColor(RESET_COLOR);
    setColor(SUBHEADER_COLOR); 
    cout<<"----------------------------------------------------"<<endl;
    setColor(RESET_COLOR);
    setColor(SUCCESS_COLOR);
    cout<<" " << left << setw(29) << "NET TAKE-HOME PAY" << " | "<<netPay<<endl;
    setColor(RESET_COLOR);
    setColor(SUBHEADER_COLOR);
    cout<<"===================================================="<<endl;
    cout<<" Status: PROCESSED SECURELY" << endl;
    cout<<"===================================================="<<endl;
    setColor(RESET_COLOR);
    pause();
}

void UpdatePassword(string empID[], string empPassword[],string empName[],string empDepartment[],int empsalary[],int empCount,int index)
{

    system("cls");
    globalHeader();
    emp_password_update();
    cout<<"\n";
    cin.ignore();
    while(true)
    {
        string newPass;
        cout<<"Enter new Password:";
        getline(cin, newPass);
        if(passwordChecker(newPass))
        {
            empPassword[index]=newPass;
            break;
        }
        else
        {
            setColor(ERROR_COLOR);
            cout << "\n[ERROR]: Password must be 8+ chars with number & special char." << endl;
            setColor(RESET_COLOR);
        }
    }
    setColor(SUCCESS_COLOR);
    cout << "\n[SUCCESS]: Password updated securely." << endl;
    setColor(RESET_COLOR);
    pause();
}

//-----USEFUL FUNCTION------
void loadingEffect(string message)
{
    cout<<"\n "<<message;
    for(int i = 0; i < 3; i++)
    {
        Sleep(300);
        cout << ".";
    }
    cout << endl;
}
void successMessage(string message)
{
    setColor(SUCCESS_COLOR);
    cout << "\n==========================================" << endl;
    cout << " [SUCCESS]: " << message << endl;
    cout << "==========================================" << endl;
    Sleep(1000);
    setColor(RESET_COLOR);
}
void errorMessage(string message)
{
    setColor(ERROR_COLOR);
    cout << "\n==========================================" << endl;
    cout << " [ERROR]: " << message << endl;
    cout << "==========================================" << endl;
    Sleep(1000);
    setColor(RESET_COLOR);
}

//----DESIGNINGS----
//welcome function
void welcomesceen()
{
    setColor(HEADER_COLOR);
    cout << "        ================================================================================\n";
    Sleep(50);
    cout << "        ||                                                                            ||\n";
    Sleep(50);
    cout << "        ||    ##      ##  #######  ##         ####     #####   ##     ##  #######     ||\n";
    Sleep(50);
    cout << "        ||    ##      ##  ##       ##        ##       ##   ##  ###   ###  ##          ||\n";
    Sleep(50);
    cout << "        ||    ##  ##  ##  #####    ##       ##        ##   ##  ## ### ##  #####       ||\n";
    Sleep(50);
    cout << "        ||    ##  ##  ##  ##       ##        ##       ##   ##  ##  #  ##  ##          ||\n";
    Sleep(50);
    cout << "        ||    ####  ####  #######  #######    ####     #####   ##     ##  #######     ||\n";
    Sleep(50);
    cout << "        ||                                                                            ||\n";
    Sleep(50);
    cout << "        ||                                  * TO *                                    ||\n";
    Sleep(50);
    cout << "        ||                                                                            ||\n";
    Sleep(50);
    cout << "        ||                    +----------------------------------+                    ||\n";
    Sleep(50);
    cout << "        ||                    |   EMPLOYEE MANAGEMENT SYSTEM     |                    ||\n";
    Sleep(50);
    cout << "        ||                    +----------------------------------+                    ||\n";
    Sleep(50);
    cout << "        ||                                                                            ||\n";
    Sleep(300);
    cout << "        ================================================================================\n";
    setColor(RESET_COLOR);
    Sleep(1000);
    cout << "\n";

    
}
//signup header functionS
void signupheader()
{
    setColor(SUBHEADER_COLOR);
    cout <<"==========================================" << endl;
    cout << "                REGISTRATION              " << endl;
    cout << "==========================================" << endl;
    setColor(RESET_COLOR);
    
}
void signup_ending_header()
{
    setColor(SUBHEADER_COLOR);
    cout << "==========================================" << endl;
    Sleep(50);
    cout << "      ACCOUNT CREATED SUCCESSFULLY!       " << endl;
    Sleep(50);
    cout << "==========================================" << endl;
    setColor(SUCCESS_COLOR);
    Sleep(50);
    cout << "Redirecting to login... " << endl;
    setColor(RESET_COLOR);
    Sleep(1000);
}
//signIN headers
void signinheader()
{
    setColor(SUBHEADER_COLOR);
    cout << "\n------------------------------------------" << endl;
    cout << "               USER LOGIN                 " << endl;
    cout << "------------------------------------------" << endl;
    setColor(RESET_COLOR);
}

//Heades of admin side
void admin_dashboard_header()
{
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    cout<<"           A D M I N  D A S H B O A R D           "<<endl;
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);

}
void add_employee_header()
{
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    cout<<"               REGISTER NEW EMPLOYEE              "<<endl;
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);
}
void search_employee_header()
{
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    cout<<"               EMPLOYEE SEARCH PORTAL              "<<endl;
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);
}
void delete_employee_header()
{
    setColor(SUBHEADER_COLOR);
    cout << "================================================" << endl;
    cout << "           REMOVE EMPLOYEE RECORD              " << endl;
    cout << "================================================" << endl;
    setColor(RESET_COLOR);
    Sleep(50);
    setColor(ERROR_COLOR);
    cout << " [WARNING]: This action cannot be undone!       " << endl;
    setColor(RESET_COLOR);
    Sleep(50);
    setColor(SUBHEADER_COLOR);
    cout << "------------------------------------------------" << endl;
    setColor(RESET_COLOR);
    Sleep(1000);
}
void update_employee_header()
{
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    cout<<"               UPDATE EMPLOYEE PORTAL              "<<endl;
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);
}
//Employee 1st heading
void employee_dashboard_header()
{
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    Sleep(50);
    cout<<"        E M P L O Y E E  D A S H B O A R D        "<<endl;
    Sleep(50);
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);
    Sleep(1000);
}
//employee side password update heading
void emp_password_update()
{
    setColor(SUBHEADER_COLOR);
    cout<<"\n================================================"<<endl;
    cout<<"               CHANGE YOUR PASSWORD              "<<endl;
    cout<<"================================================"<<endl;
    setColor(RESET_COLOR);
}

//Global header
void globalHeader() 
{
    setColor(HEADER_COLOR); // Start Cyan
    cout << "================================================================================" << endl;
    cout << " ||                       EMPLOYEE MANAGEMENT CONSOLE                         || " << endl;
    cout << " ||                     EMPLOYEE INFORMATION & SECURITY                       || " << endl;
    cout << "================================================================================" << endl;
    cout << "  [ ACCESS: GRANTED ]         [ DATE: 1-1-2026 ]          [ SYSTEM: STABLE ] " << endl;
    cout << " -------------------------------------------------------------------------------- " << endl;
    setColor(RESET_COLOR);  // Reset to White
}
//function that contain all the instuctions or rules to show 
void showInterface(string mode)
{ 
    setColor(INFO_COLOR); // Start Yellow
    cout<< "INSTRUCTIONS" << endl;
    cout<< "---------------------------------" << endl;

    if(mode == "ADMIN_SIGNUP")
    {
        cout<< "--> Name: 4-15 chars, No spaces." << endl;
        cout<< "--> Name: First letter Capital." << endl;
        cout<< "--> Name: No numbers or symbols." << endl;
        cout<< "--> Pass: more than 8 characters." << endl;
        cout<< "--> Pass: No spaces & 1 Num & 1 Spec Char (Must)" << endl;
    }
    else if(mode == "ADMIN_LOGIN")
    {
        cout<< "--> Enter registered credentials." << endl;
        cout<< "--> Maximum 3 attempts allowed." << endl;
        cout<< "--> Do not leave fields empty." << endl;
    }
    else if(mode == "EMP_LOGIN")
    {
        cout<< "--> Enter your assigned Employee ID." << endl;
        cout<< "--> Maximum 3 attempts allowed." << endl;
        cout<< "--> Password is case sensitive." << endl;
    }
    else if(mode == "ADD_EMP")
    {
        cout<< "--> ID: Unique, No spaces, Not empty." << endl;
        cout<< "--> Name/Dept: Alphabets & spaces only." << endl;
        cout<< "--> Salary: Positive numbers only." << endl;
        cout<< "--> Pass: more than 8 characters." << endl;
        cout<< "--> Pass: No spaces & 1 Num & 1 Spec Char (Must)" << endl;
    }
    cout<< "---------------------------------" << endl;
    setColor(RESET_COLOR); // Reset to White
}

//Function for colour
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//function for file handling
void saveEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int empCount)
{
    ofstream fout("employee.txt"); //to open the file
    //since i have parallel arrays, loop is used to go through them one by one
    for(int i=0; i<empCount; i++)
    {
        fout<<empID[i]<<","<<empPassword[i]<<","<<empName[i]<<","<<empDepartment[i]<<","<<empsalary[i]<<","<<endl;
    }
    fout.close();
}

//this function read data of the employee from the file, fill the array accordingly and update count
bool loadEmployee(string empID[],string empPassword[], string empName[], string empDepartment[], int empsalary[], int &empCount)
{
    ifstream fin("employee.txt");
    if(!fin)
    {
        return false;  //no file found
    }

    string line;
    empCount=0;

    while(getline(fin, line)) //as long as these lines in the file, keep going
    {
        if(line=="")
        {
            continue; //skip empty lines
        }

        int i=0;
        string temp="";
        //ID
        while(line[i] != ',')
        {
            temp=temp+line[i];
            i++;  
        }
        empID[empCount]=temp; //save those chaacters in the array
        i++; //skip the comma
        temp=""; //reset the temporary string

        //password
        while(line[i]!=',')
        {
            temp=temp+line[i];
            i++;
        }
        empPassword[empCount]=temp;
        i++;
        temp=""; //reset the temporary string

        //name
        while(line[i] != ',')
        {
            temp=temp+line[i];
            i++;  
        }
        empName[empCount]=temp;
        i++;
        temp=""; //reset the temporary string

        //department
        while(line[i] != ',')
        {
            temp=temp+line[i];
            i++;  
        }
        empDepartment[empCount]=temp;
        i++;
        temp=""; //reset the temporary string

        //salary
        while(line[i] != ',')
        {
            temp=temp+line[i];
            i++;  
        }
        if(!temp.empty())
        {
        empsalary[empCount]=stoi(temp); //convet string to number
        }
        else
        {
            empsalary[empCount]=0;
        }
        empCount++; //move to the next index fo the next employee
    }
    fin.close();
    return true;  //data loaded
}

void saveAdmin(string username, string password)
{
    ofstream fout("admin.txt");
    if(fout)
    {
        fout<<username<<","<<password<<","<<endl;
    }
    fout.close();
}

bool loadAdmin(string &user, string &pass)
{
    ifstream fin("admin.txt");
    string line;
    if(fin) //if file exists
    {
        getline(fin, line);
        int i=0;
        string temp = "";
        //username
        while(i<line.length() && line[i] != ',')
        {
        temp=temp+line[i];
        i++;
        }
        user=temp;
        i++; //skip comma

        temp="";
        //password
        while(i<line.length() && line[i] != ',')
        {
        temp=temp+line[i];
        i++;
        }
        pass=temp;
        fin.close();
        return true; //admin data loaded
    }
    return false; //no admin file
}
