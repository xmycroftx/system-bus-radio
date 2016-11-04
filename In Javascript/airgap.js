//Credits to https://github.com/fulldecent/system-bus-radio
//As well as Jordan Harband for the nodejs simd library
//Tested to be working on Chrome at 1560khz

function now() {
	return window.performance.now() * 1000000;
}

var NSEC_PER_SEC = 1000000000;
var register = 3.1415;

function square_am_signal(time, freq) {
	document.getElementById('logs').value += "Playing / " + time + " seconds / " + freq + "Hz\n";
	var period = NSEC_PER_SEC / freq;
	var start = now();
	var end = now() + time * NSEC_PER_SEC;
	while (now() < end) {
		var mid = start + period / 2;
		var reset = start + period;
		while (now() < mid) {
			for (var i = 0; i < 100; i++) {
				register = 1 - Math.log(register) / 1.7193;
			}
		}
		while (now() < reset) {}
		start = reset;
	}
}

function start() {
	var song = document.getElementById("tones").value.split("\n");
	var length = song.length;
	var line, time, freq;
	for (var i = 0; i < length; i++) {
		line = song[i].split(" ");
		if (+line[1] == 0) {
			pause(line[0]);
		}
		else {
			freq = +line[1];
			time = (+line[0])*.001;
			square_am_signal(time, freq);
		}
	}
}

function pause(time) {
	window.logs.value += "\nPaused / " + time*.001 + " seconds";
	var dt = new Date();
	while ((new Date()) - dt <= time) { /* Do nothing */ }
}