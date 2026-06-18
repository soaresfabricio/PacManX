module main

import math
import gg

struct Player {
mut:
	tile_col    int
	tile_row    int
	progress    f32
	dir         Dir
	desired     Dir
	px          f32 // fractional tile column (for rendering)
	py          f32 // fractional tile row
	mouth_angle f32 = 0.25 // radians, half-angle of mouth opening
	lives       int = 3
	death_timer f32
}

fn new_player() Player {
	return Player{
		tile_col: 10
		tile_row: 29
	}
}

// update advances the player by dt seconds. Returns (score_delta, trigger_frightened).
fn (mut p Player) update(dt f32, mut board Board, time f32) (int, bool) {
	// Accept reversal immediately without waiting for a tile boundary.
	if p.desired != .none_dir && p.desired == opposite(p.dir) {
		p.dir = p.desired
		p.desired = .none_dir
	}

	// Try to start moving from rest.
	if p.dir == .none_dir && p.desired != .none_dir {
		nc := p.tile_col + dir_dc(p.desired)
		nr := p.tile_row + dir_dr(p.desired)
		if board.player_can_enter(nc, nr) {
			p.dir = p.desired
			p.desired = .none_dir
		} else {
			p.update_pixel_pos()
			return 0, false
		}
	}

	p.progress += player_speed * dt

	mut total_score := 0
	mut trigger_frightened := false

	for p.dir != .none_dir && p.progress >= 1.0 {
		p.progress -= 1.0

		p.tile_col += dir_dc(p.dir)
		p.tile_row += dir_dr(p.dir)
		p.tile_col, p.tile_row = tunnel_wrap(p.tile_col, p.tile_row)

		score, scared := board.collect(p.tile_col, p.tile_row)
		total_score += score
		if scared {
			trigger_frightened = true
		}

		// Accept queued direction at tile boundary if the way is clear.
		if p.desired != .none_dir {
			nc := p.tile_col + dir_dc(p.desired)
			nr := p.tile_row + dir_dr(p.desired)
			if board.player_can_enter(nc, nr) {
				p.dir = p.desired
				p.desired = .none_dir
			}
		}

		// Stop if the current direction is now blocked.
		nc := p.tile_col + dir_dc(p.dir)
		nr := p.tile_row + dir_dr(p.dir)
		if !board.player_can_enter(nc, nr) {
			p.dir = .none_dir
			p.progress = 0.0
		}
	}

	p.update_pixel_pos()

	// Animate mouth: fully open → closed → fully open at ~4 Hz.
	if p.dir != .none_dir {
		p.mouth_angle = f32(math.abs(math.sin(f64(time) * 8.0))) * 0.45
	} else {
		p.mouth_angle = 0.25
	}

	return total_score, trigger_frightened
}

fn (mut p Player) update_pixel_pos() {
	p.px = f32(p.tile_col) + f32(dir_dc(p.dir)) * p.progress
	p.py = f32(p.tile_row) + f32(dir_dr(p.dir)) * p.progress
}

fn (p &Player) screen_x() f32 {
	return p.px * tile_size + tile_size / 2.0
}

fn (p &Player) screen_y() f32 {
	return p.py * tile_size + tile_size / 2.0 + hud_height
}

fn draw_player(ctx &gg.Context, p &Player) {
	cx := p.screen_x()
	cy := p.screen_y()
	r := f32(tile_size) * 0.42

	if p.death_timer > 0 {
		// Shrink to nothing over 1.5 s.
		frac := p.death_timer / 1.5
		if frac >= 1.0 {
			return
		}
		ctx.draw_circle_filled(cx, cy, r * (1.0 - frac), gg.yellow)
		return
	}

	base := dir_angle(p.dir)
	// draw_slice_filled angles are in radians; 0 = right, increases clockwise in screen coords.
	start := base + p.mouth_angle
	end := base + tau - p.mouth_angle
	ctx.draw_slice_filled(cx, cy, r, start, end, 32, gg.yellow)
}
