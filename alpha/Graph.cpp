#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

/* 邻接矩阵 */
struct Graph1
{
	int * vex;
	int ** arc;
	int vexnum;
	int arcnum;
};

struct ArcNode2
{
	int index;
	int weight;
	ArcNode2 * next;
};

struct VexNode2
{
	int data;
	ArcNode2 * firstin;
	ArcNode2 * firstout;
};

/* 邻接链表 */
struct Graph2
{
	VexNode2 * vex;
	int vexnum;
	int arcnum;
};

struct ArcNode3
{
	int begin;
	int end;
	int weight;
	bool operator<(const ArcNode3 & a) const
	{
		return weight < a.weight;
	}
	bool operator>(const ArcNode3 & a) const
	{
		return weight > a.weight;
	}
};

/* 边集数组 */
struct Graph3
{
	ArcNode3 * arc;
	int vexnum;
	int arcnum;
};

/* 广度优先搜索 */
bool BFS(const Graph1 & G, int i)
{
	bool * flag = new bool[G.vexnum];
	std::fill(flag, flag + G.vexnum, false);
	flag[i] = true;
	std::cout << G.vex[i] << std::endl;
	std::queue<int> q;
	q.push(i);
	while (!q.empty())
	{
		i = q.front();
		q.pop();
		for (int j = 0; j < G.vexnum; j++)
		{
			if (!flag[j] && G.arc[i][j] != 0)
			{
				flag[j] = true;
				std::cout << G.vex[j] << std::endl;
				q.push(j);
			}
		}
	}
	int temp = std::count(flag, flag + G.vexnum, false);
	delete[] flag;
	return temp == 0;
}

/* 广度优先搜索 */
bool BFS(const Graph2 & G, int i)
{
	bool * flag = new bool[G.vexnum];
	std::fill(flag, flag + G.vexnum, false);
	flag[i] = true;
	std::cout << G.vex[i].data << std::endl;
	std::queue<int> q;
	q.push(i);
	while (!q.empty())
	{
		i = q.front();
		q.pop();
		for (ArcNode2 * p = G.vex[i].firstout; p != nullptr; p = p->next)
		{
			if (!flag[p->index])
			{
				flag[p->index] = true;
				std::cout << G.vex[p->index].data << std::endl;
				q.push(p->index);
			}
		}
	}
	int temp = std::count(flag, flag + G.vexnum, false);
	delete[] flag;
	return temp == 0;
}

/* 深度优先搜索 */
bool DFS(const Graph1 & G, int i)
{
	bool * flag = new bool[G.vexnum];
	std::fill(flag, flag + G.vexnum, false);
	flag[i] = true;
	std::cout << G.vex[i] << std::endl;
	std::stack<int> s;
	s.push(i);
	while (!s.empty())
	{
		i = s.top();
		s.pop();
		for (int j = 0; j < G.vexnum; j++)
		{
			if (!flag[j] && G.arc[i][j] != 0)
			{
				flag[j] = true;
				std::cout << G.vex[j] << std::endl;
				s.push(i);
				s.push(j);
				break;
			}
		}
	}
	int temp = std::count(flag, flag + G.vexnum, false);
	delete[] flag;
	return temp == 0;
}

/* 深度优先搜索 */
bool DFS(const Graph2 & G, int i)
{
	bool * flag = new bool[G.vexnum];
	std::fill(flag, flag + G.vexnum, false);
	flag[i] = true;
	std::cout << G.vex[i].data << std::endl;
	std::stack<int> s;
	s.push(i);
	while (!s.empty())
	{
		i = s.top();
		s.pop();
		for (ArcNode2 * p = G.vex[i].firstout; p != nullptr; p = p->next)
		{
			if (!flag[p->index])
			{
				flag[p->index] = true;
				std::cout << G.vex[p->index].data << std::endl;
				s.push(i);
				s.push(p->index);
				break;
			}
		}
	}
	int temp = std::count(flag, flag + G.vexnum, false);
	delete[] flag;
	return temp == 0;
}

/* 最小生成树 */
int Prim(const Graph1 & G, int v)
{
	int sum = 0;
	int * lowcost = new int[G.vexnum];
	int * adjvex = new int[G.vexnum];
	for (int i = 0; i < G.vexnum; i++)
	{
		lowcost[i] = G.arc[v][i];
		adjvex[i] = v;
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		int min = INT_MAX;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				v = j;
			}
		}
		std::cout << v << '\t' << adjvex[v] << std::endl;
		sum += lowcost[v];
		lowcost[v] = 0;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < G.arc[v][j])
			{
				lowcost[j] = G.arc[v][j];
				adjvex[j] = v;
			}
		}
	}
	delete[] adjvex;
	delete[] lowcost;
	return sum;
}

/* 最小生成树 */
int Kruskal(const Graph3 & G)
{
	int sum = 0;
	int * s = new int[G.vexnum];
	std::fill(s, s + G.vexnum, -1);
	std::priority_queue<ArcNode3, std::vector<ArcNode3>, std::greater<ArcNode3>> q;
	for (int i = 0; i < G.arcnum; i++)
	{
		q.push(G.arc[i]);
	}
	while (!q.empty())
	{
		ArcNode3 a = q.top();
		q.pop();
		int x = a.begin;
		int y = a.end;
		while (s[x] != -1) x = s[x];
		while (s[y] != -1) y = s[y];
		if (x != y)
		{
			std::cout << x << '\t' << y << std::endl;
			s[x] = y;
			sum += a.weight;
		}
	}
	delete[] s;
	return sum;
}

/* 单源最短路径 */
void Dijkstra(const Graph1 & G, int v, int * path, int * length)
{
	bool * flag = new bool[G.vexnum];
	std::fill(flag, flag + G.vexnum, false);
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.arc[v][i] < INT_MAX) path[i] = v;
		else path[i] = -1;
		length[i] = G.arc[v][i];
	}
	flag[v] = true;
	path[v] = -1;
	for (int i = 1, k; i < G.vexnum; i++)
	{
		int min = INT_MAX;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (!flag[j] && path[j] < min)
			{
				min = path[j];
				k = j;
			}
		}
		flag[k] = true;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (!flag[j] && length[k] + G.arc[k][j] < length[j])
			{
				length[j] = length[k] + G.arc[k][j];
				path[j] = k;
			}
		}
	}
	delete[] flag;
}

/* 全源最短路径 */
void Floyd(const Graph1 & G, int ** path, int ** length)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; i++)
		{
			path[i][j] = -1;
			length[i][j] = G.arc[i][j];
		}
	}
	for (int k = 0; k < G.vexnum; k++)
	{
		for (int i = 0; i < G.vexnum; i++)
		{
			for (int j = 0; j < G.vexnum; j++)
			{
				if (length[i][k] + length[k][j] < length[i][j])
				{
					path[i][j] = k;
					length[i][j] = length[i][k] + length[k][j];
				}
			}
		}
	}
}

/* 拓扑排序 */
bool TopologicalSort(const Graph2 & G)
{
	int * degree = new int[G.vexnum];
	std::fill(degree, degree + G.vexnum, 0);
	for (int i = 0; i < G.vexnum; i++)
		for (ArcNode2 * p = G.vex[i].firstin; p != nullptr; p = p->next)
			degree[i]++;
	std::stack<int> s;
	for (int i = 0; i < G.vexnum; i++)
		if (degree[i] == 0)
			s.push(i);
	while (!s.empty())
	{
		int i = s.top();
		s.pop();
		std::cout << G.vex[i].data << std::endl;
		for (ArcNode2 * p = G.vex[i].firstout; p != nullptr; p = p->next)
			if (--degree[p->index])
				s.push(p->index);
	}
	int temp = std::count(degree, degree + G.vexnum, 0);
	delete[] degree;
	return temp == G.vexnum;
}

