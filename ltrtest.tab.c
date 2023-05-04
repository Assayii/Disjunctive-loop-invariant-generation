/* A Bison parser, made by GNU Bison 3.7.5.  */

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "ltrtest.y"

#include <iostream>
#include "var-info.h"
#include "Location.h"
#include "PolyUtils.h"
#include "TransitionRelation.h"
#include "InvariantMap.h"
#include "DualInvariantMap.h"
#include "System.h"
#include "Timer.h"
#include "ppl.hh"
   
   
   using namespace std;
   using namespace Parma_Polyhedra_Library;
   using namespace Parma_Polyhedra_Library::IO_Operators;

   bool gendrop;
   int num_context;
   bool zero;
   bool one;
   int prop_steps;
   int weave_time;
   bool ch79,bhrz03,dual;
   
   C_Polyhedron * trivial, *dualp;
   
#ifndef MAX_ID_SIZE
#define MAX_ID_SIZE 100
#endif
   
#define ONECONTEXT 0
#define GENDROP 1
#define MANYCONTEXT 2
#define BULLSHIT 3
#define RESIDUAL_TR_SYS 4
#define ZERO_ONLY 5
#define ONE_ONLY 6
#define ZERO_ONE 7
#define NO_INSTANTIATION 8
#define NO_CH79 9
#define NO_BHRZ03 10
#define NO_DUAL 11
#define YES_CH79 12
#define YES_BHRZ03 13
#define YES_DUAL 14
#define INV_CHECK 15
#define NO_INV_CHECK 16
   
   
   
   char err_str[100];
   extern int linenum;
   int dimension;
   var_info * f, *fd, *fm;
   vector<Location *> * loclist;
   vector<TransitionRelation *> * trlist;
   Context *glc;// The global context
   vector<Context *>* children;
   vector<System *> * global_sub_system_list;
   System * global_system;
   Timer weave_timer;
   int * tt;
   C_Polyhedron * invd;

   bool inv_check;
   
   
   extern int yyparse();
   extern int yylex();
   void yyerror(char const * x);
   void yyerror(string  const & x);
   void parseinit();
   void collect_generators(vector<Context *> * children , Generator_System & g);
   int parse_cmd_line(char * x);
   int weave_count;
   int bang_count;
   int prune_count;
   int clump_prune_count;
   int context_count;
   bool search_location(char * w, Location ** m);
   bool search_transition_relation(char * w, TransitionRelation ** m);
   int find_variable( char* what);
   void add_preloc_invariants_to_transitions();
   void print_status();
   void print_bake_off(InvariantMap const & what);
   
   void check_invariant_ok();
   

#line 162 "ltrtest.tab.c"

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

#include "ltrtest.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_PRIME = 5,                      /* PRIME  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_VARIABLED = 7,                  /* VARIABLED  */
  YYSYMBOL_LOCATION = 8,                   /* LOCATION  */
  YYSYMBOL_TRANSITION = 9,                 /* TRANSITION  */
  YYSYMBOL_EQ = 10,                        /* EQ  */
  YYSYMBOL_LEQ = 11,                       /* LEQ  */
  YYSYMBOL_GEQ = 12,                       /* GEQ  */
  YYSYMBOL_LE = 13,                        /* LE  */
  YYSYMBOL_GE = 14,                        /* GE  */
  YYSYMBOL_PRES = 15,                      /* PRES  */
  YYSYMBOL_PROPS = 16,                     /* PROPS  */
  YYSYMBOL_INVARIANT = 17,                 /* INVARIANT  */
  YYSYMBOL_18_ = 18,                       /* '+'  */
  YYSYMBOL_19_ = 19,                       /* '-'  */
  YYSYMBOL_20_ = 20,                       /* '*'  */
  YYSYMBOL_UMINUS = 21,                    /* UMINUS  */
  YYSYMBOL_22_ = 22,                       /* '['  */
  YYSYMBOL_23_ = 23,                       /* ']'  */
  YYSYMBOL_24_ = 24,                       /* '('  */
  YYSYMBOL_25_ = 25,                       /* ')'  */
  YYSYMBOL_26_ = 26,                       /* ':'  */
  YYSYMBOL_27_ = 27,                       /* ','  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_program = 29,                   /* program  */
  YYSYMBOL_header = 30,                    /* header  */
  YYSYMBOL_31_1 = 31,                      /* $@1  */
  YYSYMBOL_optional_commands = 32,         /* optional_commands  */
  YYSYMBOL_dimvector = 33,                 /* dimvector  */
  YYSYMBOL_system_descriptor = 34,         /* system_descriptor  */
  YYSYMBOL_location_descriptor = 35,       /* location_descriptor  */
  YYSYMBOL_transition_descriptor = 36,     /* transition_descriptor  */
  YYSYMBOL_invariant_descriptor = 37,      /* invariant_descriptor  */
  YYSYMBOL_location_identifier = 38,       /* location_identifier  */
  YYSYMBOL_transition_identifier = 39,     /* transition_identifier  */
  YYSYMBOL_linear_assertion = 40,          /* linear_assertion  */
  YYSYMBOL_linear_inequality = 41,         /* linear_inequality  */
  YYSYMBOL_linear_term = 42,               /* linear_term  */
  YYSYMBOL_linear_expression = 43,         /* linear_expression  */
  YYSYMBOL_primed_linear_assertion = 44,   /* primed_linear_assertion  */
  YYSYMBOL_preservative = 45,              /* preservative  */
  YYSYMBOL_variable_list = 46,             /* variable_list  */
  YYSYMBOL_primed_linear_inequality = 47,  /* primed_linear_inequality  */
  YYSYMBOL_primed_term = 48,               /* primed_term  */
  YYSYMBOL_primed_linear_expression = 49,  /* primed_linear_expression  */
  YYSYMBOL_identifier = 50                 /* identifier  */
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
typedef yytype_int8 yy_state_t;

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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


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
      24,    25,    20,    18,    27,    19,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   138,   138,   145,   148,   151,   155,   160,
     163,   166,   169,   172,   173,   176,   179,   185,   190,   197,
     200,   206,   217,   229,   235,   242,   247,   252,   258,   267,
     270,   280,   283,   289,   294,   300,   306,   312,   315,   322,
     336,   341,   346,   352,   357,   362,   368,   372,   376,   379,
     383,   388,   391,   397,   402,   408
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "IDENT",
  "PRIME", "END", "VARIABLED", "LOCATION", "TRANSITION", "EQ", "LEQ",
  "GEQ", "LE", "GE", "PRES", "PROPS", "INVARIANT", "'+'", "'-'", "'*'",
  "UMINUS", "'['", "']'", "'('", "')'", "':'", "','", "$accept", "program",
  "header", "$@1", "optional_commands", "dimvector", "system_descriptor",
  "location_descriptor", "transition_descriptor", "invariant_descriptor",
  "location_identifier", "transition_identifier", "linear_assertion",
  "linear_inequality", "linear_term", "linear_expression",
  "primed_linear_assertion", "preservative", "variable_list",
  "primed_linear_inequality", "primed_term", "primed_linear_expression",
  "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    43,    45,
      42,   273,    91,    93,    40,    41,    58,    44
};
#endif

#define YYPACT_NINF (-79)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-22)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      30,   -79,    54,    23,    40,   -79,    53,    61,    60,    77,
      60,    60,    60,    95,    61,    61,    61,   -79,     4,   -79,
      62,    19,   -79,    76,   -79,     2,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,    83,    46,   -79,    19,   -79,     1,   -79,
      60,    19,   -79,    60,   -79,   -79,    19,    19,    19,    46,
      46,    78,   -79,   -79,    48,    48,    48,   -79,   -79,    21,
      84,    60,    85,    39,    79,   -79,    21,    21,   -79,    71,
      82,    93,   -79,    60,   -79,   -79,    21,   -79,   -79,    12,
      12,    12,    39,    39,    60,   -79,    87,     3,   -79,    81,
      81,    81,   -79,   -79,   -79,   -79,    60,   -79,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,     0,     6,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    12,    14,    55,     0,     8,
       0,    15,    21,     0,    22,     0,     2,     9,    10,    13,
       4,     7,     5,    29,     0,    16,    24,    31,     0,    28,
       0,     0,    19,     0,    34,    23,     0,     0,     0,     0,
       0,     0,    20,    30,    27,    25,    26,    32,    33,     0,
      48,     0,     0,     0,     0,    18,    37,    36,    51,     0,
      46,     0,    47,     0,    54,    46,     0,    38,    35,     0,
       0,     0,     0,     0,     0,    49,     0,    42,    17,    44,
      43,    45,    52,    53,    50,    39,     0,    40,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,   -79,   -79,   -79,   -79,   -79,    70,   -79,   -79,   -79,
     -11,   -79,    16,   -79,    11,    45,   -20,   -79,   -78,   -79,
     -49,    15,    -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,     7,    18,    13,    14,    15,    16,
      21,    23,    35,    36,    37,    38,    65,    66,    86,    67,
      68,    69,    39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,    25,    22,    24,    22,    33,    17,    17,    17,    97,
      31,    46,    47,    48,    74,    60,    17,    61,    98,    49,
      50,    34,    33,    17,    60,    17,    61,    30,    41,    51,
      96,    63,    22,    92,    93,    53,    62,     1,    34,     6,
      63,    42,    60,    17,    61,    44,    77,    78,    64,    33,
      17,    70,    45,    72,     5,    75,    88,    52,    75,    75,
      57,    58,     8,    85,    17,    87,    49,    50,    75,    10,
      11,    75,    75,    75,    75,    75,    94,     9,    12,    87,
      20,    79,    80,    81,    27,    28,    29,    32,    87,    82,
      83,    54,    55,    56,    89,    90,    91,    17,    84,    82,
      83,    26,    40,    43,    71,    59,    76,    73,     0,   -21,
      95
};

static const yytype_int8 yycheck[] =
{
       8,    12,    10,    11,    12,     3,     4,     4,     4,    87,
      18,    10,    11,    12,    63,     3,     4,     5,    96,    18,
      19,    19,     3,     4,     3,     4,     5,    23,    26,    40,
      27,    19,    40,    82,    83,    43,    15,     7,    19,    16,
      19,    25,     3,     4,     5,    34,    66,    67,    59,     3,
       4,    59,    36,    61,     0,    63,    76,    41,    66,    67,
      49,    50,    22,    71,     4,    73,    18,    19,    76,     8,
       9,    79,    80,    81,    82,    83,    84,    24,    17,    87,
       3,    10,    11,    12,    14,    15,    16,    25,    96,    18,
      19,    46,    47,    48,    79,    80,    81,     4,     5,    18,
      19,     6,    26,    20,    20,    27,    27,    22,    -1,    27,
      23
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    29,    30,    31,     0,    16,    32,    22,    24,
       8,     9,    17,    34,    35,    36,    37,     4,    33,    50,
       3,    38,    50,    39,    50,    38,     6,    34,    34,    34,
      23,    50,    25,     3,    19,    40,    41,    42,    43,    50,
      26,    26,    40,    20,    42,    40,    10,    11,    12,    18,
      19,    38,    40,    50,    43,    43,    43,    42,    42,    27,
       3,     5,    15,    19,    38,    44,    45,    47,    48,    49,
      50,    20,    50,    22,    48,    50,    27,    44,    44,    10,
      11,    12,    18,    19,     5,    50,    46,    50,    44,    49,
      49,    49,    48,    48,    50,    23,    27,    46,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    31,    30,    32,    32,    33,    33,    34,
      34,    34,    34,    34,    34,    35,    35,    36,    36,    37,
      37,    38,    39,    40,    40,    41,    41,    41,    42,    42,
      42,    43,    43,    43,    43,    44,    44,    44,    44,    45,
      46,    46,    46,    47,    47,    47,    48,    48,    48,    48,
      48,    49,    49,    49,    49,    50
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     0,     5,     4,     0,     2,     1,     2,
       2,     1,     1,     2,     1,     2,     3,     8,     6,     3,
       4,     1,     1,     2,     1,     3,     3,     3,     1,     1,
       3,     1,     3,     3,     2,     2,     1,     1,     2,     4,
       2,     3,     1,     3,     3,     3,     1,     2,     1,     3,
       4,     1,     3,     3,     2,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {yyvsp
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 2: /* program: header optional_commands system_descriptor END  */
#line 134 "ltrtest.y"
                                                       {
   // just print it for the fun of it
}
#line 1275 "ltrtest.tab.c"
    break;

  case 3: /* $@1: %empty  */
#line 138 "ltrtest.y"
                  {
}
#line 1282 "ltrtest.tab.c"
    break;

  case 4: /* header: VARIABLED $@1 '[' dimvector ']'  */
#line 139 "ltrtest.y"
                   {
   f=(yyvsp[-1].vi); // This is the main dimvector
   dimension=f->get_dimension();
}
#line 1291 "ltrtest.tab.c"
    break;

  case 5: /* optional_commands: PROPS '(' INT ')'  */
#line 145 "ltrtest.y"
                                     {
   prop_steps=(yyvsp[-1].integer);
   
}
#line 1300 "ltrtest.tab.c"
    break;

  case 6: /* optional_commands: %empty  */
#line 148 "ltrtest.y"
    {}
#line 1306 "ltrtest.tab.c"
    break;

  case 7: /* dimvector: dimvector identifier  */
#line 151 "ltrtest.y"
                                {
   (yyval.vi)=(yyvsp[-1].vi);
   (yyval.vi)->search_and_insert((yyvsp[0].identifier));
}
#line 1315 "ltrtest.tab.c"
    break;

  case 8: /* dimvector: identifier  */
#line 155 "ltrtest.y"
             {
   (yyval.vi)=new var_info();
   (yyval.vi)->search_and_insert((yyvsp[0].identifier));
}
#line 1324 "ltrtest.tab.c"
    break;

  case 9: /* system_descriptor: location_descriptor system_descriptor  */
#line 160 "ltrtest.y"
                                                       {
   
}
#line 1332 "ltrtest.tab.c"
    break;

  case 10: /* system_descriptor: transition_descriptor system_descriptor  */
#line 163 "ltrtest.y"
                                         {

}
#line 1340 "ltrtest.tab.c"
    break;

  case 11: /* system_descriptor: location_descriptor  */
#line 166 "ltrtest.y"
                     {

}
#line 1348 "ltrtest.tab.c"
    break;

  case 12: /* system_descriptor: transition_descriptor  */
#line 169 "ltrtest.y"
                       {
   
}
#line 1356 "ltrtest.tab.c"
    break;

  case 13: /* system_descriptor: invariant_descriptor system_descriptor  */
#line 172 "ltrtest.y"
                                        {}
#line 1362 "ltrtest.tab.c"
    break;

  case 14: /* system_descriptor: invariant_descriptor  */
#line 173 "ltrtest.y"
                      {}
#line 1368 "ltrtest.tab.c"
    break;

  case 15: /* location_descriptor: LOCATION location_identifier  */
#line 176 "ltrtest.y"
                                                 {
   (yyval.ll)=(yyvsp[0].ll);
}
#line 1376 "ltrtest.tab.c"
    break;

  case 16: /* location_descriptor: LOCATION location_identifier linear_assertion  */
#line 179 "ltrtest.y"
                                               {
   (yyval.ll)=(yyvsp[-1].ll);
   (yyval.ll)->set_polyhedron((yyvsp[0].pp));
}
#line 1385 "ltrtest.tab.c"
    break;

  case 17: /* transition_descriptor: TRANSITION transition_identifier ':' location_identifier ',' location_identifier ',' primed_linear_assertion  */
#line 185 "ltrtest.y"
                                                                                                                                   {
   (yyval.tt)=(yyvsp[-6].tt);
   (yyval.tt)->set_locs((yyvsp[-4].ll),(yyvsp[-2].ll));
   (yyval.tt)->set_relation((yyvsp[0].pp));
}
#line 1395 "ltrtest.tab.c"
    break;

  case 18: /* transition_descriptor: TRANSITION transition_identifier ':' location_identifier ',' primed_linear_assertion  */
#line 190 "ltrtest.y"
                                                                                       {
   (yyval.tt)=(yyvsp[-4].tt);
   (yyval.tt)->set_locs((yyvsp[-2].ll),(yyvsp[-2].ll));
   (yyval.tt)->set_relation((yyvsp[0].pp));
}
#line 1405 "ltrtest.tab.c"
    break;

  case 19: /* invariant_descriptor: INVARIANT location_identifier linear_assertion  */
#line 197 "ltrtest.y"
                                                                     {
   (yyvsp[-1].ll)->set_invariant_polyhedron((yyvsp[0].pp));
}
#line 1413 "ltrtest.tab.c"
    break;

  case 20: /* invariant_descriptor: INVARIANT location_identifier ':' linear_assertion  */
#line 200 "ltrtest.y"
                                                    {
     (yyvsp[-2].ll)->set_invariant_polyhedron((yyvsp[0].pp));
}
#line 1421 "ltrtest.tab.c"
    break;

  case 21: /* location_identifier: identifier  */
#line 206 "ltrtest.y"
                               {
   // search loclist for the identifier
   Location * what;
   if (!search_location((yyvsp[0].identifier), &what)){
      (yyval.ll)=new Location(dimension,f,fd,fm,(yyvsp[0].identifier));
      loclist->push_back((yyval.ll));
   } else
      (yyval.ll)=what;
}
#line 1435 "ltrtest.tab.c"
    break;

  case 22: /* transition_identifier: identifier  */
#line 217 "ltrtest.y"
                                 {
      // search loclist for the identifier
   TransitionRelation * what;
   if (!search_transition_relation((yyvsp[0].identifier), &what)){
      (yyval.tt)=new TransitionRelation(dimension,f,fd,fm,(yyvsp[0].identifier));
      trlist->push_back((yyval.tt));
   } else {
      cout<<"Error: Already Encountered transition name #"<<what<<(yyvsp[0].identifier);
      (yyval.tt)=what;
   }
}
#line 1451 "ltrtest.tab.c"
    break;

  case 23: /* linear_assertion: linear_inequality linear_assertion  */
#line 229 "ltrtest.y"
                                                    {
   (yyval.pp)=(yyvsp[0].pp);
   //$$->add_constraint_and_minimize(*$1);
   (yyval.pp)->add_constraint(*(yyvsp[-1].cc));
   delete((yyvsp[-1].cc));
}
#line 1462 "ltrtest.tab.c"
    break;

  case 24: /* linear_assertion: linear_inequality  */
#line 235 "ltrtest.y"
                   {
   (yyval.pp)= new C_Polyhedron(dimension, UNIVERSE);
   //$$->add_constraint_and_minimize(*$1);
   (yyval.pp)->add_constraint(*(yyvsp[0].cc));
   delete((yyvsp[0].cc));
}
#line 1473 "ltrtest.tab.c"
    break;

  case 25: /* linear_inequality: linear_expression LEQ linear_expression  */
#line 242 "ltrtest.y"
                                                           {
   (yyval.cc)=new Constraint(*(yyvsp[-2].li) <= *(yyvsp[0].li));
   delete((yyvsp[-2].li));
   delete((yyvsp[0].li));
}
#line 1483 "ltrtest.tab.c"
    break;

  case 26: /* linear_inequality: linear_expression GEQ linear_expression  */
#line 247 "ltrtest.y"
                                          {
   (yyval.cc)=new Constraint(*(yyvsp[-2].li) >= *(yyvsp[0].li));
   delete((yyvsp[-2].li));
   delete((yyvsp[0].li));
}
#line 1493 "ltrtest.tab.c"
    break;

  case 27: /* linear_inequality: linear_expression EQ linear_expression  */
#line 252 "ltrtest.y"
                                         {
   (yyval.cc)=new Constraint(*(yyvsp[-2].li) == *(yyvsp[0].li));

   // // (yyval.cc)=new Constraint("A" == "0");
   
   // cout<<"Constraint is "<<*(yyval.cc)<<endl;
   // cout<<"Linear Expression is "<<typeid(*(yyvsp[-2].li)).name()<<endl;
   // cout<<"Linear Expression is "<<typeid(*(yyvsp[0].li)).name()<<endl;
   delete((yyvsp[-2].li));
   delete((yyvsp[0].li));
   }
#line 1503 "ltrtest.tab.c"
    break;

  case 28: /* linear_term: identifier  */
#line 258 "ltrtest.y"
                        {
   int i =f->search((yyvsp[0].identifier));
   if (i==VAR_NOT_FOUND){
      string x=string("Error:: Variable ")+ (yyvsp[0].identifier) + string(" not found");
      yyerror(x);
      exit(1);
   }
   (yyval.li)=new Linear_Expression(Variable(i));
}
#line 1517 "ltrtest.tab.c"
    break;

  case 29: /* linear_term: INT  */
#line 267 "ltrtest.y"
      {
   (yyval.li)= new Linear_Expression((yyvsp[0].integer));
}
#line 1525 "ltrtest.tab.c"
    break;

  case 30: /* linear_term: INT '*' identifier  */
#line 270 "ltrtest.y"
                    {
   int i =f->search((yyvsp[0].identifier));
   if (i==VAR_NOT_FOUND){
      string x=string("Error:: Variable ")+ (yyvsp[0].identifier) + string(" not found");
      yyerror(x);
      exit(1);
   }
   (yyval.li)=new Linear_Expression((yyvsp[-2].integer) * Variable(i));
}
#line 1539 "ltrtest.tab.c"
    break;

  case 31: /* linear_expression: linear_term  */
#line 280 "ltrtest.y"
                              {
   (yyval.li)=(yyvsp[0].li);
}
#line 1547 "ltrtest.tab.c"
    break;

  case 32: /* linear_expression: linear_expression '+' linear_term  */
#line 283 "ltrtest.y"
                                    {
   (yyval.li)=(yyvsp[-2].li);
   (*(yyvsp[-2].li))+=(*(yyvsp[0].li));
   delete((yyvsp[0].li));
   
}
#line 1558 "ltrtest.tab.c"
    break;

  case 33: /* linear_expression: linear_expression '-' linear_term  */
#line 289 "ltrtest.y"
                                    {
   (yyval.li)=(yyvsp[-2].li);
   (*(yyvsp[-2].li))-=(*(yyvsp[0].li));
   delete((yyvsp[0].li));
}
#line 1568 "ltrtest.tab.c"
    break;

  case 34: /* linear_expression: '-' linear_term  */
#line 294 "ltrtest.y"
                              {
   (yyval.li)=(yyvsp[0].li);
   (*(yyvsp[0].li))=-(*(yyvsp[0].li));
}
#line 1577 "ltrtest.tab.c"
    break;

  case 35: /* primed_linear_assertion: primed_linear_inequality primed_linear_assertion  */
#line 300 "ltrtest.y"
                                                                         {
   (yyval.pp)=(yyvsp[0].pp);
   //$$->add_constraint_and_minimize(*$1);
   (yyval.pp)->add_constraint(*(yyvsp[-1].cc));
   delete((yyvsp[-1].cc));
}
#line 1588 "ltrtest.tab.c"
    break;

  case 36: /* primed_linear_assertion: primed_linear_inequality  */
#line 306 "ltrtest.y"
                          {
   (yyval.pp)= new C_Polyhedron(2*dimension,UNIVERSE);
   //$$->add_constraint_and_minimize(*$1);
   (yyval.pp)->add_constraint(*(yyvsp[0].cc));
   delete((yyvsp[0].cc));
}
#line 1599 "ltrtest.tab.c"
    break;

  case 37: /* primed_linear_assertion: preservative  */
#line 312 "ltrtest.y"
              {
   (yyval.pp)=(yyvsp[0].pp);
}
#line 1607 "ltrtest.tab.c"
    break;

  case 38: /* primed_linear_assertion: preservative primed_linear_assertion  */
#line 315 "ltrtest.y"
                                      {
   (yyval.pp)=(yyvsp[0].pp);
   (yyval.pp)->intersection_assign(*(yyvsp[-1].pp));
   delete((yyvsp[-1].pp));
}
#line 1617 "ltrtest.tab.c"
    break;

  case 39: /* preservative: PRES '[' variable_list ']'  */
#line 322 "ltrtest.y"
                                        {
   (yyval.pp)= new C_Polyhedron(2*dimension,UNIVERSE);
   vector<int>::iterator vi=(yyvsp[-1].vv)->begin();
   for (; vi < (yyvsp[-1].vv)->end(); ++vi){
      Linear_Expression ll=Variable((*vi)) - Variable((*vi)+dimension);
      //$$->add_constraint_and_minimize(ll ==0);
      (yyval.pp)->add_constraint(ll ==0);
   }

   delete((yyvsp[-1].vv));
   
}
#line 1634 "ltrtest.tab.c"
    break;

  case 40: /* variable_list: identifier variable_list  */
#line 336 "ltrtest.y"
                                        {
   int i=find_variable((yyvsp[-1].identifier));
   (yyval.vv)=(yyvsp[0].vv);
   (yyval.vv)->push_back(i);
}
#line 1644 "ltrtest.tab.c"
    break;

  case 41: /* variable_list: identifier ',' variable_list  */
#line 341 "ltrtest.y"
                               {
   int i=find_variable((yyvsp[-2].identifier));
   (yyval.vv)=(yyvsp[0].vv);
   (yyval.vv)->push_back(i);
}
#line 1654 "ltrtest.tab.c"
    break;

  case 42: /* variable_list: identifier  */
#line 346 "ltrtest.y"
            {
   int i=find_variable((yyvsp[0].identifier));
   (yyval.vv)=new vector<int>();
   (yyval.vv)->push_back(i);
}
#line 1664 "ltrtest.tab.c"
    break;

  case 43: /* primed_linear_inequality: primed_linear_expression LEQ primed_linear_expression  */
#line 352 "ltrtest.y"
                                                                               {
   (yyval.cc)=new Constraint(*(yyvsp[-2].li) <= *(yyvsp[0].li));
   delete((yyvsp[-2].li));
   delete((yyvsp[0].li));
}
#line 1674 "ltrtest.tab.c"
    break;

  case 44: /* primed_linear_inequality: primed_linear_expression EQ primed_linear_expression  */
#line 357 "ltrtest.y"
                                                       {
   (yyval.cc)=new Constraint(*(yyvsp[-2].li)== *(yyvsp[0].li));
   delete((yyvsp[-2].li));
   delete((yyvsp[0].li));
}
#line 1684 "ltrtest.tab.c"
    break;

  case 45: /* primed_linear_inequality: primed_linear_expression GEQ primed_linear_expression  */
#line 362 "ltrtest.y"
                                                        {
   (yyval.cc)= new Constraint(*(yyvsp[-2].li) >= *(yyvsp[0].li));
   delete((yyvsp[-2].li));
   delete((yyvsp[0].li));
}
#line 1694 "ltrtest.tab.c"
    break;

  case 46: /* primed_term: identifier  */
#line 368 "ltrtest.y"
                        {
   int i= find_variable((yyvsp[0].identifier));
   (yyval.li)=new Linear_Expression(Variable(i));
}
#line 1703 "ltrtest.tab.c"
    break;

  case 47: /* primed_term: PRIME identifier  */
#line 372 "ltrtest.y"
                  {
   int i= find_variable((yyvsp[0].identifier));
   (yyval.li)=new Linear_Expression(Variable(i+dimension));
}
#line 1712 "ltrtest.tab.c"
    break;

  case 48: /* primed_term: INT  */
#line 376 "ltrtest.y"
      {
   (yyval.li)=new Linear_Expression((yyvsp[0].integer));
}
#line 1720 "ltrtest.tab.c"
    break;

  case 49: /* primed_term: INT '*' identifier  */
#line 379 "ltrtest.y"
                    {
   int i= find_variable((yyvsp[0].identifier));
   (yyval.li)=new Linear_Expression((yyvsp[-2].integer) * Variable(i));
}
#line 1729 "ltrtest.tab.c"
    break;

  case 50: /* primed_term: INT '*' PRIME identifier  */
#line 383 "ltrtest.y"
                          {
   int i= find_variable((yyvsp[0].identifier));
   (yyval.li)=new Linear_Expression((yyvsp[-3].integer) * Variable(i+dimension));
}
#line 1738 "ltrtest.tab.c"
    break;

  case 51: /* primed_linear_expression: primed_term  */
#line 388 "ltrtest.y"
                                     {
   (yyval.li)=(yyvsp[0].li);
}
#line 1746 "ltrtest.tab.c"
    break;

  case 52: /* primed_linear_expression: primed_linear_expression '+' primed_term  */
#line 391 "ltrtest.y"
                                          {
   (yyval.li)=(yyvsp[-2].li);
   (*(yyvsp[-2].li))+= (*(yyvsp[0].li));
   delete((yyvsp[0].li));
}
#line 1756 "ltrtest.tab.c"
    break;

  case 53: /* primed_linear_expression: primed_linear_expression '-' primed_term  */
#line 397 "ltrtest.y"
                                           {
   (yyval.li)=(yyvsp[-2].li);
   (*(yyvsp[-2].li))-= (*(yyvsp[0].li));
   delete((yyvsp[0].li));
}
#line 1766 "ltrtest.tab.c"
    break;

  case 54: /* primed_linear_expression: '-' primed_term  */
#line 402 "ltrtest.y"
                              {
   (yyval.li)=(yyvsp[0].li);
   (*(yyvsp[0].li))= -(*(yyvsp[0].li));
}
#line 1775 "ltrtest.tab.c"
    break;

  case 55: /* identifier: IDENT  */
#line 408 "ltrtest.y"
                 {
  strcpy((yyval.identifier),(yyvsp[0].identifier));
}
#line 1783 "ltrtest.tab.c"
    break;


#line 1787 "ltrtest.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 414 "ltrtest.y"


void do_some_propagation(){
   // try and fire each transition relation

   
   vector<TransitionRelation*>::iterator vi;
   int fired_up=0;
   int ntrans=trlist->size();


   while (fired_up < prop_steps * ntrans){
      for (vi=trlist->begin();vi < trlist->end(); vi++){
         (*vi)->fire();
         fired_up++;
      }
   }

}

int find_variable(char * what){
   int i=f->search(what);
   if (i==VAR_NOT_FOUND){
      string x=string("Error:: Variable ")+ what + string(" not found");
      yyerror(x);
      exit(1);
   }

   return i;
}

void parseinit(){
   weave_count=bang_count=0;
   linenum=0;
   inv_check=false;
   clump_prune_count=prune_count=0;
   context_count=0;
   fm=new var_info();
   fd=new var_info();
   loclist= new vector<Location *>();
   trlist=new vector<TransitionRelation *>();
   num_context=2;
   gendrop=false;
   global_sub_system_list=new vector<System *> ();
   zero=one=true;
   prop_steps=2;
   weave_time=360000;
   ch79=true;
   bhrz03=true;
   dual=false;
}

bool search_location( char * name, Location ** what){
   vector<Location*>::iterator vi;
   string nstr(name);
   for(vi=loclist->begin();vi< loclist->end();vi++){
      if ((*vi)->matches(nstr)){
         *what=(*vi);
         return true;
      }
   }

   return false;
}


bool search_transition_relation( char * name, TransitionRelation ** what){
   vector<TransitionRelation*>::iterator vi;
   string nstr(name);
   for(vi=trlist->begin();vi< trlist->end();vi++){
      if ((*vi)->matches(nstr)){
         *what=(*vi);
         return true;
      }
   }
   
   return false;
}

void yyerror(char const * x){
   yyerror(string(x));
}

void yyerror(string const & x){

   cerr<<x<<endl;
   cerr<<"Line number::"<<linenum<<endl;
   exit(1);
   
}

int parse_cmd_line(char * x){
   
   if (strcmp(x,"one")==0) return ONECONTEXT;
   if (strcmp(x,"many")==0) return MANYCONTEXT;
   if (strcmp(x,"gendrop")==0) return GENDROP;
   if (strcmp(x,"zero_only")==0) return ZERO_ONLY;
   if (strcmp(x,"one_only")==0) return ONE_ONLY;
   if (strcmp(x,"zero_one")==0) return ZERO_ONE;
   if (strcmp(x,"noinst")==0) return NO_INSTANTIATION;
   if (strcmp(x,"noch79")==0) return NO_CH79;
   if (strcmp(x,"nobhrz03")==0) return NO_BHRZ03;
   if (strcmp(x,"ch79")==0) return YES_CH79;
   if (strcmp(x,"bhrz03")==0) return YES_BHRZ03;
   if (strcmp(x,"invcheck")==0) return INV_CHECK;
   if (strcmp(x,"noinvcheck")==0) return NO_INV_CHECK;
   
  
   
   return BULLSHIT;
}

void collect_invariants(C_Polyhedron & cpoly, C_Polyhedron & invd){

   /*
    *  Collect invariants
    */
   
   vector<Location * >::iterator vl;
   
   invd=C_Polyhedron(fd->get_dimension(),UNIVERSE);

   for (vl=loclist->begin();vl<loclist->end();vl++){
      (*vl)->extract_invariants_and_update(cpoly,invd);
   }

   return;

}


void prune_clumps(vector<Clump>& vcl){
   
   C_Polyhedron pp(fd->get_dimension(),UNIVERSE);

   vector<Clump>::iterator vi;
   vector<Location *>::iterator vl;
   
   for (vl=loclist->begin(); vl < loclist->end(); vl++){
      pp=C_Polyhedron(fd->get_dimension(),UNIVERSE);
      (*vl)->update_dual_constraints(pp);
      
      for (vi=vcl.begin();vi < vcl.end();vi++)
         (*vi).prune(pp);
      
   }
      
}


void dfs_traverse_recursive(int depth, vector<Clump> & vcl, C_Polyhedron & cpoly, C_Polyhedron & invd){
   
   
   if (invd.contains(cpoly)){
      bang_count++;
      return;
   }
   
   if (depth==0){
      weave_count++;
      collect_invariants(cpoly,invd);
      //    prune_clumps(vcl);
      return;
   }

   if (weave_timer.compute_time_elapsed() >= weave_time){
      cout<< "Time is up!"<<endl;
      return;
   }
   
   vcl[depth-1].clear();
   while(vcl[depth-1].has_next()){
      
      C_Polyhedron p(cpoly);

      p.intersection_assign(vcl[depth-1].get_reference());

      dfs_traverse_recursive(depth-1,vcl,p,invd);

      vcl[depth-1].next();
   }

   return;
  
   
}

void dfs_traverse(vector<Clump> & vcl, C_Polyhedron & initp){
   // first find out the number of clumps
   // a polyhedron containing the solutions contained to date
   // initiate a dfs traversal.
   // write an invariant extraction function at depth 0

   C_Polyhedron  invd(*trivial);
   int ncl=0;
   vector<Clump>::iterator vi;
   for (vi=vcl.begin();vi < vcl.end();vi++){
      ncl++;
      (*vi).clear();
   }

   weave_timer.restart();
  
   dfs_traverse_recursive(ncl,vcl,initp,invd);
   
}


int main(int argc, char * argv[]){
   // measure total time
   Timer total_time;
   
   parseinit();

   if (argc<=1){
      // by default one context and no gendrop
      num_context=2;
      gendrop=false;
   } else {
      for (int k=1;k<argc;k++){
         switch(parse_cmd_line(argv[k])){
            case GENDROP:
               gendrop=true;
               break;
            case ONECONTEXT:
               num_context=1;
               break;
            case MANYCONTEXT:
               num_context=2;
               break;
            case RESIDUAL_TR_SYS:
               num_context=3;
               break;
            case ZERO_ONLY:
               one=false;
               zero=true;
               break;
            case ONE_ONLY:
               one=true;
               zero=false;
               break;
            case ZERO_ONE:
               zero=one=true;
               break;

            case NO_INSTANTIATION:
               zero=one=false;
               break;
            case NO_CH79:
               ch79=false;
               break;
            case YES_CH79:
               ch79=true;
               break;

            case NO_BHRZ03:
               bhrz03=false;
               break;
            case YES_BHRZ03:
               bhrz03=true;
               break;

            case NO_DUAL:
               dual=false;
               break;
            case YES_DUAL:
               dual=true;
               break;
            case INV_CHECK:
               inv_check=true;
               break;
            case NO_INV_CHECK:
               inv_check=false;
               break;
            default:
               cerr<<"Illegal option:"<<argv[k]<<" ignored."<<endl;
               cerr<<"Usage:"<<argv[0]<<" [one,many,ch,noch,bhrz03,nobhrz03,invcheck,noinvcheck] [ < input file ] [> output file ] "<<endl;
               break;
         }
      }
   }
   
   
   
   vector<Location *>::iterator vi;
   vector<TransitionRelation *>::iterator vj;
   

   // parse the input file
   yyparse();

   // print out the locations
   cout<<"Locations-------------------------"<<endl;
   for (vi=loclist->begin();vi< loclist->end();vi++){
         // cout<<"line 2287"<<endl;
         cout<<*(*vi)<<endl;
         // cout<<"line 2289"<<endl;
         // cout<<(*(*vi)).get_name()<<endl;
         // cout<<"line 2291"<<endl;
         // cout<<typeid((*(*vi)).get_poly_reference()).name()<<endl;
         // cout<<"line 2293"<<endl;
         // cout<<*((*(*vi)).get_initial())<<endl;
         // cout<<"line 2295"<<endl;
         // (*((*(*vi)).get_var_info())).print_info(cout);
   }

   // add mod info -> loclist_with_mod
   int count = trlist->size();
   vector<Location *> loclist_with_mod;
   for (vi=loclist->begin();vi< loclist->end();vi++){
      int k = (*(*vi)).get_dimension();
      for (int i=0; i<count; i++){
         string loc_name = "l";
         loc_name.push_back(char('1'+i));
         loc_name += " (y mod ";
         loc_name += to_string(count);
         loc_name += " = ";
         if (i < count-1){
            loc_name += to_string(i+1);
         }
         else {
            loc_name += "0";
         }
         loc_name += ")";

         Location *vk = new Location(k,f,fd,fm,loc_name);
         auto vii = loclist->begin();
         C_Polyhedron * p = &((*(*vii)).get_non_const_poly_reference());
         (*vk).set_polyhedron(p);
         // cout<<"line 2305"<<endl;
         // cout<<*vk<<endl;
         // cout<<(*vk).get_name()<<endl;
         loclist_with_mod.push_back(vk);
      }
   }

   cout<<"Locations with mod--------------------------------"<<endl;
   // print loclist_with_mod
   for (auto vk = loclist_with_mod.begin(); vk < loclist_with_mod.end(); vk++){
      // cout<<"line 2315"<<endl;
      cout<<*(*vk)<<endl;
      // (*((*(*vk)).get_var_info())).print_info(cout);
      // cout<<(*(*vk)).get_name()<<endl;
   }

   cout<<"Transitions----------------------------------"<<endl;
   //print out the transitions
   for (vj=trlist->begin();vj< trlist->end();vj++){
         // cout<<"line 2300"<<endl;
         cout<<*(*vj)<<endl;
         // cout<<"line 2302"<<endl;
         // cout<<(*(*vj)).get_name()<<endl;
         // cout<<"line 2304"<<endl;
         // cout<<(*(*vj)).get_preloc_name()<<endl;
         // cout<<"line 2306"<<endl;
         // cout<<(*(*vj)).get_postloc_name()<<endl;
         // cout<<"line 2308"<<endl;
         // cout<<(*(*vj)).get_relation()<<endl;
         // cout<<"line 2310"<<endl;
         // (*((*(*vj)).get_varinfo())).print_info(cout);
   }


   // add mod info -> trlist_with_mod
   int idx = 1;
   vector<TransitionRelation *> trlist_with_mod;
   for (vj=trlist->begin();vj< trlist->end();vj++){
      int n = (*(*vj)).get_dimension();
      C_Polyhedron *rel = &((*(*vj)).get_relation_byme());
      C_Polyhedron *grd = &((*(*vj)).get_guard_byme());
      C_Polyhedron *upd = &((*(*vj)).get_update_byme());
      // const C_Polyhedron *upd = &((*(*vj)).get_update_poly());
      // cout<<"---------------------------------------------------------"<<endl;
      // cout<<*upd<<endl;
      // cout<<typeid(*upd).name()<<endl;
      // cout<<(*upd).constraints()<<endl;
      // cout<<*(((*upd).constraints()).begin())<<endl;
      // cout<<(*(((*upd).constraints()).begin())).type()<<endl;

      const Constraint_System& cs = (*upd).constraints();
      for (Constraint_System::const_iterator c = cs.begin(),
         cs_end = cs.end(); c != cs_end; ++c) {
         int k = (*((*(*vj)).get_varinfo())).get_dimension();
         // cout<<(*c).coefficient(Variable(1))<<" "<<Variable(1)<<" ";
         // cout<<typeid((*c).coefficient(Variable(1))).name()<<endl;
         // cout<<(*c).coefficient(Variable(k/2+1))<<" "<<Variable(k/2+1)<<" "<<endl;
         // cout<<(*c).inhomogeneous_term()<<endl<<endl;
         long aa = ((*c).coefficient(Variable(1))).get_si();
         long bb = ((*c).coefficient(Variable(k/2+1))).get_si();
         long cc = (*c).inhomogeneous_term().get_si();
         // aay + bby' + cc = 0
         // cout<<aa<<" "<<bb<<" "<<cc<<endl;

         // flag to check if it concerns y' and y
         bool flag = false;
         var_info *ff = &((*(*vj)).get_varinfo_f());
         var_info *ffd = &((*(*vj)).get_varinfo_fd());
         var_info *ffm = &((*(*vj)).get_varinfo_fm());

         if (aa==0 && bb==0) {
            continue;
         }
         else if (aa!=0 && bb!=0){
            flag = true;
            int t1 = - aa / bb;
            int t2 = - cc / bb;
            auto va = loclist_with_mod.begin() + idx - 1;
            int post_tr = (idx * t1 + t2)%count - 1 >=0 ? (idx * t1 + t2)%count - 1 : count - 1;
            auto vb = loclist_with_mod.begin() + post_tr;

            string tr_name = (*va)->get_name() + " -> " + (*vb)->get_name();
            TransitionRelation *vc = new TransitionRelation(n,ff,ffd,ffm,*va,*vb,rel,tr_name);
            vc->set_guard_byme(grd);
            vc->set_update_byme(upd);
            trlist_with_mod.push_back(vc);
         }

         if (!flag) {
            auto va = loclist_with_mod.begin() + idx - 1;
            string tr_name = (*va)->get_name() + " -> " + (*va)->get_name();
            TransitionRelation *vc = new TransitionRelation(n,ff,ffd,ffm,*va,*va,rel,tr_name);
            vc->set_guard_byme(grd);
            vc->set_update_byme(upd);
            trlist_with_mod.push_back(vc);
         }
      }
      idx ++;


      // // use pow_k to generate all the transitions with mod
      // for (auto va=loclist_with_mod.begin();va< loclist_with_mod.end();va++){
      //    for (auto vb=loclist_with_mod.begin();vb< loclist_with_mod.end();vb++){
      //       string tr_name = (*va)->get_name();
      //       tr_name.push_back('-');
      //       tr_name.append((*vb)->get_name());
      //       TransitionRelation *vc = new TransitionRelation(n,ff,ffd,ffm,*va,*vb,rel,tr_name);

      //       // (*vc).strengthen("A = 101")
      //       trlist_with_mod.push_back(vc);
      //    }
      // }
   }

   cout<<"Transitions with mod----------------------------------"<<endl;
   // print trlist_with_mod
   for (auto vc = trlist_with_mod.begin(); vc < trlist_with_mod.end(); vc++){
      // cout<<"line 2335"<<endl;
      cout<<*(*vc)<<endl;
      // cout<<(*(*vc)).get_name()<<endl;
      // cout<<(*(*vc)).get_preloc_name()<<endl;
      // cout<<(*(*vc)).get_postloc_name()<<endl;
      // cout<<(*(*vc)).get_relation()<<endl;
   }

   // replace initial location
   loclist->swap(loclist_with_mod);
   // replace trlist
   trlist->swap(trlist_with_mod);

   print_status();

   add_preloc_invariants_to_transitions();
   
   global_system= new System(f,fd,fm);

   
   for (vi=loclist->begin();vi< loclist->end();vi++){
      global_system->add_location((*vi));  
   }

   for (vj=trlist->begin();vj< trlist->end();vj++){
      global_system->add_transition((*vj));
   }

   global_system->compute_duals();
   
   tt= new int[fm->get_dimension()];

   //
   // start a timer
   //

   Timer my_time;
   
   
   if (num_context==1){
      
      glc=global_system->get_context();

      glc->simplify_repeat();
      
      
      int ndd=fd->get_dimension();
      
      trivial=new C_Polyhedron(ndd,UNIVERSE);
      
      dualp=new C_Polyhedron(ndd,UNIVERSE);
      
      for (vi=loclist->begin();vi< loclist->end();vi++)
         (*vi)->add_to_trivial(trivial);
      
      invd=new C_Polyhedron(*trivial);

      glc->recursive_strategy(loclist,invd,weave_time,true);

      my_time.stop();
      
   } else if (num_context==2) {
      // manycontexts
      
      // dualize using a clump

      int nd=fd->get_dimension();

      // obtain a polyedron characterizing "trivial"
      
      trivial=new C_Polyhedron(nd,UNIVERSE);

      vector<Location *>::iterator vi;
      for (vi=loclist->begin();vi< loclist->end();vi++)
         (*vi)->add_to_trivial(trivial);

      // now dualize each location
      
      C_Polyhedron initp(nd,UNIVERSE); // for the dualized initial conditions
      cout<<endl;
      cout<<"1."<<endl;
      cout<<"The locations read in are:"<<endl<<endl;
      
      
      for (vi=loclist->begin();vi< loclist->end();vi++){
         cout<<*(*vi)<<endl;
         (*vi)->make_context();
         cout<<"Dualizing....(in location)"<<endl;
         (*vi)->compute_dual_constraints(initp);
      }

      // now dualize the transition systems and collect the "clumps"

      vector<Clump> vcl;
      cout<<"----------------------------------------------"<<endl;
      cout<<endl;
      cout<<"2."<<endl;
      cout<<"The transitions read in are::"<<endl<<endl;
      
      vector<TransitionRelation *>::iterator vj;
      for (vj=trlist->begin();vj< trlist->end();vj++){
         cout<<*(*vj)<<endl;
         cout<<"Dualizing....(in transitionrelation)"<<endl;
         (*vj)->compute_consecution_constraints(vcl,initp);
      }
      cout<<"----------------------------------------------"<<endl;
      cout<<endl;
      cout<<"3."<<endl;
      for (vi=loclist->begin();vi< loclist->end();vi++){
         (*vi)->add_clump(vcl);
         // this also should trigger the simplification of the context
      }
      
      // now perform a dfs traversal with clump
      cout<<"----------------------------------------------"<<endl;
      cout<<endl;
      cout<<"4."<<endl;
      dfs_traverse(vcl,initp);
      
      my_time.stop();

      cout<<"strategy ID 2 ending (num_context==2)"<<endl;
      
   } else if (num_context==3){
      //
      // This strategy is no longer useful
      // need to clean this up
      //
      
      glc=global_system->get_context();

            
      cout<<"The populated context is "<<endl;
      cout<<(*glc);
      cout<<endl;

      invd=new C_Polyhedron(fd->get_dimension());
      
      global_system->obtain_trivial_polyhedron(*invd);
      
      glc->recursive_strategy((*global_system), invd);

      // finally print the transition systems generated
      my_time.stop();
   }
   cout<<"----------------------------------------------"<<endl;
   cout<<endl;
   cout<<"5."<<endl;
   cout<<"The locations read in are:"<<endl<<endl;
   vector<Location *>::iterator vl;
   for(vl=loclist->begin();vl< loclist->end();vl++){
      cout<<*(*vl);
   }
   cout<<"----------------------------------------------"<<endl;

   
      
   cout<<" # of Contexts generated ="<<context_count<<endl;
   cout<<" # pruned by inclusion tests = "<<prune_count<<endl;
   cout<<" # of invariants *weav*ed="<<weave_count<<endl;
   cout<<" #  *bang*ed="<<bang_count<<endl;
   cout<<" # Pruned in Cump.cc ="<<clump_prune_count<<endl;
   cout<<" Time Taken (0.01S)="<<my_time.compute_time_elapsed()<<endl;

   if (inv_check)
      check_invariant_ok();
   
   cout<<endl<<endl;
   
   cout<<" Doing Initial Propagation"<<endl;
   Timer prop_timer;
   do_some_propagation();
   prop_timer.stop();

   cout<< "Propagation done -- Time Taken (0.01S):" <<
      prop_timer.compute_time_elapsed()<<endl;
   
   if (dual){
      cout<<"---- Running Cousot-Halbwachs dual propagation/narrowing----"<<endl;
      Timer dual_time;
      
      InvariantMap dualmap(f, *loclist);
      global_system->compute_dual_invariant(dualmap);
      
      dual_time.stop();
      cout<<" Time taken for Dual (0.01 S)"<<dual_time.compute_time_elapsed()<<endl;
      cout<<"--------------------------------------------------------"<<endl;
   }

   InvariantMap h79map(f, *loclist);
      
   if (ch79){
      cout<<"---- Running Cousot-Halbwachs with H79 widening ----"<<endl;
      
      Timer h79_time;
      
   
      
      global_system->compute_invariant_h79(h79map);

      h79_time.stop();
      
      cout<<" Time taken for Cousot-Halbwachs Widening (0.01 S)"<<h79_time.compute_time_elapsed()<<endl;
      
      cout<< " The bake-off results vs. CH79"<<endl;
      print_bake_off(h79map);
      
      if (inv_check){
         cout<<"Checking...."<<endl;
         h79map.check_consecution(trlist);
         cout<<"Done!"<<endl;
      }
      
      cout<<"--------------------------------------------------------"<<endl;
   }
   
   InvariantMap bhrz03map(f, *loclist);
      
   if (bhrz03){
      
      cout<<"---- Running Cousot-Halbwachs with BHRZ03 widening ----"<<endl;
      Timer bhrz03_time;
      
      global_system->compute_invariant(bhrz03map);
      
      bhrz03_time.stop();

      cout<<" Time taken for BHRZ03 (0.01 S)"<<bhrz03_time.compute_time_elapsed()<<endl;

      cout<< " The bake-off results vs. BHRZ03"<<endl;
      print_bake_off(bhrz03map);

      if (inv_check){
         cout<<"Checking...."<<endl;
         bhrz03map.check_consecution(trlist);
         cout<<"Done!"<<endl;
       }
      
      cout<<"--------------------------------------------------------"<<endl;
   }
   
   cout<<" Time taken for the initial propagation (0.01 S)"<<prop_timer.compute_time_elapsed()<<endl;
   cout<<" Time taken for the quantifier elimination (0.01 S)"<<my_time.compute_time_elapsed()<<endl;
   cout<<" Total Time taken (0.01S) "<<total_time.compute_time_elapsed()<<endl;
   
   return 0;
}



void collect_generators(vector<Context *> * children , Generator_System & g){
   vector<Context *>::iterator vk;
    for(vk=children->begin();vk < children->end(); vk++){
       (*vk)->collect_generators(g);
    }
}


void add_preloc_invariants_to_transitions(){
   vector<TransitionRelation *>::iterator vtr;
   for (vtr=trlist->begin(); vtr < trlist->end(); ++vtr){
      (*vtr)->add_preloc_invariant();
   }
   return;
}

void print_status(){

   cout<<"---------------------------------------------------"<<endl;
   cout<<" Local invariants to be generated : "<<zero<<endl;
   cout<<" Increasing invariants to be generated : "<<zero<<endl;
   cout<<" Strategy ID #"<<num_context<<endl;
   cout<<" # of initial propagation steps:"<<prop_steps<<endl;
   cout<<" Weave Time allowed:"<<weave_time<<endl;
   cout<<" Cousot-Halbwachs to be performed:"<<ch79<<endl;
   cout<<" BHRZ03 to be performed:"<<bhrz03<<endl;
   cout<<"----------------------------------------------------"<<endl;
}

void print_bake_off( InvariantMap const & invmap){
   bool disjoint;
   int r2;

   vector<Location *>::iterator vl;
   
   for (vl=loclist->begin(); vl <loclist->end(); vl ++){
      r2=0;
      disjoint=true;
      
      string const & what=(*vl)->get_name();
      C_Polyhedron & loc_inv= (*vl)->invariant_reference();
      C_Polyhedron const & other_inv = invmap(what);
      
      cout<<"Location :"<<what<<" ";
      
      // Am I stronger   
      if (other_inv.contains(loc_inv)){
         r2++; // I am one up
         disjoint=false;
      }
      // Is the other_inv stronger?
      
      if (loc_inv.contains(other_inv)){
            r2--; // h79 is one up
            disjoint=false;
      }

      if (disjoint) {
         cout<<"Disjoint"<<endl;
      } else if (r2 > 0){
         cout<<" + "<<endl;
      } else if (r2 <0 ){
         cout<<" - "<<endl;
      } else if (r2==0){
         cout<<" == "<<endl;
      } else {
         // this is unreachable (or is it? :-)
         cout<<" <<Unknown Relation>>"<<endl;
      }
        
   }
}

void check_invariant_ok(){
   cerr<<" Checking..."<<endl;
   vector<TransitionRelation *>::iterator vi;
   for (vi=trlist->begin(); vi != trlist->end(); ++vi){
      (*vi)->check_map();
   }
   cerr<<"done!"<<endl;
   
}
