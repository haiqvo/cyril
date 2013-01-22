// $Id: options.java,v 1.2 2012-11-12 00:32:55-08 - - $

class options {
   boolean count_only = false;
   boolean dump_tree = false;
   boolean fold_cases = false;
   boolean wrong_option = false;
   String[] filenames = null;
   String optionType = null;
   int counter = 0;
   int loop = 0;
   options (String[] args) {
       if(args[0].startsWith("-") && args[0].length()>1){
           optionType = args[0];
           loop = 1;
           filenames = new String[args.length-1];
       }else{
           filenames = new String[args.length];
       }
       for(int i = loop; i<args.length; i++){
           filenames[counter]= args[i];
           counter++;
       }
       if(optionType != null){
           for(int j = 1; j<optionType.length(); j++){
               if(optionType.charAt(j) == 'c'){
                   count_only = true;
               }
               else if(optionType.charAt(j)=='d'){
                   dump_tree = true;
               }
               else if(optionType.charAt(j)=='f'){
                   fold_cases = true;
               }else{
                   System.err.printf("jxref: %s: is a invalid"
                           + " option%n", optionType.charAt(j));
                   wrong_option = true;
               }
           }
       }
   }

}
