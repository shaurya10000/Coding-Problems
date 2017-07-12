// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "list"
#include "vector"
using namespace std;
#define N 9

class Cell
{
	int val = 0;
	int x, y;
	int bitNums = 0x01ff;// all nums are possible
public:
	/*Cell(int x, int y): x(x), y(y){}
	Cell(int v, int x, int y) :val(v), x(x), y(y){
		bitNums = 1 << v;
	}*/
	int GetX(){ return x; }
	int GetY(){ return y; }
	void Initialize(int i, int j, int v)
	{
		val = v;
		if (v != 0)
			bitNums = 1 << (v-1);
		//else
		//using default value
		x = i;
		y = j;
	}
	vector<int> PossibleNums()
	{
		vector<int> vec;
		int k = 0;
		while (k < N)
		{
			if ((bitNums >> k) & 1)
				vec.push_back(k + 1);
			k++;
		}
		return vec;
	}
	int RetVal()
	{
		return val;
	}
	void Update(int v = 0)
	{
		if (v == 0)
			val = GetTheVal();
		else
			val = v;
	//	if (x == 8 && (y == 1 || y == 2))
	//		while (1);
	//	if (x == 5 && y == 1)
	//		while (1);
		bitNums = 1 << (val-1);
	}
	void RemoveNum(int v)
	{
		bitNums &= ~(1 << (v-1));
	}
	int PossibleValueCount()
	{
		int count = 0;
		int val = bitNums;
		while (val)
		{
			if (val & 0x1)
				count++;
			val >>= 1;
		}
		return count;
	}
	bool IsSolved()
	{
		return val != 0;
	}
	int GetTheVal()
	{
		int num = 0;
		if (PossibleValueCount() == 1)
		{
			int val = bitNums;
			while (val)
			{
				num++;
				if (val & 0x1)
					break;
				val >>= 1;
			}
		}
		//else
		//error condition

		return num;
	}
	void SetRemNums(int v)
	{
		bitNums = 1 << (v - 1);
	}
};

class Game
{
	int knownCount = 0;
	Cell c[N][N];
	list<Cell *> cellsUpdated;
	list<pair<Cell *, int> > cellsForUpdation;

public:
	Game()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int num = 0;
				cin >> num;
				c[i][j].Initialize(i,j,num);
				if (num != 0)
				{
					knownCount++;
				}
			}
		}

		//cout << endl;
		//PrintSolution();
		//cout << endl;
	};
	void UpdateCell(int x, int y, int v);
	void UpdateRowForVal(int x, int y, int v);
	void UpdateColumnForVal(int x, int y, int v);
	void UpdateSquareForVal(int x, int y, int v);
	int StartGame();
	void PrintSolution();
	void PrintState();
	bool ProcessUniquePossibleNumbers();
};

void Game::UpdateCell(int x, int y, int v)
{
	for (int i = 0; i < N; i++)
	{
		if (c[x][i].IsSolved() == false)
		{
			c[x][i].RemoveNum(v);
			if (c[x][i].PossibleValueCount() == 1)
			{
				c[x][i].Update(c[x][i].GetTheVal());
				knownCount++;
				cellsUpdated.push_back(&c[x][i]);
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		if (c[i][y].IsSolved() == false)
		{
			c[i][y].RemoveNum(v);
			if (c[i][y].PossibleValueCount() == 1)
			{
				c[i][y].Update(c[i][y].GetTheVal());
				knownCount++;
				cellsUpdated.push_back(&c[i][y]);
			}
		}
	}
	UpdateSquareForVal(x, y, v);
}

void Game::PrintState()
{
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			cout << "(" << x << ", " << y << ") ";
			vector<int> vec = c[x][y].PossibleNums();
			for (auto it = vec.begin(); it != vec.end(); it++)
				cout << *it << ", ";
			cout << "  " << endl;
		}
		cout << endl;
	}
}

bool Game::ProcessUniquePossibleNumbers()
{
	int initVal = knownCount;
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			int arr[N];
			for (int i = 0; i < N; i++)
			{
				arr[i] = 0;
			}
			for (int i = 0; i < N; i++)
			{
				if (c[x][i].IsSolved() == false)
				{
					vector<int> vec = c[x][i].PossibleNums();
					for (auto it = vec.begin(); it != vec.end(); it++)
					{
						arr[*it - 1]++;
					}
				}
			}
			for (int i = 0; i < N; i++)
			{
				if (arr[i] == 1)
				{
					for (int j = 0; j < N; j++)
					{
						if (c[x][j].IsSolved() == false)
						{
							vector<int> vec = c[x][j].PossibleNums();
							for (auto it = vec.begin(); it != vec.end(); it++)
							{
								if (*it == i + 1)
								{
									c[x][j].Update(i + 1);
									c[x][j].SetRemNums(i + 1);// just for sanity
									knownCount++;
									cellsUpdated.push_back(&c[x][j]);
									return initVal != knownCount;
									//UpdateCell(x, j, i+1);
								}
							}
						}
					}
				}
			}
					
			for (int i = 0; i < N; i++)
			{
				arr[i] = 0;
			}
			for (int i = 0; i < N; i++)
			{
				if (c[i][y].IsSolved() == false)
				{
					vector<int> vec = c[i][y].PossibleNums();
					for (auto it = vec.begin(); it != vec.end(); it++)
						arr[*it - 1]++;
				}
			}
			for (int i = 0; i < N; i++)
			{
				if (arr[i] == 1)
				{
					for (int j = 0; j < N; j++)
					{
						if (c[j][y].IsSolved() == false)
						{
							vector<int> vec = c[j][y].PossibleNums();
							for (auto it = vec.begin(); it != vec.end(); it++)
							{
								if (*it == i + 1)
								{
									c[j][y].Update(i + 1);
									c[j][y].SetRemNums(i + 1);// just for sanity
									knownCount++;
									cellsUpdated.push_back(&c[j][y]);
									return initVal != knownCount;
									//UpdateCell(j, y, i + 1);
								}
							}
						}
					}
				}
			}

							for (int i = 0; i < N; i++)
							{
								arr[i] = 0;
							}
							int i0 = x - (x % 3);
							int j0 = y - (y % 3);
							for (int i = i0; i < i0 + 3; i++)
							{
								for (int j = j0; j < j0 + 3; j++)
								{
									if (c[i][j].IsSolved() == false)
									{
										vector<int> vec = c[i][j].PossibleNums();
										for (auto it = vec.begin(); it != vec.end(); it++)
											arr[*it - 1]++;
									}
								}
							}

							for (int k = 0; k < N; k++)
							{
								if (arr[k] == 1)
								{
									for (int i = i0; i < i0 + 3; i++)
									{
										for (int j = j0; j < j0 + 3; j++)
										{
											if (c[i][j].IsSolved() == false)
											{
												vector<int> vec = c[i][j].PossibleNums();
												for (auto it = vec.begin(); it != vec.end(); it++)
												{
													if (*it == k + 1)
													{
														c[i][j].Update(k + 1);
														c[i][j].SetRemNums(k + 1);// just for sanity
														knownCount++;
														cellsUpdated.push_back(&c[i][j]);
														return initVal != knownCount;
														//UpdateCell(i, j, k + 1);
													}
												}
											}
										}
									}
								}
							}
							//PrintState();
						}
						
					}
	return initVal != knownCount;//found some new cells
}
int Game::StartGame()
{
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (c[x][y].IsSolved() == false)
			{
				for (int k = 0; k < N; k++)
				{
					if (c[x][k].IsSolved() == true)
						c[x][y].RemoveNum(c[x][k].RetVal());
					if (c[k][y].IsSolved() == true)
						c[x][y].RemoveNum(c[k][y].RetVal());
				}
				int i0 = x - (x % 3);
				int j0 = y - (y % 3);
				for (int i = i0; i < i0 + 3; i++)
				{
					for (int j = j0; j < j0 + 3; j++)
					{
						if (c[i][j].IsSolved() == true)
							c[x][y].RemoveNum(c[i][j].RetVal());
					}
				}
			/*	cout << "(" << x << ", " << y << ") ";
				vector<int> vec = c[x][y].PossibleNums();
				for (auto it = vec.begin(); it != vec.end(); it++)
					cout << *it << ", ";
				cout << endl;*/
			}
		}
	}


	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (c[x][y].IsSolved() == 0 && c[x][y].PossibleValueCount() == 1)
			{
				c[x][y].Update(c[x][y].GetTheVal());
				knownCount++;
				cellsUpdated.push_back(&c[x][y]);
			}
		}
	}

		do
		{
			if (!cellsUpdated.empty())
			{
				auto cell = cellsUpdated.front();
				cellsUpdated.pop_front();
				UpdateCell(cell->GetX(), cell->GetY(), cell->GetTheVal());
			}
			else
			{
				//PrintSolution();
				if (ProcessUniquePossibleNumbers() == false)
					break;
			}
		} while (knownCount < N * N);

	//PrintState();

	return knownCount == N * N;
}

void Game::PrintSolution()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << c[i][j].RetVal() << "  ";
		}
		cout << endl;
	}
}

void Game::UpdateSquareForVal(int x, int y, int v)
{
	int i0 = x - (x % 3);
	int j0 = y - (y % 3);
	for (int i = i0; i < i0 + 3; i++)
	{
		for (int j = j0; j < j0 + 3; j++)
		{
			if (c[i][j].IsSolved() == false)
			{
				c[i][j].RemoveNum(v);
				if (c[i][j].PossibleValueCount() == 1)
				{
					c[i][j].Update(c[i][j].GetTheVal());
					knownCount++;
					cellsUpdated.push_back(&c[i][j]);
				}
			}
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	Game gm;
	
	gm.StartGame();
	gm.PrintSolution();

	getchar();
	getchar();
	return 0;
}
