


void integer_to_string(int num, char *str) {
    if(num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if(num < 0) {
        *str = '-';
        str++;
        num = -num;
    }
    char *ptr = str;

    while(num) {
        *ptr = (num%10+'0');
        num = num/10;
        ptr++;
    }
    ptr--;

    // reverse the buffer
    while(str < ptr) {
        char temp = *str;
        *str = *ptr;
        *ptr = temp;
        str++;
        ptr--;
    }
}