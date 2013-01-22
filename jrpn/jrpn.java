//Hai Vo hqvo@ucsc.edu
import java.util.Scanner;

public class jrpn {

    public static boolean isDouble( String input ) {
        try {
            Double.parseDouble( input );
            return true;
        }
        catch( Exception e ) {
            return false;
        }
    }
    
    
    public static void main(String[] args) {
        final int EMPTY = -1;
        int top = EMPTY;
        double[] stack = new double[16];
        Scanner input = new Scanner(System.in);
        while (input.hasNext()){
            String scanInput = input.next();
            if (scanInput.startsWith("#")){
                input.nextLine();
                continue;
            }
            if(isDouble(scanInput)){
                top++;
                try{
                    stack[top] = Double.parseDouble(scanInput);
                }catch(Exception e){
                    System.err.printf("Stack Overflow%n");
                }    
            }
            else{
                if(scanInput.length()==1){
                    try{
                    switch (scanInput.charAt(0)) {
                        case '+':
                            stack[top-1] = stack[top]+stack[top-1];
                            top--;
                            break;
                        case '-':
                            stack[top-1] = stack[top]-stack[top-1];
                            top--;
                            break;
                        case '*':
                            stack[top-1] = stack[top]*stack[top-1];
                            top--;
                            break;
                        case '/':
                            stack[top-1] = stack[top]/stack[top-1];
                            top--;
                            break;
                        case '~':
                            for(int i = stack.length-1; i>=0; i--){
                                stack[i] = 0;
                            }
                            top = EMPTY;
                            break;
                        case ';':
                            for(int i = top; i>=0; i--){
                                System.out.printf("%22.15g\n", 
                                                   stack[i]);
                            }
                            break;
                        default:
                            System.err.printf("improper command%n");
                            break;
                    }
                    }catch(Exception e) {
                        System.err.printf("Stack underflow%n");
                    }
                }else{
                        System.err.printf("%s is not a single "
                                + "character%n", scanInput);
                }
            }
        }
    }
}
