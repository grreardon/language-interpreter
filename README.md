# Interpreter (In Progress)

A C-like scripting language and its interpreter, written from scratch in C++17
with Flex and Bison.

```js
func factorial(n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

let arr = [1, 2, 3];
for (let i = 0; i < 3; i += 1) {
    arr[i] *= factorial(i);
}
```

Full C-style operator precedence, arrays, recursion, and nested functions.
Grammar in [`Grammar.txt`](Grammar.txt).

## State

The front end is done. Lexer, parser, and AST all work, and both files in
`tests/` parse clean. The binary parses stdin and prints the tree:

```console
$ echo 'let x = 1 + 2 * 3;' | ./interpreter
BlockStmt
  LetStmt: x
    BinaryExpr (op=43)
      LiteralExpr: 1
      BinaryExpr (op=42)
        LiteralExpr: 2
        LiteralExpr: 3
```

The runtime is in progress of being built.

## Build

Bison 3.6+, Flex, and a C++17 compiler. macOS ships Bison 2.3, which is too old:

```bash
brew install bison
export PATH="$(brew --prefix bison)/bin:$PATH"
```

```bash
bison -d -v parser.y
flex lexer.l
clang++ -std=c++17 -x c++ -o interpreter \
    parser.tab.c lex.yy.c \
    AST/Expr/Expr.cpp AST/Stmt/Statement.cpp AST/ASTPrinter/ASTPrinter.cpp
```

```bash
./interpreter < tests/overall.txt
```
