#include <iostream>


class Deck
{
public:
	int* begin;
	int* end;
	int** map;
	int size = 0;
	int size_map = 0;
	Deck()
	{
		map = new int* [++size_map]; // 1 - default capacity for map
		map[0] = new int[5]; // 5 - default capacity for chuck
		begin = &map[0][0];
		end = &map[0][0];
	}

	~Deck()
	{
		for (int i = 0; i < size_map; i++) {
			delete[] map[i];
		}
		delete[] map;
		
	}

	void delete_top() {
		if (size == 0)
			return;

		*begin = GARBAGE;

		if ((map[0][4] == GARBAGE) && size_map != 1) {
			begin = &map[1][0];
			size--;
			delete[] map[0];

			for (int i = 0; i < size_map-1; i++) {
				map[i] = map[i + 1];
			}

			//map = &map[1];

			size_map--;

			return;
		}

		begin = (begin + 1);
		size--;
	}

	void delete_bottom() {
		if (size == 0)
			return;

		*end = GARBAGE;
		if ((map[size_map - 1][0] == GARBAGE) && size_map!=1 ) {
			end = &map[size_map - 2][4];
			size--;
			delete map[size_map - 1];
			size_map--;
			
			return;
		}

		end = (end - 1); // смещение не работает почему-то
		size--;

	}

	void push_top(int value) { // создает лишние чанки
		if (size == 0) {
			map[0][0] = value;
			size++;
			return;
		}
		if (map[0][0] != GARBAGE) {
			creating_new_chuck_on_top();
			map[0][4] = value;
			begin = &map[0][4];
			size++;
			return;
		}
		begin = (begin - 1);
		*begin = value;
		size++;


	}

	void push_bottom(int value) { // создает лишние чанки
		if (size == 0) {
			map[0][0] = value;
			size++;
			return;
		}
		if (map[size_map - 1][4] != GARBAGE) {
			creating_new_chuck_on_bottom();
			map[size_map - 1][0] = value;
			end = &map[size_map - 1][0];
			size++;
			return;
		}
		end = (end + 1);
		*end = value;
		size++;
	}

	void insert_by_index(int value, int index) {
		if (index == 0) {
			push_top(value);
			return;
		}
		if (index == size) {
			push_bottom(value);
			return;
		}
		
		int temp_size = size_map;
		int temp_ind = size-1;
		if (map[size_map - 1][4] != GARBAGE) {
			push_bottom(map[size_map - 1][4]);
			size--;
		}

		for (int i = temp_size - 1; i >= 0; i--) {
			for (int j = 4; j >= 0; j--) {
				if (map[i][j] == GARBAGE) {
					continue;
				}
				
				if (j != 4) {
					map[i][j + 1] = map[i][j];
				}
				else {
					map[i + 1][0] = map[i][j];
				}

				if (temp_ind == index) {
					map[i][j] = value;
					size++;
					return;
				}
				temp_ind--;

			}
		}

	}


	void delete_by_index(int index) {

		if (size == 0)
			return;

		int temp_ind = 0;

		for (int i = 0; i < size_map; i++) {
			for (int j = 0; j < 5; j++) {
				if (map[i][j] == GARBAGE) {
					continue;
				}
				if (temp_ind < index) {
					temp_ind++;
					continue;
				}
				else {

					if (j != 4) {
						map[i][j] = map[i][j + 1];
						
					}
					else {
						if (i == size_map - 1)
							map[i][j] = GARBAGE;

						map[i][j] = map[i + 1][0];

					}
				}



			}
		}
		size--;

	}

	void show_instance() {

		for (int i = 0; i < size_map; i++) {
			for (int j = 0; j < 5; j++) {
				if (map[i][j] != GARBAGE) {
					std::cout << map[i][j] << ' ';
				}
				
			}
			std::cout << std::endl;
		}

	}



private:

	const int GARBAGE = -842150451;

	void creating_new_chuck_on_top() {
		int** temp = new int* [++size_map];
		for (int i = 1; i < size_map; i++) {
			temp[i] = map[i - 1]; // relocation
		}
		delete[] map;
		map = temp;
		map[0] = new int[5];
	}

	void creating_new_chuck_on_bottom() {
		int** temp = new int* [++size_map];
		for (int i = 0; i < size_map - 1; i++) {
			temp[i] = map[i]; // relocation
		}
		delete[] map;
		map = temp;
		map[size_map - 1] = new int[5];
	}

};

int main() {
	
		Deck p;
		p.push_top(1);
		p.push_top(2);
		p.push_top(3);
		p.push_top(4);
		p.push_top(5);
		p.push_bottom(-1);
		p.push_bottom(-2);
		p.push_bottom(-3);
		p.push_bottom(-3);
		p.push_bottom(-9);
		p.push_bottom(-10);
		p.delete_bottom();
		p.delete_bottom();
		p.delete_bottom();
		p.delete_top();
		p.delete_top();
		p.delete_top();
	
	return 0;
}
