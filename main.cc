#include <stdio.h>
#include <string.h>

#define MAX_INPUT 10000
#define MAX_WORD_LEN 100
#define MAX_DIC 1000000

namespace
{
    FILE* in;
    int occ[26];
    char word[MAX_INPUT];
    char strs[MAX_DIC][MAX_WORD_LEN];
    int raw_dat[MAX_DIC][26];
    int matches_i[MAX_DIC];
    int sn;
    int hits;
}

void input()
{
    memset(occ,0,sizeof(occ));
    memset(word,0,sizeof(word));
    memset(matches_i,0,sizeof(matches_i));
    hits=0;

    printf("What are your characters (only letters are processed)? ");
    fgets(word,MAX_INPUT,stdin);

    int len=strlen(word)-1;
    for(int i=0;i<len;++i)
    {
        char c=word[i];
        if (c>='a'&&c<='z') ++occ[c-'a'];
        else if (c>='A'&&c<='Z') ++occ[c-'A'];
    }
}

bool open_file()
{
    in=fopen("words.txt","r");

    if(in==NULL)
    {
        perror("HA HA HA ... Error opening file words.txt");
        return 1;
    }

    return 0;
}

void process_file()
{
    int n=0;
    while(fgets(strs[n],1000,in)!=NULL)
    {
        int len=strlen(strs[n]);
        for(int i=0;i<len;++i)
        {
            char c=strs[n][i];
            if (c>='a'&&c<='z') ++raw_dat[n][c-'a'];
            else if (c>='A'&&c<='Z') ++raw_dat[n][c-'A'];
        }

        ++n;
    }
    sn=n;
}

void unscramble()
{
    for(int i=0;i<sn;++i)
    {
        bool hit=true;
        for(int ii=0;ii<26;++ii)
        {
            if(raw_dat[i][ii]>occ[ii])
            {
                hit=false;
                break;
            }
        }

        if(hit)
        {
            matches_i[hits]=i;
            ++hits;
        }
    }

    printf("\n%d matches found:\n",hits);
}

void output()
{
    for(int i=0;i<hits;++i)
    {
        printf(strs[matches_i[i]]);
    }
    putchar('\n');
}

void unduplicate()
{
    for(int i=0;i<sn;++i)
    {
        for(int j=i+1;j<sn;++j)
        {
            bool dup=true;
            for(int k=0;k<26;++k)
            {
                if(raw_dat[i][k]!=raw_dat[j][k])
                {
                    dup=false;
                    break;
                }
            }

            if(dup) printf("%d %s %d %s\n",i+1,strs[i],j+1,strs[j]);
        }
    }
}

int main()
{
    if(open_file()) return 0;
    process_file();

    while(true)
    {
        input();
        unscramble();
        output();
    }

    //unduplicate();
    return 0;
}
