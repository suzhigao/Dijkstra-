#pragma once
//#pragma once��һ���Ƚϳ��õ�C/C++��ע��
//ֻҪ��ͷ�ļ����ʼ����������ע��
//���ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

#include<iostream>
#include<string>

using namespace std;

/*
��������ʹ��Dijkstra�㷨ʵ��������·��������
���õ��ڽӾ������洢ͼ
*/
//��¼��㵽ÿ����������·������Ϣ
struct Dis {
	string path;
	int value;
	bool visit;
	Dis() {
		visit = false;
		value = 0;
		path = "";
	}
};

class Graph_DG {
private:
	int vexnum;   //ͼ�Ķ������
	int edge;     //ͼ�ı���
	int** arc;   //�ڽӾ���
	Dis* dis;   //��¼�����������·������Ϣ
public:
	//���캯��
	Graph_DG(int vexnum, int edge);
	//��������
	~Graph_DG();
	// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
	//�����1��ʼ���
	bool check_edge_value(int start, int end, int weight);
	//����ͼ
	void createGraph();
	//��ӡ�ڽӾ���
	void print();
	//�����·��
	void Dijkstra(int begin);
	//��ӡ���·��
	void print_path(int);
};


//���캯��
Graph_DG::Graph_DG(int vexnum, int edge) {
	//��ʼ���������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
	arc = new int* [this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//�ڽӾ����ʼ��Ϊ�����
			arc[i][k] = INT_MAX;
		}
	}
}
//��������
Graph_DG::~Graph_DG() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
}

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

void Graph_DG::createGraph() {
	cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//�����жϱߵ���Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		//���ڽӾ����Ӧ�ϵĵ㸳ֵ
		arc[start - 1][end - 1] = weight;
		//����ͼ��������д���
		//arc[end - 1][start - 1] = weight;
		++count;
	}
}

void Graph_DG::print() {
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0; //��ӡ�еı�ǩ
	int count_col = 0; //��ӡ�еı�ǩ
	//��ʼ��ӡ
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)
				cout << "��" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

void Graph_DG::Dijkstra(int begin) {
	//���ȳ�ʼ�����ǵ�dis����
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//���õ�ǰ��·��
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	//�������ĵ�����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value < min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
			}
		}
	}

}

void Graph_DG::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);

	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ��" << endl;

	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << dis[i].path << "�������·����" << endl;
		}
	}
}


//������������Ͷ�������ֵ�Ƿ���Ч�������Լ�����Ϊɶ��
//�������ͱ����Ĺ�ϵ�ǣ�((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
	if (Vexnum <= 0 || edge <= 0 || ((Vexnum * (Vexnum - 1)) / 2) < edge)
		return false;
	return true;
}
int main() {
	int vexnum; int edge;

	cout << "����ͼ�Ķ�������ͱߵ�������" << endl;
	cin >> vexnum >> edge;

	while (!check(vexnum, edge)) {
		cout << "�������ֵ���Ϸ�������������" << endl;
		cin >> vexnum >> edge;
	}

	Graph_DG graph(vexnum, edge);
	graph.createGraph();
	graph.print();
	graph.Dijkstra(1);
	graph.print_path(1);
	system("pause");

	return 0;
}