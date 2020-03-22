import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Stack;

class Bracket {
    Bracket(char type, int position) {
        this.type = type;
        this.position = position;
    }

    boolean Match(char c) {
        if (this.type == '[' && c == ']')
            return true;
        if (this.type == '{' && c == '}')
            return true;
        if (this.type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
}

class check_brackets {
    public static void main(String[] args) throws IOException {
        InputStreamReader input_stream = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(input_stream);
        String text = reader.readLine();
        int answer = -1;
        Stack<Bracket> opening_brackets_stack = new Stack<Bracket>();
        for (int position = 0; position < text.length(); ++position) {
            char next = text.charAt(position);

            if (next == '(' || next == '[' || next == '{') {
                // Process opening bracket, write your code here
                Bracket tmp = new Bracket(next, position);
                opening_brackets_stack.push(tmp);
            }

            if (next == ')' || next == ']' || next == '}') {
                // Process closing bracket, write your code here
               if(opening_brackets_stack.isEmpty()){
                   answer = position + 1;
                   break;
               }
               if(opening_brackets_stack.peek().Match(next)){
                   opening_brackets_stack.pop();
               }
               else{
                   answer = position + 1;
                   break;
               }
               
            }
        }

        // Printing answer, write your code here
        if(opening_brackets_stack.isEmpty() && answer==-1){
            System.out.println("Success");
        }
        else{
            if(!opening_brackets_stack.isEmpty() && answer==-1){
                answer = opening_brackets_stack.peek().position + 1;
            }
            System.out.println(answer);
        }
    }
}
