#ifndef LICH_SU_MUON_TRA_H
#define LICH_SU_MUON_TRA_H
#include "MoHinhDuLieu.h"
#include <cstddef>

class LoanList {
    struct Node { Loan value; Node* next; explicit Node(const Loan& l):value(l),next(NULL){} };
    Node* head;
public:
    LoanList():head(NULL){}
    ~LoanList(){clear();}
    void pushBack(const Loan& l);
    bool markReturned(const std::string& loanId);
    void print() const;
    void clear();
};

class TransactionArray {
    Transaction* items;
    std::size_t count, capacity;
    void grow();
public:
    TransactionArray():items(NULL),count(0),capacity(0){}
    ~TransactionArray();
    TransactionArray(const TransactionArray&)=delete;
    TransactionArray& operator=(const TransactionArray&)=delete;
    void add(const Transaction& t);
    std::size_t size() const { return count; }
    const Transaction& at(std::size_t i) const { return items[i]; }
    void print() const;
};
#endif
