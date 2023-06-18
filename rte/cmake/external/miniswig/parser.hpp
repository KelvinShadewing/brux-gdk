/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_UJ_BRUX_GDK_RTE_CMAKE_EXTERNAL_MINISWIG_PARSER_HPP_INCLUDED
# define YY_YY_HOME_UJ_BRUX_GDK_RTE_CMAKE_EXTERNAL_MINISWIG_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_INT = 258,                   /* T_INT  */
    T_FLOAT = 259,                 /* T_FLOAT  */
    T_STRING = 260,                /* T_STRING  */
    T_ID = 261,                    /* T_ID  */
    T_ATOMIC_TYPE = 262,           /* T_ATOMIC_TYPE  */
    T_NAMESPACEREF = 263,          /* T_NAMESPACEREF  */
    T_CLASS = 264,                 /* T_CLASS  */
    T_STRUCT = 265,                /* T_STRUCT  */
    T_STATIC = 266,                /* T_STATIC  */
    T_SUSPEND = 267,               /* T_SUSPEND  */
    T_CUSTOM = 268,                /* T_CUSTOM  */
    T_CONST = 269,                 /* T_CONST  */
    T_UNSIGNED = 270,              /* T_UNSIGNED  */
    T_SIGNED = 271,                /* T_SIGNED  */
    T_VOID = 272,                  /* T_VOID  */
    T_BOOL = 273,                  /* T_BOOL  */
    T_CHAR = 274,                  /* T_CHAR  */
    T_SHORT = 275,                 /* T_SHORT  */
    T_LONG = 276,                  /* T_LONG  */
    T_DOUBLE = 277,                /* T_DOUBLE  */
    T_PUBLIC = 278,                /* T_PUBLIC  */
    T_PROTECTED = 279,             /* T_PROTECTED  */
    T_PRIVATE = 280,               /* T_PRIVATE  */
    T_NAMESPACE = 281,             /* T_NAMESPACE  */
    T_DDCOL = 282                  /* "::"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "/home/uj/brux-gdk/rte/external/miniswig/src/parser.yy"

    char*       str;
    int         ival;
    float       fval;
    Class*      _class;
    Function*   function;
    Field*      field;
    Type*       type;
    AtomicType* atomic_type;
    Namespace*  _namespace;

#line 103 "/home/uj/brux-gdk/rte/cmake/external/miniswig/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void);


#endif /* !YY_YY_HOME_UJ_BRUX_GDK_RTE_CMAKE_EXTERNAL_MINISWIG_PARSER_HPP_INCLUDED  */
