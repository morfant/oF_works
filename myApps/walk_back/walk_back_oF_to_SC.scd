s.meter;


(//OSCresp. PLEASE SYNTH CHECK!!
var realtime = True;
var oscRespBar, oscRespBH;
var synNode1, synNodeBH, synNode3, synNodeBlock, synReset;
var outBus = 0;

oscRespBH = OSCresponder(nil, '/BLACKHOLE', {| a, b, msg | if(realtime == False, {msg.postln});
		if(msg[1] == 1, {synNodeBH = Synth(\but2);}, {synNodeBH.free;})
		}).add;
//				arg id = 0, beat = 5, offset = 2950, amp = 0.2;

oscRespBar = Array.newClear(16);

for(0, 15, {| i |
	oscRespBar[i].remove;
});

for(0, 15, {| i |

	oscRespBar[i] = OSCresponder(nil, '/BALL_HIT', {| a, b, msg | if(realtime == False, {msg.postln});
	synNode1 = Synth(\ssin, [
	\freq, 170 + (msg[1] * 80),
	\atkTime, 0.01,
	\amp, ((msg[2]/100.0) / (msg[3] * 2)) - 0.5,
	\filfreq, 800 + (msg[4]/100.0) * 200];
	)
		}).add;
});

SynthDef(\ssin,
{
	| ob = 0, freq = 380, ranRange = 80, amp = 0.5, atkTime = 0.5, atkAmp = 0.7, gate = 1, filfreq = 250 |
	var sig, env, psig, fil;
	sig = SinOsc.ar(freq, amp);
	fil = Ringz.ar(sig, filfreq, 0.1);
	env = EnvGen.kr(Env.new([0.0, atkAmp, atkAmp - 0.2, 0], [atkTime, 0.1, 0.7]), gate: gate, doneAction: 2);
	psig = Pan2.ar(fil * env, 0);
	Out.ar(ob, psig);
	}
).send(s);

//2 low_beat
SynthDef.new(\but2,
				{
				arg id = 0, beat = 5, offset = 2950, amp = 0.2;
				var sig1, sig2, sig3, out;
				RandID.ir(id);
				sig1 = LFSaw.ar(1/2) * SinOsc.ar(LFNoise1.kr(1).range(2998-offset, 3002-offset)); //100 or  80
				sig2 = Delay1.ar(sig1);
				sig3 = LFNoise0.ar(beat, mul: amp);
				out  = Out.ar(0, Pan2.ar((sig1 + sig2)*sig3, 0) * 1);
				}
		).send(s);


);



a = Synth(\but2);
a = Synth(\nn);
b = Synth(\glue, [\freq, 100]);
a = Synth(\ssin, [\amp, 0.5, \atkTime, 3]);
a.release(1);