void swap(int *a, int *b){
    if(a != b){
        *a ^= *b;
        *b = *a ^ *b;
        *a ^= *b;
    }
}