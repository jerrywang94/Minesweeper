#pragma once
#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include <chrono>
#include <gtkmm.h>

namespace minesweeper {

	enum class states { covered, uncovered, flagged };

	class tile {
		friend class MSGame;

	public:

		tile() {}
		tile(int x, int y, int type, states tflag);

		void flip_flag();
		int return_type() { return tile_type; }
		states return_state() { return tile_status; }

	private:
		int tile_x = 0;
		int tile_y = 0;
		int tile_type = 0; // > 0 is how many mines, -1 means this is a mine, 0 means no mines
		states tile_status = states::covered;

	};

	class MSGame {

	public:
		MSGame() : game_tiles(100), rows(10), columns(10), mines(10) {}
		MSGame(int r, int c, int m);

		int check_adjacent_mines(int x, int y);
		int check_adjacent_flags(int x, int y);

		void reset();
		void reset(int r, int c, int m);

		const std::vector<tile>& returntiles() { // TO be deleted - for testing only
			return game_tiles;
		}

	private:
		std::vector<tile> game_tiles;
		int rows = 0;
		int columns = 0;
		int mines = 0;
	};

	template <class T>
	void fy_shuffle(T& arr, int shuffle_number = 0) { // implementation of fisher yates shuffle

		if (shuffle_number < 0)
			return;

		int arr_size = static_cast<int> (arr.end() - arr.begin());

		if (shuffle_number == 0 || shuffle_number == arr_size)
			shuffle_number = arr_size - 1;

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 mgen(seed);

		for (int i = 0; i < shuffle_number; i++) {
			// re-construct udist each time to change bounds - apparently lightweight operation
			std::uniform_int_distribution<int> udist(i, (arr_size - 1));
			std::swap(arr[i], arr[udist(mgen)]);
		}

		return;

	}
}