// Hai Vo hqvo@ucsc.edu

class options {
   boolean insensitive=false;
   boolean filename_only=false;
   boolean number_lines=false;
   boolean reverse_match=false;
   boolean moreThanOneFile=false;
   boolean realOption=true;
   String regex;
   String[] filenames;
   char[] letterOptions;
   int startIndex = 1;
   //Hello

   options (String[] args) {
         int count =0;
         if(args[0].startsWith("-")){
              letterOptions = new char[args[0].length()];
              regex = args[1];
              startIndex = 2;
              for(int i = 0; i<args[0].length(); i++){
                   letterOptions[i] = args[0].charAt(i);
              }
              for(int j = 2; j<args.length; j++){
                   count++;
              }
         }else{
              regex=args[0];
              for(int i = 1; i<args.length; i++){
                   count++;
              }
         }
         if(count>1){
              moreThanOneFile = true;
         }
   }
   public void optionCases() {
         for(int i = 1; i<letterOptions.length; i++){
              switch(letterOptions[i]){
                   case 'i':
                        insensitive = true;
                        break;
                   case 'l':
                        filename_only = true;
                        break;
                   case 'n':
                        number_lines = true;
                        break;
                   case 'v':
                        reverse_match = true;
                        break;
                   default:
                        realOption=false;
              }
         }
   }
}

