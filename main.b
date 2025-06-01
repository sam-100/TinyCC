x: integer;

add: function integer (a: integer, b: integer) {
    sum: integer;
    sum = a + b;
    c: char;
    c = 'x';
    return sum;
}

main: function void () {
    a: integer;
    b: integer;

    read a;
    read b;
    
    sum: integer;
    sum = add(a, b);

    print sum;
}
