module main

import gg

struct App {
mut:
	gg   &gg.Context = unsafe { nil }
	game Game
}

fn main() {
	mut app := &App{
		game: new_game()
	}
	app.gg = gg.new_context(
		bg_color:     gg.black
		width:        win_width
		height:       win_height
		window_title: 'PacMan'
		sample_count: 2
		frame_fn:     frame
		event_fn:     on_event
		user_data:    app
	)
	app.gg.run()
}

fn frame(mut app App) {
	dt := f32(app.gg.timer.elapsed().milliseconds()) / 1000.0
	app.gg.timer.restart()
	// Clamp to avoid physics explosions on frame spikes or focus loss.
	safe_dt := if dt > 0.05 || dt <= 0 { f32(0.016) } else { dt }

	app.game.update(safe_dt)

	app.gg.begin()
	app.game.draw(app.gg)
	app.gg.end()
}

fn on_event(e &gg.Event, mut app App) {
	if e.typ != .key_down {
		return
	}
	match e.key_code {
		.left  { app.game.player.desired = .left }
		.right { app.game.player.desired = .right }
		.up    { app.game.player.desired = .up }
		.down  { app.game.player.desired = .down }
		.p {
			if app.game.state == .playing {
				app.game.state = .paused
			} else if app.game.state == .paused {
				app.game.state = .playing
			}
		}
		.r {
			if app.game.state in [GameState.game_over, GameState.won] {
				app.game = new_game()
			}
		}
		.escape { app.gg.quit() }
		else {}
	}
}
