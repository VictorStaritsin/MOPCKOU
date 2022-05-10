#include <iostream>
#include <conio.h>   //для очистки (_getch)
#include <windows.h> //для задержки (sleep)

using namespace std;
const int N = 10; //размер поля
const int NUM_SHIPS = 9;//количество кораблей


void set_rand_ships(int map[N][N], int size_ship, int ships_id)
{
	int x, y;  //координаты первичной точки

	int dir = 0;//генерация случайного корабля

	int count_ship = 0;//счетчик кораблей

	int count_tact = 0;//счетчик числа тактов

	while (count_ship < 1) //цикл работает до той степени, пока все корабли не будут установлены
	{
		x = rand() % N;//первичная позиция координаты X - отвечает за столбцы
		y = rand() % N;//первичная позиция координаты Y - отвечает за строки
		int temp_x = x;//сохранение первоночальные координаты X временно, чтобы не потерялись 
		int temp_y = y;//сохранение первоночальные координаты Y временно, чтобы не потерялись 
        dir = rand() % 4; //для случайного направления
		bool setting_is_possible = 1;
		//проверка возможности постановки корабля
		for (int i = 0; i < size_ship; i++)
		{
			if (x < 0 || y < 0 || x >= N || y >= N)
			{
				setting_is_possible = 0;
				break;
			}
			//проверка ячейки; если занята, то скидываем на 0 (setting_is_possible), и идем дальше 
			if (map[x][y] >= 1)
			{
				setting_is_possible = 0;
				break;
			}
			if (y < N - 1)
				if (map[x][y + 1] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (y > 0)
				if (map[x][y - 1] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (x < N - 1)
				if (map[x + 1][y] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (x < N - 1 && y < N - 1)
				if (map[x + 1][y + 1] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (x < N - 1 && y > 0)
				if (map[x][y - 1] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (x > 0)
				if (map[x - 1][y] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (x > 0 && y < N - 1)
				if (map[x - 1][y + 1] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			if (x > 0 && y > 0)
				if (map[x - 1][y - 1] >= 1)
				{
					setting_is_possible = 0;
					break;
				}
			switch (dir)// изменение координат в зависимости от направления
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
		//если есть возможность поставить корабль
		if (setting_is_possible == 1)
		{
			x = temp_x;
			y = temp_y;

			for (int i = 0; i < size_ship; i++)//цикл размера корабля
			{
				map[x][y] = ships_id;// в этой клетке находится палуба корабля
				switch (dir)  //для случайного построения нашего корабля в зависимости от направления; если это возможно
				{
				case 0:
					x++;//корабль растет вправо
					break;
				case 1:
					y++;//корабль растет вниз
					break;
				case 2:
					x--;//корабль растет влево
					break;
				case 3:
					y--;//корабль растет вверх
					break;
				}
			}
		    count_ship++;
		}
	}
}
//прорисовка карты
void map_show(int map[N][N], int mask[N][N],bool useMask)
{
	cout << ' ';

	for (int i = 0; i < N; i++)
	{
    cout << i;// выводим нумерацию столбцов
	}
	cout << endl;
	
	for (int i = 0; i < N; i++)
		{
		cout << i;//выводим нумерацию строк

		for (int j = 0; j < N; j++)
		{
			if (mask[j][i] == 1 || useMask == 0)//чтобы видеть свои корабли и корабли компьютера
			{

				if (map[j][i] == 0)
				{
					cout << '-';//для пустой клетки
				}
				else if (map[j][i] == -1)//для палуб
				{
					cout << 'X';//подбитый корабль
				}
				else if (map[j][i] == -2)
				{
					cout << '*';//для промаха
				}
				else
				{
					cout << map[j][i];
				}
			}
		}
		cout << endl;
	}
}
//Функция для стрельбы
int shot(int map[N][N], int x, int y, int ships[NUM_SHIPS + 1], int mask[N][N])
{
	int result = 0;//результат стрельбы
	if (map[x][y] == -1 || map[x][y] == -1)//цикл для компьютера (если попал в ячейку, заново стрелять туда уже не будет)
	{
		result = 3;
	}
	if (map[x][y] >= 1)
	{
		ships[map[x][y]]--;

		if (ships[map[x][y]] <= 0)
		{
			result = 2;//убит
		}
		else
		{
			result = 1;//ранен
		}
		map[x][y] = -1;
		
	}
	else
	{
		map[x][y] = -2;//промах
	}
	
	mask[x][y] = 1;
	return result;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << " Игра Морской бой " << endl;
	cout << " Пиратской сборки " << endl;
	while (1)
	{
		int map[N][N] = { 0 };//поле пользователя
		int map2[N][N] = { 0 };//поле компьютера
		int ships1[NUM_SHIPS + 1] = {  4, 3, 3, 2, 2, 2, 1, 1, 1 ,1};//входные данные для функции set_rand_ships
		int ships2[NUM_SHIPS + 1] = {  4, 3, 3, 2, 2, 2, 1, 1, 1 ,1};//компьютер
		int mask[N][N] = { 0 }; //маска для пользователя
		int mask2[N][N] = { 0 };//маска для компьютера
		bool winMe = 0;//для выхода из главного цикла
		
		//цикл для заполнения карты пользователя
		for (int i = 1; i <= NUM_SHIPS; i++)
		{
			set_rand_ships(map, ships1[i], i);
		}
		//цикл для заполнения карты компьютера
		for (int i = 1; i <= NUM_SHIPS; i++)
		{
			set_rand_ships(map2, ships2[i], i);
		}

		int x = 0, y = 0;
		int dir = 0;
		int size_ship = 4;
		int ch;

		bool turn = 0;//для ввода координат пользователя или компьютера

		while (true)
		{
            int resultShot = 0;//результат стрельбы
			do//цикл для стрельбы и перехода хода
			{
				map_show(map, mask, 0);
				cout << endl;
				map_show(map2, mask2, 1);//чтобы видеть корабли компьютера, поставь '0'
				
				if (turn == 1)
				{
					cout << endl << "Ход ПИРАТА : "<< endl;
					//ход пользователя
					cout << "Введи координату X по горизонтали : ";
					cin >> x;
					cout << "Введи координату Y по вертикали :   ";
					cin >> y;
                    resultShot = shot(map2, x, y, ships2, mask2);
				}
				else
				{
					//ход компьютера рандомный выстрел
					cout << endl << "Ход компьютера : "<< endl;
					Sleep(1000);
					x = rand() % N;
					y = rand() % N;
					resultShot = shot(map, x, y, ships1, mask);
				}
				//анализ стрельбы
				if (resultShot == 1)
				{
					cout << "Ранен" << endl;

				}
				else if (resultShot == 2)
				{   
					bool died = 1;
					for (int i = 1; i <= NUM_SHIPS; i++)
					{
						
						if (ships2[i] != 0)
						{
							died = 0;
							
							break;
						}
					}
					if (died == 1)
					{
						winMe = 1;
						
						break;
					}
					cout << "Убит" << endl;
				}
				else
				{
					cout << "Промах" << endl;
				}
				Sleep(1000);// для небольшой задержки
				system("cls");//для очищения консольного окна

			}while (resultShot != 0);//пока результат стрельбы не '0', стреляем
			turn =! turn;//для перехода хода
			if (winMe == true)
			{
				cout << endl;
				cout << "Вы Победили" << endl;
				cout << endl;
			}
			
		}
		_getch(); //не дать консоли преждевременно закрыться
		system("cls");//для очищения консольного окна	
	}
	return 0;
}

//int Ships_id = 1; 
//int Ships[10] = { 0 }; //массив поля

//Доработать Пиратскую версию
//функция для перестановки курсора в заданные координаты
//void move_cursor_xy(int x, int y)
//{
//	COORD p = { x,y };
//	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), p);//нахождение в библиотеке windows
//}

//функция для перестановки курсора в заданные координаты
//void ship_show(int x, int y, int dir, int size_ship)
//{
//	for (int i = 0; i < size_ship; i++)//цикл для размер корабля
//	{
//		move_cursor_xy(x + 1, y + 1);//добовляем 1 для координат x = 0 и y = 0, чтобы не выходили за нашу рамку
//		cout << '#'; // вывод символа вместо палубы
//
//		switch (dir)  //для случайного построения нашего корабля в зависимости от направления (если это возможно)
//		{
//		case 0:
//			x++;//корабль растет вправо
//			break;
//		case 1:
//			y++;//корабль растет вниз
//			break;
//		case 2:
//			x--;//корабле растет влево
//			break;
//		case 3:
//			y--;//корабль растет вверх
//			break;
//		}
//	}
//};

//функция проверки постановки корабля
//bool ship_in_map(int x, int y, int dir, int size_ship)
//{
//	bool in_map = 1;
//	for (int i = 0; i < size_ship; i++)
//	{
//		if (x < 0 || y < 0 || x >= N || y >= N)
//		{
//			in_map = 0;
//			break;
//		}
//		switch (dir)// изменение координат в зависимости от направления
//		{
//		case 0:
//			x++;
//			break;
//		case 1:
//			y++;
//			break;
//		case 2:
//			x--;
//			break;
//		case 3:
//			y--;
//			break;
//		}
//	}
//	return in_map;
//}

//функция для проверки не накладываются ли корабли друг на друга и не соприкасаются ли
//bool set_ship(int map[N][N], int x, int y, int dir, int size_ship)
//{
//	int temp_x = x; //первичная позиция координаты X - отвечает за столбцы
//	int temp_y = y; //первичная позиция координаты Y - отвечает за строки
//  //проверка возможности постановки корабля
//	bool setting_is_possible = 1;
//	for (int i = 0; i < size_ship; i++)
//	{
//     //проверка ячейки, если занята то скидываем на 0 (setting_is_possible) и идем дальше 
//		if (x < 0 || y < 0 || x >= N || y >= N)
//		{
//			setting_is_possible = 0;
//			break;
//		}
//		// 9 if для границы нашего поля
//		if (map[x][y] >= 1)
//		{
//			setting_is_possible = 0;
//			break;
//		}
//		if (y < N - 1)
//			if (map[x][y + 1] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (y > 0)
//			if (map[x][y - 1] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (x < N - 1)
//			if (map[x + 1][y] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (x < N - 1 && y < N - 1)
//			if (map[x + 1][y + 1] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (x < N - 1 && y > 0)
//			if (map[x][y - 1] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (x > 0)
//			if (map[x - 1][y] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (x > 0 && y < N - 1)
//			if (map[x - 1][y + 1] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//		if (x > 0 && y > 0)
//			if (map[x - 1][y - 1] >= 1)
//			{
//				setting_is_possible = 0;
//				break;
//			}
//
//		switch (dir)// изменение координат в зависимости от направления
//		{
//		case 0:
//			x++;
//			break;
//		case 1:
//			y++;
//			break;
//		case 2:
//			x--;
//			break;
//		case 3:
//			y--;
//			break;
//		}
//	}
//   // если есть возможность поставить корабль, то ставим
//	if (setting_is_possible == 1)
//	{
//		x = temp_x;
//		y = temp_y;
//
//		for (int i = 0; i < size_ship; i++)//цикл размер каробля
//		{
//			map[x][y] = Ships_id;// в этой клетке находится палуба корабля
//			switch (dir)  //для случайного построения нашего корабля в зависимости от направления (если это возможно)
//			{
//			case 0:
//				x++;//корабль растет вправо
//				break;
//			case 1:
//				y++;//корабль растет вниз
//				break;
//			case 2:
//				x--;//корабле растет влево
//				break;
//			case 3:
//				y--;//корабль растет вверх
//				break;
//			}
//		}
//		Ships[Ships_id] = size_ship;
//		Ships_id++;
//	}
//	return setting_is_possible;
//}