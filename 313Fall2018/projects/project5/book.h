#ifndef BOOK_H
#define BOOK_H

#define TITLE_LEN       40
#define AUTHOR_LEN      20

typedef struct book {
    char title[TITLE_LEN + 1];      /* title */
    char author[AUTHOR_LEN + 1];    /* first author */
    unsigned int year;              /* year of e-book release */
} books;
#endif /* BOOK_H */
