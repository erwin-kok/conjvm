# C on JVM Compiler

[![ci](https://github.com/erwin-kok/conjvm/actions/workflows/ci.yaml/badge.svg)](https://github.com/erwin-kok/conjvm/actions/workflows/ci.yaml)
[![Kotlin](https://img.shields.io/badge/kotlin-2.3.0-blue.svg?logo=kotlin)](http://kotlinlang.org)
[![License](https://img.shields.io/github/license/erwin-kok/conjvm.svg)](https://github.com/erwin-kok/conjvm/blob/master/LICENSE)

# Introduction

conjvm (“C on the JVM”) is an ANTLR4-based experimental C compiler targeting the Java Virtual Machine.
The project explores translating and executing a subset of the C language on the JVM, focusing on compiler construction rather than full language compatibility.

It serves as a hands-on study of compiler technology, including C parsing, AST construction and transformation, intermediate representations (such as SSA), and code generation for the JVM.

The project is not production-ready and intentionally supports only a subset of C. Its goal is learning and experimentation in compiler design, not completeness or performance guarantees.


## Frontend

```mermaid
flowchart TD
%% Define Phases Colors (Pastel) with black font
    classDef parserPhase fill:#FFFACD,stroke:#555,stroke-width:1px,color:#000;    %% LemonChiffon
    classDef declPhase fill:#B0E0E6,stroke:#555,stroke-width:1px,color:#000;      %% PowderBlue
    classDef astPhase fill:#98FB98,stroke:#555,stroke-width:1px,color:#000;       %% PaleGreen
    classDef normPhase fill:#FFB6C1,stroke:#555,stroke-width:1px,color:#000;      %% LightPink

%% Nodes
    A[<font color="black">C Source Code</font>]:::parserPhase
B[<font color="black">ANTLR4 Lexer / Parser</font>]:::parserPhase
C[<font color="black">Declaration Collection<br/>DeclarationListener + DeclarationParser</font>]:::declPhase
D[<font color="black">Scopes & Namespaces Populated</font>]:::declPhase
E[<font color="black">ANTLR4 ParseTree</font>]:::parserPhase
F[<font color="black">AST Construction<br/>uses ParseTree + Declarations</font>]:::astPhase
G[<font color="black">Type Building & Semantic Analysis</font>]:::astPhase
H[<font color="black">AST Normalization<br/>e.g. for-loops converted to while-loops</font>]:::normPhase
I[<font color="black">Backend</font><br/>]:::normPhase

%% Arrows with labels
A --> B
B -- initial parse --> C
C --> D
D -- typedefs available --> B
B -- full parse --> E
D -- scope info --> F
E --> F
F --> G
D -- type info --> G
G --> H
H --> I
```

Frontend architecture overview.
The compiler frontend uses ANTLR4 with a custom declaration-collection phase to correctly handle C typedefs and scope resolution. Typedef information is fed back into parsing to disambiguate between identifiers and typedefs, after which the AST is constructed, type-checked, and normalized.

