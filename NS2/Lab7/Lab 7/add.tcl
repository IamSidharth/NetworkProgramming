set ns [new Simulator]

set f [open out.tr w]
$ns trace-all $f

set nf [open out.nam w]
$ns namtrace-all $nf

for {set i 0} {$i < 12} {incr i} {
  set n($i) [$ns node]
}

for {set i 2} {$i < 7} {incr i} {
  $ns duplex-link $n($i) $n(0) 10Mb 20ms RED
}

for {set i 7} {$i < 12} {incr i} {
  $ns duplex-link $n($i) $n(1) 10Mb 20ms RED
}

$ns duplex-link $n0 $n1 1.5Mb 40ms RED

for {set i 1} {$i < 6} {incr i} {
  set tcp($i) [new Agent/TCP]
  set tcpsink($i) [new Agent/TCPSink]
  $ns attach-agent $n1 $tcp($i)
  $ns attach-agent $n($i) $tcpsink($i)
  $ns connect $tcp $tcpsink
}
