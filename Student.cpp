#include "Student.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>



void Student::search_book()
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

	std::cout << "Search A Book:\n\n";
	std::string cho;
	std::cout << "1.Name Of The Book.\n";
	std::cout << "2.Author Of The Book.\n";
	std::cout << "3.Edition Of The Book.\n";
	std::cout << "4.Publication Of The Book.\n";
	std::cout << "\nChoose Your Type Of Search (1-4): ";
	getline(std::cin, cho);
	int choice = stoi(cho);

	std::string search_item;
	if (choice == 1)
	{
		std::cout << "\nPlease Enter The Name Of The Book: ";
		getline(std::cin, search_item);
	}
	else if (choice == 2)
	{
		std::cout << "\nPlease Enter The Name Of The Author Of The Book: ";
		getline(std::cin, search_item);
	}
	else if (choice == 3)
	{
		std::cout << "\nPlease Enter The Edition Of The Book: ";
		getline(std::cin, search_item);
	}
	else if (choice == 4)
	{
		std::cout << "\nPlease Enter The Publisher Of The Book: ";
		getline(std::cin, search_item);
	}

	std::vector<std::string> book_details;
	char delimiter = ',';
	std::string line;
	std::string book_element;
	bool flag = false;

	while (!book_data.eof())
	{
		book_details.clear();
		getline(book_data, line);
		std::stringstream s(line);

		while (std::getline(s, book_element, delimiter))
		{
			book_details.push_back(book_element);
		}

		if (book_details.at(choice - 1) == search_item)
		{
			flag = true;
			search.set_book_name(book_details.at(0));
			search.set_author(book_details.at(1));
			search.set_edition(book_details.at(2));
			search.set_publication(book_details.at(3));
			search.dispaly_book();
		}
	}

	if (flag == false)
	{
		std::cout << "\nSorry The Book Not Found!" << std::endl;
	}
	book_data.close();
}

void Student::list_and_display_book()
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

	int n;
	std::cout << "Please Enter The Number Of Books You Want To See In One Page(Your Number Should Be Greater Than 0): ";
	std::cin >> n;
	int copy_of_n = n;
	int size_of_list_of_books = list_of_books.size();

	while (n <= 0) //to check if n is greater than 0.
	{
		std::cout << "Please Enter A Number Greater Than 0 :) : ";
		std::cin >> n;
	}
	
	std::string button;
	if (size_of_list_of_books % n == 0)
	{
		for (int j = 0; j < size_of_list_of_books / n; j++)//pages
		{
			system("cls||clear");
			std::cout << "Page " << j+1 << " of " << size_of_list_of_books / n << std::endl;
			std::cout << std::endl;
			for (int k = 0; k < n; k++)//elements
			{
				std::cout << k + (j * n) +1 << ". ";
				list_of_books[k+(j*n)].dispaly_book();
			}
			std::cout << std::endl;
			std::cout << "Previous Page ( Enter < )" << "----------" << "Next Page ( Enter  > )" 
				<< "----------" << "Retrun To Menu (Enter 0)" << std::endl;
			std::cin >> button;

			do
			{
				if (button == ">" || button == "<" || button == "0")
					break;

				std::cout << "Please Enter ( < ) To Going To Previous Page Or ( > ) To Going To Next Page or ( 0 ) To Return To Menu: " 
					<< std::endl;
			} while (std::cin>>button);

			if (button == "<")
			{
				j -= 2;
				if (j == -2)
				{
					j += 1;
				}
			}
			else if (button == ">")
			{
				if (j == (size_of_list_of_books / n) - 1)
				{
					j--;
				}
			}
			else if (button == "0")
			{
				return;
			}
		}
	}
	else
	{
		for (int j = 0; j < size_of_list_of_books / n + 1; j++)//pages
		{
			system("cls||clear");
			std::cout << "Page " << j + 1 << " Of " << size_of_list_of_books / n + 1 << std::endl;
			std::cout << std::endl;

			if (j == (size_of_list_of_books / n))
			{
				copy_of_n = size_of_list_of_books % n;
			}
			else
			{
				copy_of_n = n;
			}

			for (int k = 0; k < copy_of_n; k++)//elements
			{
				std::cout << k + (j * n) + 1 << ". ";
				list_of_books[k + (j * n)].dispaly_book();
			}
			std::cout << std::endl;
			std::cout << "Previous Page ( Enter < )" << "----------" << "Next Page ( Enter  > )"
				<< "----------" << "Retrun To Menu (Enter 0)" << std::endl;
			std::cin >> button;

			do
			{
				if (button == ">" || button == "<" || button == "0")
					break;

				std::cout << "Please Enter ( < ) To Going To Previous Page Or ( > ) To Going To Next Page or ( 0 ) To Return To Menu: "
					<< std::endl;
			} while (std::cin >> button);

			if (button == "<")
			{
				j -= 2;
				if (j == -2)
				{
					j += 1;
				}
			}
			else if (button == ">")
			{
				if (j == (size_of_list_of_books / n))
				{
					j--;
				}
			}
			else if (button == "0")
			{
				return;
			}
		}
	}
	book_data.close();
}

void Student::display_student()
{
	std::cout << "Name: " << student_name << " -- " << "Family Name: " << student_family_name << " -- "
		"Age: " << student_age << " -- " << "ID: " << student_id << " -- " << "Position: " << student_position << std::endl;
}
