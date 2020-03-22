# python3

from collections import namedtuple


Bracket = namedtuple("Bracket", ["char", "position"])
answer = -1
len_stack = 0
def are_matching(left, right):
    return (left + right) in ["()", "[]", "{}"]


def find_mismatch(text):
    opening_brackets_stack = []
    global answer
    global len_stack
    for i, next in enumerate(text):
        if next in "([{":
            # Process opening bracket, write your code here
            opening_brackets_stack.append(Bracket(next,i))
            pass

        if next in ")]}":
            # Process closing bracket, write your code here
            if len(opening_brackets_stack)==0:
                answer = i + 1
                break
            top = opening_brackets_stack.pop().char
            if not are_matching(top, next):
                answer = i + 1
                break 
            pass
    len_stack = len(opening_brackets_stack)
    if len_stack:
        answer = opening_brackets_stack.pop().position + 1

def main():
    text = input()
    mismatch = find_mismatch(text)
    global answer
    # Printing answer, write your code here
    if answer != -1:
        print(answer)
    else:
        print("Success")

if __name__ == "__main__":
    main()
