/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

        #include "stdio.h"
        #include "stackFrames.h"
        #include "phase4.h"

        void yyerror(char* yaccProvideMessage);
        
        int yylex(void);
        extern int yylineno;
        extern char* yytext;
        extern FILE* yyin;
        int line_number = 0;
        int scope = 0;
        int inloop = 0; /* check if yor are inside a loop ( >0 )*/ 
        int isfunc = 0; /* check for lvalue if it's a function */
        int func_block = 0;
        int funcDefinition = 0;
        int breakstmt = 0;
        char* userFuncName =  NULL;
        int unnamedFunc = 0; /* check if the function is anonymoys */
        int prevOffset = 0; /* It stores the recovered offset */
        stackFrame* topOfStack;
        int loopcounter = 0;

#line 96 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_REALCONST = 5,                  /* REALCONST  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_FUNCTION = 11,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_BREAK = 13,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 14,                  /* CONTINUE  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_LOCAL = 18,                     /* LOCAL  */
  YYSYMBOL_TRUE = 19,                      /* TRUE  */
  YYSYMBOL_FALSE = 20,                     /* FALSE  */
  YYSYMBOL_NIL = 21,                       /* NIL  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 23,                      /* PLUS  */
  YYSYMBOL_MINUS = 24,                     /* MINUS  */
  YYSYMBOL_MUL = 25,                       /* MUL  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_MOD = 27,                       /* MOD  */
  YYSYMBOL_EQUAL = 28,                     /* EQUAL  */
  YYSYMBOL_DIFF = 29,                      /* DIFF  */
  YYSYMBOL_PLUS_PLUS = 30,                 /* PLUS_PLUS  */
  YYSYMBOL_MINUS_MINUS = 31,               /* MINUS_MINUS  */
  YYSYMBOL_GREATER = 32,                   /* GREATER  */
  YYSYMBOL_LESS = 33,                      /* LESS  */
  YYSYMBOL_GREATER_EQUAL = 34,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 35,                /* LESS_EQUAL  */
  YYSYMBOL_LEFT_BRACE = 36,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 37,               /* RIGHT_BRACE  */
  YYSYMBOL_LEFT_BRACKET = 38,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 39,             /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_PARENTHESIS = 40,          /* LEFT_PARENTHESIS  */
  YYSYMBOL_RIGHT_PARENTHESIS = 41,         /* RIGHT_PARENTHESIS  */
  YYSYMBOL_SEMICOLON = 42,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 43,                     /* COMMA  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_D_COLON = 45,                   /* D_COLON  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_D_DOT = 47,                     /* D_DOT  */
  YYSYMBOL_UMINUS = 48,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_stmts = 51,                     /* stmts  */
  YYSYMBOL_stmt = 52,                      /* stmt  */
  YYSYMBOL_expr = 53,                      /* expr  */
  YYSYMBOL_54_1 = 54,                      /* $@1  */
  YYSYMBOL_55_2 = 55,                      /* $@2  */
  YYSYMBOL_56_3 = 56,                      /* $@3  */
  YYSYMBOL_57_4 = 57,                      /* $@4  */
  YYSYMBOL_term = 58,                      /* term  */
  YYSYMBOL_assignexpr = 59,                /* assignexpr  */
  YYSYMBOL_primary = 60,                   /* primary  */
  YYSYMBOL_lvalue = 61,                    /* lvalue  */
  YYSYMBOL_member = 62,                    /* member  */
  YYSYMBOL_call = 63,                      /* call  */
  YYSYMBOL_callsuffix = 64,                /* callsuffix  */
  YYSYMBOL_normcall = 65,                  /* normcall  */
  YYSYMBOL_methodcall = 66,                /* methodcall  */
  YYSYMBOL_elist = 67,                     /* elist  */
  YYSYMBOL_objectdef = 68,                 /* objectdef  */
  YYSYMBOL_indexed = 69,                   /* indexed  */
  YYSYMBOL_indexedelem = 70,               /* indexedelem  */
  YYSYMBOL_block = 71,                     /* block  */
  YYSYMBOL_72_5 = 72,                      /* $@5  */
  YYSYMBOL_73_6 = 73,                      /* $@6  */
  YYSYMBOL_funcname = 74,                  /* funcname  */
  YYSYMBOL_funcprefix = 75,                /* funcprefix  */
  YYSYMBOL_76_7 = 76,                      /* $@7  */
  YYSYMBOL_funcargs = 77,                  /* funcargs  */
  YYSYMBOL_78_8 = 78,                      /* $@8  */
  YYSYMBOL_funcbody = 79,                  /* funcbody  */
  YYSYMBOL_funcdef = 80,                   /* funcdef  */
  YYSYMBOL_const = 81,                     /* const  */
  YYSYMBOL_idlist = 82,                    /* idlist  */
  YYSYMBOL_ifprefix = 83,                  /* ifprefix  */
  YYSYMBOL_elseprefix = 84,                /* elseprefix  */
  YYSYMBOL_ifstmts = 85,                   /* ifstmts  */
  YYSYMBOL_whilestart = 86,                /* whilestart  */
  YYSYMBOL_whilecond = 87,                 /* whilecond  */
  YYSYMBOL_whilestmts = 88,                /* whilestmts  */
  YYSYMBOL_N = 89,                         /* N  */
  YYSYMBOL_M = 90,                         /* M  */
  YYSYMBOL_forprefix = 91,                 /* forprefix  */
  YYSYMBOL_forstmts = 92,                  /* forstmts  */
  YYSYMBOL_loopstart = 93,                 /* loopstart  */
  YYSYMBOL_loopend = 94,                   /* loopend  */
  YYSYMBOL_loopstmt = 95,                  /* loopstmt  */
  YYSYMBOL_returnstmts = 96                /* returnstmts  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   576

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    82,    87,   100,   105,   111,   115,   119,
     123,   129,   143,   155,   159,   164,   170,   172,   177,   182,
     187,   192,   197,   201,   205,   209,   213,   213,   220,   220,
     227,   227,   238,   238,   252,   258,   263,   274,   289,   308,
     327,   347,   367,   373,   397,   403,   407,   411,   416,   422,
     472,   505,   520,   526,   530,   538,   542,   553,   558,   575,
     585,   588,   593,   599,   605,   609,   614,   622,   635,   652,
     656,   663,   672,   672,   690,   690,   714,   718,   725,   725,
     757,   757,   762,   768,   782,   786,   790,   794,   798,   802,
     807,   808,   826,   846,   855,   861,   868,   893,   899,   909,
     933,   939,   942,   951,   971,   972,   973,   978,   986
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "STRING",
  "REALCONST", "ID", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN",
  "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL",
  "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQUAL", "DIFF",
  "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESS", "GREATER_EQUAL",
  "LESS_EQUAL", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET",
  "RIGHT_BRACKET", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON",
  "COMMA", "COLON", "D_COLON", "DOT", "D_DOT", "UMINUS", "$accept",
  "program", "stmts", "stmt", "expr", "$@1", "$@2", "$@3", "$@4", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "objectdef", "indexed", "indexedelem",
  "block", "$@5", "$@6", "funcname", "funcprefix", "$@7", "funcargs",
  "$@8", "funcbody", "funcdef", "const", "idlist", "ifprefix",
  "elseprefix", "ifstmts", "whilestart", "whilecond", "whilestmts", "N",
  "M", "forprefix", "forstmts", "loopstart", "loopend", "loopstmt",
  "returnstmts", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-168)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     167,  -168,  -168,  -168,  -168,   -21,  -168,   -19,  -168,   210,
       1,    11,   286,    55,  -168,  -168,  -168,   286,    -4,    -4,
      27,   240,   263,  -168,    74,    87,   167,  -168,     0,  -168,
    -168,  -168,    25,  -168,    52,  -168,  -168,    53,  -168,  -168,
     167,  -168,    60,  -168,  -168,  -168,  -168,   286,   286,    98,
    -168,   332,  -168,  -168,  -168,  -168,  -168,    94,    39,    52,
      39,    69,   167,   286,   500,   -23,     6,  -168,   374,    67,
    -168,  -168,  -168,  -168,  -168,   286,   286,   286,   286,   286,
    -168,  -168,   286,   286,   286,   286,  -168,   286,  -168,  -168,
     286,   286,   103,   104,  -168,  -168,  -168,   286,   286,   106,
    -168,    77,   107,   286,  -168,   286,   395,   -12,  -168,  -168,
    -168,    73,  -168,   124,   310,  -168,   286,  -168,    80,  -168,
      81,  -168,  -168,   -16,   -16,  -168,  -168,  -168,   286,   286,
     288,   288,   288,   288,   500,   437,     5,  -168,    82,   458,
       9,  -168,   111,  -168,  -168,  -168,   167,   416,   167,  -168,
      16,  -168,  -168,    81,  -168,   286,   500,  -168,   286,   286,
     286,   528,   528,  -168,  -168,   286,  -168,  -168,  -168,    19,
    -168,  -168,  -168,  -168,   286,   479,    54,   541,   515,    58,
    -168,   117,  -168,  -168,   353,  -168,  -168,  -168,  -168,  -168,
    -168,  -168
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    84,    86,    85,    49,     0,    97,     0,    78,     0,
       0,     0,     0,     0,    88,    89,    87,     0,     0,     0,
      74,    64,     0,    15,     0,     0,     2,     5,     0,    34,
      16,    42,    44,    52,    45,    46,    13,     0,    14,    48,
       0,     7,     0,     8,   100,     9,    10,     0,    64,    77,
     107,     0,    11,    12,    37,    50,    36,     0,    38,     0,
      40,     0,     0,     0,    65,     0,     0,    69,     0,     0,
      51,     1,     4,    30,    32,     0,     0,     0,     0,     0,
      26,    28,     0,     0,     0,     0,     6,     0,    39,    41,
       0,    64,     0,     0,    58,    60,    61,     0,    64,     0,
      80,     0,    95,     0,   104,    64,     0,     0,    76,    79,
     108,     0,    73,     0,     0,    67,     0,    68,     0,    35,
      47,   101,   101,    17,    18,    19,    20,    21,     0,     0,
      22,    24,    23,    25,    43,     0,     0,    53,     0,     0,
       0,    55,    90,    82,    83,    94,     0,     0,     0,    99,
       0,    93,   101,     0,    75,     0,    66,    70,    64,     0,
       0,    27,    29,    54,    62,    64,    56,    57,    91,     0,
      96,    98,   105,   100,     0,     0,     0,    31,    33,     0,
      81,     0,   106,   104,     0,    71,    59,    63,    92,   100,
     102,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,    63,   -22,    -9,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,    65,  -168,    84,  -168,  -168,  -168,   -47,  -168,
    -168,    14,    38,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,   -17,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -167,  -115,  -168,  -168,  -168,  -168,   -42,  -168
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,   128,   129,   121,   122,    29,
      30,    31,    32,    33,    34,    94,    95,    96,    65,    35,
      66,    67,    36,    61,    62,   109,    37,    49,   101,   142,
     144,    38,    39,   169,    40,   146,    41,    42,   104,    43,
     105,   159,    44,    45,   148,   182,   149,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   107,     4,    54,    72,    69,   183,   160,    56,    77,
      78,    79,    64,    68,    13,    73,   115,    74,   102,    47,
     116,    48,   191,    75,    76,    77,    78,    79,    80,    81,
     152,   116,    82,    83,    84,    85,    57,   174,   106,    64,
     111,    24,    86,    52,   136,   117,   164,    87,   116,   118,
     167,   140,   116,    53,   114,    88,    89,   173,   150,   116,
     180,    55,   181,    90,   -72,    91,   123,   124,   125,   126,
     127,    92,    93,   130,   131,   132,   133,    90,   134,    91,
      70,   135,    64,    58,    60,    92,    93,    71,   139,    64,
      97,    72,    98,   100,   147,   186,    64,   116,    99,   187,
     103,   116,    59,    59,   108,     8,   112,   156,   120,   137,
     138,   176,   141,    20,   153,   145,    63,   168,   179,   161,
     162,   158,   165,   188,   170,   113,   172,     1,     2,     3,
       4,     5,   157,     6,     7,     8,     9,    10,    11,   143,
      12,   189,    13,    14,    15,    16,   175,     0,    17,    64,
     177,   178,     0,     0,    18,    19,    64,     0,     0,     0,
      20,   154,    21,     0,    22,   184,    23,     0,     0,    24,
       1,     2,     3,     4,     5,     0,     6,     7,     8,     9,
      10,    11,     0,    12,     0,    13,    14,    15,    16,     0,
       0,    17,     0,     0,     0,     0,     0,    18,    19,     0,
       0,     0,     0,    20,     0,    21,     0,    22,     0,    23,
       0,     0,    24,     1,     2,     3,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     0,    13,    14,
      15,    16,     0,     0,    17,     0,     0,     0,     0,     0,
      18,    19,     0,     1,     2,     3,     4,     0,    21,     0,
      22,     0,    50,     0,     0,    24,    12,     0,    13,    14,
      15,    16,     0,     0,    17,     0,     1,     2,     3,     4,
      18,    19,     0,     0,     8,     0,    63,     0,    21,    12,
      22,    13,    14,    15,    16,    24,     0,    17,     0,     1,
       2,     3,     4,    18,    19,     0,     0,     0,     0,     0,
       0,    21,    12,    22,    13,    14,    15,    16,    24,     0,
      17,    75,    76,    77,    78,    79,    18,    19,     0,     0,
     -73,   -73,   -73,   -73,    21,    73,    22,    74,     0,     0,
       0,    24,     0,    75,    76,    77,    78,    79,    80,    81,
       0,     0,    82,    83,    84,    85,     0,    73,     0,    74,
       0,     0,     0,     0,   155,    75,    76,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    73,     0,
      74,     0,     0,     0,   110,     0,    75,    76,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    73,
       0,    74,     0,     0,     0,   190,     0,    75,    76,    77,
      78,    79,    80,    81,     0,     0,    82,    83,    84,    85,
      73,     0,    74,     0,     0,   119,     0,     0,    75,    76,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    73,     0,    74,     0,     0,   151,     0,     0,    75,
      76,    77,    78,    79,    80,    81,     0,     0,    82,    83,
      84,    85,    73,     0,    74,     0,     0,   171,     0,     0,
      75,    76,    77,    78,    79,    80,    81,     0,     0,    82,
      83,    84,    85,    73,     0,    74,   163,     0,     0,     0,
       0,    75,    76,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    73,     0,    74,   166,     0,     0,
       0,     0,    75,    76,    77,    78,    79,    80,    81,     0,
       0,    82,    83,    84,    85,    73,   185,    74,     0,     0,
       0,     0,     0,    75,    76,    77,    78,    79,    80,    81,
      73,     0,    82,    83,    84,    85,     0,     0,    75,    76,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    75,    76,    77,    78,    79,   -73,   -73,     0,     0,
      82,    83,    84,    85,    75,    76,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
       9,    48,     6,    12,    26,    22,   173,   122,    17,    25,
      26,    27,    21,    22,    18,    15,    39,    17,    40,    40,
      43,    40,   189,    23,    24,    25,    26,    27,    28,    29,
      42,    43,    32,    33,    34,    35,    40,   152,    47,    48,
      57,    45,    42,    42,    91,    39,    41,    22,    43,    43,
      41,    98,    43,    42,    63,    30,    31,    41,   105,    43,
      41,     6,    43,    38,    37,    40,    75,    76,    77,    78,
      79,    46,    47,    82,    83,    84,    85,    38,    87,    40,
       6,    90,    91,    18,    19,    46,    47,     0,    97,    98,
      38,   113,    40,    40,   103,    41,   105,    43,    46,    41,
      40,    43,    18,    19,     6,    11,    37,   116,    41,     6,
       6,   158,     6,    36,    41,     8,    36,     6,   165,   128,
     129,    40,    40,     6,   146,    62,   148,     3,     4,     5,
       6,     7,   118,     9,    10,    11,    12,    13,    14,   101,
      16,   183,    18,    19,    20,    21,   155,    -1,    24,   158,
     159,   160,    -1,    -1,    30,    31,   165,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,   174,    42,    -1,    -1,    45,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    14,    -1,    16,    -1,    18,    19,    20,    21,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,    -1,    38,    -1,    40,    -1,    42,
      -1,    -1,    45,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,     3,     4,     5,     6,    -1,    38,    -1,
      40,    -1,    42,    -1,    -1,    45,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    24,    -1,     3,     4,     5,     6,
      30,    31,    -1,    -1,    11,    -1,    36,    -1,    38,    16,
      40,    18,    19,    20,    21,    45,    -1,    24,    -1,     3,
       4,     5,     6,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    16,    40,    18,    19,    20,    21,    45,    -1,
      24,    23,    24,    25,    26,    27,    30,    31,    -1,    -1,
      32,    33,    34,    35,    38,    15,    40,    17,    -1,    -1,
      -1,    45,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    -1,    15,    -1,    17,
      -1,    -1,    -1,    -1,    44,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    15,    -1,
      17,    -1,    -1,    -1,    42,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    15,
      -1,    17,    -1,    -1,    -1,    42,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      15,    -1,    17,    -1,    -1,    41,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    15,    -1,    17,    -1,    -1,    41,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    15,    -1,    17,    -1,    -1,    41,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    39,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    39,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    37,    17,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      15,    -1,    32,    33,    34,    35,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    16,    18,    19,    20,    21,    24,    30,    31,
      36,    38,    40,    42,    45,    50,    51,    52,    53,    58,
      59,    60,    61,    62,    63,    68,    71,    75,    80,    81,
      83,    85,    86,    88,    91,    92,    96,    40,    40,    76,
      42,    53,    42,    42,    53,     6,    53,    40,    61,    63,
      61,    72,    73,    36,    53,    67,    69,    70,    53,    80,
       6,     0,    52,    15,    17,    23,    24,    25,    26,    27,
      28,    29,    32,    33,    34,    35,    42,    22,    30,    31,
      38,    40,    46,    47,    64,    65,    66,    38,    40,    46,
      40,    77,    52,    40,    87,    89,    53,    67,     6,    74,
      42,    80,    37,    51,    53,    39,    43,    39,    43,    41,
      41,    56,    57,    53,    53,    53,    53,    53,    54,    55,
      53,    53,    53,    53,    53,    53,    67,     6,     6,    53,
      67,     6,    78,    71,    79,     8,    84,    53,    93,    95,
      67,    41,    42,    41,    37,    44,    53,    70,    40,    90,
      90,    53,    53,    39,    41,    40,    39,    41,     6,    82,
      52,    41,    52,    41,    90,    53,    67,    53,    53,    67,
      41,    43,    94,    89,    53,    37,    41,    41,     6,    95,
      42,    89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    53,    55,    53,
      56,    53,    57,    53,    53,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    60,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    65,    66,    67,    67,    67,    68,    68,    69,
      69,    70,    72,    71,    73,    71,    74,    74,    76,    75,
      78,    77,    79,    80,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    83,    84,    85,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    96
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     5,     0,     5,     1,     3,     2,     2,     2,     2,
       2,     2,     1,     3,     1,     1,     1,     3,     1,     1,
       2,     2,     1,     3,     4,     3,     4,     4,     2,     6,
       1,     1,     3,     5,     0,     1,     3,     3,     3,     1,
       3,     5,     0,     3,     0,     4,     1,     0,     0,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     1,     3,     4,     1,     2,     4,     1,     3,     3,
       0,     0,     7,     7,     0,     0,     3,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* program: %empty  */
#line 82 "parser.y"
             {
                printf("Program: stmts, Line: %d\n",yylineno);
            }
#line 1395 "parser.c"
    break;

  case 4: /* stmts: stmts stmt  */
#line 87 "parser.y"
                  {
                printf("stmts: stmts stmt Line: %d\n",yylineno);
                if ((yyvsp[0].stm) && (yyvsp[-1].stm)){
                        (yyval.stm)->breakList=mergelist((yyvsp[0].stm)->breakList, (yyvsp[-1].stm)->breakList);
                        (yyval.stm)->contList=mergelist((yyvsp[0].stm)->contList, (yyvsp[-1].stm)->contList);
                }else if((yyvsp[-1].stm)){                    
                        (yyval.stm)=(yyvsp[-1].stm);                      
                }else if((yyvsp[0].stm)){                       
                        (yyval.stm)=(yyvsp[0].stm);
                }else{                       
                        (yyval.stm)=NULL;
                }
        }
#line 1413 "parser.c"
    break;

  case 5: /* stmts: stmt  */
#line 100 "parser.y"
              {
                printf("stmts: stmt Line: %d\n",yylineno);              
                (yyval.stm) = (yyvsp[0].stm);}
#line 1421 "parser.c"
    break;

  case 6: /* stmt: expr SEMICOLON  */
#line 105 "parser.y"
                         {
                shortCircuitEval((yyvsp[-1].expression), yylineno);
                resettemp();
                (yyval.stm) = NULL;
                printf("stmt: Expression semicolon Line: %d\n",yylineno);
        }
#line 1432 "parser.c"
    break;

  case 7: /* stmt: ifstmts  */
#line 111 "parser.y"
                  {
                (yyval.stm) = (yyvsp[0].stm);
                printf("stmt: if statement Line: %d\n",yylineno);
        }
#line 1441 "parser.c"
    break;

  case 8: /* stmt: whilestmts  */
#line 115 "parser.y"
                    {
                (yyval.stm) = NULL;
                printf("stmt: while statement Line: %d\n",yylineno);
        }
#line 1450 "parser.c"
    break;

  case 9: /* stmt: forstmts  */
#line 119 "parser.y"
                  {
                (yyval.stm) = NULL;
                printf("stmt: for statement Line: %d\n",yylineno);
        }
#line 1459 "parser.c"
    break;

  case 10: /* stmt: returnstmts  */
#line 123 "parser.y"
                     {
                /* check on whether you can return based on some scope 
                yyerror();*/
                (yyval.stm) = NULL;
                printf("stmt: return statement Line: %d\n",yylineno);
        }
#line 1470 "parser.c"
    break;

  case 11: /* stmt: BREAK SEMICOLON  */
#line 129 "parser.y"
                         {
                /* check if theres a break statement outside of a loop */
                if(loopcounter == 0){
                        yyerror("Break statement outside of loop");
                }else{
                        breakstmt  = 1;
                        printf("stmt: Break statement Line: %d\n",yylineno);
                }
                (yyvsp[-1].stm) = make_stmt();
                (yyvsp[-1].stm)->breakList = newlist(nextQuad()); 
                emit(jump,NULL,NULL,NULL,nextQuad(),yylineno); 
                (yyval.stm) = (yyvsp[-1].stm);
                
        }
#line 1489 "parser.c"
    break;

  case 12: /* stmt: CONTINUE SEMICOLON  */
#line 143 "parser.y"
                            {
                /* check if theres a break statement outside of a loop */
                if(loopcounter == 0){
                        yyerror("Continue statement outside of loop");
                }else{
                        printf("stmt: Continue statement Line: %d\n",yylineno);
                }
                (yyvsp[-1].stm) = make_stmt();
                (yyvsp[-1].stm)->contList = newlist(nextQuad()); 
                emit(jump,NULL,NULL,NULL,0,yylineno); 
                (yyval.stm) = (yyvsp[-1].stm);
        }
#line 1506 "parser.c"
    break;

  case 13: /* stmt: block  */
#line 155 "parser.y"
               {
                (yyval.stm) = (yyvsp[0].stm);
                printf("stmt: Block of code Line: %d\n",yylineno);
        }
#line 1515 "parser.c"
    break;

  case 14: /* stmt: funcdef  */
#line 159 "parser.y"
                 {
                /* should i increase the scope in this section ?????? */
                (yyval.stm) = NULL;
                printf("stmt: Function (definition) Line: %d\n",yylineno);
        }
#line 1525 "parser.c"
    break;

  case 15: /* stmt: SEMICOLON  */
#line 164 "parser.y"
                    {
                (yyval.stm) = NULL;
                printf(" - - ; - - \n");
        }
#line 1534 "parser.c"
    break;

  case 16: /* expr: assignexpr  */
#line 170 "parser.y"
                                        {       (yyval.expression) = (yyvsp[0].expression); }
#line 1540 "parser.c"
    break;

  case 17: /* expr: expr PLUS expr  */
#line 172 "parser.y"
                                        { 
                                                (yyval.expression) = emit_arithOp(add,(yyvsp[-2].expression),(yyvsp[0].expression),-1,scope,yylineno);
                                                printf("Expression: %f + %f \n", (yyvsp[-2].expression)->numConst,(yyvsp[0].expression)->numConst);
                                        }
#line 1549 "parser.c"
    break;

  case 18: /* expr: expr MINUS expr  */
#line 177 "parser.y"
                                        { 
                                                (yyval.expression) = emit_arithOp(sub,(yyvsp[-2].expression),(yyvsp[0].expression),-1,scope,yylineno);
                                                printf("Expression: %f - %f \n", (yyvsp[-2].expression)->numConst,(yyvsp[0].expression)->numConst);
                                        }
#line 1558 "parser.c"
    break;

  case 19: /* expr: expr MUL expr  */
#line 182 "parser.y"
                                        { 
                                                (yyval.expression) = emit_arithOp(mul,(yyvsp[-2].expression),(yyvsp[0].expression),-1,scope,yylineno);
                                                printf("Expression: %f * %f \n", (yyvsp[-2].expression)->numConst,(yyvsp[0].expression)->numConst);
                                        }
#line 1567 "parser.c"
    break;

  case 20: /* expr: expr DIV expr  */
#line 187 "parser.y"
                                        { 
                                                (yyval.expression) = emit_arithOp(divv,(yyvsp[-2].expression),(yyvsp[0].expression),-1,scope,yylineno);
                                                printf("Expression: %f / %f \n", (yyvsp[-2].expression)->numConst,(yyvsp[0].expression)->numConst);
                                        }
#line 1576 "parser.c"
    break;

  case 21: /* expr: expr MOD expr  */
#line 192 "parser.y"
                                        { 
                                                (yyval.expression) = emit_arithOp(mod,(yyvsp[-2].expression),(yyvsp[0].expression),-1,scope,yylineno);
                                                printf("Expression: %f %% %f \n", (yyvsp[-2].expression)->numConst,(yyvsp[0].expression)->numConst);
                                        }
#line 1585 "parser.c"
    break;

  case 22: /* expr: expr GREATER expr  */
#line 197 "parser.y"
                                        {       printf("Expression:  >  \n"); 
                                                (yyval.expression) = emit_comparisonOp(if_greater, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), -1, scope, yylineno);
                                        }
#line 1593 "parser.c"
    break;

  case 23: /* expr: expr GREATER_EQUAL expr  */
#line 201 "parser.y"
                                        {       printf("Expression:  >=  \n");
                                                (yyval.expression) = emit_comparisonOp(if_greatereq, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), -1, scope, yylineno);
                                        }
#line 1601 "parser.c"
    break;

  case 24: /* expr: expr LESS expr  */
#line 205 "parser.y"
                                        {       printf("Expression:  <  \n");
                                                (yyval.expression) = emit_comparisonOp(if_less, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), -1, scope, yylineno);
                                        }
#line 1609 "parser.c"
    break;

  case 25: /* expr: expr LESS_EQUAL expr  */
#line 209 "parser.y"
                                        {       printf("Expression:  <=  \n");
                                                (yyval.expression) = emit_comparisonOp(if_lesseq, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), -1, scope, yylineno);
                                        }
#line 1617 "parser.c"
    break;

  case 26: /* $@1: %empty  */
#line 213 "parser.y"
                     { shortCircuitEval((yyvsp[-1].expression), yylineno); }
#line 1623 "parser.c"
    break;

  case 27: /* expr: expr EQUAL $@1 expr  */
#line 214 "parser.y"
                                        {       
                                                shortCircuitEval((yyvsp[0].expression),yylineno);
                                                printf("Expression:  ==  \n");
                                                (yyval.expression) = emit_comparisonOp(if_eq, (yyvsp[-3].expression), (yyvsp[0].expression), (yyval.expression), -1, scope, yylineno);
                                        }
#line 1633 "parser.c"
    break;

  case 28: /* $@2: %empty  */
#line 220 "parser.y"
                    { shortCircuitEval((yyvsp[-1].expression), yylineno); }
#line 1639 "parser.c"
    break;

  case 29: /* expr: expr DIFF $@2 expr  */
#line 221 "parser.y"
                                        {       
                                                shortCircuitEval((yyvsp[0].expression), yylineno);
                                                printf("Expression:  !=  \n");
                                                (yyval.expression) = emit_comparisonOp(if_noteq, (yyvsp[-3].expression), (yyvsp[0].expression), (yyval.expression), -1, scope, yylineno);
                                        }
#line 1649 "parser.c"
    break;

  case 30: /* $@3: %empty  */
#line 227 "parser.y"
                   {(yyvsp[-1].expression) = createBoolexpr((yyvsp[-1].expression),nextQuad(), nextQuad()+1, scope, yylineno);}
#line 1655 "parser.c"
    break;

  case 31: /* expr: expr AND $@3 M expr  */
#line 228 "parser.y"
                                        {       
                                                (yyvsp[0].expression) = createBoolexpr((yyvsp[0].expression),nextQuad(), nextQuad()+1, scope, yylineno );                        
                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(scope,yylineno);

                                                patchlist((yyvsp[-4].expression)->truelist,(yyvsp[-1].intVal));
                                                (yyval.expression)->truelist = (yyvsp[0].expression)->truelist;
                                                (yyval.expression)->falselist = mergelist((yyvsp[-4].expression)->falselist,(yyvsp[0].expression)->falselist);
                                        }
#line 1669 "parser.c"
    break;

  case 32: /* $@4: %empty  */
#line 238 "parser.y"
                  { (yyvsp[-1].expression) = createBoolexpr((yyvsp[-1].expression),nextQuad(), nextQuad()+1, scope, yylineno);}
#line 1675 "parser.c"
    break;

  case 33: /* expr: expr OR $@4 M expr  */
#line 239 "parser.y"
                                        {       
                                                (yyvsp[0].expression) = createBoolexpr((yyvsp[0].expression),nextQuad(), nextQuad()+1, scope, yylineno );

                                                (yyval.expression) = newexpr(boolexpr_e);
                                                (yyval.expression)->sym = newtemp(scope,yylineno);

                                                patchlist((yyvsp[-4].expression)->falselist, (yyvsp[-1].intVal));
                                                (yyval.expression)->truelist = mergelist((yyvsp[-4].expression)->truelist,(yyvsp[0].expression)->truelist);
                                                (yyval.expression)->falselist = (yyvsp[0].expression)->falselist;

                                                printf("Expression:  ||  \n");
                                        }
#line 1692 "parser.c"
    break;

  case 34: /* expr: term  */
#line 252 "parser.y"
                                        {       
                                                printf("Expression: term Line: %d\n", yylineno);
                                                (yyval.expression) = (yyvsp[0].expression);
                                        }
#line 1701 "parser.c"
    break;

  case 35: /* term: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 258 "parser.y"
                                                 {
                shortCircuitEval((yyvsp[-1].expression),yylineno);
                (yyval.expression) = (yyvsp[-1].expression);
                printf("term: ( expression ) Line: %d\n",yylineno);              
        }
#line 1711 "parser.c"
    break;

  case 36: /* term: MINUS expr  */
#line 263 "parser.y"
                                 {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith((yyvsp[0].expression), "uminus statement");
                        (yyval.expression) = newexpr(arithexpr_e);
                        (yyval.expression)->sym = newtemp(scope, yylineno);
                        emit(uminus,(yyvsp[0].expression), NULL, (yyval.expression),-1,yylineno);
                }
                printf("term: -lvalue Line: %d\n",yylineno);
        }
#line 1727 "parser.c"
    break;

  case 37: /* term: NOT expr  */
#line 274 "parser.y"
                   {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        (yyvsp[0].expression) = createBoolexpr((yyvsp[0].expression), nextQuad(), nextQuad()+1, scope, yylineno);

                        (yyval.expression) = newexpr(boolexpr_e);
                        (yyval.expression)->sym = newtemp(scope, yylineno);

                        (yyval.expression)->truelist = (yyvsp[0].expression)->falselist;
                        (yyval.expression)->falselist = (yyvsp[0].expression)->truelist;

                        printf("term: !lvalue Line: %d\n",yylineno);
                }
        }
#line 1747 "parser.c"
    break;

  case 38: /* term: PLUS_PLUS lvalue  */
#line 289 "parser.y"
                          {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith((yyvsp[0].expression), "++lvalue");
                        if ((yyvsp[0].expression)->type == tableitem_e) {
                                (yyval.expression) = emit_iftableitem((yyvsp[0].expression),scope, yylineno);
                                emit(add, (yyval.expression), newexpr_constnum(1), (yyval.expression),-1,yylineno);
                                emit(tablesetelem, (yyvsp[0].expression), (yyvsp[0].expression)->index, (yyval.expression),-1,yylineno);
                        }
                        else {
                                emit(add, (yyvsp[0].expression), newexpr_constnum(1), (yyvsp[0].expression), -1, yylineno);
                                (yyval.expression) = newexpr(arithexpr_e);
                                (yyval.expression)->sym = newtemp(scope,yylineno);
                                emit(assign, (yyvsp[0].expression), NULL, (yyval.expression), -1,yylineno);
                        }
                }
                printf("term: ++lvalue Line: %d\n",yylineno);
        }
#line 1771 "parser.c"
    break;

  case 39: /* term: lvalue PLUS_PLUS  */
#line 308 "parser.y"
                          {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }
                check_arith((yyvsp[-1].expression), "lvalue++");
                (yyval.expression) = newexpr(var_e);
                (yyval.expression)->sym = newtemp(scope, yylineno);
                if ((yyvsp[-1].expression) != NULL && (yyvsp[-1].expression)->type == tableitem_e) {
                        expr* val = emit_iftableitem((yyvsp[-1].expression), scope, yylineno);
                        emit(assign, val, NULL, (yyval.expression),-1,yylineno);
                        emit(add, val, newexpr_constnum(1), val,-1,yylineno);
                        emit(tablesetelem, (yyvsp[-1].expression), (yyvsp[-1].expression)->index, val,-1,yylineno);
                }
                else {
                        emit(assign, (yyvsp[-1].expression), NULL, (yyval.expression),-1,yylineno);
                        emit(add, (yyvsp[-1].expression), newexpr_constnum(1), (yyvsp[-1].expression),-1,yylineno);
                }   
                printf("term: lvalue++ Line: %d\n",yylineno);
        }
#line 1795 "parser.c"
    break;

  case 40: /* term: MINUS_MINUS lvalue  */
#line 327 "parser.y"
                            {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith((yyvsp[0].expression), "--lvalue");
                        if ((yyvsp[0].expression)->type == tableitem_e) {
                                (yyval.expression) = emit_iftableitem((yyvsp[0].expression), scope, yylineno);
                                emit(sub, (yyval.expression), newexpr_constnum(1), (yyval.expression),-1,yylineno);
                                emit(tablesetelem, (yyvsp[0].expression), (yyvsp[0].expression)->index, (yyval.expression),-1,yylineno);
                        }
                        else {
                                emit(sub, (yyvsp[0].expression), newexpr_constnum(1), (yyvsp[0].expression), -1, yylineno);
                                (yyval.expression) = newexpr(arithexpr_e);
                                (yyval.expression)->sym = newtemp(scope, yylineno);
                                emit(assign, (yyvsp[0].expression), NULL, (yyval.expression), -1, yylineno);
                        }
                }
                     
                printf("term: --lvalue Line: %d\n",yylineno);
        }
#line 1820 "parser.c"
    break;

  case 41: /* term: lvalue MINUS_MINUS  */
#line 347 "parser.y"
                            {
                if( isfunc == 1){
                        yyerror("Function used as an lvalue");
                }else{
                        check_arith((yyvsp[-1].expression), "lvalue--");
                        (yyval.expression) = newexpr(var_e);
                        (yyval.expression)->sym = newtemp(scope, yylineno);
                        if ((yyvsp[-1].expression)->type == tableitem_e) {
                                expr* val = emit_iftableitem((yyvsp[-1].expression), scope, yylineno);
                                emit(assign, val, NULL, (yyval.expression),-1,yylineno);
                                emit(sub, val, newexpr_constnum(1), val,-1,yylineno);
                                emit(tablesetelem, (yyvsp[-1].expression), (yyvsp[-1].expression)->index, val,-1,yylineno);
                        }
                        else {
                                emit(assign, (yyvsp[-1].expression), NULL, (yyval.expression),-1,yylineno);
                                emit(sub, (yyvsp[-1].expression), newexpr_constnum(1), (yyvsp[-1].expression),-1,yylineno);
                        }  
                }
                printf("term: lvalue-- Line: %d\n",yylineno);
        }
#line 1845 "parser.c"
    break;

  case 42: /* term: primary  */
#line 367 "parser.y"
                 {
                (yyval.expression) = (yyvsp[0].expression);
                printf("term: primary | Line: %d\n",yylineno);
        }
#line 1854 "parser.c"
    break;

  case 43: /* assignexpr: lvalue ASSIGN expr  */
#line 373 "parser.y"
                                    {

                        /* check if the assignment has a function on the left e.g. func f(){}; f=10; */
                        if( isfunc == 1){
                                yyerror("Function used as an lvalue");
                                isfunc = 0;
                        }
                        if( (yyvsp[-2].expression)->type == tableitem_e ){
                                shortCircuitEval((yyvsp[0].expression),yylineno);
                                emit(tablesetelem,(yyvsp[-2].expression)->index,(yyvsp[0].expression),(yyvsp[-2].expression),-1,yylineno);     /*¬ Use result operand for the assigned value*/
                                (yyval.expression) = emit_iftableitem((yyvsp[-2].expression), scope, yylineno);      /* ¬ Will always emit*/
                                (yyval.expression)->type = assignexpr_e;
                        }else {
                                shortCircuitEval((yyvsp[0].expression),yylineno);
                                emit(assign,(yyvsp[0].expression),NULL,(yyvsp[-2].expression),-1,yylineno);        /*that is: lvalue = expr*/
                                (yyval.expression) = newexpr(assignexpr_e);
                                (yyval.expression)->sym = newtemp(scope, yylineno);
                                emit(assign, (yyvsp[-2].expression), NULL, (yyval.expression),-1,yylineno);
                        }
                        
                        printf("assignexpr: lvalue = expression Line: %d\n",yylineno);
                }
#line 1881 "parser.c"
    break;

  case 44: /* primary: lvalue  */
#line 397 "parser.y"
                 {
                /* here we have to check for emit tableitem*/
                (yyval.expression) = emit_iftableitem((yyvsp[0].expression), scope, yylineno);   
                
                printf("primary: lvalue Line: %d\n",yylineno);
        }
#line 1892 "parser.c"
    break;

  case 45: /* primary: call  */
#line 403 "parser.y"
                {
                (yyval.expression) = (yyvsp[0].expression); /* the semantic action assigns $1 (the result of the call rule) to $$ */
                printf("call\n");
        }
#line 1901 "parser.c"
    break;

  case 46: /* primary: objectdef  */
#line 407 "parser.y"
                   {
                /* don't know what is needed here */
                printf("primary: object definition | Line: %d\n",yylineno);
        }
#line 1910 "parser.c"
    break;

  case 47: /* primary: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS  */
#line 411 "parser.y"
                                                    {
                (yyval.expression) = newexpr(programfunc_e);    /* create a new expression of program function type*/
                (yyval.expression)->sym = (yyvsp[-1].symTabEntry);              /* assign the symbol of the function to the expression */
                printf("primary: (function definition) Line: %d\n",yylineno);
        }
#line 1920 "parser.c"
    break;

  case 48: /* primary: const  */
#line 416 "parser.y"
                {
                (yyval.expression) = (yyvsp[0].expression); /* assigns the result of the 'const' rule to $$ */
                printf("primary: const Line: %d\n",yylineno);
        }
#line 1929 "parser.c"
    break;

  case 49: /* lvalue: ID  */
#line 422 "parser.y"
             {
                SymbolTableEntry *entry, *check;
                printf("lvalue -> id Line: %d\n",yylineno);
                isfunc = 0;
                
		SymbolTableEntry *libfunc = checkLibFuncName(yylval.strVal);
		if (libfunc != NULL) {
		        printf("Library function '%s' detected.\n", libfunc->s_name);
		        isfunc = 1;
		        (yyval.expression) = lvalue_expr(libfunc);
		        
    		}else{
			if(scope == 0){
                        	entry = createEntry(yylval.strVal,scope,yylineno,GLOBAL,VAR,1);
                        
                	}else{
                        	entry = createEntry(yylval.strVal,scope,yylineno,LOCL,VAR,1);
              		}

                	entry->offset = currscopeoffset();
                	entry->space = currscopespace();
                	entry->s_name = yylval.strVal;
                	entry->s_scope = scope;
                	entry->line = yylineno;
                	entry->type = var_s;
                
                	(yyval.expression) = NULL;

                	if((check=lookup(entry,"lvalue_ID")) == NULL){
                        
                        	SymbolTableInsert(entry);
                        	inccurrscopeoffset();
                        	(yyval.expression) = lvalue_expr(entry); 
                                                      
                	}else{
                        	if(check->isActive == 0 && check->scope_type != LIBFUNC){
                                	if(check->scope_type != USERFUNC && check->scope_type != GLOBAL){
						yyerror("ID collision");
                        		}
				}else{
                                	printf("Symbol found\n");
                                	if( check->scope_type == USERFUNC){
                                	        isfunc = 1;
                                	}
                                	inccurrscopeoffset();
                                	(yyval.expression) = lvalue_expr(check); 
                        	}
                	}                
        	}
	}
#line 1984 "parser.c"
    break;

  case 50: /* lvalue: LOCAL ID  */
#line 472 "parser.y"
                  {

                SymbolTableEntry *entry, *check;
                printf("lvalue -> local id\n");
                isfunc = 0;
                entry = createEntry((yyvsp[0].strVal),scope,yylineno,LOCL,VAR,1);
                
                entry->offset = currscopeoffset();
                entry->space = currscopespace();
                entry->s_name = (yyvsp[0].strVal);
                entry->s_scope = scope;
                entry->line = yylineno;
                entry->type = var_s;
                
                (yyval.expression) = NULL;

                if((check=lookup(entry,"lvalue_local_ID")) == NULL){
                        SymbolTableInsert(entry);
                        (yyval.expression) = lvalue_expr(entry);
                        inccurrscopeoffset();
                }else{
                        if(check->isActive == 0){
                                yyerror("local ID collision");
                        }else{
                                printf("Symbol found\n");
                                if( check->scope_type == USERFUNC && scope == 0){
                                        isfunc = 1;
                                }
                                (yyval.expression) = lvalue_expr(check);
                                inccurrscopeoffset();
                        }
                }
        }
#line 2022 "parser.c"
    break;

  case 51: /* lvalue: D_COLON ID  */
#line 505 "parser.y"
                    { /* only lookup on scope == 0 */
                SymbolTableEntry *entry, *check;
                printf("lvalue -> :: id\n");
                (yyval.expression) = NULL;
                entry = createEntry((yyvsp[0].strVal),scope,yylineno,GLOBAL,VAR,1);

                check=lookup(entry,"lvalue_d_colon_ID");
                
                if(check->isActive == 0){
                        yyerror("Global ID does not exist");
                }else{
                        printf("Symbol found\n");
                        (yyval.expression) = lvalue_expr(check);
                }              
        }
#line 2042 "parser.c"
    break;

  case 52: /* lvalue: member  */
#line 520 "parser.y"
                {
                (yyval.expression) = (yyvsp[0].expression);
                printf("lvalue: member Line: %d\n",yylineno);
        }
#line 2051 "parser.c"
    break;

  case 53: /* member: lvalue DOT ID  */
#line 526 "parser.y"
                                                        {
                printf("member: lvalue.id Line: %d\n",yylineno);
                (yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].strVal));
        }
#line 2060 "parser.c"
    break;

  case 54: /* member: lvalue LEFT_BRACKET expr RIGHT_BRACKET  */
#line 530 "parser.y"
                                                        {
                printf("member: lvalue[expr] Line: %d\n",yylineno);
                (yyvsp[-3].expression) = emit_iftableitem((yyvsp[-3].expression), scope, yylineno); 
                shortCircuitEval((yyvsp[-1].expression),yylineno);
                (yyval.expression) = newexpr(tableitem_e);
                (yyval.expression)->sym = (yyvsp[-3].expression)->sym;
                (yyval.expression)->index = (yyvsp[-1].expression);
        }
#line 2073 "parser.c"
    break;

  case 55: /* member: call DOT ID  */
#line 538 "parser.y"
                                                        { 
                printf("member: call.id Line: %d\n",yylineno);
                (yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].strVal));
        }
#line 2082 "parser.c"
    break;

  case 56: /* member: call LEFT_BRACKET expr RIGHT_BRACKET  */
#line 542 "parser.y"
                                                        {   
                    
                printf("member: call[expr] Line: %d\n",yylineno);
                (yyvsp[-3].expression) = emit_iftableitem((yyvsp[-3].expression), scope, yylineno); 
                shortCircuitEval((yyvsp[-1].expression),yylineno);
                (yyval.expression) = newexpr(tableitem_e);
                (yyval.expression)->sym = (yyvsp[-3].expression)->sym;
                (yyval.expression)->index = (yyvsp[-1].expression);
        }
#line 2096 "parser.c"
    break;

  case 57: /* call: call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 553 "parser.y"
                                                       {
                printf("call: call(elist) Line: %d",yylineno);
                (yyvsp[-1].expression) = reverseElist((yyvsp[-1].expression));
                (yyval.expression) = make_call((yyvsp[-3].expression), (yyvsp[-1].expression), scope, yylineno);
          }
#line 2106 "parser.c"
    break;

  case 58: /* call: lvalue callsuffix  */
#line 558 "parser.y"
                           {

                (yyvsp[-1].expression) = emit_iftableitem((yyvsp[-1].expression), scope, yylineno); /* in case it was a table item too */
                

                if ((yyvsp[0].calls)->method){

                        get_last((yyvsp[0].calls)->elist)->next = (yyvsp[-1].expression);  /*insert first (reversed, so from last) */
                        (yyvsp[-1].expression) = emit_iftableitem(member_item((yyvsp[-1].expression), (yyvsp[0].calls)->name), scope, yylineno);
                }
		printf("sym->name: %s, sym->type: %d (expecting LIBFUNC=%d)\n", (yyvsp[-1].expression)->sym->s_name, (yyvsp[-1].expression)->sym->type, LIBFUNC);

               
                (yyval.expression) = make_call((yyvsp[-1].expression), (yyvsp[0].calls)->elist, scope, yylineno);
                printf("call: lvalue callsuffix Line: %d\n",yylineno);
                }
#line 2127 "parser.c"
    break;

  case 59: /* call: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 575 "parser.y"
                                                                                                {
                
                printf("call: (funcdef)(elist) Line: %d\n",yylineno);
                expr* func = newexpr(programfunc_e);
                func->sym = (yyvsp[-4].symTabEntry);
                (yyvsp[-1].expression) = reverseElist((yyvsp[-1].expression));
                (yyval.expression) = make_call(func, (yyvsp[-1].expression), scope, yylineno); /* here it may needed to put $5 in a reverse elist func */
                }
#line 2140 "parser.c"
    break;

  case 60: /* callsuffix: normcall  */
#line 585 "parser.y"
                           { printf("callsuffix: Normal call Line: %d\n",yylineno);
                        (yyval.calls) = (yyvsp[0].calls);
                }
#line 2148 "parser.c"
    break;

  case 61: /* callsuffix: methodcall  */
#line 588 "parser.y"
                               {printf("Method call\n");
                        (yyval.calls) = (yyvsp[0].calls);
                }
#line 2156 "parser.c"
    break;

  case 62: /* normcall: LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 593 "parser.y"
                                                          {
                        (yyval.calls) = new_call((yyvsp[-1].expression),0,NULL);
                        printf("normcall: (elist) Line: %d\n",yylineno);
                }
#line 2165 "parser.c"
    break;

  case 63: /* methodcall: D_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 599 "parser.y"
                                                                   {
                        (yyval.calls) = new_call((yyvsp[-1].expression),1,(yyvsp[-3].strVal));
                        printf("methodcall: ..id(elist) Line: %d\n",yylineno);
                }
#line 2174 "parser.c"
    break;

  case 64: /* elist: %empty  */
#line 605 "parser.y"
          {
                (yyval.expression)=NULL;
                printf("empty elist\n");
        }
#line 2183 "parser.c"
    break;

  case 65: /* elist: expr  */
#line 609 "parser.y"
               { 
                shortCircuitEval((yyvsp[0].expression),yylineno);
                printf("elist: expr Line: %d\n",yylineno);
                (yyval.expression)=(yyvsp[0].expression);
        }
#line 2193 "parser.c"
    break;

  case 66: /* elist: elist COMMA expr  */
#line 614 "parser.y"
                          {
                printf("elist: elist comma expr Line: %d\n",yylineno);
                shortCircuitEval((yyvsp[0].expression),yylineno);
                (yyvsp[0].expression)->next = (yyvsp[-2].expression);
                (yyval.expression) = (yyvsp[0].expression);
        }
#line 2204 "parser.c"
    break;

  case 67: /* objectdef: LEFT_BRACKET elist RIGHT_BRACKET  */
#line 622 "parser.y"
                                                  {
                        expr* t = newexpr(newtable_e);
                        t->sym = newtemp(scope,yylineno);
                        emit(tablecreate,NULL,NULL,t,-1,yylineno);

                        expr* list = reverseElist((yyvsp[-1].expression));

                        for(int i=0;list;list=list->next){
                                emit(tablesetelem,newexpr_constnum(i++),list,t,-1,yylineno);
                        }
                        (yyval.expression) = t;
                        printf("[elist]\n");
                }
#line 2222 "parser.c"
    break;

  case 68: /* objectdef: LEFT_BRACKET indexed RIGHT_BRACKET  */
#line 635 "parser.y"
                                                    {
                        struct tablepair* ind;
                        expr* t = newexpr(newtable_e);
                        t->sym = newtemp(scope,yylineno);
                        emit(tablecreate,NULL,NULL,t,-1,yylineno);

                        ind = reverseIndexed((yyvsp[-1].tablepair));

                        while(ind!=NULL){                               
                                emit(tablesetelem,ind->key,ind->value,t,-1,yylineno);                                
                                ind = ind->next;
                        }
                        (yyval.expression) = t;
                        printf("[indexed]\n");
                }
#line 2242 "parser.c"
    break;

  case 69: /* indexed: indexedelem  */
#line 652 "parser.y"
                      {
               (yyval.tablepair) = (yyvsp[0].tablepair);
               printf("indexed: indexedelem Line: %d\n",yylineno); 
        }
#line 2251 "parser.c"
    break;

  case 70: /* indexed: indexed COMMA indexedelem  */
#line 656 "parser.y"
                                  {
                (yyvsp[0].tablepair)->next = (yyvsp[-2].tablepair);
                (yyval.tablepair) = (yyvsp[0].tablepair);
                printf("indexed: indexed,indexedelem Line: %d\n",yylineno);  
        }
#line 2261 "parser.c"
    break;

  case 71: /* indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE  */
#line 663 "parser.y"
                                                        {
                        shortCircuitEval((yyvsp[-3].expression),yylineno);
                        shortCircuitEval((yyvsp[-1].expression),yylineno);

                        printf("indexedelem: { expr : expr } Line: %d\n",yylineno);
                        (yyval.tablepair) = make_pair((yyvsp[-3].expression),(yyvsp[-1].expression));
                }
#line 2273 "parser.c"
    break;

  case 72: /* $@5: %empty  */
#line 672 "parser.y"
                      { // if the brackets {} are empty the scope stays the same since it increases by 1 and decreases by 1 immediately
                if(funcDefinition != 1){
                        scope++;
                }else{
                        funcDefinition = 0;
                }
                
        }
#line 2286 "parser.c"
    break;

  case 73: /* block: LEFT_BRACE $@5 RIGHT_BRACE  */
#line 679 "parser.y"
                        { 
                /* hide function */
                HideSymbolsAtScope(scope);
                scope--;
                if(func_block == 1){
                        popStack();
                        func_block = 0;
                }
                
                printf("block: {} Line: %d\n",yylineno); 
        }
#line 2302 "parser.c"
    break;

  case 74: /* $@6: %empty  */
#line 690 "parser.y"
                     {
                        printf("block: Left brace Line: %d\n",yylineno);
                        if(funcDefinition != 1){
                                scope++;
                        }else{
                                funcDefinition = 0;
                        }
                }
#line 2315 "parser.c"
    break;

  case 75: /* block: LEFT_BRACE $@6 stmts RIGHT_BRACE  */
#line 699 "parser.y"
                            {
                        /* hide function */
                        HideSymbolsAtScope(scope);
                        scope--;
                        
                        if(func_block == 1){
                                popStack();
                                func_block = 0;
                        }
                        
                        (yyval.stm) = (yyvsp[-1].stm);
                        printf("block: { statement } Line: %d\n",yylineno);
                }
#line 2333 "parser.c"
    break;

  case 76: /* funcname: ID  */
#line 714 "parser.y"
             {
                (yyval.strVal) = (yyvsp[0].strVal);
                unnamedFunc = 0;
        }
#line 2342 "parser.c"
    break;

  case 77: /* funcname: %empty  */
#line 718 "parser.y"
          {
                userFuncName = generateName();
                (yyval.strVal) = userFuncName;
                unnamedFunc = 1;
                
        }
#line 2353 "parser.c"
    break;

  case 78: /* $@7: %empty  */
#line 725 "parser.y"
                          {funcDefinition = 1;}
#line 2359 "parser.c"
    break;

  case 79: /* funcprefix: FUNCTION $@7 funcname  */
#line 725 "parser.y"
                                                         {
                        SymbolTableEntry *entry = createEntry((yyvsp[0].strVal),scope,yylineno,USERFUNC,FUNC,0), *check;
                        entry->value.funcVal->iaddress = nextQuad();

                        (yyval.symTabEntry) = entry;
                        if(unnamedFunc == 1){ /* we can combine if else with if(unnamedFunc == 1 || (check=lookup(entry,"funcdef")) == NULL )*/
                                SymbolTableInsert(entry);
                                printf("Symbol Inserted in line: %d\n", yylineno);
                                pushStack(entry->s_name, entry->s_scope,currscopeoffset()); /*save current offset*/
                                emit(funcstart, lvalue_expr((yyval.symTabEntry)),NULL, NULL, 0, yylineno );
                                enterscopespace();              /*Entering function arguments scope space*/
                                resetformalargsoffset();        /*Start formals from zero*/

                        }else{
                                if((check=lookup(entry,"funcdef")) == NULL){
                                        SymbolTableInsert(entry);
                                        printf("Symbol Inserted in line: %d\n", yylineno);
                                        pushStack(entry->s_name, entry->s_scope,currscopeoffset()); /*save current offset*/
                                        emit(funcstart, lvalue_expr((yyval.symTabEntry)),NULL, NULL, 0, yylineno );
                                        enterscopespace();      /*Entering function arguments scope space*/
                                        resetformalargsoffset();        /*Start formals from zero*/
                                }else{
                                        if(check->isActive == 0){
                                                yyerror("Name of function already exists");
                                        }else{
                                                printf("Symbol found\n");
                                        }
                                }
                        }
                        printf("funcprefix: FUNCTION funcname Line: %d\n",yylineno);
                }
#line 2395 "parser.c"
    break;

  case 80: /* $@8: %empty  */
#line 757 "parser.y"
                                   {scope++;}
#line 2401 "parser.c"
    break;

  case 81: /* funcargs: LEFT_PARENTHESIS $@8 idlist RIGHT_PARENTHESIS  */
#line 757 "parser.y"
                                                                      { 
                        func_block = 1;	
                        enterscopespace();              /* Now entering function locals space */
                        resetfunctionlocaloffset();    /* Start counting locals from zero */
                }
#line 2411 "parser.c"
    break;

  case 82: /* funcbody: block  */
#line 762 "parser.y"
                       { 
                        (yyval.undef) = currscopeoffset();  /* Extract #total locals */
                        exitscopespace();       /* Exiting function locals space */
                        funcDefinition = 0;
                }
#line 2421 "parser.c"
    break;

  case 83: /* funcdef: funcprefix funcargs funcbody  */
#line 768 "parser.y"
                                      { 

                exitscopespace();                              /* Exiting function definition space */
                (yyvsp[-2].symTabEntry)->value.funcVal->totalLocals = (yyvsp[0].undef);                           /* Store #locals in symbol entry */
                topOfStack = popStack();        /* pop and get pre scope offset */
                prevOffset = topOfStack->scopeOffset;
                restorecurrscopeoffset(prevOffset);            /* Restore previous scope offset */
                (yyval.symTabEntry) = (yyvsp[-2].symTabEntry);                                        /* The function definition returns the symbol */
                emit(funcend, lvalue_expr((yyvsp[-2].symTabEntry)), NULL, NULL, 0, yylineno);

                printf("function (idlist) block\n");        
        }
#line 2438 "parser.c"
    break;

  case 84: /* const: INTEGER  */
#line 782 "parser.y"
                        {
                (yyval.expression) = newexpr_constnum(yylval.intVal);
                printf("Integer\n");
        }
#line 2447 "parser.c"
    break;

  case 85: /* const: REALCONST  */
#line 786 "parser.y"
                        {
                (yyval.expression) = newexpr_constnum(yylval.floatVal);
                printf("Real number\n");
        }
#line 2456 "parser.c"
    break;

  case 86: /* const: STRING  */
#line 790 "parser.y"
                        {
                (yyval.expression) = newexpr_conststring(yylval.strVal);
                printf("String %s\n",yylval.strVal);}
#line 2464 "parser.c"
    break;

  case 87: /* const: NIL  */
#line 794 "parser.y"
                        {
                (yyval.expression) = newexpr(nil_e);
                printf("Nil\n");}
#line 2472 "parser.c"
    break;

  case 88: /* const: TRUE  */
#line 798 "parser.y"
                        {
                (yyval.expression) = newexpr_constbool(1);
                printf("True\n");}
#line 2480 "parser.c"
    break;

  case 89: /* const: FALSE  */
#line 802 "parser.y"
                        {
                (yyval.expression) = newexpr_constbool(0);
                printf("False\n");}
#line 2488 "parser.c"
    break;

  case 91: /* idlist: ID  */
#line 808 "parser.y"
           {
                SymbolTableEntry *entry, *check;
                printf("lvalue -> id\n");

                
                entry = createEntry(yylval.strVal,scope,yylineno,FORMAL,VAR,1);
                
                if((check=lookup(entry,"formal_arg")) == NULL){
                        SymbolTableInsert(entry);
                        printf("Symbol Inserted\n");
                }else{
                        if(check->isActive == 0){
                                yyerror("ID collision\n");
                        }else{
                                printf("Symbol found\n");
                        }
                }
        }
#line 2511 "parser.c"
    break;

  case 92: /* idlist: idlist COMMA ID  */
#line 826 "parser.y"
                         {
                SymbolTableEntry *entry, *check;
                printf("lvalue -> id\n");

                
                entry = createEntry((yyvsp[0].strVal),scope,yylineno,FORMAL,VAR,1);
                
                if((check=lookup(entry,"formal_arg")) == NULL){
                        SymbolTableInsert(entry);
                        printf("Symbol Inserted\n");
                }else{
                        if(check->isActive == 0){
                                yyerror("ID collision");
                        }else{
                                printf("Symbol found\n");
                        }
                }
        }
#line 2534 "parser.c"
    break;

  case 93: /* ifprefix: IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 846 "parser.y"
                                                            {
                        /* check if $3(expr) is equal to true and set label as +2 positions */
                        shortCircuitEval((yyvsp[-1].expression),yylineno);
                        emit(if_eq, (yyvsp[-1].expression), newexpr_constbool(1), NULL, nextQuad()+2,yylineno);
                        (yyval.undef) = nextQuad();
                        emit(jump, NULL, NULL, NULL, 0, yylineno );
                }
#line 2546 "parser.c"
    break;

  case 94: /* elseprefix: ELSE  */
#line 855 "parser.y"
                      {
                        (yyval.undef) = nextQuad();
                        emit(jump, NULL, NULL, NULL, 0, yylineno);

                }
#line 2556 "parser.c"
    break;

  case 95: /* ifstmts: ifprefix stmt  */
#line 861 "parser.y"
                        {
                /* $1 should have $ifprefix in order to patch the label */
                patchlabel((yyvsp[-1].undef), nextQuad());
                (yyval.stm) = make_stmt();
                (yyval.stm) = (yyvsp[0].stm);
                printf("if (expr) stmts\n");
        }
#line 2568 "parser.c"
    break;

  case 96: /* ifstmts: ifprefix stmt elseprefix stmt  */
#line 868 "parser.y"
                                        { 

                /* $1 should have $ifprefix in order to patch the label */
                /*  $3 should have $elseprefix in order to patch the other label*/
                
                patchlabel((yyvsp[-3].undef), (yyvsp[-1].undef)+1);
                patchlabel((yyvsp[-1].undef), nextQuad());

                (yyval.stm) = make_stmt();
                
                if ((yyvsp[-2].stm) && (yyvsp[0].stm)){
                        (yyval.stm)->breakList=mergelist((yyvsp[-2].stm)->breakList, (yyvsp[0].stm)->breakList);
                        (yyval.stm)->contList=mergelist((yyvsp[-2].stm)->contList, (yyvsp[0].stm)->contList);
                }else if((yyvsp[-2].stm)){                       
                        (yyval.stm) = (yyvsp[-2].stm);                      
                }else if((yyvsp[0].stm)){                       
                        (yyval.stm) = (yyvsp[0].stm);
                }else{                       
                    (yyval.stm)=NULL;
                }
                printf("if (expr) stmts else stmts");
                
        }
#line 2596 "parser.c"
    break;

  case 97: /* whilestart: WHILE  */
#line 893 "parser.y"
                       {
                        (yyval.undef) = nextQuad();
                        printf("whilestart: WHILE Line: %d\n",yylineno);
                }
#line 2605 "parser.c"
    break;

  case 98: /* whilecond: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 899 "parser.y"
                                                         {
                        shortCircuitEval((yyvsp[-1].expression),yylineno);
                        emit(if_eq, (yyvsp[-1].expression), newexpr_constbool(1), NULL, nextQuad()+2, yylineno);
                        (yyval.undef) = nextQuad();
                        emit(jump, NULL, NULL, NULL, 0, yylineno);
                        inloop++;
                        printf("opening while statement\n");
                }
#line 2618 "parser.c"
    break;

  case 99: /* whilestmts: whilestart whilecond loopstmt  */
#line 909 "parser.y"
                                               {

                        /* $1 because the jump should be at while start unless there is a break/continue*/
                        emit(jump, NULL, NULL,NULL,(yyvsp[-2].undef),yylineno);
                        patchlabel((yyvsp[-1].undef),nextQuad());             

                        if((yyvsp[0].stm) && (yyvsp[0].stm)->breakList ){
                                patchlist((yyvsp[0].stm)->breakList, nextQuad());
                        }
                        
                        if((yyvsp[0].stm) && (yyvsp[0].stm)->contList){
                                patchlist((yyvsp[0].stm)->contList,  (yyvsp[-2].undef));
                        }

                        if(breakstmt == 1){
                                breakstmt = 0;
                        }else{
                                inloop--;
                        }
                        
                        printf("closing while statement\n");
                }
#line 2645 "parser.c"
    break;

  case 100: /* N: %empty  */
#line 933 "parser.y"
                 { 
                 (yyval.intVal) = nextQuad();
                 emit(jump,NULL,NULL,NULL,0,yylineno); 
                }
#line 2654 "parser.c"
    break;

  case 101: /* M: %empty  */
#line 939 "parser.y"
                  { (yyval.intVal) = nextQuad();}
#line 2660 "parser.c"
    break;

  case 102: /* forprefix: FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON  */
#line 942 "parser.y"
                                                                       {
                        shortCircuitEval((yyvsp[-1].expression),yylineno);
                        (yyval.forloop) = (struct forloop*)malloc(sizeof(struct forloop));
                        (yyval.forloop)->test = (yyvsp[-2].intVal);
                        (yyval.forloop)->enter = nextQuad();
                        emit(if_eq,(yyvsp[-1].expression),newexpr_constbool(1),NULL,0,yylineno);
                }
#line 2672 "parser.c"
    break;

  case 103: /* forstmts: forprefix N elist RIGHT_PARENTHESIS N loopstmt N  */
#line 951 "parser.y"
                                                                  {
                        patchlabel((yyvsp[-6].forloop)->enter, (yyvsp[-2].intVal)+1);
                        patchlabel((yyvsp[-5].intVal), nextQuad());
                        patchlabel((yyvsp[-2].intVal), (yyvsp[-6].forloop)->test);
                        patchlabel((yyvsp[0].intVal), (yyvsp[-5].intVal)+1);

                        if ((yyvsp[-1].stm) && (yyvsp[-1].stm)->breakList){
                                patchlist((yyvsp[-1].stm)->breakList, nextQuad());
                        }
                        
                        if((yyvsp[-1].stm) && (yyvsp[-1].stm)->contList){
                                patchlist((yyvsp[-1].stm)->contList, (yyvsp[-5].intVal)+1);
                        }
                        if(breakstmt == 1){
                                breakstmt = 0;
                        }                     
                        printf("for (elist; expr; elist) stmts\n");
                }
#line 2695 "parser.c"
    break;

  case 104: /* loopstart: %empty  */
#line 971 "parser.y"
                 {++loopcounter;}
#line 2701 "parser.c"
    break;

  case 105: /* loopend: %empty  */
#line 972 "parser.y"
                 {--loopcounter;}
#line 2707 "parser.c"
    break;

  case 106: /* loopstmt: loopstart stmt loopend  */
#line 973 "parser.y"
                                        {
                        printf("loopstmt: loopstart stmt loopend Line: %d\n",yylineno);
                        (yyval.stm)=(yyvsp[-1].stm);
                }
#line 2716 "parser.c"
    break;

  case 107: /* returnstmts: RETURN SEMICOLON  */
#line 978 "parser.y"
                                   {
                        if(func_block != 0){
                                emit(ret, NULL,NULL,NULL,-1,yylineno); 
                                printf("returnstmts: return; Line: %d\n",yylineno);
                        }else{
                                yyerror("Return statement outside function\n");
                        }
                }
#line 2729 "parser.c"
    break;

  case 108: /* returnstmts: RETURN expr SEMICOLON  */
#line 986 "parser.y"
                                       {
                        if(func_block != 0){
                                shortCircuitEval((yyvsp[-1].expression),yylineno);
                                emit(ret, NULL,NULL,(yyvsp[-1].expression),-1,yylineno);
                                printf("returnstmts: return expr; Line: %d\n",yylineno);
                        }else{
                                yyerror("Return statement outside function\n");
                        }
                }
#line 2743 "parser.c"
    break;


#line 2747 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 997 "parser.y"


void yyerror(char* yaccProvideMessage){
        fprintf(stderr, "\033[31mError: %s: at line %d, before token %s\033[0m ", yaccProvideMessage, yylineno, yytext);
        fprintf(stderr,"\n");
}



int main(int argc, char **argv){

        if(argc>1){
                if(!(yyin = fopen(argv[1],"r"))){
                        fprintf(stderr,"Cannot read file: %s\n", argv[1]);
                        return 1;
                }
        }else{
                yyin = stdin;
        }
        insertLibFunctions();
        yyparse();
        printSymbolTable();
        printQuads();
        generateInstr();
        createPrintFile("file.bin");
        file_read_Arrays("file.bin");
        return 0;
}
