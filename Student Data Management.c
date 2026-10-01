#include "student.h"
static int c=1;
int main()
{
        SLL *headptr=0;
        char op;
        FILE *fp=fopen("student.dat","r");
        if(fp!=0)
        {
                SLL **ptr=&headptr;
                SLL *new,*last;
                while(1)
                {
                        new=malloc(sizeof(SLL));
                        if(fscanf(fp,"%d %s %f",&new->rollno,new->name,&new->percentage)==-1)
                                break;
                        c++;
                        new->next=0;
                        if(*ptr==0)
                                *ptr=new;
                        else
                        {
                                last=*ptr;
                                while(last->next)
                                        last=last->next;
                                last->next=new;
                        }
                }
                printf("\033[31;3m\nStudent records copied from file...\n\033[0m");
        }
        while(1)
        {
                printf("\n******** STUDENT RECORD MENU ********\n\na/A : Add new record\nd/D : Delete a record\ns/S : Show the list\nm/M : Modify a record\nv/V : Save records\ne/E : Exit\nt/T : Sort the list\nl/L : Delete all the records\nr/R : Reverse the list\n\nEnter your choice : ");
                scanf(" %c",&op);
                printf("\n");
                switch(op)
                {
                        case 'a':
                        case 'A':
                                stud_add(&headptr);
                                break;
                        case 's':
                        case 'S':
                                stud_show(headptr);
                                break;
                        case 'm':
                        case 'M':
                                stud_mod(headptr);
                                break;
                        case 'd':
                        case 'D':
                                stud_del(&headptr);
                                break;
                        case 'l':
                        case 'L':
                                del_all(&headptr);
                                break;
                        case 'v':
                        case 'V':
                                stud_save(headptr);
                                break;
                        case 't':
                        case 'T':
                                stud_sort(headptr);
                                break;
                        case 'r':
                        case 'R':
                                rev_list(&headptr);
                                break;
                        case 'e':
                        case 'E':
                                {
                                        char op;
                                        printf("S/s : Save and exit\nE/e : Exit without saving\n\nEnter your choice : ");
                                        scanf(" %c",&op);
                                        switch(op)
                                        {
                                                case 's':
                                                case 'S':
                                                        stud_save(headptr);
                                                        break;
                                                case 'e':
                                                case 'E':
                                                        return 0;
                                        }
                                }
                                return 0;
                }
        }
}

// *********************** saving in a file ***************************

void stud_save(SLL *ptr)
{
        FILE *fp=fopen("student.dat","w");
        while(ptr)
        {
                fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->percentage);
                ptr=ptr->next;
        }
        printf("Records Saved Successfully in a File...\n");
        fclose(fp);
}

// *********************** adding a record ****************************

void stud_add(SLL **ptr)   // Adding at last
{
        SLL *new,*last;
        new=malloc(sizeof(SLL));
        printf("Enter name and percentage : ");
        new->rollno = c++;
o:
        scanf("%s %f",new->name,&new->percentage);
        if(new->percentage<0 || new->percentage>100)
        {
                printf("\nPercentage should be in between 0 to 100...\n\nEnter name and percentage again : ");
                goto o;
        }
        new->next=0;
        if(*ptr==0)
                *ptr=new;
        else
        {
                last=*ptr;
                while(last->next)
                        last=last->next;
                last->next=new;
        }
}// ************************** show records *****************************

void stud_show(SLL *ptr)
{
        if(ptr==0)
        {
                printf("\033[31mNo student records Available..\n\033[0m");
                return ;
        }
        printf("-------------------------------------\nRollno.   Name    Percentage\n-------------------------------------\n");
        while(ptr)
        {
                printf("%d    %s   %f\n",ptr->rollno,ptr->name,ptr->percentage);
                ptr=ptr->next;
        }
}

// ************************ delete a record *****************************

void stud_del(SLL **ptr)
{
        if(*ptr==0)
        {
                printf("\033[31;3mNo records found...\n\033[0m");
                return ;
        }
        char op;
        SLL *del=*ptr,*prev;
        printf("R/r : Enter roll number to delete\nN/n : Enter name to delete\n\nEnter your choice: ");
        scanf(" %c",&op);
        switch(op)
        {
                case 'r':
                case 'R':
l:
                        {
                                int roll=0;
                                printf("\nEnter rollno to delete...\n");
                                scanf("%d",&roll);
                                while(del)
                                {
                                        if(roll==del->rollno)
                                        {
                                                if(*ptr==del)
                                                        *ptr=del->next;
                                                else
                                                        prev->next=del->next;
                                                free(del);
                                                printf("\nRecord Deleted Successfully...\n");
                                                return ;
                                        }
                                        prev=del;
                                        del=del->next;
                                }
                                printf("\nRollno Not found..\n");
                        }
                        break;

                case 'n':
                case 'N':
                        {
                                SLL *after;
                                char name[20];
                                int co=0;
                                printf("Enter name to delete : ");
                                scanf("%s",name);
                                while(del)
                                {
                                        if(strcmp(name,del->name)==0)
                                        {
                                                after=del->next;
                                                while(after)
                                                {
                                                        if(strcmp(del->name,after->name)==0)
                                                        {
                                                                co++;
                                                                if(co==1)
                                                                {
                                                                        printf("\nName Present More Than One Time..\n\n");
                                                                        printf("%d %s %f\n",del->rollno,del->name,del->percentage);
                                                                }
                                                                printf("%d %s %f\n",after->rollno,after->name,after->percentage);
                                                        }
                                                        after=after->next;
                                                }
                                                if(co>0)
                                                        goto l;
                                                if(*ptr==del)
                                                        *ptr=del->next;
                                                else
                                                        prev->next=del->next;
                                                free(del);
                                                printf("\nRecord Deleted Successfully...\n");
                                                return ;
                                        }
                                        prev=del;
                                        del=del->next;
                                        after=del->next;
                                }
                                printf("\nName Not Found..\n");
                        }
                        break;
        }
}
//*************************** DELETE ALL RECORDS *****************************

void del_all(SLL **ptr)
{
        if(*ptr==0)
        {
                printf("\nNo Records Found..\n");
                return ;
        }
        SLL *del=*ptr;
        while(del)
        {
                *ptr=del->next;
                free(del);
                del=*ptr;
        }
        printf("All Records Deleted Successfully...\n");
}//*********************** Sorting the list ****************************************

void stud_sort(SLL *ptr)
{
        if(ptr==0)
        {
                printf("No Records Found..\n");
                return ;
        }
        char op;
        int co,i,j;
        SLL *p1=ptr,*p2,t;
        co=countNode(ptr);
        printf("N/n : Sort with name\nP/p : Sort with percentage\n\nEnter your choice : ");
        scanf(" %c",&op);
        switch(op)
        {
                case 'n':
                case 'N':
                        {
                                for(i=0;i<co-1;i++)
                                {
                                        p2=p1->next;
                                        for(j=1+i;j<co;j++)
                                        {
                                                if(strcmp(p1->name,p2->name)>0)
                                                {
                                                        strcpy(t.name,p1->name);
                                                        t.percentage=p1->percentage;

                                                        strcpy(p1->name,p2->name);
                                                        p1->percentage=p2->percentage;

                                                        strcpy(p2->name,t.name);
                                                        p2->percentage=t.percentage;
                                                }
                                                p2=p2->next;
                                        }
                                        p1=p1->next;
                                }
                                printf("\nSorting Completed According to Name..\n");
                        }
                        break;
                case 'p':
                case 'P':
                        {
                                for(i=0;i<co-1;i++)
                                {
                                        p2=p1->next;
                                        for(j=1+i;j<co;j++)
                                        {
                                                if(p1->percentage < p2->percentage)
                                                {
                                                        strcpy(t.name,p1->name);
                                                        t.percentage=p1->percentage;

                                                        strcpy(p1->name,p2->name);
                                                        p1->percentage=p2->percentage;

                                                        strcpy(p2->name,t.name);
                                                        p2->percentage=t.percentage;
                                                }
                                                p2=p2->next;
                                        }
                                        p1=p1->next;
                                }
                                printf("\nSorting Completed According to Percentage..\n");

                        }
                        break;
        }
}
// ******************************** Reversing the list *********************************

void rev_list(SLL **ptr)
{
        if(*ptr==0)
        {
                printf("No Records Found...\n");
                return ;
        }
        int co=0,i;
        co=countNode(*ptr);
        if(co>1)
        {
                SLL **a,*t=*ptr;
                a=malloc(sizeof(SLL *)*co);
                for(i=0;i<co;i++)
                {
                        a[i]=t;
                        t=t->next;
                }
                for(i=co-1;i>0;i--)
                        a[i]->next=a[i-1];
                a[0]->next=0;
                *ptr=a[co-1];
        }
        printf("List has Been Reversed Successfully...\n");
}

//****************************** Count Nodes ********************************

int countNode(SLL *ptr)
{
        int count=0;
        while(ptr)
        {
                count++;
                ptr=ptr->next;
        }
        return count;
}
//*************************** Modifying a record *********************************

void stud_mod(SLL *ptr)
{
        if(ptr==0)
        {
                printf("No Records Found...\n");
                return ;
        }
        char op;
        printf("Enter which record to search for modification\n\nR/r : Search by roll number\nN/n : Search by name\nP/p : Search by percentage\n\nEnter Your Choice : ");
        scanf(" %c",&op);
        switch(op)
        {
                case 'r':
                case 'R':
n:
                        {
                                int roll;
                                printf("\nEnter Rollno : ");
                                scanf("%d",&roll);
                                while(ptr)
                                {
                                        if(roll==ptr->rollno)
                                        {
                                                printf("%d %s %f\n\n",ptr->rollno,ptr->name,ptr->percentage);
                                                printf("Enter name and percentage to Modify : ");
                                                scanf("%s %f",ptr->name,&ptr->percentage);
                                                printf("\nModified Successfully..\n");
                                                return ;
                                        }
                                        ptr=ptr->next;
                                }
                                printf("\033[31m\nInvalid Rollno...\n\033[0m");
                        }
                        break;
                case 'n':
                case 'N':
                        {
                                int co=0;
                                char name[20];
                                printf("\nEnter name : ");
                                scanf("%s",name);
                                SLL *after;
                                while(ptr)
                                {
                                        if(strcmp(name,ptr->name)==0)
                                        {
                                                after=ptr->next;
                                                while(after)
                                                {
                                                        if(strcmp(ptr->name,after->name)==0)
                                                        {
                                                                co++;
                                                                if(co==1)
                                                                {
                                                                        printf("\nMore than One Records Found..\n");
                                                                        printf("\n%d %s %f\n",ptr->rollno,ptr->name,ptr->percentage);
                                                                }
                                                                printf("%d %s %f\n",after->rollno,after->name,after->percentage);
                                                        }
                                                        after=after->next;
                                                }
                                                if(co>0)
                                                        goto n;
                                                printf("\n%d %s %f\n",ptr->rollno,ptr->name,ptr->percentage);
                                                printf("\nEnter name and percentage to Modify : ");
                                                scanf("%s %f",ptr->name,&ptr->percentage);
                                                printf("\nModified Successfully..\n");
                                                return;
                                        }
                                        ptr=ptr->next;
                                }
                                printf("\033[31m\nInvalid Name....\n\033[0m");
                        }
                        break;
                case 'p':
                case 'P':
                        {
                                                                int co=0;
                                float p;
                                printf("\nEnter percentage : ");
                                scanf("%f",&p);
                                SLL *after;
                                while(ptr)
                                {
                                        if(p==ptr->percentage)
                                        {
                                                after=ptr->next;
                                                while(after)
                                                {
                                                        if(ptr->percentage==after->percentage)
                                                        {
                                                                co++;
                                                                if(co==1)
                                                                {
                                                                        printf("\nMore than One Records Found..\n");
                                                                        printf("\n%d %s %f\n",ptr->rollno,ptr->name,ptr->percentage);
                                                                }
                                                                printf("%d %s %f\n",after->rollno,after->name,after->percentage);
                                                        }
                                                        after=after->next;
                                                }
                                                if(co>0)
                                                        goto n;
                                                printf("\n%d %s %f\n",ptr->rollno,ptr->name,ptr->percentage);
                                                printf("\nEnter name and percentage to Modify : ");
                                                scanf("%s %f",ptr->name,&ptr->percentage);
                                                printf("\nModified Successfully..\n");
                                                return;
                                        }
                                        ptr=ptr->next;
                                }
                                printf("\033[31m\nInvalid Percentage....\n\033[0m");

                        }
                        break;
}
