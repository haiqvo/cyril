// Hai Vo hqvo@ucsc.edu

//
// This program is a stub showing how to create a pattern from a
// regular expression.  It does not handle options or files, and
// has some other bugs which you must discover and fix.
//

import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;

class jgrep {

   static void scanfile (Scanner input, String filename,
                         Pattern pattern, options opts) {
      int counter = 0;
      int matchCount = 0;
      while (input.hasNextLine()) {
         counter++;
         String line = input.nextLine();
         String sentence =""; 
         boolean matches = pattern.matcher (line).find();
         if(opts.reverse_match){
              matches = !matches;
         }
         if (matches) {
              if(messages.exit_status == 1){
                   messages.match();
              }
              matchCount++;
              if(opts.filename_only){
                   out.printf("%s%n", filename);
                   break;
              }
              else if(opts.number_lines && opts.moreThanOneFile){
                   out.printf("%s:%s:%s%n", filename, counter, line);
              }
              else if (opts.number_lines && !opts.moreThanOneFile){
                   out.printf("%s:%s%n", counter, line);
              }else{
                   if(opts.moreThanOneFile){
                        out.printf("%s:%s%n", filename, line);
                   }else{
                        out.printf("%s%n", line);
                   }
              }
         }
      }
   }

   public static void main (String[] args) {
      if (args.length == 0) {
         err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                     messages.program_name);
         exit (messages.EXIT_FAILURE);
      }
      options opts = new options (args);
      try {
         messages.noMatch();
         if(args[0].startsWith("-")){
              opts.optionCases();
         }
         if(!opts.realOption){
              err.printf
              ("Not a possible option only [ilnv] will work%n");
              messages.exit_status = messages.EXIT_FAILURE;
         }
         Pattern pattern = Pattern.compile(opts.regex);
         if (opts.insensitive){
              pattern = Pattern.compile(opts.regex, 
                                        Pattern.CASE_INSENSITIVE);
         }
         if (args.length == opts.startIndex) {
              scanfile (new Scanner (in), "<stdin>", pattern, opts);
         }else {
            for (int argi = opts.startIndex; 
                                   argi < args.length; ++argi) {
               try {
                  String filename = args[argi];
                  Scanner input = new Scanner (new File (filename));
                  scanfile (input, filename, pattern, opts);
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
