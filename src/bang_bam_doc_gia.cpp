#include "BangBamDocGia.h"

// Tinh gia tri bam tu ma CMND
std::size_t ReaderHash::hashKey(const std::string& key) const
{
    std::size_t h = 0;

    for (std::size_t i = 0; i < key.size(); ++i)
    {
        h = (h * 31 + static_cast<unsigned char>(key[i]))
            % buckets.size();
    }

    return h;
}

// Them doc gia vao bang bam
bool ReaderHash::insert(const Reader& r)
{
    // Kiem tra ma CMND da ton tai chua
    if (find(r.cmnd))
    {
        return false;
    }

    // Dua doc gia vao ngan tuong ung
    buckets[hashKey(r.cmnd)].push_back(r);

    return true;
}

// Xoa doc gia theo ma CMND
bool ReaderHash::erase(const std::string& key)
{
    std::vector<Reader>& b = buckets[hashKey(key)];

    for (std::vector<Reader>::iterator i = b.begin(); i != b.end(); ++i)
    {
        if (i->cmnd == key)
        {
            b.erase(i);
            return true;
        }
    }

    return false;
}

// Tim doc gia theo ma CMND
Reader* ReaderHash::find(const std::string& key)
{
    std::vector<Reader>& b = buckets[hashKey(key)];

    for (std::size_t i = 0; i < b.size(); ++i)
    {
        if (b[i].cmnd == key)
        {
            return &b[i];
        }
    }

    return NULL;
}

// Tim doc gia (phien ban chi doc du lieu)
const Reader* ReaderHash::find(const std::string& key) const
{
    const std::vector<Reader>& b = buckets[hashKey(key)];

    for (std::size_t i = 0; i < b.size(); ++i)
    {
        if (b[i].cmnd == key)
        {
            return &b[i];
        }
    }

    return NULL;
}

// Lay toan bo danh sach doc gia
std::vector<Reader> ReaderHash::all() const
{
    std::vector<Reader> out;

    for (std::size_t i = 0; i < buckets.size(); ++i)
    {
        for (std::size_t j = 0; j < buckets[i].size(); ++j)
        {
            out.push_back(buckets[i][j]);
        }
    }

    return out;
}

// Xoa toan bo doc gia trong bang bam
void ReaderHash::clear()
{
    for (std::size_t i = 0; i < buckets.size(); ++i)
    {
        buckets[i].clear();
    }
}

// Dem tong so doc gia
std::size_t ReaderHash::size() const
{
    std::size_t n = 0;

    for (std::size_t i = 0; i < buckets.size(); ++i)
    {
        n += buckets[i].size();
    }

    return n;
}