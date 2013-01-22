// $Id: linkedlist.java,v 1.1 2012-10-18 13:19:38-07 - - $
//Hai Vo hqvo@ucsc.edu
import java.util.Iterator;
import java.util.NoSuchElementException;

class linkedlist implements Iterable<pair> {

   private class node {
      pair item;
      node link;
   }
   private node head = null;

   public String get (String key) {
      for (node curr = head; curr != null; curr = curr.link) {
         if(curr.item.key.equals(key)){
             return key+"="+curr.item.value;
         }
         if(key.equals("")){
             System.out.println(curr.item.key+"="+curr.item.value);
         }
         if(key.startsWith("=")){
             if(key.equals("="+curr.item.value)){
                 System.out.println(curr.item.key+"="+curr.item.value);
             }
         }
      } 
      return "not found";
   }

   public String put (String key, String value) {
      node prev = null;
      node curr = head;
      int cmp = 1;
      while (curr != null){
          cmp = curr.item.key.compareTo(key);
          if (cmp >=0){
              break;
          }
          prev = curr;
          curr = curr.link;
      }
      if(cmp != 0){
          node tmp = new node();
          pair foo = new pair(key, value);
          tmp.item = foo;
          tmp.link = curr;
          
          if(prev == null){
              head = tmp;
          }else{
              prev.link = tmp;
          }
      }
      else if(cmp == 0){
          String output = key+"="+value+"\n"+curr.item.key+"="
                  +curr.item.value;
          curr.item.value=value;
          return output;
      }
   return key+"="+value;
   }

   public String delete (String key) {
       node prev = null;
       node curr = head;
       int cmp = 1;
       while (curr != null){
           cmp = curr.item.key.compareTo(key);
           if(cmp >= 0){
               break;
           }
           prev = curr;
           curr = curr.link;
       }
       if(cmp == 0){
           String output = key+"="+"\n"+curr.item.key+"="
                  +curr.item.value;
           if(prev == null){
              head=head.link;
          }else{
           prev.link=curr.link;
           }
           return output;
       }
      return key+"="; 
   }

   public Iterator<pair> iterator () {
      return new itor ();
   }

   private class itor implements Iterator<pair> {
      private node nextnode = head;

      public boolean hasNext () {
         return nextnode != null;
      }

      public pair next () {
         if (! hasNext()) throw new NoSuchElementException ();
         pair result = nextnode.item;
         nextnode = nextnode.link;
         return result;
      }

      public void remove () {
         throw new UnsupportedOperationException ();
      }
   }
}
