#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <cstddef>
#include <new>
#include<cstdio>
#define numb_cards_expected 999
#define random_number 692
using namespace std;

enum kolor { g, e, r, v, y, w, k, o };

struct karta {
	kolor color;
	int value;
};

int count_spaces(char read[], int licznik, int end)
{
	for (int j = 0; j < end; j++)
	{
		if (read[j] == ' ')
		{
			licznik++;
		}
	}
	return licznik;
}

int set_j(char read[], int j)
{
	while ((int)read[j] < 48 || (int)read[j]>57) // ustawienie iteratora j na 1 liczbe poza liczba numeru gracza
	{
		j++;
	}
	return j;
}

void find_spaces(char* pointer, int l, int cnt, int tempp, int space[], char read[])
{
	pointer = strchr(read, ' ');
	while (l--)
	{
		tempp = pointer - read;

		space[cnt] = tempp;
		pointer = strchr(pointer + 1, ' ');      // spisanie lokalizacji spacji
		cnt++;
	}
}

int set_iterator(int j, int iterator, int space[])
{
	while (j > space[iterator] != 0)             // ustawienie iteratora na nastepna spacje 
	{
		++iterator;
	}
	return iterator;
}

int get_value(int tempv, int roznica, int iterator, int j, int indeks, int space[], int tempvalues[], char read[])
{
	tempv = 0;
	roznica = space[iterator] - j;     // wczytanie wartosci liczbowej karty z tekstu
	tempv = (int)read[j] - 48;
	--roznica;
	while (roznica--)
	{
		tempv *= 10;
		++j;
		tempv += (int)read[j] - 48;
	}
	tempvalues[indeks] = tempv;
	j++;
	return j;
}

int get_color(char first_let, int j, int iterator, int roznica, int indeks, kolor letters[], char read[], int space[], kolor unique, int unique_colors[])
{
	first_let = read[j];
	switch (first_let)
	{													// szczytanie i ustawienie koloru karty dla danego gracza w zaleznosci od linijki
	case 'g':
		j += 5;
		letters[indeks] = g;
		break;
	case 'r':
		j += 3;
		letters[indeks] = r;
		break;
	case 'v':
		j += 6;
		letters[indeks] = v;
		break;
	case 'y':
		j += 6;
		letters[indeks] = y;
		break;
	case 'w':
		j += 5;
		letters[indeks] = w;
		break;
	case 'b':
		roznica = space[iterator] - j;
		if (roznica == 4)
		{
			j += 4;
			letters[indeks] = e;
			break;
		}
		if (roznica == 5)
		{
			j += 5;
			letters[indeks] = k;
			break;
		}

		break;
	default:
		cout << "nie ma takiego koloru?\n";
		break;
	}
	unique = letters[indeks];
	unique_colors[unique]++;
	return j;
}

void swap_cards(karta tab[], int i)
{
	karta pom;
	pom.color = tab[i].color;
	pom.value = tab[i].value;
	tab[i].color = tab[i + 1].color;
	tab[i].value = tab[i + 1].value;
	tab[i + 1].color = pom.color;
	tab[i + 1].value = pom.value;
}

void tasuj(karta* tab, int x1, int x2)
{
	karta pom;
	pom.color = tab[x1].color;
	pom.value = tab[x1].value;
	tab[x1].color = tab[x2].color;
	tab[x1].value = tab[x2].value;
	tab[x2].color = pom.color;
	tab[x2].value = pom.value;
}

void sort_cards_by_color(karta tab[], int end)
{
	for (int j = 0; j < end - 1; j++)
	{
		for (int i = 0; i < end - 1; i++)
		{
			if (tab[i].color > tab[i + 1].color)
			{
				swap_cards(tab, i);
			}
			else
			{
				if (tab[i].color == tab[i + 1].color)
				{
					if (tab[i].value > tab[i + 1].value)
					{
						swap_cards(tab, i);
					}
				}
			}
		}
	}
}

void sort_cards_by_value_asc(karta tab[], int end)
{
	for (int j = 0; j < end - 1; j++)
	{
		for (int i = 0; i < end - 1; i++)
		{
			if (tab[i].value > tab[i + 1].value)
			{
				swap_cards(tab, i);
			}
			else
			{
				if (tab[i].value == tab[i + 1].value)
				{
					if (tab[i].color > tab[i + 1].color)
					{
						swap_cards(tab, i);
					}
				}
			}
		}
	}
}

void sort_cards_by_value_dcr(karta tab[], int end)
{

	for (int j = 0; j < end - 1; j++)
	{
		for (int i = 0; i < end - 1; i++)
		{
			if (tab[i].value < tab[i + 1].value)
			{
				swap_cards(tab, i);
			}
			else
			{
				if (tab[i].value == tab[i + 1].value)
				{
					if (tab[i].color < tab[i + 1].color)
					{
						swap_cards(tab, i);
					}
				}
			}
		}
	}
}

bool check_green(int unique_colors[], karta wartosci[])
{
	if (unique_colors[0] != 0)
	{
		for (int i = 0; i < unique_colors[0] - 1; i++)
		{
			if (wartosci[i].value != wartosci[i + 1].value)
			{
				return 1;

			}
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

bool check_other_colors(int unique_colors[], int k)
{
	for (int i = 1; i < k; i++)
	{
		if (unique_colors[i] != unique_colors[i + 1])
		{
			return 1;
		}
	}
	return 0;
}

bool check_other_value(int k, karta wartosci[], int unique_colors[])
{
	if (check_other_colors(unique_colors, k) == 0)
	{
		for (int i = unique_colors[0]; i < unique_colors[0] + unique_colors[1]; i++)
		{
			for (int j = 0; j < k - 1; j++)
			{
				if (wartosci[i + j * unique_colors[1]].value != wartosci[i + (j + 1) * unique_colors[1]].value)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	else
		return 1;
}

int get_number(char read[])
{
	int i = strlen(read) - 1;
	while (read[i] != ' ')
	{
		i--;
	}
	i++;
	int roznica = 0;
	int number = 0;
	roznica = strlen(read) - i - 2;
	number += (int)read[i] - 48;
	while (roznica--)
	{
		number *= 10;
		i++;
		number += (int)read[i] - 48;
	}
	return number;
}

bool check_hand_cards(int handcards_cnt[], int outcards_cnt, int n, int active_player)
{
	int i = active_player - 2;
	while (outcards_cnt--)
	{
		if (i == -1)
		{
			i = n - 1;
		}
		handcards_cnt[i]++;
		i--;
	}
	int flaga = 0;
	for (int j = 0; j < n - 1; j++)
	{
		if (handcards_cnt[j] > handcards_cnt[j + 1])
		{
			flaga += handcards_cnt[j] - handcards_cnt[j + 1];
		}
		if (handcards_cnt[j] < handcards_cnt[j + 1])
		{
			flaga += 2;
		}
	}
	if (flaga < 2)
		return 0;
	else
		return 1;
}

bool check_kociolek(karta* kociolek)
{
	int i = 0;
	while (kociolek[i + 1].value != NULL)
	{
		if (kociolek[i].color != kociolek[i + 1].color)
		{
			if (kociolek[i].color == g || kociolek[i + 1].color == g)
			{

			}
			else
			{
				return 1;
			}
		}
		i++;
	}
	return 0;
}
bool check_explosion(karta* kociolek, int e)
{
	int i = 0, suma = 0;
	while (kociolek[i].value != NULL)
	{
		suma += kociolek[i].value;
		i++;
		if (suma > e)
		{
			return 1;
		}
	}
	return 0;
}

bool check_game(int* unique_colors, karta* wartosci, int k, int* handcards_cnt, int outcards_cnt, int n, int active_player, karta** kociolek, int e)
{
	bool* tab = new bool[4 + k * 2];
	int x = 0;
	tab[x] = check_green(unique_colors, wartosci);
	x++;
	tab[x] = check_other_colors(unique_colors, k);
	x++;
	tab[x] = check_other_value(k, wartosci, unique_colors);
	x++;
	tab[x] = check_hand_cards(handcards_cnt, outcards_cnt, n, active_player);
	x++;
	for (int i = 0; i < k; i++)
	{
		tab[x] = check_kociolek(kociolek[i]);
		x++;
	}
	for (int i = 0; i < k; i++)
	{
		tab[x] = check_explosion(kociolek[i], e);
		x++;
	}
	for (int i = 0; i < 4 + k * 2; i++)
	{
		if (tab[i] == 1)
		{
			delete[]tab;
			return 1;
		}
	}
	delete[]tab;
	return 0;
}

int player_number(int active_player, int n)
{
	if (active_player == n)
	{
		active_player = 1;
	}
	else
	{
		active_player++;
	}
	return active_player;
}

int seek_kociolek(kolor a, karta** kociolek, int k)
{
	if (a == g)
	{
		return -1;
	}
	int y = 0;
	for (int i = 0; i < k; i++)
	{
		if (kociolek[i][0].color == g)
		{
			int x = 1;
			while (x)
			{
				if (kociolek[i][x].color != g)
				{
					if (kociolek[i][x].color == a)
					{
						return i;
					}
					else
					{
						if (kociolek[i][x].value == NULL)
						{
							y = i;
						}
						break;
					}
				}
				x++;
			}
		}
		else
		{
			if (kociolek[i][0].value == NULL)
			{
				y = i;
			}
			int j = 0;
			while (kociolek[i][j].value != NULL)
			{
				if (kociolek[i][j].color == a)
				{
					return i;
				}
				else
				{
					if (kociolek[i][j].color != g)
					{
						break;
					}
				}
				j++;
			}
		}
	}
	return y;
}
int simple_move(int active_player, karta** hand, karta** kociolek, int k, int n)
{
	int a = 0;
	if (hand[active_player - 1][0].color != g)
	{
		a = seek_kociolek(hand[active_player - 1][0].color, kociolek, k);
		if (a == -1)
		{
			a = 0;
		}
		int i = 0;
		while (kociolek[a][i].value != NULL)
		{
			i++;
		}
		kociolek[a][i].value = hand[active_player - 1][0].value;
		kociolek[a][i].color = hand[active_player - 1][0].color;
		hand[active_player - 1][0].value = NULL;
		hand[active_player - 1][0].color = o;
	}
	else
	{
		int i = 0;
		while (kociolek[0][i].value != NULL)
		{
			i++;
		}
		kociolek[0][i].value = hand[active_player - 1][0].value;
		kociolek[0][i].color = hand[active_player - 1][0].color;
		hand[active_player - 1][0].value = NULL;
		hand[active_player - 1][0].color = o;
	}
	int j = 1;
	while (hand[active_player - 1][j].value != NULL)
	{
		j++;
	}
	for (int x = 0; x < j - 1; x++)
	{
		swap_cards(hand[active_player - 1], x);
	}
	return a;
}

int check_sum(karta* kociolek)
{
	int sum = 0;
	int i = 0;
	while (kociolek[i].value != NULL)
	{
		sum += kociolek[i].value;
		i++;
	}
	return sum;
}
int choose_min(karta* tab, karta** kociolek, int j, int k, karta** hand, int active_player, int e, int* it)
{
	int* rab = new int[j];
	bool* kab = new bool[j];
	kolor a;
	int x = -1;
	for (int i = 0; i < j; i++)
	{
		x = i;
		a = hand[active_player - 1][x].color;
		x = seek_kociolek(a, kociolek, k);
		if (x == -1)
		{
			int* gre = new int[k];
			for (int u = 0; u < k; u++)
			{
				gre[u] = check_sum(kociolek[u]);
			}
			int minm = gre[0];
			x = 0;
			for (int u = 1; u < k; u++)
			{
				if (gre[u] < minm)
				{
					minm = gre[u];
					x = u;
					*it = u;
				}
			}
		}
		rab[i] = check_sum(kociolek[x]);
		if (rab[i] + tab[x].value > e)
		{
			kab[i] = 1;
		}
		else
		{
			kab[i] = 0;
		}
	}
	int min = rab[0];
	int flaga = 0;
	for (int i = 1; i < j; i++)
	{
		if (rab[i] < min)
		{
			min = rab[i];
			flaga = i;
		}
	}
	flaga++;
	if (kab[flaga - 1] == 1)
	{
		delete[]rab;
		delete[]kab;
		return -flaga;
	}
	delete[]rab;
	delete[]kab;
	return flaga;
}

int min_move(int active_player, karta** hand, karta** kociolek, int k, int n, int* handcards_cnt, int e)
{
	int it;
	sort_cards_by_value_asc(hand[active_player - 1] - 1, handcards_cnt[active_player - 1]);
	int j = 0;
	while (hand[active_player - 1][j].value == hand[active_player - 1][j + 1].value)
	{
		j++;
	}
	j++;
	karta* tab = new karta[j];
	kolor a;
	for (int i = 0; i < j; i++)
	{
		tab[i].color = hand[active_player - 1][i].color;
		tab[i].value = hand[active_player - 1][i].value;
	}
	int t = choose_min(tab, kociolek, j, k, hand, active_player, e, &it);
	t = abs(t);
	t--;
	a = tab[t].color;
	int x = seek_kociolek(a, kociolek, k);
	if (x == -1)
	{
		x = it;
	}
	int y = 0;
	while (kociolek[x][y].value != NULL)
	{
		y++;
	}
	kociolek[x][y].value = hand[active_player - 1][t].value;
	kociolek[x][y].color = hand[active_player - 1][t].color;
	hand[active_player - 1][t].value = NULL;
	hand[active_player - 1][t].color = o;
	int h = t + 1;
	while (hand[active_player - 1][h].value != NULL)
	{
		h++;
	}
	for (int i = t; i < h; i++)
	{
		swap_cards(hand[active_player - 1], i);
	}
	delete[]tab;
	return x;
}

int count_pile_cards(karta* kociolek)
{
	int i = 0;
	while (kociolek[i].value != NULL)
	{
		i++;
	}
	return i;
}

int choose_max(karta* tab, karta** kociolek, int j, int k, int active_player, karta** hand)
{
	int* rab = new int[j];
	int x;
	kolor a;
	for (int i = 0; i < j; i++)
	{
		x = i;
		a = hand[active_player - 1][x].color;
		x = seek_kociolek(a, kociolek, k);
		rab[i] = count_pile_cards(kociolek[x]);
	}
	int min = rab[0];
	int flaga = 0;
	for (int i = 0; i < j; i++)
	{
		if (rab[i] < min)
		{
			min = rab[i];
			flaga = i;
		}
	}
	return flaga;
}

int min_move_maximized(int active_player, karta** hand, karta** kociolek, int k, int n, int* handcards_cnt, int e)
{
	int it;
	sort_cards_by_value_asc(hand[active_player - 1] - 1, handcards_cnt[active_player - 1]);
	int j = 0;
	while (hand[active_player - 1][j].value == hand[active_player - 1][j + 1].value)
	{
		j++;
	}
	j++;
	karta* tab = new karta[j];
	kolor a;
	for (int i = 0; i < j; i++)
	{
		tab[i].color = hand[active_player - 1][i].color;
		tab[i].value = hand[active_player - 1][i].value;
	}
	int t = choose_min(tab, kociolek, j, k, hand, active_player, e, &it);
	if (t > 0)
	{
		t--;
	}
	else
	{
		delete[]tab;
		sort_cards_by_value_dcr(hand[active_player - 1] - 1, handcards_cnt[active_player - 1]);
		j = 0;
		while (hand[active_player - 1][j].value == hand[active_player - 1][j + 1].value)
		{
			j++;
		}
		j++;
		karta* tab = new karta[j];
		for (int i = 0; i < j; j++)
		{
			tab[i].value = hand[active_player - 1][i].value;
			tab[i].color = hand[active_player - 1][i].color;
		}
		t = choose_max(tab, kociolek, j, k, active_player, hand);
	}
	a = tab[t].color;
	int x = seek_kociolek(a, kociolek, k);
	int y = 0;
	while (kociolek[x][y].value != NULL)
	{
		y++;
	}
	kociolek[x][y].value = hand[active_player - 1][t].value;
	kociolek[x][y].color = hand[active_player - 1][t].color;
	hand[active_player - 1][t].value = NULL;
	hand[active_player - 1][t].color = o;
	int h = t + 1;
	while (hand[active_player - 1][h].value != NULL)
	{
		h++;
	}
	for (int i = t; i < h; i++)
	{
		swap_cards(hand[active_player - 1], i);
	}
	delete[]tab;
	return x;
}

int opti_cards(karta* tab, int j, int e, karta** kociolek, int active_player, karta** hand, int k, int* it)
{
	int* rab = new int[j];
	bool* kab = new bool[j];
	int x;
	kolor a;
	for (int i = 0; i < j; i++)
	{
		x = i;
		a = tab[x].color;
		x = seek_kociolek(a, kociolek, k);
		if (x == -1)
		{
			bool* gre = new bool[k];
			for (int u = 0; u < k; u++)
			{
				if (check_sum(kociolek[u]) + tab[i].value > e)
				{
					gre[u] = 1;
				}
				else
				{
					gre[u] = 0;
					delete[]gre;
					*it = u;
					return i;
				}
			}
			delete[]gre;
			int* gren = new int[k];
			for (int u = 0; u < k; u++)
			{
				gren[u] = count_pile_cards(kociolek[u]);
			}
			int min = gren[0];
			*it = 0;
			for (int u = 1; u < k; u++)
			{
				if (gren[u] < min)
				{
					min = gren[u];
					*it = u;
				}
			}
			return i;
		}
		rab[i] = check_sum(kociolek[x]);
		if (rab[i] + tab[i].value > e)
		{
			kab[i] = 1;
		}
		else
		{
			kab[i] = 0;
		}
	}
	for (int i = 0; i < j; i++)
	{
		if (kab[i] == 0)
		{
			delete[]rab;
			delete[]kab;
			return i;
		}
	}
	delete[]rab;
	delete[]kab;
	return -1;

}
int opti(karta** hand, karta** kociolek, int active_player, int e, int* handcards_cnt, int k)
{
	sort_cards_by_value_dcr(hand[active_player - 1], handcards_cnt[active_player - 1] + 1);
	int j = 0, i = 0, t = 2, j1 = 0, value, it;
	bool end = 0;
	kolor a;
	while (end == 0)
	{
		while (hand[active_player - 1][j].value == hand[active_player - 1][j + 1].value && j < handcards_cnt[active_player - 1])
		{
			j++;
		}
		j++;
		karta* tab = new karta[j - j1];
		i = 0;
		while (i < j - j1)
		{
			tab[i].color = hand[active_player - 1][i + j1].color;
			tab[i].value = hand[active_player - 1][i + j1].value;
			i++;
		}
		t = opti_cards(tab, j - j1, e, kociolek, active_player, hand, k, &it);
		if (t > -1)
		{
			end = 1;
			a = tab[t].color;
		}
		if (end == 0)
			j1 = j;
		delete[]tab;
	}
	if (j < handcards_cnt[active_player - 1])
	{

	}
	else
	{
		sort_cards_by_value_dcr(hand[active_player - 1], handcards_cnt[active_player - 1] + 1);
		j = 0;
		j1 = 0;
		while (hand[active_player - 1][j].value == hand[active_player - 1][j + 1].value)
		{
			j++;
		}
		j++;
		karta* tab = new karta[j];
		for (int i = 0; i < j; i++)
		{
			tab[i].value = hand[active_player - 1][i].value;
			tab[i].color = hand[active_player - 1][i].color;
		}
		t = choose_max(tab, kociolek, j, k, active_player, hand);
		a = tab[t].color;
		delete[]tab;
	}
	int x = seek_kociolek(a, kociolek, k);
	if (x == -1)
	{
		x = it;
	}
	int y = 0;
	while (kociolek[x][y].value != NULL)
	{
		y++;
	}
	kociolek[x][y].value = hand[active_player - 1][t + j1].value;
	kociolek[x][y].color = hand[active_player - 1][t + j1].color;
	hand[active_player - 1][t + j1].value = NULL;
	hand[active_player - 1][t + j1].color = o;
	int h = t + j1 + 1;
	while (hand[active_player - 1][h].value != NULL)
	{
		h++;
	}
	for (int i = t + j1; i < h; i++)
	{
		swap_cards(hand[active_player - 1], i);
	}
	return x;
}
bool check_if_explode(int e, int a, karta** kociolek)
{
	int sum = 0, i = 0;
	while (kociolek[a][i].value != 0)
	{
		sum += kociolek[a][i].value;
		i++;
	}
	if (sum > e)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void explode(int e, int a, karta** deck, int active_player, karta** kociolek)
{
	if (check_if_explode(e, a, kociolek) == 1)
	{
		int i = 0, j = 0;
		while (deck[active_player - 1][j].value != NULL)
		{
			j++;
		}
		while (kociolek[a][i].value != NULL)
		{
			deck[active_player - 1][j].value = kociolek[a][i].value;
			deck[active_player - 1][j].color = kociolek[a][i].color;
			j++;
			kociolek[a][i].value = NULL;
			kociolek[a][i].color = o;
			i++;
		}
	}
}

bool check_ifend(karta** hand, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (hand[i][0].value != NULL)
		{
			return 1;
		}
	}
	return 0;
}

int max_color(int* tab, int n, const char* kolory[], int b)
{
	bool flaga = 0;
	int m = -1;
	for (int i = 0; i < n; i++)
	{
		if (tab[i] > tab[m])
		{
			m = i;
			flaga = 0;
		}
		else
		{
			if (tab[i] == tab[m])
			{
				flaga = 1;
			}
		}
	}
	if (flaga == 0)
	{
		cout << "Na kolor " << kolory[b] << " odporny jest gracz " << m + 1 << "\n";
		return m;
	}
	else
	{
		return -1;
	}
}
void endgame(karta** deck, int n, int k, const char* kolory[])
{
	FILE* koniec;
	koniec = fopen("end.txt", "w+");
	int** tab = new int* [k + 1];
	for (int i = 0; i <= k; i++)
	{
		tab[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			tab[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while (deck[i][j].value != NULL)
		{
			tab[deck[i][j].color][i]++;
			j++;
		}
	}
	int* rab = new int[k + 1];
	rab[0] = NULL;
	for (int j = 1; j <= k; j++)
	{
		rab[j] = max_color(tab[j], n, kolory, j);
	}
	int* result = new int[n];
	for (int i = 0; i < n; i++)
	{
		result[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if (i != rab[j])
			{
				result[i] += tab[j][i];
			}
		}
		result[i] += tab[0][i];
		result[i] += tab[0][i];
		cout << "Wynik gracza " << i + 1 << " = " << result[i] << "\n";
		fprintf(koniec, "Wynik gracza %d = %d\n", i + 1, result[i]);
	}
	delete[]result;
	delete[]rab;
	for (int i = 0; i <= k; i++)
	{
		delete[]tab[i];
	}
	delete[]tab;
	fclose(koniec);
}
void print_game(int active_player, int n, int e, karta** hand, karta** deck, karta** kociolek, const char* kolory[], int k)
{
	FILE* zapis;
	zapis = fopen("gamestate.txt", "w+");
	fprintf(zapis, "active player = %d\nplayers number = %d\n explosion threshold = %d\n", active_player, n, e);
	cout <<"active player = "<<active_player << "\nplayers number = " << n << "\nexplosion threshold = " << e << "\n";
	for (int i = 0; i < 2 * n; i++)
	{
		if (i % 2 == 0)
		{
			fprintf(zapis, "%d player hand cards: ", (i / 2) + 1);
			cout << (i/2)+1 << " player hand cards: ";
			int j = 0;
			while (hand[i / 2][j].value != NULL)
			{
				cout << hand[i / 2][j].value << " " << kolory[hand[i / 2][j].color] << " ";
				fprintf(zapis, "%d %s ", hand[i / 2][j].value, kolory[hand[i / 2][j].color]);
				j++;
			}
		}
		else
		{
			cout << (i / 2) + 1 << " player deck cards: ";
			fprintf(zapis, "%d player deck cards: ", (i / 2) + 1);
			int j = 0;
			while (deck[i / 2][j].value != NULL)
			{
				fprintf(zapis, "%d %s ", deck[i / 2][j].value, kolory[deck[i / 2][j].color]);
				cout << deck[i / 2][j].value << " " << kolory[deck[i / 2][j].color] << " ";
				j++;
			}
		}
		cout << "\n";
		fprintf(zapis, "\n");
	}
	for (int i = 0; i < k; i++)
	{
		cout << i + 1 << " pile cards: ";
		fprintf(zapis, "%d pile cards: ", i + 1);
		int j = 0;
		while (kociolek[i][j].value != NULL)
		{
			fprintf(zapis, "%d %s ", kociolek[i][j].value, kolory[kociolek[i][j].color]);
			cout << kociolek[i][j].value << " " << kolory[kociolek[i][j].color] << " ";
			j++;
		}
		cout << "\n";
		fprintf(zapis, "\n");
	}
	fclose(zapis);
}

kolor get_color_init(int j)
{
	switch (j)
	{
	case 0:
		return e;
		break;
	case 1:
		return r;
		break;
	case 2:
		return v;
		break;
	case 3:
		return y;
		break;
	case 4:
		return w;
		break;
	case 5:
		return k;
		break;
	default:
		return o;
		break;
	}
}
void generate(const char* kolory[])
{
	int n, k, e, gq, gv, o, val;
	cout << "Podaj liczbe graczy: \n";
	cin >> n;
	cout << "Podaj liczbe kolorow kart(bez zielonego): \n";
	cin >> k;
	cout << "Podaj limit wybuchu kociolka: \n";
	cin >> e;
	cout << "Podaj liczbe kart zielonych: \n";
	cin >> gq;
	cout << "Podaj wartosc kart zielonych: \n";
	cin >> gv;
	cout << "Podaj liczbe kart jednego koloru: \n";
	cin >> o;
	karta* tab = new karta[gq + k * o];
	kolor d;
	d = g;
	for (int i = 0; i < gq; i++)
	{
		tab[i].color = d;
		tab[i].value = gv;

	}
	cout << "Podaj wartosci dla kart niezielonych: \n";
	for (int i = 0; i < o; i++)
	{
		cin >> val;
		for (int j = 0; j < k; j++)
		{
			tab[gq + i + j * o].value = val;
			tab[gq + i + j * o].color = get_color_init(j);
		}
	}
	int x1, x2;
	int rand_number = ((gq + k * o) * 4 * n);
	int cards_number = gq + k * o;
	int l;
	srand(time(NULL));
	l = rand() % 100;
	for (int i = 0; i < rand_number; i++)
	{
		srand((l + i) * (o + 2 * gv));
		x1 = rand() % cards_number;
		srand((4 * i + k * (2 + i)) + (3 * n + gq));
		x2 = rand() % cards_number;
		if (x1 != x2)
			tasuj(tab, x1, x2);
	}
	FILE* plik;
	plik = fopen("gamestate.txt", "w");
	fprintf(plik, "active player = 1\n");
	fprintf(plik, "players number = %d\n", n);
	fprintf(plik, "explosion threshold = %d\n", e);
	for (int i = 0; i < n; i++)
	{
		fprintf(plik, "%d player hand cards: ", i + 1);
		int j = i;
		while (j < gq + k * o)
		{
			fprintf(plik, "%d %s ", tab[j].value, kolory[tab[j].color]);
			j += n;
		}
		fprintf(plik, "\n");
		fprintf(plik, "%d player deck cards:\n", i + 1);
	}
	for (int i = 0; i < k; i++)
	{
		fprintf(plik, "%d pile cards:\n", i + 1);
	}
	fclose(plik);
	delete[]tab;
}
int main()
{
	int menu;
	const char* kolory[] = { "green","blue","red","violet","yellow","white","black","error" };
	char read[9999] = { "alamakota" };
	karta* tab = new karta[500];
	int n, active_player, e;
	FILE* odczyt;
	cout << "Witaj w grze trucizna!\n";
	cout << "Jezeli nie posiadasz pliku z talia, wygeneruj go wciskajac: 1, lub wklej go do folderu gdzie znajduje sie ten program. Jesli plik jest na swoim miejscu, wpisz inna liczbe.";
	cin >> menu;
	if (menu == 1)
	{
		generate(kolory);
	}
	odczyt = fopen("gamestate.txt", "r");
	fgets(read, 100, odczyt);
	active_player = get_number(read);
	fgets(read, 100, odczyt);
	n = get_number(read);
	fgets(read, 100, odczyt);
	e = get_number(read);
	//alokacja pamieci
	karta** hand = new karta * [n + 1];
	int tempv = 0, tempp = 0, roznica = 0, indeks = 0;
	char* pointer = 0;
	char first_let = 'a';
	int licznik = 0;
	int* handcards_cnt = new int[n];
	int* handcards_test = new int[n];
	for (int i = 0; i < n; i++)
	{
		handcards_cnt[i] = 0;
		handcards_test[i] = 0;
	}
	int outcards_cnt = 0;
	for (int i = 0; i < n; i++)
	{
		handcards_cnt[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		hand[i] = new karta[numb_cards_expected];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < numb_cards_expected; j++)
		{
			hand[i][j].value = NULL;
			hand[i][j].color = o;
		}
	}
	kolor unique = o;
	karta** deck = new karta * [n + 1];
	for (int i = 0; i < n; i++)
	{
		deck[i] = new karta[numb_cards_expected];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < numb_cards_expected; j++)
		{
			deck[i][j].value = NULL;
			deck[i][j].color = o;
		}
	}
	karta* wartosci = new karta[numb_cards_expected];
	for (int i = 0; i < numb_cards_expected; i++)
	{
		wartosci[i].color = o;
		wartosci[i].value = NULL;
	}
	int it = 0;
	int unique_colors[7] = {};
	for (int i = 0; i < 2 * n; i++)
	{
		fgets(read, 9999, odczyt);
		licznik = 0;
		indeks = 0;
		unique = o;
		int end = strlen(read);
		licznik = count_spaces(read, licznik, end);
		int* tempvalues = new int[licznik / 2 + 2];
		for (int j = 0; j < licznik / 2 + 2; j++)
		{
			tempvalues[j] = NULL;
		}
		kolor* letters = new kolor[licznik / 2 + 2];
		for (int j = 0; j < licznik / 2 + 2; j++)
		{
			letters[j] = o;
		}
		int* space = new int[licznik + 3];
		for (int j = 0; j < licznik + 3; j++)     // alokacja pamieci do spamietania polozenia spacji
		{
			space[j] = NULL;
		}
		int j = 2, cnt = 0;
		j = set_j(read, j);
		int l = licznik;
		find_spaces(pointer, l, cnt, tempp, space, read);
		int iterator = 0;
		space[licznik] = end - 1;
		space[licznik + 1] = 0;
		iterator = set_iterator(j, iterator, space);
		while (j < end && space[iterator])
		{
			if ((int)read[j] > 47 && (int)read[j] < 58)
			{
				j = get_value(tempv, roznica, iterator, j, indeks, space, tempvalues, read);
			}
			if ((int)read[j] > 96 && (int)read[j] < 123)
			{
				j = get_color(first_let, j, iterator, roznica, indeks, letters, read, space, unique, unique_colors);
			}
			if (tempvalues[indeks] != -1 && letters[indeks] != o)
			{
				indeks++;
			}
			j++;
			iterator++;
		}
		for (int j = 0; j < licznik / 2 - 1; j++)
		{
			if (i % 2 == 0)
			{
				hand[i / 2][j].value = tempvalues[j];
				hand[i / 2][j].color = letters[j];
				handcards_cnt[i / 2]++;
				handcards_test[i / 2]++;
				wartosci[it].value = tempvalues[j];
				wartosci[it].color = letters[j];
				it++;
			}
			else
			{
				deck[i / 2][j].value = tempvalues[j];
				deck[i / 2][j].color = letters[j];
				outcards_cnt++;
				wartosci[it].value = tempvalues[j];
				wartosci[it].color = letters[j];
				it++;
			}
		}
		delete[]space;
		delete[]letters;
		delete[]tempvalues;
	}
	int k = 0;
	for (int i = 0; i < 7; i++)
	{
		if (unique_colors[i] != 0)
		{
			k++;
		}
	}
	if (unique_colors[0] != 0)
	{
		--k;
	}
	karta** kociolek = new karta * [k];
	for (int i = 0; i < k; i++)
	{
		kociolek[i] = new karta[numb_cards_expected];
	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < numb_cards_expected; j++)
		{
			kociolek[i][j].color = o;
			kociolek[i][j].value = NULL;
		}
	}
	for (int i = 0; i < k; i++)
	{
		fgets(read, 9999, odczyt);
		licznik = 0;
		indeks = 0;
		unique = o;
		int end = strlen(read);
		licznik = count_spaces(read, licznik, end);
		int* tempvalues = new int[licznik / 2 + 2];
		for (int j = 0; j < licznik / 2 + 2; j++)
		{
			tempvalues[j] = NULL;
		}
		kolor* letters = new kolor[licznik / 2 + 2];
		for (int j = 0; j < licznik / 2 + 2; j++)
		{
			letters[j] = o;
		}
		int* space = new int[licznik + 3];
		for (int j = 0; j < licznik + 3; j++)     // alokacja pamieci do spamietania polozenia spacji
		{
			space[j] = NULL;
		}
		int j = 2, cnt = 0;
		j = set_j(read, j);
		int l = licznik;
		find_spaces(pointer, l, cnt, tempp, space, read);
		int iterator = 0;
		space[licznik] = end - 1;
		space[licznik + 1] = 0;
		iterator = set_iterator(j, iterator, space);
		while (j < end && space[iterator])
		{
			if ((int)read[j] > 47 && (int)read[j] < 58)
			{
				j = get_value(tempv, roznica, iterator, j, indeks, space, tempvalues, read);
				iterator++;
			}
			if ((int)read[j] > 96 && (int)read[j] < 123)
			{
				j = get_color(first_let, j, iterator, roznica, indeks, letters, read, space, unique, unique_colors);
				iterator++;
			}
			if (tempvalues[indeks] != -1 && letters[indeks] != o)
			{
				indeks++;
			}
			j++;
		}
		for (int j = 0; j < licznik / 2 - 1; j++)
		{
			kociolek[i][j].value = tempvalues[j];
			kociolek[i][j].color = letters[j];
			outcards_cnt++;
			wartosci[it].value = tempvalues[j];
			wartosci[it].color = letters[j];
			it++;
		}
		delete[]space;
		delete[]letters;
		delete[]tempvalues;
	}
	int liczba_kart = 0;
	for (int i = 0; i <= k; i++)
	{
		liczba_kart += unique_colors[i];
	}
	fclose(odczyt);

	sort_cards_by_color(wartosci, it);
	int outcards_test = outcards_cnt;
	int menu2;
	cout << "Wejściowy stan gry:\n";
	print_game(active_player, n, e, hand, deck, kociolek, kolory, k);
	cout << "Aby wczytac stan gry i wykonać ruch okreslonym graczem, wpisz: 1\n";
	cout << "Aby rozegrac runde do konca, wpisz 2\n";
	cin >> menu2;
	switch (menu2)
	{
	case 1:
		int menu3;
		cout << "Aby wykonac ruch gracza grajacego losowo, wcisnij: 1\n";
		cout << "Aby wykonac ruch gracza wykladajacego najmniejsza karte, wcisnij: 2\n";
		cout << "Aby wykonac ruch gracza wykladajacego najwieksza karte w sytuacji nieuniknionego wybuchu, wcisnij: 3\n";
		cout << "Aby wykonac ruch gracza grajacego optymalnie, wcisnij: 4\n";
		cin >> menu3;
		switch (menu3)
		{
		case 1:
			if (check_game(unique_colors, wartosci, k, handcards_test, outcards_test, n, active_player, kociolek, e) == 0)
			{
				int a;
				a = simple_move(active_player, hand, kociolek, k, n);
				explode(e, a, deck, active_player, kociolek);
				active_player = player_number(active_player, n);
				if (check_ifend(hand, n) == 0)
				{
					endgame(deck, n, k, kolory);
				}
				else
				{
					print_game(active_player, n, e, hand, deck, kociolek, kolory, k);
				}
			}
			else
			{
				cout << "Blad danych\n";
			}
			break;
		case 2:
			if (check_game(unique_colors, wartosci, k, handcards_test, outcards_test, n, active_player, kociolek, e) == 0)
			{
				int a;
				a = min_move(active_player, hand, kociolek, k, n, handcards_cnt, e);
				explode(e, a, deck, active_player, kociolek);
				active_player = player_number(active_player, n);
				if (check_ifend(hand, n) == 0)
				{
					endgame(deck, n, k, kolory);
				}
				else
				{
					print_game(active_player, n, e, hand, deck, kociolek, kolory, k);
				}
			}
			else
			{
				cout << "Blad danych\n";
			}
			break;
		case 3:
			if (check_game(unique_colors, wartosci, k, handcards_test, outcards_test, n, active_player, kociolek, e) == 0)
			{
				int a;
				a = min_move_maximized(active_player, hand, kociolek, k, n, handcards_cnt, e);
				explode(e, a, deck, active_player, kociolek);
				active_player = player_number(active_player, n);
				if (check_ifend(hand, n) == 0)
				{
					endgame(deck, n, k, kolory);
				}
				else
				{
					print_game(active_player, n, e, hand, deck, kociolek, kolory, k);
				}
			}
			else
			{
				cout << "Blad danych\n";
			}
			break;
		case 4:
			if (check_game(unique_colors, wartosci, k, handcards_test, outcards_test, n, active_player, kociolek, e) == 0)
			{
				int a;
				a = opti(hand, kociolek, active_player, e, handcards_cnt, k);
				explode(e, a, deck, active_player, kociolek);
				active_player = player_number(active_player, n);
				if (check_ifend(hand, n) == 0)
				{
					endgame(deck, n, k, kolory);
				}
				else
				{
					print_game(active_player, n, e, hand, deck, kociolek, kolory, k);
				}
			}
			else
			{
				cout << "Blad danych\n";
			}
			break;
		default:
			cout << "Zla komenda\n";
			break;
		}
		break;
	case 2:
		while (check_ifend(hand,n) == 1)
		{
			if (check_game(unique_colors, wartosci, k, handcards_test, outcards_test, n, active_player, kociolek, e) == 0)
			{
				int a;
				a = simple_move(active_player, hand, kociolek, k, n);
				explode(e, a, deck, active_player, kociolek);
				active_player = player_number(active_player, n);
				if (check_ifend(hand, n) == 0)
				{
					endgame(deck, n, k, kolory);
				}
				else
				{
					print_game(active_player, n, e, hand, deck, kociolek, kolory, k);
				}
			}
			else
			{
				cout << "Blad danych\n";
			}
		}
		break;
	default:
		cout << "Zla komenda\n";
		break;
	}
	for (int i = 0; i < k; i++)
	{
		delete[]kociolek[i];
	}
	delete[]kociolek;
	for (int i = 0; i < n; i++)                       //zwracanie pamięci
	{
		delete[]hand[i];
	}
	delete[]hand;
	for (int i = 0; i < n; i++)
	{
		delete[]deck[i];
	}
	delete[]deck;
	delete[]wartosci;
	delete[]handcards_cnt;
	delete[]handcards_test;
	return 0;
}