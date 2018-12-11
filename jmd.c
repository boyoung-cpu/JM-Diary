#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void calendar();

char init_arr[257] = { 0 };

int main(int argc, char *argv[]) {
    int opt_a = 0;
    int opt_c = 0;
    int opt_d = 0;
    int opt_e = 0;
    int opt_f = 0;
    int option = 0;
    int fd, temp_fd;
    struct tm *tm;
    time_t t;
    char buf[257] = { 0 };
    char file_name[50] = { 0 };

    t = time(NULL);
    tm = localtime(&t);

    mode_t mode;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (argc < 2) {
        printf("        ���ڸ�  �Է��ϼ���         \n");
        printf("-------------------------------------------\n");
        printf("  -c : �޷� ����\n\n");
        printf("  -a : ���� �߰�\n");
        printf("       �Է� ����\n");
        printf("       1. '���ھ��� ��������ǥ �� ����'\n");
        printf("       2. ��-��-�� '����'\n");
        printf("       3. ��-��-�� ��:�� '����'\n\n");
        printf("  -e : ���� ����\n");
        printf("       ��-��-�� ���·� ���� ���� ��\n");
        printf("       ������ �׸� ����\n");
        printf("       c. ���� ����\n");
        printf("       t. �ð� ����\n\n");
        printf("  -d : ���� ����\n");
        printf("       ��-��-�� ���·� ���� ���� ��\n");
        printf("       ������ �׸� ���� ��\n");
        printf("       y. ����\n");
        printf("       n. ���\n\n");
        printf("  -f : ���� �˻�\n");
        printf("       ��-��-�� �Է� �� Ư������ �˻�\n");
        printf("--help: �ɼ� ����\n");
        printf("-------------------------------------------\n");
        return 0;
    }
    else {
        if (strcmp(argv[1], "--help") == 0) {
            printf("        ���ڸ�  �Է��ϼ���         \n");
            printf("-------------------------------------------\n");
            printf("  -c : �޷� ����\n\n");
            printf("  -a : ���� �߰�\n");
            printf("       �Է� ����\n");
            printf("       1. '���ھ��� ��������ǥ �� ����'\n");
            printf("       2. ��-��-�� '����'\n");
            printf("       3. ��-��-�� ��:�� '����'\n\n");
            printf("  -e : ���� ����\n");
            printf("       ��-��-�� ���·� ���� ���� ��\n");
            printf("       ������ �׸� ����\n");
            printf("       c. ���� ����\n");
            printf("       t. �ð� ����\n\n");
            printf("  -d : ���� ����\n");
            printf("       ��-��-�� ���·� ���� ���� ��\n");
            printf("       ������ �׸� ���� ��\n");
            printf("       y. ����\n");
            printf("       n. ���\n\n");
            printf("  -f : ���� �˻�\n");
            printf("       ��-��-�� �Է� �� Ư������ �˻�\n");
            printf("--help: �ɼ� ����\n");
            printf("-------------------------------------------\n");
            return 0;
        }
        while ((option = getopt(argc, argv, "ca:e:d:f:")) != -1) {
            switch (option) {
                case 'c':
                    opt_c++;
                    break;
                case 'a':
                    opt_a++;
                    break;
                case 'e':
                    opt_e++;
                    break;
                case 'd':
                    opt_d++;
                    break;
                case 'f':
                    opt_f++;
                    break;
                default:
                    break;
            }
        }
    }

    // �޸� �Է� �ɼ�
    if (opt_a) {
        switch (argc)
        {
            case 3: // ���ڰ� 3���϶� (JM-Diary -a '����')
                t = time(NULL);
                tm = localtime(&t);
                sprintf(file_name, "%04d-%02d.txt", tm->tm_year + 1900, tm->tm_mon + 1);
                fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, mode);
                if (fd == -1) {
                    perror("���� ����");
                    exit(1);
                }
                sprintf(buf, "%04d-%02d-%02d %02d:%02d %s\n",
                        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                        tm->tm_hour, tm->tm_min, argv[2]);
                if (write(fd, buf, strlen(buf)) != strlen(buf))
                    perror("���� ����");
                close(fd);
                break;
            case 4: // ���ڰ� 4���� �� (JM-Diary -a 2018-05-12 '����')
                sprintf(file_name, "%c%c%c%c-%c%c.txt",
                        argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
                fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, mode);
                if (fd == -1) {
                    perror("���� ����");
                    exit(1);
                }
                sprintf(buf, "%s 09:00 %s\n", argv[2], argv[3]);
                if (write(fd, buf, strlen(buf)) != strlen(buf))
                    perror("���� ����");
                close(fd);
                break;
            case 5: // ���ڰ� 5���� �� (JM-Diary -a 2018-07-11 12:11 '����')
                sprintf(file_name, "%c%c%c%c-%c%c.txt",
                        argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
                fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, mode);
                if (fd == -1) {
                    perror("���� ����");
                    exit(1);
                }
                sprintf(buf, "%s %s %s\n", argv[2], argv[3], argv[4]);
                if (write(fd, buf, strlen(buf)) != strlen(buf))
                    perror("���� ����");
                close(fd);
                break;
        }
    }

    //�޸� ���� �ɼ�
    else if (opt_e) {
        if (argc != 3) {
            printf("���Ŀ� �°� �Է����ּ���\n");
            printf("jmd -e 0000-00-00\n");
        }
        else {
            //������ ���ϴ� ���ڸ� �Է¹޾� �ش� �޸� ����ִ� ������ ����
            sprintf(file_name, "%c%c%c%c-%c%c.txt", argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);    //�Էµ� ������ �� ���� ������ ���ϸ� Ȯ��

            fd = open(file_name, O_RDWR, mode);     //�ش����� ���� ����

            if (fd == -1) {
                perror("���� ����");
                exit(1);
            }

            temp_fd = open("temp.txt", O_RDWR | O_CREAT, mode);     //������ ������ �����ų �ӽ� ����
            if (fd == -1) {
                perror("���� ����");
                exit(1);
            }

            int length = 0;
            int line_num = 0;
            int file_line_num = 0;
            int file_line_nums[100] = { 0 };
            int sel_line = 0;
            char edit_sel[5] = { 0 };
            char edit_content[100] = { 0 };
            char edit_time[100] = { 0 };
            char origin_cont[100] = { 0 };
            int edit_set = 0;
            char temp[100] = { 0 };

            //���� �ش� ���ڿ� �ԷµǾ� �ִ� �޸� ���� ��ü ���
            while (read(fd, temp, 1) > 0) {
                if (temp[0] != '\n') {
                    buf[length] = temp[0];
                    length++;
                }
                else {
                    buf[length] = '\0';
                    length = 0;

                    file_line_num++;

                    if (strncmp(argv[2], buf, 10) == 0) {
                        file_line_nums[line_num] = file_line_num;
                        printf("%d. ", line_num + 1);
                        line_num++;
                        puts(buf);
                    }
                }
            }

            if (line_num == 0) {
                printf("������ �׸��� �����ϴ�.\n");
                exit(1);
            }
            else {
                printf("������ �׸��� �����ϼ���\n->");

                fflush(stdout);

                scanf("%d", &sel_line);
                length = 0;

                printf("-------------------------------\n");
                printf("���� �ϼ���\n\n");
                printf("c. ���� ����\n");
                printf("t. �ð� ����\n");
                printf("-------------------------------\n");
                printf("->");
                scanf("%s", &edit_sel);

                if (strcmp(edit_sel, "c") == 0) {
                    edit_set = 1;
                    printf("������ ������ �Է��ϼ���\n->");
                    rewind(stdin);
                    gets(edit_content);
                }
                else if (strcmp(edit_sel, "t") == 0) {
                    edit_set = 2;
                    printf("������ �ð��� �Է��ϼ��� (�Է� ���� 00:00)\n->");
                    scanf("%s", &edit_time);
                }
                else if (strcmp(edit_sel, "t") != 0 || strcmp(edit_sel, "c") != 0) {
                    printf("�߸� �ԷµǾ����ϴ�.\n");
                    printf("�ٽ� �������ּ���\n");
                    return 0;
                }
                if (sel_line >= 1 && sel_line < line_num + 1) {
                    line_num = 0;
                    lseek(fd, 0, SEEK_SET);
                    while (read(fd, temp, 1) > 0) {
                        if (temp[0] != '\n') {
                            buf[length] = temp[0];
                            length++;
                        }
                        else {
                            buf[length] = '\0';
                            length = 0;

                            line_num++;

                            //�����Ϸ��� ���� �ƴ� ���
                            if (line_num != file_line_nums[sel_line - 1]) {
                                write(temp_fd, buf, strlen(buf));
                                write(temp_fd, "\n", 1);
                            }
                            //�����Ϸ��� ���� ���
                            else if (line_num == file_line_nums[sel_line - 1]) {
                                //�Է��� �������� �ӽ����Ͽ� �Է�
                                if (edit_set == 1) {
                                    write(temp_fd, buf, 17);
                                    write(temp_fd, edit_content, strlen(edit_content));
                                    write(temp_fd, "\n", 1);
                                }
                                else if (edit_set == 2) {
                                    strcpy(origin_cont, buf + 17);
                                    write(temp_fd, buf, 11);
                                    write(temp_fd, edit_time, strlen(edit_time));
                                    write(temp_fd, " ", 1);
                                    write(temp_fd, origin_cont, strlen(origin_cont));
                                    write(temp_fd, "\n", 1);
                                }
                            }
                        }
                    }

                    close(fd);
                    remove(file_name);

                    lseek(temp_fd, 0, SEEK_SET);

                    //�� ���Ͽ� ������ ������ �����
                    fd = open(file_name, O_CREAT | O_WRONLY, mode);
                    int n;
                    while ((n = read(temp_fd, buf, 6)) > 0) {
                        if (write(fd, buf, n) != n)
                            perror("Write");
                    }
                    close(fd);
                    close(temp_fd);
                    remove("temp.txt");
                }
                else {
                    printf("������ �׸��� �����ϴ�.\n");
                    exit(1);
                }
            }
            close(fd);
        }
    }
    //delete �޸� ���� �ɼ�
    else if (opt_d) {
        if (argc != 3) {
            printf("���Ŀ� �°� �Է����ּ���\n");
            printf("jmd -d 0000-00-00\n");
        }
        else {
            //������ ���ϴ� ���ڸ� �Է¹޾� �ش� �޸� ����ִ� ������ ����
            sprintf(file_name, "%c%c%c%c-%c%c.txt",
                    argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);    //�Էµ� ���ڸ� �̿��� ���ϸ� Ȯ��

            fd = open(file_name, O_RDWR, mode);     //�ش� ���� �޸� ����ִ� ���� ����
            if (fd == -1) {
                perror("���� ����");
                exit(1);
            }

            temp_fd = open("temp.txt", O_RDWR | O_CREAT, mode);     //������ ������ ��� ���� �ӽ����� ����
            if (fd == -1) {
                perror("���� ����");
                exit(1);
            }

            int length = 0;
            int line_num = 0;
            int file_line_num = 0;
            int file_line_nums[100] = { 0 };
            int sel_line = 0;
            char temp[100] = { 0 };
            while (read(fd, temp, 1) > 0) {
                if (temp[0] != '\n') {
                    buf[length] = temp[0];
                    length++;
                }
                else {
                    buf[length] = '\0';
                    length = 0;

                    file_line_num++;

                    if (strncmp(argv[2], buf, 10) == 0) {
                        file_line_nums[line_num] = file_line_num;
                        printf("%d. ", line_num + 1);
                        line_num++;
                        puts(buf);
                    }
                }
            }

            if (line_num == 0) {
                printf("������ �׸��� �����ϴ�.\n");
                exit(1);
            }
            else {
                printf("������ �׸��� �����ϼ���\n->");

                fflush(stdout);

                scanf("%d", &sel_line);
                length = 0;

                if (sel_line >= 1 && sel_line < line_num + 1) {
                    line_num = 0;
                    lseek(fd, 0, SEEK_SET);
                    while (read(fd, temp, 1) > 0) {
                        if (temp[0] != '\n') {
                            buf[length] = temp[0];
                            length++;
                        }
                        else {
                            buf[length] = '\0';
                            length = 0;

                            line_num++;

                            //������ ���ϴ� ������ ������ ������ ������ �ӽ����Ͽ� ����
                            if (line_num != file_line_nums[sel_line - 1]) {
                                write(temp_fd, buf, strlen(buf));
                                write(temp_fd, "\n", 1);
                            }
                        }
                    }

                    close(fd);
                    remove(file_name);

                    lseek(temp_fd, 0, SEEK_SET);

                    //�ӽ� ���Ͽ� ����� ������ �� ���Ͽ� ���� ����
                    fd = open(file_name, O_CREAT | O_WRONLY, mode);
                    int n;
                    while ((n = read(temp_fd, buf, 6)) > 0) {
                        if (write(fd, buf, n) != n)
                            perror("Write");
                    }
                    close(fd);
                    close(temp_fd);
                    remove("temp.txt");
                }
                else {
                    printf("������ �׸��� �����ϴ�.\n");
                    exit(1);
                }
            }
            close(fd);
        }
    }
    //find �޸� �˻� �ɼ�
    else if (opt_f) {
        if (argc != 3) {
            printf("���Ŀ� �°� �Է��ϼ���\n");
            printf("jmd -f 0000-00-00\n");
        }
        else {
            //�Էµ� ��¥ ���� ���� ����Ǿ��ִ� ���� ����
            sprintf(file_name, "%c%c%c%c-%c%c.txt",
                    argv[2][0], argv[2][1], argv[2][2], argv[2][3], argv[2][5], argv[2][6]);
            fd = open(file_name, O_RDONLY, mode);
            if (fd == -1) {
                perror("���� ����");
                exit(1);
            }
            int length = 0;
            int line_num = 1;
            char temp[100] = { 0 };
            while (read(fd, temp, 1) > 0) {
                if (temp[0] != '\n') {
                    buf[length] = temp[0];
                    length++;
                }
                else {
                    buf[length] = '\0';
                    length = 0;
                    if (strncmp(argv[2], buf, 10) == 0) {
                        printf("%d. ", line_num);
                        line_num++;
                        puts(buf);
                    }
                }
            }
            if (line_num == 1) {
                printf("��ȸ�� �׸��� �����ϴ�.\n");
                exit(1);
            }
            close(fd);
        }
    }
    else if (opt_c) {
        calendar(); // �޷����
    }
    return 0;
}

//�޷� ��� �Լ�
void calendar() {
    struct tm *tm;
    time_t t;
    time(&t);
    tm = localtime(&t);
    //�� ���� ��¥ �� ����
    int month[12] = { 31,0,31,30,31,30,31,31,30,31,30,31 };
    int i, j, d, k;
    int totalday = 0;
    int h = 1;

    int year = tm->tm_year + 1900;
    int _month = tm->tm_mon + 1;

    printf("%10d �� %3d �� \n", year, _month);
    printf("------------------------------\n");
    printf("  ��  ��  ȭ  ��  ��  ��  ��  \n");
    printf("------------------------------\n");
    //���� üũ
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        month[1] = 29;
    }
    else month[1] = 28;

    //������
    totalday = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    for (k = 1; k <= _month - 1; k++) {
        totalday = totalday + month[k - 1];
    }
    //���
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 7; j++, h++) {
            if (h <= month[_month - 1] + 1 + totalday % 7) {
                d = h - totalday % 7;
                if (d - 1 <= 0)
                    printf("    ");
                else
                    printf("%4d", d - 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

                                                                                                                                                                                            