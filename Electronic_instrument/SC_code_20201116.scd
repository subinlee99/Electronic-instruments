//20201116 Subin Lee

// make your own sound using arduino (ultra sonic sensor and accelerometer gyro sesor)
// if you make a hand move like hitting the drum, then drum sound will play!
// and using your hand, adjust the sound you are playing

//get info and connect to Arduino
SerialPort.devices;
~port = SerialPort.new("/dev/cu.usbmodem101", 9600);
~openframeworks = NetAddr("127 .0.0.1", 12345);

~openframeworks = NetAddr("Subinui-MacBookAir.local", 12345);

~openframeworks.sendMsg('/x',1);
~openframeworks.sendMsg('/dis',1);
~port.read.postln;
//use when you need to close the Arduino
~port.close;
//get information from the arduino
//info from each sensor will be separated by alphabet
(
~charArray = [ ];

~getValues  = Routine.new({
	var ascii;
	{
		ascii = ~port.read.asAscii;
		if(ascii.isDecDigit, {~charArray = ~charArray.add(ascii)});
		if(ascii == $a, {
			//convert ~charArray to integer then empty ~charArray
			~val = ~charArray.collect(_.digit).convertDigits;
			~charArray = [ ];

		});
		if (ascii == $b, {
			//convert ~charArray to integer then empty ~charArray
			~val2 = ~charArray.collect(_.digit).convertDigits;
			~charArray= [ ];
		});
		if (ascii == $c, {
			//convert ~charArray to integer then empty ~charArray
			~valx = ~charArray.collect(_.digit).convertDigits;
			~charArray= [ ];

		});
		if (ascii == $d, {
			//convert ~charArray to integer then empty ~charArray
			~valy = ~charArray.collect(_.digit).convertDigits;
			~charArray= [ ];

		});
		if (ascii == $e, {
			//convert ~charArray to integer then empty ~charArray
			~valz = ~charArray.collect(_.digit).convertDigits;
			~charArray= [ ];

		});

	}.loop;
}).play

)
//test if i am gettinf the values right
~val;
~val2;
~valx;
~valy;
~valz;

//SynthDeft any sound you want to make!!

(
SynthDef.new(\sound1,{
	arg cutoff = 1000;
	var sig;
	sig = Saw.ar([50,51]);
	sig = RLPF.ar(sig, cutoff.lag(0.02), 0.25, 0.2);
	Out.ar(0,sig);
}).add;
)

(
SynthDef.new(\sound2, {arg freq=100, dur=3, amp=0.5, cutoff2 = 500;
	var a;
	var out;
	a = Saw.ar([50,51]);
	a = RLPF.ar(a, cutoff2.lag(0.02), 0.25, 0.2);
	out = Out.ar([0, 1], a);
}).add;
)

//~synth2 = Synth(\sound2, [\freq, rrand(100, 500), 3, 0.1, \amp, 0.5, \cutoff2, 50])


//drum
(
SynthDef("Drum_Sound", {arg baseFreq = 80, dur = 1, amp=1;
	var freqEnv, ampEnv, lowPass;
	//Freq
	freqEnv = EnvGen.kr(
		Env(levels: [6*amp, 1],
			times: [0.1],
			curve: \exp),
		gate: 1) * baseFreq;
	//Amp
	ampEnv = EnvGen.kr(
		Env.perc(
			attackTime: 0.001,
			releaseTime: 0.2),
		1, levelScale: 5*amp,
		doneAction:2);
	// Noise
	lowPass = LPF.ar(
		in: WhiteNoise.ar(1),
		freq: 200) * ampEnv;

	Out.ar([0,1],  SinOsc.ar(freqEnv, 0, ampEnv) + lowPass);
}).load(s);
)

//
~synth= Synth(\sound1, [100, 50]);
~synth.set(\cutoff, ~valz.linexp(0, 16260, 50, 1000 ));
~synth.free;


///////////////////////////////////////////////////////////////////



~valy


//play first
(
~synth = Synth (\sound1, [\cutoff, 100]);
~synth2 = Synth(\sound2, [\freq, rrand(100, 500), 3, 0.1, \acmp, 0.5, \cutoff2, 50])
)
//play if continuously
(
~control = Routine.new({
	{
		//
		~openframeworks.sendMsg('/x',~valx.linexp(0, 15000, 0, 500 ));
		~openframeworks.sendMsg('/y',~valy.linexp(0, 15000, 0, 500 ));
		~openframeworks.sendMsg('/z',~valz.linexp(0, 15000, 0, 500 ));
		~synth.set(\cutoff, ~valx.linexp(0, 15000, 80, 4000 ));

		~synth2.set(\cutoff, ~valy.linexp(0, 15000, 80, 4000 ));

		1.wait;
		(
		if(~val < 10){
		Synth("\Drum_Sound", [300, 100, \dur, 100, \amp, 0.1] );
		~openframeworks.sendMsg('/drum',1);
		}
		);
		(
		if(~val > 10){

		~openframeworks.sendMsg('/no',1);
		}
		);



	}.loop;
}).play
)



