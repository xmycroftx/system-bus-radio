var player;

function start() {
	var logs = document.getElementById('logs');
	if (window.Worker && typeof(player) == "undefined") {
		var player = new Worker("worker.js");
		window.player = player; // Make variable Global
		player.onmessage = function(event) {
			var data = event.data;
			window.logs.value += data;
		};
		var song = document.getElementById("tones").innerHTML;
		player.postMessage(song);
	}
}

function end() {
	player.terminate();
}
