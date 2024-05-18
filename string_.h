#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_N_WORDS_IN_STRING   20
typedef struct WordDescriptor 
{
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

typedef struct BagOfWords 
{
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

size_t          strlen1                         (char *s);
char           *find                            (char *begin, char *end, int ch);
bool            isNonSpace                      (char sym);
bool            isSpace                         (char sym);
char           *findNonSpace                    (char *begin);
char           *findSpace                       (char *begin);
char           *findNonSpaceReverse             (char *rbegin, const char *rend);
char           *findSpaceReverse                (char *rbegin, const char *rend);
int             strcmp1                         (const char *lhs, const char *rhs);
char           *copy                            (char *beginSource, const char *endSource, char *beginDestination);
char           *copyStr                         (char *dest, char *src);
char           *copyIf                          (char *beginSource, const char *endSource, char *beginDestination, bool (*f)(char));
char           *copyIfReverse                   (char *rbeginSource, const char *rendSource, char *beginDestination, bool (*f)(char));
void            removeNonLetters                (char *s);
void            removeExtraSpaces               (char *s);
int             getWord                         (char *beginSearch, WordDescriptor *word);
int             getWordReverse                  (char *rbegin, char *rend, WordDescriptor *word);
bool            isNum                           (char *sym);
void            addNumOfSpaces                  (char *s);
void            replace                         (char *source, char *w1, char *w2);
int             WordsCmp                        (WordDescriptor w1, WordDescriptor w2);
bool            isAlphabeticalOrder             (char *str);
void            getBagOfWords                   (BagOfWords *bag, char *s);
void            printWord                       (WordDescriptor w);
void            PrintWordsBackwards             (char *str);
bool            isWordPalindrome                (WordDescriptor word);
int             wordsPalindrome                 (char *str);
char           *alternatingStringWords          (char *s1, char *s2);
void            reverseWordOrder                (char *str);
bool            findSymInWord                   (char s, WordDescriptor word);
void            printWordBeforeFirstWordWithA   (char *s);
bool            wordCmp                         (WordDescriptor word1, WordDescriptor word2);
void            findWordInOtherString           (char *s1, char *s2);
bool            FindSameWords                   (char *s1, char *s2);
void            getAllUniqueSortedLetters       (WordDescriptor *w);
void            sortSymInWord                   (WordDescriptor a);
bool            FindSameLettersInWords          (char *s);
void            getStringFromBag                (BagOfWords *w, char *s);
void            deleteLastWord                  (char *s);
WordDescriptor  findWordBeforeFirstFoundWord    (char *s1, char *s2);
void            deleteWord                      (char *s, WordDescriptor w);
void            deletePalindromeWords           (char *s);
char            *addWordDiffToShorterStr        (char *s1, char *s2);
bool            isLettersInWordPresentInStr     (char *s, WordDescriptor word);
