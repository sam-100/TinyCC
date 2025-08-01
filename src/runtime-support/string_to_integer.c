

int string_to_integer(char *str) {
    int num = 0;
    char *ptr = str;
    if(*ptr == '-')
        ptr++;
    while(*ptr != '\0') {
        num = num*10 + (*ptr-'0');
        ptr++;
    }
    if(*str == '-')
        num *= -1;
    return num;
}