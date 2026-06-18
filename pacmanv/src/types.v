module main

import math

const tile_size            = 20
const cols                 = 28
const rows                 = 31
const hud_height           = 44
const win_width            = cols * tile_size       // 560
const win_height           = rows * tile_size + hud_height  // 664
const player_speed         = f32(8.0)
const ghost_speed          = f32(6.0)
const ghost_scared_speed   = f32(3.5)
const frightened_duration  = f32(8.0)
const scatter_duration     = f32(7.0)
const chase_duration       = f32(20.0)
const tau                  = f32(math.pi * 2.0)

// Tile types matching the C++ maze character encoding
enum TileType {
	empty      // Z — outside the maze border, not traversable
	wall       // B — blue wall
	pellet     // G — yellow dot
	energizer  // R — power pellet
	house      // W — ghost house interior / tunnel connector
}

enum Dir {
	none_dir
	up
	down
	left
	right
}

fn dir_dc(d Dir) int {
	return match d {
		.left  { -1 }
		.right { 1 }
		else   { 0 }
	}
}

fn dir_dr(d Dir) int {
	return match d {
		.up   { -1 }
		.down { 1 }
		else  { 0 }
	}
}

// dir_angle returns the facing angle in radians (0 = right, π/2 = down).
fn dir_angle(d Dir) f32 {
	return match d {
		.right { f32(0.0) }
		.down  { f32(math.pi / 2.0) }
		.left  { f32(math.pi) }
		.up    { f32(3.0 * math.pi / 2.0) }
		else   { f32(0.0) }
	}
}

fn opposite(d Dir) Dir {
	return match d {
		.up    { Dir.down }
		.down  { Dir.up }
		.left  { Dir.right }
		.right { Dir.left }
		else   { Dir.none_dir }
	}
}

enum GhostState {
	chasing
	scattered
	frightened
	eaten
}

enum GameState {
	playing
	dying
	game_over
	won
	paused
}

enum GhostKind {
	blinky // red  — direct pursuit
	pinky  // pink — leads player by 4 tiles
	inky   // cyan — reflected from Blinky
	clyde  // orange — chases or scatters based on distance
}
