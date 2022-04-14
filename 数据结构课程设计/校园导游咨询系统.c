#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 10000
#define M 20                                                    /*��󶥵���*/
typedef struct {
	int num;                                                    /*��������*/
	char name[20];                                              /*��������*/
	char intro[200];                                            /*�������*/
}vertextype;

typedef int edgtype;                                            /*Ȩֵ����*/
typedef struct {                                                /*У԰����ͼ�ṹ��*/
	vertextype vexs[M];                                         /*������Ϣ��*/
	edgtype edge[M][M];                                         /*�ڽӾ���*/
	int vexNum, edgNum;                                         /*�������ͱ���*/
}mgraphtype;

int menu();                                                     /*���˵�*/
void Create_Map(mgraphtype *g);                                 /*���ļ���ȡ��Ϣ����ͼ*/
void Print_Map();                                               /*��ʾУ԰������ͼ*/
int Judge_Input(int num);                                       /*�ж�����ı���Ƿ����*/
void Search_Location(mgraphtype *g);                            /*������Ϣ��ѯ*/
void ShortPath(mgraphtype *g);                                  /*���������·��*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum);            /*�ݹ��ӡ��������·��*/
void Shortpath_Print(mgraphtype *g);                            /*�������ӡ���������·��*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum);              /*������ȱ�����ѯ������������·��*/
void Allpath_Print(mgraphtype *g);                              /*��ѯ������������·������ӡ*/
void BestPath(mgraphtype *g);                                   /*�ඥ��������·��*/
void System_Exit(int *q);                                       /*�˳�ϵͳ*/

/*У԰����ͼ�Ķ�ȡ�봴��*/
void Create_Map(mgraphtype *g)
{
	int i, j, k, e;
	FILE *rf;
	rf = fopen("map.txt", "r");
	if (rf)
	{
		fscanf(rf, "%d%d", &g->vexNum, &g->edgNum);//��ȡ�ڵ��� ����
		for (i = 0; i < g->vexNum; i++)
			fscanf(rf, "%d%s%s", &g->vexs[i].num, g->vexs[i].name, g->vexs[i].intro);  //���붥����Ϣ����  �����
		for (i = 0; i < g->vexNum; i++)//��ʼ���ڽӾ���
			for (j = 0; j < g->vexNum; j++)
			{
				if (i == j)
					g->edge[i][j] = 0;//�Լ����Լ���ȨֵΪ0
				else
					g->edge[i][j] = INFINITY; ///��ʼ������֮���Ȩֵ Ĭ��Ϊ����
			}
		for (k = 0; k < g->edgNum; k++)
		{
			fscanf(rf, "%d%d%d", &i, &j, &e); //��ȡֵ  ���ڽӱ���и�ֵ
			g->edge[i][j] = g->edge[j][i] = e;//����ͼʱ����Ҫ���������ͼʱ��Ҫ����
		}
		fclose(rf);
	}
	else
		g->edgNum = 0;
}

/*У԰����ͼ����ʾ*/
void Dis_Map() {


	printf("\n                             �����������ѧ��У��У԰������ͼһ����                                                                  \n\n");

	printf("                 9.������  ��10.��������          11.��ҽ����                                                                              \r");
	printf("                       �U   �U                       �U                                                                                    \r");
	printf("                       -----------------------------------------------------                                                            \r");
	printf("                       �U                        �U                        �U                                                           \r");
	printf("                       �U                        �U                        ��12.�Ļ���                                                  \r");
	printf("                       �U        8.���˼ѧԺ��--�U                                                                                     \r");
	printf("                       �U                        �U                                                                                     \r");
	printf("                       �U        7.��������ġ�--�U----��4.����                                                                     \r");
	printf("        6.Уʷ�ݡ�----------------------------- �U    �U                                                                                \r");
	printf("                �U                   3.ͼ��ݡ�--�U    �U                                                                               \r");
	printf("                �U                               �U----��2.11�Ž�ѧ¥                                                                   \r");
	printf("                �U                               �U    �U                                                                               \r");
	printf("      5.�������š�-----------------------------------��1.��У���ſ�                                                                     \r");

}

/*������Ϣ��ѯ*/
void Search_Location(mgraphtype *g) {
	int s;
	do {
		printf("\n��������Ҫ���ҵĽ�����ţ�");
		scanf("%d", &s);
	} while (Judge_Input(s));
	printf("\n�������ƣ�[%s]\n\n", g->vexs[s - 1].name);
	printf("������飺 %s\n\n", g->vexs[s - 1].intro);
}

/*Floyd�㷨�����������һ����̵�·��*/
int dist[M][M];                                                    /*��������*/
int path[M][M];                                                    /*·������*/
void ShortPath(mgraphtype *g) {
	int i, j, k;
	for (i = 0; i < g->vexNum; i++)                                /*��ʼ����������������·����������*/
		for (j = 0; j < g->vexNum; j++) {
			dist[i][j] = g->edge[i][j];// "����i"��"����j"��·������Ϊ"i��j��Ȩֵ"
			if (i != j && dist[i][j] < INFINITY) path[i][j] = i; //"����i"��"����j"�����·���Ǿ�������j
			else path[i][j] = -1;                                  /*-1����ǰ���㲻�ɴ�*/
		}
	for (k = 0; k < g->vexNum; k++)                                /*�������ÿ�����������·��*/
		for (i = 0; i < g->vexNum; i++)
			for (j = 0; j <= g->vexNum; j++)                        /*����dist[i][j]��ֵ*/
				if (dist[i][j] >(dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;                                /*path���ڼ�¼���·���ϵľ����*/
				}
}

/*�ݹ�ʵ�ִ�ӡ���������·��*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum) {
	if (path[sNum][eNum] == -1 || path[sNum][eNum] == eNum || path[sNum][eNum] == sNum)
		return;
	else {
		Floyd_Print(g, sNum, path[sNum][eNum]);                 /*���м����Ϊ�յ������ӡ·��*/
		printf("%s->", g->vexs[path[sNum][eNum]].name);         /*��ӡ�м佨������*/
		Floyd_Print(g, path[sNum][eNum], eNum);                 /*���м����Ϊ��������ӡ·��*/
	}
}

/*�������ӡ���������·��*/
void Shortpath_Print(mgraphtype *g) {
	int sNum, eNum;                                             /*����ţ��յ���*/
	do {
		printf("\n����������ţ�");
		scanf("%d", &sNum);
	}while (Judge_Input(sNum));
	do {
		printf("\n�������յ��ţ�");
		scanf("%d", &eNum);
	} while (Judge_Input(eNum));

	printf("\n%s��%s����̾����ǣ�%dm\n", g->vexs[--sNum].name, g->vexs[--eNum].name, dist[sNum][eNum]);
	printf("\n�����������·�ߣ�");
	printf("%s->", g->vexs[sNum].name);                                       /*���·���ϵ����*/
	Floyd_Print(g, sNum, eNum);                                               /*���·���ϵ��м��*/
	printf("%s\n\n", g->vexs[eNum].name);                                     /*���·���ϵ��յ�*/
}

/*������ȱ�����ѯ������������֮�������·��*/
int pathStack[M];                                                             /*·��ջ���洢·����Ϣ*/
int top;                                                                      /*ջ��*/
int visited[M];                                                               /*��ջ��ǣ���ֹ�γɻ�·*/
int count;                                                                    /*·��������*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum) {
	int dis = 0;                                                              /*���ڼ�¼·������*/
	pathStack[top] = sNum;                                                    /*�����������ջ*/
	top++;
	visited[sNum] = 1;                                                        /*����ջ����Ϊ����ջ*/
	for (int i = 0; i < g->vexNum; i++) {
		if (g->edge[sNum][i] > 0 && g->edge[sNum][i] != INFINITY && !visited[i]) {
			/*����ǰһ����ջ����õ�ɴ�Ҹõ�δ��ջ��δ�����ʣ�*/
			if (i == eNum) {                                                  /*�����ȱ����ѵ����յ㣬������ղŵ�·��*/
				printf("��%d��·:", count++);
				for (int j = 0; j < top; j++) {
					printf("%s->", g->vexs[pathStack[j]].name);
					if (j < top - 1)
						dis = dis + g->edge[pathStack[j]][pathStack[j + 1]];        /*ͳ��·������*/
				}
				dis = dis + g->edge[pathStack[top - 1]][eNum];                      /*���һ��·������������Ϊenum������ջ*/
				printf("%s\n", g->vexs[eNum].name);
				printf("�ܳ����ǣ�%dm\n\n", dis);
			}
			else {
				Dfs_Print(g, i, eNum);                                              /*����õ㲻���յ�,�����������*/
				top--;                                                              /*֧·ȫ������һ��󣬶����ջ*/
				visited[i] = 0;                                                     /*����ջ����Ϊ�ѳ�ջ�������´η���*/
			}
		}
	}
}

/*��ѯ������������֮�������·������ӡ*/
void Allpath_Print(mgraphtype *g) {
	int sNum, eNum;
	count = 1;                                                       /*·��������*/
	top = 0;                                                         /*ջ��*/
	memset(pathStack, 0, sizeof(pathStack));                         /*·��ջ��ʼ��   memset() �����������ڴ�ռ��ʼ��*/
	memset(visited, 0, sizeof(visited));                             /*��ջ��ǳ�ʼ��*/
	do {
		printf("\n����������ţ�");
		scanf("%d", &sNum);
	} while (Judge_Input(sNum));
	do {
		printf("\n�������յ��ţ�");
		scanf("%d", &eNum);
	} while (Judge_Input(eNum));
	printf("\n");
	Dfs_Print(g, sNum - 1, eNum - 1);
}

/*�ཨ���������·��*/
void BestPath(mgraphtype *g) {
	int vNum[M] = { 0 }, j = 1;                                       /*��¼�û�����ı����Ϣ*/
	int d = 0;                                                        /*ͳ��ȫ���ܳ�*/
	printf("\n��������Ҫ�����ĵ�%d�������ı�ţ�����-1�������룩��", j);
	scanf("%d", &vNum[j - 1]);
	while (vNum[j - 1] != -1 && j < 12) {
		while (Judge_Input(vNum[j - 1])) {
			printf("\n��������Ҫ�����ĵ�%d��������ţ�", j);
			scanf("%d", &vNum[j - 1]);
		}
		if (vNum[j - 1] == -1) break;
		printf("\n��������Ҫ�����ĵ�%d��������ţ�", ++j);
		scanf("%d", &vNum[j - 1]);
	}
	printf("\n������ѷ���·����");
	for (int i = 0; vNum[i] > 0 && vNum[i + 1] > 0; i++) {
		printf("%s->", g->vexs[vNum[i] - 1].name);                   /*���·���ϵ����*/
		Floyd_Print(g, vNum[i] - 1, vNum[i + 1] - 1);                /*����Floyd�㷨*/
		d += dist[vNum[i] - 1][vNum[i + 1] - 1];
	}
	printf("%s\n\n", g->vexs[vNum[j - 2] - 1].name);                 /*���·���ϵ��յ�*/
	printf("ȫ���ܳ�Ϊ��%dm\n\n", d);
}

/*���˵�*/
int menu() {
	int s;
	printf("\t\t            ��------------------------------------------��           \n");
	printf("\t\t           ��---- ��ӭʹ�����������ѧУ԰������ѯϵͳ --��          \n");
	printf("\t\t            ��------------------------------------------��           \n");
	printf("\t\t                                                                      \n");
	printf("\t\t                                                                      \n");
	printf("\t\t   ��------------------------��        ��------------------------��   \n");
	printf("\t\t   �� 1.�����У��������Ϣ   ��        �� 2.�����������·����ѯ ��   \n");
	printf("\t\t   ��------------------------��        ��------------------------��   \n");
	printf("\t\t                                                                      \n");
	printf("\t\t   ��------------------------��        ��------------------------��   \n");
	printf("\t\t   �� 3.������������·����ѯ ��        �� 4.�ཨ�������·�߲�ѯ ��   \n");
	printf("\t\t   ��------------------------��        ��------------------------��   \n");
	printf("\t\t                                                                      \n");
	printf("\t\t   ��------------------------��        ��------------------------��   \n");
	printf("\t\t   �� 5.������               ��        �� 6.�˳�У԰������ѯϵͳ ��   \n");
	printf("\t\t   ��------------------------��        ��------------------------��   \n");


	printf("\t\t������������ѡ�������");
	scanf_s("%d", &s);
	printf("\n\n");
	return s;
}

/*��������*/
struct 
{
	int close;                                               //�����رյı��
	char name[20];                                           //��Ž���������
	char reason[100];                                        //��Ž����رյ�ԭ��
}Scenic_Manager[M];

void ScenicManager(mgraphtype *g)
{
	int n, i, no;
	system("cls"); Dis_Map();
	printf("������Ҫ�رյĽ������: ");
	scanf("%d", &no);
	if (no < 1 || no > 12)
	{
		printf("����ı�Ų���ȷ������������\n");
	}
	else
	{
		Scenic_Manager[no].close = INFINITY;
		strcpy(Scenic_Manager[no].name, g->vexs[no].name);//�����߸��Ƹ�ǰ��
		printf("\n");
		printf("�����뽨���رյ�ԭ��: \n");
		scanf("%s", Scenic_Manager[no].reason);
		printf("�����رճɹ���");
		printf("\n");
		Login_System();
	}
	
}

/*�ж�����ı���Ƿ����*/
int Judge_Input(int num)
{
	int i = 0;
	if (num == -1)
		return i;
	if (num < 1 || num>12)
	{
		printf("\n����ı������������1-12֮������֣�\n");
		i = 1;
	}
	else if(Scenic_Manager[num].close == INFINITY)
	{
		printf("\n�ý�����ʱ�رգ��޷�������\n");
		printf("\n");
		printf("�ر�ԭ��: %s\n", Scenic_Manager[num].reason);
		i = 1;
	}

	return i;
}

/*����Ա����*/
void Manager()
{
	int n, num, no, i;
	mgraphtype *g;
	int quit = 0;
	FILE * rf;
	rf = fopen("Information.txt", "r");
	char info[200];
	printf("\t\t               ��------------��         ��------------��               \n");
	printf("\t\t               �� 1.�������� ��         �� 2.�������� ��               \n");
	printf("\t\t               ��------------��         ��------------��               \n");
	printf("������Ҫѡ��ı��:\n");
	scanf("%d", &n);
		switch (n)
		{
		case 1:
			if (rf)
			{
				printf("����Ҫ�����Ĺ�����Ϣ��Ŀ: ");
				scanf("%d", &no);
				printf("\n");
				for (i = 1; i <= no; i++)
				{
					printf("�������%d��������Ϣ���: ", i);
					scanf("%d", &num);
					printf("\n");
					printf("�������%d��������Ϣ����: ", i);
					scanf("%s", info);
					printf("\n");
					fprintf(rf, "%d\n%s\n",num,info);
					printf("���淢���ɹ�!\n\n");
					printf("\n");
				}
			}
			fclose(rf);
			Manager();
			break;
		case 2:
			ScenicManager(&g);
			break;
		case -1:
			break;
		default:
			printf("\t\t\t\t\t����û�и�ѡ���Ӧ�Ĳ�����\n\n");
			break;
		}
}

/*�û���¼*/
int Login()
{
	int n = 1, num;
	char count[20] = "user";
	char password[20] = "123456";
	char count_input[20], password_input[20];
	printf("�������˺�:");
	scanf("%s", count_input);
	printf("\n");
	printf("����������:");
	scanf("%s", password_input);
	printf("\n");
	if ((strcmp(count, count_input) == 0) && (strcmp(password, password_input) == 0))
	{
		printf("��¼�ɹ�!\n");
		return n;
	}
	else printf("������˺Ż���������,����������!\n\n");
	Login();

}

/*���������ѧУ԰������ѯϵͳ��¼ϵͳ*/
int Login_System()
{
	int num = 0;
	printf("\t\t               ��----------------------------------------------------��                \n");
	printf("\t\t              ��--       ��ӭʹ�����������ѧУ԰������ѯϵͳ       --��               \n");
	printf("\t\t               ��----------------------------------------------------��                \n");
	printf("\t\t                                         ���¼                                          \n");
	printf("\t\t              ��----------------------��       ��----------------------��         \n");
	printf("\t\t              ��     1.����Ա��¼     ��       ��      2.�ο͵�¼      ��         \n");
	printf("\t\t              ��----------------------��       ��----------------------��         \n");
	printf("������Ҫѡ��ı��:\n");
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		system("cls"); Login(); Manager(); break;
	case 2:
		system("cls"); Login(); break;
	default:
		printf("\t\t\t\t\t����û�и�ѡ���Ӧ�Ĳ�����\n\n");
		break;
	}
	return 1;
}

/*������*/
void Information_print()
{
	FILE *rf;
	char a[100];
	int n,i;
	rf = fopen("Information.txt", "r");
	if (rf)
	{
		printf("������������:\n\n");
		for (i = 0;i < 2; i++)
		{
			fscanf(rf, "%d%s", &n, a);
			printf("%d:%s\n\n", n, a);
		}
	}
	fclose(rf);
}

/*�˳��˵���*/
void System_Exit(int *quit) {
	*quit = 1;
	printf("\t\t                ��-------------------------------------��                \n");
	printf("\t\t              ��----        ��ӭ�´�ʹ�ã�лл��      ---��              \n");
	printf("\t\t                ��-------------------------------------��                \n");
	printf("\t\t                  *             *******        *      *                   \n");
	printf("\t\t                  *            *               *      *                   \n");
	printf("\t\t                  *             *******        ********                   \n");
	printf("\t\t                  *                    *       *      *                   \n");
	printf("\t\t                  *******       *******        *      *                   \n");
}

/*������*/
void main() {
	int quit = 0;
	mgraphtype g;
	Create_Map(&g);                                                              /*���ļ���ȡ��Ϣ����ͼ*/
	ShortPath(&g);                                                               /*Floyd���dist��path*/
	if (Login_System()) {
		while (!quit) {                                                          /*ϵͳ�˳����������ж�*/
			switch (menu()) {                                                    /*��ӡ���˵�*/
			case 1:system("cls"); Dis_Map(); Search_Location(&g); break;         /*���������ѧУ԰������Ϣ��ѯ*/
			case 2:system("cls"); Dis_Map(); Shortpath_Print(&g); break;         /*�����������·����ѯ*/
			case 3:system("cls"); Dis_Map(); Allpath_Print(&g); break;           /*������������·����ѯ*/
			case 4:system("cls"); Dis_Map(); BestPath(&g); break;                /*�ཨ�������·�߲�ѯ*/
			case 5:system("cls"); Dis_Map(); Information_print(); break;         /*�������鿴*/
			case 6:system("cls"); System_Exit(&quit); break;                     /*�˳�У԰������ѯϵͳ*/
			default:printf("\t\t\t\t\t����û�и�ѡ���Ӧ�Ĳ�����\n\n");
			}
			system("pause");
			system("cls");                                                           /*����*/
		}
	}
}