#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef NULL
    #define NULL 0
#endif

enum OPCode
{
    Zero = 0,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Invaild = 0x5ff7b
};

struct Statment
{
    int i;
    enum OPCode OP_Code;
    struct Statment *next;
};

//Init struct Statment element into struct Statment array to default(invaild) value.
void Init(struct Statment **input, int Len)
{
    struct Statment *input_r = *input, element;
    int i;
    for(i = 0; i < Len; i++)
    {
        element = input_r[i];
        element.i = -1;
        element.OP_Code = Invaild;
        element.next = 0;
    }
}

typedef enum _bool
{
    false = 0,
    true
} bool;

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

struct Statment *Parse(int input)
{
    char buf[64];
    sprintf(buf,"%d",input);
    char c, *p;
    int i = 0;
    struct Statment *stat = (struct Statment *)malloc(sizeof(struct Statment) * 64);
    Init(&stat, 64);
    for(p = &(buf[0]); *p != '\0'; p += sizeof(char), i++)
    {
        c = *p;
        if(isDigit(c))
        {
            stat[i].i = (int)(c - '0');
            stat[i].OP_Code = (enum OPCode)(c - '0');
            stat[i].next = &(stat[i + 1]);
        }
    }
    return stat;
}

bool CheckC(struct Statment stat)
{
    return stat.i > -1 && stat.OP_Code != Invaild && stat.next != 0;
}

struct UL
{
    int Len;
    struct Statment *stat;
};

struct UL UUL;

struct UL GetVaildItems(struct Statment *items)
{
    struct Statment item;
    struct Statment *TL;
    int i = -1;
    memset(&UUL, 0, sizeof(struct UL));
    for(item = items[0]; item.next != 0; item = *(item.next))
    {
        if(CheckC(item))
        {
            i++;
            //printf("%d\n",(int)items[i].OP_Code);
        }
    }
    if(i == -1)
    {
        return UUL;
    }
    TL = (struct Statment *)malloc(sizeof(struct Statment) * (i + 1));   
    memmove(TL, items, (i + 1) * sizeof(struct Statment));
    UUL.Len = i + 1;
    UUL.stat = (struct Statment*)malloc(sizeof(struct Statment) * UUL.Len);
    UUL.stat = TL;
    int j;
    for(j = 0; j < (i + 1); j++)
    {
        //printf("%d\n",(int)(UUL.stat[j].OP_Code));
    }
    return UUL;
}

void Swap_OP(enum OPCode *a, enum OPCode *b)
{
    enum OPCode tmp = *a;
    *b = *a;
    *a = tmp;
}

void Swap_Stat(struct Statment *a, struct Statment *b)
{
    struct Statment tmp = *a;
    (*a).i = (*b).i;
    (*a).OP_Code = (*b).OP_Code;
    //(*a).next = (*b).next;
    //(*b).next = tmp.next;
    (*b).i = tmp.i;
    (*b).OP_Code = tmp.OP_Code;
}

struct UL Revers(struct UL *input)
{
    struct Statment *stat1, *stat2, *stat3;
    stat1 = (*input).stat;
    stat2 = (struct Statment *)malloc(sizeof(struct Statment) * (*input).Len);
    stat3 = (struct Statment *)malloc(sizeof(struct Statment) * (*input).Len);
    int j, s, l = (*input).Len, t = l - 1;
    memmove(stat2, stat1, sizeof(struct Statment) * (*input).Len);
    int code = l % 2;
    switch(code)
    {
        case 0:
           s = l / 2; 
           for(j = 0; j < s; j++)
           {
                Swap_Stat(&stat2[t - j],&stat2[j]);
           }
           break;
        case 1:
           s = t / 2; 
           for(j = 0; j < s; j++)
           {
                Swap_Stat(&stat2[t - j],&stat2[j]);
           }
           break;
        default:
           break;
    }
    int i;
    for(i = 0; i < l; i++)
    {
        stat2[i].next = i + 1 == l ? 0 : &(stat2[i + 1]);
        //printf("%d-%d-%p\n",i,l - 1,stat2[i].next);
    }
    struct UL ULH;
    ULH.Len = (*input).Len;
    ULH.stat = stat2;
    free(stat3);
    stat3 = NULL;
    return ULH;
}

struct Info_KI
{
    int H;
    int number;
    int Revers;
    int *ALL;
} *m;

typedef long long LL;
LL binaryPow(LL a, LL b);

struct Info_KI *GetInfo(struct UL input)
{
    m = (struct Info_KI *)malloc(sizeof(struct Info_KI));
    m->H = input.Len;
    m->ALL = (int *)malloc(sizeof(int) * m->H);
    int i = 0;
    struct Statment *stat, stmp;
    stat = input.stat;
    for(stmp = stat[0]; stmp.next != 0; stmp = *(stmp.next))
    {
        if(i > m->H){ break; }
        m->ALL[i] = (int)(stmp.OP_Code);
        i++;
    }
    int ins = 0;
    int j, f;
    for(j = m->H - 1; j >= 0; j--)
    {
        ins += m->ALL[(m->H -1) - j] * binaryPow(10, j);
    }
    m->number = ins;
    struct UL ULK = Revers(&input);
    int *LR_ALL = (int *)malloc(sizeof(int) * ULK.Len), k = 0;
    struct Statment *R_stat, R_stmp;
    R_stat = ULK.stat;
    for(R_stmp = R_stat[0] ; k < ULK.Len ; R_stmp = (R_stmp.next == 0 ? R_stmp : *(R_stmp.next)))
    {
        if(k > ULK.Len){ break; }
        LR_ALL[k] = (int)(R_stmp.OP_Code);
        //printf("%d-%d-%d-%d\n",k,(int)(R_stmp.OP_Code),LR_ALL[k],ULK.Len);
        k++;
    }
    //printf("%d\n",(R_stat[0].next->next->next->next->next - &(R_stat[0])));
    int ins_r = 0;
    for(f = ULK.Len - 1; f >= 0; f--)
    {
        //printf("%d-%d-%d\n",f,LR_ALL[f],LR_ALL[f] * binaryPow(10 , f));
        ins_r += LR_ALL[(ULK.Len -1) - f] * binaryPow(10, f);
    }
    m->Revers = ins_r;
    //m->Revers = 5;
    ULK.Len = -1;
    free(ULK.stat);
    return m;
}

void freel(struct Info_KI *info)
{
    info->number = info->Revers = 0;
    free(info->ALL);
    info->ALL = NULL;
    info->H = 0;
    free(info);
    info = NULL;
}

struct Info_KI *L_Parse(int number)
{
    struct Statment *s_stat = Parse(number);
    struct UL ULH = GetVaildItems(s_stat);   
    struct Info_KI *info = GetInfo(ULH);
    free(s_stat);
    ULH.Len = -1;
    free(ULH.stat);
    s_stat = NULL;
    ULH.stat = NULL;
    return info;
}

int Convert_h(char *input)
{
    return atoi(input);
}

void Print(int number, struct Info_KI *info)
{
    char buf[256], buf2[64];
    sprintf(
        buf,
        "输入数字为:%d\n输入数字有%d位\n",
        number,
        info->H
    );
    sprintf(buf2,"每位为");
    strcat(buf,buf2);
    int i;
    for(i = 0; i < info->H - 1; i++)
    {
        sprintf(
            buf2,
            "%d-",
            info->ALL[i]
        );
        strcat(buf,buf2);
    }
    sprintf(buf2,"%d\n",info->ALL[info->H - 1]);
    strcat(buf,buf2);
    sprintf
    (
        buf2,
        "倒过来为%d\n",
        info->Revers
    );
    strcat(buf,buf2);
    sprintf
    (
        buf2,
        "解析后的数字为:%d\n",
        info->number
    );
    strcat(buf,buf2);
    printf("%s",buf);
}

int main(int argc, char **argv)
{
    int number_h = 197983167;
    struct Info_KI *info = L_Parse(number_h);
    Print(number_h, info);
    freel(info);
    return 0;
}

LL binaryPow_r(LL a, LL b)
{
    LL ans = 1;
    while(b > 0)
    {
        if(b & 1)
        {
            ans = ans * a;
        }
        a = a * a;
        b = b >> 1;
    }
    return ans;
}

LL binaryPow_k(LL a, LL b)
{
    if(b == 0){return 1;}
    if(b % 2 == 1)
    {
        return a * binaryPow_k(a, b - 1);
    }
    else
    {
        LL tmp = binaryPow_k(a, b / 2);
        return tmp * tmp;
    }
}

#define UseL_W 0

LL binaryPow(LL a, LL b)
{
    LL tmp;
    #if UseL_W
        tmp = binaryPow_k(a, b);
    #else
        tmp = binaryPow_r(a, b);
    #endif
    return tmp;
}

