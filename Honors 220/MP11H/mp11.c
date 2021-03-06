/*									tab:8
 *
 * mp11.c - skeleton code generation for ECE190 compiler MP (F08 MP5)
 *
 * "Copyright (c) 2008-2018 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Steve Lumetta
 * Version:	    3
 * Creation Date:   Wed Oct 15 10:16:14 2008
 * Filename:	    mp11.c
 * History:
 *	SL	3	Tue Apr 03 23:23:23 2018
 *		Changed MP5 to MP11 and 190 to 220 for ECE220.
 *	SL	2	Tue Oct 21 14:28:10 2008
 *		Extracted from gold version.
 *	SL	1	Wed Oct 15 10:16:14 2008
 *		First written.
 */


#include <stdio.h>

#include "ece220_label.h"
#include "ece220_parse.h"
#include "ece220_symtab.h"


/*
 * PARAMETERS AND CONSTANTS
 */

typedef enum {
    BR_NEVER, BR_P, BR_Z, BR_ZP, BR_N, BR_NP, BR_NZ, BR_ALWAYS, NUM_BR
} br_type_t;



/*
 * HELPER FUNCTION PROTOTYPES--see function headers for further information
 */

static void gen_long_branch (br_type_t type, ece220_label_t* label);

static void gen_statement (ast220_t* ast);
static void gen_for_statement (ast220_t* ast);
static void gen_if_statement (ast220_t* ast);
static void gen_return_statement (ast220_t* ast);
static void gen_pop_stack (ast220_t* ast);
static void gen_debug_marker (ast220_t* ast);

static void gen_expression (ast220_t* ast);
static void gen_push_int (ast220_t* ast);
static void gen_push_str (ast220_t* ast);
static void gen_push_variable (ast220_t* ast);
static void gen_func_call (ast220_t* ast);
static void gen_get_address (ast220_t* ast);
static void gen_op_assign (ast220_t* ast);
static void gen_op_pre_incr (ast220_t* ast);
static void gen_op_pre_decr (ast220_t* ast);
static void gen_op_post_incr (ast220_t* ast);
static void gen_op_post_decr (ast220_t* ast);
static void gen_op_add (ast220_t* ast);
static void gen_op_sub (ast220_t* ast);
static void gen_op_mult (ast220_t* ast);
static void gen_op_div (ast220_t* ast);
static void gen_op_mod (ast220_t* ast);
static void gen_op_negate (ast220_t* ast);
static void gen_op_log_not (ast220_t* ast);
static void gen_op_log_or (ast220_t* ast);
static void gen_op_log_and (ast220_t* ast);
static void gen_comparison (ast220_t* ast, const char* false_cond);
static void gen_op_cmp_ne (ast220_t* ast);
static void gen_op_cmp_less (ast220_t* ast);
static void gen_op_cmp_le (ast220_t* ast);
static void gen_op_cmp_eq (ast220_t* ast);
static void gen_op_cmp_ge (ast220_t* ast);
static void gen_op_cmp_greater (ast220_t* ast);


/*
 * FILE SCOPE VARIABLES
 *
 * N.B.  You will need to have a file scope variable to implement one
 * of the statements.  Define it here.
 *
 * static int foo;  <-- a file scope variable ("static" means only this file)
 *
 */

static ece220_label_t *tear_label;

/*
 * INTERFACE FUNCTIONS -- called from other files; the one function listed
 * here is the equivalent of "main" for students working on this MP
 */

/*
 * MP11_generate_code
 *   DESCRIPTION: perform LC-3 code generation (print to stdout)
 *   INPUTS: prog -- the main subroutine of the program (a list of
 *                   statements)
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
void
MP11_generate_code (ast220_t* prog)
{
    /*create tear label once*/
    static int count = 0;
    if(count++ == 0)    tear_label = label_create();
    /*if prog is null, print out the tear label and return*/
    if(!prog)
    {
        printf("%s\n", label_value(tear_label));
        return;
    }
    /*generate the current statement*/
    gen_statement(prog);
    /*generate statement for the next statement*/
    MP11_generate_code(prog->next);
}

/*
 * HELPER FUNCTIONS (used only within this file)
 */

/*
 * gen_long_branch
 *   DESCRIPTION: generate LC-3 assembly code for a branch without offset
 *                limitations
 *   INPUTS: type -- the type of branch to be performed
 *           label -- the branch target label
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_long_branch (br_type_t type, ece220_label_t* label)
{
    static const char* const br_names[NUM_BR] = {
        "; ", "BRp", "BRz", "BRzp", "BRn", "BRnp", "BRnz", "BRnzp"
    };
    br_type_t neg_type;
    ece220_label_t* target_label;
    ece220_label_t* false_label;

    neg_type = (type ^ 7);
    target_label = label_create ();
    false_label = label_create ();
    printf ("\t%s %s\n", br_names[neg_type], label_value (false_label));
    printf ("\tLD R3,%s\n\tJMP R3\n", label_value (target_label));
    printf ("%s\n", label_value (target_label));
    printf ("\t.FILL %s\n", label_value (label));
    printf ("%s\n", label_value (false_label));
}

/*
 * gen_statement
 *   DESCRIPTION: generate LC-3 assembly code for an arbitrary statement
 *   INPUTS: ast -- the AST node corresponding to the statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_statement (ast220_t* ast)
{
    switch (ast->type) {
        case AST220_FOR_STMT:     gen_for_statement (ast);    break;
        case AST220_IF_STMT:      gen_if_statement (ast);     break;
        case AST220_RETURN_STMT:  gen_return_statement (ast); break;
        case AST220_POP_STACK:    gen_pop_stack (ast);        break;
        case AST220_DEBUG_MARKER: gen_debug_marker (ast);     break;
	      default: fputs ("BAD EXPRESSION TYPE\n", stderr);   break;
    }
}

/*
 * gen_for_statement
 *   DESCRIPTION: generate LC-3 assembly code for an for loop
 *   INPUTS: ast -- the AST node corresponding to the for loop
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_for_statement (ast220_t* ast)
{
    /*First, assignment, then test, then execute, then update, branch to test*/
    if(ast->left)
        gen_statement(ast->left);
    /*create label for the test code, and generate the test code*/
    ece220_label_t *test_do = label_create();
    printf("%s\n", label_value(test_do));
    /*No need to check for null, it always exists*/
    gen_expression(ast->test);
    /*check if the test condition was satisfied*/
    ece220_label_t *test_fail = label_create();
    printf("\tLDR R1,R6,#0\n");
    br_type_t zero = BR_Z;
    br_type_t always = BR_ALWAYS;
    /*if it wasn't, branch to test fail label*/
    gen_long_branch(zero,test_fail);
    /*generate the body of the code*/
    ast220_t *curr = ast->middle;
    while(curr){
        gen_statement(curr);
        curr=curr->next;
    }
    /*if there's an update statement, generate it*/
    if(ast->right)
        gen_statement(ast->right);

    /*the code goes always goes back to the test*/
    gen_long_branch(always, test_do);
    printf("%s\n",label_value(test_fail));
}

/*
 * gen_if_statement
 *   DESCRIPTION: generate LC-3 assembly code for an if statement
 *   INPUTS: ast -- the AST node corresponding to the if statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_if_statement (ast220_t* ast)
{
    /*If the test is correct*/
    /*execute statements in left, else right (a linked list)*/
    gen_expression(ast->test);
    ece220_label_t *if_l = label_create();
    /*This leaves a 0 or 1 on stack, depending on that value, branch*/
    printf("\tLDR R1,R6,#0\n");
    br_type_t np = BR_NP;
    gen_long_branch(np,if_l);
    /*generate the body for the else part*/
    ast220_t *curr = ast->right;
    while(curr)
    {
        gen_statement(curr);
        curr = curr->next;
    }
    br_type_t always = BR_ALWAYS;
    ece220_label_t *else_l = label_create();
    /*dont want to execute the if body, so branch away*/
    gen_long_branch(always, else_l);
    /*if the if test passes, we'll branch to this label*/
    printf("%s\n",label_value(if_l));
    curr = ast->left;
    /*generate code for the if then body*/
    while(curr)
    {
        gen_statement(curr);
        curr = curr->next;
    }
    /*want else body without executing if body code, so print label for that*/
    printf("%s\n", label_value(else_l));
}

/*
 * gen_return_statement
 *   DESCRIPTION: generate LC-3 assembly code for a return statement
 *   INPUTS: ast -- the AST node corresponding to the return statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_return_statement (ast220_t* ast)
{
      /* generate expression to be RETURNed
       * the assumption being made is that the top holds the
       * result of the expression (string, a number, whatever)
       */
      gen_expression(ast->left);
      printf("\tLDR R0,R6,#0\n\tSTR R0,R5,#3\n");
      br_type_t always = BR_ALWAYS;
      /*Branch to the part of the code responsible for tearing down the stack*/
      /*MP11_gen is responsible for printing out the label in it's place*/
      gen_long_branch(always,tear_label);
}

/*
 * gen_pop_stack
 *   DESCRIPTION: generate LC-3 assembly code to pop and discard a value
 *                from the stack
 *   INPUTS: ast -- the AST node corresponding to the pop stack statement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_pop_stack (ast220_t* ast)
{
    /*left is assumed to exist, so not checking it. Simply produce a result*/
    gen_expression(ast->left);
    /*and discard the value*/
    printf("\tADD R6,R6,#1\n");
}

/*
 * gen_debug_marker
 *   DESCRIPTION: generate LC-3 assembly code for a debug marker used to
 *                help debug LC-3 code generation; the marker is simply
 *                a comment in the assembly code that can be used to
 *                identify pieces of code generated by the compiler
 *   INPUTS: ast -- the AST node corresponding to the debug marker
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints an LC-3 assembly comment
 */
static void
gen_debug_marker (ast220_t* ast)
{
    printf ("; --------------- DEBUG(%d) ---------------\n", ast->value);
}

/*
 * gen_expression
 *   DESCRIPTION: generate LC-3 assembly code to calculate an arbitrary
 *                expression and push the result onto the stack
 *   INPUTS: ast -- the AST node corresponding to the expression
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_expression (ast220_t* ast)
{
    switch (ast->type) {
        case AST220_PUSH_INT:     gen_push_int (ast);       break;
        case AST220_PUSH_STR:     gen_push_str (ast);       break;
        case AST220_VARIABLE:     gen_push_variable (ast);  break;
        case AST220_FUNC_CALL:    gen_func_call (ast);      break;
      	case AST220_GET_ADDRESS:  gen_get_address (ast);    break;
      	case AST220_OP_ASSIGN:    gen_op_assign (ast);      break;
      	case AST220_OP_PRE_INCR:  gen_op_pre_incr (ast);    break;
      	case AST220_OP_PRE_DECR:  gen_op_pre_decr (ast);    break;
      	case AST220_OP_POST_INCR: gen_op_post_incr (ast);   break;
      	case AST220_OP_POST_DECR: gen_op_post_decr (ast);   break;
      	case AST220_OP_ADD:       gen_op_add (ast);         break;
      	case AST220_OP_SUB:       gen_op_sub (ast);         break;
      	case AST220_OP_MULT:      gen_op_mult (ast);        break;
      	case AST220_OP_DIV:       gen_op_div (ast);         break;
      	case AST220_OP_MOD:       gen_op_mod (ast);         break;
      	case AST220_OP_NEGATE:    gen_op_negate (ast);      break;
      	case AST220_OP_LOG_NOT:   gen_op_log_not (ast);     break;
      	case AST220_OP_LOG_OR:    gen_op_log_or (ast);      break;
      	case AST220_OP_LOG_AND:   gen_op_log_and (ast);     break;
      	case AST220_CMP_NE:       gen_op_cmp_ne (ast);      break;
      	case AST220_CMP_LESS:     gen_op_cmp_less (ast);    break;
      	case AST220_CMP_LE:       gen_op_cmp_le (ast);      break;
      	case AST220_CMP_EQ:       gen_op_cmp_eq (ast);      break;
      	case AST220_CMP_GE:       gen_op_cmp_ge (ast);      break;
      	case AST220_CMP_GREATER:  gen_op_cmp_greater (ast); break;
      	default: fputs ("BAD EXPRESSION TYPE\n", stderr);   break;
    }
}

static void
variable_functions(ast220_t *ast)
{
      symtab_entry_t *var = symtab_lookup(ast->name);
      ece220_label_t *address_lbl = label_create();
      ece220_label_t *branch = label_create();
      if(var->array_len == 0){
          /*The case where it's not an array*/
          /*Load the offset into R2, the offset is .FILLed into an address*/
          printf("\tLD R2,%s\n", label_value(address_lbl));
          /**/
          printf("\tADD R3,R%d,R2\n\tADD R6,R6,#-1\n\tBRnzp %s\n",
          (5-var->is_global), label_value(branch));
          printf("%s\n\t.FILL #%d\n", label_value(address_lbl), var->offset);
          printf("%s\n",label_value(branch));
      }
      else
      {
          /*Get the index we want to access*/
          gen_expression(ast->left);
          /*load the index, add it to the offsetted register, load the variable*/
          /*then push it onto the stack. Leaving the address in R0 will help*/
          /*when we want to increment/decrement a variable*/
          printf("\tLD R2,%s\n", label_value(address_lbl));
          printf("\tLDR R1,R6,#0\n\tADD R0,R%d,R1\n",
          (5-var->is_global));
          printf("\tADD R3,R2,R0\n\tBRnzp %s\n", label_value(branch));
          printf("%s\n\t.FILL #%d\n",label_value(address_lbl), var->offset);
          printf("%s\n", label_value(branch));
      }
  }

/*
 * gen_push_int
 *   DESCRIPTION: generate LC-3 assembly code to push a constant integer
 *                expression onto the stack
 *   INPUTS: ast -- the AST node corresponding to the integer
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_push_int (ast220_t* ast)
{
    /*create label for .fill*/
    ece220_label_t* fill_label = label_create ();
    ece220_label_t* target_label = label_create ();
    /*load value into R0 from label*/
    printf("\tLD R0,%s\n", label_value(fill_label));
    /*increment stack pointer,store value in R0 at adress in R6*/
    printf("\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n");
    /*branch to next position, thereby skipping the .fill*/
    printf("\tBRnzp %s\n", label_value(target_label));
    printf("%s\n", label_value(fill_label));
    printf("\t.FILL #%d\n", ast->value);
    printf("%s\n", label_value(target_label));
}

/*
 * gen_push_str
 *   DESCRIPTION: generate LC-3 assembly code to push a constant string
 *                expression onto the stack
 *   INPUTS: ast -- the AST node corresponding to the string
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_push_str (ast220_t* ast)
{
    /*create label for string address*/
    ece220_label_t *string_label = label_create();
    ece220_label_t *jump = label_create();
    /*load address of string label,increase stack size, push address on stack*/
    printf("\tLEA R0,%s\n\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n",
    label_value(string_label));
    printf("\tBRnzp %s\n", label_value(jump));
    printf("%s\n",label_value(string_label));
    printf("\t.STRINGZ %s\n", ast->name);
    printf("%s\n", label_value(jump));
}

/*
 * gen_push_variable
 *   DESCRIPTION: generate LC-3 assembly code to push a variable's value
 *                onto the stack
 *   INPUTS: ast -- the AST node corresponding to the variable reference
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_push_variable (ast220_t* ast)
{
    /*Call variable functions and push the variable onto the stack*/
    variable_functions(ast);
    printf("\tLDR R1,R3,#0\n\tSTR R1,R6,#0\n");
}

/*
 * Helper function to branch to the printf and scanf subroutines
 * called by gen_func_call when the printf function is called
 * There's a linked list of arguments that needs to be processed
 */
static void gen_io(ast220_t *ast, char func[])
{
    /*This sets curr to ast left and pushes all arguments onto stack*/
    ast220_t *curr = ast->left;
    /*while keeping track of the number (to pop them later)*/
    int32_t i = 0;
    while(curr)
    {
        gen_expression(curr);
        curr = curr->next;
        i++;
    }
    /*create label for function name*/
    ece220_label_t *func_label = label_create();
    ece220_label_t *return_address = label_create();
    /*Based on printf or scanf, print the label to jump to*/
    printf("\tLD R0,%s\n\tJSRR R0\n", label_value(func_label));
    printf("\tBRnzp %s\n", label_value(return_address));
    printf("%s\n\t.FILL %s\n", label_value(func_label), func);
    /*Load return value, pop all arguments but one, and push the return value*/
    printf("%s\n\tLDR R1,R6,#0\n",label_value(return_address));
    while(i-- != 0)
        printf("\tADD R6,R6,#1\n");
    printf("\tSTR R1,R6,#0\n");
}

static void gen_rand(ast220_t *ast)
{
    /*check if it's rand or srand based on number of arguments*/
    ast220_t *curr = NULL;
    int32_t i = 0;
    int is_srand = 0;
    if(ast->left){
        curr = ast->left;
        while(curr)
        {
            is_srand = 1;
            gen_expression(curr);
            curr = curr->next;
            i++;
        }
    }
    /*create lavels, jump to the function*/
    ece220_label_t *rand_l = label_create();
    ece220_label_t *return_address = label_create();
    printf("\tLD R0, %s\n", label_value(rand_l));
    printf("\tJSRR R0\n");
    printf("\tBRnzp %s\n", label_value(return_address));
    printf("%s\n", label_value(rand_l));
    if(is_srand)  printf("\t.FILL SRAND\n");
    else          printf("\t.FILL RAND\n");
    printf("%s\n",label_value(return_address));
    /*load return value, pop off arguments, and push argument value on*/
    printf("\tLDR R1,R6,#0\n");
    while(is_srand && i-- != 0)
        printf("\tADD R6,R6,#1\n");
    printf("\tSTR R1,R6,#0\n");
}


/*
 * gen_func_call
 *   DESCRIPTION: generate LC-3 assembly code to perform a function call,
 *                remove the arguments from the stack, and leave the
 *                return value on top of the stack
 *   INPUTS: ast -- the AST node corresponding to the function call
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_func_call (ast220_t* ast)
{
    switch (ast->fnum) {
        case  AST220_PRINTF: gen_io(ast,"PRINTF");    break;
        case  AST220_RAND:   gen_rand(ast);      break;
        case  AST220_SCANF:  gen_io(ast,"SCANF ");     break;
        case  AST220_SRAND:  gen_rand(ast);      break;
        default: fputs("BAD EXPRESSION TYPE\n", stderr);   break;
    }
}


/*
 * gen_get_address
 *   DESCRIPTION: generate LC-3 assembly code to push the address of
 *                a variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to the variable reference
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_get_address (ast220_t* ast)
{
    /*get the variable address in R3 (the fixed variable address register)*/
    /*and push that onto the stack*/
    variable_functions(ast->left);
    printf("\tSTR R3,R6,#0\n");
}

/*
 * gen_op_assign
 *   DESCRIPTION: generate LC-3 assembly code to perform an assignment,
 *                leaving the value assigned on the stack (assignments
 *                are also expressions,with value equal to that of the
 *                value assigned)
 *   INPUTS: ast -- the AST node corresponding to the assignment
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_assign (ast220_t* ast)
{
    /*generate the expressions for the variable and the expression it is */
    /*being equated to, and store the expression into the variable*/
    /*and leave it on top of the stack*/
    gen_expression(ast->right);
    variable_functions(ast->left);
    printf("\tLDR R1,R6,#1\n\tADD R6,R6,#1\n\tSTR R1,R6,#0\n\tSTR R1,R3,#0\n");
}

/*
 * gen_op_pre_incr
 *   DESCRIPTION: generate LC-3 assembly code to for a pre-increment
 *                expression, which increments a variable and pushes
 *                the new value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to pre-increment
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_pre_incr (ast220_t* ast)
{
    /*push the variable onto the stack, add 1, store it back, push onto stack*/
    gen_expression(ast->left);
    printf("\tLDR R1,R3,#0\n\tADD R1,R1,#1\n\tSTR R1,R3,#0\n\tSTR R1,R6,#0\n");
}

/*
 * gen_op_pre_decr
 *   DESCRIPTION: generate LC-3 assembly code to for a pre-decrement
 *                expression,which decrements a variable and pushes
 *                the new value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to pre-decrement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_pre_decr (ast220_t* ast)
{
    /*push the variable onto the stack, subtract 1, store it, push onto stack*/
    gen_expression(ast->left);
    printf("\tLDR R1,R6,#0\n\tADD R1,R1,#-1\n\tSTR R1,R3,#0\n\tSTR R1,R6,#0\n");
}

/*
 * gen_op_post_incr
 *   DESCRIPTION: generate LC-3 assembly code to for a post-increment
 *                expression, which increments a variable and pushes
 *                the original value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to post-increment
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_post_incr (ast220_t* ast)
{
    /*push the variable onto the stack, add 1, then store it back*/
    gen_expression(ast->left);
    printf("\tLDR R1,R6,#0\n\tADD R1,R1,#1\n\tSTR R1,R3,#0\n");
}

/*
 * gen_op_post_decr
 *   DESCRIPTION: generate LC-3 assembly code to for a post-decrement
 *                expression, which decrements a variable and pushes
 *                the original value of the variable onto the stack
 *   INPUTS: ast -- the AST node corresponding to post-decrement
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_post_decr (ast220_t* ast)
{
    /*push the variable onto the stack, subtract 1, then store it back*/
    gen_expression(ast->left);
    printf("\tLDR R1,R6,#0\n\tADD R1,R1,#-1\n\tSTR R1,R3,#0\n");
}

/*
 * gen_op_add
 *   DESCRIPTION: generate LC-3 assembly code to calculate the sum of two
 *                expressions, leaving the sum on the stack
 *   INPUTS: ast -- the AST node corresponding to the add operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_add (ast220_t* ast)
{
    /*Left is first, right is second*/
    gen_expression(ast->right);
    gen_expression(ast->left);
    /*add the expressions, pop everything, push result onto the stack*/
    printf("\tLDR R1,R6,#0\n\tLDR R0,R6,#1\n\tADD R0,R1,R0\n");
    printf("\tADD R6,R6,#1\n\tSTR R0,R6,#0\n");
}

/*
 * gen_op_sub
 *   DESCRIPTION: generate LC-3 assembly code to calculate the difference
 *                of two expressions,leaving the difference on the stack
 *   INPUTS: ast -- the AST node corresponding to the subtraction operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_sub (ast220_t* ast)
{
    /*Left is first, right is second*/
    gen_expression(ast->right);
    gen_expression(ast->left);
    /*subtract the expressions, pop everything, push the result*/
    printf("\tLDR R1,R6,#1\n\tNOT R1,R1\n\tADD R1,R1,#1\n");
    printf("\tLDR R0,R6,#0\n\tADD R0,R1,R0\n\tADD R6,R6,#1\n\tSTR R0,R6,#0\n");
}

static void
gen_operations(ast220_t *ast, char func_name[])
{
    /*handles multiplication, division, and modulo*/
    ece220_label_t *skip = label_create();
    ece220_label_t *mod_label = label_create();
    /*generate expressions for the arguments*/
    gen_expression(ast->right);
    gen_expression(ast->left);
    /*load them, pop them off, branch to the operation*/
    printf("\tLDR R1,R6,#1\n\tLDR R0,R6,#0\n\tADD R6,R6,#2\n");
    printf("\tLD R3, %s\n\tJSRR R3\n\tBRnzp %s\n%s\n\t.FILL %s\n%s\n",
    label_value(mod_label), label_value(skip), label_value(mod_label),
    func_name, label_value(skip));
    /*push the result onto the stack*/
    printf("\tADD R6,R6,#-1\n\tSTR R0,R6,#0\n");
}

/*
 * gen_op_mult
 *   DESCRIPTION: generate LC-3 assembly code to calculate the product
 *                of two expressions (using the MULTIPLY subroutine in
 *                the LC-3 library), leaving the product on the stack
 *   INPUTS: ast -- the AST node corresponding to the multiplication operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_mult (ast220_t* ast)
{
    gen_operations(ast,"MULTIPLY");
}

/*
 * gen_op_div
 *   DESCRIPTION: generate LC-3 assembly code to calculate the quotient
 *                of two expressions (using the DIVIDE subroutine in
 *                the LC-3 library), leaving the quotient on the stack
 *   INPUTS: ast -- the AST node corresponding to the division operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_div (ast220_t* ast)
{
    gen_operations(ast, "DIVIDE");
}

/*
 * gen_op_mod
 *   DESCRIPTION: generate LC-3 assembly code to calculate the modulus
 *                of one expression relative to a second expression (using
 *                the MODULUS subroutine in the LC-3 library), leaving
 *                the result on the stack
 *   INPUTS: ast -- the AST node corresponding to the division operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_mod (ast220_t* ast)
{
    gen_operations(ast,"MODULUS");
}

/*
 * gen_op_negate
 *   DESCRIPTION: generate LC-3 assembly code to negate the value of an
 *                expression, leaving the result on the stack
 *   INPUTS: ast -- the AST node corresponding to the negation operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_negate (ast220_t* ast)
{
    /*again, the assumption is that the top holds the value to be negated*/
    gen_expression(ast->left);
    printf("\tLDR R1,R6,#0\n\tNOT R1,R1\n\tADD R1,R1,#1\n\tSTR R1,R6,#0\n");
}

/* Produces an output given a logical operator and it's input(s)
 * Leaves the result on the stack
 * supports not, and and or operators (xor etc are not supported)
 * called by different functions with a different logic character depending on
 * the operator type.
 */
static void
gen_op_logic(ast220_t *ast, char logic)
{
    /*all the logical operators have a left child, generate expression for it*/
    gen_expression(ast->left);
    /*create a whole bunch of labels, create branch types*/
    ece220_label_t *lb1 = label_create();
    ece220_label_t *lb2 = label_create();
    ece220_label_t *lb3 = label_create();
    ece220_label_t *lb4 = label_create();
    ece220_label_t *lb5 = label_create();
    ece220_label_t *lb6 = label_create();
    ece220_label_t *store_1 = label_create();
    ece220_label_t *store_2 = label_create();
    br_type_t np = BR_NP;
    br_type_t z = BR_Z;
    /*Not. Doesn't have a right child. Simply evaluate and store*/
    if(logic == 'N')
    {
        /*We dont need to save the original value on the stack*/
        printf("\tLDR R1,R6,#0\n\tBRz %s\n\tADD R1,R1,#-1\n\tBRnzp %s\n",
        label_value(lb1),label_value(lb2));
        /*simply add one (or subtract one based on the branch) and store*/
        printf("%s\n\tADD R1,R1,#1\n",label_value(lb1));
        printf("%s\n\tSTR R1,R6,#0\n",label_value(lb2));
    }
    else if(logic == 'R')
    {
        /*load the first expression from the stack*/
        printf("\tLDR R1,R6,#0\n");
        /*shortcutting*/
        gen_long_branch(np,lb3);
        /*gen expression for the second part*/
        gen_expression(ast->right);
        /*load it, then branch to appropriate label*/
        printf("\tLDR R1,R6,#0\n\tBRz %s\n",label_value(lb4));
        printf("%s\n\tAND R1,R1,#0\n\tADD R1,R1,#1\n\tBRnzp %s\n",
        label_value(lb3),label_value(store_1));
        printf("%s\n\tADD R6,R6,#1\n\tAND R1,R1,#0\n%s\n",
        label_value(lb4),label_value(store_1));
        printf("\tSTR R1,R6,#0\n");
    }
    else if(logic == 'A')
    {
        /*load the first expression*/
        printf("\tLDR R1,R6,#0\n");
        /*shortcutting*/
        gen_long_branch(z,lb6);
        gen_expression(ast->right);
        /*if this code executes, that means there were 2 args. pop one*/
        /*branch according to the logic*/
        printf("\tLDR R1,R6,#0\n\tADD R6,R6,#1\n\t\nADD R1,R1,#0\n\tBRz %s\n",
        label_value(lb6));
        printf("%s\n\tAND R1,R1,#0\n\tADD R1,R1,#1\n\tBRnzp %s\n",
        label_value(lb5),label_value(store_2));
        printf("%s\n\tAND R1,R1,#0\n%s\n\tSTR R1,R6,#0\n",
        label_value(lb6),label_value(store_2));
    }
}

/*
 * gen_op_log_not
 *   DESCRIPTION: generate LC-3 assembly code to perform a logical NOT
 *                operation on an expression, leaving the result (0 or 1)
 *                on the stack
 *   INPUTS: ast -- the AST node corresponding to the logical NOT operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_log_not (ast220_t* ast)
{
    gen_op_logic(ast,'N');
}

/*
 * gen_op_log_or
 *   DESCRIPTION: generate LC-3 assembly code to perform a logical OR
 *                operation on two expressions, leaving the result (0 or 1)
 *                on the stack; the code generated must perform proper
 *                shortcutting, i.e., if the first expression is true
 *                the second is not evaluated (the code is not executed)
 *   INPUTS: ast -- the AST node corresponding to the logical OR operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_log_or (ast220_t* ast)
{
    gen_op_logic(ast,'R');
}

/*
 * gen_op_log_and
 *   DESCRIPTION: generate LC-3 assembly code to perform a logical AND
 *                operation on two expressions, leaving the result (0 or 1)
 *                on the stack; the code generated must perform proper
 *                shortcutting, i.e., if the first expression is false
 *                the second is not evaluated (the code is not executed)
 *   INPUTS: ast -- the AST node corresponding to the logical AND operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_log_and (ast220_t* ast)
{
    gen_op_logic(ast,'A');
}

/*
 * gen_comparison
 *   DESCRIPTION: generate LC-3 assembly code for a comparison operator,
 *                leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the comparison
 *           false_cond -- a string representation of the condition codes
 *                         for which the comparison is false (as calculated
 *                         by subtracting the second expression from the
 *                         first)
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 *   KNOWN BUGS: ignores 2's complement overflow in making the comparison
 */
static void
gen_comparison (ast220_t* ast, const char* false_cond)
{
    ece220_label_t* false_label;

    false_label = label_create ();
    gen_expression (ast->left);
    gen_expression (ast->right);
    printf ("\tLDR R1,R6,#0\n\tLDR R0,R6,#1\n\tADD R6,R6,#2\n");
    printf ("\tAND R2,R2,#0\n\tNOT R1,R1\n\tADD R1,R1,#1\n\tADD R0,R0,R1\n");
    printf ("\tBR%s %s\n\tADD R2,R2,#1\n", false_cond,
	    label_value (false_label));
    printf ("%s\n", label_value (false_label));
    printf ("\tADD R6,R6,#-1\n\tSTR R2,R6,#0\n");
}

/*
 * gen_op_cmp_ne
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is not equal to the value of a second
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the inequality operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_cmp_ne (ast220_t* ast)
{
    gen_comparison (ast, "z");
}

/*
 * gen_op_cmp_less
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is less than the value of a second
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the less-than operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_cmp_less (ast220_t* ast)
{
    gen_comparison (ast, "zp");
}

/*
 * gen_op_cmp_le
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is less than or equal to the value
 *                of a second expression, leaving the result (0 or 1) on
 *                the stack
 *   INPUTS: ast -- the AST node corresponding to the less-or-equal-to
 *                  operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_cmp_le (ast220_t* ast)
{
    gen_comparison (ast, "p");
}

/*
 * gen_op_cmp_eq
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is equal to the value of a second
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the equality operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_cmp_eq (ast220_t* ast)
{
    gen_comparison (ast, "np");
}

/*
 * gen_op_cmp_ge
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is greater than or equal to the value
 *                of a second expression, leaving the result (0 or 1) on
 *                the stack
 *   INPUTS: ast -- the AST node corresponding to the greater-or-equal-to
 *                  operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_cmp_ge (ast220_t* ast)
{
    gen_comparison (ast, "n");
}

/*
 * gen_op_cmp_greater
 *   DESCRIPTION: generate LC-3 assembly code to compare whether the value
 *                of one expression is greater than the value of a second
 *                expression, leaving the result (0 or 1) on the stack
 *   INPUTS: ast -- the AST node corresponding to the greater-than operation
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: prints LC-3 instructions
 */
static void
gen_op_cmp_greater (ast220_t* ast)
{
    gen_comparison (ast, "nz");
}
