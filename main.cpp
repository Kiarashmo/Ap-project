#include <iostream>
#include "Book.h"
#include "Student.h"
#include "Admin.h"
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

std::string adminORstudent;
//std::string adminORstudent = "2";
std::string id;

void cls();
inline std::string getCurrentDateTime(std::string s);
void write_text_to_log_file(const std::string& command);
void login();
void adminmenu(Admin a);
void studentmenu(Student stu);

int main()
{
	Student stu;
	Admin a;
	std::string return_to_login;
	do {
		login();

		if (adminORstudent == "1") //student menu.
		{
			studentmenu(stu);
			std::cout << "\nTo Go TO Login Page Press '1' & TO Exit The Program Press '0' and Then Press 'Enter': ";
			getline(std::cin, return_to_login);
			if (return_to_login == "0")
				write_text_to_log_file("Close The Program");
		}
		else if (adminORstudent == "2") //admin menu.
		{
			adminmenu(a);
			std::cout << "\nTo Go TO Login Page Press '1' & TO Exit The Program Press '0' and Then Press 'Enter': ";
			getline(std::cin, return_to_login);
			if (return_to_login == "0")
				write_text_to_log_file("Close The Program");
		}
	} while (return_to_login == "1");
	
	return 0;
}

void cls()
{
	system("cls||clear"); //works for both windows and linux.
	return;
}

////////////////////////////////////////////////////////////////////////

inline std::string getCurrentDateTime(std::string s)
{
	time_t now = time(0);
	struct tm  tstruct;
	char  buf[80];
	localtime_s(&tstruct, &now); 
	//In Linux run the code below and comment the code above:
	//localtime_r(&now, &tstruct);

	if (s == "now")
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return std::string(buf);
}
void write_text_to_log_file(const std::string& command)
{
	std::ofstream log_file("log_file.log", std::ios_base::out | std::ios_base::app);

	log_file << std::endl << getCurrentDateTime("now") << " -- Command: " << command << " -- ID: " << id << std::endl;

	log_file.close();
}

//////////////////////////////////////////////////////////////////////////

void login()
{
	std::fstream student_data;
	student_data.open("student_admin_data.csv", std::ios::in);
	if (!student_data)
	{
		std::cerr << "Could not open student_admin_data.csv for read/write." << std::endl;
		return;
	}

	student_data.seekg(0, std::ios::end);
	int length = student_data.tellg();
	if (length == 0)
	{
		std::cout << "\n\t\tEmpty File!\n";
		student_data.close();
		return;
	}
	student_data.seekg(0, std::ios::beg);

	std::vector<std::string> student_details;
	char delimiter = ',';
	std::string line;
	std::string student_element;
	Student tmp;
	std::vector<Student> list_of_students;

	while (!student_data.eof())
	{
		student_details.clear();
		getline(student_data, line);
		std::stringstream s(line);

		while (std::getline(s, student_element, delimiter))
		{
			student_details.push_back(student_element);
		}

		tmp.set_student_name(student_details[0]);
		tmp.set_student_family_name(student_details[1]);
		tmp.set_student_age(student_details[2]);
		tmp.set_student_id(student_details[3]);
		tmp.set_student_position(student_details[4]);
		tmp.set_password(student_details[5]);
		list_of_students.push_back(tmp);
	}

	bool flag = false;
	std::string user_id;
	std::string user_pass;
	std::string yesorno;

	while (flag == false)
	{
		cls();

		std::cout << "Username(You Should Enter Your ID): ";
		getline(std::cin, user_id);

		std::cout << "Password: ";
		getline(std::cin, user_pass);
		


		for (int j = 0; j < list_of_students.size(); j++)
		{
			if (list_of_students[j].get_student_id() == user_id && list_of_students[j].get_password() == user_pass)
			{
				adminORstudent = list_of_students[j].get_student_position();
				id = user_id;
				flag = true;
				std::cout << "\nYou Have Successfully Entered:)" << std::endl;
				write_text_to_log_file("Login");
				break;
			}
		}
		if (flag == false)
		{
			std::cout << "\n\t\t!!Your 'Username' or 'Password' Is Wrong Please Try Again!!" << std::endl;
			id = user_id;
			write_text_to_log_file("Wrong Username or Password");
			std::cout << "\nDo You Want To Try Again?(Press y/n, 'No' Will Close The Program)" << std::endl;
			getline(std::cin, yesorno);

			if (yesorno == "n" || yesorno == "N")
			{
				cls();
				std::cout << "\n\t\tThank You For Using Our Software. Have Good Day." << std::endl;
				write_text_to_log_file("Close The Program");
				exit(0);
			}
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////

void adminmenu(Admin a)
{
	std::string enter;
	std::cout << "\nPress 'Enter' Key To Continue .... ";
	getline(std::cin, enter);
	
	cls();
	std::string choice;

	std::cout << "\n\t\tWelcome To The Admin Menu\n\n";
	std::cout << "1.Add Student Or Admin To Library.\n";
	std::cout << "\n2.Edit Student Or Admin Record.\n";
	std::cout << "\n3.Delete Student Or Admin From Library.\n";
	std::cout << "\n4.Change The Position Of Student To Admin.\n";
	std::cout << "\n5.Change The Position Of Admin To Student.\n";
	std::cout << "\n6.Add A Book.\n";
	std::cout << "\n7.Edit A Book.\n";
	std::cout << "\n8.Delete A Book.\n";
	std::cout << "\n9.Search A Book.\n";
	std::cout << "\n10.Display All Available Books.\n";
	std::cout << "\n0.Return To Login Page Or Close The Program.\n";

	std::cout << "\nPlease Enter Your Choice (0-10): ";
	getline(std::cin, choice);
	
	if (choice == "1")
	{
		cls();
		a.add_student();
		write_text_to_log_file("Add Student or Admin by Admin");
	}
	else if (choice == "2")
	{
		cls();
		a.edit_student();
		write_text_to_log_file("Edit Student or Admin by Admin");
	}
	else if (choice == "3")
	{
		cls();
		a.delete_student();
		write_text_to_log_file("Delete Student or Admin by Admin");
	}
	else if (choice == "4")
	{
		cls();
		a.student_to_admin();
		write_text_to_log_file("Student To Admin by Admin");
	}
	else if (choice == "5")
	{
		cls();
		a.admin_to_student();
		write_text_to_log_file("Admin To Student by Admin");
	}
	else if (choice == "6")
	{
		cls();
		a.add_book();
		write_text_to_log_file("Add Book by Admin");
	}
	else if (choice == "7")
	{
		cls();
		a.edit_book();
		write_text_to_log_file("Edit Book by Admin");
	}
	else if (choice == "8")
	{
		cls();
		a.delete_book();
		write_text_to_log_file("Delete Book by Admin");
	}
	else if (choice == "9")
	{
		cls();
		a.search_book();
		write_text_to_log_file("Search Book by Admin");
	}
	else if (choice == "10")
	{
		cls();
		a.list_and_display_book();
		write_text_to_log_file("List & Display All Books by Admin");
	}
	else if (choice == "0")
	{
		return;
	}
	else
	{
		std::cout << "\n !!Invalid Command!! \n";
		write_text_to_log_file("Invalid Command by Admin");
	}
	adminmenu(a);
}

void studentmenu(Student stu)
{
	std::string enter;
	std::cout << "\nPress 'Enter' Key To Continue .... ";
	getline(std::cin, enter);

	cls();
	std::string choice;

	std::cout << "\n\t\tWelcome To The Library Menu\n\n";
	std::cout << "\n1.Search A Book.\n";
	std::cout << "\n2.Display All Available Books.\n";
	std::cout << "\n0.Return To Login Page Or Close The Program.\n";

	std::cout << "\nPlease Enter Your Choice (0-10): ";
	getline(std::cin, choice);

	if (choice == "1")
	{
		cls();
		stu.search_book();
		write_text_to_log_file("Search Book by Admin");
	}
	else if (choice == "2")
	{
		cls();
		stu.list_and_display_book();
		write_text_to_log_file("List & Display All Books by Admin");
	}
	else if (choice == "0")
	{
		return;
	}
	else
	{
		std::cout << "\n !!Invalid Command!! \n";
		write_text_to_log_file("Invalid Command by Admin");
	}
	studentmenu(stu);
}