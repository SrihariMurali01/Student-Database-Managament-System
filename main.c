#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student {
    char name[20], usn[20], add[100], branch[20], type[20];
    struct date {
        int dd, mm, yy;
    } dob;
    char phone[10];
    float user_fees;
    struct marks {
        int ade, math, ds, coa, kan, cpp, java;
    } marks;
    struct remarks {
        int ade, math, ds, coa, kan, cpp, java;
    } rem;
    struct att {
        int ade, math, ds, coa, kan, cpp, java;
    } att;
    int total_marks, total_att;
    struct student *lptr, *rptr;
};

typedef struct student node;

void replacechar(char *s, char c1, char c2) {
    int i = 0;
    for (i = 0; s[i]; i++) {
        if (s[i] == c1) {
            s[i] = c2;
        }
    }
}

node *getnode() {
    int i;
    int ade[6], math[6], ds[6], coa[6], kan[6], java[6], cpp[6];
    node *new1 = malloc(sizeof(node));
    printf("Enter Name, USN, Address, Branch, Phone number, Mode of Admission(CET/COMEDK/MANAGEMENT[MGMT]) (Use \'_\' for spaces):\n");
    scanf("%s%s%s%s%s%s", new1->name, new1->usn, new1->add, new1->branch, new1->phone, new1->type);
    replacechar(new1->name, '_', ' ');
    replacechar(new1->add, '_', ' ');
    printf("Enter Date of Birth: (DD-MM-YY) format\n");
    scanf("%d%d%d", &new1->dob.dd, &new1->dob.mm, &new1->dob.yy);
    printf("Enter the fees paid by the student till date: ");
    scanf("%f", &new1->user_fees);
    for (i = 0; i < 3; i++) {
        printf("Enter the marks and attendance of the subjects in the corresponding order at once: ");
        printf("INTERNALS %d\n", (i + 1));
        printf("1.ADE  2.MATH  3.DS  4.COA  5.KAN  6.C++  7.JAVA\n");
        scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &ade[i], &ade[i + 3], &math[i],
              &math[i + 3], &ds[i], &ds[i + 3], &coa[i], &coa[i + 3],
              &kan[i], &kan[i + 3], &cpp[i], &cpp[i + 3], &java[i],
              &java[i + 3]);
    }
    new1->marks.ade = (ade[0] + ade[1] + ade[2]) / 3;
    new1->att.ade = (ade[3] + ade[4] + ade[5]) / 3;
    new1->marks.math = (math[0] + math[1] + math[2]) / 3;
    new1->att.math = (math[3] + math[4] + math[5]) / 3;
    new1->marks.ds = (ds[0] + ds[1] + ds[2]) / 3;
    new1->att.ds = (ds[3] + ds[4] + ds[5]) / 3;
    new1->marks.coa = (coa[0] + coa[1] + coa[2]) / 3;
    new1->att.coa = (coa[3] + coa[4] + coa[5]) / 3;
    new1->marks.kan = (kan[0] + kan[1] + kan[2]) / 3;
    new1->att.kan = (kan[3] + ade[4] + ade[5]) / 3;
    new1->marks.cpp = (cpp[0] + cpp[1] + cpp[2]) / 3;
    new1->att.cpp = (cpp[3] + cpp[4] + cpp[5]) / 3;
    new1->marks.java = (java[0] + java[1] + java[2]) / 3;
    new1->att.java = (java[3] + java[4] + java[5]) / 3;

    new1->total_marks =
            new1->marks.ade + new1->marks.math + new1->marks.ds + new1->marks.coa + new1->marks.kan + new1->marks.cpp +
            new1->marks.java;
    new1->total_att = new1->att.ade + new1->att.math + new1->att.ds + new1->att.coa + new1->att.kan + new1->att.cpp +
                      new1->att.java;

    new1->rem.ade = new1->rem.math = new1->rem.ds = new1->rem.coa = new1->rem.kan = new1->rem.cpp = new1->rem.java = -1;

    new1->lptr = NULL;
    new1->rptr = NULL;
    return new1;
}

node *start = NULL;


// Function to insert a new node in the DLL
void insert(node *new1) {
    node *temp = start;
    if (start == NULL) {
        start = new1;
        return;
    }
    while (temp->rptr != NULL && strcmp(new1->usn, temp->usn) > 0)
        temp = temp->rptr;
    if (temp->rptr == NULL) {
        if (strcmp(new1->usn, temp->usn) > 0) {
            temp->rptr = new1;
            new1->lptr = temp;
        } else if (temp->lptr == NULL) {
            new1->rptr = start;
            start = new1;
        } else {
            new1->rptr = temp;
            new1->lptr = temp->lptr;
            (temp->lptr)->rptr = new1;
            temp->lptr = new1;
        }
    } else if (temp->lptr == NULL) {
        new1->rptr = start;
        start = new1;
    } else {
        new1->rptr = temp;
        new1->lptr = temp->lptr;
        (temp->lptr)->rptr = new1;
        temp->lptr = new1;
    }
}

void print() {
    node *temp = start;
    int i = 1;
    char x[20];
    if (temp == NULL) {
        printf("-------------- NO RECORDS EXIST --------------\n");
        return;
    }

    while (temp != NULL) {
        printf("\nSl. no: %d\n", i);
        printf("NAME: %s\n", temp->name);
        printf("USN: %s\n", temp->usn);
        printf("BRANCH: %s\n", temp->branch);
        temp = temp->rptr;
        i++;
    }

    printf("\nEnter the USN of the student for a detailed description: (Enter 0 to skip)\n");
    scanf("%s", x);
    temp = start;
    if (strcmp(x, "0") == 0) {
        return;
    }
    while (temp != NULL) {

        if (strcmp(temp->usn, x) == 0) {

            printf("\nName: %s\n", temp->name);
            printf("USN: %s\n", temp->usn);
            printf("Address: %s\n", temp->add);
            printf("Branch: %s\n", temp->branch);
            printf("Phone no. :%s\n", temp->phone);
            printf("Date of Birth: %d - %d - %d\n", temp->dob.dd, temp->dob.mm, temp->dob.yy);
            printf("Type of Admission: %s\n", temp->type);
            printf("Fees Paid: Rs. %.3f", temp->user_fees);
            printf("\n****************************************\n");
            printf("\nMARKS DETAILS: \n\n");
            printf("Analog and Digital Electronics (ADE): %d\n", temp->marks.ade);
            printf("Data Structures and Applications (DSA): %d\n", temp->marks.ds);
            printf("Mathematics (MAT): %d\n", temp->marks.math);
            printf("Computer Organisation and Architecture (COA): %d\n", temp->marks.coa);
            printf("Kannada (KAN): %d\n", temp->marks.kan);
            printf("C++ Programming (CPP): %d\n", temp->marks.cpp);
            printf("Object Oriented Programming with Java (JAVA): %d\n\n", temp->marks.java);
            printf("\n****************************************\n");
            printf("\nTOTAL ATTENDANCE OF ALL SUBJECTS: %d\n", temp->total_att);
            printf("TOTAL MARKS OF ALL SUBJECTS: %d\n", temp->total_marks);
            printf("\n****************************************\n");
            printf("\nPass - Fail Details:\n\n");

            printf("Subject: ADE\n");
            if (temp->rem.ade == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.ade == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }

            printf("Subject: MATH\n");
            if (temp->rem.math == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.math == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }

            printf("Subject: DSA\n");
            if (temp->rem.ds == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.ds == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }

            printf("Subject: COA\n");
            if (temp->rem.coa == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.coa == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }

            printf("Subject: KAN\n");
            if (temp->rem.kan == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.kan == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }

            printf("Subject: CPP\n");
            if (temp->rem.cpp == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.cpp == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }

            printf("Subject: JAVA\n");
            if (temp->rem.java == -1) {
                printf("Automated P/F function has not yet been implemented for this subject...\n");
            } else {
                if (temp->rem.java == 0) {
                    printf("FAIL\n");
                } else {
                    printf("PASS\n");
                }
            }
            return;
        }
        temp = temp->rptr;
    }
    printf("No Student Entries found\n\n");
}

void categorize(int lr, int hr, int sub) {

    if (start == NULL) {
        printf("\n-------------- NO RECORDS EXIST --------------\n\n");
        return;
    }
    node *temp = start;
    printf("\n------------------ STUDENTS UNDER GIVEN CRITERIA --------------\n");
    switch (sub) {
        case 1:
            while (temp != NULL) {
                if (temp->marks.ade >= lr && temp->marks.ade <= hr) {
                    printf("%s -> %d", temp->name, temp->marks.ade);
                }
                temp = temp->rptr;
            }
            break;
        case 2:
            while (temp != NULL) {
                if (temp->marks.math >= lr && temp->marks.math <= hr) {
                    printf("\n%s -> %d\n", temp->name, temp->marks.math);
                }
                temp = temp->rptr;
            }
            break;
        case 3:
            while (temp != NULL) {
                if (temp->marks.ds >= lr && temp->marks.ds <= hr) {
                    printf("%s -> %d\n", temp->name, temp->marks.ds);
                }
                temp = temp->rptr;
            }
            break;
        case 4:
            while (temp != NULL) {
                if (temp->marks.coa >= lr && temp->marks.coa <= hr) {
                    printf("%s -> %d\n", temp->name, temp->marks.coa);
                }
                temp = temp->rptr;
            }
            break;
        case 5:
            while (temp != NULL) {
                if (temp->marks.kan >= lr && temp->marks.kan <= hr) {
                    printf("%s -> %d\n", temp->name, temp->marks.kan);
                }
                temp = temp->rptr;
            }
            break;
        case 6:
            while (temp != NULL) {
                if (temp->marks.cpp >= lr && temp->marks.cpp <= hr) {
                    printf("%s -> %d\n", temp->name, temp->marks.cpp);
                }
                temp = temp->rptr;
            }
            break;
        case 7:
            while (temp != NULL) {
                if (temp->marks.java >= lr && temp->marks.java <= hr) {
                    printf("%s -> %d\n", temp->name, temp->marks.java);
                }
                temp = temp->rptr;
            }
            break;
        default:
            printf("\n\nInvalid subject code entered!\n\n");
    }
}

void pass_fail(int sub, int min) {
    int p = 0, f = 0;

    if (start == NULL) {
        printf("\n-------------- NO RECORDS EXIST --------------\n\n");
        return;
    }
    node *temp = start;
    printf("\n------------------ STUDENTS CATEGORIZED --------------\n");

    switch (sub) {
        case 1:
            printf("\nSubject Chosen: ADE\n");
            while (temp != NULL) {
                if (temp->marks.ade < min) {
                    temp->rem.ade = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    p++;
                    temp->rem.ade = 1;
                }
                temp = temp->rptr;
            }
            break;
        case 2:
            printf("\nSubject Chosen: MATH\n");
            while (temp != NULL) {
                if (temp->marks.math < min) {
                    temp->rem.math = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    p++;
                    temp->rem.math = 1;
                }
                temp = temp->rptr;
            }
            break;
        case 3:
            printf("\nSubject Chosen: DS\n");
            while (temp != NULL) {

                if (temp->marks.ds < min) {
                    temp->rem.ds = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    temp->rem.ds = 1;
                    p++;
                }
                temp = temp->rptr;
            }
            break;
        case 4:
            printf("\nSubject Chosen: COA\n");
            while (temp != NULL) {

                if (temp->marks.coa < min) {
                    temp->rem.coa = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    temp->rem.coa = 1;
                    p++;
                }
                temp = temp->rptr;
            }
            break;
        case 5:
            printf("\nSubject Chosen: KAN\n");
            while (temp != NULL) {

                if (temp->marks.kan < min) {
                    temp->rem.kan = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    temp->rem.kan = 1;
                    p++;
                }
                temp = temp->rptr;
            }
            break;
        case 6:
            printf("\nSubject Chosen: CPP\n");
            while (temp != NULL) {

                if (temp->marks.cpp < min) {
                    temp->rem.cpp = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    temp->rem.cpp = 1;
                    p++;
                }
                temp = temp->rptr;
            }
            break;
        case 7:
            printf("\nSubject Chosen: JAVA\n");
            while (temp != NULL) {

                if (temp->marks.java < min) {
                    temp->rem.java = 0;
                    f++;
                    printf("%s: FAIL\n", temp->usn);
                } else {
                    printf("%s: PASS\n", temp->usn);
                    temp->rem.java = 1;
                    p++;
                }
                temp = temp->rptr;
            }
            break;
        default:
            printf("\n\nInvalid subject code entered!\n\n");
    }
    printf("\nNo. of students passed: %d\nNo. of students failed: %d\n", p, f);
}

void fees_due(int cet, int comedk, int mgmt) {
    int y = 0, n = 0;
    int bal = 0;
    if (start == NULL) {
        printf("\n-------------- NO RECORDS EXIST --------------\n\n");
        return;
    }
    node *temp = start;
    printf("\n------------------ STUDENTS BALANCE FEES LIST --------------\n");

    while (temp != NULL) {


        if (strcmp(temp->type, "cet") == 0) {
            bal = cet - temp->user_fees;
        }
        if (strcmp(temp->type, "comedk") == 0) {
            bal = comedk - temp->user_fees;
        }
        if (strcmp(temp->type, "mgmt") == 0) {
            bal = mgmt - temp->user_fees;
        }
        if (bal > 0) {
            printf("%s: Rs. %d\n", temp->name, bal);
            y++;
        } else {
            printf("%s: No dues\n", temp->name);
            n++;
        }
        temp = temp->rptr;
    }
    printf("\nNo. of students paid: %d\nNo. of students not paid: %d\n", n, y);
}

void att_list(int sub, int min) {
    int bal = 0;
    int y = 0, n = 0;
    int min_att = (min * 0.85);
    if (start == NULL) {
        printf("\n-------------- NO RECORDS EXIST --------------\n\n");
        return;
    }
    node *temp = start;
    printf("\n------------------ STUDENTS ATTENDANCE LIST (Shortage only) --------------\n");
    switch (sub) {
        case 1:
            while (temp != NULL) {
                bal = min_att - temp->att.ade;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        case 2:
            while (temp != NULL) {
                bal = min_att - temp->att.math;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        case 3:
            while (temp != NULL) {
                bal = min_att - temp->att.ds;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        case 4:
            while (temp != NULL) {
                bal = min_att - temp->att.coa;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        case 5:
            while (temp != NULL) {
                bal = min_att - temp->att.kan;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        case 6:
            while (temp != NULL) {
                bal = min_att - temp->att.cpp;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        case 7:
            while (temp != NULL) {
                bal = min_att - temp->att.java;
                if (bal > 0) {
                    printf("%s\n", temp->name);
                    y++;
                } else
                    n++;
                temp = temp->rptr;
            }
            break;
        default:
            printf("\n\nInvalid subject code entered!\n\n");
    }
    printf("\nNo. of students with shortage: %d\nNo. of students without shortage: %d\n", y, n);
}

void retest(int sub, int min) {

    int retest_count = 0;
    float avg = 0, sum = 0;
    int flag = 0, i;
    if (start == NULL) {
        printf("\n-------------- NO RECORDS EXIST --------------\n\n");
        return;
    }
    node *temp = start;
    printf("\n------------------ STUDENTS RETEST LIST --------------\n");
    switch (sub) {
        case 1:
            while (temp != NULL) {
                if (temp->rem.ade == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.ade + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        case 2:
            while (temp != NULL) {
                if (temp->rem.math == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.math + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        case 3:
            while (temp != NULL) {
                if (temp->rem.ds == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.ds + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        case 4:
            while (temp != NULL) {
                if (temp->rem.coa == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.coa + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        case 5:
            while (temp != NULL) {
                if (temp->rem.kan == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.kan + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        case 6:
            while (temp != NULL) {
                if (temp->rem.cpp == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.cpp + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        case 7:
            while (temp != NULL) {
                if (temp->rem.java == 1) {
                    printf("%s -> NO RETEST REQUIRED\n", temp->name);
                } else {
                    avg += temp->marks.java + min + 7;
                    avg = avg / 2;
                    if (avg >= min) {
                        retest_count = 1;
                    } else {
                        avg += min + 7;
                        avg = avg / 2;
                        if (avg >= min) {
                            retest_count = 2;
                        } else {
                            retest_count = -1;
                        }
                    }
                    if (retest_count != -1)
                        printf("%s  -> %d retests\n", temp->name, retest_count);
                    else
                        printf("%s -> HAVE TO RETAKE CURRENT SEMESTER\n", temp->name);
                }
                temp = temp->rptr;
            }
            break;
        default:
            printf("\n\nInvalid subject code entered!\n\n");
    }
}

void edit() {
    node *temp = start;
    int i = 1;
    char x[20];
    if (temp == NULL) {
        printf("-------------- NO RECORDS EXIST --------------\n");
        return;
    }

    printf("\nEnter the USN of the student for a detailed description: \n");
    scanf("%s", x);
    temp = start;
    while (temp != NULL) {

        if (strcmp(temp->usn, x) == 0) {

            printf("Enter the corresponding field number to edit:\n\n");
            printf("\n1.Name\n");
            printf("2.USN\n");
            printf("3.Address\n");
            printf("4.Branch: \n");
            printf("5.Phone no.\n");
            printf("6.Date of Birth\n");
            printf("7.Type of Admission\n");
            printf("8.Fees Paid (Used for updating paid fees)\n");
            printf("9.Exit\n");
            int ch;
            scanf("%d", &ch);
            switch (ch) {
                case 1:
                    printf("Enter new Name: \n");
                    scanf("%s", temp->name);
                    replacechar(temp->name, '_', ' ');
                    return;
                    break;
                case 2:
                    printf("Enter new USN: \n");
                    scanf("%s", temp->usn);
                    return;
                    break;
                case 3:
                    printf("Enter new Address: \n");
                    scanf("%s", temp->add);
                    replacechar(temp->add, '_', ' ');
                    return;
                    break;
                case 4:
                    printf("Enter new Branch: \n");
                    scanf("%s", temp->branch);
                    return;
                    break;
                case 5:
                    printf("Enter new Phone Number: \n");
                    scanf("%s", temp->phone);
                    return;
                    break;
                case 6:
                    printf("Enter correct DOB (\'dd mm yy\' format): \n");
                    scanf("%d%d%d", &temp->dob.dd, &temp->dob.mm, &temp->dob.yy);
                    return;
                    break;
                case 7:
                    printf("Enter correct type of admission: \n");
                    scanf("%s", temp->type);
                    return;
                    break;
                case 8:
                    printf("Enter Updated Fees paid by the student: \n");
                    scanf("%f", &temp->user_fees);
                    return;
                    break;
                case 9:
                    return;
                default:
                    printf("Wrong Choice, Enter again!\n");
            }
        }
        temp = temp->rptr;
        printf("No Student Entries found\n\n");
    }
}

void deleteNode(char usn[]) {
    node *temp = start;

    if (start == NULL) {
        printf("-------------- NO RECORDS EXIST --------------\n");
        return;
    }
    if (start->rptr == NULL) {
        if (strcmp(temp->usn, usn) == 0) {
            printf("Deleted Student Entry:\n Name: %s\n USN: %s\n\n", temp->name, temp->usn);
            free(temp);
            start = NULL;
        } else
            printf("Student Entry Not Found!\n");
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->usn, usn) == 0)
            break;
        temp = temp->rptr;
    }
    if (temp->rptr == NULL) {
        (temp->lptr)->rptr = NULL;
        printf("Deleted Student Entry:\n Name: %s\n USN: %s\n\n", temp->name, temp->usn);
        free(temp);
        return;
    }
    if (temp == NULL) {
        printf("Student Entry Not Found!\n");
        return;
    }
    (temp->rptr)->lptr = temp->lptr;
    (temp->lptr)->rptr = temp->rptr;
    printf("Deleted Student Entry:\n Name: %s\n USN: %s\n\n", temp->name, temp->usn);
    free(temp);
}

void loadList() {
    node *new1 = malloc(sizeof(node));
    FILE *fp = fopen("linked_list.bin", "rb");
    if (!fp) {
        printf("\nNote: Empty Data file, the program is being run for the 1st time!!\n");
    } else {
        while (fread(new1, sizeof(node), 1, fp)) {
            new1->lptr = new1->rptr = NULL;
            insert(new1);
            new1 = malloc(sizeof(node));
        }
    }
}

void storeList() {
    FILE *fp = fopen("linked_list.bin", "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    node *temp = start;
    while (temp != NULL) {
        fwrite(temp, sizeof(node), 1, fp);
        temp = temp->rptr;
    }
    fclose(fp);
}


int main() {
    int ch, i;
    int n, lr, hr, sub, min, cet, comedk, mgmt;
    int men;
    node *new1 = malloc(sizeof(node));

    loadList();
    printf("\n\n------------------------------------------ STUDENT DATABASE MANAGEMENT SYSTEM ----------------------------------------- \n\n");

    while (1) {
        printf("\n==================================================");
        printf("\n=================== MAIN MENU ====================\n");
        printf("\n1.Enter 'n' student details.\n2.Edit Student Record\n3.Print all student details\n4.Delete a student entry from the records"
               "\n5.Categorize students according to given range."
               "\n6.Automatic Pass/Fail Allocation\n7.Listing FEE Dues\n8.Automatic Retest Checker\n9.Attendance shortage list curation\n10.Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the number of student entries: ");
                scanf("%d", &n);

                for (i = 0; i < n; i++) {
                    printf("\n%d.\n", i + 1);
                    new1 = getnode();
                    insert(new1);
                }
                break;
            case 2:
                printf("\nNote: Use this function to edit student personal data only. Academic data edition is not supported.\n");
                edit();
                break;
            case 3:
                printf("\n\n---------------- STUDENT LIST --------------------\n\n");
                print();
                break;
            case 4:
                printf("Enter the USN of the student to be deleted from the list: (Enter 0 to skip)\n");
                char usn[20];
                scanf("%s", usn);
                if (strcmp(usn, "0") == 0) {
                    break;
                }
                deleteNode(usn);
                break;
            case 5:
                printf("Enter the subject(corresponding entry) and marks range(Lower and Higher) for categorization: \n");
                printf("Subjects: 1.ADE, 2.Math, 3.DS, 4.COA, 5.KAN, 6.C++, 7.Java\n");
                scanf("%d%d%d", &sub, &lr, &hr);
                categorize(lr, hr, sub);
                break;
            case 6:
                printf("Enter the subject(corresponding entry) and the minimum marks for remarks (P or F): \n");
                printf("Subjects: 1.ADE, 2.Math, 3.DS, 4.COA, 5.KAN, 6.C++, 7.Java\n");
                scanf("%d%d", &sub, &min);
                pass_fail(sub, min);
                break;
            case 7:
                printf("Enter the total fees for CET, COMEDK and Management:\n");
                scanf("%d%d%d", &cet, &comedk, &mgmt);
                fees_due(cet, comedk, mgmt);
                break;
            case 8:
                printf("Enter the subject(corresponding entry) and the minimum marks for passing: "
                       "\n\n*Note: This prediction is not guaranteed results. "
                       "It works on mere arithmetic assumptions that the failed candidate "
                       "\npasses the next two retests with an extra of 5-10 marks from the minimum passing marks\n\n"
                       "*This prediction works only after running the 4th option on \"Automatic PASS/FAIL Allocation\" function."
                       "If you have not run the 4th option for your subject, please enter 9 to re-enter the menu, or press any other number: \n");
                scanf("%d", &men);
                if (men == 9) {
                    break;
                }
                printf("Subjects: 1.ADE, 2.Math, 3.DS, 4.COA, 5.KAN, 6.C++, 7.Java\n");
                scanf("%d%d", &sub, &min);
                retest(sub, min);
                break;
            case 9:
                printf("Enter the subject(corresponding entry) and the total days of classes taken: \n");
                printf("Subjects: 1.ADE, 2.Math, 3.DS, 4.COA, 5.KAN, 6.C++, 7.Java\n");
                scanf("%d%d", &sub, &min);
                att_list(sub, min);
                break;
            case 10:
                printf("\n==================================================\n");
                printf("\nThank you for running our program! We are currently storing the data on the drive!\n");
                printf("\nWe are, as always, open to all of your suggestions!!\n");
                printf("Please do feel free to give us your valuable feedback!\n");
                printf("\nThis project is Open-Sourced.\n");
                printf("\nThank you once again! Have a great Day!\n\n");
                printf("Done by: \n");
                printf("Srihari M, S R Abhiram Anandh and Soundarya R.\n3rd Semester - ISE C\n");
                printf("\n==================================================\n");
                storeList();
                exit(0);
            default:
                printf("\n\nINVALID CHOICE!! ENTER AGAIN!\n\n");
        }
    }
}