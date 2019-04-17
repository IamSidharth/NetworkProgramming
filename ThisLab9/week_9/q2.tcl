set ns [new Simulator]

$ns color 1 red

set val(bw) [lindex $argv 0]

set nf [open out_$val(bw).nam w]
$ns namtrace-all $nf

set f [open out_$val(bw).tr w]
$ns trace-all $f

for {set i 0} {$i < 8} {incr i} {
  set n($i) [$ns node]
}

$n(1) shape box
$n(1) color red

$ns duplex-link $n(0) $n(2) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 1Mb 10ms DropTail
$ns duplex-link $n(3) $n(4) 1Mb 10ms DropTail
$ns duplex-link $n(4) $n(6) 1Mb 10ms DropTail
$ns duplex-link $n(3) $n(5) 1Mb 10ms DropTail
$ns duplex-link $n(5) $n(7) 1Mb 10ms DropTail

$ns duplex-link $n(2) $n(3) $val(bw)Mb 10ms DropTail

$ns duplex-link-op $n(2) $n(3) orient right
$ns duplex-link-op $n(3) $n(4) orient right-up
$ns duplex-link-op $n(3) $n(5) orient right-down
$ns duplex-link-op $n(4) $n(6) orient right
$ns duplex-link-op $n(5) $n(7) orient right
$ns duplex-link-op $n(2) $n(0) orient left-up
$ns duplex-link-op $n(2) $n(1) orient left-down

set tcp [new Agent/TCP]
$ns attach-agent $n(0) $tcp

set tcp_sink [new Agent/TCPSink]
$ns attach-agent $n(6) $tcp_sink

$ns connect $tcp $tcp_sink

set udp [new Agent/UDP]
$ns attach-agent $n(1) $udp

set udp_sink [new Agent/Null]
$ns attach-agent $n(7) $udp_sink

$ns connect $udp $udp_sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

proc finish {} {
  global ns nf f
  $ns flush-trace
  close $nf
  close $f
  exit 0
}

$ns at 0.1 "$ftp start"
$ns at 0.1 "$cbr start"

$ns at 0.9 "$ftp stop"
$ns at 0.9 "$cbr stop"

$ns at 10.0 "finish"

$ns run
