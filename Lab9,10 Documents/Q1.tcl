set ns [new Simulator]

# use dynamic routing

set nm [open out.nam w]
$ns namtrace-all $nm

set nf [open out.tr w]
$ns trace-all $nf

set nt [open out.tr w]
$ns trace-all $nt

proc finish {} {
	global ns nm nt
	$ns flush-trace
	close $nm
	close $nt
	exec nam out.nam
	exit 0
}

# create 5 nodes
for {set i 0} {$i < 5} {incr i} {
	set n($i) [$ns node]
}

# connect nodes to n4 (center)
for {set i 0} {$i < 4} {incr i} {
	$ns duplex-link $n($i) $n(4) 1Mb 10ms DropTail
}


# create a udp agent and attach to n0 (traffic source)
set udp0 [new Agent/UDP]
$ns attach-agent $n(0) $udp0

# create CBR(Constant Bit Rate) traffic and attach to udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

# create null traffic sink at n(3)
set null0 [new Agent/Null]
$ns attach-agent $n(3) $null0

# connect udp0 to null0
$ns connect $udp0 $null0

# create a udp agent and attach to n1 (traffic source)
set udp1 [new Agent/UDP]
$ns attach-agent $n(1) $udp1

# create CBR(Constant Bit Rate) traffic and attach to udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
$cbr1 attach-agent $udp1

set null1 [new Agent/Null]
$ns attach-agent $n(2) $null1

$ns connect $udp1 $null1

# event scheduling
$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

$ns at 4.6 "$cbr1 start"
$ns at 9.9 "$cbr1 stop"

# call finish at 5 sec
$ns at 10.0 "finish"

# run the sim
$ns run
