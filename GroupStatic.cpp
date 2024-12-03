#include <iostream>
#include <string>

using namespace std;

class Student {
    string name;
    string surname;
    int age;

public:
    // Конструктори
    Student() 
    {
        name = "Botyslav";
        surname = "Linchevskiy";
        age = 2;
    }

    Student(string name, string surname, int age)
    {
        this->name = name;
        this->surname = surname;
        this->age = age;
    }

    Student(const Student& obj) 
    {
        name = obj.name;
        surname = obj.surname;
        age = obj.age;
    }

    // Методи
    void PrintInfoAboutStudent() const {
        cout << "Name: " << name << ", Surname: " << surname << ", Age: " << age << endl;
    }

    void ChangeInfoAboutStudent() {
        cout << "Enter new name: ";
        cin >> name;
        cout << "Enter new surname: ";
        cin >> surname;
        cout << "Enter new age: ";
        cin >> age;
    }

    string GetName() const 
    { 
        return name; 
    }
    string GetSurname() const 
    { 
        return surname; 
    }
    int GetAge() const 
    { 
        return age; 
    }

    void SetName(const string& name) 
    { 
        this->name = name; 
    }
    void SetSurname(const string& surname) 
    { 
        this->surname = surname; 
    }
    void SetAge(int age) 
    { 
        this->age = age; 
    }
};

class Group {
    Student* students;
    int studentCount;

    static int totalStudents;

public:
    // Конструктор
    Group() : students(nullptr), studentCount(0) {}

    // Деструктор
    ~Group() {
        delete[] students;
    }

    // Додавання студента
    void AddStudent(const Student& newStudent) {
        Student* temp = new Student[studentCount + 1];
        for (int i = 0; i < studentCount; i++) {
            temp[i] = students[i];
        }
        temp[studentCount] = newStudent;
        delete[] students;
        students = temp;
        studentCount++;
        totalStudents++;
    }

    // Видалення студента
    void RemoveStudent(int index) {
        if (index < 0 || index >= studentCount) {
            cout << "Invalid index!" << endl;
            return;
        }
        Student* temp = new Student[studentCount - 1];
        for (int i = 0, j = 0; i < studentCount; i++) {
            if (i != index) {
                temp[j++] = students[i];
            }
        }
        delete[] students;
        students = temp;
        studentCount--;
        totalStudents--;
    }

    // Перейменування студента
    void RenameStudent(int index, const string& newName) {
        if (index < 0 || index >= studentCount) {
            cout << "Invalid index!" << endl;
            return;
        }
        students[index].SetName(newName);
    }

    // Виведення інформації про всіх студентів
    void PrintGroup() const {
        for (int i = 0; i < studentCount; i++) {
            cout << "Student " << i + 1 << ": ";
            students[i].PrintInfoAboutStudent();
        }
    }

    // Отримання кількості студентів
    static int GetTotalStudents() { return totalStudents; }
};

// Ініціалізація статичного поля
int Group::totalStudents = 0;

int main() {
    Group group;
    group.AddStudent(Student("Liza", "Scherbatyuk", 16));
    group.AddStudent(Student("Vlad", "ByryakXZKaknapisat", 4));

    cout << "Group members:" << endl;
    group.PrintGroup();

    cout << "\nRenaming second student to 'Kolya'.." << endl;
    group.RenameStudent(1, "Kolya");

    cout << "Updated group members:" << endl;
    group.PrintGroup();

    cout << "\nRemoving second student.." << endl;
    group.RemoveStudent(1);

    cout << "Final group members:" << endl;
    group.PrintGroup();

    cout << "\nTotal students: " << Group::GetTotalStudents() << endl;
}
