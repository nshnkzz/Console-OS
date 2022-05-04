#include "lib.h"
#include "console.h"
#include "stdint.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
    
static void cmd_get_total_memory(void)
{
    uint64_t total;
    
    total = get_total_memoryu();
    printf("Total Memory is %dMB\n", total);
}
unsigned int MyRand(unsigned int start_range,unsigned int end_range)
  {
    static unsigned int rand = 0xACE1U;

    if(start_range == end_range) {
        return start_range;
    }

    rand += 0x3AD;
    rand %= end_range;

    while(rand < start_range){
        rand = rand + end_range - start_range;
    }

    return rand;
}

static void toss(){
    int a = MyRand(0, 25); 
    if(a <= 12){
        printf("Heads\n");
    }
    else{
        printf("Tails\n");
    }
}



static void sayhii()
{
    char name[20]= { 0 };
    char ch[2] =  { 0 };
    int buffer_size =0;
    printf("Enter name: \n");
       
       while (1) {
        ch[0] = keyboard_readu();
        
        if (ch[0] == '\n' || buffer_size >= 80) {
            printf("%s", ch);
            break;
        }
        else if (ch[0] == '\b') {    
            if (buffer_size > 0) {
                buffer_size--;
                printf("%s", ch);    
            }           
        }          
        else {     
            name[buffer_size++] = ch[0]; 
            printf("%s", ch);        
        }
    }
 
    printf("hii %s ! have a great day!!\n", name);
}
static void help(){
    char commnds[4][80]={
        "help     :  description of project and list of commands",
        "sayhi    :  the os shows a greeting message",
        "toss     :  Flip a coin",
        "totalmem :  shows total memory assigned to the os",

    };
    int i=0;
    
    printf("\n TOPIC\n\t Console++ Operating system ");
    printf("\n SHORT DESCRIPTION\n\t An Operating system project developed for the partial fulfilment of B.tech degree in IIIT Bhopal.\n");
    printf("\n List of commands available to use:\n\t");
    for(i=0;i<5;i++){
        printf("\n\t%s",commnds[i]);
    }
    printf("\n");
}
static int read_cmd(char *buffer)
{
    char ch[2] = { 0 };
    int buffer_size = 0; 

    while (1) {
        ch[0] = keyboard_readu();
        
        if (ch[0] == '\n' || buffer_size >= 80) {
            printf("%s", ch);
            break;
        }
        else if (ch[0] == '\b') {    
            if (buffer_size > 0) {
                buffer_size--;
                printf("%s", ch);    
            }           
        }          
        else {     
            buffer[buffer_size++] = ch[0]; 
            printf("%s", ch);        
        }
    }

    return buffer_size;
}

static int parse_cmd(char *buffer, int buffer_size)
{
    int cmd = -1;

    if (buffer_size == 8 && (!memcmp("totalmem", buffer, 8))) {
        cmd = 0;
    }
    if (buffer_size == 5 && (!memcmp("sayhi", buffer, 5))) {
        cmd = 1;
    }
    if (buffer_size == 4 && (!memcmp("help", buffer, 4))) {
        cmd = 2;
    }
    if (buffer_size == 4 && (!memcmp("toss", buffer, 4))) {
        cmd = 3;
    }
    
    return cmd;
}

static void execute_cmd(int cmd)
{ 
    CmdFunc cmd_list[1] = {cmd_get_total_memory};
    
    if (cmd == 0) {       
        cmd_list[0]();
    }
    
    if (cmd == 1) {       
        sayhii();
    }
    if(cmd == 2) {
        help();
    }
    if(cmd == 3) {
        toss();
    }
    
}

int main(void)
{
    char buffer[80] = { "/0" };
    int buffer_size = 0;
    int cmd = 0;

    while (1) {
        printf("Console++ shell# ");
        buffer_size = read_cmd(buffer);

        if (buffer_size == 0) {
            continue;
        }
        
        cmd = parse_cmd(buffer, buffer_size);
        
        if (cmd < 0) {
            printf("Command Not Found! try help.\n");
        }
        else {
            execute_cmd(cmd);             
        }            
    }

    return 0;
}

