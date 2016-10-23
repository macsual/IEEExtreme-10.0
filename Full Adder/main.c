#define _GNU_SOURCE

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int b;
    char symbols[63];
    static char line1[10000003], line2[10000003], line3[10000002], sum[10000002];
    char *p;
    char *operand1;
    char *operand2;
    size_t op1len, op2len;
    int i, j;
    int symbol_sum;
    div_t divresult;
    int count;
    int difference;
    int lookup_table[256];
    
    scanf("%d %s", &b, symbols);
    
    /* consume newline left over by scanf() so that fgets() below won't misbehave */
    (void)getchar();
    
    for (i = 0; i < b; i++)
        lookup_table[symbols[i]] = i;
    
    /* use fgets() due to possible leading spaces; operand1 */
    (void)fgets_unlocked(line1, sizeof line1, stdin);
    
    /* use fgets() due to possible leading spaces; operand2 */
    (void)fgets_unlocked(line2, sizeof line2, stdin);
    
    /* ------- */
    scanf("%s", line3);
    
/* commented out because this can be skipped */
#if 0
    scanf("%*s");
#endif
    
    /* offet of 1 to skip space for alignment due to plus sign (+) in line2 */
    operand1 = line1 + 1;
    
    p = operand1;
    
    /* line1 buffer is large enough to always store newline included by fgets() */
    while (*p != '\n')
        p++;
    
    op1len = p - operand1;
    
    operand1[op1len] = '\0';
    
    /* offet of 1 to ignore trailing plus sign (+) */
    operand2 = line2 + 1;
    
    p = operand2;
    
    /* line2 buffer is large enough to always store newline included by fgets() */
    while (*p != '\n')
        p++;
    
    op2len = p - operand2;
    
    operand2[op1len] = '\0';

    /* leading space to meet alignment requirement due to plus sign */
    sum[0] = ' ';
    
    sum[op2len + 2] = '\0';
    
    divresult.quot = 0; /* carry */
    
    count = 0;
    
    i = op2len - 1;
    
    j = op1len - 1;
    
    lookup_table[32] = 0;
    
    if (op1len > op2len)
        count = op1len;
    else if (op1len < op2len)
        count = op2len;
    else    /* op1len == op2len */
        count = op1len;
    
    /* operand 1 may be shorter than operand 2 */
    while (count) {
        symbol_sum = divresult.quot + lookup_table[operand1[j]] + lookup_table[operand2[i]];
        
        divresult = div(symbol_sum, b);
        
        sum[i + 1] = symbols[divresult.rem];
        
        i--;
        j--;      
        count--;
    }
    
    printf(
        "%d %s\n"
        "%s\n"
        "%s\n"
        "%s\n"
        "%s\n",
        b, symbols, line1, line2, line3, sum);

    return 0;
}
