#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <conio.h>

using namespace std;

char NameFile[30]; 
string start,end;			
int NumEdge = 0; // ����� ����� � �������� �������� 
int ActualNode;


int ReadFile(){
	setlocale(LC_ALL, "Russian");
	cout << "������� ��� ����� (.tgf)";cin >> NameFile;
	ifstream fin;
	fin.open(NameFile);
	if(!fin.is_open()){
		cout << "������" << endl;
		ReadFile();
		return 0;
	}
	int Quant = 0;
	string str = "";
	while(str != "#"){
		getline(fin,str);
		Quant++;
	}
	Quant--;
	fin.close();
	return Quant;
}

class Graf{
protected:
	bool **Matr; //������� ���������
	string *MasLabel; //������ ���� 
	int QuantNode; //���-�� �����
public:
	Graf(int q){
		QuantNode = q;
		MasLabel = new string[QuantNode];
		Matr = new bool*[QuantNode];
		for(int i = 0;i < QuantNode;i++){
			Matr[i] = new bool[QuantNode];
		}
		for(int i = 0;i < q;i++){
			for(int j = 0;j < q;j++){
				Matr[i][j] = 0;
			}
		}
	}
	
	void Enter(){
		cout << "  ";
		for(int i = 0;i < QuantNode;i++){
			cout << MasLabel[i] << " ";
		}
		cout << endl;
		for(int i = 0;i < QuantNode;i++){
			cout << MasLabel[i] << "|";
			for(int j = 0;j < QuantNode;j++){
				cout << Matr[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	int getQuantNode(){
		return QuantNode;
	}
	
	int getIndNode(string Name){
		int ind = -1;
		for(int i = 0;i < QuantNode;i++){
			if(Name == MasLabel[i]){
				ind = i;
			}
		}
		if(ind > -1){return ind;}
		cout << "���� � ������ "  << Name << " �� ������\n";
		exit(0);
	}
	
	string getNameNode(int ind){
			return MasLabel[ind];
	}
	
	void setEdge(int ind1, int ind2, bool val){
			Matr[ind1][ind2] = val;
	}
	
	void setNameNode(int ind, string Name){
			MasLabel[ind] = Name;
	}
	
	bool CheckEdge(int s, int f){
		if(Matr[s][f] == 1){
			return 1;
		}
		else{
			return 0;
		}
	}
	
	void ChangeEdge(){
		Enter();
		string NameStart,NameEnd; // ����� �����
		int s = -1,e = -1; // ������� �����
		cout << "\n����� ����� ��������:.\n";
		cout << "������:"; cin >> NameStart;
		cout << "�����:"; cin >> NameEnd;
		s = getIndNode(NameStart);
		e = getIndNode(NameEnd);
		cout << "1)�������� �����\n2)������� �����\n3)�������� ���������� �����.\n(��� ������ ������� ����� ������ �������)\n";
		switch(getche()){
		case '1':// ���������� ����� 
			Matr[s][e] = 1;
			system("cls");
			cout << "����� (" << NameStart << "->" << NameEnd<< ") ����������.\n\n";
			break;
		case '2':// �������� �����
			Matr[s][e] = 0;
			system("cls");
			cout << "����� (" << NameStart << "->" << NameEnd << ") ��������.\n\n";
			break;
		case '3':// ��������� �����������
			system("cls");
			if(Matr[s][e] == 0){cout << "���� ���.\n\n";}
			else{
				Matr[s][e] = 0;
				Matr[e][s] = 1;
				cout << "����������� ���������.\n\n";
			}
			break;
		}
	}
	
	void AddNode(){
		string NameNewNode;// ��� ����
		cout << "\n������� ��� ����:"; cin >> NameNewNode;
		bool BufMatr[QuantNode][QuantNode];// ����� �������
		string BufMasLabel[QuantNode];// ����� �������
		for(int i = 0; i < QuantNode;i++){ // �������� �������� ������� ���� � �������
			BufMasLabel[i] = MasLabel[i];
			for(int j = 0; j < QuantNode;j++){
				BufMatr[i][j] = Matr[i][j];	
			}
		}
		for(int i = 0; i < QuantNode;i++){ // ������� �������
			delete [] Matr[i];
		}
		delete [] MasLabel;// ������� ������
		
		QuantNode++;// ����������� �� 1 ���-�� �����
		MasLabel = new string[QuantNode];// ������� ����� ������
		Matr = new bool*[QuantNode];// ������� ����� �������
		for(int i = 0;i < QuantNode;i++){
			Matr[i] = new bool[QuantNode];
		}
		// ���������� �������� �� ������ ������� � �����
		for(int i = 0; i < QuantNode;i++){
			if(i < QuantNode-1){
				MasLabel[i] = BufMasLabel[i];
			}
			else{
				MasLabel[i] = NameNewNode;
			}
			for(int j = 0; j < QuantNode;j++){
				if(i < QuantNode-1 && j < QuantNode-1){
					Matr[i][j] = BufMatr[i][j];	
				}
				else{
					Matr[i][j] = 0;
				}	
			}
		}
	}
	
	void DeleteNode(){
		string NameNode;// ��� ����
		int IndNode;
		bool flag = 0;
		cout << "\n������� ��� ����:"; cin >> NameNode;
		for(int i = 0;i < QuantNode;i++){// ����� �������� �����
			if(MasLabel[i] == NameNode){flag = 1;IndNode = i;}
		}
		if(!flag){
			cout << "���� �� ������.\n\n";
			return;
		}
		bool BufMatr[QuantNode][QuantNode];// ����� �������
		string BufMasLabel[QuantNode];// ����� �������
		for(int i = 0; i < QuantNode;i++){ // �������� �������� ������� ���� � �������
			BufMasLabel[i] = MasLabel[i];
			for(int j = 0; j < QuantNode;j++){
				BufMatr[i][j] = Matr[i][j];	
			}
		}
		for(int i = 0; i < QuantNode;i++){ // ������� �������
			delete [] Matr[i];
		}
		delete [] MasLabel;// ������� ������
		
		QuantNode--;// ��������� �� 1 ���-�� �����
		MasLabel = new string[QuantNode];// ������� ����� ������
		Matr = new bool*[QuantNode];// ������� ����� �������
		for(int i = 0;i < QuantNode;i++){
			Matr[i] = new bool[QuantNode];
		}
		// ���������� �������� �� ������ ������� � �����
		int k = 0;
		for(int i = 0; i <= QuantNode;i++){
			if(i != IndNode){
				MasLabel[k] = BufMasLabel[i];
				int  d = 0;
				for(int j = 0; j <= QuantNode;j++){
					if(j != IndNode){
						Matr[k][d] = BufMatr[i][j];	
						d++;	
					}
				}
				k++;	
			}	
		}
	}
};

Graf ObjGraf(ReadFile());

class Way{
private:
	struct NodeWay{
		int nod;
		NodeWay *next;
	};
	typedef NodeWay *PWay;
	PWay Head = NULL;
	
public:
	PWay getHead(){
		return Head;
	}
	PWay CreateWay(int NewInd){
		PWay NewWay = new NodeWay;
		NewWay->nod = NewInd;
		NewWay->next = NULL;
		return NewWay;
	}
	
	void AddAfter(PWay p,PWay NewWay){
		NewWay->next = p->next;
		p->next = NewWay;
	}

	void AddFirst(PWay NewWay){
		NewWay->next = Head;
		Head = NewWay;
	}

	void AddLast(PWay NewWay){
		if(Head == NULL){
			AddFirst(NewWay);
			return;
		}
		PWay q = Head;
		while(q->next) q = q->next;
		AddAfter(q,NewWay);
	}
	
	int BackWay(){
		PWay q = Head;
		PWay p = Head->next;
		if(p != NULL){
			while(p->next) {
				q = q->next;
				p = p->next;
			}
			q->next = NULL;
			return q->nod;
		}
		else {
			Head = NULL;
			return 0;
		}
	}
	
	void EnterSpis(){
		PWay q = Head;
	 	while(q != NULL){
			cout << ObjGraf.getNameNode(q->nod) <<"->"; 
			q= q->next;	
		}
		cout << end <<endl;
	}
	
	bool CheckNode(int N){
		PWay q = Head;
		while(q != NULL){
			if(q->nod == N) {
				return true;
			}
			q = q->next;
		}
		return false;
	}
	
	int getLast(){
		PWay q = Head;
		PWay p = q->next;
		if(p != NULL){
			while(p->next) {
			q = q->next;
			p = p->next;
			}
		}
		return q->nod;
	}	
	
	void operator +(PWay NewWay){
		if(Head == NULL){
			AddFirst(NewWay);
			return;
		}
		PWay q = Head;
		while(q->next) q = q->next;
		AddAfter(q,NewWay);
	}
};

Way ObjWay;

void Fill(char NameF[] , int QuantNode){
		ifstream fin;
		fin.open(NameF);
		string str;
		for(int i = 0;i < QuantNode;i++){
			fin >> str;
			fin >> str;
			ObjGraf.setNameNode(i,str);
		}
		fin >> str;
		int buf1,buf2;
		while(fin >> buf1 && fin >> buf2){
			ObjGraf.setEdge(buf1 - 1, buf2 - 1, 1);
		}
		fin.close();	
	}

void SearchWay(int NEdge, int lM){
	for(int i = NEdge;i < lM;i++){
		if(ObjGraf.CheckEdge(ActualNode,i)){
			if(ActualNode == i || i == ObjWay.getLast() || ObjWay.CheckNode(i)){/*"�������"*/}
			else if(i == ObjGraf.getIndNode(end)){
			ObjWay.EnterSpis();
			}
			else{
				ActualNode = i; //��������� � �����
				ObjWay + ObjWay.CreateWay(i); // ���������� �������
				NumEdge = 0; //�������� � 0 �����
				return;
			}
		}
	}
	NumEdge = ActualNode + 1;// �������� � ����� ����� �����������
	ActualNode = ObjWay.BackWay();	// ���������� ������� ����
}	

void First(){
	string f = ObjGraf.getNameNode(1);
	cout << "����� ������ �������:" << ObjGraf.getIndNode(f) << endl; 
}

void Next(string v, int i){
	int ind = ObjGraf.getIndNode(v);
	for(int j = i; j < ObjGraf.getQuantNode();j++){
		if(ObjGraf.CheckEdge(ind,j)){
			cout << "������ ������� �������:" << j << endl;
			return;
		}
	}
}

void Vertex(string v,int i){
	int ind = ObjGraf.getIndNode(v);
	if(ObjGraf.CheckEdge(ind,i)){
		cout << "�������:" << ObjGraf.getNameNode(i) << endl;
	}
}

int main() {
    //setlocale(LC_ALL,"Rus");
    
	string V;
	int I;	
	Fill(NameFile,ObjGraf.getQuantNode());
	while(true){
		ObjGraf.Enter();
		cout << "1)����� ��� ������� ����.\n2)��������� �����.\n3)�������� ����.\n4)������� ����.\n5)FIRST\n6)NEXT\n7)VERTEX\n0)�����.\n";
		switch(getche()){
			case '1':
				cout << "������ ����:"; cin >> start;
				cout << "����� ����:"; cin >> end;
				system("cls");
				ActualNode = ObjGraf.getIndNode(start); //�������������� ����
				ObjWay + ObjWay.CreateWay(ActualNode); //���������� ���� � ������
				NumEdge = 0;
				while(ObjWay.getHead() != NULL){
					SearchWay(NumEdge,ObjGraf.getQuantNode());
				}
				break;
				
			case '2':
				system("cls");
				ObjGraf.ChangeEdge();
				break;
			case '3':
				system("cls");
				ObjGraf.AddNode();
				break;
			case '4':
				system("cls");
				ObjGraf.DeleteNode();
				break;
			case '5':
				system("cls");
				First();
				break;
			case '6':
				system("cls");
				cout << "������� �������:";cin >> V;
				cout << "������� ������:";cin >> I;
				Next(V,I);
				break;
			case '7':
				system("cls");
				cout << "������� �������:";cin >> V;
				cout << "������� ������:";cin >> I;
				Vertex(V,I);
				break;
			case '0':
				exit(0);
				break;	
		}
	}
	system("pause");
}
