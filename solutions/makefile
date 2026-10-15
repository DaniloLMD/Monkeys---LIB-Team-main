// flags for speed. Make the code run faster and don't debug things. Just using some of the debugging flags so you know that something is exploding.

CXX = g++
CXXFLAGS = -fsanitize=address -fno-omit-frame-pointer -g -O2 -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare

// Flags for debug. Use it in case something goes very wrong. They are separated because those below makes the compiler and the program go absurdly slow. Use it to catch mistakes like segmentation fault, division by zero, and many other things. It's not that much flags, but there is no need to make the compiler and the code run very slow everytime.
    
CXX = g++
CXXFLAGS = -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts -fsanitize=undefined -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC