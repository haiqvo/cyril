import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;

class jgrep {

   static void scanfile (Scanner input, String filename,
                         Pattern pattern) {
      while (input.hasNextLine()) {
         String line = input.nextLine();
         boolean matches = pattern.matcher (line).find();
         if (matches) {
            out.printf ("%s:%s%n", filename, line);
         }
      }
   }

   public static void main (String[] args) {
      options opts = new options (args);
      if (args.length == 0) {
         err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                     messages.program_name);
         exit (messages.EXIT_FAILURE);
      }
      try {
         String regex = args[0];
         Pattern pattern = Pattern.compile (regex);
         if (args.length == 1) {
            scanfile (new Scanner (in), "<stdin>", pattern);
         }else {
            for (int argi = 1; argi < args.length; ++argi) {
               try {
                  String filename = args[argi];
                  Scanner input = new Scanner (new File (filename));
                  scanfile (input, filename, pattern);
                  input.close();
               }catch (IOException error) {
                  messages.warn (error.getMessage());
               }
            }
         }
      }catch (PatternSyntaxException error) {
         messages.die (error.getMessage());
      }
      exit (messages.exit_status);
   }

}
