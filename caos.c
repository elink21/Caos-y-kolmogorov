#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 50000


/*Codigo propio del calculo de Kolmogorov Smirnov*/
double proEqual[SIZE];
double type[SIZE];
double phiZ[SIZE];
double diff[SIZE];
double diff2[SIZE];
double deviationTable[35][10]=
{
 {.5000, .5040, .5080, .5120, .5160, .5199, .5239, .5279, .5319, .5359},
 {.5398, .5438, .5478, .5517, .5557, .5596, .5636, .5675, .5714, .5753},
 {.5793, .5832, .5871, .5910, .5948, .5987, .6026, .6064, .6103, .6141},
 {.6179, .6217, .6255, .6293, .6331, .6368, .6406, .6443, .6480, .6517},
 {.6554, .6591, .6628, .6664, .6700, .6736, .6772, .6808, .6844, .6879},
 {.6915, .6950, .6985, .7019, .7054, .7088, .7123, .7157, .7190, .7224},
 {.7257, .7291, .7324, .7357, .7389, .7422, .7454, .7486, .7517, .7549},
 {.7580, .7611, .7642, .7673, .7704, .7734, .7764, .7794, .7823, .7852},
 {.7881, .7910, .7939, .7967, .7995, .8023, .8051, .8078, .8106, .8133},
 {.8159, .8186, .8212, .8238, .8264, .8289, .8315, .8340, .8365, .8389},
 {.8413, .8438, .8461, .8485, .8508, .8531, .8554, .8577, .8599, .8621},
 {.8643, .8665, .8686, .8708, .8729, .8749, .8770, .8790, .8810, .8830},
 {.8849, .8869, .8888, .8907, .8925, .8944, .8962, .8980, .8997, .9015},
 {.9032, .9049, .9066, .9082, .9099, .9115, .9131, .9147, .9162, .9177},
 {.9192, .9207, .9222, .9236, .9251, .9265, .9279, .9292, .9306, .9319},
 {.9332, .9345, .9357, .9370, .9382, .9394, .9406, .9418, .9429, .9441},
 {.9452, .9463, .9474, .9484, .9495, .9505, .9515, .9525, .9535, .9545},
 {.9554, .9564, .9573, .9582, .9591, .9599, .9608, .9616, .9625, .9633},
 {.9641, .9649, .9656, .9664, .9671, .9678, .9686, .9693, .9699, .9706},
 {.9713, .9719, .9726, .9732, .9738, .9744, .9750, .9756, .9761, .9767},
 {.9772, .9778, .9783, .9788, .9793, .9798, .9803, .9808, .9812, .9817},
 {.9821, .9826, .9830, .9834, .9838, .9842, .9846, .9850, .9854, .9857},
 {.9861, .9864, .9868, .9871, .9875, .9878, .9881, .9884, .9887, .9890},
 {.9893, .9896, .9898, .9901, .9904, .9906, .9909, .9911, .9913, .9916},
 {.9918, .9920, .9922, .9925, .9927, .9929, .9931, .9932, .9934, .9936},
 {.9938, .9940, .9941, .9943, .9945, .9946, .9948, .9949, .9951, .9952},
 {.9953, .9955, .9956, .9957, .9959, .9960, .9961, .9962, .9963, .9964},
 {.9965, .9966, .9967, .9968, .9969, .9970, .9971, .9972, .9973, .9974},
 {.9974, .9975, .9976, .9977, .9977, .9978, .9979, .9979, .9980, .9981},
 {.9981, .9982, .9982, .9983, .9984, .9984, .9985, .9985, .9986, .9986},
 {.9987, .9987, .9987, .9988, .9988, .9989, .9989, .9989, .9990, .9990},
 {.9990, .9991, .9991, .9991, .9992, .9992, .9992, .9992, .9993, .9993},
 {.9993, .9993, .9994, .9994, .9994, .9994, .9994, .9995, .9995, .9995},
 {.9995, .9995, .9995, .9996, .9996, .9996, .9996, .9996, .9996, .9997},
 {.9997, .9997, .9997, .9997, .9997, .9997, .9997, .9997, .9997, .9998}
};
double deviationTableForNegatives[35][10]={
    {.5000, .4960, .4920, .4880, .4840, .4801, .4761, .4721, .4681 ,.4641},
    {.4602, .4562, .4522, .4483, .4443, .4404, .4364 ,.4325 ,.4286, .4247},
    {.4207, .4168, .4129 ,.4090, .4052, .4013, .3974 ,.3936 ,.3897, .3859},
    {.3821, .3783 ,.3745 ,.3707 ,.3669 ,.3632 ,.3594 ,.3557 ,.3520 ,.3483},
    {.3446 ,.3409 ,.3372 ,.3336 ,.3300 ,.3264 ,.3228 ,.3192 ,.3156 ,.3121},
    {.3085 ,.3050 ,.3015 ,.2981 ,.2946 ,.2912 ,.2877 ,.2843 ,.2810 ,.2776},
    {.2743 ,.2709 ,.2676 ,.2643 ,.2611 ,.2578 ,.2546 ,.2514 ,.2483 ,.2451},
    {.2420, .2389, .2358 ,.2327 ,.2296 ,.2266 ,.2236 ,.2206 ,.2177 ,.2148},
    {.2119 ,.2090, .2061 ,.2033 ,.2005 ,.1977, .1949 ,.1922 ,.1894, .1867},
    {.1841, .1814 ,.1788 ,.1762, .1736 ,.1711 ,.1685 ,.1660 ,.1635 ,.1611},
    {.1587, .1562 ,.1539, .1515 ,.1492 ,.1469 ,.1446 ,.1423 ,.1401 ,.1379},
    {.1357, .1335, .1314, .1292 ,.1271, .1251 ,.1230 ,.1210 ,.1190 ,.1170},
    {.1151, .1131, .1112, .1093 ,.1075, .1056 ,.1038 ,.1020 ,.1003 ,.0985},
    {.0968, .0951 ,.0934 ,.0918 ,.0901 ,.0885 ,.0869 ,.0853 ,.0838 ,.0823},
    {.0808 ,.0793 ,.0778 ,.0764 ,.0749 ,.0735 ,.0721 ,.0708 ,.0694 ,.0681},
    {.0668 ,.0655 ,.0643 ,.0630, .0618, .0606 ,.0594 ,.0582 ,.0571 ,.0559},
    {.0548 ,.0537 ,.0526 ,.0516 ,.0505 ,.0495 ,.0485 ,.0475 ,.0465 ,.0455},
    {.0446 ,.0436, .0427, .0418 ,.0409 ,.0401 ,.0392 ,.0384 ,.0375 ,.0367},
    {.0359 ,.0351, .0344 ,.0336 ,.0329 ,.0322 ,.0314 ,.0307 ,.0301 ,.0294},
    {.0287, .0281 ,.0274 ,.0268 ,.0262 ,.0256 ,.0250 ,.0244 ,.0239 ,.0233},
    {.0228, .0222 ,.0217 ,.0212 ,.0207 ,.0202 ,.0197, .0192 ,.0188 ,.0183},
    {.0179 ,.0174 ,.0170 ,.0166 ,.0162 ,.0158 ,.0154 ,.0150 ,.0146 ,.0143},
    {.0139 ,.0136, .0132 ,.0129 ,.0125 ,.0122 ,.0119 ,.0116 ,.0113 ,.0110},
    {.0107 ,.0104 ,.0102 ,.0099, .0096, .0094 ,.0091 ,.0089 ,.0087 ,.0084},
    {.0082 ,.0080 ,.0078 ,.0075 ,.0073 ,.0071 ,.0069, .0068 ,.0066 ,.0064},
    {.0062 ,.0060 ,.0059 ,.0057 ,.0055 ,.0054 ,.0052 ,.0051 ,.0049 ,.0048},
    {.0047 ,.0045 ,.0044 ,.0043 ,.0041, .0040 ,.0039 ,.0038 ,.0037 ,.0036},
    {.0035 ,.0034 ,.0033 ,.0032 ,.0031 ,.0030 ,.0029 ,.0028 ,.0027 ,.0026},
    {.0026 ,.0025 ,.0024 ,.0023 ,.0023 ,.0022 ,.0021 ,.0021 ,.0020 ,.0019},
    {.0019 ,.0018, .0018, .0017 ,.0016 ,.0016 ,.0015 ,.0015, .0014 ,.0014},
    {.0013 ,.0013 ,.0013 ,.0012 ,.0012 ,.0011 ,.0011 ,.0011 ,.0010 ,.0010},
    {.0010 ,.0009 ,.0009, .0009 ,.0008, .0008 ,.0008 ,.0008, .0007 ,.0007},
    {.0007 ,.0007 ,.0006 ,.0006 ,.0006 ,.0006 ,.0006 ,.0005 ,.0005 ,.0005},
    {.0005, .0005 ,.0005 ,.0004 ,.0004 ,.0004 ,.0004 ,.0004 ,.0004 ,.0003},
    {.0003, .0003 ,.0003, .0003 ,.0003 ,.0003 ,.0003 ,.0003 ,.0003 ,.0002}
};

void sortArray(double a[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
            {
                float aux=a[i];
                a[i]=a[j];
                a[j]=aux;
            }
        }
    }
}

void printArray(double a[SIZE],int n)
{
    for(int i=0;i<n;i++) printf("%.4f\t",a[i]);
    printf("\n\n");
}

void typing(double a[SIZE],double b[SIZE],double avg,double deviation,int n)
{
    for(int i=0;i<n;i++)
    {
        a[i]=(b[i]-avg)/deviation;
    }
}


void makeEqual(double a[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        a[i]=((float)i+1)/n;
    }
}



double avg(double a[SIZE],int n){
    double sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=a[i];
    }
    return sum/n;
}

double deviation(double a[SIZE],double avg, int n)
{
    double sum=0;
    double dev;
    for(int i=0;i<n;i++)
    {
        sum+=pow(a[i]-avg,2);
    }
    sum/=(float)n;
    dev=sqrt(sum);
    return dev;
}

 double truncate(double n)
{
     long x = 100 * n;
     float y = (float)x / (float)100;
     return y;
}

void makePhi(double a[SIZE],double b[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        double trun=truncate(b[i]);
        trun*=100;
        int index=fabs(trun);
        int x=index%10;
        int y=index/10;
        if(b[i]>=0)
        {
            a[i]=deviationTable[y][x];
        }
        else a[i]=deviationTableForNegatives[y][x];
    }
}

void makeDiffPhi(double a[SIZE],double b[SIZE],double c[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        a[i]=b[i]-c[i];
    }
}

void makeLastDiff(double a[SIZE],double b[SIZE],double c[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            a[i]=fabs(b[i]);
        }
        else{
            a[i]=fabs(c[i-1]-b[i]);
        }
    }
}
double getMax(double a[SIZE],double b[SIZE],int n)
{
    double max=-1;
    for(int i=0;i<n;i++)
    {
        if(a[i]>max)max=a[i];
        if(b[i]>max)max=b[i];
    }
    return max;
}

void getKolmogorovEvaluation(double a[SIZE],int n)
{
    double valores[SIZE];
    for(int i=0;i<n;i++) valores[i]=a[i];
    sortArray(valores,n);
    makeEqual(proEqual,n);
    double average=avg(valores,n);
    printf("%f\n",average);
    double deviationStandard=deviation(valores,average,n);
    printf("%f\n",deviationStandard);
    typing(type,valores,average,deviationStandard,n);
    makePhi(phiZ,type,n);
    makeDiffPhi(diff,proEqual,phiZ,n);
    makeLastDiff(diff2,phiZ,proEqual,n);
    printf("Values\n");
    printArray(valores,n);
    printf("ProEqual\n");
    printArray(proEqual,n);
    printf("Typing\n");
    printArray(type,n);
    printf("PhiZ\n");
    printArray(phiZ,n);
    printf("DiffPhi\n");
    printArray(diff,n);
    printf("Diff 2\n");
    printArray(diff2,n);
    printf("Kolmogorov:%f\n\n",getMax(diff,diff2,n));
}

/*Inicio del codigo propio del generador aleatorio y el ordenamiento y graficacion*/
double x[SIZE]={0};
double y[SIZE]={0};
double z[SIZE]={0};

void sortArrays(double x[SIZE],double y[SIZE],double z[SIZE],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(z[j]<z[i])
            {
                double aux=z[j];
                z[j]=z[i];
                z[i]=aux;

                aux=x[j];
                x[j]=x[i];
                x[i]=aux;

                aux=y[j];
                y[j]=y[i];
                y[i]=aux;
            }
        }
    }
}

void writeData(double x[SIZE],double y[SIZE],double z[SIZE],int n)
{
    FILE *fp;
	fp = fopen ( "chaos.data", "w" );
	//fprintf(fp,"set isosamples 100,100\n");
    for(int i=0;i<n;i++)
    {
        fprintf(fp,"%f %f\n",x[i],y[i]);
    }
    fclose(fp);
}

struct range
{
    int li;
    int ls;
}r;

double filterChaos(double pv,double B)
{
    double a=(B*pv)-B*pow(pv,2);
    return a;
}

double myChaos(int li, int ls)
{
    double rand_range;
    rand_range=rand()%10000;
    rand_range/=10000;
    return (li+  (rand_range*(ls-li)));
}

void printArrays(double x[SIZE],double y[SIZE],double z[SIZE],int n)
{
    printf("x\t\t y\t\t f(x,y)\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%f\t%f\t%f\n",x[i],y[i],z[i]);
    }
}
double f(double x,double y)
{
    return pow(  (x*x*y)+ (3*x*y*y)+ (2*x*y)+ 1 ,-1 );
}
int main()
{
    int n;
    srand(time(NULL));
    double pv;
    //pv=rand()%10000;
    //pv/=10000;

    scanf("%d %d %d",&r.li,&r.ls,&n);

    for(int i=0;i<n;i++)
    {
        double pv=myChaos(r.li,r.ls);
        x[i]=myChaos(r.li,r.ls);
       // x[i]=filterChaos(pv,x[i])*10;
        //x[i]=filterChaos(pv,x[i]);
    }
    for(int i=0;i<n;i++)
    {
        y[i]=myChaos(r.li,r.ls);
        z[i]=f(x[i],y[i]);
    }
    sortArrays(x,y,z,n);

    //printArray(x,y,z,n);
    writeData(x,y,z,n);
    system("C:/gnuplot/bin/gnuplot.exe -p -e \"plot 'chaos.data' \"");
    system("C:/gnuplot/bin/gnuplot.exe -p -e \"splot  (( (x**2) * y )+ (3*x*(y**2))+ (2*x*y)+ 1)**-1  \"");
    getKolmogorovEvaluation(x,n);
    printArrays(x,y,z,n);
}
