set ns [new Simulator]

set val(rate) [lindex $argv 0]

set nf [open out_$val(rate).nam w]
$ns namtrace-all $nf

set f [open out_$val(rate).tr w]
$ns trace-all $f

for {set i 0} {$i < 3} {incr i} {
  set n($i) [$ns node]
}

$ns duplex-link $n(0) $n(1) 1Mb 50ms DropTail
$ns duplex-link $n(1) $n(2) 100Kb 5ms DropTail

$ns duplex-link-op $n(0) $n(1) orient right
$ns duplex-link-op $n(1) $n(2) orient right

set udp [new Agent/UDP]
$ns attach-agent $n(0) $udp

set udp_sink [new Agent/Null]
$ns attach-agent $n(2) $udp_sink

$ns connect $udp $udp_sink

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set rate_ $val(rate)Kb

proc finish {} {
  global ns nf f
  $ns flush-trace
  close $nf
  close $f
  exit 0
}

$ns at 0.0 "$n(0) label Source"
$ns at 0.0 "$n(1) label Router"
$ns at 0.0 "$n(2) label Target"

$ns at 0.1 "$cbr start"

$ns at 9.0 "$cbr stop"

$ns at 10.0 "finish"

$ns run
