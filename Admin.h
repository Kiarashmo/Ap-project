#pragma once
#include "Student.h"

class Admin :
    public Student
{
public:
    Admin() {}
    ~Admin() {}

    //Book management:
    void add_book();
    void edit_book();
    void delete_book();

    //Student management:
    void add_student();
    void edit_student();
    void delete_student();
    void admin_to_student();
    void student_to_admin();
   
};
