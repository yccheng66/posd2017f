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
