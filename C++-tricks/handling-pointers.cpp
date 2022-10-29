typedef int* pint;
int n=4;
pint ptr1=&n;
cout<<ptr1<<endl;// logs 0x1f3afffcc0 ( address of n)
cout<<*ptr1<<endl;// logs 4

typedef pint* ppint;
ppint ptr2=&ptr1; 
cout<<ptr2<<endl; // logs 0x1f3afffcb8 (address of ptr1)
cout<<*ptr2<<endl;// logs 0x1f3afffcc0 ( address of n)
cout<<**ptr2<<endl;// logs 4

typedef ppint* pppint;
pppint ptr3=&ptr2; 
cout<<ptr3<<endl; // logs 0x1f3afffcb0 (address of ptr2)
cout<<*ptr3<<endl;// logs 0x1f3afffcb8 ( address of ptr1)
cout<<**ptr3<<endl;// logs 0x1f3afffcc0 ( address of n)
cout<<***ptr3<<endl;// logs 4
