//Credits to https://github.com/fulldecent/system-bus-radio
//As well as Jordan Harband for the nodejs simd library
//Tested to be working on Chrome at 1560khz

function now() {
 return performance.now()*1000000;
}

var NSEC_PER_SEC = 1000000000;
var register = 3.1415;

function square_am_signal(time,freq) {
	document.getElementById('logs').value += "Playing / "+time+" seconds / "+freq+"Hz\n";
	var period = NSEC_PER_SEC/freq;
	var start = now();
	var end = now()+time*NSEC_PER_SEC;
	while (now() < end) {
		var mid = start+period/2;
		var reset = start+period;
		while (now()<mid) {
			for (var i = 0; i < 100; i++) {
				register = 1 - Math.log(register) / 1.7193;
			}
		}
		while(now() < reset){
		}
		start = reset;
	}
}

function start() {
	var song = document.getElementById("tones").value.split(":");
	var length = song.length;
	var i = 1, line, time, freq;
	while (1 <= length) {
		line = song[i].split(" ");
		if (line[0] == "beep") {
			freq = +line[0].split("=")[1];
			time = +line[2].split("=")[1].slice(0,-1);
			square_am_signal(time, freq);
		}
		if (line[0] == "delay") {
			// delay
		}
		if (song[i] == "end") {
			i = 1;
		}
		i++;
	}
}
