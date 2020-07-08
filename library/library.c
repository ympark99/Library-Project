#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Book{
    int book_id;        //도서번호
    char *book_name;    //도서명
    char *purblisher;   //출판사
    char *writer;       //저자명
    long isbn;         //ISBN
    char *local;        //소장처
    char book_rent;    //대여가능 여부
    struct _Book *next; //자기참조
}Book;

typedef struct _Client{
    int std_id;         //학번
    char *password;     //비밀번호
    char *std_name;     //학생 이름
    char *addr;         //주소
    char *ph_num;       //핸드폰 번호
    struct _Client *next;
} Client;

typedef struct _Borrow{
    int std_id;         //학번
    int bk_id;          //도서번호
    time_t rent_date;   //빌린 날짜
    time_t return_date; //반납 날짜
    struct _Borrow *next;
} Borrow;

/*-------------영민,민영-------------*/
typedef struct _client {
    int std_id; //학번
    char password[300]; //비밀번호
    char std_name[300]; //이름
    char addr[300]; //주소
    char ph_num[300];   //연락처
    struct _client* next;
}client;
/*-------------영민,민영-------------*/

/*----------------용준-----------------*/
typedef struct book {

    char bnum[8];//책번호
    char bname[100];//책이름
    char pname[100];//출판사이름
    char writer[100];//저자명
    char ISBN[15];//ISBN번호
    char own[100];//소장처
    char YN;//Y or N 대여가능여부
    struct book *next;
} book;//book.txt파일에서 책 정보 읽어오는 자기참조구조체선언
/*-----------------용준----------------*/


void login(Book *cur, Client *cl_cur, Borrow *br_cur);
int admin_login(Book *cur, Client *cl_cur, Borrow *br_cur); //로그인 함수
void book_manage(int num, Book *cur, Client *cl_cur, Borrow *br_cur);
char *get_string(char * str, int start);
Book *create_node(Book *data);
void insert_node(Book **cur, Book *new_node);
void add_node(Book **cur, Book *new_node, Book *next_node);
void delete_node(Book **cur, Book *del_node);
Book *book_regis(Book **cur);
Borrow *create_br_node(Borrow *data);
void insert_br_node(Borrow **cur, Borrow *new_node);
void delete_br_node(Borrow **cur, Borrow *del_node);
Client *create_cl_node(Client *data);
void insert_cl_node(Client **cur, Client *new_node);
void delete_cl_node(Client **cur, Client *del_node);
time_t make_time (time_t date, int *year, int *month, int *day);
void mul_time(time_t date, int  *year, int *month, int *day);

/*-------------영민-------------*/
void client_add();
void register_member();   // 회원 등록
void member_menu(int id, Borrow *br_cur, Book *bk_cur, Client *cl_cur);      // 회원 메뉴
void modify_member();   // 회원 정보 수정
void delete_member(int id, Borrow *br_cur, Client *cl_cur);  // 회원 탈퇴
void borrow_search(int id, Borrow *br_cur, Book *bk_cur);

client *client_head;
client *client_tail;

char id_login[300];   // 로그인할때 쓸 학번
char password_login[50]; // 로그인할때 쓸 비밀번호
/*-------------영민-------------*/

/*-------------민영-------------*/
void search_name(FILE *);   //이름 검색 함수
void all_client(FILE *);    //전체검색
void client_list();         //전채검색
void search_id_num(FILE *); //학번검색

/*-------------민영-------------*/

/*-------------용준-------------*/
typedef book *LINK;//struct book *형을 LINK정의.
void findbname(FILE *);//책이름검색함수
void findpname(FILE *, char *);//출판사명검색함수
void findISBN(FILE *);//ISBN검색함수
void findwriter(FILE *, char *);//작가명검색함수
void findall(FILE *);//전체검색함수
void search();//회원 로그인 후 도서검색 눌렀을때 실행
/*-------------용준-------------*/

FILE *fp,*bfp,*cfp,*dfp,*ifp;

int main (void) {

    /*-------------영민-------------*/
    client_head=(client *)malloc(sizeof(client));
    client_tail=(client *)malloc(sizeof(client));
    client_add();
    /*-------------영민-------------*/

    bfp = fopen("./borrow.txt","r+w");
    if(bfp == NULL) printf("파일없음\n");
    Borrow *br_p = (Borrow*)malloc(sizeof(Borrow));
    Borrow *br_head = (Borrow*)malloc(sizeof(Borrow));
    Borrow *br_cur = br_head;
    br_head->next = NULL;
    br_head->std_id=0;

    char *br_info = (char *)malloc(1024);
    int br_curNum=0;

    while(fgets(br_info,1024,bfp) != NULL) {    //구조체에 데이터 파싱
        br_curNum=0;
        br_p->std_id = atoi(get_string(br_info,br_curNum));
        br_curNum += 9;
        br_p->bk_id = atoi(get_string(br_info,br_curNum));
        br_curNum += strlen(get_string(br_info,br_curNum))+1;
        br_p->rent_date = atoi(get_string(br_info,br_curNum));
        br_curNum += strlen(get_string(br_info,br_curNum))+1;
        br_p->return_date = atoi(get_string(br_info,br_curNum));

        insert_br_node(&br_cur,create_br_node(br_p));
    }
    br_cur = br_head;

    cfp = fopen("./client.txt","r+w");
    if(cfp == NULL) printf("파일없음\n");
    Client *cl_p = (Client*)malloc(sizeof(Client));
    Client *cl_head = (Client*)malloc(sizeof(Client));
    Client *cl_cur = cl_head;
    cl_head->next = NULL;
    cl_head->std_id = 0;

    char *cl_info = (char *)malloc(1024);
    int cl_curNum = 0;

    while(fgets(cl_info,1024,cfp) != NULL) {
        cl_curNum = 0;
        cl_p->std_id = atoi(get_string(cl_info,cl_curNum));
        cl_curNum += 9;
        cl_p->password = get_string(cl_info,cl_curNum);
        cl_curNum += strlen(cl_p->password)+1;
        cl_p->std_name = get_string(cl_info,cl_curNum);
        cl_curNum += strlen(cl_p->std_name)+1;
        cl_p->addr = get_string(cl_info,cl_curNum);
        cl_curNum += strlen(cl_p->addr)+1;
        cl_p->ph_num = get_string(cl_info,cl_curNum);
        cl_curNum += strlen(cl_p->ph_num)+1;

        insert_cl_node(&cl_cur,create_cl_node(cl_p));
    }
    cl_cur = cl_head;


    /* 링크드리스트 */

    fp = fopen("./book.txt","r+w");
    if(fp == NULL) printf("파일 없음\n");
    Book *book_p=(Book*)malloc(sizeof(Book));

    Book *bk_head = (Book *)malloc(sizeof(Book));
    Book *cur = bk_head;
    bk_head->next = NULL;
    bk_head -> book_id = 0;

    char *info = (char *)malloc(1024);
    int curNum=0;
    while(fgets(info, 1024, fp) != NULL) {  //구조체에 데이터 파싱
        curNum=0;
        book_p->book_id = atoi(get_string(info, curNum));
        curNum += sizeof(book_p->book_id)*2;
        book_p->book_name=get_string(info,curNum);
        curNum += strlen(book_p->book_name)+1;
        book_p->purblisher=get_string(info, curNum);
        curNum += strlen(book_p->purblisher)+1;
        book_p->writer=get_string(info, curNum);
        curNum += strlen(book_p->writer)+1;
        book_p->isbn = atol(get_string(info, curNum));
        curNum += sizeof(book_p->isbn)+6;
        book_p->local=get_string(info, curNum);
        curNum += strlen(book_p->local)+1;
        char *rent=get_string(info, curNum);
        book_p->book_rent=rent[0];
        curNum += 1;

        insert_node(&cur, create_node(book_p));

    }
    cur= bk_head;

    /* 메인화면 */
    int select;
     system("clear");

    while(1) {
         system("clear");
        printf(">>도서관 서비스<<\n");
        printf("1. 회원가입\t2.로그인\t3. 프로그램종료\n");
        printf("번호를 선택하세요: ");

        scanf("%d", &select);

        if(select == 1) {
            //회원가입 함수
            /*-------------영민-------------*/
            register_member();
            /*-------------영민-------------*/
        } else if(select == 2) {
            //로그인함수
            system("clear");
            login(cur, cl_cur, br_cur);
        }



         else if(select == 3) {
            /*-------------영민-------------*/
            printf("====================================\n");
            printf("프로그램을 종료합니다\n");
            exit(1);
            /*-------------영민-------------*/
        }
    }

    fclose(fp);
    fclose(bfp);
    fclose(cfp);

    return 0;
}

void login(Book *cur, Client *cl_cur, Borrow *br_cur)
{
     while(1)
    {
        printf(">>로그인<<\n");
        printf("학번: ");
        scanf("%s", id_login);

        if (!strcmp(id_login, "admin"))
        {
            printf("비밀번호: ");
            scanf("%s", password_login);

            if (!strcmp(password_login, "lib_admin7"))
            {
                admin_login(cur, cl_cur, br_cur); //관리자용 메뉴로 이동
                break;
            }

            else
            {
                printf("비밀번호가 틀렸습니다. 다시입력하십시오.\n");
                id_login[0] = '\0';
                password_login[0] = '\0';
                continue; //로그인 화면 처음으로 이동
            }
        }

        else
        {
            client* current = (client*)malloc(sizeof(client));
            current = client_head;

            while (current != client_tail)
            {
                if (current->std_id == atoi(id_login)) //입력한 학번이 존재할 때
                {
                    printf("비밀번호: ");
                    scanf("%s", password_login);

                    if (!strcmp(current->password, password_login)) //비밀번호가 맞으면 회원용 메뉴로 이동
                    {
                        member_menu(atoi(id_login), br_cur, cur, cl_cur);
                        break;
                    }
                    else //아니면 반복문 나온후 로그인 화면 처음으로 이동
                    {
                        printf("비밀번호가 틀렸습니다. 다시 입력하세요.\n");
                        password_login[0] = '\0';
                        break;
                    }
                }
                current = current->next;
            }

            if (current == client_tail) //linked_list를 전부 확인해도 입력한 학번이 없을 때
            {
                printf("존재하지 않는 학번입니다. 다시 입력하세요.\n");
                continue; //로그인 화면으로  이동
            }

            if (!strcmp(current->password, password_login)) //회원용 메뉴를 나오면 로그인 화면종료
                break;                                  //비밀번호가 다를경우 로그인화면 으로 이동
        }
    }
}

int admin_login(Book *cur, Client *cl_cur, Borrow *br_cur) {
    system("clear");

    int num;

    printf(">> 관리자 메뉴 <<\n");
    printf("1. 도서 등록 2. 도서 삭제\n");
    printf("3. 도서 대여 4. 도서 반납\n");
    printf("5. 도서 검색 6. 회원 목록\n");
    printf("7. 로그아웃 8. 프로그램 종료\n");
    printf("번호를 선택하세요 : ");
    scanf("%d", &num);

    if(num == 1 || num == 2 || num == 3 || num == 4 || num == 5)
        book_manage(num,cur,cl_cur,br_cur);
    else if(num == 6) {
        /*------------민영----------*/
        client_list();
        //회원 목록
         admin_login(cur, cl_cur, br_cur);
    } else if (num == 7) {
        //로그아웃
        return 0;
    } else if (num == 8) {
        exit(0);
    }

    return 0;
}

void book_manage(int num, Book *cur, Client *cl_cur, Borrow *br_cur) {
    int del_num=0,rent_num=0;
     system("clear");

    switch(num) {
        case 1 :    //도서 등록 //isbn순으로 정렬
            {
                Book *tail, *corr_cur;
                Book *bk_head = cur;

                printf(">>도서 등록<<\n");
                tail = book_regis(&cur);    //마지막 번호 받아옴
                fflush(stdout);
                cur = bk_head->next;
                while (cur != NULL) {
                    if(cur->isbn > tail->isbn && cur->isbn != tail->isbn){  //기존isbn보다 tail isbn 작은거 찾기
                        corr_cur=cur;   //위치 저장
                        break;
                    }
                    if(cur->isbn == tail->isbn) {   //기존이랑 tail isbn과 같다면
                        corr_cur=cur;   //위치 저장
                        break;
                    }
                    if(cur->next ==NULL) {  //맨마지막이면
                        corr_cur=cur;
                        break;
                    }
                    cur = cur->next;
                }

                cur = bk_head;  //head값 저장
                FILE *fp = fopen("book.txt", "w");
                fflush(stdout);
                Book *last_node;    //마지막노드위치
                if(cur->next->isbn > tail->isbn){   //처음꺼
                    fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",tail->book_id, tail->book_name, tail->purblisher,
                                tail->writer, tail->isbn, tail->local, tail->book_rent);
                    add_node(&cur,create_node(tail), cur->next);
                    cur = bk_head->next->next;
                    while(cur != NULL) {
                        fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",cur->book_id, cur->book_name, cur->purblisher,
                            cur->writer, cur->isbn, cur->local, cur->book_rent);
                        cur=cur->next;
                    }
                    cur=bk_head->next;
                } else if (cur->next->isbn <= tail->isbn) { //중간이면
                    cur=bk_head->next;

                    while(cur != NULL) {    //마지막찾기
                        last_node = cur;
                        cur=cur->next;
                    }
                    cur=bk_head->next;
                    if(last_node->isbn >= tail->isbn) {
                        while(cur != NULL) {
                        fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",cur->book_id, cur->book_name, cur->purblisher,
                                cur->writer, cur->isbn, cur->local, cur->book_rent);
                        if(cur->next == corr_cur) break;
                        cur = cur->next;
                        }
                        fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",tail->book_id, tail->book_name, tail->purblisher,
                                    tail->writer, tail->isbn, tail->local, tail->book_rent);
                        Book *next_node = cur->next;
                        add_node(&cur,create_node(tail), next_node);
                        cur = cur->next;
                        while(cur != NULL) {
                            fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",cur->book_id, cur->book_name, cur->purblisher,
                                    cur->writer, cur->isbn, cur->local, cur->book_rent);
                            cur = cur->next;
                        }
                        cur = bk_head;
                    }
                }
                while(cur != NULL) {    //마지막꺼찾기
                    last_node = cur;
                    cur=cur->next;
                }
                cur=bk_head->next;
                if(last_node->isbn < tail->isbn) {
                    while(cur != NULL) {
                        fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",cur->book_id, cur->book_name, cur->purblisher,
                            cur->writer, cur->isbn, cur->local, cur->book_rent);
                        if(cur->next == NULL) break;
                        cur=cur->next;
                    }
                    fprintf(fp, "%d|%s|%s|%s|%ld|%s|%c\n",tail->book_id, tail->book_name, tail->purblisher,
                                tail->writer, tail->isbn, tail->local, tail->book_rent);
                    insert_node(&cur,create_node(tail));

                    cur = bk_head;
                }


                fclose(fp);
            break;
            }
        case 2 :    // 도서 삭제
        {
            printf(">>도서 삭제<<\n");
            printf("1. 도서명 검색 2. ISBN 검색\n");
            printf("\n\n검색 번호를 입력하세요 : ");
            scanf("%d",&del_num);
            Book *head=cur; //head위치 저장포인터
            Book *corr_cur=cur; //null이 아님을 피하기위해 초기화
            Book *del_node; //지울 노드 전번째 노드위치 포인터
            int null_check = 0, del_id = 0; //도서이름이 있는지 확인변수, 삭제할 도서번호
            if(del_num == 1) {
                char b_name[100]="";    //도서 이름입력변수

                printf("도서명을 입력하세요 : ");
                getchar();
                scanf("%[^\n]", b_name);
                fflush(stdout);
                cur=head->next;
                while(cur != NULL) {    //찾는 도서이름이 없는지 확인
                    if(!strcmp(cur->book_name, b_name)) //도서이름이 있으면
                        null_check ++;
                    cur=cur->next;
                }
                if(null_check == 0) corr_cur = NULL;    //도서이름이 없으면
                cur = head->next;
                if(corr_cur != NULL) {  //찾는 도서이름이 있으면
                    printf("도서 번호 :");
                    while(cur != NULL) {
                        if(!strcmp(cur->book_name,b_name)){
                            printf(" %d(삭제 가능 여부 : %c)",cur->book_id, cur->book_rent);
                            corr_cur = cur; // 도서위치저장
                        }
                        cur=cur->next;
                    }
                    printf("\n도서명 : %s\n",corr_cur->book_name);
                    printf("출판사 : %s\n", corr_cur->purblisher);
                    printf("저자명 : %s\n", corr_cur->writer);
                    printf("ISBN : %ld\n", corr_cur->isbn);
                    printf("소장처 : %s\n", corr_cur->local);
                    printf("\n삭제할 도서의 번호를 입력하세요 : ");
                    scanf("%d", &del_id);
                    cur=head->next; //cur위치는 다시 처음으로

                    int check=0,success=0;
                    while(cur != NULL) {
                        if(!strcmp(cur->book_name,b_name) && cur->book_id == del_id) {
                            check++;
                            corr_cur=cur;   //지울노드에 현재커서위치 넘겨주기
                            if(cur->book_rent=='N') {
                                printf("이 도서는 삭제할 수 없습니다.\n");
                            } else if (cur->book_rent=='Y') {
                                success = 1;
                                printf("도서를 삭제했습니다.\n");
                            }
                        }
                        cur = cur->next;
                    }
                    cur = head;
                    while(cur != NULL) {
                        if(cur->next == corr_cur) {
                            del_node = cur; //지울노드 전노드 위치 넘겨주기
                        }
                        cur=cur->next;
                    }
                    cur=head; //cur위치 다시 처음으로
                    FILE *dfp;
                    if(success==1) {
                        delete_node(&del_node,corr_cur);
                        dfp = fopen("./book.txt","w");
                        while(cur!=NULL) {
                            if(cur->book_id != 0) {
                                fprintf(dfp, "%d|%s|%s|%s|%ld|%s|%c\n", cur->book_id, cur->book_name, cur->purblisher,
                               cur->writer, cur->isbn, cur->local, cur->book_rent);
                            }
                        cur=cur->next;
                        }
                        cur = head->next;
                    } else {    //예외 처리
                        dfp = fopen("./book.txt","r");
                    }
                    fclose(dfp);
                    if(check == 0)
                        printf("도서 번호가 잘못되었습니다.\n");
                } else if (corr_cur == NULL) {
                    printf("찾으시는 도서이름이 없습니다.\n");
                }
            } else if (del_num == 2) {
                long b_isbn;
                Book *del_node; //지울 노드 전번째 노드위치 포인터
                printf("ISBN을 입력하세요 : ");
                scanf("%ld", &b_isbn);

                while(cur != NULL) {
                    if(cur->isbn == b_isbn) //찾는 도서 isbn이 있으면
                        null_check ++;
                    cur=cur->next;
                }
                if(null_check == 0) corr_cur = NULL;    //도서이름이 없으면
                cur = head->next;
                if(corr_cur != NULL) {  //있을때
                    printf("도서 번호 :");
                    while(cur != NULL) {
                        if(cur->isbn == b_isbn) {
                            printf(" %d(삭제 가능 여부: %c)", cur->book_id, cur->book_rent);
                            corr_cur = cur; //도서위치저장
                        }
                        cur=cur->next;
                    }
                    printf("\n도서명 : %s\n",corr_cur->book_name);
                    printf("출판사 : %s\n", corr_cur->purblisher);
                    printf("저자명 : %s\n", corr_cur->writer);
                    printf("ISBN : %ld\n", corr_cur->isbn);
                    printf("소장처 : %s\n", corr_cur->local);
                    printf("\n삭제할 도서의 번호를 입력하세요 : ");
                    scanf("%d", &del_id);
                    cur=head->next;   //cur위치는 다시 처음으로
                    int check=0,success=0;
                    while(cur != NULL) {
                        if(cur->isbn == b_isbn && cur->book_id == del_id) {
                            check++;
                            corr_cur=cur;   //지울노드에 현재커서위치 넘겨주기
                            if(cur->book_rent=='N') {
                                printf("이 도서는 삭제할 수 없습니다.\n");
                            } else if (cur->book_rent=='Y') {
                                success = 1;
                                printf("도서를 삭제했습니다.\n");
                                break;
                            }
                        }
                        cur = cur->next;
                    }
                    cur=head;
                    while(cur != NULL) {
                        if(cur->next == corr_cur) {
                            del_node = cur; //지울노드 전노드 위치 넘겨주기
                        }
                        cur=cur->next;
                    }
                    cur=head; //cur위치 다시 처음으로
                    FILE *dfp;
                    if(success==1) {
                        delete_node(&del_node,corr_cur);
                        dfp = fopen("./book.txt","w");
                        while(cur!=NULL) {
                            if(cur->book_id!=0) {
                                fprintf(dfp, "%d|%s|%s|%s|%ld|%s|%c\n", cur->book_id, cur->book_name, cur->purblisher,
                                    cur->writer, cur->isbn, cur->local, cur->book_rent);
                            }
                            cur=cur->next;
                        }
                    } else {    //예외 처리
                        dfp = fopen("./book.txt","r");
                    }
                    fclose(dfp);
                    if(check == 0)
                        printf("도서 번호가 잘못되었습니다.\n");
                } else if(corr_cur == NULL) {   //없을때
                    printf("찾으시는 도서ISBN이 없습니다.\n");
                }
            } else {    //1,2번 아닌거 입력했을때
                printf("번호를 잘못 입력하셨습니다.\n");
            }
            break;
        }
        case 3 :
            {
                //도서 대여
                printf(">>도서 대여<<\n");
                printf("1. 도서명 검색 2. ISBN 검색\n");
                printf("\n\n검색 번호를 입력하세요 : ");
                scanf("%d", &rent_num);
                Borrow *br_head=br_cur;
                Book *bk_head=cur;
                Client *cl_head=cl_cur;
                Book *cor_cur=cur;  //null이 아님을 피하기 위해 초기화
                int n_check=0;
                if(rent_num == 1){
                    char b_name[100]="",rent='\0';
                    int s_id=0,b_id=0;

                    getchar();
                    printf("도서명을 입력하세요 : ");
                    scanf("%[^\n]", b_name);

                    cur= bk_head->next;
                    while(cur != NULL) {
                        if(!strcmp(cur->book_name, b_name)) //도서이름이 있으면
                            n_check ++;
                        cur=cur->next;
                    }
                    if(n_check == 0) cor_cur = NULL;    //도서이름이 없으면
                    cur = bk_head->next;
                    if(cor_cur != NULL) {  //찾는 도서이름이 있으면
                        printf("도서 번호 :");
                        while(cur != NULL) {
                            if(!strcmp(cur->book_name,b_name)){
                                printf(" %d(대여 가능 여부 : %c)",cur->book_id, cur->book_rent);
                                cor_cur = cur; // 도서위치저장
                            }
                            cur=cur->next;
                        }
                        printf("\n도서명 : %s\n",cor_cur->book_name);
                        printf("출판사 : %s\n", cor_cur->purblisher);
                        printf("저자명 : %s\n", cor_cur->writer);
                        printf("ISBN : %ld\n", cor_cur->isbn);
                        printf("소장처 : %s\n", cor_cur->local);
                        printf("\n학번을 입력하세요 : ");
                        scanf("%d", &s_id);
                        cur=bk_head->next;
                        int id_check=0,id_suc=0;
                        while(cl_cur != NULL) {
                            if(s_id == cl_cur->std_id)  //같으면
                                id_check = 1;
                            cl_cur=cl_cur->next;
                        }
                        cl_cur = cl_head->next;//처음으로
                        if(id_check == 0) {
                            printf("학번이 잘못되었습니다.\n");
                            break;
                        }
                        printf("도서번호를 입력하세요 : ");
                        scanf("%d", &b_id);
                        while(cur != NULL) {
                            if(b_id == cur->book_id) {
                                id_suc=1;
                                cor_cur = cur;  //현재위치 잡아주기
                            }
                            cur=cur->next;
                        }
                        cur = bk_head->next;
                        printf("이 도서를 대여합니까? : ");
                        getchar();
                        scanf("%c", &rent);

                        FILE *br_fp;
                        struct tm *t;
                        time_t timer;
                        char *weekday[] = {"일요일",   "월요일", "화요일", "수요일",
                                           "목요일", "금요일", "토요일"};
                        char *a_date=(char*)malloc(100);
                        char *b_date=(char*)malloc(100);
                        time(&timer);
                        t = localtime(&timer);
                        mktime(t);
                        if(id_suc==1 && rent == 'Y' && cor_cur->book_rent == 'Y') {
                            printf("도서가 대여 되었습니다.\n");
                            cor_cur->book_rent = 'N';
                            br_fp = fopen("./borrow.txt","a+w");
                            sprintf(a_date, "%d%02d%02d",t->tm_year+1900, t->tm_mon+1, t->tm_mday);
                            timer += 60*60*24*30;
                            t = localtime(&timer);
                            mktime(t);
                            if(!strcmp(weekday[t->tm_wday],"일요일")){
                                timer += 60*60*24;
                                t=localtime(&timer);
                                mktime(t);
                            }
                            sprintf(b_date, "%d%02d%02d",t->tm_year+1900, t->tm_mon+1, t->tm_mday);
                            fprintf(br_fp,"%d|%d|%s|%s\n", s_id, b_id, a_date, b_date);
                            fclose(br_fp);
                            bfp=fopen("./book.txt","wt");
                            while(cur != NULL) {
                                if(cur->book_id==cor_cur->book_id){
                                    //부분수정
                                    fprintf(bfp, "%d|%s|%s|%s|%ld|%s|%c\n", cor_cur->book_id, cor_cur->book_name,
                                            cor_cur->purblisher,cor_cur->writer, cor_cur->isbn,
                                            cor_cur->local, cor_cur->book_rent);
                                }
                                else {
                                    fprintf(bfp, "%d|%s|%s|%s|%ld|%s|%c\n", cur->book_id, cur->book_name, cur->purblisher,
                                            cur->writer, cur->isbn, cur->local, cur->book_rent);
                                }
                                cur=cur->next;
                            }
                            fclose(bfp);
                        } else if(id_suc==1 && rent == 'Y' && cor_cur->book_rent == 'N') {
                            printf("도서 대여를 실패했습니다.\n");
                        } else if (rent == 'N') {
                            printf("도서 대여를 취소합니다. \n");
                        }
                        free(a_date);
                        free(b_date);

                    } else if(cor_cur == NULL) {
                        printf("찾으시는 도서이름이 없습니다.\n");
                    }

                } else if (rent_num == 2) { //isbn검색
                    long b_isbn;
                    char rent='\0';
                    int s_id=0,b_id=0;
                    printf("ISBN을 입력하세요 : ");
                    scanf("%ld", &b_isbn);

                    while(cur != NULL) {
                        if(cur->isbn == b_isbn) //찾는 도서 isbn이 있으면
                            n_check ++;
                        cur=cur->next;
                    }
                    if(n_check == 0) cor_cur = NULL;    //도서 isbn이 없으면

                    cur = bk_head->next;
                    if(cor_cur != NULL) {  //찾는 도서isbn이 있으면
                        printf("도서 번호 :");
                        while(cur != NULL) {
                            if(cur->isbn == b_isbn) {
                                printf(" %d(대여 가능 여부 : %c)",cur->book_id, cur->book_rent);
                                cor_cur = cur; // 도서위치저장
                            }
                            cur=cur->next;
                        }
                        printf("\n도서명 : %s\n",cor_cur->book_name);
                        printf("출판사 : %s\n", cor_cur->purblisher);
                        printf("저자명 : %s\n", cor_cur->writer);
                        printf("ISBN : %ld\n", cor_cur->isbn);
                        printf("소장처 : %s\n", cor_cur->local);
                        printf("\n학번을 입력하세요 : ");
                        scanf("%d", &s_id);
                        cur=bk_head->next;
                        int id_check=0,id_suc=0;
                        while(cl_cur != NULL) {
                            if(s_id == cl_cur->std_id)  //같으면
                                id_check = 1;
                            cl_cur=cl_cur->next;
                        }
                        cl_cur = cl_head->next;//처음으로
                        if(id_check == 0) {
                            printf("학번이 잘못되었습니다.\n");
                            break;
                        }
                        printf("도서번호를 입력하세요 : ");
                        scanf("%d", &b_id);
                        while(cur != NULL) {
                            if(b_id == cur->book_id) {
                                id_suc=1;
                                cor_cur = cur;  //현재위치 잡아주기
                            }
                            cur=cur->next;
                        }
                        cur = bk_head->next;
                        printf("이 도서를 대여합니까? : ");
                        getchar();
                        scanf("%c", &rent);
                        FILE *br_fp;
                        struct tm *t;
                        time_t timer;
                        char *weekday[] = {"일요일",   "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};
                        char *a_date=(char*)malloc(100);
                        char *b_date=(char*)malloc(100);
                        time(&timer);   //시간받아오는거
                        t = localtime(&timer);  //시간 나눠주는거
                        mktime(t);  //요일
                        if(id_suc==1 && rent == 'Y' && cor_cur->book_rent == 'Y') {
                            printf("도서가 대여 되었습니다.\n");
                            cor_cur->book_rent = 'N';
                            br_fp = fopen("./borrow.txt","a+w");
                            sprintf(a_date, "%d%02d%02d",t->tm_year+1900, t->tm_mon+1, t->tm_mday);
                            timer += 60*60*24*30;
                            t = localtime(&timer);
                            mktime(t);
                            if(!strcmp(weekday[t->tm_wday],"일요일")){
                                timer += 60*60*24;
                                t=localtime(&timer);
                                mktime(t);
                            }
                            sprintf(b_date, "%d%02d%02d",t->tm_year+1900, t->tm_mon+1, t->tm_mday);
                            fprintf(br_fp,"%d|%d|%s|%s\n", s_id, b_id, a_date, b_date);
                            fclose(br_fp);
                            bfp=fopen("./book.txt","wt");
                            while(cur != NULL) {
                                if(cur->book_id==cor_cur->book_id){
                                    fprintf(bfp, "%d|%s|%s|%s|%ld|%s|%c\n", cor_cur->book_id, cor_cur->book_name,
                                            cor_cur->purblisher,cor_cur->writer, cor_cur->isbn,
                                            cor_cur->local, cor_cur->book_rent);
                                }
                                else {
                                    fprintf(bfp, "%d|%s|%s|%s|%ld|%s|%c\n", cur->book_id, cur->book_name, cur->purblisher,
                                            cur->writer, cur->isbn, cur->local, cur->book_rent);
                                }
                                cur=cur->next;
                            }
                            fclose(bfp);
                        } else if(id_suc==1 && rent == 'Y' && cor_cur->book_rent == 'N') {
                            printf("도서 대여를 실패했습니다.\n");
                        } else if (rent == 'N') {
                            printf("도서 대여를 취소합니다. \n");
                        }
                        free(a_date);
                        free(b_date);

                    } else if(cor_cur == NULL) {
                        printf("찾으시는 도서가 없습니다.\n");
                    }
                } else {
                    printf("번호를 잘못 입력하셨습니다.\n");
                }
                break;
            }
        case 4 :
            {
                //도서 반납
                int s_id=0, bk_id=0, success=0;
                int year, month, day;
                Borrow *br_head=br_cur;
                Book *bk_head=cur;
                Client *cl_head=cl_cur;
                Borrow *del_node,*corr_cur;
                char rent='\0';
                printf("학번을 입력하세요 : ");
                scanf("%d", &s_id);
                struct tm* timeinfo;
                char *weekday[] = {"일요일",   "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};

                printf(">>회원의 대여 목록<<\n");
                br_cur = br_head->next;
                while(br_cur != NULL) {
                    if(br_cur->std_id == s_id) {
                        bk_id = br_cur->bk_id;
                        printf("도서번호 : %d\n", bk_id);
                        while(cur != NULL) {
                            if(cur->book_id == bk_id)
                                printf("도서명 : %s\n", cur->book_name);
                            cur=cur->next;
                        }
                        cur = bk_head->next;

                        mul_time(br_cur->rent_date, &year, &month, &day);
                        time_t baseTime = make_time(br_cur->rent_date, &year, &month, &day);

                        timeinfo = localtime(&baseTime);
                        timeinfo->tm_year = year - 1900;
                        timeinfo->tm_mon = month - 1;
                        timeinfo->tm_mday = day;
                        mktime(timeinfo);
                        printf("대여 일자 : %ld%s\n",br_cur->rent_date,weekday[timeinfo->tm_wday]);

                        mul_time(br_cur->return_date, &year, &month, &day);
                        baseTime = make_time(br_cur->return_date, &year, &month, &day);

                        timeinfo = localtime(&baseTime);
                        timeinfo->tm_year = year - 1900;
                        timeinfo->tm_mon = month - 1;
                        timeinfo->tm_mday = day;
                        mktime(timeinfo);

                        printf("반납 일자 : %ld%s\n\n",br_cur->return_date,weekday[timeinfo->tm_wday]);
                    }
                    br_cur=br_cur->next;
                }
                printf("반납할 도서번호를 입력하세요 : ");
                scanf("%d",&bk_id);
                printf("\n도서 반납처리를 할까요? : ");
                getchar();
                scanf("%c",&rent);
                corr_cur = br_head;
                br_cur=br_head->next;
                if(rent == 'Y') {
                    while (br_cur != NULL) {
                        if(br_cur->bk_id == bk_id) {
                            break;
                        }
                        corr_cur = br_cur; //지울 노드 찾기
                        br_cur = br_cur->next;
                    }
                    delete_br_node(&corr_cur, br_cur);
                } else {
                    printf("반납처리를 취소합니다. \n");
                }
                br_cur = br_head->next;
                if(rent == 'Y') {
                    FILE *fp = fopen("./borrow.txt", "wt");
                    while(br_cur != NULL) { //borrow파일 수정
                        fprintf(fp, "%d|%d|%ld|%ld\n",br_cur->std_id,br_cur->bk_id,br_cur->rent_date,br_cur->return_date);
                        br_cur = br_cur->next;
                    }
                    br_cur = br_head->next;

                    FILE *bfp = fopen("./book.txt", "wt");
                    while(cur != NULL) {    //book파일 수정
                        if(cur->book_id==bk_id){
                            cur->book_rent = rent;
                            fprintf(bfp, "%d|%s|%s|%s|%ld|%s|%c\n", cur->book_id, cur->book_name,
                                    cur->purblisher,cur->writer, cur->isbn,
                                    cur->local, cur->book_rent);
                        } else {
                            fprintf(bfp, "%d|%s|%s|%s|%ld|%s|%c\n", cur->book_id, cur->book_name, cur->purblisher,
                                    cur->writer, cur->isbn, cur->local, cur->book_rent);
                        }
                        cur=cur->next;
                    }
                    cur=bk_head->next;

                    fclose(fp);
                    fclose(bfp);
                }

                break;
            }
        case 5 :
            {search();//도서 검색
             admin_login(cur, cl_cur, br_cur);
            break;
    }}
}
/*-----------------------민영-------------------------*/
void client_list() {
    FILE *dfp = NULL;               //client 파일을 여는 파일 포인터 선언
    dfp = fopen("client.txt", "r");
    if (dfp == NULL) {
        return;
    }
    int choice;
    char name[10]; //입력받을 이름


    printf(">>검색 결과<<\n");
    printf("1.이름 검색\t 2.학번 검색\n3.전체 검색\t 4.이전 메뉴\n");
    printf("번호를 입력하세요\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        search_name(dfp);
        printf("\n\n");
        client_list();
        break;
    case 2:
        search_id_num(dfp);
        printf("\n\n");
        client_list();
        break;
    case 3: {
        all_client(dfp);
        printf("\n\n");
        client_list();
    }
            break;
    case 4:
        fclose(dfp);
        break;
    default:
        printf("1~4사이 숫자를 입력하세요");
        break;

    }
    fclose(dfp);
    return;
}

void search_name(FILE *dfp)  //이름 검색 함수
{
    char input_name[20];
    char buf[10];
    client *head = NULL;
    client *p = NULL;
    client *q = (client *)malloc(sizeof(client));

    printf("이름을 입력하세요:");
    scanf("%s", input_name);
    while (1) {
        if (fscanf(dfp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", buf, q->password, q->std_name, q->addr, q->ph_num) != 5)
        {
            printf("검색 결과 없음");
            break;
        }
        q->std_id = atoi(buf);
        if (strcmp(input_name, q->std_name) != 0)
        {

            continue;
        }
        else
        {
            printf("학번:%d\n이름:%s\n주소:%s\n전화번호:%s\n", q->std_id, q->std_name, q->addr, q->ph_num);
            break;
        }
    }
}

void search_id_num(FILE *dfp) //학번검색함수

{

    int input_id;
    char buf[10];

    client *head = NULL;
    client *q = NULL;
    client *p = NULL;
    q = (client *)malloc(sizeof(client));
    printf("학번을 입력하세요:");
    scanf("%d", &input_id);
    while (1) {

        if (fscanf(dfp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", buf, q->password, q->std_name, q->addr, q->ph_num) != 5)
        {
            printf("검색결과가 없습니다.");
            break;
        }
        q->std_id = atoi(buf);

        if (input_id == q->std_id) {

            printf("\n학번:%d\n이름:%s\n주소:%s\n전화번호:%s", q->std_id, q->std_name, q->addr, q->ph_num);

            break;
        }
    }
}



void all_client(FILE *dfp)  //전체 검색함수
{
    int count = 0;
    client *head = NULL;
    client *p = NULL;
    client *q = NULL;
    char buf[10];
    while (1) {
        q = malloc(sizeof(client));
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            if (fscanf(dfp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", buf, q->password, q->std_name, q->addr, q->ph_num) == 5)
            {
                q->std_id = atoi(buf);

                printf("학번:%d\n", q->std_id);
                printf("이름:%s\n", q->std_name);
                printf("주소:%s\n", q->addr);
                printf("전화번호:%s\n\n", q->ph_num);
            }
        }
        else {
            p = head;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = q;
            if (fscanf(dfp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", buf, q->password, q->std_name, q->addr, q->ph_num) == 5)
            {
                q->std_id = atoi(buf);
                printf("학번:%d\n", q->std_id);
                printf("이름:%s\n", q->std_name);
                printf("주소:%s\n", q->addr);
                printf("전화번호:%s\n\n", q->ph_num);

            }
            else {
                free(q);
                return;
            }
        }
    }
}
/*----------------------민영--------------------*/


time_t make_time (time_t date, int *year, int *month, int *day) {
    char* weekday[] = {"일요일",   "월요일", "화요일", "수요일",
                       "목요일", "금요일", "토요일"};

    struct tm t = {0};
    t.tm_year = *year - 1900;
    t.tm_mon = *month - 1;
    t.tm_mday = *day;

    return mktime(&t);
}
void mul_time(time_t date, int  *year, int *month, int *day) {
    *year= date / 10000 ;
    *month = (date - ((*year) * 10000)) / 100;
    *day = date % 100 ;
}

Client *create_cl_node(Client *data) {
    Client *new_node = (Client*)malloc(sizeof(Client));
    memcpy(new_node, data, sizeof(Client));
    new_node->next = NULL;
    return new_node;
}

void insert_cl_node(Client **cur, Client *new_node) {
    (*cur)->next = new_node;
    *cur = new_node;
}

void delete_cl_node(Client **cur, Client *del_node) {
    (*cur)->next = del_node->next;
    free(del_node);
}

Borrow *create_br_node(Borrow *data) {
    Borrow *new_node = (Borrow*)malloc(sizeof(Borrow));
    memcpy(new_node, data, sizeof(Borrow));
    new_node->next = NULL;
    return new_node;
}

void insert_br_node(Borrow **cur, Borrow *new_node) {
    (*cur)->next = new_node;
    *cur = new_node;
}

void delete_br_node(Borrow **cur, Borrow *del_node) {
    (*cur)->next = del_node->next;
    free(del_node);
}

Book *create_node(Book *data){
    Book *new_node = (Book*)malloc(sizeof(Book));
    memcpy(new_node, data, sizeof(Book));
    new_node->next = NULL;
    return new_node;
}

void insert_node(Book **cur, Book *new_node) {
    (*cur)->next = new_node;
    *cur = new_node;
}

void add_node(Book **cur, Book *new_node, Book *next_node) {
    (*cur)->next = new_node;
    *cur = new_node;
    (*cur) -> next = next_node;
}

void delete_node(Book **cur, Book *del_node) {
    (*cur)->next = del_node->next;
    free(del_node);
}

char *get_string(char * str, int start){
    int i = 0;
    char * temp = (char*)calloc(1024, sizeof(char));
    while(str[start] != '|' && str[start] != '\n' && str[start] != '\0'){
        temp[i] = str[start];
        i++;
        start++;
    }
    return temp;
}

Book *book_regis(Book **cur) { //책 등록
    char input[100]="";
    char *name, *purb, *writer, *local, answer;
    int last_id=0;
    long isbn;

    printf("도서명 : ");
    scanf("%s", input);
    name = (char *)malloc(strlen(input));
    strcpy(name,input);

    printf("출판사 : ");
    scanf("%s", input);
    purb = (char *)malloc(strlen(input));
    strcpy(purb,input);

    printf("저자명 : ");
    scanf("%s", input);
    writer = (char *)malloc(strlen(input));
    strcpy(writer,input);

    printf("ISBN : ");
    scanf("%ld", &isbn);

    printf("소장처 : ");
    scanf("%s", input);
    local = (char *)malloc(strlen(input));
    strcpy(local,input);

    while ((*cur) != NULL) {
        if((*cur)->book_id > last_id) {
            last_id = (*cur)->book_id;
        }
        *cur = (*cur) -> next;
    }
    last_id++;

    getchar();
    printf("\n자동 입력 사항\n\n대여가능 여부 : Y\n도서 번호 : %d\n\n저장하시겠습니까? ",last_id);
    scanf("%c", &answer);

    if(answer == 'Y') {
        Book *book_p = (Book *)malloc(sizeof(Book));

        book_p->book_id = last_id;

        book_p->book_name = (char *)malloc(strlen(name));
        strcpy(book_p->book_name, name);
        book_p->purblisher = (char *)malloc(strlen(purb));
        strcpy(book_p->purblisher,purb);

        book_p->writer = (char *)malloc(strlen(writer));
        strcpy(book_p->writer, writer);

        book_p->isbn = isbn;

        book_p->local = (char *)malloc(strlen(local));
        strcpy(book_p->local, local);

        book_p->book_rent = 'Y';

        fflush(stdout);

        return book_p;
    } else {
        printf("다시 입력하세요\n");
    }
    return NULL;
}
/*-------------용준-------------*/
void search() {//도서검색실행
    FILE *ifp = NULL;
    ifp = fopen("book.txt", "r");
    printf(">> 도서 검색<<\n1.도서명 검색 2. 출판사 검색\n3.ISBN 검색 4. 저자명 검색\n5.전체 검색 6. 이전 메뉴\n\n");
    printf("번호를 선택하세요:");
    int c;//도서검색에서 선택할 번호입력.
    scanf("%d", &c);
    while (getchar() != '\n');//scanf이후 버퍼에서 엔터('\n')지우기
    if (c == 1)
    {
        findbname(ifp);
        fclose(ifp);
        printf("\n\n");
        search();
    }
    else
        if (c == 2)
        {
            char s[100];//출판사명 입력할 배열
            printf("출판사명을 입력하세요:");
            scanf("%[^\n]", s);
            while (getchar() != '\n');
            findpname(ifp, s);
            fclose(ifp);
            printf("\n\n");
            search();
        }
        else
            if (c == 3)
            {
                findISBN(ifp);
                fclose(ifp);
                printf("\n\n");
                search();
            }
            else
                if (c == 4)
                {
                    char s[100];//작가명 입력할 배열 생성.
                    printf("작가명을 입력하세요:");
                    scanf("%[^\n]", s);
                    while (getchar() != '\n');
                    findwriter(ifp, s);//인자로파일포인터와 문자열 전달.
                                        fclose(ifp);
                    printf("\n\n");
                    search();
                }
                else
                    if (c == 5)
                    {
                        findall(ifp);
                        fclose(ifp);
                        printf("\n\n");
                        search();
                    }
                    else if (c == 6)
                    {
                        fclose(ifp);
                        return;
                    }
                    else
                    {
                        printf("잘못된 선택입니다. 1~6중에서 선택해주세요.\n");
                        fclose(ifp);
                        search();
                    }
    fclose(ifp);
    return;
}

void findbname(FILE *ifp) {
    char s[100];//도서명입력
    LINK head = NULL;
    LINK p = NULL;
    LINK q = NULL;
    LINK r = NULL;
    int n1 = 0;//대여가능여부 Y의 수
    int n2 = 0;//대여가능여부 N의 수
    printf("도서명을 입력하세요:");
    scanf("%[^\n]", s);
    while (getchar() != '\n');
    while (1) {
        q = (LINK)malloc(sizeof(book));//book.txt파일 한 줄 읽을 때마다 동적메모리 생성.
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            head->next = NULL;
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", head->bnum, head->bname, head->pname, head->writer, head->ISBN, head->own, &head->YN) != 7)
            {
                printf("검색오류입니다.\n");
                free(q);
                break;
            }
            if (!strcmp(s, head->bname))
            {
                if (head->YN == 'Y')
                    n1++;
                else
                    n2++;
                r = malloc(sizeof(book));
                r->next = NULL;
                while (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    if (!strcmp(r->ISBN, head->ISBN))//같은 도서 존재하면 YN(대여가능여부)검사 후 대여가능(Y)이면 n1에 1더하고 대여불가능(N)이면 n2에 1더함.
                    {
                        if (r->YN == 'Y')
                            n1++;
                        else
                            n2++;
                    }
                free(r);
                if (n1>0)
                    head->YN = 'Y';
                printf("\n\n>> 검색 결과 <<\n");
                printf("도서명:%s\n", s);
                printf("출판사:%s\n", head->pname);
                printf("저자명:%s\n", head->writer);
                printf("ISBN  :%s\n", head->ISBN);
                printf("소장처:%s\n", head->own);
                printf("대여가능 여부:%c(%d/%d)\n", head->YN, n2, n1 + n2);
                printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                free(q);
                break;
            }
        }
        else
        {
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) != 7)
            {
                free(q);
                break;
            }
            q->next = NULL;
            p = head;
            while (p->next != NULL)
                p = p->next;//p포인터 이동
            p->next = q;
            if (!strcmp(s, q->bname))
            {
                if (q->YN == 'Y')
                    n1++;
                else
                    n2++;
                r = malloc(sizeof(book));
                r->next = NULL;
                while (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    if (!strcmp(r->ISBN, q->ISBN))
                    {
                        if (r->YN == 'Y')
                            n1++;
                        else
                            n2++;
                    }
                free(r);
                if (n1>0)
                    q->YN = 'Y';
                printf("\n\n>> 검색 결과 <<\n");
                printf("도서명:%s\n", q->bname);
                printf("출판사:%s\n", q->pname);
                printf("저자명:%s\n", q->writer);
                printf("ISBN  :%s\n", q->ISBN);
                printf("소장처:%s\n", q->own);
                printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);
      printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                free(q);
                break;
            }
        }
    }
    return;
}

void findpname(FILE *ifp, char *s) {//출판사검색
    FILE *ifp2 = NULL;
    ifp2 = fopen("book.txt", "r");
    LINK head = NULL;
    LINK p = NULL;
    LINK q = NULL;
    LINK r = NULL;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;//같은책이 몇권인지 셈.
    while (1) {
        q = malloc(sizeof(book));
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) == 7)
            {
                if (!strcmp(s, q->pname))
                {
                    r = malloc(sizeof(book));
                    r->next = NULL;
                    while (fscanf(ifp2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    {
                        if (!strcmp(r->ISBN, q->ISBN))
                        {
                            if (r->YN == 'Y')
                                n1++;
                            else
                                n2++;
                        }
                        n3 = n1 + n2 - 1;
                        if (n3 >= 0)
                            if ((!strcmp(r->pname, q->pname)) && (strcmp(r->ISBN, q->ISBN)))
                            {
                                for (int k = 0; n3>k; k++)//같은책수만큼 파일지시자 이동
                                    fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN);
                                fclose(ifp2);
                                findpname(ifp, q->pname);
                            }
                    }
                    free(r);
                    if (n1>0)
                        q->YN = 'Y';
                    printf("\n\n>> 검색 결과 <<\n");
                    printf("도서명:%s\n", q->bname);
                    printf("출판사:%s\n", q->pname);
                    printf("저자명:%s\n", q->writer);
                    printf("ISBN  :%s\n", q->ISBN);
                    printf("소장처:%s\n", q->own);
                    printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);
                    printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
          free(q);
                    break;
                }
            }
            else
            {
                free(q);
                return;
            }
        }
        else//head!=NULL일떄
        {
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) == 7)
            {
                q->next = NULL;
                p = head;
                while (p->next != NULL)
                    p = p->next;
                p->next = q;
                if (!strcmp(s, q->pname)) {
                    r = malloc(sizeof(book));
                    r->next = NULL;
                    while (fscanf(ifp2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    {
                        if (!strcmp(r->ISBN, q->ISBN))
                        {
                            if (r->YN == 'Y')
                                n1++;
                            else
                                n2++;
                        }

                        n3 = n1 + n2 - 1;
                        if (n3 >= 0)
                            if ((!strcmp(r->pname, q->pname)) && (strcmp(r->ISBN, q->ISBN)))
                            {
                                for (int k = 0; n3>k; k++)
                                    fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN);
                                fclose(ifp2);
                                findpname(ifp, q->pname);
                            }
                    }
                    free(r);
                    if (n1>0)
                        q->YN = 'Y';

                    printf("\n\n>> 검색 결과 <<\n");
                    printf("도서명:%s\n", q->bname);
                    printf("출판사:%s\n", q->pname);
                    printf("저자명:%s\n", q->writer);
                    printf("ISBN  :%s\n", q->ISBN);
                    printf("소장처:%s\n", q->own);
                    printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);
                    printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                    free(q);
                    break;
                }
            }
            else
            {
                free(q);
                return;
            }
        }
    }
    fclose(ifp2);
    return;
}

void findwriter(FILE *ifp, char *s) {//작가명검색
    FILE *ifp2 = NULL;
    ifp2 = fopen("book.txt", "r");
    LINK head = NULL;
    LINK p = NULL;
    LINK q = NULL;
    LINK r = NULL;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;//같은책이 몇권인지셈.
    while (1) {
        q = malloc(sizeof(book));
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) == 7)
            {
                if (!strcmp(s, q->writer))
                {
                    r = malloc(sizeof(book));//한줄씩 읽으면서 같은 책 찾는 임시 공간
                    r->next = NULL;
                    while (fscanf(ifp2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    {
                        if (!strcmp(r->ISBN, q->ISBN))//ISBN이 같은지(도서가 같은지)검사함
                        {
                            if (r->YN == 'Y')
                                n1++;
                            else
                                n2++;
                        }
                        n3 = n1 + n2 - 1;
                        if (n3 >= 0)
                            if ((!strcmp(r->writer, q->writer)) && (strcmp(r->ISBN, q->ISBN)))
                            {
                                for (int k = 0; n3>k; k++)
                                    fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN);
                                fclose(ifp2);
                                findwriter(ifp, q->writer);
                            }
                    }
                    free(r);
                    if (n1>0)
                        q->YN = 'Y';
                    printf("\n\n>> 검색 결과 <<\n");
                    printf("도서명:%s\n", q->bname);
                    printf("출판사:%s\n", q->pname);
                    printf("저자명:%s\n", q->writer);
                    printf("ISBN  :%s\n", q->ISBN);
                    printf("소장처:%s\n", q->own);
                    printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);
                    printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                    free(q);
                    break;
                }
            }
            else
            {
                free(q);
                return;
            }
        }
        else//head!=NULL
        {
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) == 7)
            {
                q->next = NULL;
                p = head;
                while (p->next != NULL)
                    p = p->next;//p포인터 노드 끝으로 이동
                p->next = q;
                if (!strcmp(s, q->writer)) {
                    r = malloc(sizeof(book));
                    r->next = NULL;
                    while (fscanf(ifp2, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    {
                        if (!strcmp(r->ISBN, q->ISBN))//ISBN이 같은지(도서가 같은지)검사함 도서 같으면 YN(대여가능여부)검사 후 대여가능(Y)이면 n1에 1더하고 대여불가능(N)이면 n2에 1더함.
                        {
                            if (r->YN == 'Y')
                                n1++;
                            else
                                n2++;
                        }
                        n3 = n1 + n2 - 1;
                        if (n3 >= 0)
                            if ((!strcmp(r->writer, q->writer)) && (strcmp(r->ISBN, q->ISBN)))
                            {
                                for (int k = 0; n3>k; k++)
                                    fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN);
                                fclose(ifp2);
                                findwriter(ifp, q->writer);
                            }
                    }
                    free(r);
                    if (n1>0)
                        q->YN = 'Y';

                    printf("\n\n>> 검색 결과 <<\n");
                    printf("도서명:%s\n", q->bname);
                    printf("출판사:%s\n", q->pname);
                    printf("저자명:%s\n", q->writer);
                    printf("ISBN  :%s\n", q->ISBN);
                    printf("소장처:%s\n", q->own);
                    printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);
                    printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                    free(q);
                    break;
                }
            }
            else
            {
                free(q);
                return;
            }

        }
    }
    fclose(ifp2);
    return;
}

void findISBN(FILE *ifp) {
    char s[14];//검색할 ISBN
    LINK head = NULL;
    LINK p = NULL;
    LINK q = NULL;
    LINK r = NULL;
    int n1 = 0;
    int n2 = 0;
    printf("ISBN을 입력하세요:");
    scanf("%s", s);
    while (getchar() != '\n');
    while (1) {
        q = malloc(sizeof(book));
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) != 7)
            {
                printf("검색오류입니다.");
                free(q);
                break;
            }
            if (!strcmp(s, q->ISBN))
            {
                if (q->YN == 'Y')
                    n1++;
                else
                    n2++;
                r = malloc(sizeof(book));
                r->next = NULL;
                while (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    if (!strcmp(r->ISBN, q->ISBN)) {

                        if (r->YN == 'Y')
                            n1++;
                        else
                            n2++;
                    }
                free(r);
                if (n1>0)
                    q->YN = 'Y';

                printf("\n\n>> 검색 결과 <<\n");
                printf("도서명:%s\n", q->bname);
                printf("출판사:%s\n", q->pname);
                printf("저자명:%s\n", q->writer);
                printf("ISBN  :%s\n", q->ISBN);
                printf("소장처:%s\n", q->own);
                printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);
                printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                free(q);
                break;
            }
        }
        else
        {
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) != 7)
            {
                free(q);
                break;
            }
            q->next = NULL;
            p = head;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = q;
            if (!strcmp(s, q->ISBN)) {
                if (q->YN == 'Y')
                    n1++;
                else
                    n2++;
                r = malloc(sizeof(book));
                r->next = NULL;
                while (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", r->bnum, r->bname, r->pname, r->writer, r->ISBN, r->own, &r->YN) == 7)
                    if (!strcmp(r->ISBN, q->ISBN)) {
                        if (r->YN == 'Y')
                            n1++;
                        else
                            n2++;
                    }
                free(r);
                if (n1>0)
                    q->YN = 'Y';

                printf("\n\n>> 검색 결과 <<\n");
                printf("도서명:%s\n", q->bname);
                printf("출판사:%s\n", q->pname);
                printf("저자명:%s\n", q->writer);
                printf("ISBN  :%s\n", q->ISBN);
                printf("소장처:%s\n", q->own);
                printf("대여가능 여부:%c(%d/%d)\n", q->YN, n2, n1 + n2);//복사
                printf("**Y는 대여가능,N은 대여불가를 의미\n**(x/y):(대여된 총 권수/보유하고 있는 총 권수i\n\n");
                free(q);
                break;
            }
        }
    }
    return;
}

void findall(FILE *ifp) {//전체검색함수.
    LINK head = NULL;
    LINK p = NULL;
    LINK q = NULL;
    printf("\n\n>> 검색 결과 <<\n");
    while (1) {
        q = malloc(sizeof(book));
        q->next = NULL;
        if (head == NULL) {
            head = q;
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) == 7)
            {
                printf("도서명:%s\n", q->bname);
                printf("출판사:%s\n", q->pname);
                printf("저자명:%s\n", q->writer);
                printf("ISBN  :%s\n", q->ISBN);
                printf("소장처:%s\n", q->own);
                printf("대여가능 여부:%c\n\n", q->YN);
            }
        }
        else
        {
            p = head;
            while (p->next != NULL)
                p = p->next;
            p->next = q;
            if (fscanf(ifp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n", q->bnum, q->bname, q->pname, q->writer, q->ISBN, q->own, &q->YN) == 7)
            {
                printf("도서명:%s\n", q->bname);
                printf("출판사:%s\n", q->pname);
                printf("저자명:%s\n", q->writer);
                printf("ISBN  :%s\n", q->ISBN);
                printf("소장처:%s\n", q->own);
                printf("대여가능 여부:%c\n\n", q->YN);
            }
            else
            {
                free(q);
                return;
            }
        }
    }
}

/*------------용준----------------*/



/*-------------영민-------------*/

void register_member()   // 등록
{
    int student_number; //학번
    char password[50]; //비밀번호
    char name[20]; //이름
    char address[100]; //주소
    char phone_number[12]; //전화번호

    client* current = (client*)malloc(sizeof(client)); //현재 가리키고 있는 구조체 포인터
    client* current_past = (client*)malloc(sizeof(client));
    current_past = current = client_head;

    printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n");
    printf("학번: ");
    scanf("%d", &student_number);
    getchar();

    //기존링크드에 입력받은 값을 학번순으로 삽입하여 새로운 링크드리스트를 만듦
    while (current != client_tail) //링크드의 모든 값을 비교하기 전까지 반복
    {
        if (current->std_id < student_number) // 다음 링크드로 넘어감
        {
            current_past = current;
            current = current->next;
        }
        else if (current->std_id > student_number) // 링크드 사이에 새로운 링크드 삽입
        {
            printf("비밀번호: ");
            scanf("%s", password);
            getchar();
            printf("이름: ");
            scanf("%[^\n]", name);
            getchar();
            printf("주소: ");
            scanf("%[^\n]", address);
            printf("전화번호: ");
            scanf("%s", phone_number);
            getchar();

            if (current_past == current) //입력받은 학번이 링크드의 가장 첫번째 순서일 경우
            {
                client_head = (client*)malloc(sizeof(client));
                client_head->std_id = student_number;
                strcpy(client_head->password, password);
                strcpy(client_head->std_name, name);
                strcpy(client_head->addr, address);
                strcpy(client_head->ph_num, phone_number);

                client_head->next = (client*)malloc(sizeof(client));
                client_head->next = current;    //head의 다음 링크드리스트를 기존의 head로 만듦
                client_tail = current->next = (client*)malloc(sizeof(client)); //다음 링크드리스트를 tail로 설정
                break;
            }
            else
            {
                current_past = current_past->next = (client*)malloc(sizeof(client));
                current_past->std_id = student_number;                      //새로운 링크드리스트에 입력
                strcpy(current_past->password, password);
                strcpy(current_past->std_name, name);
                strcpy(current_past->addr, address);
                strcpy(current_past->ph_num, phone_number);

                current_past->next = (client*)malloc(sizeof(client));
                current_past->next = current; //새로운 링크드리스트 다음에 이전 링크드리스트 연결하여 삽입
                break;
            }
        }
        else
        {
            printf("이미 가입되어 있습니다.\n");
            break;
        }
    }
    if (current == client_tail) // std_id가 마지막 정렬순서일 경우
    {
        printf("비밀번호: ");
        scanf("%s", current->password);
        getchar();
        printf("이름: ");
        scanf("%[^\n]", current->std_name);
        getchar();
        printf("주소: ");
        scanf("%[^\n]", current->addr);
        printf("전화번호: ");
        scanf("%s", current->ph_num);
        getchar();

        current->std_id = student_number;               //  마지막 링크에 입력받은 학번

        client_tail = current->next = (client*)malloc(sizeof(client));
    }


    FILE* fp = fopen("client.txt", "w");
    current = client_head; //링크드리스트의 처음으로 이동

    while (current != client_tail) //링크드리스트의 모든 값을 입력하기 전까지 반복
    {
        fprintf(fp, "%d|", current->std_id);
        fprintf(fp, "%s|", current->password);
        fprintf(fp, "%s|", current->std_name);
        fprintf(fp, "%s|", current->addr);
        fprintf(fp, "%s\n", current->ph_num);

        current = current->next; //while문 탈출
    }
    fclose(fp);

}
void member_menu(int id, Borrow *br_cur, Book *bk_cur, Client *cl_cur)  //회원메뉴
{
    system("clear");
    int choose;
    while(1){
        printf(">>회원 매뉴<<\n");
        printf("1. 도서 검색\t 2. 내 대여 목록\n");
        printf("3. 개인정보 수정\t 4. 회원 탈퇴\n");
        printf("5. 로그아웃\t 6. 프로그램 종료\n");

        printf("번호를 선택하세요:");
        scanf("%d",&choose);

        if(choose==1){
            search();
            //도서 검색 함수
        }
        if(choose==2){
            // 대여 목록 함수
            borrow_search(id, br_cur, bk_cur);
        }
        if(choose==3){
            modify_member();
        }
        if(choose==4){
            delete_member(id, br_cur, cl_cur);
        }
        if(choose==5){
            main();
        }
        if(choose==6){
            exit(1);
        }

    }
}

void borrow_search(int id, Borrow *br_cur, Book *bk_cur) {
    Borrow *br_head = br_cur;
    Book *bk_head = bk_cur;

    int year,month,day;
    struct tm* timeinfo;
    char *weekday[] = {"일요일",   "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};

    printf(">>내 대여 목록<<\n");

    br_cur = br_head -> next;
    bk_cur = bk_head -> next;
    while(br_cur != NULL) {
        if(br_cur->std_id == id) {
            printf("도서번호 : %d\n", br_cur -> bk_id);
            while(bk_cur != NULL) {
                if(bk_cur -> book_id == br_cur->bk_id) {
                    printf("도서명 : %s\n", bk_cur->book_name);
                }
                bk_cur=bk_cur->next;
            }
            bk_cur=bk_head->next;
            //날짜 출력
            mul_time(br_cur->rent_date, &year, &month, &day);
            time_t baseTime = make_time(br_cur->rent_date, &year, &month, &day);
            timeinfo = localtime(&baseTime);
            timeinfo->tm_year = year - 1900;
            timeinfo->tm_mon = month - 1;
            timeinfo->tm_mday = day;
            mktime(timeinfo);
            printf("대여 일자 : %ld%s\n",br_cur->rent_date,weekday[timeinfo->tm_wday]);

            mul_time(br_cur->return_date, &year, &month, &day);
            baseTime = make_time(br_cur->return_date, &year, &month, &day);

            timeinfo = localtime(&baseTime);
            timeinfo->tm_year = year - 1900;
            timeinfo->tm_mon = month - 1;
            timeinfo->tm_mday = day;
            mktime(timeinfo);

            printf("반납 일자 : %ld%s\n\n",br_cur->return_date,weekday[timeinfo->tm_wday]);

        }
        br_cur = br_cur -> next;
    }
    br_cur = br_head-> next;
}

void modify_member()      // 수정
{
    int student_id;
    student_id = atoi(id_login);
    char change_password[300]; // 현재 비밀번호
    client * current = (client*)malloc(sizeof(client));
    current = client_head;
    while (current != client_tail) // 현재 학번과 일치하는 링크탐색
    {
        if (current->std_id == student_id)
            break;
        else
            current = current->next;
    }

    while (1)
    {
        printf("개인정보를 수정하기 위해 현재 비밀번호를 입력하세요.\n비밀먼호 : ");
        scanf("%s", change_password);


        if (!strcmp(current->password, change_password))
        {
            printf("수정할 비밀번호, 주소, 전화번호를 입력하세요.\n");
            printf("비밀번호 : ");
            scanf("%s", current->password);
            getchar();
            printf("주소 : ");
            gets(current->addr);
            printf("전화번호 : ");
            scanf("%s", current->ph_num);
            getchar();

            FILE * fp = fopen("client.txt", "w");
            current = client_head;

            while (current != client_tail)
            {
                fprintf(fp, "%d|", current->std_id);
                fprintf(fp, "%s|", current->password);
                fprintf(fp, "%s|", current->std_name);
                fprintf(fp, "%s|", current->addr);
                fprintf(fp, "%s\n", current->ph_num);

                current = current->next;
            }

            fclose(fp);

            break;
        }
        else
        {
            printf("비밀번호가 틀립니다.\n");
            change_password[0] = '\0';
        }
    }
}
void client_add()  // txt 에 저장된 값을 링크드리스트에 저장해주는 함수
{
    FILE* fp = fopen("client.txt", "r");
    client* current= (client*)malloc(sizeof(client));
    current= client_head;
    while (!feof(fp)) //파일에 더이상 읽을 값이 없으면 반복문 종료.
    {
        fscanf(fp, "%d|", &current->std_id);
        fscanf(fp, "%[^|]|", current->password);
        fscanf(fp, "%[^|]|", current->std_name);
        fscanf(fp, "%[^|]|", current->addr);
        fscanf(fp, "%[^\n]\n", current->ph_num);

        current = current->next = (client*)malloc(sizeof(client)); //다음 링크드ㄹ스트로로 이동
    }
    fclose(fp);
    client_tail = current;
}

void delete_member(int id, Borrow *br_cur, Client *cl_cur)   // 탈퇴
{
    Borrow *br_head = br_cur;
    Client *cl_head = cl_cur, *del_node, *tail_node;
    int br_check=0;

    br_cur = br_head -> next;

    while(br_cur != NULL) {
        if(br_cur -> std_id == id) {
            br_check ++;
        }
        br_cur = br_cur -> next;
    }
    br_cur = br_head -> next;


    FILE *cfp = fopen("./client.txt", "w");

    if(br_check == 0) { //대여중인 도서가 없을때
        if(cl_head -> next-> std_id == id) {       //첫번째 노드일때
            delete_cl_node(&cl_head, cl_head->next);
            while(cl_cur != NULL) {
                if(cl_cur->std_id != 0) {
                    fprintf(cfp, "%d|%s|%s|%s|%s\n", cl_cur->std_id, cl_cur->password, cl_cur->std_name, cl_cur->addr, cl_cur->ph_num);
                }
                cl_cur=cl_cur->next;
            }
        } else {    //중간이나 끝일때
            cl_cur=cl_head->next;
            while(cl_cur != NULL) { //끝에서 두번째 노드 찾기
                if(cl_cur->next->next == NULL) {
                    tail_node = cl_cur;
                    break;
                }
                cl_cur=cl_cur->next;
            }
            if(tail_node->next->std_id == id) {   //마지막 노드일때
                delete_cl_node(&tail_node, tail_node->next);
                cl_cur=cl_head->next;
                while(cl_cur != NULL) {
                    fprintf(cfp, "%d|%s|%s|%s|%s\n", cl_cur->std_id, cl_cur->password, cl_cur->std_name, cl_cur->addr, cl_cur->ph_num);
                    cl_cur = cl_cur -> next;
                }
            } else {    //중간일때
                cl_cur=cl_head->next;
                while(cl_cur != NULL) {
                    if(cl_cur->next->std_id == id) {    //전에 노드 위치저장
                        del_node = cl_cur;
                        break;
                    }
                    cl_cur=cl_cur->next;
                }
                cl_cur=cl_head->next;
                delete_cl_node(&del_node, del_node->next);
                while(cl_cur != NULL) {
                    fprintf(cfp, "%d|%s|%s|%s|%s\n", cl_cur->std_id, cl_cur->password, cl_cur->std_name, cl_cur->addr, cl_cur->ph_num);
                    cl_cur = cl_cur -> next;
                }
            }
        }
        printf("탈퇴 성공\n");
    } else {
        printf("탈퇴 불가능\n");
    }

    fclose(cfp);
}


/*-------------영민-------------*/
