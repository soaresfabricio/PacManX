module main

// Maze encoded directly from C++ Tabuleiro::carrega() mapa[] strings.
// 'B' wall · 'G' pellet · 'R' energizer · 'W' ghost-house/tunnel · 'Z' outside
const maze_rows = [
	'BBBBBBBBBBBBBBBBBBBBBBBBBBBB',
	'BGGGGGGGGGGGGBBGGGGGGGGGGGGB',
	'BGBBBBGBBBBBGBBGBBBBBGBBBBGB',
	'BRBZZBGBZZZBGBBGBZZZBGBZZBRB',
	'BGBBBBGBBBBBGBBGBBBBBGBBBBGB',
	'BGGGGGGGGGGGGGGGGGGGGGGGGGGB',
	'BGBBBBGBBGBBBBBBBBGBBGBBBBGB',
	'BGBBBBGBBGBBBBBBBBGBBGBBBBGB',
	'BGGGGGGBBGGGGBBGGGGBBGBBBBBB',
	'BBBBBBGBBBBBWBBWBBBBBGBBBBBB',
	'ZZZZZBGBBBBBWBBWBBBBBGBZZZZZ',
	'ZZZZZBGBBWWWWWWWWWWBBGBZZZZZ',
	'ZZZZZBGBBWBBBWWBBBWBBGBZZZZZ',
	'BBBBBBGBBWBWWWWWWBWBBGBBBBBB',
	'WWWWWWGWWWBWWWWWWBWWWGWWWWWW',
	'BBBBBBGBBWBWWWWWWBWBBGBBBBBB',
	'ZZZZZBGBBWBBBBBBBBWBBGBZZZZZ',
	'ZZZZZBGBBWWWWWWWWWWBBGBZZZZZ',
	'ZZZZZBGBBWBBBBBBBBWBBGBZZZZZ',
	'BBBBBBGBBWBBBBBBBBWBBGBBBBBB',
	'BGGGGGGGGGGGGBBGGGGGGGGGGGGB',
	'BGBBBBGBBBBBGBBGBBBBBGBBBBGB',
	'BRBBBBGBBBBBGBBGBBBBBGBBBBRB',
	'BGGGBBGGGGGGGGGGGGGGGGBBGGGB',
	'BBBGBBGBBGBBBBBBBBGBBGBBGBBB',
	'BBBGBBGBBGBBBBBBBBGBBGBBGBBB',
	'BGGGGGGBBGGGGBBGGGGBBGGGGGGB',
	'BGBBBBBBBBBBGBBGBBBBBBBBBBGB',
	'BGBBBBBBBBBBGBBGBBBBBBBBBBGB',
	'BGGGGGGGGGGGGGGGGGGGGGGGGGGB',
	'BBBBBBBBBBBBBBBBBBBBBBBBBBBB',
]!

fn char_to_tile(c u8) TileType {
	return match c {
		`B` { .wall }
		`G` { .pellet }
		`R` { .energizer }
		`W` { .house }
		else { .empty }
	}
}

struct Board {
mut:
	tiles        []TileType
	pellets      []bool
	pellet_count int
}

fn new_board() Board {
	mut b := Board{
		tiles:   []TileType{len: rows * cols}
		pellets: []bool{len: rows * cols}
	}
	for r in 0 .. rows {
		row_str := maze_rows[r]
		for c in 0 .. cols {
			t := char_to_tile(row_str[c])
			b.tiles[r * cols + c] = t
			if t == .pellet || t == .energizer {
				b.pellets[r * cols + c] = true
				b.pellet_count++
			}
		}
	}
	return b
}

fn (b &Board) tile_at(c int, r int) TileType {
	if c < 0 || c >= cols || r < 0 || r >= rows {
		return .empty
	}
	return b.tiles[r * cols + c]
}

// player_can_enter: player may traverse pellets, energizers, and the tunnel row.
fn (b &Board) player_can_enter(c int, r int) bool {
	t := b.tile_at(c, r)
	return match t {
		.pellet, .energizer { true }
		.house { r == 14 } // only the tunnel row is accessible to the player
		else { false }
	}
}

// ghost_can_enter: ghosts may traverse everything except solid walls and outside tiles.
fn (b &Board) ghost_can_enter(c int, r int) bool {
	t := b.tile_at(c, r)
	return t != .wall && t != .empty
}

// collect removes any collectible at (c,r). Returns (score_delta, trigger_frightened).
fn (mut b Board) collect(c int, r int) (int, bool) {
	idx := r * cols + c
	if !b.pellets[idx] {
		return 0, false
	}
	b.pellets[idx] = false
	b.pellet_count--
	return if b.tiles[idx] == .energizer { 50, true } else { 10, false }
}

fn (b &Board) all_collected() bool {
	return b.pellet_count == 0
}

// reset restores all pellets (used for new game).
fn (mut b Board) reset() {
	for r in 0 .. rows {
		for c in 0 .. cols {
			idx := r * cols + c
			t := b.tiles[idx]
			b.pellets[idx] = t == .pellet || t == .energizer
		}
	}
	b.pellet_count = b.pellets.count(true)
}
