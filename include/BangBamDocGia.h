#ifndef BANG_BAM_DOC_GIA_H
#define BANG_BAM_DOC_GIA_H
#include "MoHinhDuLieu.h"
#include <vector>
class ReaderHash {
    std::vector<std::vector<Reader> > buckets;
    std::size_t hashKey(const std::string& key) const;
public:
    explicit ReaderHash(std::size_t capacity=101):buckets(capacity?capacity:101){}
    bool insert(const Reader& r);
    bool erase(const std::string& cmnd);
    Reader* find(const std::string& cmnd);
    const Reader* find(const std::string& cmnd) const;
    std::vector<Reader> all() const;
    void clear();
    std::size_t size() const;
    const std::vector<std::vector<Reader> >& getBuckets() const { return buckets; }
};
#endif
