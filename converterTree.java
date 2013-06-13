/*converterTree uses a stack in order to evaluate postfix notation*/

package CSHomework.HW3;
import java.util.Stack;
import java.util.Scanner;
  
public class converterTree  {  

  
  public static String toPostFix(String line)  
  {
    int length = line.length();  
    String postFix = "";
    BoundedStackInterface<String> stack = new ArrayStack<String>(length);	//initialize stack
    
    for(int i = 0; i < length; i++){
    	
      char value = line.charAt(i);
      String s3 = Character.toString(value);
         
         if(value  >= '0' & value<= '9'){
         	     
               postFix = postFix + value;
	       postFix = postFix + " ";
            }        
            
         else if("(".equals(s3)){
           
             String s1 = Character.toString(value);
             stack.push(s1);
           }
         
                  
           else if(")".equals(s3)){
           	
             while(!("(".equals(stack.top()))){
             	
               String x = stack.top();
               stack.pop();
               postFix = postFix + x;
               postFix = postFix + " ";
            
             }
             
           }    
         else if(value=='+' || value=='-' || value=='*' || value=='/' || value=='^'){
           
             String s2 = Character.toString(value);
             
             if(stack.isEmpty()){
               stack.push(s2);
              }
             
             else if(checkPrecedence(stack.top()) <= checkPrecedence(s2)){
               stack.push(s2);
             }
             
             else if(checkPrecedence(stack.top()) > checkPrecedence(s2)){
                 
               while(!(stack.isEmpty())){
               	
                 if("(".equals(stack.top())){
                 	
                   stack.pop();
                   break;
                   
                  }
                  
                 if(checkPrecedence(stack.top()) > checkPrecedence(s2)){
                 	
                   String r = stack.top();
                   stack.pop();
                   postFix = postFix + r;
                   postFix = postFix + " ";
                   
                   }
                   
               break;
                 
             }
        stack.push(s2);
             }
         }
  }   
            while(!(stack.isEmpty())){
            	
      		if("(".equals(stack.top())){
      			
              		stack.pop();
              	}
              	
      		else{
      			
        	String g = stack.top();
      		stack.pop();
      		postFix = postFix + g;
      		postFix = postFix + " ";

      		}
      	}
            return postFix; 
  }
  
     public static int checkPrecedence(String value)
      {
       if("^".equals(value)){
         return 4;}
       if("*".equals(value)){
         return 3;}
       if("/".equals(value)){
         return 2;}
       if("+".equals(value)){
         return 1;}
       if("-".equals(value)){
         return 1;}
       return 0;
      }      

} 
