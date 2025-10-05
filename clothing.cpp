#include "clothing.h"
#include <sstream>

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty,
                   const std::string& size, const std::string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand)
{ }

std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> brandKeys = parseStringToWords(brand_);
  keys = setUnion(keys, brandKeys);
  return keys;
}

std::string Clothing::displayString() const
{
  std::ostringstream oss;
  oss << name_ << "\n"
      << "Size: " << size_ << " Brand: " << brand_ << "\n"
      << price_ << " " << qty_ << " left.";
  return oss.str();
}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n";
  os << size_ << "\n";
  os << brand_ << "\n";
}
