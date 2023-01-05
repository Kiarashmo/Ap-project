#pragma once
#include "Book.h"
#include <vector>

class Student
{
public:
	Student() : student_name("N.A."), student_family_name("N.A."), student_age("0"), student_id("0000000"), student_position("1") {}
	~Student() {}

	void search_book();
	void list_and_display_book();
	void display_student();

	void set_student_name(std::string name) { student_name = name; }
	void set_student_family_name(std::string familyname) { student_family_name = familyname; }
	void set_student_age(std::string age) { student_age = age; }
	void set_student_id(std::string id) { student_id = id; }
	void set_student_position(std::string position) { student_position = position; }
	void set_password(std::string pass) { password = pass; }

	std::string get_student_name() { return student_name; }
	std::string get_student_family_name() { return student_family_name; }
	std::string get_student_age() { return student_age; }
	std::string get_student_id() { return student_id; }
	std::string get_student_position() { return student_position; }
	std::string get_password() { return password; }

private:
	std::string student_name;
	std::string student_family_name;
	std::string student_age;
	std::string student_id; // ID has made with 7 numbers.
	std::string student_position; // student := "1" & admin := "2"
	std::string password;

	Book search;
};

