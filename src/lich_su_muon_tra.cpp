#include "LichSuMuonTra.h"
#include <iostream>
#include <stdexcept>

// =====================================
// 1. DANH SACH PHIEU MUON (LINKED LIST)
// =====================================

// Them phieu muon vao cuoi danh sach
void LoanList::pushBack(const Loan& l)
{
    // Tao nut moi
    Node* n = new Node(l);

    // Neu danh sach rong
    if (head == NULL)
    {
        head = n;
        return;
    }

    // Tim nut cuoi danh sach
    Node* p = head;

    while (p->next != NULL)
    {
        p = p->next;
    }

    // Gan nut moi vao cuoi
    p->next = n;
}

// Danh dau phieu muon da tra
bool LoanList::markReturned(const std::string& id)
{
    Node* p = head;

    while (p != NULL)
    {
        // Kiem tra ma phieu va trang thai
        if (p->value.loanId == id && !p->value.returned)
        {
            p->value.returned = true;
            return true;
        }

        p = p->next;
    }

    return false;
}

// In danh sach phieu muon
void LoanList::print() const
{
    // Kiem tra danh sach rong
    if (head == NULL)
    {
        std::cout << "Chua co phieu muon.\n";
        return;
    }

    // Duyet va hien thi tung phieu
    Node* p = head;

    while (p != NULL)
    {
        std::cout << p->value.loanId
            << " | Doc gia: " << p->value.readerCmnd
            << " | ISBN: " << p->value.isbn
            << " | "
            << (p->value.returned ? "Da tra" : "Dang muon")
            << "\n";

        p = p->next;
    }
}

// Xoa toan bo danh sach phieu muon
void LoanList::clear()
{
    while (head != NULL)
    {
        Node* t = head;
        head = head->next;

        delete t;
    }
}

// =====================================
// 2. LICH SU GIAO DICH (DYNAMIC ARRAY)
// =====================================

// Ham huy: giai phong bo nho dong
TransactionArray::~TransactionArray()
{
    delete[] items;
}

// Mo rong kich thuoc mang khi day
void TransactionArray::grow()
{
    // Tang gap doi dung luong mang
    std::size_t nc = capacity ? capacity * 2 : 4;

    // Cap phat mang moi
    Transaction* p = new Transaction[nc];

    // Sao chep du lieu cu sang mang moi
    for (std::size_t i = 0; i < count; ++i)
    {
        p[i] = items[i];
    }

    // Giai phong mang cu
    delete[] items;

    // Cap nhat mang moi
    items = p;
    capacity = nc;
}

// Them giao dich vao mang
void TransactionArray::add(const Transaction& t)
{
    // Neu mang da day thi mo rong
    if (count == capacity)
    {
        grow();
    }

    // Them giao dich vao vi tri tiep theo
    items[count] = t;
    ++count;
}

// In danh sach lich su giao dich
void TransactionArray::print() const
{
    // Kiem tra mang rong
    if (count == 0)
    {
        std::cout << "Chua co giao dich.\n";
        return;
    }

    // Duyet va hien thi tung giao dich
    for (std::size_t i = 0; i < count; ++i)
    {
        std::cout << items[i].transactionId
            << " | " << items[i].type
            << " | " << items[i].dateTime
            << " | ISBN: " << items[i].isbn
            << " | CMND: " << items[i].readerCmnd
            << " | " << items[i].note
            << "\n";
    }
}
