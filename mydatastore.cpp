#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <iomanip>

using namespace std;

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore()
{
  // free dynamically allocated products and users
  for(size_t i = 0; i < products_.size(); i++){
    delete products_[i];
  }
  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    delete it->second;
  }
}

void MyDataStore::addProduct(Product* p)
{
  if(p == NULL) return;
  products_.push_back(p);

  // collect keywords from the product
  set<string> keys = p->keywords();
  for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it){
    keywordMap_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u)
{
  if(u == NULL) return;
  string uname = convToLower(u->getName());
  users_[uname] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  vector<Product*> hits;
  if(terms.empty()) return hits;

  // start with the first term’s results
  string firstTerm = convToLower(terms[0]);
  set<Product*> results;
  if(keywordMap_.find(firstTerm) != keywordMap_.end()){
    results = keywordMap_[firstTerm];
  }

  // combine with other terms using AND/OR
  for(size_t i = 1; i < terms.size(); i++){
    string t = convToLower(terms[i]);
    set<Product*> temp;
    if(keywordMap_.find(t) != keywordMap_.end()){
      temp = keywordMap_[t];
    }
    if(type == 0) { // AND
      results = setIntersection(results, temp);
    }
    else { // OR
      results = setUnion(results, temp);
    }
  }

  for(set<Product*>::iterator it = results.begin(); it != results.end(); ++it){
    hits.push_back(*it);
  }
  return hits;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for(size_t i = 0; i < products_.size(); i++){
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(const string& username, Product* p)
{
  string uname = convToLower(username);
  if(users_.find(uname) == users_.end() || p == NULL){
    cout << "Invalid request" << endl;
    return;
  }
  carts_[uname].push_back(p);
}

void MyDataStore::viewCart(const string& username)
{
  string uname = convToLower(username);
  if(users_.find(uname) == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }
  vector<Product*>& cart = carts_[uname];
  for(size_t i = 0; i < cart.size(); i++){
    cout << "Item " << i+1 << endl;
    cout << cart[i]->displayString() << endl;
  }
}

void MyDataStore::buyCart(const string& username)
{
  string uname = convToLower(username);
  if(users_.find(uname) == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }
  User* u = users_[uname];
  vector<Product*>& cart = carts_[uname];
  vector<Product*> remaining;

  for(size_t i = 0; i < cart.size(); i++){
    Product* p = cart[i];
    if(p->getQty() > 0 && u->getBalance() >= p->getPrice()){
      p->subtractQty(1);
      u->deductAmount(p->getPrice());
    }
    else {
      remaining.push_back(p); // keep in cart
    }
  }
  carts_[uname] = remaining;
}
