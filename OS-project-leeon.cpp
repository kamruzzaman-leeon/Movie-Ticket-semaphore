///kamruzzaman leeon 2018-1-60-252
///MD ASHRAFUL ALAM HRIDOY	2018-1-60-174

#include <pthread.h>
#include <semaphore.h>
#include<bits/stdc++.h>

using namespace std;
sem_t m;

struct str
{
    string rating,name;
} li[100];
int li_size=0;

bool compare(str x,str y)
{
    return x.rating>y.rating;
}
void input_file()
{
    string line,x;
    ifstream myfile("in.txt");
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            getline(myfile,x);
            li[li_size].rating=x;
            li[li_size].name=line;
            li_size++;
        }
        myfile.close();
    }
    else
        cout<<"unable to open file"<<endl;
}
void *func(void *arg)
{

    sem_wait(&m);

    string str1,str2;
    cout<<"Enter word to search:"<<endl;
    fflush(stdin);
    cin>>str1;
    for(int k=0; k<li_size; k++)
    {
        fflush(stdin);
        str2=li[k].name;
        if(str2.find(str1)!=-1)
        {
            cout<<li[k].name<<'\t'<<li[k].rating<<endl;
        }
    }

    sem_post(&m);
}
int main ()
{

    input_file();
    int movie_number_in_list=15;///15 fixed for list data,where i insert 15 movie

//    cout<<"Total list of movie & rating:"<<endl;
    ///to see the list of in.txt file

//    for(int i=0; i<movie_number_in_list; i++)
//    {
//        cout<<li[i].name<<'\t'<<li[i].rating<<endl;
//    }
    ///sort fucting use for seeing the data in decreasing order
    sort(li,li+movie_number_in_list,compare);

//    cout<<"After sort"<<endl;
//    for(int i=0; i<movie_number_in_list; i++)
//    {
//        cout<<li[i].name<<'\t'<<li[i].rating<<endl;
//    }

    pthread_t tid[10];///consider 10 as users
    int i;

    if (sem_init(&m, 0, 5) == -1)
    {
        perror("Could not initialize semaphore");
        exit(2);
    }

    for (i=0; i<10; i++)
    {
        if (pthread_create(&tid[i], NULL, func, NULL) < 0)
        {
            perror("Error: thread cannot be created");
            exit(1);
        }
        pthread_join(tid[i], NULL);
    }

    exit(0);

}
