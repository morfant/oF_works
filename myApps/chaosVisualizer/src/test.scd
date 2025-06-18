(
SynthDef(\bufReader2, {
	|out=0, rate=1.0, amp=0.2, x = 0, y = 0|

	var sig, pos, bufFrames;

	// 현재 버퍼 프레임 수 구함
	bufFrames = ~voice.numFrames.postln;
	// bufFrames.poll(10, \bl);

	pos = ((1200*y + x)/(1200 * 800)) * bufFrames;
	pos.poll(10, \pos);

	// BufRd: 버퍼에서 위치 기반으로 읽기 (linear interpolation)
	sig = BufRd.ar(2, ~voice, K2A.ar(pos), loop: 0);

	// 출력
	Out.ar(out, sig * amp ! 2);
}).add;
)


a = Synth(\bufReader2)

a.set(\x, MouseX.kr(0, 120), \y, MouseY.kr(0, 80))

(
fork{
	1000.do{|i|
		a.set(\x, i, \y, i);
		0.001.wait;
	}
}
)

~voice.numFrames