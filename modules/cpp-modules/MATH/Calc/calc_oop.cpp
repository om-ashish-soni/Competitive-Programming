class Calc{
public:
    static double eval(double a,double b,char op){
        double res=0.0;
        if(op=='+') res=a+b;
        else if(op=='-') res=a-b;
        else if(op=='*') res=a*b;
        else if(op=='/') res=a/b;
        
        return res;
    }
    static int modulo(int a,int b){
        return a%b;
    }
};
