#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "shell.h"
#include "../libc/string.h"

void shell(char *input){

    char int_str_convert[255];

    if (strcmp(input, "EXIT") == 0) {
        kprint("          Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if(substrCheck("SUM", input) !=-1){
        int sum_nos = sum_decode(input,4);
        int_to_ascii(sum_nos, int_str_convert);
        kprint("          ");
        kprint(int_str_convert);
    }
    else if(substrCheck("MULTIPLY", input) !=-1){
        int mul_nos = mul_decode(input,9);
        int_to_ascii(mul_nos, int_str_convert);
        kprint("          ");
        kprint(int_str_convert);
    }
    else if(substrCheck("EXPONENTIAL", input) !=-1){
        int exp_val = exponential_decode(input,11);
        int_to_ascii(exp_val, int_str_convert);
        kprint("          ");
        kprint(int_str_convert);
    }
    else if(strcmp(input,"HELP") == 0){
        kprint("==================== XXXXX ====================\n\n");
        kprint("   Hello Welcome to Lantern os kernel.\n\n");
        kprint("   HELPFUL COMMANDS.\n\n");
        kprint("   SUM : Gives Summation of provided inputs. \n     Example Syntax : SUM 1,2,3\n\n");
        kprint("   MULTIPLY : Gives Multiplication of provided inputs. \n     Example Syntax : MULTIPLY 1,2,3\n\n");
        kprint("   EXPONENTIAL : Computes Exponent of provided input. \n     Example Syntax : EXPONENTIAL 2\n\n");
        kprint("   CLRSCR : Clear the screen.\n\n");
        kprint("   EXIT : Exits the current kernel.\n\n");
        kprint("==================== XXXXX ====================");
    }
    else if (strcmp(input, "CLRSCR") == 0) {
        clear_screen();
    }
    else{    
        kprint("          Sorry The command does not exist.");
    }
    kprint("\n\nLantern > ");
}

int sum_decode(char s[], int pos){
    int str_len = strlen(s);
    char extracted_str[100] = "";
    int j = 0, i = 0;
    for (i = pos; i<str_len; i++){
        extracted_str[j] = s[i];
        j++;
    }
    extracted_str[j]='0';
    
    int extracted_str_len = strlen(extracted_str);
    int sum = 0;
    for (i = 0; i<extracted_str_len-1; i++){
        if(extracted_str[i] != ',' ){
            if((extracted_str[i+1] != ',') && (i+1 < extracted_str_len-1)){
                sum = sum + (extracted_str[i+1] - '0') + 10*(extracted_str[i] - '0');
                i++;
            }else{
                sum = sum + (extracted_str[i] - '0');
            }
        }
    }
    return sum;
}

int mul_decode(char s[], int pos){
    int str_len = strlen(s);
    char extracted_str[100] = "";
    int j = 0, i = pos;
    for (i = pos; i<str_len; i++){
        extracted_str[j] = s[i];
        j++;
    }
    extracted_str[j]= '0';
    
    int extracted_str_len = strlen(extracted_str);
    int mul = 1;
    for (i = 0; i< extracted_str_len-1; i++){
        if(extracted_str[i] != ',' ){
            if((extracted_str[i+1] != ',') && (i+1 < extracted_str_len-1)){
                mul = mul * ((extracted_str[i+1] - '0') + 10*(extracted_str[i] - '0'));
                i++;
            }else{
                mul = mul * (extracted_str[i] - '0');
            }
        }
    }
    return mul;
}

int exponential_decode(char s[], int pos){
    int inp_no = (s[pos+1] - '0');
    float sum = 1.0f; // initialize sum of series 
    int n = 10, i=0;
    for (i = n-1; i > 0; --i ) 
        sum = 1 + inp_no * sum / i; 
  
    return sum;
}