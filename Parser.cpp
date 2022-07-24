﻿// Parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <AclAPI.h>// This is libclang.
#include <inttypes.h>
#include <clang-c/Index.h>
#include <iostream>
#include <clang-c/Index.h>

using namespace std;

ostream& operator<<(ostream& stream, const CXString& str)
{
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

void recursive(CXCursor cursor) {
    
    CXCursor CXChildVisit_Recurse2;
    clang_visitChildren(
        cursor,
         [](CXCursor c, CXCursor parent, CXClientData client_data)
        {
            cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
                << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
            // CXChildVisit_Recurse;
            return CXChildVisit_Recurse;
        },
        nullptr);

}

int main()
{
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        "header.h", nullptr, 0,
        nullptr, 0,
        CXTranslationUnit_None);
    if (unit == nullptr)
    {
        cerr << "Unable to parse translation unit. Quitting." << endl;
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    
    CXCursor ret = clang_getNullCursor();
    clang_visitChildren(
        cursor,
        [](CXCursor c, CXCursor parent, CXClientData client_data)
        {
            cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
                << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
            return CXChildVisit_Recurse;
        },
        & ret);

    


    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}