(
// Synthdef
SynthDef(\blackholeVoice, { |out=0, strength=0, mode=1, pan=0, id = 0|
    var mag, freqBase, freq, tone, noisy, sig, env, step, stepVal, stepArray, stepArrayM, stepArraym;
    var ii;
    stepArrayM = [2, 3, 2, 0, 2, 2, 2, 1]*2;
    stepArraym = [2, 5, 3, 7, 1, 9, 2, 1]*1;

    stepArray = stepArrayM++stepArraym;

    stepArray.postln;

    // strength.poll;
    // 크기 -> 0..1 로 정규화 (strength 범위에 맞게 숫자 조절)
    mag = strength.abs.clip(0, 70).linlin(0, 70, 0, 1);

    // mode.poll(1, \mode);
    ii = (mode * 8) + ((id % 8) % 8);
    // ii.poll(1, \ii);
    // id를 0~(배열길이-1) 로 접어 넣기 (mod 연산)
    stepVal = Select.kr(ii, stepArray);

    // 각 블랙홀마다 기본 주파수 다르게 (id 로 분산)
    freqBase = (36 + (mode * 8) + ((id % 16) + stepVal)).midicps;

    freq = freqBase;

    // attraction: 부드러운 톤, repulsion: 거친 노이즈
    // tone  = SinOscFB.ar(freq) * (mag.linexp(0, 1, -60.dbamp, -30.dbamp));
    tone =  SinOscFB.ar(freq, mag*0.3, mag/64);
    tone = Ringz.ar(tone, freq + strength.clip(-70, 70), 0.001);
    // tone = Resonz.ar(tone, freq + strength.linlin(-70, 70, freq, freq*3).clip(-70, 70), 0.5);

    // mode > 0 이면 tone 쪽, mode < 0 이면 noisy 쪽으로 보간
    // sig = SelectX.ar(mode > 0, [noisy, tone]);
    sig = tone;

    // 패닝: x 좌표를 -1..1 로 매핑해서 넣을 예정
    sig = Pan2.ar(sig, pan, 1);

    Out.ar(out, sig);
}).add;
)


(
a = Synth(\blackholeVoice, [
        \id, 31,
        \strength, 200,
        \mode, 1,
        \pan, 0
    ]);
);

(
a.set(
    \id, 5 ,
        \strength, 60,
        \mode, 0,
        \pan, 0
    );
);
