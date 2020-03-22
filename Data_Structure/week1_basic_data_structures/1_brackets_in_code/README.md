The execution of the codes:

cpp: 
    g++ -pipe -O2 -std=c11 check_brackets.cpp -lm
    ./a.out < tests/1

java:
    javac -encoding UTF-8 check_brackets.java
    java -Xmx1024m check_brackets < tests/1

python3:
    python3 check_brackets.py < tests/1
