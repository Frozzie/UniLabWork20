#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <malloc.h>
#include "string_.h"

size_t strlen1(char *s)
{
    char *end = s;

    while (*end != '\0')
    {
        end++;
    }
    
    return end - s;
}

char* find(char *begin, char *end, int ch)
{
    while(begin != end && *begin != ch)
    {
        begin++;
    }

    return begin;
}

bool isNonSpace(char sym)
{
    bool answ = false;

    if(sym >= '0' && sym <= '9' || sym >= 'A' && sym <= 'Z' || sym >= 'a' && sym <= 'z')
    {
        answ = true;
    }

    return answ;
}

bool isSpace(char sym)
{
    bool answ = true;

    if(sym >= '0' && sym <= '9' || sym >= 'A' && sym <= 'Z' || sym >= 'a' && sym <= 'z')
    {
        answ = false;
    }

    return answ;
}

char* findNonSpace (char *begin)
{
    char *sym = begin;

    while(*sym > 0)
    {
        if (isNonSpace (*sym))
        {
            break;
        }
        sym++;
    }
    
    return sym;
}

char* findSpace (char *begin)
{
    char *sym = begin;

    while(*sym > 0)
    {
        if (isSpace (*sym))
        {
            break;
        }
        
        sym++;
    }
    
    return sym;
}

char* findNonSpaceReverse(char *rbegin, const char *rend)
{
    char *sym = rbegin;

    while(*sym > *rend)
    {
        if (!isSpace (*sym))
        {
            break;
        }
        sym--;
    }
    
    return sym;
}

char* findSpaceReverse(char *rbegin, const char *rend)
{
    char *sym = rbegin;

    while(*sym > *rend)
    {
        if (isSpace (*sym))
        {
            break;
        }
        sym--;
    }
    
    return sym;
}

int strcmp1(const char *lhs, const char *rhs)
{
    while(*lhs > 0 && *rhs > 0)
    {
        if(*lhs != *rhs)
        {
            break;
        }
        lhs++;
        rhs++;
    }

    return (int)(*lhs - *rhs);
}

char* copy(char *beginSource, const char *endSource, char *beginDestination)
{
    while(beginSource < endSource)
    {
        *beginDestination++ = *beginSource++;
    }

    return beginDestination;
}

char *copyStr (char *dest, char *src)
{
    while(*src > 0)
    {
        *dest++ = *src++;
    }

    return dest;
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, bool (*f)(char))
{
    while(beginSource < endSource)
    {
        if(f((int)*beginSource))
        {
            *beginDestination++ = *beginSource++;
        }
    }

    return beginSource;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, bool (*f)(char))
{
    while(rbeginSource > rendSource)
    {
        if(f((int)*rbeginSource))
        {
            *beginDestination++ = *rbeginSource--;
        }
    }

    return rbeginSource;
}

char *getEndOfString(char *s)
{
    char *s1 = s;
    while(*s1 != 0)
    {
        s1++;
    }
    return s1;
}

void removeNonLetters(char *s) 
{
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isNonSpace);
    *destination = '\0';
}

void removeExtraSpaces(char *s)
{
    bool leave_one = false;
    char *destination = s;
    while(s != 0)
    {
        if(isSpace(*s))
        {
            if(!leave_one)
            {
                *destination++ = *s++;
                leave_one = true;
            }
            else
            {
                s++;
            }
        }
        else
        {
            *destination++ = *s++;
            leave_one = false;
        }
    }

    *destination = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word)
{
    if (*word->begin == '\0')
    {
        return 0;
    }

    word->begin = findNonSpace(beginSearch);

    word->end = findSpace(word->begin);
    return 1;
}

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word)
{
    word->begin = findNonSpaceReverse(rbegin, rend);

    if (*word->begin == '\0' && word->begin != rend)
    {
        return 0;
    }

    word->end = findSpace(word->begin);
    return 1;
}

bool isNum(char *sym)
{
    bool answ = false;

    if(*sym >= '0' && *sym <= '9')
    {
        answ = true;
    }

    return answ;
}

void addNumOfSpaces(char *s)
{
    char *destination = s;
    
    while(s != 0)
    {
        if(isNum(s))
        {
            for(int i = 0; i < (int)*s; i++)
            {
                *destination++ = ' ';
            }
        }
        else
        {
            *destination++ = *s++;
        }
    }

    *destination = '\0';
}

void replace(char *source, char *w1, char *w2) 
{
    size_t w1Size = strlen1(w1);
    size_t w2Size = strlen1(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr, _stringBuffer;
    
    if (w1Size >= w2Size) 
    {
        readPtr = source;
        recPtr = source;
    } 
    else 
    {
        copy(source, getEndOfString(source), &_stringBuffer);
        readPtr = &_stringBuffer;
        recPtr = source;
    }
}

int WordsCmp(WordDescriptor w1, WordDescriptor w2)
{
    int cmp;

    while(w1.begin < w1.end && w2.begin < w2.end)
    {
        cmp = (int)*w1.begin - (int)*w2.begin;

        if(cmp != 0)
        {
            break;
        }
        else
        {
            w1.begin++;
            w2.begin++;
        }
    }

    if(w1.begin == w1.end && w2.begin != w2.end)
    {
        cmp = -1;
    }
    else if(w2.begin == w2.end && w1.begin != w1.end)
    {
        cmp = 1;
    }

    return cmp;
}

bool isAlphabeticalOrder(char *str)
{
    bool answ = true;
    WordDescriptor prev, next;

    if(getWord(str, &prev) != 0)
    {
        while(getWord(prev.end, &next) == 1)
        {
            if(WordsCmp(prev, next) > 0)
            {
                answ = false;
                break;
            }

            prev = next;
        }
    }

    return answ;
}

void getBagOfWords(BagOfWords *bag, char *s)
{
    WordDescriptor word;
    bag->size = 0;

    while(getWord(s, &word) == 1)
    {
        bag->words[bag->size] = word;
        s = bag->words[bag->size++].end;
    }

    bag->size--;
}

void printWord(WordDescriptor w)
{
    while(w.begin < w.end)
    {
        printf("%c", *w.begin);
        w.begin++;
    }
}

void PrintWordsBackwards (char *str)
{
    BagOfWords words;
    words.size = 0;

    while(getWord(str, &words.words[words.size]) == 1)
    {
        words.size++;
    }

    for(size_t i = words.size; i > 0; i--)
    {
        printWord(words.words[i - 1]);
    }
}

bool isWordPalindrome (WordDescriptor word)
{
    bool answ = true;
    while(word.begin < word.end)
    {
        if(*word.begin != *(word.end - 1))
        {
            answ = false;
            break;
        }
        else
        {
            word.begin++;
            word.end--;
        }
    }

    return answ;
}

int wordsPalindrome (char *str)
{
    int answ = 0;
    WordDescriptor word;

    while(getWord(str, &word) != 0)
    {
        if(isWordPalindrome(word))
        {
            answ++;
        }
        str = word.end;
    }

    return answ;
}

char *alternatingStringWords (char *s1, char *s2)
{
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2, *output;

    output = malloc(strlen1(s1) + strlen1(s2) + 1);

    while ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found = getWord(beginSearch2, &word2)), isW1Found || isW2Found) 
    {
        if(isW1Found)
        {
            output = copy(word1.begin, word1.end, output);
            beginSearch1 = word1.end;
            *output++ = ' ';
        }

        if(isW2Found)
        {
            output = copy(word2.begin, word2.end, output);
            beginSearch2 = word2.end;
            *output++ = ' ';
        }
    }

    *output = 0;
    
    return output;
}

void reverseWordOrder (char *str)
{
    char *buff = malloc(strlen1(str) + 1), *str_end;
    WordDescriptor word;
    str_end = buff + strlen1(str);
    
    char *src = str;
    char *dest = buff;
    
    while(*src != 0)
    {
        *dest++ = *src++;
    }

    while(getWordReverse(str_end, buff, &word))
    {
        str = copy(word.begin, word.end, str);
    }

    free(buff);
}

bool findSymInWord (char s, WordDescriptor word)
{
    bool answ = false;
    while(word.begin < word.end)
    {
        if(word.begin == &s)
        {
            answ = true;
            break;
        }

        word.begin++;
    }

    return answ;
}

void printWordBeforeFirstWordWithA (char *s)
{
    WordDescriptor prev_word, cur_word;
    bool is_word_with_a = false, first = true;

    while(getWord(s, &cur_word) != 0)
    {
        is_word_with_a = findSymInWord('a', cur_word) || findSymInWord('A', cur_word);

        if(is_word_with_a && !first)
        {
            printWord(prev_word);
            break;
        }

        prev_word = cur_word;

        if(first)
        {
            first = false;
        }

        s = cur_word.end;
    }
}

bool wordCmp (WordDescriptor word1, WordDescriptor word2)
{
    bool is_equal;

    while(word1.begin < word1.end && word2.begin < word2.end)
    {
        if(*word1.begin == *word2.begin)
        {
            word1.begin++;
            word2.begin++;
            is_equal = true;
        }
        else
        {
            is_equal = false;
            break;
        }
    }

    return is_equal;
}

void findWordInOtherString (char *s1, char *s2)
{
    WordDescriptor word1, word2, mem;
    char s1Start = *s1, s2Start = *s2;
    BagOfWords bag;
    bool found_word = false;

    getBagOfWords(&bag, s2);

    while (getWord(&s1Start, &word1) == 1)
    {
        for (size_t i = 0; i < bag.size; i++)
        {
            if(wordCmp(word1, bag.words[i]))
            {
                mem = word1;
                found_word = true;
            }
        }
    }

    if(found_word)
    {
        printWord(mem);
    }
}

// 13
bool FindSameWords (char *s1, char *s2)
{
    WordDescriptor word1, word2;
    char s1Start = *s1, s2Start = *s2;
    BagOfWords bag;
    bool answ = false;

    getBagOfWords(&bag, s2);

    while (getWord(&s1Start, &word1) == 1)
    {
        for (size_t i = 0; i < bag.size; i++)
        {
            if(wordCmp(word1, bag.words[i]))
            {
                answ = true;
                break;
            }
        }
    }

    return answ;
}

void getAllUniqueSortedLetters (WordDescriptor *w)
{
    int count = 1;
    char symMem = *w->begin;
    char *wBegin = w->begin,  *wEnd = w->end;
    char mem[w->end - w->begin];
    bool is_unique;

    mem[0] = symMem;

    while(wBegin < wEnd)
    {
        is_unique = true;

        for(int i = 0; i < count; i++)
        {
            if(wBegin == &mem[i])
            {
                is_unique = false;
                break;
            }
        }

        if(is_unique)
        {
            mem[count++] = *wBegin++;
        }
    }

    copy(&mem[0], &mem[count], w->begin);

    w->end = w->begin + count;
}

void sortSymInWord (WordDescriptor a)
{
    for (char *i = a.begin; i < a.end; i++)
    {
        char *min_position = i;
        char temp;

        for (char *j = i + 1; j < a.end; j++)
        {
            if (*min_position > *j)
            {
                *min_position = *j;
            }

            temp = *min_position;
            *min_position = *i;
            *i = temp;
        }
    }
}

bool FindSameLettersInWords (char *s)
{
    WordDescriptor word, mem;
    char sStart = *s;
    BagOfWords bag;
    bool answ = true;

    char *s_cpy = malloc(strlen1(s) + 1);
    copy(s, s + strlen1(s) + 1, s_cpy);
    
    getBagOfWords(&bag, s_cpy);

    for(size_t i = 0; i < bag.size; i++)
    {
        getAllUniqueSortedLetters(&bag.words[i]);
        sortSymInWord(bag.words[i]);
    }

    for(size_t i = 0; i < bag.size; i++)
    {
        for(size_t j = i + 1; j < bag.size; j++)
        {
            if(WordsCmp(bag.words[i], bag.words[j]) != 0)
            {
                answ = false;
                break;
            }
        }
    }

    free(s_cpy);

    return answ;
}

void getStringFromBag (BagOfWords *w, char *s)
{
    for(size_t i = 0; i < w->size; i++)
    {
        copy(w->words[i].begin, w->words[i].end, s);
        s += w->words[i].end - w->words[i].begin;
        *s++ = ' ';
    }

    *s = 0;
}

// 15
void deleteLastWord (char *s)
{
    WordDescriptor word1, word2;
    char sStart = *s;
    BagOfWords bag, output;

    char *s_cpy = malloc(strlen1(s) + 1);
    copy(s, s + strlen1(s) + 1, s_cpy);

    getBagOfWords(&bag, s_cpy);

    for(size_t i = 0; i < bag.size; i++)
    {   
        if(WordsCmp(bag.words[i], bag.words[bag.size]) != 0)
        {
            output.words[output.size++] = bag.words[i];
        }
    }

    getStringFromBag(&output, s);

    free(s_cpy);
}

// 16
WordDescriptor findWordBeforeFirstFoundWord (char *s1, char *s2)
{
    WordDescriptor word1, word2, prev_word;
    char s1Start = *s1, s2Start = *s2;
    BagOfWords bag1, bag2;

    prev_word.begin = NULL;
    prev_word.end = NULL;

    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);

    for(size_t i = 0; i < bag1.size; i++)
    {
        for(size_t j = 0; j < bag2.size; j++)
        {
            if(wordCmp(bag1.words[i], bag2.words[j]) == 0 && i >= 1)
            {
                prev_word = bag1.words[i - 1];
                break;
            }
        }
    }

    return prev_word;
}

void deleteWord(char *s, WordDescriptor w)
{
    if(*w.end > 0)
    {
        w.end++;
        while(*w.end > 0)
        {
            *w.begin++ = *w.end++;
        }
        
    }
    w.begin = 0;
}

//17
void deletePalindromeWords (char *s)
{
    WordDescriptor word;
    while(getWord(s, &word) == 1)
    {
        if(isWordPalindrome(word))
        {
            deleteWord(s, word);
        }
    }
}

// 18
char *addWordDiffToShorterStr (char *s1, char *s2)
{
    BagOfWords bag1, bag2;
    char *s3, *end;
    size_t amount_words;

    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);

    s3 = malloc(strlen1(s1) + strlen1(s2) + 1);

    if(bag1.size > bag2.size)
    {
        end = copyStr(s3, s2);

        for(size_t i = bag1.size; i <= bag2.size; i++)
        {
            *end++ = ' ';
            copy(bag2.words[i - 1].begin, bag2.words[i - 1].end, end);
            end += bag2.words[i - 1].end - bag2.words[i - 1].begin;
        }
    }
    else if (bag1.size < bag2.size)
    {
        end = copyStr(s3, s1);

        for(size_t i = bag2.size; i <= bag1.size; i++)
        {
            *end++ = ' ';
            copy(bag1.words[i - 1].begin, bag1.words[i - 1].end, end);
            end += bag1.words[i - 1].end - bag1.words[i - 1].begin;
        }
    }
    else // equal
    {
        end = copyStr(s3, s1);
    }

    *end = 0;

    return s3;
}

// 19
bool isLettersInWordPresentInStr (char *s, WordDescriptor word)
{
    getAllUniqueSortedLetters(&word);
    bool answ = false;

    while(*s > 0)
    {
        for(char *i = word.begin; i < word.end; i++)
        {
            if(*s == *i)
            {
                answ = true;
                break;
            }
        }
    }

    return answ;
}
