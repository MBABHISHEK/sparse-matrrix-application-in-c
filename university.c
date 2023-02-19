#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct studentlist
{
  char name[10];
  int roll;
  int semester;
  char usn[10];
  int courses;
  struct studentlist *link;
  struct courselink *llink;
};

struct courselist
{
  char name[10];
  char code[10];
  float credit;
  int students;
  struct courselist *link;
  struct studentlink *llink;
};

struct studentlink
{
  struct studentlist *link;
  struct studentlink *slink;
};

struct courselink
{
  struct courselist *link;
  struct courselink *clink;
};

typedef struct studentlist STU;
typedef struct courselist COURSE;
typedef struct courselist *CLINK;
typedef struct studentlist *SLINK;
typedef struct courselink CLN;
typedef struct studentlink SLN;
typedef struct courselink *CLP;
typedef struct studentlink *SLP;

struct head
{
  int stu, cor;
  struct courselist *clink;
  struct studentlist *slink;
};

typedef struct head HEAD;
typedef struct head *HP;

SLINK createstudentlist()
{
  SLINK nn = (SLINK)malloc(sizeof(STU));
  if (nn == NULL)
  {
    printf("THE MEMORY IS FULL\n");
    exit(1);
  }
  nn->llink = NULL;
  nn->courses = 0;
  return nn;
}

CLINK createcourselist()
{
  CLINK nn = (CLINK)malloc(sizeof(COURSE));
  if (nn == NULL)
  {
    printf("THE MEMORY IS FULL\n");
    exit(1);
  }
  nn->students = 0;
  nn->llink = NULL;
  return nn;
}

CLP createcourselink()
{
  CLP nn = (CLP)malloc(sizeof(CLN));
  if (nn == NULL)
  {
    printf("THE MEMORY IS FULL\n");
    exit(1);
  }
  nn->link = NULL;
  return nn;
}
SLP createstudentlink()
{
  SLP nn = (SLP)malloc(sizeof(SLN));
  if (nn == NULL)
  {
    printf("THE MEMORY IS FULL\n");
    exit(1);
  }
  nn->link = NULL;
  return nn;
}

void readcourse(HP ph)
{
  int ch;
  for (;;)
  {
    printf("ENTER 1 READ TO THE COURSE DETAILS AND ENTER 0 TO STOP\n");
    scanf("%d", &ch);
    if (ch == 0)
      break;
    CLINK nn = createcourselist();
    printf("ENTER THE COURSE NAMES\n");
    scanf("%s", nn->name);
    printf("ENTER THE COURSE CODE\n");
    scanf("%s", nn->code);
    printf("ENTER THE CREDITS OF THE COURSE\n");
    scanf("%f", &nn->credit);
    nn->link = ph->clink;
    ph->clink = nn;
    ph->cor++;
  }
}

void displaycourse(HP ph)
{
  CLINK tp = ph->clink;
  int i = 1;
  printf("COURSE DETAILS: \n");
  if (ph->clink == NULL)
  {
    printf("THE LIST IS EMPTY\n");
    return;
  }
  printf("SL.NO:\t\tTITLE:\t\tCOURSE CODE:\tCOURSE CREDITS:\n");
  while (tp != NULL)
  {
    printf("%d.\t", i++);
    printf("%15s\t\t", tp->name);
    printf("%s\t\t", tp->code);
    printf("%.2f\n", tp->credit);
    tp = tp->link;
  }
}

void readstudent(HP ph)
{
  int ch;
  for (;;)
  {
    printf("ENTER 1 READ TO THE STUDENT DETAILS AND ENTER 0 TO STOP STUDENT COURSES\n");
    scanf("%d", &ch);
    if (ch == 0)
      break;
    SLINK nn = createstudentlist();
    printf("ENTER THE STUDENT NAME\n");
    scanf("%s", nn->name);
    printf("ENTER THE ROLL NUMBER\n");
    scanf("%d", &nn->roll);
    printf("ENTER THE SEMESTER\n");
    scanf("%d", &nn->semester);
    printf("ENTER THE USN\n");
    scanf("%s", nn->usn);
    nn->link = ph->slink;
    ph->slink = nn;
    ph->stu++;
  }
}

void displaystudent(HP ph)
{
  SLINK tp = ph->slink;
  int i = 1;
  printf("STUDENT DETAILS: \n");
  if (ph->slink == NULL)
  {
    printf("THE LIST IS EMPTY\n");
    return;
  }
  printf("SL.NO:\t\tNAME:\tROLL NUMBER:\t  SEMESTER:\tUSN:\n");
  while (tp != NULL)
  {
    printf("%d.\t", i++);
    printf("%15s\t\t", tp->name);
    printf("%d\t\t", tp->roll);
    printf("%d\t", tp->semester);
    printf("%s\n", tp->usn);
    tp = tp->link;
  }
}

void display(HP ph)
{
  if (ph->slink == NULL)
  {
    printf("THE LIST IS EMPTY\n");
    return;
  }

  SLINK tp = ph->slink;

  int i;
  for (i = 0; i < ph->stu; i++)
  {
    CLP sp = tp->llink;
    if (sp == NULL)
    {
      printf("STUDENT %s HAS TAKEN NO COURSES\n", tp->name);
    }
    if (sp != NULL)
      printf("COURSES TAKEN BY %s:\n", tp->name);
    int i = 0;
    while (sp != NULL)
    {
      CLINK dp = sp->link;
      printf("%d. %s\n", ++i, dp->name);
      sp = sp->clink;
    }
    tp = tp->link;
  }
}

void display1(HP ph)
{

  if (ph->clink == NULL)
  {
    printf("THE LIST IS EMPTY\n");
    return;
  }

  CLINK tp = ph->clink;

  int i;
  for (i = 0; i < ph->cor; i++)
  {
    SLP sp = tp->llink;
    if (sp == NULL)
    {
      printf("NO STUDENT HAS TAKEN THE COURSE \" %s \" \n", tp->name);
    }
    if (sp != NULL)
      printf("STUDENTS ENROLLED IN %s:\n", tp->name);
    int j = 0;
    while (sp != NULL)
    {
      SLINK dp = sp->link;
      printf("%d. %s\n", ++j, dp->name);
      sp = sp->slink;
    }
    tp = tp->link;
  }
}

void addcourse(HP ph)
{
  SLINK tp = ph->slink;
  int i = 0, ch;

  while (i < ph->stu)
  {
    printf("ENTER 1 TO READ COURSES AND 2 TO SKIP THIS STUDENT \n");
    scanf("%d", &ch);
    if (ch == 2)
    {
      tp = tp->link;
      i++;
      continue;
    }
    char name[10];
    if (tp->courses > 10)
    {
      printf("THE STUDENT HAS ALREADY REGISTERED FOR 10 COURSES");
      if (i == ph->stu - 1)
        break;
      else
      {
        tp = tp->link;
        i++;
      }
    }
    printf("ENTER THE COURSE NAMES FOR THE STUDENT %s\n", tp->name);
    scanf("%s", name);
    CLINK sp = ph->clink;
    while (sp != NULL)
    {
      if (strcmp(sp->name, name) == 0)
      {
        SLP s = createstudentlink();
        CLP c = createcourselink();
        c->clink = tp->llink; // studentlink
        s->slink = sp->llink; // courselink
        tp->llink = c;
        sp->llink = s;
        s->link = tp;
        c->link = sp;
        tp->courses++;
        break;
      }
      sp = sp->link;
    }
    if (sp == NULL)
      printf("THE COURSE NOT EXIT \n");
  }
  printf("ALL STUDENTS HAVE BEEN REGISTERED\n");
}

void addstudents(HP ph)
{
  CLINK tp = ph->clink;
  int i = 0, ch;

  while (i < ph->cor)
  {
    printf("ENTER 1 TO READ STUDENTS AND 2 TO SKIP THIS COURSE \n");
    scanf("%d", &ch);
    if (ch == 2)
    {
      tp = tp->link;
      i++;
      continue;
    }
    char name[10];
    printf("ENTER THE STUDENT NAMES FOR \" %s \" COURSE\n", tp->name);
    scanf("%s", name);
    SLINK sp = ph->slink;
    while (sp != NULL)
    {
      if (strcmp(sp->name, name) == 0)
      {
        SLP s = createstudentlink();
        CLP c = createcourselink();
        c->clink = sp->llink; // coursetlink
        s->slink = tp->llink; // studentlink
        tp->llink = s;
        sp->llink = c;
        s->link = sp;
        c->link = tp;

        break;
      }
      sp = sp->link;
    }
    if (sp == NULL)
      printf("THE COURSE NOT EXIT \n");
  }
  printf("ADDED ALL COURSES");
}
void main()
{
  HEAD head;
  head.stu = 0;
  head.cor = 0;
  head.clink = NULL;
  head.slink = NULL;
  HP hp = &head;
  int ch;
  system("cls");
  printf("\t\t*******************************************************************************************************\t\t\n");
  printf("\n\t\t\t\t\t\tWELCOME TO UNIVERSITY DATABASE\n\n");
  printf("\t\t*******************************************************************************************************\t\t\n");
  printf("\n\t\t\t\t\t\tTHE PROJECT DEVELOPED BY\n");
  printf("\n\t\t\t\t\t\t> ABHISHEK M B\n\n");
  printf("\t\t*******************************************************************************************************\t\t\n");
  printf("\t\t\tPress any key to continue...");
  system("pause");
  for (;;)
  {
    printf("ENTER THE CHOICE FOR\n1.READ COURSES\n2.READ STUDENTS\n");
    printf("3.ADD COURSES TO STUDENTS\n4.ADD STUDENTS TO COURSES\n");
    printf("5.DISPLAY STUDENT DETAILS\n");
    printf("6.DISPLAY COURSE DETAILS\n7.STUDENTWISE COURSES LIST\n");
    printf("8.COURSEWISE LIST OF STUDENTS\n0.EXIT\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      readcourse(hp);
      break;
    case 2:
      readstudent(hp);
      break;
    case 3:
      addcourse(hp);
      break;
    case 4:
      addstudents(hp);
      break;
    case 5:
      displaystudent(hp);
      break;
    case 6:
      displaycourse(hp);
      break;
    case 7:
      display(hp);
      break;
    case 8:
      display1(hp);
      break;
    case 0:
      printf("THE PROGRAM TERMINATED THANK YOU\n");
      exit(0);
    default:
      printf("ENTER THE CORRECT CHOICE\n");
    }
  }
}
