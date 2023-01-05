#include "Book.h"
#include <iostream>

void Book::set_book_name(std::string bname)
{
	book_name = bname;
}
void Book::set_author(std::string au)
{
	author = au;
}
void Book::set_edition(std::string ed)
{
	edition = ed;
}
void Book::set_publication(std::string pu)
{
	publication = pu;
}
////////////////////////////////////////////////////////////////
std::string Book::get_book_name() const
{
	return book_name;
}
std::string Book::get_author() const
{
	return author;
}
std::string Book::get_edition() const
{
	return edition;
}
std::string Book::get_publication() const
{
	return publication;
}
////////////////////////////////////////////////////////////////
void Book::dispaly_book() const
{
	std::cout << "'" << book_name << "'" << " Written By " << "'" << author << "'" << " --- Edition: " 
		<< edition << " --- Publisher: " << publication << std::endl;
}
