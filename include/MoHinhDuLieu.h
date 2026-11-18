#ifndef MO_HINH_DU_LIEU_H
#define MO_HINH_DU_LIEU_H
#include <string>

struct Book {
    std::string isbn, title, author, genre;
    int publicationYear;
    int quantity;
    Book() : publicationYear(0), quantity(0) {}
};

struct Reader {
    std::string cmnd, fullName, email, phone, cardType;
};

struct Loan {
    std::string loanId, readerCmnd, isbn, borrowDate, dueDate;
    bool returned;
    Loan() : returned(false) {}
};

struct Transaction {
    std::string transactionId, type, dateTime, readerCmnd, isbn, note;
};
#endif
