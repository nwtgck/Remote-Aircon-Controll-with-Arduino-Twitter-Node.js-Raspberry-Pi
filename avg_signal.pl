# リーダー部のあとには、560, 1144, 532, 288, 548, ....と続く
# この数値は２つ区切りで意味をなしていて、　
# (560, 1144), (532, 288), (548, ...
# と読めばいい。読み方は、
# (0), (1), (1), (...
# となる。先頭の数は小さく、その後の数値が1275に近いか、425に近いかで0, 1が決まる
# 1275に近いなら0, 425に近いなら1になる。
# このプログラムは先頭の数の平均値とその後の数値の平均値を算出している

# http://entropiajp.hatenablog.com/entry/2014/08/24/011011

@signal;

while(<STDIN>){
	chomp;
	@signal = (@signal, $_);
}

$head = 0;
$head_cnt = 0;

$tail0 = 0;
$tail0_cnt = 0;
$tail1 = 0;
$tail1_cnt = 0;

for($i = 0; $i < $#signal; $i+=2){
	$head += $signal[$i];
	$head_cnt++;
	if($signal[$i+1] >= 100){
		# tail is 0
		$tail0 += $signal[$i+1];
		$tail0_cnt++;
	} else {
		# tail is 1
		$tail1 += $signal[$i+1];
		$tail1_cnt++;
	}
}

print "head avg\t".($head / $head_cnt)."\n";
print "tail0 avg\t".($tail0 / $tail0_cnt)."\n";
print "tail1 avg\t".($tail1 / $tail1_cnt)."\n";

# 結果は以下のようになり、上記のサイトで1210, 470, 360というマジックナンバーの意味がわかった
# head avg	473.809128630705
# tail0 avg	1210.1592920354
# tail1 avg	362.9375
