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
$ns duplex-link $n4 $n3 1Mb 10ms RED
$ns duplex-link $n4 $n2 1Mb 10ms RED

$ns duplex-link-op $n0 $n4  orient right-down
$ns duplex-link-op $n1 $n4  orient left-down
$ns duplex-link-op $n4 $n3  orient right-down
$ns duplex-link-op $n4 $n2  orient left-down

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1

set udpsink0 [new Agent/Null]
$ns attach-agent $n3 $udpsink0

set udpsink1 [new Agent/Null]
$ns attach-agent $n2 $udpsink1

$ns connect $udp0 $udpsink0
$ns connect $udp1 $udpsink1

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

proc finish {} {
  global ns nf f
  $ns flush-trace
  close $nf
  close $f
  exec nam out.nam & 
  exit 0
}

$ns at 0.1 "$cbr0 start"
$ns at 0.1 "$cbr1 start"

$ns at 9.0 "$cbr0 stop"
$ns at 9.0 "$cbr1 stop"

$ns at 10.0 "finish"

$ns run
