import java.util.Scanner;
import static java.lang.System.*;

class Test {

   static class list_t {
      node_t head;
   }
   static class node_t {
      String item;
      node_t link;
   }

   static void insertascending (list_t list, String newitem) {
      node_t prev = null;
      node_t curr = list.head;

      // Find the insertion position.
      while (curr != null) {
         if (curr.item.compareTo (newitem) > 0) break;
         prev = curr;
         curr = curr.link;
      }

      // Do the insertion.
      node_t temp = new node_t();
      temp.item = newitem;
      temp.link = curr;
      if (prev == null) list.head = temp;
                   else prev.link = temp;
   }

   public static void main (String[] args) {
      Scanner stdin = new Scanner (System.in);
      list_t list = new list_t();

      while (stdin.hasNextLine()) {
         String line = stdin.nextLine();
         insertascending (list, line);
      }

      for (node_t curr = list.head; curr != null; curr = curr.link) {
         out.printf ("%s%n", curr.item);
      }
   }

}