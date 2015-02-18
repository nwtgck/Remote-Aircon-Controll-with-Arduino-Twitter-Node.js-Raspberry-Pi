@signal;

while(<STDIN>){
	chomp;
	if($_ != "\n"){
		@signal = (@signal, $_);
	}
}

for($i = 0; $i <= $#signal; $i+=2){
	if($signal[$i+1] >= 100){
		print "0, ";
	} else {
		print "1, ";
	}
}



