#ifndef QUAN_LY_TAP_TIN_H
#define QUAN_LY_TAP_TIN_H

#include "MoHinhDuLieu.h"
#include <vector>
#include <string>

bool saveBooksBinary(
    const std::vector<Book>& books,
    const std::string& path
);

bool loadBooksBinary(
    std::vector<Book>& books,
    const std::string& path
);

bool saveReadersBinary(
    const std::vector<Reader>& readers,
    const std::string& path
);

bool loadReadersBinary(
    std::vector<Reader>& readers,
    const std::string& path
);

#endif
