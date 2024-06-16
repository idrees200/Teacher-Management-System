#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class teacher {
    string name;
    string address;
    string contact;
    string email;
    string institution;
    string department;
    char type;
    string designation;
    string allocatedcourses[3];
    int credithours[3];
    int credithoursperweek;
    int monthlysalary;
    int experience;
    int publications;
    string qualification;

public:
    teacher(int n = 0, string s = "", char a = '\0') {
        name = s;
        address = s;
        contact = s;
        email = s;
        institution = s;
        department = s;
        type = a;
        designation = s;
        for (int i = 0; i < 3; i++) {
            allocatedcourses[i] = s;
            credithours[i] = 0;
        }
        credithoursperweek = n;
        monthlysalary = 0;
        experience = n;
        publications = n;
        qualification = s;
    }

    // Set methods
    void setname(string n) { name = n; }
    void setaddress(string a) { address = a; }
    void setcontact(string c) { contact = c; }
    void setemail(string e) { email = e; }
    void setinstitution(string i) { institution = i; }
    void setdepartment(string d) { department = d; }
    void settype(char T) { type = T; }
    void setdesignation(string dg) { designation = dg; }
    void setallocatedcourses(string course) {
        // Logic to parse allocated courses
        // Assuming the input format is comma-separated
        // Example: "PF,OOP,DSA"
        int s = 0;
        size_t pos = 0;
        string token;
        while ((pos = course.find(",")) != string::npos) {
            token = course.substr(0, pos);
            allocatedcourses[s++] = token;
            course.erase(0, pos + 1);
        }
    }
    void setcredithours(int n) {
        // Logic to set credit hours from integer input
        int i = 0;
        while (n > 0 && i < 3) {
            credithours[i++] = n % 10;
            n /= 10;
        }
    }
    void setcredithoursperweek(int index) { credithoursperweek = index; }
    void setsalary() {
        // Logic to calculate salary based on type, designation, experience, and publications
        int credit_sum = 0;
        for (int i = 0; i < 3; i++) {
            credit_sum += credithours[i];
        }
        if (type == 'V') {
            if (designation == "Lecturer") {
                monthlysalary = credit_sum * 2000;
            } else if (designation == "Assistant Professor") {
                monthlysalary = credit_sum * 4000;
            } else if (designation == "Associate Professor") {
                monthlysalary = credit_sum * 7000;
            } else if (designation == "Professor") {
                monthlysalary = credit_sum * 9000;
            }
        } else if (type == 'P') {
            if (designation == "Lecturer") {
                monthlysalary = 100000;
            } else if (designation == "Assistant Professor") {
                monthlysalary = 175000;
            } else if (designation == "Associate Professor") {
                monthlysalary = 250000;
            } else if (designation == "Professor") {
                monthlysalary = 325000;
            }
        }

        // Experience and publications bonuses
        monthlysalary += (monthlysalary * experience * 100) / (5 * 12); // 100% per 5 years
        monthlysalary += publications * 8000;
    }
    void setexperience(int ex) { experience = ex; }
    void setpublications(int p) { publications = p; }
    void setqualifications(string s) { qualification = s; }

    // Get methods
    string getname() { return name; }
    string getaddress() { return address; }
    string getcontact() { return contact; }
    string getemail() { return email; }
    string getinstitution() { return institution; }
    string getdepartment() { return department; }
    char gettype() { return type; }
    string getdesignation() { return designation; }
    void getallocatedcourses() {
        for (int i = 0; i < 3; i++) {
            cout << allocatedcourses[i] << endl;
        }
    }
    void getcredithours() {
        for (int i = 0; i < 3; i++) {
            cout << allocatedcourses[i] << " : " << credithours[i] << endl;
        }
    }
    int getcredithoursperweek() { return credithoursperweek; }
    int getsalary() { return monthlysalary; }
    int getexperience() { return experience; }
    int getpublications() { return publications; }
    string getqualifications() { return qualification; }

    void show() {
        cout << "NAME : " << getname() << endl;
        cout << "ADDRESS : " << getaddress() << endl;
        cout << "CONTACT : " << getcontact() << endl;
        cout << "EMAIL ID : " << getemail() << endl;
        cout << "INSTITUTION : " << getinstitution() << endl;
        cout << "DEPARTMENT : " << getdepartment() << endl;
        cout << "TYPE : " << gettype() << endl;
        cout << "DESIGNATION : " << getdesignation() << endl;
        cout << "ALLOCATED COURSES : " << endl;
        getallocatedcourses();
        cout << "CREDIT HOURS : " << endl;
        getcredithours();
        cout << "CREDIT HOURS PER WEEK FOR A 14 WEEK COURSE: " << getcredithoursperweek() << endl;
        setsalary();
        cout << "SALARY : " << getsalary() << endl;
        cout << "EXPERIENCE : " << getexperience() << endl;
        cout << "PUBLICATIONS : " << getpublications() << endl;
        cout << "QUALIFICATIONS : " << getqualifications() << endl;
    }

    int file() {
        // Return salary for file output
        return monthlysalary;
    }

    void updateinfo(int update, string change) {
        // Update information based on user input
        switch (update) {
            case 1:
                qualification = change;
                break;
            case 2:
                contact = change;
                break;
            case 3:
                institution = change;
                break;
            default:
                break;
        }
    }
};

int main() {
    int size, credithours, credithoursperweek, experience, publications;
    string name, address, contact, email, institution, department, designation, allocatedcourses, qualification;
    char type;

    ifstream ain("kip.txt");
    if (!ain.is_open()) {
        cerr << "ERROR OPENING FILE!" << endl;
        return 1;
    }

    ain >> size;
    ain.ignore(); // Ignore newline after size

    teacher *array = new teacher[size];

    for (int i = 0; i < size; i++) {
        getline(ain, name);
        getline(ain, address);
        getline(ain, contact);
        getline(ain, email);
        getline(ain, institution);
        getline(ain, department);
        ain >> type;
        ain.ignore(); // Ignore newline after type
        getline(ain, designation);
        getline(ain, allocatedcourses);
        ain >> credithours;
        ain >> credithoursperweek;
        ain >> experience;
        ain >> publications;
        ain.ignore(); // Ignore newline after publications
        getline(ain, qualification);

        // Set values for current teacher object
        array[i].setname(name);
        array[i].setaddress(address);
        array[i].setcontact(contact);
        array[i].setemail(email);
        array[i].setinstitution(institution);
        array[i].setdepartment(department);
        array[i].settype(type);
        array[i].setdesignation    
        array[i].setdesignation(designation);
        array[i].setallocatedcourses(allocatedcourses);
        array[i].setcredithours(credithours);
        array[i].setcredithoursperweek(credithoursperweek);
        array[i].setexperience(experience);
        array[i].setpublications(publications);
        array[i].setqualifications(qualification);

        // Clear temporary variables
        name = "", address = "", contact = "", email = "", institution = "", department = "", designation = "", allocatedcourses = "", qualification = "";
    }

    // Output details of each teacher
    for (int i = 0; i < size; i++) {
        cout << "Teacher #" << (i + 1) << " Details:" << endl;
        array[i].show();
        cout << "____________________________________________" << endl;
    }

    // Prompt user for updating information
    int no = 0;
    do {
        cout << "Do you want to update info of any member?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cin >> no;
    } while (no != 1 && no != 2);

    // Update information if requested
    if (no == 1) {
        int sel = 0, flag = 0;
        string e;
        cout << "Select member index you want to update:" << endl;
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << array[i].getname() << endl;
        }
        cin >> sel;
        if (sel >= 1 && sel <= size) {
            cout << "What do you want to update?" << endl;
            cout << "1. Update Qualification" << endl;
            cout << "2. Update Contact" << endl;
            cout << "3. Update Institution" << endl;
            cin >> flag;

            cin.ignore(); // Consume newline left by cin

            switch (flag) {
                case 1:
                    cout << "Enter new qualification: ";
                    getline(cin, e);
                    array[sel - 1].updateinfo(1, e);
                    break;
                case 2:
                    cout << "Enter new contact: ";
                    getline(cin, e);
                    array[sel - 1].updateinfo(2, e);
                    break;
                case 3:
                    cout << "Enter new institution: ";
                    getline(cin, e);
                    array[sel - 1].updateinfo(3, e);
                    break;
                default:
                    cout << "Invalid option!" << endl;
                    break;
            }
        }
    }

    // Output results to a file
    ofstream aout("RESULT.txt");
    if (!aout.is_open()) {
        cerr << "Failed to open RESULT.txt for writing!" << endl;
        return 1;
    }

    for (int i = 0; i < size; i++) {
        aout << "Teacher #" << (i + 1) << " Details:" << endl;
        aout << "____________________________________________" << endl;
        aout << "NAME: " << array[i].getname() << endl;
        aout << "ADDRESS: " << array[i].getaddress() << endl;
        aout << "CONTACT: " << array[i].getcontact() << endl;
        aout << "EMAIL ID: " << array[i].getemail() << endl;
        aout << "INSTITUTION: " << array[i].getinstitution() << endl;
        aout << "DEPARTMENT: " << array[i].getdepartment() << endl;
        aout << "TYPE: " << array[i].gettype() << endl;
        aout << "DESIGNATION: " << array[i].getdesignation() << endl;
        aout << "ALLOCATED COURSES: " << endl;
        array[i].getallocatedcourses();
        aout << "CREDIT HOURS: " << endl;
        array[i].getcredithours();
        aout << "CREDIT HOURS PER WEEK FOR A 14 WEEK COURSE: " << array[i].getcredithoursperweek() << endl;
        array[i].setsalary();
        aout << "SALARY: " << array[i].getsalary() << endl;
        aout << "EXPERIENCE: " << array[i].getexperience() << endl;
        aout << "PUBLICATIONS: " << array[i].getpublications() << endl;
        aout << "QUALIFICATIONS: " << array[i].getqualifications() << endl;
        aout << "____________________________________________" << endl;
    }

    // Clean up
    delete[] array;
    array = nullptr;

    return 0;
}

