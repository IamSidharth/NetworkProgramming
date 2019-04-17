set ns [new Simulator]

set f [open out.tr w]
$ns trace-all $f

set nf [open out.nam w]
$ns namtrace-all $nf


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n4 1Mb 10ms RED
$ns duplex-link $n1 $n4 1Mb 10ms RED
$ns duplex-link $n2 $n4 1Mb 10ms RED
$ns duplex-link $n3 $n4 1Mb 10ms RED

set udp0 [new Agent/UDP]
set null3 [new Agent/Null]

set udp1 [new Agent/UDP]
set null2 [new Agent/Null]



$ns attach-agent $n0 $udp0
$ns attach-agent $n3 $null3


$ns attach-agent $n1 $udp1
$ns attach-agent $n2 $null2


$ns connect $udp0 $null3
$ns connect $udp1 $null2

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp0
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1mb
$cbr1 set random_ false

proc finish {} {
	global ns nf f
	$ns flush-trace
	close $nf
	close $f
	exec nam out.nam &
	exit 0
}

$ns at 0.5 "$cbr start"
$ns at 1.5 "$cbr1 start"

$ns at 3.5 "$cbr stop"
$ns at 4.5 "$cbr1 stop"

$ns at 5 "finish"

$ns run




