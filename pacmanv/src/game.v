module main

import math
import gg

struct Game {
mut:
	board       Board
	player      Player
	ghosts      []Ghost
	state       GameState
	score       int
	ghost_combo int // consecutive ghost-eats this frightened period
	time        f32
}

fn new_game() Game {
	mut g := Game{
		board:  new_board()
		player: new_player()
		state:  .playing
	}
	g.ghosts << new_ghost(.blinky)
	g.ghosts << new_ghost(.pinky)
	g.ghosts << new_ghost(.inky)
	g.ghosts << new_ghost(.clyde)
	return g
}

fn (mut game Game) reset_positions() {
	game.player = new_player()
	game.ghosts = []Ghost{}
	game.ghosts << new_ghost(.blinky)
	game.ghosts << new_ghost(.pinky)
	game.ghosts << new_ghost(.inky)
	game.ghosts << new_ghost(.clyde)
}

fn (mut game Game) trigger_frightened() {
	game.ghost_combo = 0
	for mut g in game.ghosts {
		if g.state != .eaten {
			if g.state != .frightened {
				g.dir = opposite(g.dir) // reverse on fright entry
			}
			g.state = .frightened
			g.frightened_timer = frightened_duration
		}
	}
}

fn (mut game Game) update(dt f32) {
	match game.state {
		.paused {}
		.dying {
			game.player.death_timer += dt
			if game.player.death_timer >= 1.5 {
				game.player.lives--
				if game.player.lives <= 0 {
					game.state = .game_over
				} else {
					game.reset_positions()
					game.state = .playing
				}
			}
		}
		.playing {
			game.time += dt

			// Update player.
			score, scared := game.player.update(dt, mut game.board, game.time)
			game.score += score
			if scared {
				game.trigger_frightened()
			}

			if game.board.all_collected() {
				game.state = .won
				return
			}

			// Update ghosts — cache Blinky's position for Inky's targeting.
			blinky_col := game.ghosts[0].tile_col
			blinky_row := game.ghosts[0].tile_row
			for mut g in game.ghosts {
				update_ghost(mut g, dt, &game.board, &game.player, blinky_col, blinky_row)
			}

			// Collision detection.
			for mut g in game.ghosts {
				dx := game.player.px - g.px
				dy := game.player.py - g.py
				dist_sq := dx * dx + dy * dy
				if dist_sq > 0.75 * 0.75 {
					continue
				}
				match g.state {
					.frightened {
						g.state = .eaten
						combo_idx := if game.ghost_combo < eat_scores.len {
							game.ghost_combo
						} else {
							eat_scores.len - 1
						}
						game.score += eat_scores[combo_idx]
						game.ghost_combo++
					}
					.chasing, .scattered {
						game.state = .dying
						game.player.death_timer = 0.0
					}
					else {}
				}
			}
		}
		else {}
	}
}

// ── Drawing ─────────────────────────────────────────────────────────────────

fn (game &Game) draw(ctx &gg.Context) {
	game.draw_board(ctx)
	draw_player(ctx, &game.player)
	for g in game.ghosts {
		draw_ghost(ctx, &g)
	}
	game.draw_hud(ctx)
}

fn (game &Game) draw_board(ctx &gg.Context) {
	wall_color := gg.rgb(33, 33, 222)
	pellet_color := gg.rgb(255, 222, 178)
	energizer_color := gg.rgb(255, 200, 120)

	for r in 0 .. rows {
		for c in 0 .. cols {
			idx := r * cols + c
			t := game.board.tiles[idx]
			sx := f32(c * tile_size)
			sy := f32(r * tile_size + hud_height)

			match t {
				.wall {
					ctx.draw_rect_filled(sx, sy, f32(tile_size), f32(tile_size), wall_color)
				}
				.pellet {
					if game.board.pellets[idx] {
						cx := sx + f32(tile_size) / 2.0
						cy := sy + f32(tile_size) / 2.0
						ctx.draw_circle_filled(cx, cy, 2.5, pellet_color)
					}
				}
				.energizer {
					if game.board.pellets[idx] {
						cx := sx + f32(tile_size) / 2.0
						cy := sy + f32(tile_size) / 2.0
						// Pulse radius using game time.
						pr := 4.5 + f32(math.sin(f64(game.time) * 6.0)) * 1.5
						ctx.draw_circle_filled(cx, cy, pr, energizer_color)
					}
				}
				else {}
			}
		}
	}

	// Draw a thin pink line to indicate the ghost-house door (row 13, cols 11-16).
	door_y := f32(13 * tile_size + hud_height) + f32(tile_size) / 2.0 - 1.5
	ctx.draw_rect_filled(f32(11 * tile_size), door_y, f32(6 * tile_size), 3.0,
		gg.rgb(220, 100, 220))
}

fn (game &Game) draw_hud(ctx &gg.Context) {
	// Score background strip.
	ctx.draw_rect_filled(0, 0, f32(win_width), f32(hud_height), gg.rgb(20, 20, 20))

	ctx.draw_text(8, 12, 'SCORE  ${game.score}', gg.TextCfg{
		color: gg.white
		size:  18
	})

	// Draw one small Pac-Man icon per remaining life.
	for i in 0 .. game.player.lives {
		lx := f32(win_width - 24 - i * 22)
		ly := f32(hud_height / 2)
		ctx.draw_slice_filled(lx, ly, 8.0, 0.35, tau - 0.35, 16, gg.yellow)
	}

	match game.state {
		.game_over {
			ctx.draw_text(win_width / 2 - 60, win_height / 2, 'GAME  OVER', gg.TextCfg{
				color: gg.red
				size:  28
			})
			ctx.draw_text(win_width / 2 - 80, win_height / 2 + 36, 'press R to restart', gg.TextCfg{
				color: gg.white
				size:  16
			})
		}
		.won {
			ctx.draw_text(win_width / 2 - 50, win_height / 2, 'YOU  WIN!', gg.TextCfg{
				color: gg.yellow
				size:  28
			})
			ctx.draw_text(win_width / 2 - 80, win_height / 2 + 36, 'press R to restart', gg.TextCfg{
				color: gg.white
				size:  16
			})
		}
		.paused {
			ctx.draw_text(win_width / 2 - 35, win_height / 2, 'PAUSED', gg.TextCfg{
				color: gg.white
				size:  24
			})
		}
		else {}
	}
}
