//
// Created by norma on 29/3/2021.
//

#include "Inventory.h"

//Relacion asociación por composición, porque crea los objetos parte en la misma clase
Inventory::Inventory(const int &identifier, const string &name, const int &size){
    this-> identifier = identifier;
    this-> name = name;
    myCollection = new ProductCollection(size);
    myCashRegister = new CashRegister();
}

Inventory::~Inventory() {
    if (getProductCollection()){
        delete getProductCollection();
    }
    if(getCashRegister()){
        delete getCashRegister();
    }
}

void Inventory::setIdentifier(const int &identifier) {
    this-> identifier = identifier;
}

void Inventory::setName(const string &name) {
    this->name = name;
}

void Inventory::setProductCollection(ProductCollection * myCollection) {
    this->myCollection = myCollection;
}

void Inventory::setCashRegister(CashRegister *myCashRegister) {
    this->myCashRegister = myCashRegister;
}

int Inventory::getIdentifier() const{
    return identifier;
}

string Inventory::getName() const {
    return name;
}

ProductCollection *Inventory::getProductCollection() const {
    return myCollection;
}

CashRegister *Inventory::getCashRegister() const {
    return myCashRegister;
}

string Inventory::toString() const {
    stringstream s;
    s << "\nInventory";
    s << "\n\tID: " << getIdentifier();
    s << "\n\tName: " << getName();
    s << "\n" << getProductCollection()->toString();
    s << "\n" << getCashRegister()->toString();
    return s.str();
}

void Inventory::insert(Product *P) {
    getProductCollection()->addProduct(P);
}

void Inventory::increaseQuantity(string id, int cant) {
    getProductCollection()->increaseQuantity(id, cant);
}

void Inventory::reduceQuantity(string id, int cant) {
    getProductCollection()->reduceQuantity(id, cant);
}

void Inventory::deleteProduct(string id) {
    getProductCollection()->deleteProduct(id);
}

Product *Inventory::check(string id) {
    if(getProductCollection()->verifyProduct(id)){
        return getProductCollection()->productReturn(id);
    }
    return nullptr;
}

void Inventory::depositMoney(int c)  {
    getCashRegister()->setMoney(getCashRegister()->getMoney() + c);
}

bool Inventory::withdrawMoney(int x) {
    int money = 0;
    money = getCashRegister()->getMoney();
    if (x <= money){
        getCashRegister()->setMoney(money - x);
        return true;
    }
    return false;
}

string Inventory::getNameS() const {
    return name;
}

string Inventory::toMakeThePurchase(string id, int quantity, int paymentAmount, int optionBill) {
    stringstream t;
    int change = 0;

    if (optionBill >= paymentAmount) {
        if (optionBill - paymentAmount < getCashRegister()->getMoney() + paymentAmount) {
            t << "\nSuccessful purchase!";
            depositMoney(paymentAmount);
            change = optionBill - paymentAmount;
            t << "\nMoney: " << optionBill;
            t << "\nTo pay: " << paymentAmount;
            t << getCashRegister()->changeBreakdown(change);
            getProductCollection()->reduceQuantity(id, quantity);
        }
        t << "\nInsufficient funds!\n";
    }
    t << "\nNot enough money for change!\n";
    return t.str();
}


string Inventory::toStringS() const {
    stringstream s;
    s << "\n\tList of products available";
    s << getProductCollection()->toString() << "\n";
    return s.str();
}

bool Inventory::collectionEmpty() const {
    if(getProductCollection()->empty()){
        return true;
    }
    return false;
}

string Inventory::toStringSimple() const{
    stringstream ss;
    ss << "\nInventory";
    ss << "\n\tID: " << getIdentifier();
    ss << "\n\tName: " << getName();
    return ss.str();
}