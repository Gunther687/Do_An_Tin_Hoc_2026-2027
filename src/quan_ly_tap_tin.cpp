#include "QuanLyTapTin.h"
#include <fstream>
#include <cstdint>

// =====================================
// 1. GHI CHUOI VAO FILE NHI PHAN
// =====================================

static bool writeString(std::ofstream& f, const std::string& s)
{
    // Luu do dai chuoi
    uint32_t n = static_cast<uint32_t>(s.size());

    f.write(
        reinterpret_cast<const char*>(&n),
        sizeof(n)
    );

    // Luu noi dung chuoi
    if (n > 0)
    {
        f.write(s.data(), n);
    }

    return f.good();
}

// =====================================
// 2. DOC CHUOI TU FILE NHI PHAN
// =====================================

static bool readString(std::ifstream& f, std::string& s)
{
    uint32_t n = 0;

    // Doc do dai chuoi
    f.read(
        reinterpret_cast<char*>(&n),
        sizeof(n)
    );

    // Kiem tra du lieu doc duoc
    if (!f || n > 1000000)
    {
        return false;
    }

    // Cap phat bo nho cho chuoi
    s.assign(n, '\0');

    // Doc noi dung chuoi
    if (n > 0)
    {
        f.read(&s[0], n);
    }

    return f.good();
}

// =====================================
// 3. GHI THONG TIN SACH
// =====================================

static bool writeBook(std::ofstream& f, const Book& b)
{
    // Ghi cac thong tin dang chuoi
    if (!writeString(f, b.isbn))
        return false;

    if (!writeString(f, b.title))
        return false;

    if (!writeString(f, b.author))
        return false;

    if (!writeString(f, b.genre))
        return false;

    // Ghi nam xuat ban
    f.write(
        reinterpret_cast<const char*>(&b.publicationYear),
        sizeof(int)
    );

    if (!f.good())
        return false;

    // Ghi so luong sach
    f.write(
        reinterpret_cast<const char*>(&b.quantity),
        sizeof(int)
    );

    return f.good();
}

// =====================================
// 4. DOC THONG TIN SACH
// =====================================

static bool readBook(std::ifstream& f, Book& b)
{
    // Doc cac thong tin dang chuoi
    if (!readString(f, b.isbn))
        return false;

    if (!readString(f, b.title))
        return false;

    if (!readString(f, b.author))
        return false;

    if (!readString(f, b.genre))
        return false;

    // Doc nam xuat ban
    f.read(
        reinterpret_cast<char*>(&b.publicationYear),
        sizeof(int)
    );

    if (!f.good())
        return false;

    // Doc so luong sach
    f.read(
        reinterpret_cast<char*>(&b.quantity),
        sizeof(int)
    );

    return f.good();
}

// =====================================
// 5. GHI THONG TIN DOC GIA
// =====================================

static bool writeReader(std::ofstream& f, const Reader& r)
{
    if (!writeString(f, r.cmnd))
        return false;

    if (!writeString(f, r.fullName))
        return false;

    if (!writeString(f, r.email))
        return false;

    if (!writeString(f, r.phone))
        return false;

    if (!writeString(f, r.cardType))
        return false;

    return f.good();
}

// =====================================
// 6. DOC THONG TIN DOC GIA
// =====================================

static bool readReader(std::ifstream& f, Reader& r)
{
    if (!readString(f, r.cmnd))
        return false;

    if (!readString(f, r.fullName))
        return false;

    if (!readString(f, r.email))
        return false;

    if (!readString(f, r.phone))
        return false;

    if (!readString(f, r.cardType))
        return false;

    return f.good();
}

// =====================================
// 7. LUU DANH SACH SACH VAO FILE
// =====================================

bool saveBooksBinary(
    const std::vector<Book>& v,
    const std::string& path
)
{
    // Mo file o che do nhi phan
    std::ofstream f(path.c_str(), std::ios::binary);

    if (!f)
    {
        return false;
    }

    // Ghi so luong sach
    uint32_t n = static_cast<uint32_t>(v.size());

    f.write(
        reinterpret_cast<const char*>(&n),
        sizeof(n)
    );

    // Ghi tung sach vao file
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        if (!writeBook(f, v[i]))
        {
            return false;
        }
    }

    return f.good();
}

// =====================================
// 8. DOC DANH SACH SACH TU FILE
// =====================================

bool loadBooksBinary(
    std::vector<Book>& v,
    const std::string& path
)
{
    // Mo file de doc nhi phan
    std::ifstream f(path.c_str(), std::ios::binary);

    if (!f)
    {
        return false;
    }

    // Doc so luong sach
    uint32_t n = 0;

    f.read(
        reinterpret_cast<char*>(&n),
        sizeof(n)
    );

    if (!f || n > 1000000)
    {
        return false;
    }

    // Doc sach vao danh sach tam
    std::vector<Book> temp;

    for (uint32_t i = 0; i < n; ++i)
    {
        Book b;

        if (!readBook(f, b))
        {
            return false;
        }

        temp.push_back(b);
    }

    // Cap nhat danh sach sach
    v.swap(temp);

    return true;
}

// =====================================
// 9. LUU DANH SACH DOC GIA VAO FILE
// =====================================

bool saveReadersBinary(
    const std::vector<Reader>& v,
    const std::string& path
)
{
    // Mo file o che do nhi phan
    std::ofstream f(path.c_str(), std::ios::binary);

    if (!f)
    {
        return false;
    }

    // Ghi so luong doc gia
    uint32_t n = static_cast<uint32_t>(v.size());

    f.write(
        reinterpret_cast<const char*>(&n),
        sizeof(n)
    );

    // Ghi tung doc gia vao file
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        if (!writeReader(f, v[i]))
        {
            return false;
        }
    }

    return f.good();
}

// =====================================
// 10. DOC DANH SACH DOC GIA TU FILE
// =====================================

bool loadReadersBinary(
    std::vector<Reader>& v,
    const std::string& path
)
{
    // Mo file de doc nhi phan
    std::ifstream f(path.c_str(), std::ios::binary);

    if (!f)
    {
        return false;
    }

    // Doc so luong doc gia
    uint32_t n = 0;

    f.read(
        reinterpret_cast<char*>(&n),
        sizeof(n)
    );

    if (!f || n > 1000000)
    {
        return false;
    }

    // Doc doc gia vao danh sach tam
    std::vector<Reader> temp;

    for (uint32_t i = 0; i < n; ++i)
    {
        Reader r;

        if (!readReader(f, r))
        {
            return false;
        }

        temp.push_back(r);
    }

    // Cap nhat danh sach doc gia
    v.swap(temp);

    return true;
}

