// $Id: treemap.java,v 1.1 2012-10-31 13:12:50-07 - - $

import java.io.*;
import static java.lang.System.*;

class treemap <key_t extends Comparable<key_t>, value_t> {
    private class bstree {
      key_t key;
      value_t value;
      bstree left;
      bstree right;

      private bstree(key_t key1, value_t value1) {
          key = key1;
          value = value1;
        }
   }
   private bstree root = null;

   public value_t put (key_t key, value_t value) {
      if(root == null){
          root = new bstree(key, value);
          return root.value;
      }
      int cmp;
      bstree temp = root;
      while (temp != null){
          cmp = temp.key.compareTo(key);
          if(cmp == 0){
              temp.value = value;
              break;
          } else if (cmp > 0){
              if(temp.left == null){
                  temp.left = new bstree(key, value);
                  break;
              } else {
                  temp = temp.left;
              }
          } else {
              if(temp.right == null){
                  temp.right = new bstree(key, value);
                  break;
              } else {
                  temp = temp.right;
              }
          }
      }
      return temp.value;
   }

   public value_t get (key_t key) { 
       if(root == null){
           return null;
       }
       bstree temp = root;
       int compare;
       while((compare = temp.key.compareTo(key)) != 0){
           if(compare > 0) {
               if(temp.left != null){
                   temp = temp.left;
               }else{
                   return null;
               }
           }else {
               if(temp.right != null){
                   temp = temp.right;
               }else{
                   return null;
               }
           }
       }
       return temp.value;
   }

   public value_t remove (key_t key) {
      throw new UnsupportedOperationException ();
   }

   public void visit_all (visitor <key_t, value_t> visitor_fn) {
      visit_all_inorder (root, visitor_fn);
   }

   private void visit_all_inorder (bstree tree,
                  visitor <key_t, value_t> visitor_fn) {

       if(tree !=null){
           this.visit_all_inorder(tree.left, visitor_fn);
           visitor_fn.visit (tree.key, tree.value);
           this.visit_all_inorder(tree.right, visitor_fn);
       }
   }

   public void debug_dump () {
      debug_dump_inorder (root, 0);
   }

   private void debug_dump_inorder (bstree tree, int depth) {
      if (tree == null){
          return;
      }
      this.debug_dump_inorder (tree.left, depth + 1);
      String sfmt = "%" + (depth > 0 ? depth * 3 : "") + "s";
      out.printf (sfmt + "%d: %s => %s%n",
                  "", depth, tree.key, tree.value);
      this.debug_dump_inorder (tree.right, depth + 1);
   }

}
