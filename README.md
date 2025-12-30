# C on JVM

[![ci](https://github.com/erwin-kok/conjvm/actions/workflows/ci.yaml/badge.svg)](https://github.com/erwin-kok/conjvm/actions/workflows/ci.yaml)
[![Kotlin](https://img.shields.io/badge/kotlin-2.3.0-blue.svg?logo=kotlin)](http://kotlinlang.org)
[![License](https://img.shields.io/github/license/erwin-kok/conjvm.svg)](https://github.com/erwin-kok/conjvm/blob/master/LICENSE)

# Introduction

conjvm (“C on the JVM”) is an experimental project that explores running a subset of C code on the Java Virtual Machine. It focuses on translating and executing selected C constructs on the JVM rather than full language compatibility.

Beyond execution, the project serves as a hands-on exploration of compiler technology, including C parsing, AST construction and transformation, intermediate representations (such as SSA), and code generation targeting the JVM.

This project is highly experimental, under active development, and not production-ready. Many aspects of C are intentionally unsupported or only partially implemented. The goal is learning, experimentation, and exploration—not completeness, correctness, or performance guarantees.
