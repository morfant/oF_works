~voice = Buffer.readChannel(s, ~path1, channels: [0, 0]);
~voice = Buffer.readChannel(s, "sample.ogg".resolveRelative, channels: [0, 0]);
~ambi = Buffer.read(s, "2015_jiyeon_spacelike.wav".resolveRelative, action: {"Buffer load done!".postln});

~voice.play
~voice.query

~ambi.play

a =Synth(\latooConv, [\buf, ~ambi])

(
// Synthdef
SynthDef(\latooConv, {
    arg buf = ~ambi, mul = 0.0, abcd = #[1.572, 1.372, 1.429, 1.229],
    xi = 0.1, yi = 0.1, rate = s.sampleRate/2,
    amp = 0.5, isConv = 1;

    var sig, radio, pk;
    sig = LatoocarfianN.ar(rate, abcd[0], abcd[1], abcd[2], abcd[3], xi, yi, mul: 0.1);
    sig = LeakDC.ar(sig);
    sig = RLPF.ar(sig, [100, 120]*2, 0.3);

    radio = PlayBuf.ar(2, buf, BufRateScale.kr(buf) * 0.9, startPos: s.sampleRate * 2.0, loop: 1);

    sig = Convolution.ar(radio, sig, 1024);

    // SendReply.ar(Impulse.ar(32), '/processing/peak', PeakFollower.ar(sig));

    // sig = if(isConv, radio * 0.1, sig);


    sig = FreeVerb2.ar(sig[0], sig[1], 0.5);



    Out.ar(0, sig * amp * mul!2);

}).add;




SynthDef(\latoo, {
    arg buf = ~ambi, mul = 0.0, abcd = #[1.572, 1.372, 1.429, 1.229],
    xi = 0.1, yi = 0.1, rate = s.sampleRate/2,
    amp = 0.5, isConv = 1;

    var sig, radio, pk;
    sig = LatoocarfianN.ar(rate, abcd[0], abcd[1], abcd[2], abcd[3], xi, yi, mul: 0.1);
    sig = LeakDC.ar(sig);
    sig = RLPF.ar(sig, [100, 120]*2, 0.3);

    radio = PlayBuf.ar(buf.numChannels, buf, BufRateScale.kr(buf) * 0.9, loop: 1);


    SendReply.ar(Impulse.ar(32), '/processing/peak', PeakFollower.ar(sig));

    sig = if(isConv, radio * 0.1, sig);


    sig = FreeVerb2.ar(sig[0], sig[1], 0.5);



    Out.ar(0, sig * amp * mul!2);

}).add;


SynthDef(\seedSound, {
    |freq = 440, amp = 0.2, x = 0.5, y = 0.5|

    var sig;

    // x와 y 값을 기반으로 주파수를 조절 (예시)
    var dynamicFreq = freq * ((x * 120) + (y * 80)/(120 * 80));  // x, y 좌표 반영

    sig = SinOsc.ar(dynamicFreq) * amp;

    Out.ar(0, sig.dup);
}).add;


// SynthDef(\bufReader, {
//     |out=0, rate=1.0, amp=0.2, x = 0, y = 0|
//
//     var sig, pos, bufFrames;
//
//     // 현재 버퍼 프레임 수 구함
//     bufFrames = BufFrames.kr(~voice);
//
//     pos = ((x * 120) + (y * 80)/(120 * 80)) * bufFrames;
//
//     // BufRd: 버퍼에서 위치 기반으로 읽기 (linear interpolation)
//     sig = BufRd.ar(1, ~voice, K2A.ar(pos), loop: 0);
//
//     // 출력
//     Out.ar(out, sig * amp ! 2);
// }).add;


SynthDef(\bufReader, {
    arg out = 0, bufnum, speed = 1.0, amp = 0.2, pan = 0.0;
    var frames, phase, sig;
    // 버퍼의 전체 프레임 수
    frames = BufFrames.kr(bufnum);
    // Phasor: 초기 phase는 0, increment로 speed를 사용, phase 범위는 0 ~ frames
    phase = Phasor.ar(
        0,
        speed * BufRateScale.kr(bufnum),  // speed 값에 BufRateScale을 곱해 보정
        0,
        frames,
        0
    );
    sig = BufRd.ar(2, bufnum, phase, loop: 1, interpolation: 4);
    Out.ar(out, Pan2.ar(sig, pan, amp));
}).add;



// OSC
/* RECEIVE */

// Rate
OSCdef(\latooRate, { |msg|
    var r;
    r = msg[1];
    ["Latoocarfian Rate: r=", r].postln;
    ~syn_latoo.set(\rate, r);
}, '/rate/latoo');

// 초기값 수신
OSCdef(\latooInit, { |msg|
    var x, y;
    #x, y = msg[1..2];
    ["Latoocarfian Init: x=", x, "y=", y].postln;
    ~syn_latoo.set(\xi, x, \yi, y);
}, '/init/latoo');

// a, b, c, d 파라미터 수신
OSCdef(\latooParams, { |msg|
    var a, b, c, d;
    #a, b, c, d = msg[1..4].round(0.001);
    // [a, b, c, d].postln;
    ~syn_latoo.set(\abcd, [a, b, c, d]);
}, '/latoo');

// mul 제어
OSCdef(\latooMul, { |msg|
    var mul;
    mul = msg[1];
    if (mul == 0, {
        ~syn_latoo.free;

        // 모든 Seed Synth 제거
        if (~seedSynths.notNil) {
            ~seedSynths.do { |synth, id|
                ("Freeing seed synth ID: " ++ id).postln;
                synth.free;
            };
            ~seedSynths.clear;
        };

    }, {
                ~syn_latoo = Synth(\latooConv, [\buf, ~ambi]);
        ~syn_latoo.set(\mul, 0.5);
    });
}, '/latoo/mul');


// seed 별로 Synth를 개별 생성 및 관리
~seedSynths = IdentityDictionary.new;

OSCdef(\seedPosWithID, { |msg|
    var id = msg[1].asInteger;
    var x = msg[2].asInteger;
    var y = msg[3].asInteger;
    var xx = 0, width = 1200;
    [id, x, y].postln;
    xx = x * 0.0001 * (~voice.numFrames / width);
    xx.postln;

    if (~seedSynths[id].notNil) {
        // 기존 Synth가 있다면 업데이트
        ~seedSynths[id].set(\speed, xx, \bufnum, ~voice);

    } {
        // 없으면 새로 생성
        // ~seedSynths[id] = Synth(\seedSound, [
        ~seedSynths[id] = Synth(\bufReader, [
            \speed, xx,
            \amp, 0.5
        ]);
    };
}, "/seed/vel");

OSCdef(\removeSeed, { |msg|
    var id = msg[1];
    ("Removing Synth for Seed ID: " ++ id).postln;
    ~seedSynths[id].free;
    ~seedSynths.removeAt(id);
}, "/seed/remove");


OSCdef(\shutdown, { |msg|
    "Received shutdown: %\n".postf(msg);

    // 모든 Seed Synth 제거
    if (~seedSynths.notNil) {
        ~seedSynths.do { |synth, id|
            ("Freeing seed synth ID: " ++ id).postln;
            synth.free;
        };
        ~seedSynths.clear;
    };


    ~syn_latoo.free;
}, '/shutdown');



/* SEND */
~pr = NetAddr("localhost", 12000);

// amp를 Pr로 보내기
OSCdef(\sendPeak, { |msg|
    var amp, n = 5;
    amp = (msg[3] + msg[4]) * 0.5;
    // amp = n * amp.round(0.001).postln;

    // amp.postln;
    if (amp < 0.01, {
        ~syn_latoo.set(\isConv, 1);
        // "isConv is 1".postln;

    },{
        ~syn_latoo.set(\isConv, 0);
        // "isConv is 0".postln;

    });
    // OSC로 amp를 송신
    ~pr.sendMsg("/amp", amp);

}, '/processing/peak');


)




