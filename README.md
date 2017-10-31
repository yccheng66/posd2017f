### Pattern Oriented Software Design
#### Fall, 2017
#### Prof Y C Cheng
#### Dept of Computer Science and Information Engineering
#### Taipei Tech

### Introduction
We will build a Prolog term matching program in this course. Functionally, the program is simple but non-trivial. Thus, we will have plenty of opportunities to encounter **design problems**. After analyzing the design problems, we will make use of appropriate design patterns to solve them. The patterns include _Composite_, _Interpreter_, _Builder_, _Iterator_, _Proxy_, _Visitor_, and so on. Along the way we will also pick up some useful domain knowledge of computing: symbolic matching, lexical analysis, and parsing.

Thus the course requires you to get familiar with matching, the fundamental operation of executing a Prolog program. Due to time limitation, we will focus only on defining terms and performing matches. We build our simplified term matching program after [SWI Prolog](http://www.swi-prolog.org/).

I will be using the following simple way to write C++ programs. My programs (and your programs will, too) come with a makefile that builds it by typing _make_ in bash. We will use the g++ stack. While you are free to code on any OS platform (e.g., Ubuntu, MacOS, and bash on Ubuntu on Windows), your program assignment will be graded on Ubuntu.

When coding in class, I will use the editor [Atom](https://atom.io), which comes with syntax highlighting, code completion to make coding easy. I will also use the plugin [PlatformIO IDE Terminal](https://atom.io/packages/platformio-ide-terminal) so that we can access a terminal to build programs without leaving Atom.

### Prolog basics - goal, relational goals, Conjunction of goals, disjunction of goals,

A _query_ consists of one or more _goal_:

```prolog
?- X=1.
X = 1.
```

is a query "is X matchable to 1?" consisting of the relational goal "X=1". The goal "X=1" _succeeded_ (or is _satisfiable_) because variable X matches any legitimate term.

```prolog
?- X=1, Y=X.
X = Y, Y = 1.
```

is a query "is X matchable to 1 _and_ is Y matchable to X?" that a _conjunction_ of two goals "X=1" and "Y = X". The goal succeeded.


```prolog
?- X=1, X=2.
false.
```

is a query with a _negative_ answer because the conjunction of goals  _failed_ or is _unsatisfiable_.

```prolog
?- X=1; X=2.
X = 1 ;
X = 2.
```

is a query with a _positive_ answer because the disjunctions succeeded in succession. Note that the ";" after "X=1" is typed by the user to query for more answers; the query terminates if the return key is hit.

### Data objects in Prolog

Prolog comes four types of data objects: _atom_, _number_ (collectively known as _constant_), variable (forming _simple object_ with constant), and _structure_. For a simple description of syntax, see
[Data objects in Prolog](http://eecs.wsu.edu/~cook/ai/lectures/prolog/node15.html).

Atom and number are _self-identifying_: thus wherever you see it, the atom 'tom' will always be tom, and the number 1 will always be 1. The _value_ of an atom is exactly the _symbol_ of the atom.

Variable brings _universal quantification_ to Prolog. Variable X becomes _instantiated_ when it is matched with a constant. This
```prolog
X = 1
```
gives the variable with symbol X the value of 1.  

A structure is defined by a name and its arguments. _The name has a syntax of an atom_, and an argument can be any data object including structure. Structure makes it possible to describe arbitrary complex objects through composition of other objects.

```prolog
point(1,1)
triangle(point(1,1), point(0,0), point(0,1))
```

where _point(1, 1)_ is a structure with name _point_ and arguments _1_ and _1_, etc.

### Rules of terms matching (Bratko p.41)

Let _S_ and _T_ be two terms.

* If _S_ and _T_ are constants then _S_ and _T_ match only if they are the same object.
* If _S_ is a variable and T is anything, then they match, and _S_ is instantiated to _T_. Conversely, if _T_ is a variable then _T_ is instantiated to _S_.  
* If _S_ and _T_ are structures then they match only if
  * _S_ and _T_ have the same principal functor, and
  * all their corresponding components match.

  The result of the instantiation is determined by the matching of the components.

### List

```Prolog
?- X = [1, 2, 3].
X = [1, 2, 3].

?- X = .(1,[]).
X = [1]

?- [1, 2] = .(1, .(2, [])).
true.

?- [1,2,3] = [H|L].
H = 1,
L = [2, 3]

?- [1,2,3] = .(H, L).
H = 1,
L = [2, 3]
```

### Lexical analysis and parsing

lexical analyzer, or token scanner
(Dragon book, p71, Fig 2.37)

| lexeme                   | token        | attribute value          |
| :----------------------- | :----------  | :----------------------- |
| sequence of digits       | Number       | numeric value of sequence|
| small letter followed by alphanumeric|    Atom            |      index into symbol                    |
| cap letter or '_' followed   by alphanumeric  | Var          | index into symbol        |

term -> atom | number | var | struct | list

struct -> atom '(' terms ')'

list -> '[' terms ']'

terms -> term, terms | e

atom -> Atom

number -> Number

var -> Var

rewritten to

terms -> term rest| e
rest -> ',' term rest | e
