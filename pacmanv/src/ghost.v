module main

import math
import gg

// Ghost-house exit target: the G-corridor tile just above the ghost house.
const house_exit_col = 12
const house_exit_row = 8

// Scatter corners per ghost kind (C++ Blinky/Pinky/Inky/Clyde corners).
const scatter_targets = [
	[27, 0]!, // blinky — top-right
	[0, 0]!,  // pinky  — top-left
	[27, 30]!, // inky   — bottom-right
	[0, 30]!,  // clyde  — bottom-left
]!

// Ghost-eaten bonus scores indexed by consecutive-eat count (0..3).
const eat_scores = [200, 400, 800, 1600]!

struct Ghost {
mut:
	kind             GhostKind
	state            GhostState
	tile_col         int
	tile_row         int
	progress         f32
	dir              Dir
	px               f32
	py               f32
	game_time        f32 // elapsed game time used for scatter/chase cycling
	frightened_timer f32
	release_delay    f32
	in_house         bool
}

fn new_ghost(kind GhostKind) Ghost {
	col, row, delay, in_h, d := match kind {
		.blinky { 10, 20, f32(0.0), false, Dir.left }
		.pinky  { 12, 17, f32(0.0), true, Dir.left }
		.inky   { 16, 17, f32(5.0), true, Dir.right }
		.clyde  { 8, 23, f32(0.0), false, Dir.right }
	}
	return Ghost{
		kind:          kind
		state:         .chasing
		tile_col:      col
		tile_row:      row
		px:            f32(col)
		py:            f32(row)
		dir:           d
		release_delay: delay
		in_house:      in_h
	}
}

// tunnel_wrap applies horizontal wrapping on the tunnel row (row 14).
fn tunnel_wrap(c int, r int) (int, int) {
	if r == 14 {
		if c < 0 { return cols - 1, r }
		if c >= cols { return 0, r }
	}
	return c, r
}

// ghost_scatter_or_chase returns which base state should be active at this game_time.
fn ghost_scatter_or_chase(game_time f32) GhostState {
	cycle := f32(math.fmod(f64(game_time), f64(scatter_duration + chase_duration)))
	return if cycle < scatter_duration { GhostState.scattered } else { GhostState.chasing }
}

// ghost_target returns the tile the ghost should navigate toward.
fn ghost_target(g &Ghost, player &Player, blinky_col int, blinky_row int) (int, int) {
	if g.in_house {
		return house_exit_col, house_exit_row
	}
	match g.state {
		.eaten {
			// Return to ghost-house centre.
			return 13, 15
		}
		.scattered {
			corner := scatter_targets[int(g.kind)]
			return corner[0], corner[1]
		}
		.frightened {
			// Move away from player (maximise distance).
			return player.tile_col, player.tile_row
		}
		.chasing {
			match g.kind {
				.blinky {
					return player.tile_col, player.tile_row
				}
				.pinky {
					// 4 tiles ahead of player's current direction.
					return player.tile_col + 4 * dir_dc(player.dir),
						player.tile_row + 4 * dir_dr(player.dir)
				}
				.inky {
					// Vector from Blinky to (player + 2*dir), doubled.
					pivot_c := player.tile_col + 2 * dir_dc(player.dir)
					pivot_r := player.tile_row + 2 * dir_dr(player.dir)
					return pivot_c + (pivot_c - blinky_col), pivot_r + (pivot_r - blinky_row)
				}
				.clyde {
					dx := f32(g.tile_col - player.tile_col)
					dy := f32(g.tile_row - player.tile_row)
					dist_sq := dx * dx + dy * dy
					if dist_sq >= 64.0 { // 8 tiles
						return player.tile_col, player.tile_row
					}
					corner := scatter_targets[int(GhostKind.clyde)]
					return corner[0], corner[1]
				}
			}
		}
	}
	return player.tile_col, player.tile_row
}

// pick_dir selects the ghost's next direction heading toward (target_c, target_r).
// When prefer_max is true the direction that maximises distance is chosen (frightened mode).
fn pick_dir(g &Ghost, board &Board, target_c int, target_r int, prefer_max bool) Dir {
	mut best := Dir.none_dir
	mut best_dist := if prefer_max { f32(-1.0) } else { f32(1.0e9) }

	for d in [Dir.up, Dir.down, Dir.left, Dir.right] {
		if d == opposite(g.dir) {
			continue // no U-turns (except on state transitions)
		}
		nc := g.tile_col + dir_dc(d)
		nr := g.tile_row + dir_dr(d)
		if !board.ghost_can_enter(nc, nr) {
			continue
		}
		dx := f32(nc - target_c)
		dy := f32(nr - target_r)
		dist := dx * dx + dy * dy
		if prefer_max {
			if dist > best_dist {
				best_dist = dist
				best = d
			}
		} else {
			if dist < best_dist {
				best_dist = dist
				best = d
			}
		}
	}

	return if best != .none_dir { best } else { opposite(g.dir) }
}

// update_ghost advances one ghost by dt seconds.
fn update_ghost(mut g Ghost, dt f32, board &Board, player &Player, blinky_col int, blinky_row int) {
	// Countdown before leaving the ghost house.
	if g.in_house && g.release_delay > 0 {
		g.release_delay -= dt
		return
	}

	// Promote to normal state once out of the house.
	if g.in_house && board.tile_at(g.tile_col, g.tile_row) != .house {
		g.in_house = false
	}

	g.game_time += dt

	// Handle frightened timer expiry.
	if g.state == .frightened {
		g.frightened_timer -= dt
		if g.frightened_timer <= 0 {
			g.state = ghost_scatter_or_chase(g.game_time)
			g.dir = opposite(g.dir) // reverse when exiting frightened
		}
	}

	// Scatter ↔ chase cycling (only when not frightened/eaten/in_house).
	if g.state in [GhostState.chasing, GhostState.scattered] {
		desired := ghost_scatter_or_chase(g.game_time)
		if desired != g.state {
			g.dir = opposite(g.dir)
			g.state = desired
		}
	}

	speed := if g.state == .frightened { ghost_scared_speed } else { ghost_speed }
	g.progress += speed * dt

	for g.progress >= 1.0 {
		g.progress -= 1.0

		g.tile_col += dir_dc(g.dir)
		g.tile_row += dir_dr(g.dir)
		g.tile_col, g.tile_row = tunnel_wrap(g.tile_col, g.tile_row)

		// Return from eaten state once back inside the house.
		if g.state == .eaten && board.tile_at(g.tile_col, g.tile_row) == .house {
			g.state = ghost_scatter_or_chase(g.game_time)
			g.in_house = true
			g.release_delay = 0
		}

		tc, tr := ghost_target(g, player, blinky_col, blinky_row)
		g.dir = pick_dir(g, board, tc, tr, g.state == .frightened)
	}

	g.px = f32(g.tile_col) + f32(dir_dc(g.dir)) * g.progress
	g.py = f32(g.tile_row) + f32(dir_dr(g.dir)) * g.progress
}

fn ghost_color(kind GhostKind, state GhostState, frightened_timer f32) gg.Color {
	if state == .eaten {
		return gg.rgb(40, 40, 40)
	}
	if state == .frightened {
		// Flash white when < 2 s remain.
		if frightened_timer < 2.0 && int(frightened_timer * 4) % 2 == 0 {
			return gg.white
		}
		return gg.rgb(0, 0, 200)
	}
	return match kind {
		.blinky { gg.red }
		.pinky  { gg.rgb(255, 184, 255) }
		.inky   { gg.rgb(0, 255, 255) }
		.clyde  { gg.rgb(255, 184, 81) }
	}
}

fn draw_ghost(ctx &gg.Context, g &Ghost) {
	cx := g.px * tile_size + f32(tile_size) / 2.0
	cy := g.py * tile_size + f32(tile_size) / 2.0 + hud_height
	r := f32(tile_size) * 0.42
	c := ghost_color(g.kind, g.state, g.frightened_timer)

	// Upper dome (half-circle).
	ctx.draw_slice_filled(cx, cy, r, f32(math.pi), f32(math.pi) * 2.0, 16, c)
	// Rectangular body below centre.
	ctx.draw_rect_filled(cx - r, cy, r * 2.0, r, c)

	// Eyes (only when not deep-eaten / not frightened).
	if g.state != .eaten && g.state != .frightened {
		ew := r * 0.3
		ctx.draw_circle_filled(cx - r * 0.35, cy - r * 0.25, ew, gg.white)
		ctx.draw_circle_filled(cx + r * 0.35, cy - r * 0.25, ew, gg.white)
		pw := ew * 0.4
		ctx.draw_circle_filled(cx - r * 0.22, cy - r * 0.25, pw, gg.rgb(0, 0, 180))
		ctx.draw_circle_filled(cx + r * 0.48, cy - r * 0.25, pw, gg.rgb(0, 0, 180))
	}
}
