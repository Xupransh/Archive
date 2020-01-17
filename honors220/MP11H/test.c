int main()
{
    int another[3],pnum,lmao;
    another[0] = 1;
    another[1] = 4;
    another[2] = 1;
    pnum = 2*another[1];
    pnum = 8/(5*pnum);
    pnum = pnum + 100;
    if(!(!(another[1] <= 0) && !(another[0] != 1)) || pnum == 100){
    pnum = pnum % 31;
    }
    printf("%d\n", -(pnum));
    return pnum*another[1];
}
