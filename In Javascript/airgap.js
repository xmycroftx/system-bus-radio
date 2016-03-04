//Credits to https://github.com/fulldecent/system-bus-radio
//As well as Jordan Harband for the nodejs simd library
//Tested to be working on Chrome at 1560khz

var _i32x4 = new Int32Array(4);
Int32x4 = function(x, y, z, w) {
    if (!(this instanceof Int32x4)) {
      return new Int32x4(x, y, z, w);
  }

  this.x_ = x|0;
  this.y_ = y|0;
  this.z_ = z|0;
  this.w_ = w|0;
}

Int32x4store = function(tarray, index, value) {
  var bpe = tarray.BYTES_PER_ELEMENT;
  _i32x4[0] = value.x_;
  _i32x4[1] = value.y_;
  _i32x4[2] = value.z_;
  _i32x4[3] = value.w_;
  var array = bpe == 1 ? _i8x16 :
  bpe == 2 ? _i16x8 :
  bpe == 4 ? (tarray instanceof Float32Array ? _f32x4 : _i32x4) :
  _f64x2;
  var n = 16 / bpe;
  for (var i = 0; i < n; ++i)
      tarray[index + i] = array[i];
  return value;
}

function now() {
 return performance.now()*1000000;
}

var tarray = new Int32Array(4);
var zero = Int32x4(0,0,0,0);
var one = Int32x4(-1,-1,-1,-1);
var NSEC_PER_SEC = 1000000000;

function square_am_signal(time,freq) {
    document.getElementById('logs').value += "Playing / "+time+" seconds / "+freq+"Hz\n"; 
    var period = NSEC_PER_SEC/freq;
    var start = now();
    var end = now()+time*NSEC_PER_SEC;
    while (now() < end) {
        var mid = start+period/2;
        var reset = start+period;
        while (now()<mid) {
            Int32x4store(tarray, 0, one);
            Int32x4store(tarray, 0, zero);
        }
        while(now() < reset){
        }
        start = reset
    }
}

function start() {
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2093);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2673);
    square_am_signal(0.790, 2673);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2349);
    square_am_signal(0.790, 2349);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 3136);
    square_am_signal(0.790, 3136);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2093);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2349);
    square_am_signal(0.400, 2673);
    square_am_signal(0.400, 2349);
    square_am_signal(0.790, 2093);
}
