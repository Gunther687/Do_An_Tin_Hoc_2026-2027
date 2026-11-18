#include "CauTrucSach.h"
#include <algorithm>

// =============================================
// PHAN 1: CAY AVL QUAN LY SACH THEO ISBN
// =============================================

// Lay chieu cao cua nut
int BookAVL::height(Node* n)
{
    return n ? n->height : 0;
}

// Tinh he so can bang cua nut
int BookAVL::balance(Node* n)
{
    return n ? height(n->left) - height(n->right) : 0;
}

// =============================================
// XOAY PHAI CAY AVL
// =============================================

BookAVL::Node* BookAVL::rotateRight(Node* y)
{
    Node* x = y->left;
    Node* t = x->right;

    // Thuc hien phep xoay phai
    x->right = y;
    y->left = t;

    // Cap nhat chieu cao
    y->height = 1 + std::max(
        height(y->left),
        height(y->right)
    );

    x->height = 1 + std::max(
        height(x->left),
        height(x->right)
    );

    return x;
}

// =============================================
// XOAY TRAI CAY AVL
// =============================================

BookAVL::Node* BookAVL::rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* t = y->left;

    // Thuc hien phep xoay trai
    y->left = x;
    x->right = t;

    // Cap nhat chieu cao
    x->height = 1 + std::max(
        height(x->left),
        height(x->right)
    );

    y->height = 1 + std::max(
        height(y->left),
        height(y->right)
    );

    return y;
}

// =============================================
// THEM NUT VAO CAY AVL
// =============================================

BookAVL::Node* BookAVL::insertNode(Node* n, const Book& b)
{
    // Neu vi tri hien tai rong
    if (n == NULL)
    {
        return new Node(b);
    }

    // So sanh ISBN de xac dinh vi tri chen
    if (b.isbn < n->value.isbn)
    {
        n->left = insertNode(n->left, b);
    }
    else if (b.isbn > n->value.isbn)
    {
        n->right = insertNode(n->right, b);
    }
    else
    {
        return n;
    }

    // Cap nhat chieu cao cua nut
    n->height = 1 + std::max(
        height(n->left),
        height(n->right)
    );

    // Tinh he so can bang
    int k = balance(n);

    // Truong hop LL
    if (k > 1 && b.isbn < n->left->value.isbn)
    {
        return rotateRight(n);
    }

    // Truong hop RR
    if (k < -1 && b.isbn > n->right->value.isbn)
    {
        return rotateLeft(n);
    }

    // Truong hop LR
    if (k > 1 && b.isbn > n->left->value.isbn)
    {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    // Truong hop RL
    if (k < -1 && b.isbn < n->right->value.isbn)
    {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

// =============================================
// TIM NUT CO GIA TRI NHO NHAT
// =============================================

BookAVL::Node* BookAVL::minNode(Node* n)
{
    while (n != NULL && n->left != NULL)
    {
        n = n->left;
    }

    return n;
}

// =============================================
// XOA NUT KHOI CAY AVL
// =============================================

BookAVL::Node* BookAVL::eraseNode(Node* n, const std::string& key)
{
    if (n == NULL)
    {
        return n;
    }

    // Tim nut can xoa theo ISBN
    if (key < n->value.isbn)
    {
        n->left = eraseNode(n->left, key);
    }
    else if (key > n->value.isbn)
    {
        n->right = eraseNode(n->right, key);
    }
    else
    {
        // Truong hop nut co 0 hoac 1 con
        if (n->left == NULL || n->right == NULL)
        {
            Node* child = n->left ? n->left : n->right;

            // Nut khong co con
            if (child == NULL)
            {
                delete n;
                return NULL;
            }

            // Nut co mot con
            *n = *child;
            delete child;
        }
        else
        {
            // Nut co hai con
            // Tim nut nho nhat ben cay con phai
            Node* s = minNode(n->right);

            // Thay du lieu nut can xoa
            n->value = s->value;

            // Xoa nut thay the
            n->right = eraseNode(
                n->right,
                s->value.isbn
            );
        }
    }

    // Cap nhat chieu cao
    n->height = 1 + std::max(
        height(n->left),
        height(n->right)
    );

    // Kiem tra can bang
    int k = balance(n);

    // Truong hop LL
    if (k > 1 && balance(n->left) >= 0)
    {
        return rotateRight(n);
    }

    // Truong hop LR
    if (k > 1 && balance(n->left) < 0)
    {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    // Truong hop RR
    if (k < -1 && balance(n->right) <= 0)
    {
        return rotateLeft(n);
    }

    // Truong hop RL
    if (k < -1 && balance(n->right) > 0)
    {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

// =============================================
// TIM KIEM SACH TRONG CAY AVL
// =============================================

const Book* BookAVL::findNode(Node* n, const std::string& key)
{
    while (n != NULL)
    {
        if (key == n->value.isbn)
        {
            return &n->value;
        }

        if (key < n->value.isbn)
        {
            n = n->left;
        }
        else
        {
            n = n->right;
        }
    }

    return NULL;
}

// =============================================
// DUYET CAY AVL THEO THU TU GIUA
// =============================================

void BookAVL::inorder(Node* n, std::vector<Book>& out)
{
    if (n == NULL)
    {
        return;
    }

    // Duyet cay con trai
    inorder(n->left, out);

    // Lay du lieu nut hien tai
    out.push_back(n->value);

    // Duyet cay con phai
    inorder(n->right, out);
}

// =============================================
// GIAI PHONG BO NHO CAY AVL
// =============================================

void BookAVL::clear(Node* n)
{
    if (n != NULL)
    {
        clear(n->left);
        clear(n->right);

        delete n;
    }
}

// =============================================
// CAC HAM LAM VIEC VOI CAY AVL
// =============================================

// Them sach vao cay AVL
bool BookAVL::insert(const Book& b)
{
    if (find(b.isbn) != NULL)
    {
        return false;
    }

    root = insertNode(root, b);

    return true;
}

// Xoa sach theo ISBN
bool BookAVL::erase(const std::string& key)
{
    if (find(key) == NULL)
    {
        return false;
    }

    root = eraseNode(root, key);

    return true;
}

// Tim sach theo ISBN
const Book* BookAVL::find(const std::string& key) const
{
    return findNode(root, key);
}

// Lay toan bo sach trong cay AVL
std::vector<Book> BookAVL::all() const
{
    std::vector<Book> out;

    inorder(root, out);

    return out;
}

// Xoa toan bo cay AVL
void BookAVL::clearAll()
{
    clear(root);
    root = NULL;
}


// =============================================
// PHAN 2: CAY NHI PHAN TIM KIEM THEO TEN SACH
// =============================================

// Them sach vao cay BST theo ten
BookNameBST::Node* BookNameBST::addNode(Node* n, const Book& b)
{
    // Neu vi tri hien tai rong
    if (n == NULL)
    {
        return new Node(b);
    }

    // So sanh ten sach de xac dinh vi tri chen
    if (b.title < n->value.title)
    {
        n->left = addNode(n->left, b);
    }
    else
    {
        n->right = addNode(n->right, b);
    }

    return n;
}

// Duyet cay BST theo thu tu giua
void BookNameBST::inorder(Node* n, std::vector<Book>& out)
{
    if (n == NULL)
    {
        return;
    }

    // Duyet cay con trai
    inorder(n->left, out);

    // Lay thong tin sach
    out.push_back(n->value);

    // Duyet cay con phai
    inorder(n->right, out);
}

// Giai phong bo nho cay BST
void BookNameBST::clear(Node* n)
{
    if (n != NULL)
    {
        clear(n->left);
        clear(n->right);

        delete n;
    }
}

// Xay dung lai cay BST tu danh sach sach
void BookNameBST::rebuild(const std::vector<Book>& books)
{
    // Xoa cay cu
    clear(root);
    root = NULL;

    // Them tung sach vao cay moi
    for (std::size_t i = 0; i < books.size(); ++i)
    {
        root = addNode(root, books[i]);
    }
}

// Lay danh sach sach da sap xep theo ten
std::vector<Book> BookNameBST::sortedByName() const
{
    std::vector<Book> out;

    inorder(root, out);

    return out;
}
