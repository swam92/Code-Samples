/*converterTree uses a stack to conver to postfix notation */

package CSHomework.HW3;
import java.util.Stack;
import java.util.Scanner;
  
public class converterTree  {  

  
  public static String toPostFix(String line)  
  {
    int length = line.length();  
    String postFix = "";
    BoundedStackInterface<String> stack = new ArrayStack<String>(length);	//initialize stack
    
    for(int i = 0; i < length; i++){						//iterate through infix
    	
      char value = line.charAt(i);						//tokenize
      String s3 = Character.toString(value);
         
         if(value  >= '0' & value<= '9'){					//if the token is a number
         	     
               postFix = postFix + value;					//add it to postfix
	       postFix = postFix + " ";
            }        
            
         else if("(".equals(s3)){						//if there is an open parenthesis
           
             String s1 = Character.toString(value);				//push on to stack for future use
             stack.push(s1);
           }
         
                  
           else if(")".equals(s3)){						//if there is a closing parenthesis
           	
             while(!("(".equals(stack.top()))){					//until the open open parenthesis
             	
               String x = stack.top();						//append stack contents to postfix
               stack.pop();
               postFix = postFix + x;
               postFix = postFix + " ";
            
             }
             
           }    
           
         else if(value=='+' || value=='-' || value=='*' || value=='/' || value=='^'){//if the token is an operator
           
             String s2 = Character.toString(value);				     //current token is named s2
             
             if(stack.isEmpty()){						     //if there is nothing on the stack
               stack.push(s2);							     //immediately push operator
              }
             
             else if(checkPrecedence(stack.top()) <= checkPrecedence(s2)){	     //if the current token has higher
               stack.push(s2);							     //precedence than the top of the
             }									     //stack push it on the stack
             
             else if(checkPrecedence(stack.top()) > checkPrecedence(s2)){	     //if the current token has lower precdence
                 
               while(!(stack.isEmpty())){					     //while there are still tokens on stack
               	
                 if("(".equals(stack.top())){					     //stop popping after you reach an open parenthesis
                 	
                   stack.pop();
                   break;
                   
                  }
                  
                 if(checkPrecedence(stack.top()) > checkPrecedence(s2)){	     //if the top of stack has higher precedence
                 	
                   String r = stack.top();					     //append token at top of stack to postfix
                   stack.pop();
                   postFix = postFix + r;
                   postFix = postFix + " ";
                   
                   }
                   
               break;
                 
             }
        stack.push(s2);								   // after previous 2 conditionals push the current token on stack
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
  /* This function assigns each operator a number based on order of operations rules.  The number value of each operator
     is used to determine when to push and pop tokens off the stack */
     
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
