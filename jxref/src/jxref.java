
import java.io.*;
import java.util.Iterator;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import static java.lang.System.*;

class jxref {
   static final String WORD_REGEX =  "\\w+([-'.:/]\\w+)*"; 
   static final Pattern WORD_PATTERN = Pattern.compile (WORD_REGEX);

   // Pseudo-typedef in Java, q.v., typedef in C.
   static class string_cqueue_map
                extends treemap <String, counted_queue <Integer>> {
   }

   static class print_visitor
                implements visitor <String, counted_queue <Integer>> {
      boolean want_queue_printed;
      print_visitor (boolean count_only) {
         want_queue_printed = ! count_only;
      }
      public void visit (String key, counted_queue<Integer> queue) {
         out.printf ("%s [%d]", key, queue.count());
         if (want_queue_printed) {
            for (int line_nr: queue) out.printf (" %d", line_nr);
         }
         out.printf ("%n");
      }
   }


   static void scanfile (String filename, Scanner file, options opts) {
      out.printf("%n");
      for(int i=0; i<50; i++)out.printf(":");
      out.printf ("%n%s%n", filename);
      for(int i=0; i<50; i++)out.printf(":");
      out.printf("%n%n");
      string_cqueue_map tree = new string_cqueue_map();
      treemap temp = new treemap();
      for (int linenr = 1; file.hasNextLine(); ++linenr) {
         String line = file.nextLine();
         Matcher matcher = WORD_PATTERN.matcher (line);
         while (matcher.find()) {
            String word = matcher.group();
            if(opts.fold_cases){
                word = word.toLowerCase();
            }
            counted_queue <Integer> queue = tree.get(word);
            if(queue != null){
                queue.insert(linenr);
            }else{
                queue = new counted_queue <Integer>();
                queue.insert(linenr);
                tree.put(word, queue);
            }
         }
      }
      if(opts.dump_tree){
          tree.debug_dump();  
      }else {
      tree.visit_all (new print_visitor (opts.count_only));
      }
   }

   public static void main (String[] args) {
      options opts = new options (args);
      for (String filename : opts.filenames) {
         if(opts.wrong_option){
             messages.exit_status = messages.EXIT_FAILURE;
         }
         if (filename.equals ("-")) {
            scanfile ("-", new Scanner (in), opts);
         }else {
            try {
               Scanner scan = new Scanner (new File (filename));
               scanfile (filename, scan, opts);
               scan.close();
            }catch (IOException error) {
               messages.warn (error.getMessage());
            }
         }
      }
      exit (messages.exit_status);
   }

}
