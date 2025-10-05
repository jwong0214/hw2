#include "book.h"
#include <sstream>

Book::Book(const std::string& category, const std::string& name, double price, int qty,
           const std::string& isbn, const std::string& author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author)
{ }

std::set<std::string> Book::keywords() const
{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> authorKeys = parseStringToWords(author_);
  keys = setUnion(keys, authorKeys);
  // ISBN: verbatim keyword (store lowercase for case-insensitive matching)
  keys.insert(convToLower(isbn_));
  return keys;
}

std::string Book::displayString() const
{
  std::ostringstream oss;
  oss << name_ << "\n"
      << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
      << price_ << " " << qty_ << " left.";
  return oss.str();
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n";
  os << isbn_ << "\n";
  os << author_ << "\n";
}
