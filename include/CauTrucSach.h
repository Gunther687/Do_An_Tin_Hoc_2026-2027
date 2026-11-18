#ifndef CAU_TRUC_SACH_H
#define CAU_TRUC_SACH_H

#include "MoHinhDuLieu.h"
#include <vector>
#include <string>

class BookAVL
{
private:
    struct Node
    {
        Book value;
        Node* left;
        Node* right;
        int height;

        explicit Node(const Book& b)
            : value(b), left(NULL), right(NULL), height(1)
        {
        }
    };

    Node* root;

    static int height(Node* n);
    static int balance(Node* n);
    static Node* rotateRight(Node* y);
    static Node* rotateLeft(Node* x);
    static Node* insertNode(Node* n, const Book& b);
    static Node* minNode(Node* n);
    static Node* eraseNode(Node* n, const std::string& isbn);
    static const Book* findNode(
        Node* n,
        const std::string& isbn
    );

    static void inorder(Node* n, std::vector<Book>& out);

    static void clear(Node* n);

public:
    BookAVL() : root(NULL)
    {
    }

    ~BookAVL()
    {
        clear(root);
    }

    bool insert(const Book& b);
    bool erase(const std::string& isbn);

    const Book* find(const std::string& isbn) const;

    std::vector<Book> all() const;

    void clearAll();
};



class BookNameBST
{
private:
    struct Node
    {
        Book value;
        Node* left;
        Node* right;

        explicit Node(const Book& b)
            : value(b), left(NULL), right(NULL)
        {
        }
    };

    Node* root;

    static Node* addNode(Node* n, const Book& b);

    static void inorder(Node* n, std::vector<Book>& out);

    static void clear(Node* n);

public:
    BookNameBST() : root(NULL)
    {
    }

    ~BookNameBST()
    {
        clear(root);
    }

    void rebuild(const std::vector<Book>& books);

    std::vector<Book> sortedByName() const;
};

#endif
