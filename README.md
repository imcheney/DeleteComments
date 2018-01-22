CommentDeleter Version 1.0
# What
a **python3** script to help you delete all comments in your CPP/Java code

# How
run the Python3 script with your command
For a directory: Python3 CommentDeleter.py /Users/cxl/demo cpp
For a file: Python3 CommentDeleter.py /Users/cxl/demo/code.cpp cpp

It is a best practice to clearly specify your path and code_type -- is it a c, cpp or java file?

# Why(Design)
- Use Python3's simple file manipulation;
- Very much like a tokenizer(lexer) and a parser;
- delete line comments and keep one '\n' so your code layout can stay the same way;
- delete block comments and keep only one '\n' so not much white space left;