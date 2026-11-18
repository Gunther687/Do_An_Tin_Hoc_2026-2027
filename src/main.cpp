#include "CauTrucSach.h"
#include "BangBamDocGia.h"
#include "LichSuMuonTra.h"
#include "QuanLyTapTin.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <vector>

// Lay thoi gian hien tai
static std::string nowText()
{
    std::time_t t = std::time(NULL);
    char b[32];

    std::strftime(
        b,
        sizeof(b),
        "%Y-%m-%d %H:%M:%S",
        std::localtime(&t)
    );

    return b;
}

// Nhap chuoi tu ban phim
static std::string input(const std::string& prompt)
{
    std::string s;

    std::cout << prompt;
    std::getline(std::cin, s);

    return s;
}

// Nhap so nguyen va kiem tra du lieu
static int number(const std::string& prompt)
{
    while (true)
    {
        std::string s = input(prompt);
        std::stringstream ss(s);

        int n;
        char c;

        if (ss >> n && !(ss >> c))
        {
            return n;
        }

        std::cout << "Vui long nhap so nguyen hop le.\n";
    }
}

// Hien thi thong tin sach
static void showBook(const Book& b)
{
    std::cout << b.isbn << " | "
        << b.title << " | "
        << b.author << " | "
        << b.genre << " | "
        << b.publicationYear
        << " | SL: " << b.quantity << "\n";
}

// Hien thi thong tin doc gia
static void showReader(const Reader& r)
{
    std::cout << r.cmnd << " | "
        << r.fullName << " | "
        << r.email << " | "
        << r.phone << " | "
        << r.cardType << "\n";
}

int main()
{
    // Khoi tao cac cau truc du lieu
    BookAVL books;
    BookNameBST nameTree;
    ReaderHash readers;
    LoanList loans;
    TransactionArray history;

    std::vector<Book> loadedBooks;
    std::vector<Reader> loadedReaders;

    // Nap du lieu sach tu file nhi phan
    if (loadBooksBinary(loadedBooks, "data/books.txt"))
    {
        for (std::size_t i = 0; i < loadedBooks.size(); ++i)
        {
            books.insert(loadedBooks[i]);
        }

        std::cout << "Da nap "
            << loadedBooks.size()
            << " sach.\n";
    }

    // Nap du lieu doc gia tu file nhi phan
    if (loadReadersBinary(loadedReaders, "data/readers.txt"))
    {
        for (std::size_t i = 0; i < loadedReaders.size(); ++i)
        {
            readers.insert(loadedReaders[i]);
        }

        std::cout << "Da nap "
            << loadedReaders.size()
            << " doc gia.\n";
    }

    bool running = true;

    // Vong lap menu chinh
    while (running)
    {
        std::cout << "\n===== QUAN LY THU VIEN =====\n";
        std::cout << "1. Quan ly sach (AVL/BST)\n";
        std::cout << "2. Quan ly doc gia (Hash Table)\n";
        std::cout << "3. Phieu muon (Linked List - demo)\n";
        std::cout << "4. Lich su giao dich (Dynamic Array)\n";
        std::cout << "5. Luu file \n";
        std::cout << "6. So sanh Hash va tim tuan tu\n";
        std::cout << "0. Luu va thoat\n";

        int c = number("Chon: ");

        // =====================================
        // 1. QUAN LY SACH
        // =====================================
        if (c == 1)
        {
            std::cout << "\n--- QUAN LY SACH ---\n";
            std::cout << "1. Them sach\n";
            std::cout << "2. Tim sach theo ISBN\n";
            std::cout << "3. Xoa sach\n";
            std::cout << "4. In sach theo ISBN (AVL)\n";
            std::cout << "5. In sach theo ten (BST)\n";

            int x = number("Chon: ");

            // Them sach
            if (x == 1)
            {
                Book b;

                b.isbn = input("ISBN: ");
                b.title = input("Ten sach: ");
                b.author = input("Tac gia: ");
                b.genre = input("The loai: ");
                b.publicationYear = number("Nam XB: ");
                b.quantity = number("So luong: ");

                if (b.isbn.empty() ||
                    b.title.empty() ||
                    b.quantity < 0 ||
                    !books.insert(b))
                {
                    std::cout << "Du lieu khong hop le hoac ISBN da ton tai.\n";
                }
                else
                {
                    nameTree.rebuild(books.all());

                    Transaction t;
                    t.transactionId = "T" + b.isbn;
                    t.type = "THEM_SACH";
                    t.dateTime = nowText();
                    t.isbn = b.isbn;
                    t.note = "Them sach: " + b.title;

                    history.add(t);

                    std::cout << "Them sach thanh cong.\n";
                }
            }

            // Tim sach theo ISBN
            else if (x == 2)
            {
                std::string key = input("Nhap ISBN: ");
                const Book* b = books.find(key);

                if (b != NULL)
                {
                    showBook(*b);
                }
                else
                {
                    std::cout << "Khong tim thay sach.\n";
                }
            }

            // Xoa sach
            else if (x == 3)
            {
                std::string key = input("ISBN can xoa: ");

                if (books.erase(key))
                {
                    nameTree.rebuild(books.all());
                    std::cout << "Da xoa sach.\n";
                }
                else
                {
                    std::cout << "Khong tim thay ISBN.\n";
                }
            }

            // In danh sach sach theo ISBN
            else if (x == 4)
            {
                std::vector<Book> v = books.all();

                for (std::size_t i = 0; i < v.size(); ++i)
                {
                    showBook(v[i]);
                }

                if (v.empty())
                {
                    std::cout << "Danh sach rong.\n";
                }
            }

            // In danh sach sach theo ten
            else if (x == 5)
            {
                nameTree.rebuild(books.all());

                std::vector<Book> v = nameTree.sortedByName();

                for (std::size_t i = 0; i < v.size(); ++i)
                {
                    showBook(v[i]);
                }

                if (v.empty())
                {
                    std::cout << "Danh sach rong.\n";
                }
            }
            else
            {
                std::cout << "Lua chon khong hop le.\n";
            }
        }

        // =====================================
        // 2. QUAN LY DOC GIA
        // =====================================
        else if (c == 2)
        {
            std::cout << "\n--- QUAN LY DOC GIA ---\n";
            std::cout << "1. Them doc gia\n";
            std::cout << "2. Tim doc gia theo CMND\n";
            std::cout << "3. Xoa doc gia\n";
            std::cout << "4. In danh sach doc gia\n";

            int x = number("Chon: ");

            // Them doc gia
            if (x == 1)
            {
                Reader r;

                r.cmnd = input("CMND: ");
                r.fullName = input("Ho ten: ");
                r.email = input("Email: ");
                r.phone = input("So dien thoai: ");
                r.cardType = input("Loai the: ");

                if (r.cmnd.empty() ||
                    r.fullName.empty() ||
                    !readers.insert(r))
                {
                    std::cout << "Du lieu khong hop le hoac CMND da ton tai.\n";
                }
                else
                {
                    Transaction t;

                    t.transactionId = "R" + r.cmnd;
                    t.type = "THEM_DOC_GIA";
                    t.dateTime = nowText();
                    t.readerCmnd = r.cmnd;
                    t.note = "Them doc gia: " + r.fullName;

                    history.add(t);

                    std::cout << "Them doc gia thanh cong.\n";
                }
            }

            // Tim doc gia
            else if (x == 2)
            {
                std::string key = input("Nhap CMND: ");
                const Reader* r = readers.find(key);

                if (r != NULL)
                {
                    showReader(*r);
                }
                else
                {
                    std::cout << "Khong tim thay doc gia.\n";
                }
            }

            // Xoa doc gia
            else if (x == 3)
            {
                std::string key = input("CMND can xoa: ");

                if (readers.erase(key))
                {
                    std::cout << "Da xoa doc gia.\n";
                }
                else
                {
                    std::cout << "Khong tim thay doc gia.\n";
                }
            }

            // In danh sach doc gia
            else if (x == 4)
            {
                std::vector<Reader> v = readers.all();

                for (std::size_t i = 0; i < v.size(); ++i)
                {
                    showReader(v[i]);
                }

                std::cout << "Tong: "
                    << v.size()
                    << " doc gia.\n";
            }
            else
            {
                std::cout << "Lua chon khong hop le.\n";
            }
        }

        // =====================================
        // 3. QUAN LY PHIEU MUON
        // =====================================
        else if (c == 3)
        {
            std::cout << "\n--- QUAN LY PHIEU MUON ---\n";
            std::cout << "1. Lap phieu muon (demo)\n";
            std::cout << "2. Danh sach phieu muon\n";
            std::cout << "3. Danh dau da tra\n";

            int x = number("Chon: ");

            // Lap phieu muon
            if (x == 1)
            {
                Loan l;

                l.loanId = input("Ma phieu: ");
                l.readerCmnd = input("CMND: ");
                l.isbn = input("ISBN: ");
                l.borrowDate = nowText();
                l.dueDate = input("Han tra (YYYY-MM-DD): ");

                if (l.loanId.empty() ||
                    !readers.find(l.readerCmnd) ||
                    !books.find(l.isbn))
                {
                    std::cout << "Ma phieu rong hoac sach/doc gia khong ton tai.\n";
                }
                else
                {
                    loans.pushBack(l);

                    std::cout << "Da tao phieu demo.\n";
                    std::cout << "(Chua tru so luong; chuc nang muon-tra day du thuoc tuan 6)\n";
                }
            }

            // Hien thi danh sach phieu muon
            else if (x == 2)
            {
                loans.print();
            }

            // Cap nhat trang thai da tra
            else if (x == 3)
            {
                std::string id = input("Ma phieu: ");

                if (loans.markReturned(id))
                {
                    std::cout << "Da cap nhat trang thai.\n";
                }
                else
                {
                    std::cout << "Khong tim thay phieu dang muon.\n";
                }
            }
            else
            {
                std::cout << "Lua chon khong hop le.\n";
            }
        }

        // =====================================
        // 4. XEM LICH SU GIAO DICH
        // =====================================
        else if (c == 4)
        {
            history.print();
        }

        // =====================================
        // 5. LUU DU LIEU VAO FILE NHI PHAN
        // =====================================
        else if (c == 5)
        {
            bool a = saveBooksBinary(
                books.all(),
                "data/books.txt"
            );

            bool b = saveReadersBinary(
                readers.all(),
                "data/readers.txt"
            );

            if (a && b)
            {
                std::cout << "Luu file thanh cong.\n";
            }
            else
            {
                std::cout << "Loi luu file. Kiem tra thu muc data.\n";
            }
        }

        // =====================================
        // 6. SO SANH HASH VA TIM KIEM TUAN TU
        // =====================================
        else if (c == 6)
        {
            std::string key = input("CMND can tim: ");

            std::vector<Reader> v = readers.all();
            bool found = false;

            // Tim kiem tuan tu
            for (std::size_t i = 0; i < v.size(); ++i)
            {
                if (v[i].cmnd == key)
                {
                    found = true;
                    break;
                }
            }

            // Hien thi ket qua so sanh
            std::cout << "Hash Table: "
                << (readers.find(key) ? "tim thay" : "khong thay")
                << ";\n";

            std::cout << "Tim tuan tu: "
                << (found ? "tim thay" : "khong thay")
                << ".\n";

            std::cout << "Do phuc tap ly thuyet:\n";
            std::cout << "- Hash Table trung binh: O(1)\n";
            std::cout << "- Tim kiem tuan tu: O(n)\n";
        }

        // =====================================
        // 0. LUU DU LIEU VA THOAT CHUONG TRINH
        // =====================================
        else if (c == 0)
        {
            bool a = saveBooksBinary(
                books.all(),
                "data/books.txt"
            );

            bool b = saveReadersBinary(
                readers.all(),
                "data/readers.txt"
            );

            if (a && b)
            {
                std::cout << "Da luu du lieu.\n";
            }
            else
            {
                std::cout << "Khong the luu du lieu.\n";
            }

            running = false;
        }

        else
        {
            std::cout << "Lua chon khong hop le.\n";
        }
    }

    return 0;
}
