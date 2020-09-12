#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <conio.h>

using namespace std;

char NameFile[30]; 
string start,end;			
int NumEdge = 0; // Номер ребра с которого начинаем 
int ActualNode;


int ReadFile(){
	setlocale(LC_ALL, "Russian");
	cout << "Введите имя файла (.tgf)";cin >> NameFile;
	ifstream fin;
	fin.open(NameFile);
	if(!fin.is_open()){
		cout << "Ошибка" << endl;
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
	bool **Matr; //Матрица смежности
	string *MasLabel; //Массив имен 
	int QuantNode; //Кол-во узлов
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
		cout << "Узел с именем "  << Name << " не найден\n";
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
		string NameStart,NameEnd; // Имена узлов
		int s = -1,e = -1; // Индексы узлов
		cout << "\nКакое ребро изменьть:.\n";
		cout << "Начало:"; cin >> NameStart;
		cout << "Конец:"; cin >> NameEnd;
		s = getIndNode(NameStart);
		e = getIndNode(NameEnd);
		cout << "1)Добавить ребро\n2)Удалить ребро\n3)Изменить напрвление ребра.\n(Для выхода нажмите любую другую клавишу)\n";
		switch(getche()){
		case '1':// Добавление ребра 
			Matr[s][e] = 1;
			system("cls");
			cout << "Ребро (" << NameStart << "->" << NameEnd<< ") добавленно.\n\n";
			break;
		case '2':// Удаление ребра
			Matr[s][e] = 0;
			system("cls");
			cout << "Ребро (" << NameStart << "->" << NameEnd << ") удаленно.\n\n";
			break;
		case '3':// Изменение направления
			system("cls");
			if(Matr[s][e] == 0){cout << "Дуги нет.\n\n";}
			else{
				Matr[s][e] = 0;
				Matr[e][s] = 1;
				cout << "Направление измененно.\n\n";
			}
			break;
		}
	}
	
	void AddNode(){
		string NameNewNode;// Имя узла
		cout << "\nВведите имя узла:"; cin >> NameNewNode;
		bool BufMatr[QuantNode][QuantNode];// Копия матрицы
		string BufMasLabel[QuantNode];// Копия массива
		for(int i = 0; i < QuantNode;i++){ // Копируем значения массива имен и матрицы
			BufMasLabel[i] = MasLabel[i];
			for(int j = 0; j < QuantNode;j++){
				BufMatr[i][j] = Matr[i][j];	
			}
		}
		for(int i = 0; i < QuantNode;i++){ // Удаляем матрицу
			delete [] Matr[i];
		}
		delete [] MasLabel;// Удаляем массив
		
		QuantNode++;// Увеличиваем на 1 кол-во узлов
		MasLabel = new string[QuantNode];// Создаем новый массив
		Matr = new bool*[QuantNode];// Создаем новую матрицу
		for(int i = 0;i < QuantNode;i++){
			Matr[i] = new bool[QuantNode];
		}
		// Записываем значения из старой матрицы в новую
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
		string NameNode;// Имя узла
		int IndNode;
		bool flag = 0;
		cout << "\nВведите имя узла:"; cin >> NameNode;
		for(int i = 0;i < QuantNode;i++){// Поиск индексов узлов
			if(MasLabel[i] == NameNode){flag = 1;IndNode = i;}
		}
		if(!flag){
			cout << "Узел не найден.\n\n";
			return;
		}
		bool BufMatr[QuantNode][QuantNode];// Копия матрицы
		string BufMasLabel[QuantNode];// Копия массива
		for(int i = 0; i < QuantNode;i++){ // Копируем значения массива имен и матрицы
			BufMasLabel[i] = MasLabel[i];
			for(int j = 0; j < QuantNode;j++){
				BufMatr[i][j] = Matr[i][j];	
			}
		}
		for(int i = 0; i < QuantNode;i++){ // Удаляем матрицу
			delete [] Matr[i];
		}
		delete [] MasLabel;// Удаляем массив
		
		QuantNode--;// Уменьшаем на 1 кол-во узлов
		MasLabel = new string[QuantNode];// Создаем новый массив
		Matr = new bool*[QuantNode];// Создаем новую матрицу
		for(int i = 0;i < QuantNode;i++){
			Matr[i] = new bool[QuantNode];
		}
		// Записываем значения из старой матрицы в новую
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
			if(ActualNode == i || i == ObjWay.getLast() || ObjWay.CheckNode(i)){/*"Пропуск"*/}
			else if(i == ObjGraf.getIndNode(end)){
			ObjWay.EnterSpis();
			}
			else{
				ActualNode = i; //Переходим в перед
				ObjWay + ObjWay.CreateWay(i); // Записываем переход
				NumEdge = 0; //Начинаем с 0 ребра
				return;
			}
		}
	}
	NumEdge = ActualNode + 1;// Начинаем с ребра после предедущего
	ActualNode = ObjWay.BackWay();	// Записываем прошлый узел
}	

void First(){
	string f = ObjGraf.getNameNode(1);
	cout << "Идекс первой вершины:" << ObjGraf.getIndNode(f) << endl; 
}

void Next(string v, int i){
	int ind = ObjGraf.getIndNode(v);
	for(int j = i; j < ObjGraf.getQuantNode();j++){
		if(ObjGraf.CheckEdge(ind,j)){
			cout << "Индекс смежной вершины:" << j << endl;
			return;
		}
	}
}

void Vertex(string v,int i){
	int ind = ObjGraf.getIndNode(v);
	if(ObjGraf.CheckEdge(ind,i)){
		cout << "Вершина:" << ObjGraf.getNameNode(i) << endl;
	}
}

int main() {
    //setlocale(LC_ALL,"Rus");
    
	string V;
	int I;	
	Fill(NameFile,ObjGraf.getQuantNode());
	while(true){
		ObjGraf.Enter();
		cout << "1)Найти все простые пути.\n2)Изменение ребер.\n3)Добавить узел.\n4)Удалить узел.\n5)FIRST\n6)NEXT\n7)VERTEX\n0)Выход.\n";
		switch(getche()){
			case '1':
				cout << "Начало пути:"; cin >> start;
				cout << "Конец пути:"; cin >> end;
				system("cls");
				ActualNode = ObjGraf.getIndNode(start); //Расматриваемый узел
				ObjWay + ObjWay.CreateWay(ActualNode); //Записываем узел в начало
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
				cout << "Введите вершину:";cin >> V;
				cout << "Введите индекс:";cin >> I;
				Next(V,I);
				break;
			case '7':
				system("cls");
				cout << "Введите вершину:";cin >> V;
				cout << "Введите индекс:";cin >> I;
				Vertex(V,I);
				break;
			case '0':
				exit(0);
				break;	
		}
	}
	system("pause");
}
