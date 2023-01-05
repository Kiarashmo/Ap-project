#pragma once
#include <string>

class Book
{
public:
	Book() :book_name("N.A."), author("N.A."), edition("N.A."), publication("N.A.") {}
	~Book() {}
	//setters:
	void set_book_name(std::string bname);
	void set_author(std::string au);
	void set_edition(std::string ed);
	void set_publication(std::string pu);
	//getters:
	std::string get_book_name() const;
	std::string get_author() const;
	std::string get_edition() const;
	std::string get_publication() const;
	//other Functions:
	void dispaly_book() const;
private:
	std::string book_name;
	std::string author;
	std::string edition;
	std::string publication;
};

