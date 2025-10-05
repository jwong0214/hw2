#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <vector>
#include <set>
#include <string>

class MyDataStore : public DataStore
{
public:
  MyDataStore();
  ~MyDataStore();

  // Adds a product to the store
  void addProduct(Product* p);

  // Adds a user to the store
  void addUser(User* u);

  // Performs a search of products whose keywords match the given terms
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  // Saves the current state of the database to a file
  void dump(std::ostream& ofile);

  // Extra functions to support ADD, VIEWCART, BUYCART
  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username);
  void buyCart(const std::string& username);

private:
  std::vector<Product*> products_;
  std::map<std::string, User*> users_;

  // maps lowercase keyword → set of products containing it
  std::map<std::string, std::set<Product*>> keywordMap_;

  // maps username (lowercase) → vector of products in their cart
  std::map<std::string, std::vector<Product*>> carts_;
};

#endif
