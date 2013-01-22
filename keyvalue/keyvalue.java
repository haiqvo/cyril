//Hai Vo hqvo@ucsc.edu

import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import static java.lang.System.*;
import java.util.Scanner;
import java.util.regex.PatternSyntaxException;

class keyvalue {
    
    static void scanfile (Scanner input, String filename) {
      linkedlist list = new linkedlist();
      int counter=0;
      while (input.hasNext()) {
         int checkEqual=-1;
         counter++;
         String line = input.nextLine();
         if(filename.equals("<stdin>")){
             filename="-";
         }
         if(line.trim().startsWith("#")){
             System.out.printf("%s:%d:%s%n",filename, counter, line);
             continue;
         }
         line=line.replaceAll("\\s", "");
         for(int i=0; i<line.length(); i++){
             if(line.charAt(i)=='='){
                 checkEqual=i;
             }
         }
         linklist(checkEqual, line, list, counter, filename);
         
      }
   }
    
    static void linklist(int checkEqual, String line, 
        linkedlist list, int counter, String filename){
        String key="";
        String value="";
        if(checkEqual != -1){
            key=line.substring(0, checkEqual);
            value=line.substring(checkEqual+1, line.length());
        }else{
            key=line.substring(0, line.length());
        }
        if(checkEqual==-1 && line.length()>0){
            System.out.printf("%s:%d:%s%n",filename, counter, key);
            System.out.printf("%s%n", list.get(key));
        }
        else if (checkEqual==0 && line.length()==1){
            System.out.printf("%s:%d:=%n",filename,counter);
            list.get(key);
        }
        else if (checkEqual==0 && line.length()>1){
            System.out.printf("%s:%d:=%s%n",filename,counter,value);
            list.get("="+value);
        }
        else if (checkEqual == line.length()-1){
           System.out.printf("%s:%d:%s%n",filename,
                             counter, list.delete(key));
        }
        else if (checkEqual>0 && checkEqual != line.length()-1){
            System.out.printf("%s:%d:%s%n",filename, counter,
                              list.put(key, value));
        }
    }

   public static void main (String[] args) {
      
      try {
      if (args.length == 0) {
         scanfile (new Scanner (in), "<stdin>");
      }else {
            for (int argi = 0; argi < args.length; ++argi) {
               try {
                  if(args[argi].equals("-")){
                      scanfile(new Scanner(in), "<stdin>");
                  } 
                  String filename = args[argi];
                  Scanner input = new Scanner (new File (filename));
                  scanfile (input, filename);
                  input.close();
               }catch (IOException error) {
                  messages.warn (error.getMessage());
               }
            }
         }
      }catch(PatternSyntaxException error) {
         messages.die (error.getMessage());
      }
   }

}

