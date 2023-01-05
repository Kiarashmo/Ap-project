#include "Admin.h"
#include <iostream>
#include <sstream>
#include <fstream>


void Admin::add_book()
{
	std::fstream book_data;
	book_data.open("book_data.csv", std::ios::out | std::ios::app);
	
	book_data.seekg(0, std::ios::end); // check file is 
	int length = book_data.tellg();    // empty or not and use it if.

	std::string bname, au, ed, pub;

	std::cout << "!! Please Don't Use ',' !!\n\n";
	std::cout << "Add Book:" << std::endl;
	do {
		std::cout << "Please Enter The 'Name' Of The Book: ";
		getline(std::cin, bname);
		if (bname.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." <<std::endl;
		}
	} while (bname.find(",") != std::string::npos);

	do {
		std::cout << "Please Enter The 'Author' Of The Book: ";
		getline(std::cin, au);
		if (au.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (au.find(",") != std::string::npos);

	do {
		std::cout << "Please Enter The 'Edition' Of The Book: ";
		getline(std::cin, ed);
		if (ed.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (ed.find(",") != std::string::npos);

	do {
		std::cout << "Please Enter The Name Of The 'Publisher' Of The Book: ";
		getline(std::cin, pub);
		if (pub.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (pub.find(",") != std::string::npos);
	
	if(length == 0)
		book_data << bname << "," << au << "," << ed << "," << pub;
	else
		book_data << "\n" << bname << "," << au << "," << ed << "," << pub;

	Book add;
	add.set_book_name(bname);
	add.set_author(au);
	add.set_edition(ed);
	add.set_publication(pub);

	std::cout << std::endl;
	add.dispaly_book();
	std::cout << "Has Been Added successfully :)" << std::endl;

	book_data.close();
}

void Admin::edit_book()
{
	std::fstream book_data;
	book_data.open("book_data.csv", std::ios::in);
	if (!book_data)
	{
		std::cerr << "Could not open book_data.csv for read/write." << std::endl;
		return;
	}
	book_data.seekg(0, std::ios::end);
	int length = book_data.tellg();
	if (length == 0)
	{
		std::cout << "\n\t\tEmpty File!\n";
		book_data.close();
		return;
	}
	book_data.seekg(0, std::ios::beg);

	std::fstream new_book_data;
	new_book_data.open("new_book_data.csv", std::ios::out);

	std::cout << "Edit Book:" << std::endl;
	std::string bname;
	std::cout << "Please Enter The 'Name' Of The Book You Want To Edit: ";
	getline(std::cin, bname);

	std::vector<std::string> book_details;
	char delimiter = ',';
	std::string line;
	std::string book_element;
	Book tmp;
	std::vector<Book> list_of_books;

	while (!book_data.eof())
	{
		book_details.clear();
		getline(book_data, line);
		std::stringstream s(line);

		while (std::getline(s, book_element, delimiter))
		{
			book_details.push_back(book_element);
		}

		tmp.set_book_name(book_details[0]);
		tmp.set_author(book_details[1]);
		tmp.set_edition(book_details[2]);
		tmp.set_publication(book_details[3]);
		list_of_books.push_back(tmp);
	}

	std::string newbookname, newauthor, newedition, newpublication;
	bool flag = false;
	for (int j = 0; j < list_of_books.size(); j++)
	{
		if (list_of_books[j].get_book_name() == bname)
		{
			flag = true;
			do {
				std::cout << "Please Enter The New 'Book Name': ";
				getline(std::cin, newbookname);
				if (newbookname.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newbookname.find(",") != std::string::npos);
			list_of_books[j].set_book_name(newbookname);

			do {
				std::cout << "Please Enter The New 'Author': ";
				getline(std::cin, newauthor);
				if (newauthor.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newauthor.find(",") != std::string::npos);
			list_of_books[j].set_author(newauthor);

			do {
				std::cout << "Please Enter The New 'Edition': ";
				getline(std::cin, newedition);
				if (newedition.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newedition.find(",") != std::string::npos);
			list_of_books[j].set_edition(newedition);

			do {
				std::cout << "Please Enter The New 'Publisher': ";
				getline(std::cin, newpublication);
				if (newpublication.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newpublication.find(",") != std::string::npos);
			list_of_books[j].set_publication(newpublication);
		}
	}

	for (int j = 0; j < list_of_books.size(); j++)
	{
		if (j != list_of_books.size() - 1)
			new_book_data << list_of_books[j].get_book_name() << "," << list_of_books[j].get_author() << ","
				<< list_of_books[j].get_edition() << "," << list_of_books[j].get_publication() << std::endl;
		
		else
			new_book_data << list_of_books[j].get_book_name() << "," << list_of_books[j].get_author() << ","
				<< list_of_books[j].get_edition() << "," << list_of_books[j].get_publication();
	}

	if (flag == false)
	{
		std::cout << "\nSorry The Book Not Found!" << std::endl;
	}
	else
	{
		std::cout << "\nYour Edit Has Been Done Successfully :)" << std::endl;
	}
	book_data.close();
	new_book_data.close();
	remove("book_data.csv");
	rename("new_book_data.csv", "book_data.csv");
}

void Admin::delete_book()
{
	std::fstream book_data;
	book_data.open("book_data.csv", std::ios::in);
	if (!book_data)
	{
		std::cerr << "Could not open book_data.csv for read/write." << std::endl;
		return;
	}

	book_data.seekg(0, std::ios::end);
	int length = book_data.tellg();
	if (length == 0)
	{
		std::cout << "\n\t\tEmpty File!\n";
		book_data.close();
		return;
	}
	book_data.seekg(0, std::ios::beg);

	std::fstream new_book_data;
	new_book_data.open("new_book_data.csv", std::ios::out);

	std::cout << "Delete Book:" << std::endl;
	std::string bname;
	std::cout << "Please Enter The 'Name' Of The Book You Want To Delete: ";
	getline(std::cin, bname);

	std::vector<std::string> book_details;
	char delimiter = ',';
	std::string line;
	std::string book_element;
	Book tmp;
	std::vector<Book> list_of_books;

	while (!book_data.eof())
	{
		book_details.clear();
		getline(book_data, line);
		std::stringstream s(line);

		while (std::getline(s, book_element, delimiter))
		{
			book_details.push_back(book_element);
		}

		tmp.set_book_name(book_details[0]);
		tmp.set_author(book_details[1]);
		tmp.set_edition(book_details[2]);
		tmp.set_publication(book_details[3]);
		list_of_books.push_back(tmp);
	}

	bool flag = false;

	if (list_of_books[list_of_books.size()-1].get_book_name() == bname)
	{
		for (int j = 0; j < list_of_books.size() - 1; j++)
		{
			flag = true;

			if (j != list_of_books.size() - 2)
				new_book_data << list_of_books[j].get_book_name() << "," << list_of_books[j].get_author() << ","
				<< list_of_books[j].get_edition() << "," << list_of_books[j].get_publication() << std::endl;

			else if (j == list_of_books.size() - 2)
				new_book_data << list_of_books[j].get_book_name() << "," << list_of_books[j].get_author() << ","
				<< list_of_books[j].get_edition() << "," << list_of_books[j].get_publication();
		}
	}
	else
	{
		for (int k = 0; k < list_of_books.size(); k++)
		{
			if (list_of_books[k].get_book_name() != bname)
			{
				if (k != list_of_books.size() - 1)
					new_book_data << list_of_books[k].get_book_name() << "," << list_of_books[k].get_author() << ","
					<< list_of_books[k].get_edition() << "," << list_of_books[k].get_publication() << std::endl;

				else
					new_book_data << list_of_books[k].get_book_name() << "," << list_of_books[k].get_author() << ","
					<< list_of_books[k].get_edition() << "," << list_of_books[k].get_publication();
			}
			else
				flag = true;
		}
	}

	if (flag == false)
	{
		std::cout << "\nSorry The Book Not Found!" << std::endl;
	}
	else
	{
		std::cout << "\nYour Delete Has Been Done Successfully :)" << std::endl;
	}
	book_data.close();
	new_book_data.close();
	remove("book_data.csv");
	rename("new_book_data.csv", "book_data.csv");
}

/////////////////////////////////////////////////

void Admin::add_student()
{
	std::fstream student_data;
	student_data.open("student_admin_data.csv", std::ios::out | std::ios::app | std::ios::in);

	if (!student_data)
	{
		std::cerr << "Could not open student_admin_data.csv for read/write." << std::endl;
		return;
	}

	student_data.seekg(0, std::ios::end);
	int length = student_data.tellg();
	student_data.seekg(0, std::ios::beg);
	
	std::string name, familyname, age, id, position, pass;
	std::cout << "!! Please Don't Use ',' !!\n\n";
	std::cout << "Add Student Or Admin:" << std::endl;

	do {
		std::cout << "Please Enter The 'Name' Of The Student or Admin: ";
		getline(std::cin, name);
		if (name.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (name.find(",") != std::string::npos);

	do {
		std::cout << "Please Enter The 'Family Name' Of The Student or Admin: ";
		getline(std::cin, familyname);
		if (familyname.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (familyname.find(",") != std::string::npos);

	do {
		std::cout << "Please Enter The 'Age' Of The Student or Admin: ";
		getline(std::cin, age);
		if (age.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (age.find(",") != std::string::npos);

	do {
		std::cout << "Please Enter The 'ID' Of The Student or Admin: ";
		getline(std::cin, id);
		if (id.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (id.find(",") != std::string::npos);
	if (length != 0) // check used ID.
	{
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

			tmp.set_student_id(student_details[3]);
			list_of_students.push_back(tmp);
		}
		for (int j = 0; j < list_of_students.size(); j++)
		{
			if (list_of_students[j].get_student_id() == id)
			{
				std::cout << "\n !!This ID Used Before!! \n";
				do {
					std::cout << "Please Enter The 'ID' Of The Student or Admin Again: ";
					getline(std::cin, id);
					if (id.find(",") != std::string::npos)
					{
						std::cout << "Don't Use ','! Please Try Again." << std::endl;
					}
				} while (id.find(",") != std::string::npos);
				j = 0;
			}
		}
	}

	do {
		std::cout << "Please Enter The 'Position' Of The Student or Admin(for student input 1 & for Admin input 2): ";
		getline(std::cin, position);
		if (position.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (position.find(",") != std::string::npos);
	
	do {
		std::cout << "Please Enter The 'Password' Of The Student or Admin: ";
		getline(std::cin, pass);
		if (pass.find(",") != std::string::npos)
		{
			std::cout << "Don't Use ','! Please Try Again." << std::endl;
		}
	} while (pass.find(",") != std::string::npos);

	student_data.seekg(0, std::ios::end);
	if (length == 0)
		student_data << name << "," << familyname << "," << age << "," << id << "," << position << "," << pass;
	else
		student_data << "\n" << name << "," << familyname << "," << age << "," << id << "," << position << "," << pass;
	
	
	std::cout << "\n" << name << " " << familyname << " Has Been Added Successfully :)" << std::endl;
	student_data.close();
}

void Admin::edit_student()
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

	std::fstream new_student_data;
	new_student_data.open("new_student_admin_data.csv", std::ios::out);

	std::cout << "!! Please Don't Use ',' !!\n\n";
	std::cout << "Edit Student Or Admin:" << std::endl;

	std::string user_id;
	std::cout << "Please Enter The 'ID' Of The Student Or Admin You Want To Edit: ";
	getline(std::cin, user_id);

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

	std::string newname, newfamilyname, newage, newid, newposition, newpassword;
	bool flag = false;
	for (int j = 0; j < list_of_students.size(); j++)
	{
		if (list_of_students[j].get_student_id() == user_id)
		{
			flag = true;

			do {
				std::cout << "Please Enter The New 'Name': ";
				getline(std::cin, newname);
				if (newname.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newname.find(",") != std::string::npos);
			list_of_students[j].set_student_name(newname);

			do {
				std::cout << "Please Enter The New 'Family Name': ";
				getline(std::cin, newfamilyname);
				if (newfamilyname.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newfamilyname.find(",") != std::string::npos);
			list_of_students[j].set_student_family_name(newfamilyname);

			do {
				std::cout << "Please Enter The New 'Age': ";
				getline(std::cin, newage);
				if (newage.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newage.find(",") != std::string::npos);
			list_of_students[j].set_student_age(newage);

			do {
				std::cout << "Please Enter The New 'ID': ";
				getline(std::cin, newid);
				if (newid.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newid.find(",") != std::string::npos);
			for (int k = 0; k < list_of_students.size(); k++) // check used ID before.
			{
				if (k == j)
					continue;
				if (list_of_students[k].get_student_id() == newid)
				{
					std::cout << "\n !!This ID Used Before!! \n";
					do {
						std::cout << "Please Enter The 'ID' Of The Student or Admin Again: ";
						getline(std::cin, newid);
						if (newid.find(",") != std::string::npos)
						{
							std::cout << "Don't Use ','! Please Try Again." << std::endl;
						}
					} while (newid.find(",") != std::string::npos);
					k = 0;
				}
			}
			list_of_students[j].set_student_id(newid);

			do {
				std::cout << "Please Enter The New 'Position'(for student input 1 & for Admin input 2): ";
				getline(std::cin, newposition);
				if (newposition.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newposition.find(",") != std::string::npos);
			list_of_students[j].set_student_position(newposition);

			do {
				std::cout << "Please Enter The New 'Password': ";
				getline(std::cin, newpassword);
				if (newpassword.find(",") != std::string::npos)
				{
					std::cout << "Don't Use ','! Please Try Again." << std::endl;
				}
			} while (newpassword.find(",") != std::string::npos);
			list_of_students[j].set_password(newpassword);
		}
	}

	for (int j = 0; j < list_of_students.size(); j++)
	{
		if (j != list_of_students.size() - 1)
			new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
			<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << "," 
			<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password() << std::endl;

		else
			new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
			<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << ","
			<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password();
	}

	if (flag == false)
	{
		std::cout << "\nSorry The ID Not Found!" << std::endl;
	}
	else
	{
		std::cout << "\nYour Edit Has Been Done Successfully :)" << std::endl;
	}
	student_data.close();
	new_student_data.close();
	remove("student_admin_data.csv");
	rename("new_student_admin_data.csv", "student_admin_data.csv");
}
void Admin::delete_student()
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

	std::fstream new_student_data;
	new_student_data.open("new_student_admin_data.csv", std::ios::out);

	std::cout << "Delete Student Or Admin:" << std::endl;

	std::string user_id;
	std::cout << "Please Enter The 'ID' Of The Student Or Admin You Want To Delete: ";
	getline(std::cin, user_id);

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

	if (list_of_students[list_of_students.size() - 1].get_student_id() == user_id)
	{
		flag = true;
		for (int j = 0; j < list_of_students.size() - 1; j++)
		{
			if (j != list_of_students.size() - 2)
				new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
				<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << "," 
				<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password() << std::endl;

			else if (j == list_of_students.size() - 2)
				new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
				<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << ","
				<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password();
		}
	}
	else
	{
		for (int k = 0; k < list_of_students.size(); k++)
		{
			if (list_of_students[k].get_student_id() != user_id)
			{
				if (k != list_of_students.size() - 1)
					new_student_data << list_of_students[k].get_student_name() << "," << list_of_students[k].get_student_family_name() 
					<< "," << list_of_students[k].get_student_age() << "," << list_of_students[k].get_student_id() << ","
					<< list_of_students[k].get_student_position() << "," << list_of_students[k].get_password() << std::endl;

				else
					new_student_data << list_of_students[k].get_student_name() << "," << list_of_students[k].get_student_family_name() 
					<< "," << list_of_students[k].get_student_age() << "," << list_of_students[k].get_student_id() << ","
					<< list_of_students[k].get_student_position() << "," << list_of_students[k].get_password();
			}
			else
				flag = true;
		}
	}

	if (flag == false)
	{
		std::cout << "\nSorry The ID Not Found!" << std::endl;
	}
	else
	{
		std::cout << "\nYour Delete Has Been Done Successfully :)" << std::endl;
	}
	student_data.close();
	new_student_data.close();
	remove("student_admin_data.csv");
	rename("new_student_admin_data.csv", "student_admin_data.csv");
}

void Admin::admin_to_student()
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

	std::fstream new_student_data;
	new_student_data.open("new_student_admin_data.csv", std::ios::out);

	std::string user_id;
	std::cout << "Please Enter The 'ID' Of The  Admin You Want To Change his/her Position: ";
	getline(std::cin, user_id);

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
	for (int j = 0; j < list_of_students.size(); j++)
	{
		if (list_of_students[j].get_student_id() == user_id)
		{
			flag = true;
			list_of_students[j].set_student_position("1");
		}

		if (j != list_of_students.size() - 1)
			new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
			<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << ","
			<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password() << std::endl;

		else
			new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
			<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << ","
			<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password();
	}
	if (flag == false)
	{
		std::cout << "\nSorry The ID Not Found!" << std::endl;
	}
	else
	{
		std::cout << "\nYour Edit Has Been Done Successfully :)" << std::endl;
	}
	student_data.close();
	new_student_data.close();
	remove("student_admin_data.csv");
	rename("new_student_admin_data.csv", "student_admin_data.csv");
}

void Admin::student_to_admin()
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

	std::fstream new_student_data;
	new_student_data.open("new_student_admin_data.csv", std::ios::out);

	std::string user_id;
	std::cout << "Please Enter The 'ID' Of The  Student You Want To Change his/her Position: ";
	getline(std::cin, user_id);

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
	for (int j = 0; j < list_of_students.size(); j++)
	{
		if (list_of_students[j].get_student_id() == user_id)
		{
			flag = true;
			list_of_students[j].set_student_position("2");
		}

		if (j != list_of_students.size() - 1)
			new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
			<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << ","
			<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password() << std::endl;

		else
			new_student_data << list_of_students[j].get_student_name() << "," << list_of_students[j].get_student_family_name() << ","
			<< list_of_students[j].get_student_age() << "," << list_of_students[j].get_student_id() << ","
			<< list_of_students[j].get_student_position() << "," << list_of_students[j].get_password();
	}
	if (flag == false)
	{
		std::cout << "\nSorry The ID Not Found!" << std::endl;
	}
	else
	{
		std::cout << "\nYour Edit Has Been Done Successfully :)" << std::endl;
	}
	student_data.close();
	new_student_data.close();
	remove("student_admin_data.csv");
	rename("new_student_admin_data.csv", "student_admin_data.csv");
}